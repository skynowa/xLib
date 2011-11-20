/**
 * \file  CxAutoCriticalSection.h
 * \brief auto critical section (using between threads)
 */


#include <xLib/Sync/CxAutoCriticalSection.h>


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

    if (false == cbIsUseTry) {
        bRes = _m_csCS.bLock();
        /*DEBUG*/xASSERT_DO(false != bRes, return);
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
        /*DEBUG*/xASSERT_DO(false != bRes, return);
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
