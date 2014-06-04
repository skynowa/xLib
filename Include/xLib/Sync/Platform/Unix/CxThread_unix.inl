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
    int_t          iRv = - 1;
    id_t           hid;
    pthread_attr_t attrs; xSTRUCT_ZERO(attrs);

    iRv = ::pthread_attr_init(&attrs);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    // TODO: CxThread::_create_impl() - PTHREAD_CREATE_DETACHED
    iRv = ::pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    if (a_stackSize != 0U) {
        // TODO: CxThread::_create_impl() - size_t size = PTHREAD_STACK_MIN + 0x4000;
        iRv = ::pthread_attr_setstacksize(&attrs, a_stackSize);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_create(&hid, &attrs, &_s_jobEntry, this);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    xTEST_MSG_EQ(true, 0UL < hid, CxLastError::format(iRv));

    iRv = ::pthread_attr_destroy(&attrs);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    _handle = hid;  // TODO: CxThread::_create_impl() - is it right?
    _id     = hid;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_kill_impl(
    culong_t &a_timeoutMsec
)
{
    int_t iRv = ::pthread_kill(_id, SIGALRM);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    currentSleep(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_wait_impl(
    culong_t &a_timeoutMsec
) const
{
    xUNUSED(a_timeoutMsec);

    // TODO: CxThread::_wait_impl() - thread must not be detached
    // FIX:  CxThread::_wait_impl(( - a_timeoutMsec

    int_t iRv = ::pthread_join(_id, xPTR_NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
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
    bool_t bRv = _state.isCreated && (_handle != 0UL);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_isRunning_impl() const
{
    bool_t bRv = false;

    bool_t bCond1 = (_handle != 0UL);
    bool_t bCond2 = (_id > 0UL);
    bool_t bCond3 = (_state.isRunning);

#if xTODO
    bool_t bCond4 = (::WaitForSingleObject(_handle.get(), 0UL) != WAIT_OBJECT_0);
    bool_t bCond5 = (ulRv == STILL_ACTIVE);
#endif

    bRv = bCond1 && bCond2 && bCond3 /* && bCond4 && bCond5 */;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_isPaused_impl()
{
    bool_t bRv = !_eventPause.isSignaled() /* && (0UL != _handle) */;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_isExited_impl()
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
inline void_t
CxThread::_setPriority_impl(
    const ExPriority &a_priority
) const
{
    if (!CxSystemInfo().isUserAdmin()) {
        CxTrace() << xT("::: xLib: warning (CxThread::setPriority fail, need root) :::");
        return;
    }

    sched_param param = {0};
    param.sched_priority = a_priority;

    int_t iRv = ::pthread_setschedparam(id(), SCHED_FIFO, &param);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline CxThread::ExPriority
CxThread::_priority_impl() const
{
    sched_param param  = {0};
    int_t       policy = SCHED_FIFO;

    int_t iRv = ::pthread_getschedparam(id(), &policy, &param);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    CxThread::ExPriority tpRv = static_cast<ExPriority>( param.sched_priority );

    return tpRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_isPriorityBoost_impl() const
{
    return false;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_setPriorityBoost_impl(
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
inline void_t
CxThread::_setCpuAffinity_impl(
    cint_t &a_procNum
) const
{
#if   xOS_LINUX
    cpu_set_t cpuSet;
#elif xOS_FREEBSD
    cpuset_t  cpuSet;
#endif

    CPU_ZERO(&cpuSet);
    (void_t)CPU_SET(a_procNum, &cpuSet);

    int_t iRv = ::pthread_setaffinity_np(id(), sizeof(cpuSet), &cpuSet);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_setCpuIdeal_impl(
    culong_t &a_idealCpu    ///< value is zero-based
) const
{
    xUNUSED(a_idealCpu);

    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxThread::_cpuIdeal_impl() const
{
    ulong_t ulRv = (ulong_t) - 1;

    xNOT_IMPLEMENTED;

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
    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxThread::_exitStatus_impl() const
{
    return _exitStatus;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_setDebugName_impl(
    std::ctstring_t &a_name
) const
{
#if   xOS_LINUX
    int_t iRv = ::prctl(PR_SET_NAME, a_name.c_str(), 0, 0, 0);
    xTEST_DIFF(iRv, - 1);
#elif xOS_FREEBSD
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
inline CxThread::handle_t
CxThread::_open_impl(
    culong_t &a_access,
    cbool_t  &a_isInheritHandle,
    culong_t &a_id
)
{
    xUNUSED(a_access);
    xUNUSED(a_isInheritHandle);
    xUNUSED(a_id);

    handle_t hRv = 0;

    // TODO: CxThread::_open_impl()

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
    bool_t bRv = ::pthread_equal(currentId(), a_id);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline CxThread::id_t
CxThread::_currentId_impl()
{
    id_t ulRv = ::pthread_self();
    xTEST_EQ(0UL < ulRv, true);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxThread::handle_t
CxThread::_currentHandle_impl()
{
    handle_t hRv = ::pthread_self();
    xTEST_EQ(0 < hRv, true);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_currentYield_impl()
{
    int_t iRv = ::sched_yield();
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_currentSleep_impl(
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
        xCHECK_DO(!(- 1 == iRv && EINTR == CxLastError::get()), break);

        timeSleep = timeRemain;
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxThread::_priorityMin_impl()
{
    int_t iRv = ::sched_get_priority_min(SCHED_FIFO);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxThread::_priorityMax_impl()
{
    int_t iRv = ::sched_get_priority_max(SCHED_FIFO);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));

    return iRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
