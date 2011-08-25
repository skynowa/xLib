/**
 * \file  CxAutoCriticalSection.h
 * \brief auto critical section
 */


#include <xLib/Sync/CxAutoCriticalSection.h>


#if defined(xOS_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxAutoCriticalSection
CxAutoCriticalSection::CxAutoCriticalSection(
    CxCriticalSection &csCS
) :
    _m_csCS(csCS)
{
    _m_csCS.vEnter();
}
//---------------------------------------------------------------------------
//DONE: ~CxAutoCriticalSection
CxAutoCriticalSection::~CxAutoCriticalSection() {
    _m_csCS.vLeave();
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
