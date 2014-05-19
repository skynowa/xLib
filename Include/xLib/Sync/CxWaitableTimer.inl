/**
 * \file  CxWaitableTimer.inl
 * \brief waitable timer
 */


#if xENV_WIN

xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline HANDLE
CxWaitableTimer::handle() const
{
    xTEST_EQ(_handle.isValid(), true);

    return _handle.get();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxWaitableTimer::create(
    cbool_t                     &a_bManualReset,
    std::ctstring_t             &a_name,
    const LPSECURITY_ATTRIBUTES  a_attrs
)
{
    xTEST_EQ(_handle.isValid(), false);

    HANDLE hRv = ::CreateWaitableTimer(a_attrs, a_bManualReset, a_name.c_str());
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxWaitableTimer::open(
    std::ctstring_t &a_name,
    culong_t        &a_access,
    cbool_t         &a_isInheritHandle
)
{
    xTEST_EQ(_handle.isValid(), true);

// MinGW fix
#if !defined(OpenWaitableTimer)
    #if xUNICODE
        #define OpenWaitableTimer OpenWaitableTimerW
    #else
        #define OpenWaitableTimer OpenWaitableTimerA
    #endif
#endif

    HANDLE hRv = ::OpenWaitableTimer(a_access, a_isInheritHandle, a_name.c_str());
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxWaitableTimer::cancel() const
{
    xTEST_EQ(_handle.isValid(), true);

    BOOL blRv = ::CancelWaitableTimer(_handle.get());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxWaitableTimer::set(
    clonglong_t      &a_dueTimeMsec,
    clong_t          &a_period,
    PTIMERAPCROUTINE  a_routine,
    LPVOID            a_routineArgs,
    cbool_t          &a_isResume
) const
{
    xTEST_EQ(_handle.isValid(), true);

    LARGE_INTEGER dueTimeMsec = {{0}};
    dueTimeMsec.QuadPart = a_dueTimeMsec;

    BOOL blRv = ::SetWaitableTimer(_handle.get(), &dueTimeMsec, a_period, a_routine,
        a_routineArgs, a_isResume);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxWaitableTimer::wait(
    culong_t &a_timeoutMsec
) const
{
    xTEST_EQ(_handle.isValid(), true);

    DWORD dwRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)

#endif
