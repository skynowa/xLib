/**
 * \file  CxWaitableTimer.cpp
 * \brief waitable timer
 */


#include <xLib/Sync/CxWaitableTimer.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO HANDLE
CxWaitableTimer::handle() const
{
    xTEST_EQ(true, _handle.isValid());

    return _handle.get();
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxWaitableTimer::create(
    cbool_t                     &a_bManualReset,
    std::ctstring_t             &a_name,
    const LPSECURITY_ATTRIBUTES  a_attrs
)
{
    xTEST_EQ(false, _handle.isValid());

    HANDLE hRv = ::CreateWaitableTimer(a_attrs, a_bManualReset, a_name.c_str());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _handle.set(hRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxWaitableTimer::open(
    std::ctstring_t &a_name,
    culong_t        &a_access,
    cbool_t         &a_isInheritHandle
)
{
    xTEST_EQ(true, _handle.isValid());

// MinGW fix
#if !defined(OpenWaitableTimer)
    #if xUNICODE
        #define OpenWaitableTimer OpenWaitableTimerW
    #else
        #define OpenWaitableTimer OpenWaitableTimerA
    #endif
#endif

    HANDLE hRv = ::OpenWaitableTimer(a_access, a_isInheritHandle, a_name.c_str());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    _handle.set(hRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxWaitableTimer::cancel() const
{
    xTEST_EQ(true, _handle.isValid());

    BOOL blRes = ::CancelWaitableTimer(_handle.get());
    xTEST_DIFF(FALSE, blRes);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxWaitableTimer::set(
    clonglong_t      &a_dueTimeMsec,
    clong_t          &a_period,
    PTIMERAPCROUTINE  a_routine,
    LPVOID            a_routineArgs,
    cbool_t          &a_isResume
) const
{
    xTEST_EQ(true, _handle.isValid());

    /*
    #define _SECOND 10000000   // ���� ������� ��� ���������� �������

    //����� �������� ��� ������� = 2 �������
    qwTimeInterval = -2 * _SECOND;
    */

    LARGE_INTEGER dueTimeMsec = {{0}};
    dueTimeMsec.QuadPart = a_dueTimeMsec;

    BOOL blRes = ::SetWaitableTimer(_handle.get(), &dueTimeMsec, a_period, a_routine,
        a_routineArgs, a_isResume);
    xTEST_DIFF(FALSE, blRes);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxWaitableTimer::wait(
    culong_t &a_timeoutMsec
) const
{
    xTEST_EQ(true, _handle.isValid());

    DWORD ulRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
