/**
 * \file  CxIpcSemaphore.cpp
 * \brief semaphore
 */


#include <xLib/Sync/CxIpcSemaphore.h>

#include <xLib/Filesystem/CxPath.h>

#if   xOS_ENV_WIN
    // lib: n/a
#elif xOS_ENV_UNIX
    // lib: -lrt
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxIpcSemaphore::CxIpcSemaphore() :
#if xOS_ENV_WIN
    _m_hHandle(),
#elif xOS_ENV_UNIX
    _m_hHandle(NULL),
#endif
    _m_sName  ()
{
    /*DEBUG*/xASSERT_DO(false == _bIsValid(), return);

#if xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    // sem_init
#endif
}
//---------------------------------------------------------------------------
CxIpcSemaphore::~CxIpcSemaphore() {
    /*DEBUG*/xASSERT_DO(true == _bIsValid(), return);

#if xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    int iRv = ::sem_close(_m_hHandle);  _m_hHandle = NULL;
    /*DEBUG*/xASSERT_DO(- 1 != iRv, return);

    // sem_destroy
    // sem_unlink
#endif
}
//---------------------------------------------------------------------------
const CxIpcSemaphore::handle_t &
CxIpcSemaphore::hGet() const {
    /*DEBUG*/xASSERT(true == _bIsValid());

    return _m_hHandle;
}
//---------------------------------------------------------------------------
bool
CxIpcSemaphore::bCreate(
    const long_t         &cliInitialValue,
    const std::tstring_t &csName
)
{
    /*DEBUG*/xASSERT_RET(false                  == _bIsValid(),   false);
    /*DEBUG*/xASSERT_RET(CxPath::uiGetMaxSize() >  csName.size(), false);
    /*DEBUG*/xASSERT_RET(0L <= cliInitialValue && cliInitialValue <= xSEMAPHORE_VALUE_MAX, false);

#if xOS_ENV_WIN
    const tchar_t  *pcszWinName = NULL;
    std::tstring_t  _sWinName;
        
    if (true == csName.empty()) {
        pcszWinName = NULL;
    } else {
        _sWinName   = xT("Global\\") + csName;
        pcszWinName = _sWinName.c_str();
    }

    HANDLE  hRv         = ::CreateSemaphore(NULL, cliInitialValue, xSEMAPHORE_VALUE_MAX, pcszWinName);
    ulong_t ulLastError = CxLastError::ulGet();
    /*DEBUG*/xASSERT_RET(NULL        != hRv,                  false);
    /*DEBUG*/xASSERT_RET(ulLastError != ERROR_ALREADY_EXISTS, false);

    _m_hHandle.bSet(hRv);
    _m_sName = csName;
#elif xOS_ENV_UNIX
    std::tstring_t sUnixName = CxConst::xUNIX_SLASH + csName;

    handle_t hHandle = ::sem_open(sUnixName.c_str(), O_CREAT, 0777, cliInitialValue);
    /*DEBUG*/xASSERT_RET(SEM_FAILED != hHandle, false);

    _m_hHandle = hHandle;
    _m_sName   = sUnixName;
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxIpcSemaphore::bOpen(
    const std::tstring_t &csName
)
{
    /*DEBUG*/xASSERT_RET(true == _bIsValid(), false);
    /*DEBUG*///csName    - n/a

#if xOS_ENV_WIN
    const tchar_t *pcszWinName = NULL;
    std::tstring_t _sWinName;

    if (true == csName.empty()) {
        pcszWinName = NULL;
    } else {
        _sWinName   = xT("Global\\") + csName;
        pcszWinName = _sWinName.c_str();
    }

    HANDLE hRv = ::OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, pcszWinName);
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);

    _m_hHandle.bSet(hRv);
    _m_sName = csName;
#elif xOS_ENV_UNIX
    std::tstring_t sUnixName = CxConst::xUNIX_SLASH + csName;

    handle_t hHandle = ::sem_open(sUnixName.c_str(), O_RDWR, 0777, 0U);
    /*DEBUG*/xASSERT_RET(SEM_FAILED != hHandle, false);

    _m_hHandle = hHandle;
    _m_sName   = sUnixName;
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxIpcSemaphore::bPost() const {
    /*DEBUG*/xASSERT_RET(true == _bIsValid(), false);

#if xOS_ENV_WIN
   const LONG cliPostValue = 1L;

   BOOL blRes = ::ReleaseSemaphore(_m_hHandle.hGet(), cliPostValue, NULL);
   /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRv = ::sem_post(_m_hHandle);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxIpcSemaphore::bWait(
    const ulong_t &culTimeoutMsec
) const
{
    /*DEBUG*/xASSERT_RET(true == _bIsValid(), false);
    /*DEBUG*///ulTimeout - n/a

#if xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(_m_hHandle.hGet(), culTimeoutMsec);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == dwRv, false);
#elif xOS_ENV_UNIX
    struct _SFunctor {
        static void
        timespec_addms(struct timespec *ts, long ms) {
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
        /*DEBUG*/xASSERT_RET(- 1 != iRv, false);

        (void)_SFunctor::timespec_addms(&tmsTimeout, culTimeoutMsec);
    }

#if xC99_OLD
    while (- 1 == (iRv = ::sem_timedwait(_m_hHandle, &tmsTimeout)) && (EINTR == errno)) {
        // Restart if interrupted by handler
        continue;
    }
#else
    int iLastError = 0;

    for ( ; ; ) {
        iRv        = ::sem_timedwait(_m_hHandle, &tmsTimeout);
        iLastError = errno;

        xCHECK_DO(! (- 1 == iRv && EINTR == iLastError), break);
    }
#endif

    if (- 1 == iRv) {
        if (ETIMEDOUT == iLastError) {
            // timeout
            return false;
        } else {
            return false;
        }
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
long_t
CxIpcSemaphore::liGetValue() const {
    /*DEBUG*/xASSERT_RET(true == _bIsValid(), - 1L);

    long_t liRv = - 1L;

#if xOS_ENV_WIN
    const LONG cliPostValue = 0L;

    BOOL blRv = ::ReleaseSemaphore(_m_hHandle.hGet(), cliPostValue, &liRv);
    /*DEBUG*/xASSERT_RET(FALSE != blRv, - 1L);
#elif xOS_ENV_UNIX
    int iValue = - 1;

    int iRv = ::sem_getvalue(_m_hHandle, &iValue);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, - 1L);

    liRv = iValue;
#endif

    return liRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxIpcSemaphore::_bIsValid() const {
#if xOS_ENV_WIN
    return _m_hHandle.bIsValid();
#elif xOS_ENV_UNIX
    return (NULL != _m_hHandle);
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
