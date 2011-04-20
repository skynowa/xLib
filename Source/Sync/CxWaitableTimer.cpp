/****************************************************************************
* Class name:  CxWaitableTimer
* Description: waitable timer
* File name:   CxWaitableTimer.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.05.2009 17:07:46
*
*****************************************************************************/


#include <xLib/Sync/CxWaitableTimer.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxWaitableTimer ()
CxWaitableTimer::CxWaitableTimer() :
    _m_hWaitableTimer()
{

}
//---------------------------------------------------------------------------
//DONE: ~CxWaitableTimer ()
CxWaitableTimer::~CxWaitableTimer() {
    /*DEBUG*/xASSERT(FALSE != _m_hWaitableTimer.bIsValid());

}
//---------------------------------------------------------------------------
//DONE: hGetHandle ()
HANDLE
CxWaitableTimer::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), NULL);

    return _m_hWaitableTimer.m_hHandle;
}
//---------------------------------------------------------------------------
//DONE: bCreate ()
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
//DONE: bOpen ()
BOOL
CxWaitableTimer::bOpen(LPCTSTR pcszName, ULONG ulDesiredAccess, BOOL bInheritHandle) {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

    HANDLE hRes = NULL;

    hRes = ::OpenWaitableTimerA(ulDesiredAccess, bInheritHandle, pcszName);
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hWaitableTimer.m_hHandle = hRes;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bCancel ()
BOOL
CxWaitableTimer::bCancel() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::CancelWaitableTimer(_m_hWaitableTimer.m_hHandle);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSet ()
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
//DONE: bWait ()
BOOL
CxWaitableTimer::bWait(ULONG ulTimeout) const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

    ULONG ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hWaitableTimer.m_hHandle, ulTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
