/**
 * \file  CxSemaphore.cpp
 * \brief semaphore
 */


#include <xLib/Sync/CxSemaphore.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSemaphore
CxSemaphore::CxSemaphore() :
    _m_hSemaphore   (),
    _m_psaAttributes(NULL),
    _m_sName        ()
{
}
//---------------------------------------------------------------------------
//DONE: ~CxSemaphore
CxSemaphore::~CxSemaphore() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: hGetHandle ()
HANDLE
CxSemaphore::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), NULL);

    return _m_hSemaphore.hGet();
}
//---------------------------------------------------------------------------
//DONE: bCreate (Creates or opens a named or unnamed semaphore object)
bool
CxSemaphore::bCreate(
    const LPSECURITY_ATTRIBUTES  pcsaAttributes,
    const long_t                   cliInitialCount,
    const long_t                   cliMaxCount,
    const std::tstring_t          &csName
)
{
    /*DEBUG*/xASSERT_RET(false == _m_hSemaphore.bIsValid(),                      false);
    /*DEBUG*///pcsaAttributes - n/a
    /*DEBUG*/xASSERT_RET(0 <= cliInitialCount && cliInitialCount <= cliMaxCount, false);
    /*DEBUG*/xASSERT_RET(MAX_PATH > csName.size(),                               false);

    HANDLE hRes = NULL;

    hRes = ::CreateSemaphore(pcsaAttributes, cliInitialCount, cliMaxCount, CxMacros::pcszAsCString(csName));
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hSemaphore.bSet(hRes);
    _m_psaAttributes = pcsaAttributes;
    _m_sName         = csName;

    return true;
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
bool
CxSemaphore::bOpen(
    const ulong_t         culAccess,
    const bool          cbInheritHandle,
    const std::tstring_t &csName
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), false);
    /*DEBUG*///culAccess - n/a
    /*DEBUG*///csName    - n/a

    HANDLE hRes = NULL;

    hRes = ::OpenSemaphore(culAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hSemaphore.bSet(hRes);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRelease ()
bool
CxSemaphore::bRelease(
    const long_t  cliReleaseCount,
    long_t       *pliOldCount
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), false);
    /*DEBUG*///liReleaseCount - n/a
    /*DEBUG*///pliOldCount    - n/a

    BOOL bRes = ::ReleaseSemaphore(_m_hSemaphore.hGet(), cliReleaseCount, pliOldCount);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bWait ()
bool
CxSemaphore::bWait(
    const ulong_t culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), false);
    /*DEBUG*///ulTimeout - n/a

    ulong_t ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hSemaphore.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: liGetValue ()
long_t
CxSemaphore::liGetValue() const {
    /*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(), - 1);

    long_t liRes = - 1;
    bool bRes  = false;

    bRes = bRelease(0, &liRes);
    /*DEBUG*/xASSERT_RET(true == bRes, - 1);

    return liRes;
}
//---------------------------------------------------------------------------
//DONE: bReset ()
bool
CxSemaphore::bReset(
    const long_t cliInitialCount,
    const long_t cliMaxCount
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hSemaphore.bIsValid(),                      false);
    /*DEBUG*/xASSERT_RET(0 <= cliInitialCount && cliInitialCount <= cliMaxCount, false);

    bool bRes = false;

    /*
    void Reset(int init = 0)    {
        sem_destroy(&S);

        sem_init(&S, 0, init);
    }
    */

    bRes = _m_hSemaphore.bClose();
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    bRes = bCreate(_m_psaAttributes, cliInitialCount, cliMaxCount, _m_sName);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
