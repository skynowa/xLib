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
    _m_hHandle(),
    _m_sName  ()
{
#if xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    // sem_init
#endif
}
//---------------------------------------------------------------------------
CxIpcSemaphore::~CxIpcSemaphore() {
    /*DEBUG*/// n/a

#if xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    int iRv = ::sem_close(_m_hHandle);
    /*DEBUG*/xASSERT_DO(- 1 != iRv, return);

    // sem_destroy
    // sem_unlink
#endif
}
//---------------------------------------------------------------------------
const CxIpcSemaphore::handle_t &
CxIpcSemaphore::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
bool
CxIpcSemaphore::bCreate(
    const long_t         &cliInitialValue,
    const long_t         &cliMaxValue,
    const std::tstring_t &csName
)
{
    /////*DEBUG*/xASSERT_RET(false == _m_hHandle.bIsValid(),                      false);
    /*DEBUG*/xASSERT_RET(0L <= cliInitialValue && cliInitialValue <= cliMaxValue, false);
    /*DEBUG*/xASSERT_RET(CxPath::uiGetMaxSize() > csName.size(),                  false);

#if xOS_ENV_WIN
    const tchar_t *pcszWinName = NULL;
    std::tstring_t _sWinName;

    if (true == csName.empty()) {
        pcszWinName = NULL;
    } else {
        _sWinName   = xT("Global\\") + csName;
        pcszWinName = _sWinName.c_str();
    }

    HANDLE hRv = ::CreateSemaphore(NULL, cliInitialValue, cliMaxValue, pcszWinName);
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);

    _m_hHandle.bSet(hRv);
    _m_sName = csName;
#elif xOS_ENV_UNIX
    std::tstring_t sUnixName = CxConst::xUNIX_SLASH + csName;

    handle_t hHandle = ::sem_open(sUnixName.c_str(), O_CREAT, 0777, cliInitialValue);///////////////////////
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
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
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

    handle_t hHandle = ::sem_open(sUnixName.c_str(), O_RDWR, 0777, 0U); ///////////////////////
    /*DEBUG*/xASSERT_RET(SEM_FAILED != hHandle, false);

    _m_hHandle = hHandle;
    _m_sName   = sUnixName;
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxIpcSemaphore::bRelease(
    const long_t &cliReleaseValue,
    long_t       *pliOldValue
) const
{
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
    /*DEBUG*///liReleaseValue - n/a
    /*DEBUG*///pliOldValue    - n/a

#if xOS_ENV_WIN
    BOOL blRes = ::ReleaseSemaphore(_m_hHandle.hGet(), cliReleaseValue, pliOldValue);
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
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
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
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), - 1L);

    long_t liRv = - 1L;

#if xOS_ENV_WIN
    bool bRv = bRelease(0L, &liRv);
    /*DEBUG*/xASSERT_RET(true == bRv, - 1L);
#elif xOS_ENV_UNIX
    int iValue = - 1;

    int iRv = ::sem_getvalue(_m_hHandle, &iValue);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, - 1L);

    liRv = iValue;
#endif

    return liRv;
}
//---------------------------------------------------------------------------
bool
CxIpcSemaphore::bReset(
    const long_t &cliInitialValue,
    const long_t &cliMaxValue
)
{
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(),                     false);
    /*DEBUG*/xASSERT_RET(0 <= cliInitialValue && cliInitialValue <= cliMaxValue, false);

#if xOS_ENV_WIN
    bool bRv = false;

    bRv = _m_hHandle.bClose();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    bRv = bCreate(cliInitialValue, cliMaxValue, _m_sName);
    /*DEBUG*/xASSERT_RET(true == bRv, false);
#elif xOS_ENV_UNIX
    #if xTODO
        void Reset(int init = 0)    {
            ::sem_destroy(&S);
            ::sem_init(&S, 0, init);
        }
    #endif
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
