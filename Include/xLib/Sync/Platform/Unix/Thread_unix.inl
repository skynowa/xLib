/**
 * \file  Thread.inl
 * \brief thread
 */


xNAMESPACE_BEGIN2(xl, sync)

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
    int_t          iRv = - 1;
    id_t           hid;
    pthread_attr_t attrs; Utils::structZeroT(attrs);

    iRv = ::pthread_attr_init(&attrs);
    xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));

    // TODO: [skynowa] Thread::_create_impl() - PTHREAD_CREATE_DETACHED
    iRv = ::pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE);
    xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));

    if (a_stackSizeBytes != 0U) {
        // TODO: [skynowa] Thread::_create_impl() - size_t size = PTHREAD_STACK_MIN + 0x4000;
        iRv = ::pthread_attr_setstacksize(&attrs, a_stackSizeBytes);
        xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));
    }

    iRv = ::pthread_create(&hid, &attrs, &_s_jobEntry, this);
    xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));
    xTEST_EQ_MSG(true, hid > 0, NativeError::format( static_cast<ulong_t>(iRv) ));

    iRv = ::pthread_attr_destroy(&attrs);
    xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));

    _handle = hid;  // TODO: [skynowa] Thread::_create_impl() - is it right?
    _id     = hid;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    int_t iRv = ::pthread_kill(_id, SIGALRM);
    xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));

    currentSleep(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_wait_impl(
    culong_t &a_timeoutMsec
) const
{
    xUNUSED(a_timeoutMsec);

    // TODO: [skynowa] Thread::_wait_impl() - thread must not be detached
    // FIX:  Thread::_wait_impl(( - a_timeoutMsec

    int_t iRv = ::pthread_join(_id, nullptr);
    xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));
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
    bool_t bRv = _state.isCreated && (_handle != 0UL);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isRunning_impl() const
{
    bool_t bRv = false;

    bool_t bCond1 = (_handle != 0UL);
    bool_t bCond2 = (_id > 0);
    bool_t bCond3 = (_state.isRunning);

#if xTODO
    bool_t bCond4 = (::WaitForSingleObject(_handle.get(), 0UL) != WAIT_OBJECT_0);
    bool_t bCond5 = (ulRv == STILL_ACTIVE);
#endif

    bRv = bCond1 && bCond2 && bCond3 /* && bCond4 && bCond5 */;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isPaused_impl()
{
    bool_t bRv = !_eventPause.isSignaled() /* && (0UL != _handle) */;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isExited_impl()
{
    bool_t bRv = _eventExit.isSignaled() && (0UL != _handle);

    return bRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: messages
*
**************************************************************************************************/


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
    if (!User().isAdmin()) {
        Trace() << xT("::: xLib: warning (Thread::setPriority fail, need root) :::");
        return;
    }

    sched_param param = {0};
    param.sched_priority = static_cast<int>(a_priority);

    int_t iRv = ::pthread_setschedparam(id(), SCHED_FIFO, &param);
    xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
Thread::Priority
Thread::_priority_impl() const
{
    sched_param param  = {0};
    int_t       policy = SCHED_FIFO;

    int_t iRv = ::pthread_getschedparam(id(), &policy, &param);
    xTEST_EQ_MSG(0, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));

    Thread::Priority tpRv = static_cast<Priority>( param.sched_priority );

    return tpRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_isPriorityBoost_impl() const
{
    return false;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_setPriorityBoost_impl(
    cbool_t &a_isEnabled
) const
{
    xUNUSED(a_isEnabled);

    return;
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
#if   xENV_LINUX
    cpu_set_t cpuSet;
#elif xENV_BSD
    cpuset_t  cpuSet;
#endif

    CPU_ZERO(&cpuSet);
    CPU_SET(a_procNum, &cpuSet);

    // ANDROID: ::sched_setaffinity
#if xTODO_ANDROID && 0
    int_t iRv = ::sched_setaffinity(static_cast<pid_t>( id() ), sizeof(cpuSet), &cpuSet);
    xTEST_DIFF_MSG(- 1, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));
#endif

    // pthread_setaffinity_np
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_setCpuIdeal_impl(
    culong_t &a_idealCpu    ///< value is zero-based
) const
{
    xUNUSED(a_idealCpu);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::_cpuIdeal_impl() const
{
    ulong_t ulRv = (ulong_t) - 1;

    xNOT_IMPLEMENTED

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
    return _handle;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::_exitStatus_impl() const
{
    return _exitStatus;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_setDebugName_impl(
    std::ctstring_t &a_name
) const
{
#if   xENV_LINUX
    int_t iRv = ::prctl(PR_SET_NAME, a_name.c_str(), 0, 0, 0);
    xTEST_DIFF(iRv, - 1);
#elif xENV_BSD
    (void_t)pthread_set_name_np(id(), a_name.c_str());
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
    xUNUSED(a_access);
    xUNUSED(a_isInheritHandle);
    xUNUSED(a_id);

    handle_t hRv = 0;

    // TODO: [skynowa] Thread::_open_impl()

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
    bool_t bRv = ::pthread_equal(currentId(), a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
Thread::id_t
Thread::_currentId_impl()
{
    id_t ulRv = ::pthread_self();
    xTEST_EQ(ulRv > 0, true);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
Thread::handle_t
Thread::_currentHandle_impl()
{
    handle_t hRv = ::pthread_self();
    xTEST_EQ(hRv > 0, true);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_currentYield_impl()
{
    int_t iRv = ::sched_yield();
    xTEST_DIFF_MSG(- 1, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_currentSleep_impl(
    culong_t &a_timeoutMsec
)
{
    timespec timeSleep  = {0, 0};
    timespec timeRemain = {0, 0};

    timeSleep.tv_sec  = a_timeoutMsec / 1000;
    timeSleep.tv_nsec = (a_timeoutMsec % 1000) * (1000 * 1000);

    for ( ; ; ) {
        int_t iRv = ::nanosleep(&timeSleep, &timeRemain);
        xTEST_NA(iRv);
        xCHECK_DO(!(- 1 == iRv && EINTR == NativeError::get()), break);

        timeSleep = timeRemain;
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
Thread::_priorityMin_impl()
{
    int_t iRv = ::sched_get_priority_min(SCHED_FIFO);
    xTEST_DIFF_MSG(- 1, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
Thread::_priorityMax_impl()
{
    int_t iRv = ::sched_get_priority_max(SCHED_FIFO);
    xTEST_DIFF_MSG(- 1, iRv, NativeError::format( static_cast<ulong_t>(iRv) ));

    return iRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
