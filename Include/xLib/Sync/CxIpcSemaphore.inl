/**
 * \file  CxIpcSemaphore.cpp
 * \brief semaphore (interprocess)
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxPath.h>

#if   xOS_ENV_WIN
    // lib: n/a
#elif xOS_ENV_UNIX
    // lib: -lrt
#endif


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxIpcSemaphore::CxIpcSemaphore() :
#if   xOS_ENV_WIN
    _handle(),
#elif xOS_ENV_UNIX
    _handle(NULL),
#endif
    _name  ()
{
    xTEST_EQ(false, _isValid());

#if   xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    // sem_init
#endif
}
//-------------------------------------------------------------------------------------------------
inline
CxIpcSemaphore::~CxIpcSemaphore()
{
    xTEST_EQ(true, _isValid());

#if   xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    int_t iRv = ::sem_close(_handle);  _handle = NULL;
    xTEST_DIFF(- 1, iRv);

    // sem_destroy
    // sem_unlink
#endif
}
//-------------------------------------------------------------------------------------------------
inline const CxIpcSemaphore::handle_t &
CxIpcSemaphore::handle() const
{
    xTEST_EQ(true, _isValid());

    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::create(
    clong_t         &a_initialValue,
    std::ctstring_t &a_name
)
{
    xTEST_EQ(false, _isValid());
    xTEST_GR(CxPath::maxSize(), a_name.size());
    xTEST_EQ(true, 0L <= a_initialValue && a_initialValue <= xSEMAPHORE_VALUE_MAX);

#if   xOS_ENV_WIN
    ctchar_t       *winName = NULL;
    std::tstring_t  _winName;

    if (a_name.empty()) {
        winName  = NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE  hRv       = ::CreateSemaphore(NULL, a_initialValue, xSEMAPHORE_VALUE_MAX, winName);
    ulong_t lastError = CxLastError::get();
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
    xTEST_DIFF(lastError, static_cast<ulong_t>( ERROR_ALREADY_EXISTS ));

    _handle.set(hRv);
    _name = a_name;
#elif xOS_ENV_UNIX
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hRv = ::sem_open(unixName.c_str(), O_CREAT | O_RDWR, 0777, a_initialValue);
    xTEST_DIFF(SEM_FAILED, hRv);

    _handle = hRv;
    _name   = unixName;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::open(
    std::ctstring_t &a_name
)
{
    xTEST_EQ(true, _isValid());
    //name    - n/a

#if   xOS_ENV_WIN
    ctchar_t       *winName = NULL;
    std::tstring_t  _winName;

    if (a_name.empty()) {
        winName  = NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, winName);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _handle.set(hRv);
    _name = a_name;
#elif xOS_ENV_UNIX
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hRv = ::sem_open(unixName.c_str(), O_RDWR, 0777, 0U);
    xTEST_DIFF(SEM_FAILED, hRv);

    _handle = hRv;
    _name   = unixName;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::post() const
{
    xTEST_EQ(true, _isValid());

#if   xOS_ENV_WIN
   const LONG postValue = 1L;

   BOOL blRv = ::ReleaseSemaphore(_handle.get(), postValue, NULL);
   xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(- 1, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::wait(
    culong_t &a_timeoutMsec
) const
{
    xTEST_EQ(true, _isValid());
    //ulTimeout - n/a

#if   xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(WAIT_OBJECT_0, dwRv);
#elif xOS_ENV_UNIX
    struct _Functor
    {
        static void_t
        timespecAddMsec(
            timespec *a_ts,
            long      a_ms
        )
        {
            long_t sec = 0L;

            sec  = a_ms / 1000;
            a_ms = a_ms - sec * 1000;

            // perform the addition
            a_ts->tv_nsec += a_ms * 1000000;

            // adjust the time
            a_ts->tv_sec += a_ts->tv_nsec / 1000000000 + sec;
            a_ts->tv_nsec = a_ts->tv_nsec % 1000000000;
        }
    };


    int_t    iRv        = - 1;
    timespec tmsTimeout = {0, 0};

    // add msec to timespec
    {
        iRv = ::clock_gettime(CLOCK_REALTIME, &tmsTimeout);
        xTEST_DIFF(- 1, iRv);

        (void_t)_Functor::timespecAddMsec(&tmsTimeout, a_timeoutMsec);
    }

#if 0
    while (- 1 == (iRv = ::sem_timedwait(_handle, &tmsTimeout)) && (EINTR == errno)) {
        // Restart if interrupted by handler
        continue;
    }
#else
    int_t lastError = 0;

    xFOREVER {
        iRv       = ::sem_timedwait(_handle, &tmsTimeout);
        lastError = errno;

        xCHECK_DO(! (- 1 == iRv && EINTR == lastError), break);
    }
#endif

    if (- 1 == iRv) {
        if (ETIMEDOUT == lastError) {
            // timeout
            xTEST_FAIL;
        } else {
            xTEST_FAIL;
        }
    }
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxIpcSemaphore::value() const
{
    xTEST_EQ(true, _isValid());

    long_t liRv = - 1L;

#if   xOS_ENV_WIN
    const LONG postValue = 0L;

    BOOL blRv = ::ReleaseSemaphore(_handle.get(), postValue, &liRv);
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    int_t _value = - 1;

    int_t _iRv = ::sem_getvalue(_handle, &_value);
    xTEST_DIFF(- 1, _iRv);

    liRv = _value;
#endif

    return liRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxIpcSemaphore::_isValid() const
{
#if   xOS_ENV_WIN
    return _handle.isValid();
#elif xOS_ENV_UNIX
    return (NULL != _handle);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
