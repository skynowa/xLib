/**
 * \file  CxIpcSemaphore.inl
 * \brief semaphore (interprocess)
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxPath.h>

#if   xOS_ENV_WIN
    // lib: n/a
#elif xOS_ENV_UNIX
    // lib: -lrt
#endif


xNAMESPACE2_BEGIN(xlib, sync)

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
    _handle(xPTR_NULL),
#endif
    _name  ()
{
    xTEST_EQ(_isValid(), false);

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
    xTEST_EQ(_isValid(), true);

#if   xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    int_t iRv = ::sem_close(_handle);  _handle = xPTR_NULL;
    xTEST_DIFF(iRv, - 1);

    // sem_destroy
    // sem_unlink
#endif
}
//-------------------------------------------------------------------------------------------------
inline const CxIpcSemaphore::handle_t &
CxIpcSemaphore::handle() const
{
    xTEST_EQ(_isValid(), true);

    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::create(
    clong_t         &a_initialValue,
    std::ctstring_t &a_name
)
{
    xTEST_EQ(_isValid(), false);
    xTEST_GR(CxPath::maxSize(), a_name.size());
    xTEST_EQ(0L <= a_initialValue && a_initialValue <= xSEMAPHORE_VALUE_MAX, true);

#if   xOS_ENV_WIN
    ctchar_t       *winName = xPTR_NULL;
    std::tstring_t  _winName;

    if (a_name.empty()) {
        winName  = xPTR_NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE  hRv       = ::CreateSemaphore(xPTR_NULL, a_initialValue, xSEMAPHORE_VALUE_MAX, winName);
    ulong_t lastError = CxLastError::get();
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);
    xTEST_DIFF(lastError, static_cast<ulong_t>( ERROR_ALREADY_EXISTS ));

    _handle.set(hRv);
    _name = a_name;
#elif xOS_ENV_UNIX
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hRv = ::sem_open(unixName.c_str(), O_CREAT | O_RDWR, 0777, a_initialValue);
    xTEST_DIFF(hRv, SEM_FAILED);

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
    xTEST_EQ(_isValid(), true);
    //name    - n/a

#if   xOS_ENV_WIN
    ctchar_t       *winName = xPTR_NULL;
    std::tstring_t  _winName;

    if (a_name.empty()) {
        winName  = xPTR_NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, winName);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
    _name = a_name;
#elif xOS_ENV_UNIX
    std::tstring_t unixName = CxConst::unixSlash() + a_name;

    handle_t hRv = ::sem_open(unixName.c_str(), O_RDWR, 0777, 0U);
    xTEST_DIFF(hRv, SEM_FAILED);

    _handle = hRv;
    _name   = unixName;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::post() const
{
    xTEST_EQ(_isValid(), true);

#if   xOS_ENV_WIN
   const LONG postValue = 1L;

   BOOL blRv = ::ReleaseSemaphore(_handle.get(), postValue, xPTR_NULL);
   xTEST_DIFF(blRv, FALSE);
#elif xOS_ENV_UNIX
    int_t iRv = ::sem_post(_handle);
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::wait(
    culong_t &a_timeoutMsec
) const
{
    xTEST_EQ(_isValid(), true);
    //ulTimeout - n/a

#if   xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);
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
        xTEST_DIFF(iRv, - 1);

        (void_t)_Functor::timespecAddMsec(&tmsTimeout, a_timeoutMsec);
    }

#if 0
    while ((iRv = ::sem_timedwait(_handle, &tmsTimeout)) == - 1 && (errno == EINTR)) {
        // Restart if interrupted by handler
        continue;
    }
#else
    int_t lastError = 0;

    for ( ; ; ) {
        iRv       = ::sem_timedwait(_handle, &tmsTimeout);
        lastError = errno;

        xCHECK_DO(! (iRv == - 1 && lastError == EINTR), break);
    }
#endif

    if (iRv == - 1) {
        if (ETIMEDOUT == lastError) {
            // timeout
            xTEST_FAIL;
        } else {
            xTEST_FAIL;
        }
    }
#elif xOS_ENV_APPLE
    xNOT_IMPLEMENTED
#endif
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxIpcSemaphore::value() const
{
    xTEST_EQ(_isValid(), true);

    long_t liRv = - 1L;

#if   xOS_ENV_WIN
    const LONG postValue = 0L;

    BOOL blRv = ::ReleaseSemaphore(_handle.get(), postValue, &liRv);
    xTEST_DIFF(blRv, FALSE);
#elif xOS_ENV_UNIX
    int_t _value = - 1;

    int_t iRv = ::sem_getvalue(_handle, &_value);
    xTEST_DIFF(iRv, - 1);

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
    return (_handle != xPTR_NULL);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, sync)
