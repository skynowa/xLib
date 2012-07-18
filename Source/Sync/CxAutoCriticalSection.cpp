/**
 * \file  CxAutoCriticalSection.h
 * \brief auto critical section (using between threads)
 */


#include <xLib/Sync/CxAutoCriticalSection.h>

#include <xLib/Sync/CxCriticalSection.h>
#include <xLib/Sync/CxMutex.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoCriticalSection::CxAutoCriticalSection(
    CxCriticalSection &csCS,
    const bool         cbIsUseTry /* = false*/
) :
    _m_csCS     (csCS),
    _m_bIsLocked(false)
{
    bool bRes = false;

    bRes = csCS.bCreate();
    /*DEBUG*/xASSERT_DO(true == bRes, return);

    if (false == cbIsUseTry) {
        bRes = _m_csCS.bLock();
        /*DEBUG*/xASSERT_DO(true == bRes, return);
    } else {
        bRes = _m_csCS.bTryLock();
        /*DEBUG*/// n/a
    }

    _m_bIsLocked = bRes;
}
//---------------------------------------------------------------------------
CxAutoCriticalSection::~CxAutoCriticalSection() {
    if (false != _m_bIsLocked) {
        bool bRes = _m_csCS.bUnlock();
        /*DEBUG*/xASSERT_DO(true == bRes, return);
    }

    _m_bIsLocked = false;
}
//---------------------------------------------------------------------------
bool
CxAutoCriticalSection::bIsLocked() const {
    return _m_bIsLocked;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
