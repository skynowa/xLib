/****************************************************************************
* Class name:  CxSleeper
* Description: замене ::Sleep()
* File name:   CxSleeper.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.07.2009 12:54:38
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Sync/CxSleeper.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxSleeper (конструктор)
CxSleeper::CxSleeper() :
	_m_objEvent()
{
	BOOL bRes = FALSE;

	bRes = _m_objEvent.bCreate(NULL, FALSE, FALSE, NULL);
	/*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//TODO: + ~CxSleeper (деструктор)
CxSleeper::~CxSleeper() {

}
//---------------------------------------------------------------------------
//TODO: + bSleep (засыпание)
BOOL 
CxSleeper::bSleep(ULONG ulTimeout) const {
	/*DEBUG*/// n/a
	
	BOOL  bRes  = FALSE;
	ULONG ulRes = 0;

	ulRes = ::WaitForSingleObject(_m_objEvent.hGetHandle(), ulTimeout); 
	/*DEBUG*/xASSERT_RET(WAIT_FAILED != ulRes || WAIT_OBJECT_0 == ulRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWakeUp (сброс засыпания)
BOOL 
CxSleeper::bWakeUp() const {
	/*DEBUG*/// n/a

	BOOL bRes = FALSE;

	bRes = _m_objEvent.bSet(); 
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bIsSleeping (спим ли)
BOOL 
CxSleeper::bIsSleeping() const {
	/*DEBUG*/// n/a
	
	return _m_objEvent.bIsSignaled();	
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------