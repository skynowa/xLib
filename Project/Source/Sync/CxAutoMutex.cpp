/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#include <xLib/Sync/CxAutoMutex.h>

#include <xLib/Sync/CxMutex.h>
#include <xLib/Sync/CxIpcMutex.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoMutex::CxAutoMutex(
    CxMutex &csCS,
    const bool         cbIsUseTry /* = false*/
) :
    _m_csCS     (csCS),
    _m_bIsLocked(false)
{
    bool bRv = false;

    bRv = csCS.bCreate();
    /*DEBUG*/xASSERT_DO(true == bRv, return);

    if (false == cbIsUseTry) {
        bRv = _m_csCS.bLock();
        /*DEBUG*/xASSERT_DO(true == bRv, return);
    } else {
        bRv = _m_csCS.bTryLock();
        /*DEBUG*/// n/a
    }

    _m_bIsLocked = bRv;
}
//---------------------------------------------------------------------------
CxAutoMutex::~CxAutoMutex() {
    if (false != _m_bIsLocked) {
        bool bRv = _m_csCS.bUnlock();
        /*DEBUG*/xASSERT_DO(true == bRv, return);
    }

    _m_bIsLocked = false;
}
//---------------------------------------------------------------------------
bool
CxAutoMutex::bIsLocked() const {
    return _m_bIsLocked;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
