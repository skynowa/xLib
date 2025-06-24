/**
 * \file  Thread.inl
 * \brief thread
 */


namespace xl::sync
{


/**************************************************************************************************
*    public: actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Thread::_create_impl(
    cuint_t a_stackSizeBytes
)
{
    id_t id {};

    auto hRv = reinterpret_cast<HANDLE>( ::_beginthreadex(nullptr, a_stackSizeBytes, _func, this,
        0U, (uint_t *)&id) );
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);
    xTEST_LESS(0UL, id);

    _handle = hRv;
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    _id = id;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_kill_impl(
    culong_t a_timeoutMsec
)
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);
    xTEST_NA(a_timeoutMsec);

    _exitStatus = 0U;

#if xCOMPILER_MS
    #pragma warning (push)
    #pragma warning (disable: 6258)
#endif

    BOOL blRv = ::TerminateThread(_handle, _exitStatus);

#if xCOMPILER_MS
    #pragma warning (pop)
#endif

    xTEST_DIFF(blRv, FALSE);

    for ( ; ; ) {
        ulong_t ulRv = exitStatus();
        xCHECK_DO(ulRv != STILL_ACTIVE, break);

        currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_wait_impl(
    culong_t a_timeoutMsec
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);
    xTEST_NA(a_timeoutMsec);

    // flags
    xTEST_DIFF(_id, currentId());
    xCHECK_DO(_id == currentId(), return);

    DWORD dwRv = ::WaitForSingleObject(_handle, a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: flags
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isCreated_impl() const
{
    bool_t bRv = _state.isCreated && (_handle != xNATIVE_HANDLE_NULL);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isRunning_impl() const
{
    bool_t bRv {};

    DWORD dwRv {};
    (void_t)::GetExitCodeThread(_handle, &dwRv);

    bool_t bCond1 = (_handle != xNATIVE_HANDLE_NULL);
    bool_t bCond2 = (_id > 0UL);
    bool_t bCond3 = _state.isRunning;
    bool_t bCond4 = (::WaitForSingleObject(_handle, 0UL) != WAIT_OBJECT_0);
    bool_t bCond5 = (dwRv == STILL_ACTIVE);

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isPaused_impl() const
{
    bool_t bRv = !_eventPause.isSignaled() && (_handle != xNATIVE_HANDLE_NULL);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isExited_impl() const
{
    bool_t bRv = _eventExit.isSignaled() && (_handle != xNATIVE_HANDLE_NULL);

    return bRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: messages
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Thread::postMessage(
    HWND   a_wnd,
    uint_t a_msg,
    uint_t a_param1,
    long_t a_param2
) const
{
    xTEST((_handle != xNATIVE_HANDLE_NULL));
    xTEST_DIFF(a_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_DIFF(::IsWindow(a_wnd), FALSE);

    BOOL blRv = ::PostMessage(a_wnd, a_msg, static_cast<WPARAM>( a_param1 ),
        static_cast<LPARAM>( a_param2 ));
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::sendMessage(
    HWND   a_wnd,
    uint_t a_msg,
    uint_t a_param1,
    long_t a_param2
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);
    xTEST_DIFF(a_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_DIFF(::IsWindow(a_wnd), FALSE);

    (void_t)::SendMessage(a_wnd, a_msg, static_cast<WPARAM>( a_param1 ),
        static_cast<LPARAM>( a_param2 ));
    xTEST_EQ(NativeError::get(), 0UL);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::postThreadMessage(
    uint_t a_msg,
    uint_t a_param1,
    long_t a_param2
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    BOOL blRv = ::PostThreadMessage(id(), a_msg, static_cast<WPARAM>( a_param1 ),
        static_cast<LPARAM>( a_param2 ));
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::tryPostThreadMessage(
    uint_t  a_msg,
    uint_t  a_param1,
    long_t  a_param2,
    ulong_t a_attempsNum,
    ulong_t a_attempTimeoutMsec
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    for (ulong_t i = 0UL; i < a_attempsNum; ++ i) {
        BOOL blRv = ::PostThreadMessage(id(), a_msg, static_cast<WPARAM>( a_param1 ),
            static_cast<LPARAM>( a_param2 ));

        xCHECK_RET(blRv != FALSE, true);
        xCHECK_DO (blRv == FALSE, currentSleep(a_attempTimeoutMsec));
    }

    return false;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::messageWaitQueue(
    uint_t  a_msg,
    uint_t *a_param1,
    long_t *a_param2
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);
    xTEST_LESS(0U, a_msg);

    std::vector<uint_t> msgs;
    msgs.push_back(a_msg);

    messageWaitQueue(msgs, nullptr, a_param1, a_param2);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::messageWaitQueue(
    const std::vector<uint_t> &a_msgs,
    uint_t                    *a_msg,
    uint_t                    *a_param1,
    long_t                    *a_param2
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);
    xTEST(!a_msgs.empty());

    BOOL blRv {FALSE};
    MSG  msg  {};

    while ((blRv = ::GetMessage(&msg, nullptr, 0, 0)) == TRUE) {
        xTEST_DIFF(blRv, - 1);

        for (size_t i = 0; i < a_msgs.size(); ++ i) {
            xCHECK_DO(a_msgs.at(i) != msg.message, continue);

            Utils::ptrAssignT(a_msg,    msg.message                    );
            Utils::ptrAssignT(a_param1, static_cast<uint_t>(msg.wParam));
            Utils::ptrAssignT(a_param2, static_cast<long_t>(msg.lParam));

            break;
        }
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: priority
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Thread::_setPriority_impl(
    cPriority a_priority
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    BOOL blRv = ::SetThreadPriority(_handle, static_cast<int_t>(a_priority));
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
Thread::Priority
Thread::_priority_impl() const
{
	const auto tpRv = static_cast<Priority>( ::GetThreadPriority(_handle) );
    xTEST_DIFF(static_cast<int_t>(tpRv), static_cast<int_t>(Priority::tpError));

    return tpRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isPriorityBoost_impl() const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    BOOL isDisablePriorityBoost = TRUE;

    BOOL blRv = ::GetThreadPriorityBoost(_handle, &isDisablePriorityBoost);
    xTEST_DIFF(blRv, FALSE);

    return !isDisablePriorityBoost;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_setPriorityBoost_impl(
    cbool_t a_isEnabled
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    BOOL blRv = ::SetThreadPriorityBoost(_handle, ! a_isEnabled);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: CPU
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Thread::_setCpuAffinity_impl(
    cint_t a_procNum
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

#if xARCH_BITS_32
    DWORD_PTR mask = 1UL  << a_procNum;
#else
    DWORD_PTR mask = 1i64 << a_procNum;
#endif

    DWORD_PTR pdwRv = ::SetThreadAffinityMask(_handle, mask);
#if xARCH_BITS_32
    xTEST_DIFF(pdwRv, 0UL);
#else
   /**
    * \note
    *
    * error C2446: '!=': no conversion from 'nullptr' to 'DWORD_PTR'
    * message: A native nullptr can only be converted to bool or, using reinterpret_cast, to an integral type
    */
    xTEST(!static_cast<bool_t>(pdwRv));
#endif

