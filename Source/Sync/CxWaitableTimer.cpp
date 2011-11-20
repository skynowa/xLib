/**
 * \file  CxWaitableTimer.cpp
 * \brief waitable timer
 */


#include <xLib/Sync/CxWaitableTimer.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

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
    /*DEBUG*/xASSERT(false != _m_hWaitableTimer.bIsValid());

}
//---------------------------------------------------------------------------
//DONE: hGetHandle ()
HANDLE
CxWaitableTimer::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), NULL);

    return _m_hWaitableTimer.hGet();
}
//---------------------------------------------------------------------------
//DONE: bCreate ()
bool
CxWaitableTimer::bCreate(
    const bool                   bManualReset,
    const std::tstring          &csName,
    const LPSECURITY_ATTRIBUTES  pcsaTimerAttributes
)
{
    /*DEBUG*/xASSERT_RET(false == _m_hWaitableTimer.bIsValid(), false);

    HANDLE hRes = NULL;

    hRes = ::CreateWaitableTimer(pcsaTimerAttributes, bManualReset, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hWaitableTimer.bSet(hRes);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
bool
CxWaitableTimer::bOpen(
    const std::tstring &csName,
    const ULONG         culDesiredAccess,
    const bool          cbInheritHandle
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

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
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hWaitableTimer.bSet(hRes);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bCancel ()
bool
CxWaitableTimer::bCancel() const {
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

    BOOL bRes = ::CancelWaitableTimer(_m_hWaitableTimer.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bSet ()
bool
CxWaitableTimer::bSet(
    const LONGLONG   cllDueTime,
    const LONG       cliPeriod,
    PTIMERAPCROUTINE pfnCompletionRoutine,
    LPVOID           pvArgToCompletionRoutine,
    const bool       cbResume
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

    /*
    #define _SECOND 10000000   // ���� ������� ��� ���������� �������

    //����� �������� ��� ������� = 2 �������
    qwTimeInterval = -2 * _SECOND;
    */

    LARGE_INTEGER liDueTime = {{0}};
    liDueTime.QuadPart = cllDueTime;

    BOOL bRes = ::SetWaitableTimer(_m_hWaitableTimer.hGet(), &liDueTime, cliPeriod, pfnCompletionRoutine, pvArgToCompletionRoutine, cbResume);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bWait ()
bool
CxWaitableTimer::bWait(
    const ULONG culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

    ULONG ulRes = WAIT_FAILED;

    ulRes = ::WaitForSingleObject(_m_hWaitableTimer.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
