/****************************************************************************
* Class name:  CxSemaphore
* Description: semaphore
* File name:   CxSemaphore.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 18:46:41
*
*****************************************************************************/


#include <xLib/Sync/CxSemaphore.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSemaphore
CxSemaphore::CxSemaphore() :
    _m_hSemaphore    (),
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
    /*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), NULL);

    return _m_hSemaphore.hGet();
}
//---------------------------------------------------------------------------
//DONE: bCreate (Creates or opens a named or unnamed semaphore object)
BOOL
CxSemaphore::bCreate(
    const LPSECURITY_ATTRIBUTES  pcsaAttributes,
    const LONG                   cliInitialCount,
    const LONG                   cliMaxCount,
    const tString               &csName
)
{
    /*DEBUG*/xASSERT_RET(FALSE == _m_hSemaphore.bIsValid(),                      FALSE);
    /*DEBUG*///pcsaAttributes - n/a
    /*DEBUG*/xASSERT_RET(0 <= cliInitialCount && cliInitialCount <= cliMaxCount, FALSE);
    /*DEBUG*/xASSERT_RET(MAX_PATH > csName.size(),                               FALSE);

    HANDLE hRes = NULL;

    hRes = ::CreateSemaphore(pcsaAttributes, cliInitialCount, cliMaxCount, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hSemaphore.bSet(hRes);
    _m_psaAttributes = pcsaAttributes;
    _m_sName         = csName;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
BOOL
CxSemaphore::bOpen(
    const ULONG    culAccess,
    const BOOL     cbInheritHandle,
    const tString &csName
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), FALSE);
    /*DEBUG*///culAccess - n/a
    /*DEBUG*///csName    - n/a

    HANDLE hRes = NULL;

    hRes = ::OpenSemaphore(culAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hSemaphore.bSet(hRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRelease ()
BOOL
CxSemaphore::bRelease(
    const LONG  cliReleaseCount,
    LONG       *pliOldCount
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), FALSE);
    /*DEBUG*///liReleaseCount - n/a
    /*DEBUG*///pliOldCount    - n/a

    BOOL bRes = FALSE;

    bRes = ::ReleaseSemaphore(_m_hSemaphore.hGet(), cliReleaseCount, pliOldCount);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWait ()
BOOL
CxSemaphore::bWait(
    const ULONG culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), FALSE);
    /*DEBUG*///ulTimeout - n/a

    ULONG ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hSemaphore.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: liGetValue ()
LONG
CxSemaphore::liGetValue() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(), - 1);

    LONG liRes = - 1;
    BOOL bRes  = FALSE;

    bRes = bRelease(0, &liRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, - 1);

    return liRes;
}
//---------------------------------------------------------------------------
//DONE: bReset ()
BOOL
CxSemaphore::bReset(
    const LONG cliInitialCount,
    const LONG cliMaxCount
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hSemaphore.bIsValid(),                      FALSE);
    /*DEBUG*/xASSERT_RET(0 <= cliInitialCount && cliInitialCount <= cliMaxCount, FALSE);

    BOOL bRes = FALSE;

    /*
    void Reset(int init = 0)    {
        sem_destroy(&S);

        sem_init(&S, 0, init);
    }
    */

    bRes = _m_hSemaphore.bClose();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = bCreate(_m_psaAttributes, cliInitialCount, cliMaxCount, _m_sName);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
