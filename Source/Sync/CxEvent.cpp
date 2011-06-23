/****************************************************************************
* Class name:  CxEvent
* Description: event
* File name:   CxEvent.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 17:53:15
*
*****************************************************************************/


#include <xLib/Sync/CxEvent.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxEvent (�����������)
CxEvent::CxEvent() :
    _m_hEvent()
{

}
//---------------------------------------------------------------------------
//DONE: ~CxEvent (����������)
CxEvent::~CxEvent() {

}
//---------------------------------------------------------------------------
//DONE: hGetHandle (A handle to the event object)
HANDLE
CxEvent::hGetHandle() const {
    /*DEBUG*/// n/a

    return _m_hEvent.hGet();
}
//---------------------------------------------------------------------------
//DONE: bCreate (Creates or opens a named or unnamed event object)
BOOL
CxEvent::bCreate(
    const LPSECURITY_ATTRIBUTES  pcsaAttributes,
    const BOOL                   cbManualReset,
    const BOOL                   cbInitialState,
    const tString               &csName
) {
    /*DEBUG*/xASSERT_RET(FALSE == _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    HANDLE hRes = NULL;

    hRes = ::CreateEvent(pcsaAttributes, cbManualReset, cbInitialState, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    ////--_m_hEvent = hRes;
    _m_hEvent.bSet(hRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen (Opens an existing named event object)
BOOL
CxEvent::bOpen(
    const ULONG    culAccess,
    const BOOL     cbInheritHandle,
    const tString &csName
) {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    HANDLE hRes = NULL;

    /*EVENT_MODIFY_STATE, EVENT_ALL_ACCESS, EVENT_MODIFY_STATE*/
    hRes = ::OpenEvent(culAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    ////--_m_hEvent = hRes;
    _m_hEvent.bSet(hRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bPulse (Sets the specified event object to the signaled state and then resets it to the nonsignaled state after releasing the appropriate number of waiting threads)
BOOL
CxEvent::bPulse() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = ::PulseEvent(_m_hEvent.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bReset (Sets the specified event object to the nonsignaled state)
BOOL
CxEvent::bReset() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = ::ResetEvent(_m_hEvent.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSet (Sets the specified event object to the signaled state)
BOOL
CxEvent::bSet() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/

    BOOL bRes = FALSE;

    bRes = ::SetEvent(_m_hEvent.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWait (Waits until the specified event is in the signaled state or the time-out interval elapses)
BOOL
CxEvent::bWait(
    const ULONG culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hEvent.bIsValid(), FALSE);
    /*DEBUG*/// n/a

    ULONG ulRes = ::WaitForSingleObject(_m_hEvent.hGet(), culTimeout);
    /*DEBUG*/// n/a

    return (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
//DONE: bIsSignaled (�������� ���������)
BOOL
CxEvent::bIsSignaled() const {
    /*DEBUG*/// n/a

    ULONG ulRes = ::WaitForSingleObject(_m_hEvent.hGet(), 0);
    /*DEBUG*/// n/a

    return (FALSE != _m_hEvent.bIsValid()) && (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
