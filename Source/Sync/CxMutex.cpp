/**
 * \file  CxMutex.cpp
 * \brief mutex
 */


#include <xLib/Sync/CxMutex.h>


#if xOS_ENV_WIN

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
    /*DEBUG*/xASSERT_DO(false == _m_hMutex.bIsValid(), return);
}
//---------------------------------------------------------------------------
//DONE: ~CxMutex
/*virtual*/
CxMutex::~CxMutex() {
    /*DEBUG*/xASSERT(false != _m_hMutex.bIsValid());
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
bool
CxMutex::bCreate(
    const LPSECURITY_ATTRIBUTES  pcsaAttributes,
    const bool                   cbInitialOwner,
    const std::tstring_t          &csName
)
{
    /*DEBUG*/xASSERT_RET(false == _m_hMutex.bIsValid(), false);
    /*DEBUG*///lpsaAttributes - n/a
    /*DEBUG*///bInitialOwner  - n/a
    /*DEBUG*///pcszName       - n/a

    HANDLE hRes = NULL;

    hRes = ::CreateMutex(pcsaAttributes, cbInitialOwner, CxMacros::pcszAsCString(csName));
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hMutex.bSet(hRes);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
bool
CxMutex::bOpen(
    const ulong_t         culAccess,
    const bool          cbInheritHandle,
    const std::tstring_t &csName
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hMutex.bIsValid(), false);
    /*DEBUG*///culAccess      - n/a
    /*DEBUG*///bInheritHandle - n/a
    /*DEBUG*///pcszName       - n/a

    HANDLE hRes = NULL;

    hRes = ::OpenMutex(culAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hMutex.bSet(hRes);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRelease ()
bool
CxMutex::bRelease() const {
    /*DEBUG*/xASSERT_RET(false != _m_hMutex.bIsValid(), false);

    BOOL bRes = ::ReleaseMutex(_m_hMutex.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bWait ()
bool
CxMutex::bWait(
    const ulong_t culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hMutex.bIsValid(), false);
    /*DEBUG*///culTimeout - n/a

    ulong_t ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hMutex.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0  == ulRes, false);
    /*DEBUG*/xASSERT_RET(WAIT_ABANDONED != ulRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
