/**
 * \file  CxSemaphore.cpp
 * \brief semaphore
 */


#include <xLib/Sync/CxSemaphore.h>

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
CxSemaphore::CxSemaphore() :
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
CxSemaphore::~CxSemaphore() {
    /*DEBUG*/// n/a

#if xOS_ENV_WIN
    xNA;
#elif xOS_ENV_UNIX
    // sem_close
    // sem_destroy
    // sem_unlink
#endif
}
//---------------------------------------------------------------------------
const CxSemaphore::handle_t &
CxSemaphore::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bCreate(
    const long_t         &cliInitialCount,
    const long_t         &cliMaxCount,
    const std::tstring_t &csName
)
{
    /////*DEBUG*/xASSERT_RET(false == _m_hHandle.bIsValid(),                      false);
    /*DEBUG*/xASSERT_RET(0L <= cliInitialCount && cliInitialCount <= cliMaxCount, false);
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

    HANDLE hRv = ::CreateSemaphore(NULL, cliInitialCount, cliMaxCount, pcszWinName);
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);

    _m_hHandle.bSet(hRv);
    _m_sName = csName;
#elif xOS_ENV_UNIX
    // sem_open
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bOpen(
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
    // sem_open
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bRelease(
    const long_t &cliReleaseCount,
    long_t       *pliOldCount
) const
{
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
    /*DEBUG*///liReleaseCount - n/a
    /*DEBUG*///pliOldCount    - n/a

#if xOS_ENV_WIN
    BOOL blRes = ::ReleaseSemaphore(_m_hHandle.hGet(), cliReleaseCount, pliOldCount);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    // sem_post
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bWait(
    const ulong_t &culTimeout
) const
{
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
    /*DEBUG*///ulTimeout - n/a

#if xOS_ENV_WIN
    DWORD dwRv = ::WaitForSingleObject(_m_hHandle.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == dwRv, false);
#elif xOS_ENV_UNIX
    // sem_wait
#endif

    return true;
}
//---------------------------------------------------------------------------
long_t
CxSemaphore::liGetValue() const {
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), - 1L);

    long_t liRv = - 1;

#if xOS_ENV_WIN
    bool bRv = bRelease(0, &liRv);
    /*DEBUG*/xASSERT_RET(true == bRv, - 1L);
#elif xOS_ENV_UNIX
    // sem_getvalue
#endif

    return liRv;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bReset(
    const long_t &cliInitialCount,
    const long_t &cliMaxCount
)
{
    /////*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(),                     false);
    /*DEBUG*/xASSERT_RET(0 <= cliInitialCount && cliInitialCount <= cliMaxCount, false);

#if xOS_ENV_WIN
    bool bRv = false;

    bRv = _m_hHandle.bClose();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    bRv = bCreate(cliInitialCount, cliMaxCount, _m_sName);
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
