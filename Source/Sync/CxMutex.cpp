/**
 * \file  CxMutex.cpp
 * \brief mutex
 */


#include <xLib/Sync/CxMutex.h>


#if defined(xOS_ENV_WIN)

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxMutex
CxMutex::CxMutex() :
    _m_hMutex()
{
    /*DEBUG*/xASSERT_DO(FALSE == _m_hMutex.bIsValid(), return);
}
//---------------------------------------------------------------------------
//DONE: ~CxMutex
/*virtual*/
CxMutex::~CxMutex() {
    /*DEBUG*/xASSERT(FALSE != _m_hMutex.bIsValid());
}
//---------------------------------------------------------------------------
//DONE: hGetHandle ()
HANDLE
CxMutex::hGetHandle() const {
    /*DEBUG*/// n/a

    return _m_hMutex.hGet();
}
//---------------------------------------------------------------------------
//DONE: bCreate ()
BOOL
CxMutex::bCreate(
    const LPSECURITY_ATTRIBUTES  pcsaAttributes,
    const BOOL                   cbInitialOwner,
    const std::string_t          &csName
)
{
    /*DEBUG*/xASSERT_RET(FALSE == _m_hMutex.bIsValid(), FALSE);
    /*DEBUG*///lpsaAttributes - n/a
    /*DEBUG*///bInitialOwner  - n/a
    /*DEBUG*///pcszName       - n/a

    HANDLE hRes = NULL;

    hRes = ::CreateMutex(pcsaAttributes, cbInitialOwner, CxMacros::pcszAsCString(csName));
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hMutex.bSet(hRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
BOOL
CxMutex::bOpen(
    const ULONG         culAccess,
    const BOOL          cbInheritHandle,
    const std::string_t &csName
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), FALSE);
    /*DEBUG*///culAccess      - n/a
    /*DEBUG*///bInheritHandle - n/a
    /*DEBUG*///pcszName       - n/a

    HANDLE hRes = NULL;

    hRes = ::OpenMutex(culAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hMutex.bSet(hRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRelease ()
BOOL
CxMutex::bRelease() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::ReleaseMutex(_m_hMutex.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWait ()
BOOL
CxMutex::bWait(
    const ULONG culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hMutex.bIsValid(), FALSE);
    /*DEBUG*///culTimeout - n/a

    ULONG ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hMutex.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0  == ulRes, FALSE);
    /*DEBUG*/xASSERT_RET(WAIT_ABANDONED != ulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
