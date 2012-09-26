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
    const bool                   a_bManualReset,
    const std::tstring_t        &a_csName,
    const LPSECURITY_ATTRIBUTES  a_pcsaTimerAttributes
)
{
    /*DEBUG*/xASSERT_RET(false == _m_hWaitableTimer.bIsValid(), false);

    HANDLE hRv = ::CreateWaitableTimer(a_pcsaTimerAttributes, a_bManualReset, a_csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);

    _m_hWaitableTimer.bSet(hRv);

    return true;
}
//---------------------------------------------------------------------------
bool
CxWaitableTimer::bOpen(
    const std::tstring_t &a_csName,
    const ulong_t         a_culDesiredAccess,
    const bool            a_cbInheritHandle
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

    HANDLE hRv = ::OpenWaitableTimer(a_culDesiredAccess, a_cbInheritHandle, a_csName.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);

    _m_hWaitableTimer.bSet(hRv);

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
    const longlong_t a_cllDueTime,
    const long_t     a_cliPeriod,
    PTIMERAPCROUTINE a_pfnCompletionRoutine,
    LPVOID           a_pvArgToCompletionRoutine,
    const bool       a_cbResume
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

    /*
    #define _SECOND 10000000   // ���� ������� ��� ���������� �������

    //����� �������� ��� ������� = 2 �������
    qwTimeInterval = -2 * _SECOND;
    */

    LARGE_INTEGER liDueTime = {{0}};
    liDueTime.QuadPart = a_cllDueTime;

    BOOL blRes = ::SetWaitableTimer(_m_hWaitableTimer.hGet(), &liDueTime, a_cliPeriod, a_pfnCompletionRoutine, a_pvArgToCompletionRoutine, a_cbResume);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxWaitableTimer::bWait(
    const ulong_t a_culTimeout
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hWaitableTimer.bIsValid(), false);

    DWORD ulRv = ::WaitForSingleObject(_m_hWaitableTimer.hGet(), a_culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRv, false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
