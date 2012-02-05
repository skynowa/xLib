/**
 * \file  CxSemaphore.cpp
 * \brief semaphore
 */


#include <xLib/Sync/CxSemaphore.h>

#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSemaphore::CxSemaphore() :
    _m_hSemaphore(),
    _m_sName     ()
{
}
//---------------------------------------------------------------------------
CxSemaphore::~CxSemaphore() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
const CxSemaphore::TxHandle &
CxSemaphore::hGet() const {
    /*DEBUG*/

    return _m_hSemaphore;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bCreate(
    const long_t          cliInitialCount,
    const long_t          cliMaxCount,
    const std::tstring_t &csName
)
{
    /////*DEBUG*/xASSERT_RET(false == _m_hSemaphore.bIsValid(),                       false);
    /*DEBUG*/xASSERT_RET(0L <= cliInitialCount && cliInitialCount <= cliMaxCount, false);
    /*DEBUG*/xASSERT_RET(CxPath::uiGetMaxSize() > csName.size(),                  false);

#if defined(xOS_ENV_WIN)
    HANDLE hRes = ::CreateSemaphore(NULL, cliInitialCount, cliMaxCount, CxMacros::pcszAsCString(csName));
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hSemaphore.bSet(hRes);
    _m_sName = csName;
#elif defined(xOS_ENV_UNIX)

#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bOpen(
    const ulong_t         culAccess,
    const bool            cbInheritHandle,
    const std::tstring_t &csName
)
{
    /////*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), false);
    /*DEBUG*///culAccess - n/a
    /*DEBUG*///csName    - n/a

#if defined(xOS_ENV_WIN)
    HANDLE hRes = ::OpenSemaphore(culAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hSemaphore.bSet(hRes);
#elif defined(xOS_ENV_UNIX)

#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bRelease(
    const long_t  cliReleaseCount,
    long_t       *pliOldCount
) const
{
    /////*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), false);
    /*DEBUG*///liReleaseCount - n/a
    /*DEBUG*///pliOldCount    - n/a

#if defined(xOS_ENV_WIN)
    BOOL blRes = ::ReleaseSemaphore(_m_hSemaphore.hGet(), cliReleaseCount, pliOldCount);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif defined(xOS_ENV_UNIX)

#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bWait(
    const ulong_t culTimeout
) const
{
    /////*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), false);
    /*DEBUG*///ulTimeout - n/a

#if defined(xOS_ENV_WIN)
    DWORD ulRes = ::WaitForSingleObject(_m_hSemaphore.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, false);
#elif defined(xOS_ENV_UNIX)

#endif

    return true;
}
//---------------------------------------------------------------------------
long_t
CxSemaphore::liGetValue() const {
    /////*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), - 1L);

    long_t liRes = - 1;

#if defined(xOS_ENV_WIN)
    bool bRes = bRelease(0, &liRes);
    /*DEBUG*/xASSERT_RET(true == bRes, - 1L);
#elif defined(xOS_ENV_UNIX)

#endif

    return liRes;
}
//---------------------------------------------------------------------------
bool
CxSemaphore::bReset(
    const long_t cliInitialCount,
    const long_t cliMaxCount
)
{
    /////*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(),                      false);
    /*DEBUG*/xASSERT_RET(0 <= cliInitialCount && cliInitialCount <= cliMaxCount, false);

    bool bRes = false;

#if defined(xOS_ENV_WIN)
    bRes = _m_hSemaphore.bClose();
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    bRes = bCreate(cliInitialCount, cliMaxCount, _m_sName);
    /*DEBUG*/xASSERT_RET(true == bRes, false);
#elif defined(xOS_ENV_UNIX)
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
