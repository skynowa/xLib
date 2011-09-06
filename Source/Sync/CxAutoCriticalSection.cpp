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
    CxCriticalSection &csCS
) :
    _m_csCS(csCS)
{
    BOOL bRes = _m_csCS.bEnter();
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
CxAutoCriticalSection::~CxAutoCriticalSection() {
    BOOL bRes = _m_csCS.bLeave();
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
