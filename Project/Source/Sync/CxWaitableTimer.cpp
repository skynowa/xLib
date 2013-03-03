/**
 * \file  CxWaitableTimer.cpp
 * \brief waitable timer
 */


#include <xLib/Sync/CxWaitableTimer.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxWaitableTimer::CxWaitableTimer() :
    _m_hHandle()
{

}
//------------------------------------------------------------------------------
CxWaitableTimer::~CxWaitableTimer() {
    xTEST_DIFF(false, _m_hHandle.isValid());

}
//------------------------------------------------------------------------------
HANDLE
CxWaitableTimer::handle() const {
    xTEST_EQ(true, _m_hHandle.isValid());

    return _m_hHandle.get();
}
//------------------------------------------------------------------------------
void_t
CxWaitableTimer::create(
    cbool_t                     &a_bManualReset,
    std::ctstring_t             &a_csName,
    const LPSECURITY_ATTRIBUTES  a_pcsaTimerAttributes
)
{
    xTEST_EQ(false, _m_hHandle.isValid());

    HANDLE hRv = ::CreateWaitableTimer(a_pcsaTimerAttributes, a_bManualReset, a_csName.c_str());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _m_hHandle.set(hRv);
}
//------------------------------------------------------------------------------
void_t
CxWaitableTimer::open(
    std::ctstring_t &a_csName,
    culong_t        &a_culDesiredAccess,
    cbool_t         &a_cbInheritHandle
)
{
    xTEST_EQ(true, _m_hHandle.isValid());

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

    _m_hHandle.set(hRv);
}
//------------------------------------------------------------------------------
void_t
CxWaitableTimer::cancel() const {
    xTEST_EQ(true, _m_hHandle.isValid());

    BOOL blRes = ::CancelWaitableTimer(_m_hHandle.get());
    xTEST_DIFF(FALSE, blRes);
}
//------------------------------------------------------------------------------
void_t
CxWaitableTimer::set(
    clonglong_t      &a_cllDueTime,
    clong_t          &a_cliPeriod,
    PTIMERAPCROUTINE  a_pfnCompletionRoutine,
    LPVOID            a_pvArgToCompletionRoutine,
    cbool_t          &a_cbResume
) const
{
    xTEST_EQ(true, _m_hHandle.isValid());

    /*
    #define _SECOND 10000000   // ���� ������� ��� ���������� �������

    //����� �������� ��� ������� = 2 �������
    qwTimeInterval = -2 * _SECOND;
    */

    LARGE_INTEGER liDueTime = {{0}};
    liDueTime.QuadPart = a_cllDueTime;

    BOOL blRes = ::SetWaitableTimer(_m_hHandle.get(), &liDueTime, a_cliPeriod, a_pfnCompletionRoutine, a_pvArgToCompletionRoutine, a_cbResume);
    xTEST_DIFF(FALSE, blRes);
}
//------------------------------------------------------------------------------
void_t
CxWaitableTimer::wait(
    culong_t &a_culTimeout
) const
{
    xTEST_EQ(true, _m_hHandle.isValid());

    DWORD ulRv = ::WaitForSingleObject(_m_hHandle.get(), a_culTimeout);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
