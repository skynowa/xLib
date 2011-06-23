/****************************************************************************
* Class name:  CxAutoCriticalSection
* Description: ������ � ������������ �������� � �����
* File name:   CxAutoCriticalSection.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 21:16:33
*
*****************************************************************************/


#include <xLib/Sync/CxAutoCriticalSection.h>


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
