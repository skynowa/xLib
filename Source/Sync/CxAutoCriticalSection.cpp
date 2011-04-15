/****************************************************************************
* Class name:  CxAutoCriticalSection
* Description: работа с критичечкими секциями в блоке
* File name:   CxAutoCriticalSection.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 21:16:33
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Sync/CxAutoCriticalSection.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxAutoCriticalSection (конструктор)
CxAutoCriticalSection::CxAutoCriticalSection(CxCriticalSection &csCS) : 
	_m_csCS(csCS) 
{
	_m_csCS.vEnter();
}
//---------------------------------------------------------------------------
//TODO: + CxAutoCriticalSection (конструктор)
////CxAutoCriticalSection::CxAutoCriticalSection(CxCriticalSection &csCS, BOOL bTry, ULONG ulTimeout /*= 1000*/) : 
////	_m_csCS(csCS) 
////{
////	bTry = FALSE;
////
////	if (TRUE == bTry) {       
////		/*DEBUG*/xASSERT(FALSE);
////
////		BOOL bRes = FALSE;
////
////		while (FALSE == _m_csCS.bTryEnter()) {
////			::OutputDebugString(_T("bTryEnter is FALSE\n"));
////			
////			//::Sleep(ulTimeout); 
////			BOOL bRes = _m_slSleeper.bSleep(ulTimeout);
////			/*DEBUG*/xASSERT_DO(FALSE != bRes, break)
////
////		}
////	} else {
////		_m_csCS.vEnter();
////	}
////}
//---------------------------------------------------------------------------
//TODO: + ~CxAutoCriticalSection (деструктор)
CxAutoCriticalSection::~CxAutoCriticalSection() {
	_m_csCS.vLeave();
}
//---------------------------------------------------------------------------