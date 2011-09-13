/**
 * \file  CxAutoCriticalSection.h
 * \brief auto critical section (using between threads)
 */


#include <xLib/Sync/CxAutoCriticalSection.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoCriticalSection::CxAutoCriticalSection(
    CxCriticalSection &csCS,
    const BOOL         cbIsUseTry /* = FALSE*/
) :
    _m_csCS     (csCS),
    _m_bIsLocked(FALSE)
{
    BOOL bRes = FALSE;

    if (FALSE == cbIsUseTry) {
        bRes = _m_csCS.bLock();
        /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
    } else {
        bRes = _m_csCS.bTryLock();
        /*DEBUG*/// n/a
    }

    _m_bIsLocked = bRes;
}
//---------------------------------------------------------------------------
CxAutoCriticalSection::~CxAutoCriticalSection() {
    if (FALSE != _m_bIsLocked) {
        BOOL bRes = _m_csCS.bUnlock();
        /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
    }

    _m_bIsLocked = FALSE;
}
//---------------------------------------------------------------------------
BOOL
CxAutoCriticalSection::bIsLocked() const {
    return _m_bIsLocked;
}
//---------------------------------------------------------------------------
