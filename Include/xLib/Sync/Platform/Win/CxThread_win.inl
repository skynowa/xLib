/**
 * \file  CxThread.inl
 * \brief thread
 */


xNAMESPACE_BEGIN2(xlib, sync)


/**************************************************************************************************
*    public: actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_create_impl(
    cuint_t &a_stackSize
)
{
    id_t id = 0UL;

    HANDLE hRv = reinterpret_cast<HANDLE>( ::_beginthreadex(xPTR_NULL, a_stackSize, _s_jobEntry,
        this, 0U, (uint_t *)&id) );
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
    xTEST_LESS(0UL, id);

    _handle.set(hRv);
    xTEST_EQ(_handle.isValid(), true);

    _id = id;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_kill_impl(
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
inline void_t
CxThread::_wait_impl(
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
inline bool_t
CxThread::_isCreated_impl() const
{
    bool_t bRv = _state.isCreated && _handle.isValid();

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_isRunning_impl() const
{
    bool_t bRv = false;

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
inline bool_t
CxThread::_isPaused_impl()
{
    bool_t bRv = !_eventPause.isSignaled() && _handle.isValid();

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_isExited_impl()
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
inline void_t
CxThread::postMessage(
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
inline void_t
CxThread::sendMessage(
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
    xTEST_EQ(0UL, CxLastError::get());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::postThreadMessage(
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

#endif
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::tryPostThreadMessage(
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
inline void_t
CxThread::messageWaitQueue(
    uint_t  a_msg,
    uint_t *a_param1,
    long_t *a_param2
) const
{
    xTEST_EQ(_handle.isValid(), true);
    xTEST_LESS(0U, a_msg);

    std::vector<uint_t> msgs;
    msgs.push_back(a_msg);

    messageWaitQueue(msgs, xPTR_NULL, a_param1, a_param2);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::messageWaitQueue(
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

    while ((blRv = ::GetMessage(&msg, xPTR_NULL, 0, 0 ))) {
        xTEST_DIFF(blRv, - 1);

        for (size_t i = 0; i < a_msgs.size(); ++ i) {
            xCHECK_DO(a_msgs.at(i) != msg.message, continue);

            CxUtils::ptrAssignT(a_msg,    msg.message                      );
            CxUtils::ptrAssignT(a_param1, static_cast<uint_t>( msg.wParam ));
            CxUtils::ptrAssignT(a_param2, static_cast<long_t>( msg.lParam ));

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
inline void_t
CxThread::_setPriority_impl(
    const ExPriority &a_priority
) const
{
    xTEST_EQ(_handle.isValid(), true);

    BOOL blRv = ::SetThreadPriority(_handle.get(), a_priority);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline CxThread::ExPriority
CxThread::_priority_impl() const
{
    CxThread::ExPriority tpRv = static_cast<ExPriority>( ::GetThreadPriority(_handle.get()) );
    xTEST_DIFF(tpError, tpRv);

    return tpRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_isPriorityBoost_impl() const
{
    xTEST_EQ(_handle.isValid(), true);

    BOOL isDisablePriorityBoost = TRUE;

    BOOL blRv = ::GetThreadPriorityBoost(_handle.get(), &isDisablePriorityBoost);
    xTEST_DIFF(blRv, FALSE);

    return ! isDisablePriorityBoost;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_setPriorityBoost_impl(
    cbool_t &a_isEnabled
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
inline void_t
CxThread::_setCpuAffinity_impl(
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
inline void_t
CxThread::_setCpuIdeal_impl(
    culong_t &a_idealCpu    ///< value is zero-based
) const
{
    xTEST_EQ(_handle.isValid(), true);

    DWORD dwRv = ::SetThreadIdealProcessor(_handle.get(), a_idealCpu);
    xTEST_DIFF((DWORD) - 1, dwRv);
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxThread::_cpuIdeal_impl() const
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
inline CxThread::handle_t
CxThread::_handle_impl() const
{
    xTEST_EQ(_handle.isValid(), true);

    return _handle.get();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxThread::_exitStatus_impl() const
{
    xTEST_EQ(_handle.isValid(), true);

    ulong_t ulRv = 0UL;

    BOOL blRv = ::GetExitCodeThread(_handle.get(), &ulRv);
    xTEST_DIFF(blRv, FALSE);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_setDebugName_impl(
    std::ctstring_t &a_name
) const
{
#if xCOMPILER_MS || xCOMPILER_CODEGEAR
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
    // TODO: CxThread::setDebugName() - convert from Unicode to Ansi
    //// info.pszName    = xTS2S(csName).c_str();
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
    // TODO: CxThread::setDebugName() - xCOMPILER_MINGW
#else
    // TODO: CxThread::setDebugName() - other
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline CxThread::handle_t
CxThread::_open_impl(
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
inline bool_t
CxThread::_isCurrent_impl(
    const CxThread::id_t &a_id
)
{
    bool_t bRv = (currentId() == a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline CxThread::id_t
CxThread::_currentId_impl()
{
    id_t ulRv = ::GetCurrentThreadId();
    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxThread::handle_t
CxThread::_currentHandle_impl()
{
    handle_t hRv = ::GetCurrentThread();
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_currentYield_impl()
{
    (void_t)::SwitchToThread();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_currentSleep_impl(
    culong_t &a_timeoutMsec
)
{
    (void_t)::Sleep(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxThread::_priorityMin_impl()
{
    int_t iRv = THREAD_PRIORITY_IDLE;

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxThread::_priorityMax_impl()
{
    int_t iRv = THREAD_PRIORITY_TIME_CRITICAL;

    return iRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
