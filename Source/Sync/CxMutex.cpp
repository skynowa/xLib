/**
 * \file  CxMutex.cpp
 * \brief mutex
 */


#include <xLib/Sync/CxMutex.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxMutex::CxMutex() :
    _m_hHandle()
{
    /*DEBUG*/xASSERT_DO(false == _m_hHandle.bIsValid(), return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxMutex::~CxMutex() {
    /*DEBUG*/xASSERT(false != _m_hHandle.bIsValid());
}
//---------------------------------------------------------------------------
const CxMutex::TxHandle &
CxMutex::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
bool
CxMutex::bCreate(
    const LPSECURITY_ATTRIBUTES  pcsaAttributes,
    const bool                   cbInitialOwner,
    const std::tstring_t        &csName
)
{
    /*DEBUG*/xASSERT_RET(false == _m_hHandle.bIsValid(), false);
    /*DEBUG*///lpsaAttributes - n/a
    /*DEBUG*///bInitialOwner  - n/a
    /*DEBUG*///pcszName       - n/a

    HANDLE hRes = NULL;

    hRes = ::CreateMutex(pcsaAttributes, cbInitialOwner, CxMacros::pcszAsCString(csName));
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hHandle.bSet(hRes);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMutex::bRelease() const {
    /*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);

    BOOL bRes = ::ReleaseMutex(_m_hHandle.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMutex::bWait(
    const ulong_t culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hHandle.bIsValid(), false);
    /*DEBUG*///culTimeout - n/a

    ulong_t ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hHandle.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0  == ulRes, false);
    /*DEBUG*/xASSERT_RET(WAIT_ABANDONED != ulRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
