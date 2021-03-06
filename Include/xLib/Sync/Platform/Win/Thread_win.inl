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
    cuint_t &a_stackSizeBytes
)
{
    id_t id = 0UL;

    HANDLE hRv = reinterpret_cast<HANDLE>( ::_beginthreadex(nullptr, a_stackSizeBytes,
        _s_jobEntry, this, 0U, (uint_t *)&id) );
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
    xTEST_LESS(0UL, id);

    _handle.set(hRv);
    xTEST_EQ(_handle.isValid(), true);

    _id = id;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    xTEST_EQ(_handle.isValid(), true);
    xTEST_NA(a_timeoutMsec);

    _exitStatus = 0U;

    BOOL blRv = ::TerminateThread(_handle.get(), _exitStatus);
    xTEST_DIFF(blRv, FALSE);

    for ( ; ; ) {
        ulong_t ulRv = exitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_wait_impl(
    culong_t &a_timeoutMsec
) const
{
    xTEST_EQ(_handle.isValid(), true);
    xTEST_NA(a_timeoutMsec);

    // flags
    xTEST_DIFF(currentId(), _id);
    xCHECK_DO(currentId() == _id, return);

    DWORD dwRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(WAIT_OBJECT_0, dwRv);
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
    bool_t bRv = _state.isCreated && _handle.isValid();

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isRunning_impl() const
{
    bool_t bRv {};

    DWORD dwRv = 0UL;
    (void_t)::GetExitCodeThread(_handle.get(), &dwRv);

    bool_t bCond1 = _handle.isValid();
    bool_t bCond2 = _id > 0UL;
    bool_t bCond3 = _state.isRunning;
    bool_t bCond4 = (::WaitForSingleObject(_handle.get(), 0UL) != WAIT_OBJECT_0);
    bool_t bCond5 = (dwRv == STILL_ACTIVE);

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isPaused_impl()
{
    bool_t bRv = !_eventPause.isSignaled() && _handle.isValid();

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isExited_impl()
{
    bool_t bRv = _eventExit.isSignaled() && _handle.isValid();

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
    xTEST_EQ(_handle.isValid(), true);
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, a_wnd);
    xTEST_DIFF(FALSE, ::IsWindow(a_wnd));

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
    xTEST_EQ(_handle.isValid(), true);
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, a_wnd);
    xTEST_DIFF(FALSE, ::IsWindow(a_wnd));

    (void_t)::SendMessage(a_wnd, a_msg, static_cast<WPARAM>( a_param1 ),
        static_cast<LPARAM>( a_param2 ));
    xTEST_EQ(0UL, NativeError::get());
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::postThreadMessage(
    uint_t a_msg,
    uint_t a_param1,
    long_t a_param2
) const
{
    xTEST_EQ(_handle.isValid(), true);

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
    xTEST_EQ(_handle.isValid(), true);

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
    xTEST_EQ(_handle.isValid(), true);
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
    xTEST_EQ(_handle.isValid(), true);
    xTEST_EQ(a_msgs.empty(), false);

    BOOL blRv = FALSE;
    MSG  msg  = {0};

    while ((blRv = ::GetMessage(&msg, nullptr, 0, 0 ))) {
        xTEST_DIFF(blRv, - 1);

        for (size_t i = 0; i < a_msgs.size(); ++ i) {
            xCHECK_DO(a_msgs.at(i) != msg.message, continue);

            Utils::ptrAssignT(a_msg,    msg.message                      );
            Utils::ptrAssignT(a_param1, static_cast<uint_t>( msg.wParam ));
            Utils::ptrAssignT(a_param2, static_cast<long_t>( msg.lParam ));

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
    const Priority a_priority
) const
{
    xTEST_EQ(_handle.isValid(), true);

    BOOL blRv = ::SetThreadPriority(_handle.get(), a_priority);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
Thread::Priority
Thread::_priority_impl() const
{
    Thread::Priority tpRv = static_cast<Priority>( ::GetThreadPriority(_handle.get()) );
    xTEST_DIFF(tpError, tpRv);

    return tpRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isPriorityBoost_impl() const
{
    xTEST_EQ(_handle.isValid(), true);

    BOOL isDisablePriorityBoost = TRUE;

    BOOL blRv = ::GetThreadPriorityBoost(_handle.get(), &isDisablePriorityBoost);
    xTEST_DIFF(blRv, FALSE);

    return ! isDisablePriorityBoost;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_setPriorityBoost_impl(
    cbool_t a_isEnabled
) const
{
    xTEST_EQ(_handle.isValid(), true);

    BOOL blRv = ::SetThreadPriorityBoost(_handle.get(), ! a_isEnabled);
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
    cint_t &a_procNum
) const
{
    xTEST_EQ(_handle.isValid(), true);

#if xARCH_BITS_32
    DWORD_PTR mask = 1UL  << a_procNum;
#else
    DWORD_PTR mask = 1i64 << a_procNum;
#endif

    DWORD_PTR pdwRv = ::SetThreadAffinityMask(_handle.get(), mask);
#if xARCH_BITS_32
    xTEST_DIFF(0UL, pdwRv);
#else
    xTEST_PTR(pdwRv);
#endif

    xTEST_EQ(ERROR_INVALID_PARAMETER != pdwRv, true);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_setCpuIdeal_impl(
    culong_t &a_idealCpu    ///< value is zero-based
) const
{
    xTEST_EQ(_handle.isValid(), true);

    DWORD dwRv = ::SetThreadIdealProcessor(_handle.get(), a_idealCpu);
    xTEST_DIFF((DWORD) - 1, dwRv);
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::_cpuIdeal_impl() const
{
    ulong_t ulRv = ::SetThreadIdealProcessor(_handle.get(), MAXIMUM_PROCESSORS);
    xTEST_DIFF((ulong_t) - 1, ulRv);

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
    xTEST_EQ(_handle.isValid(), true);

    return _handle.get();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::_exitStatus_impl() const
{
    xTEST_EQ(_handle.isValid(), true);

    ulong_t ulRv = 0UL;

    BOOL blRv = ::GetExitCodeThread(_handle.get(), &ulRv);
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

    tagTHREADNAME_INFO info = {0};
    info.dwType = 0x1000;
#if xUNICODE
    // TODO: [skynowa] Thread::setDebugName() - convert from Unicode to Ansi
    //// info.pszName    = xT2A(csName).c_str();
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
    culong_t &a_access,
    cbool_t  &a_isInheritHandle,
    culong_t &a_id
)
{
    handle_t hRv = ::OpenThread(a_access, a_isInheritHandle, a_id);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    return hRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isCurrent_impl(
    const Thread::id_t &a_id
)
{
    bool_t bRv = (currentId() == a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
Thread::id_t
Thread::_currentId_impl()
{
    id_t ulRv = ::GetCurrentThreadId();
    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Thread::handle_t
Thread::_currentHandle_impl()
{
    handle_t hRv = ::GetCurrentThread();
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_currentYield_impl()
{
    (void_t)::SwitchToThread();
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_currentSleep_impl(
    culong_t &a_timeoutMsec
)
{
    (void_t)::Sleep(a_timeoutMsec);
}
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
