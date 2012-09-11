/**
 * \file  CxIpcMutex.cpp
 * \brief mutex
 */


#include <xLib/Sync/CxIpcMutex.h>

#if   xOS_ENV_WIN
    // lib: n/a
#elif xOS_ENV_UNIX
    // lib: -lrt
#endif

#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxIpcMutex::CxIpcMutex() :
    _m_hHandle(),
    _m_sName  ()
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxIpcMutex::~CxIpcMutex() {

}
//---------------------------------------------------------------------------
const CxIpcMutex::handle_t &
CxIpcMutex::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
bool
CxIpcMutex::bCreate(
    const std::tstring_t &a_csName
)
{
    /////*DEBUG*/xASSERT_RET(false == _m_hHandle.bIsValid(), false);
#if   xOS_ENV_WIN
    /*DEBUG*/// csName
#elif xOS_ENV_UNIX
    /*DEBUG*/xASSERT_RET(xNAME_MAX - 4 > a_csName.size(), false);
#endif

#if xOS_ENV_WIN
    const tchar_t *pcszWinName = NULL;
    std::tstring_t _sWinName;

    if (true == a_csName.empty()) {
        pcszWinName = NULL;
    } else {
        _sWinName   = xT("Global\\") + a_csName;
        pcszWinName = _sWinName.c_str();
    }

    HANDLE hRv = ::CreateMutex(NULL, FALSE, pcszWinName);
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);

    _m_hHandle.bSet(hRv);
    _m_sName = a_csName;
#elif xOS_ENV_UNIX
    std::tstring_t sUnixName = CxConst::xUNIX_SLASH + a_csName;

    handle_t hHandle = ::sem_open(sUnixName.c_str(), O_CREAT | O_RDWR, 0777, 1U);
    /*DEBUG*/xASSERT_RET(SEM_FAILED != hHandle, false);

    _m_hHandle = hHandle;
    _m_sName   = sUnixName;
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxIpcMutex::bOpen(
    const std::tstring_t &a_csName
)
{
    /*DEBUG*/

#if   xOS_ENV_WIN
    const tchar_t *pcszWinName = NULL;
    std::tstring_t _sWinName;

    if (true == a_csName.empty()) {
        pcszWinName = NULL;
    } else {
        _sWinName   = xT("Global\\") + a_csName;
        pcszWinName = _sWinName.c_str();
    }

    HANDLE hRv = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, pcszWinName);
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);

    _m_hHandle.bSet(hRv);
    _m_sName = a_csName;
#elif xOS_ENV_UNIX
    std::tstring_t sUnixName = CxConst::xUNIX_SLASH + a_csName;

    handle_t hHandle = ::sem_open(sUnixName.c_str(), O_RDWR, 0777, 1U);
    /*DEBUG*/xASSERT_RET(SEM_FAILED != hHandle, false);

    _m_hHandle = hHandle;
    _m_sName   = sUnixName;
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxIpcMutex::bLock(
    const ulong_t &a_culTimeoutMsec
) const
{
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
    /*DEBUG*///culTimeout - n/a

#if xOS_ENV_WIN
    DWORD ulRv = ::WaitForSingleObject(_m_hHandle.hGet(), a_culTimeoutMsec);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0  == ulRv, false);
    /*DEBUG*/xASSERT_RET(WAIT_ABANDONED != ulRv, false);
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

        (void)_SFunctor::timespec_addms(&tmsTimeout, a_culTimeoutMsec);
    }

    while (- 1 == (iRv = ::sem_timedwait(_m_hHandle, &tmsTimeout)) && (EINTR == errno)) {
        // Restart if interrupted by handler
        continue;
    }

    if (- 1 == iRv) {
        if (ETIMEDOUT == errno) {
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
bool
CxIpcMutex::bUnlock() const {
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);

#if xOS_ENV_WIN
    BOOL blRes = ::ReleaseMutex(_m_hHandle.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRv = ::sem_post(_m_hHandle);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
