/****************************************************************************
* Class name:  CxEvent
* Description: ивенты
* File name:   CxEvent.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 17:53:15
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Sync/CxEvent.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxEvent (конструктор)
CxEvent::CxEvent() :
	_m_hEvent()
{

}
//---------------------------------------------------------------------------
//TODO: + ~CxEvent (деструктор)
CxEvent::~CxEvent() {

}
//---------------------------------------------------------------------------
//TODO: + hGetHandle (A handle to the event object)
HANDLE 
CxEvent::hGetHandle() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), NULL);
    
    return _m_hEvent.m_hHandle;
}
//---------------------------------------------------------------------------
//TODO: + bCreate (Creates or opens a named or unnamed event object)
BOOL 
CxEvent::bCreate(LPSECURITY_ATTRIBUTES lpsaAttributes, BOOL bManualReset, BOOL bInitialState, LPCTSTR pcszName) {
	/*DEBUG*/xASSERT_RET(FALSE == _m_hEvent.bIsValid(), FALSE);
	/*DEBUG*/

	HANDLE hRes = NULL;

	hRes = ::CreateEvent(lpsaAttributes, bManualReset, bInitialState, pcszName);
	/*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

	////--_m_hEvent = hRes;
	_m_hEvent.m_hHandle = hRes; 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bOpen (Opens an existing named event object)
BOOL 
CxEvent::bOpen(ULONG ulAccess, BOOL bInheritHandle, LPCTSTR pcszName) {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);		
	/*DEBUG*/
	
	HANDLE hRes = NULL;

	/*EVENT_MODIFY_STATE, EVENT_ALL_ACCESS, EVENT_MODIFY_STATE*/
	hRes = ::OpenEvent(ulAccess, bInheritHandle, pcszName);
	/*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

	////--_m_hEvent = hRes;
	_m_hEvent.m_hHandle = hRes; 

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bPulse (Sets the specified event object to the signaled state and then resets it to the nonsignaled state after releasing the appropriate number of waiting threads)
BOOL 
CxEvent::bPulse() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);		
	/*DEBUG*/
	
	BOOL bRes = FALSE;

	bRes = ::PulseEvent(_m_hEvent.m_hHandle);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bReset (Sets the specified event object to the nonsignaled state)
BOOL 
CxEvent::bReset() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);		
	/*DEBUG*/

	BOOL bRes = FALSE;

	bRes = ::ResetEvent(_m_hEvent.m_hHandle);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSet (Sets the specified event object to the signaled state) 
BOOL 
CxEvent::bSet() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);		
	/*DEBUG*/

	BOOL bRes = FALSE;

	bRes = ::SetEvent(_m_hEvent.m_hHandle);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWait (Waits until the specified event is in the signaled state or the time-out interval elapses)
BOOL 
CxEvent::bWait(ULONG ulTimeout) const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);		
	/*DEBUG*/// n/a

	//WAIT_OBJECT_0   Объект перешёл в состояние свободного 
	//WAIT_TIMEOUT    Объект  не  перешёл  в  состояние  свободного  за указанный период времени 
	//WAIT_ABANDONED  Объект мьютекс стал свободен из-за отказа от него 
	//WAIT_FAILED     Произошла ошибка

	ULONG ulRes = ::WaitForSingleObject(_m_hEvent.m_hHandle, ulTimeout); 
	/*DEBUG*/// n/a

	return (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
//TODO: + bIsSignaled (проверка состояния)
BOOL 
CxEvent::bIsSignaled() const {
	/*DEBUG*/// n/a

	ULONG ulRes = ::WaitForSingleObject(_m_hEvent.m_hHandle, 0);  
	/*DEBUG*/// n/a

	return (FALSE != _m_hEvent.bIsValid()) && (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
