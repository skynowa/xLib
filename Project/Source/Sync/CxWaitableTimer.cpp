/**
 * \file  CxWaitableTimer.cpp
 * \brief waitable timer
 */


#include <xLib/Sync/CxWaitableTimer.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxWaitableTimer::CxWaitableTimer() :
    _m_hHandle()
{

}
//---------------------------------------------------------------------------
CxWaitableTimer::~CxWaitableTimer() {
    xTEST_DIFF(false, _m_hHandle.bIsValid());

}
//---------------------------------------------------------------------------
HANDLE
CxWaitableTimer::hHandle() const {
    xTEST_EQ(true, _m_hHandle.bIsValid());

    return _m_hHandle.hGet();
}
//---------------------------------------------------------------------------
void
CxWaitableTimer::vCreate(
    const bool                  &a_bManualReset,
    const std::tstring_t        &a_csName,
    const LPSECURITY_ATTRIBUTES  a_pcsaTimerAttributes
)
{
    xTEST_EQ(false, _m_hHandle.bIsValid());

    HANDLE hRv = ::CreateWaitableTimer(a_pcsaTimerAttributes, a_bManualReset, a_csName.c_str());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _m_hHandle.vSet(hRv);
}
//---------------------------------------------------------------------------
void
CxWaitableTimer::vOpen(
    const std::tstring_t &a_csName,
    const ulong_t        &a_culDesiredAccess,
    const bool           &a_cbInheritHandle
)
{
    xTEST_EQ(true, _m_hHandle.bIsValid());

//MinGW fix
#if !defined(OpenWaitableTimer)
    #if xUNICODE
        #define OpenWaitableTimer OpenWaitableTimerW
    #else
        #define OpenWaitableTimer OpenWaitableTimerA
    #endif
#endif

    HANDLE hRv = ::OpenWaitableTimer(a_culDesiredAccess, a_cbInheritHandle, a_csName.c_str());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _m_hHandle.vSet(hRv);
}
//---------------------------------------------------------------------------
void
CxWaitableTimer::vCancel() const {
    xTEST_EQ(true, _m_hHandle.bIsValid());

    BOOL blRes = ::CancelWaitableTimer(_m_hHandle.hGet());
    xTEST_DIFF(FALSE, blRes);
}
//---------------------------------------------------------------------------
void
CxWaitableTimer::vSet(
    const longlong_t &a_cllDueTime,
    const long_t     &a_cliPeriod,
    PTIMERAPCROUTINE  a_pfnCompletionRoutine,
    LPVOID            a_pvArgToCompletionRoutine,
    const bool       &a_cbResume
) const
{
    xTEST_EQ(true, _m_hHandle.bIsValid());

    /*
    #define _SECOND 10000000   // ���� ������� ��� ���������� �������

    //����� �������� ��� ������� = 2 �������
    qwTimeInterval = -2 * _SECOND;
    */

    LARGE_INTEGER liDueTime = {{0}};
    liDueTime.QuadPart = a_cllDueTime;

    BOOL blRes = ::SetWaitableTimer(_m_hHandle.hGet(), &liDueTime, a_cliPeriod, a_pfnCompletionRoutine, a_pvArgToCompletionRoutine, a_cbResume);
    xTEST_DIFF(FALSE, blRes);
}
//---------------------------------------------------------------------------
void
CxWaitableTimer::vWait(
    const ulong_t &a_culTimeout
) const
{
    xTEST_EQ(true, _m_hHandle.bIsValid());

    DWORD ulRv = ::WaitForSingleObject(_m_hHandle.hGet(), a_culTimeout);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