    xTEST(pdwRv != ERROR_INVALID_PARAMETER);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_setCpuIdeal_impl(
    culong_t a_idealCpu    ///< value is zero-based
) const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    DWORD dwRv = ::SetThreadIdealProcessor(_handle, a_idealCpu);
    xTEST_DIFF(dwRv, (DWORD) - 1);
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::_cpuIdeal_impl() const
{
    ulong_t ulRv = ::SetThreadIdealProcessor(_handle, MAXIMUM_PROCESSORS);
    xTEST_DIFF(ulRv, (ulong_t) - 1);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Thread::handle_t
Thread::_handle_impl() const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    return _handle;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::_exitStatus_impl() const
{
    xTEST(_handle != xNATIVE_HANDLE_NULL);

    ulong_t ulRv {};

    BOOL blRv = ::GetExitCodeThread(_handle, &ulRv);
    xTEST_DIFF(blRv, FALSE);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
// TODO: Win10 - SetThreadDescription
void_t
Thread::_setDebugName_impl(
    std::ctstring_t &a_name
) const
{
#if xCOMPILER_MS
    const DWORD msVcException = 0x406D1388;

#pragma pack(push, 8)
    struct tagTHREADNAME_INFO
    {
        DWORD  dwType;      // must be 0x1000
        LPCSTR pszName;     // pointer to name (in user addr space)
        DWORD  dwThreadID;  // thread ID (-1 = caller thread)
        DWORD  dwFlags;     // reserved for future use, must be zero
    };
#pragma pack(pop)

    tagTHREADNAME_INFO info {};
    info.dwType = 0x1000;
#if xUNICODE
    // TODO: [skynowa] Thread::setDebugName() - convert from Unicode to Ansi
    //// info.pszName    = xT2A(a_name).c_str();
    info.pszName    = "[Unknown]";
#else
    info.pszName    = a_name.c_str();
#endif
    info.dwThreadID = id();
    info.dwFlags    = 0;

    __try {
        (void_t)::RaiseException(msVcException, 0, sizeof(info) / sizeof(ULONG_PTR),
            (ULONG_PTR *)&info);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        //n/a
    }
#elif xCOMPILER_MINGW
    // TODO: [skynowa] Thread::setDebugName() - xCOMPILER_MINGW
#else
    // TODO: [skynowa] Thread::setDebugName() - other
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
Thread::handle_t
Thread::_open_impl(
    culong_t  a_access,
    cbool_t   a_isInheritHandle,
	cid_t    &a_id
)
{
    handle_t hRv = ::OpenThread(a_access, a_isInheritHandle, a_id);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    return hRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
int_t
Thread::_priorityMin_impl()
{
    int_t iRv = THREAD_PRIORITY_IDLE;

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
Thread::_priorityMax_impl()
{
    int_t iRv = THREAD_PRIORITY_TIME_CRITICAL;

    return iRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
