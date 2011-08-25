/**
 * \file  CxWaitableTimer.cpp
 * \brief waitable timer
 */


#include <xLib/Sync/CxWaitableTimer.h>


#if defined(xOS_WIN)
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

    return _m_hWaitableTimer.hGet();
}
//---------------------------------------------------------------------------
//DONE: bCreate ()
BOOL
CxWaitableTimer::bCreate(
    const BOOL                   bManualReset,
    const std::tstring               &csName,
    const LPSECURITY_ATTRIBUTES  pcsaTimerAttributes
)
{
    /*DEBUG*/xASSERT_RET(FALSE == _m_hWaitableTimer.bIsValid(), FALSE);

    HANDLE hRes = NULL;

    hRes = ::CreateWaitableTimer(pcsaTimerAttributes, bManualReset, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hWaitableTimer.bSet(hRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
BOOL
CxWaitableTimer::bOpen(
    const std::tstring &csName,
    const ULONG    culDesiredAccess,
    const BOOL     cbInheritHandle
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

    HANDLE hRes = NULL;

//MinGW fix
#if !defined(OpenWaitableTimer)
    #if defined(xINICODE)
        #define OpenWaitableTimer OpenWaitableTimerW
    #else
        #define OpenWaitableTimer OpenWaitableTimerA
    #endif
#endif

    hRes = ::OpenWaitableTimer(culDesiredAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    _m_hWaitableTimer.bSet(hRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bCancel ()
BOOL
CxWaitableTimer::bCancel() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::CancelWaitableTimer(_m_hWaitableTimer.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSet ()
BOOL
CxWaitableTimer::bSet(
    const LONGLONG   cllDueTime,
    const LONG       cliPeriod,
    PTIMERAPCROUTINE pfnCompletionRoutine,
    LPVOID           pvArgToCompletionRoutine,
    const BOOL       cbResume
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

    /*
    #define _SECOND 10000000   // ���� ������� ��� ���������� �������

    //����� �������� ��� ������� = 2 �������
    qwTimeInterval = -2 * _SECOND;
    */

    BOOL bRes = FALSE;  //#define _SECOND 10000000   // ���� ������� ��� ���������� �������

    LARGE_INTEGER liDueTime = {{0}};
    liDueTime.QuadPart = cllDueTime;

    bRes = ::SetWaitableTimer(_m_hWaitableTimer.hGet(), &liDueTime, cliPeriod, pfnCompletionRoutine, pvArgToCompletionRoutine, cbResume);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWait ()
BOOL
CxWaitableTimer::bWait(
    const ULONG culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hWaitableTimer.bIsValid(), FALSE);

    ULONG ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hWaitableTimer.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
