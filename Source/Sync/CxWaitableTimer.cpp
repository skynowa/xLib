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
CxWaitableTimer::CxWaitableTimer() :
    _m_hWaitableTimer()
{

}
//---------------------------------------------------------------------------
CxWaitableTimer::~CxWaitableTimer() {
    /*DEBUG*/xASSERT(false != _m_hWaitableTimer.bIsValid());

}
//---------------------------------------------------------------------------
HANDLE
CxWaitableTimer::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), NULL);

    return _m_hWaitableTimer.hGet();
}
//---------------------------------------------------------------------------
bool
CxWaitableTimer::bCreate(
    const bool                   bManualReset,
    const std::tstring_t        &csName,
    const LPSECURITY_ATTRIBUTES  pcsaTimerAttributes
)
{
    /*DEBUG*/xASSERT_RET(false == _m_hWaitableTimer.bIsValid(), false);

    HANDLE hRes = ::CreateWaitableTimer(pcsaTimerAttributes, bManualReset, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hWaitableTimer.bSet(hRes);

    return true;
}
//---------------------------------------------------------------------------
bool
CxWaitableTimer::bOpen(
    const std::tstring_t &csName,
    const ulong_t         culDesiredAccess,
    const bool            cbInheritHandle
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

//MinGW fix
#if !defined(OpenWaitableTimer)
    #if xUNICODE
        #define OpenWaitableTimer OpenWaitableTimerW
    #else
        #define OpenWaitableTimer OpenWaitableTimerA
    #endif
#endif

    HANDLE hRes = ::OpenWaitableTimer(culDesiredAccess, cbInheritHandle, csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, false);

    _m_hWaitableTimer.bSet(hRes);

    return true;
}
//---------------------------------------------------------------------------
bool
CxWaitableTimer::bCancel() const {
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

    BOOL blRes = ::CancelWaitableTimer(_m_hWaitableTimer.hGet());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxWaitableTimer::bSet(
    const longlong_t cllDueTime,
    const long_t     cliPeriod,
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

    BOOL blRes = ::SetWaitableTimer(_m_hWaitableTimer.hGet(), &liDueTime, cliPeriod, pfnCompletionRoutine, pvArgToCompletionRoutine, cbResume);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxWaitableTimer::bWait(
    const ulong_t culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

    DWORD ulRes = ::WaitForSingleObject(_m_hWaitableTimer.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
