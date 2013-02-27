/**
 * \file  CxIpcSemaphore.cpp
 * \brief semaphore (interprocess)
 */


#include <xLib/Sync/CxIpcSemaphore.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Filesystem/CxPath.h>

#if   xOS_ENV_WIN
    // lib: n/a
#elif xOS_ENV_UNIX
    // lib: -lrt
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxIpcSemaphore::CxIpcSemaphore() :
#if   xOS_ENV_WIN
    _m_hHandle(),
#elif xOS_ENV_UNIX
    _m_hHandle(NULL),
#endif
    _m_sName  ()
{
    xTEST_EQ(false, _isValid());

#if   xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    // sem_init
#endif
}
//------------------------------------------------------------------------------
CxIpcSemaphore::~CxIpcSemaphore() {
    xTEST_EQ(true, _isValid());

#if   xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    int iRv = ::sem_close(_m_hHandle);  _m_hHandle = NULL;
    xTEST_DIFF(- 1, iRv);

    // sem_destroy
    // sem_unlink
#endif
}
//------------------------------------------------------------------------------
const CxIpcSemaphore::handle_t &
CxIpcSemaphore::handle() const {
    xTEST_EQ(true, _isValid());

    return _m_hHandle;
}
//------------------------------------------------------------------------------
void
CxIpcSemaphore::create(
    const long_t         &a_cliInitialValue,
    const std::tstring_t &a_csName
)
{
    xTEST_EQ(false, _isValid());
    xTEST_GR(CxPath::maxSize(), a_csName.size());
    xTEST_EQ(true, 0L <= a_cliInitialValue && a_cliInitialValue <= xSEMAPHORE_VALUE_MAX);

#if   xOS_ENV_WIN
    const tchar_t  *pcszWinName = NULL;
    std::tstring_t  _sWinName;

    if (true == a_csName.empty()) {
        pcszWinName = NULL;
    } else {
        _sWinName   = xT("Global\\") + a_csName;
        pcszWinName = _sWinName.c_str();
    }

    HANDLE  hRv         = ::CreateSemaphore(NULL, a_cliInitialValue, xSEMAPHORE_VALUE_MAX, pcszWinName);
    ulong_t ulLastError = CxLastError::get();
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
    xTEST_DIFF(ulLastError, static_cast<ulong_t>( ERROR_ALREADY_EXISTS ));

    _m_hHandle.set(hRv);
    _m_sName = a_csName;
#elif xOS_ENV_UNIX
    std::tstring_t sUnixName = CxConst::xUNIX_SLASH + a_csName;

    handle_t handle = ::sem_open(sUnixName.c_str(), O_CREAT | O_RDWR, 0777, a_cliInitialValue);
    xTEST_DIFF(SEM_FAILED, handle);

    _m_hHandle = handle;
    _m_sName   = sUnixName;
#endif
}
//------------------------------------------------------------------------------
void
CxIpcSemaphore::open(
    const std::tstring_t &a_csName
)
{
    xTEST_EQ(true, _isValid());
    //csName    - n/a

#if   xOS_ENV_WIN
    const tchar_t *pcszWinName = NULL;
    std::tstring_t _sWinName;

    if (true == a_csName.empty()) {
        pcszWinName = NULL;
    } else {
        _sWinName   = xT("Global\\") + a_csName;
        pcszWinName = _sWinName.c_str();
    }

    HANDLE hRv = ::OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, pcszWinName);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _m_hHandle.set(hRv);
    _m_sName = a_csName;
#elif xOS_ENV_UNIX
    std::tstring_t sUnixName = CxConst::xUNIX_SLASH + a_csName;

    handle_t handle = ::sem_open(sUnixName.c_str(), O_RDWR, 0777, 0U);
    xTEST_DIFF(SEM_FAILED, handle);

    _m_hHandle = handle;
    _m_sName   = sUnixName;
#endif
}
//------------------------------------------------------------------------------
void
CxIpcSemaphore::post() const {
    xTEST_EQ(true, _isValid());

#if   xOS_ENV_WIN
   const LONG cliPostValue = 1L;

   BOOL blRes = ::ReleaseSemaphore(_m_hHandle.get(), cliPostValue, NULL);
   xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::sem_post(_m_hHandle);
    xTEST_DIFF(- 1, iRv);
#endif
}
//------------------------------------------------------------------------------
void
CxIpcSemaphore::wait(
    const ulong_t &a_culTimeoutMsec
) const
{
    xTEST_EQ(true, _isValid());
    //ulTimeout - n/a

#if   xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(_m_hHandle.get(), a_culTimeoutMsec);
    xTEST_EQ(WAIT_OBJECT_0, dwRv);
#elif xOS_ENV_UNIX
    struct _SFunctor {
        static
        void
        timespec_addms(
            struct timespec *ts,
            long             ms
        )
        {
            int sec = 0;

            sec = ms / 1000;
            ms  = ms - sec * 1000;

            // perform the addition
            ts->tv_nsec += ms * 1000000;

            // adjust the time
            ts->tv_sec += ts->tv_nsec / 1000000000 + sec;
            ts->tv_nsec = ts->tv_nsec % 1000000000;
        }
    };


    int             iRv        = - 1;
    struct timespec tmsTimeout = {0};

    // add msec to struct timespec
    {
        iRv = ::clock_gettime(CLOCK_REALTIME, &tmsTimeout);
        xTEST_DIFF(- 1, iRv);

        (void)_SFunctor::timespec_addms(&tmsTimeout, a_culTimeoutMsec);
    }

#if xC99_OLD
    while (- 1 == (iRv = ::sem_timedwait(_m_hHandle, &tmsTimeout)) && (EINTR == errno)) {
        // Restart if interrupted by handler
        continue;
    }
#else
    int iLastError = 0;

    xFOREVER {
        iRv        = ::sem_timedwait(_m_hHandle, &tmsTimeout);
        iLastError = errno;

        xCHECK_DO(! (- 1 == iRv && EINTR == iLastError), break);
    }
#endif

    if (- 1 == iRv) {
        if (ETIMEDOUT == iLastError) {
            // timeout
            xTEST_FAIL;
        } else {
            xTEST_FAIL;
        }
    }
#endif
}
//------------------------------------------------------------------------------
long_t
CxIpcSemaphore::value() const {
    xTEST_EQ(true, _isValid());

    long_t liRv = - 1L;

#if   xOS_ENV_WIN
    const LONG cliPostValue = 0L;

    BOOL blRv = ::ReleaseSemaphore(_m_hHandle.get(), cliPostValue, &liRv);
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    int iValue = - 1;

    int iRv = ::sem_getvalue(_m_hHandle, &iValue);
    xTEST_DIFF(- 1, iRv);

    liRv = iValue;
#endif

    return liRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
bool
CxIpcSemaphore::_isValid() const {
#if   xOS_ENV_WIN
    return _m_hHandle.isValid();
#elif xOS_ENV_UNIX
    return (NULL != _m_hHandle);
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
