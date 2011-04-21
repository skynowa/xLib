/****************************************************************************
* Class name:  CxAutoCriticalSection
* Description: работа с критичечкими секциями в блоке
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
//DONE: CxAutoCriticalSection (конструктор)
CxAutoCriticalSection::CxAutoCriticalSection(CxCriticalSection &csCS) : 
    _m_csCS(csCS) 
{
    _m_csCS.vEnter();
}
//---------------------------------------------------------------------------
//DONE: CxAutoCriticalSection (конструктор)
////CxAutoCriticalSection::CxAutoCriticalSection(CxCriticalSection &csCS, BOOL bTry, ULONG ulTimeout /*= 1000*/) : 
////    _m_csCS(csCS) 
////{
////    bTry = FALSE;
////
////    if (TRUE == bTry) {       
////        /*DEBUG*/xASSERT(FALSE);
////
////        BOOL bRes = FALSE;
////
////        while (FALSE == _m_csCS.bTryEnter()) {
////            ::OutputDebugString(xT("bTryEnter is FALSE\n"));
////            
////            //::Sleep(ulTimeout); 
////            BOOL bRes = _m_slSleeper.bSleep(ulTimeout);
////            /*DEBUG*/xASSERT_DO(FALSE != bRes, break)
////
////        }
////    } else {
////        _m_csCS.vEnter();
////    }
////}
//---------------------------------------------------------------------------
//DONE: ~CxAutoCriticalSection (деструктор)
CxAutoCriticalSection::~CxAutoCriticalSection() {
    _m_csCS.vLeave();
}
//---------------------------------------------------------------------------