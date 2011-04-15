/****************************************************************************
* Class name:  CxWaitableTimer
* Description: работа с таймером ожидания
* File name:   CxWaitableTimer.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     27.05.2009 17:07:46
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Sync/CxWaitableTimer.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxWaitableTimer ()
CxWaitableTimer::CxWaitableTimer() :
	_m_hWaitableTimer()
{

}
//---------------------------------------------------------------------------
//TODO: + ~CxWaitableTimer ()
CxWaitableTimer::~CxWaitableTimer() {
	/*DEBUG*/xASSERT(FALSE != _m_hWaitableTimer.bIsValid());

}
//---------------------------------------------------------------------------
//TODO: + hGetHandle ()
HANDLE
CxWaitableTimer::hGetHandle() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), NULL);

	return _m_hWaitableTimer.m_hHandle;
}
//---------------------------------------------------------------------------
//TODO: + bCreate ()
BOOL
CxWaitableTimer::bCreate(BOOL bManualReset, LPCTSTR pcszName, LPSECURITY_ATTRIBUTES lpTimerAttributes) {
	/*DEBUG*/xASSERT_RET(FALSE == _m_hWaitableTimer.bIsValid(), FALSE);

	HANDLE hRes = NULL;

	hRes = ::CreateWaitableTimer(lpTimerAttributes, bManualReset, pcszName);
	/*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

	_m_hWaitableTimer.m_hHandle = hRes;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bOpen ()
BOOL
CxWaitableTimer::bOpen(LPCTSTR pcszName, ULONG ulDesiredAccess, BOOL bInheritHandle) {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

	HANDLE hRes = NULL;

	hRes = ::OpenWaitableTimer(ulDesiredAccess, bInheritHandle, pcszName);
	/*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

	_m_hWaitableTimer.m_hHandle = hRes;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bCancel ()
BOOL
CxWaitableTimer::bCancel() const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

	BOOL bRes = FALSE;

	bRes = ::CancelWaitableTimer(_m_hWaitableTimer.m_hHandle);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSet ()
BOOL
CxWaitableTimer::bSet(LONGLONG i64DueTime, LONG liPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID pvArgToCompletionRoutine, BOOL bResume) const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

	/*
	#define _SECOND 10000000   // одна секунда для ожидающего таймера

	//время задержки для таймера = 2 секунды
	qwTimeInterval = -2 * _SECOND;
	*/
	BOOL bRes = FALSE;  //#define _SECOND 10000000   // одна секунда для ожидающего таймера

	LARGE_INTEGER liDueTime = {{0}};
	liDueTime.QuadPart = i64DueTime;

	bRes = ::SetWaitableTimer(_m_hWaitableTimer.m_hHandle, &liDueTime, liPeriod, pfnCompletionRoutine, pvArgToCompletionRoutine, bResume);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bWait ()
BOOL
CxWaitableTimer::bWait(ULONG ulTimeout) const {
	/*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

	ULONG ulRes = WAIT_FAILED;

	ulRes = ::WaitForSingleObject(_m_hWaitableTimer.m_hHandle, ulTimeout);
	/*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
