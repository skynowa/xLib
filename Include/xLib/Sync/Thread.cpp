/**
 * \file  Thread.inl
 * \brief thread
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Thread.h"
#endif

#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>
#include <xLib/System/SystemInfo.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Thread_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Thread_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/Thread_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/Thread_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Thread_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Thread::Thread(
    cbool_t &a_isAutoDelete
) :
    // data
    _tag         (0UL),
    _handle      (),
    _id          (0UL),
    _exitStatus  (0U),
    _param       (xPTR_NULL),
    _isAutoDelete(a_isAutoDelete),
    // states
    _state       (),
    // other
    _eventStarter(xPTR_NULL),
    _eventPause  (false, false),
    _eventExit   (true,  false)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Thread::~Thread()
{
    // close thread, if it still running
    bool_t bRv = isRunning();
    if (bRv) {
        exit();

        // TODO: Thread::~Thread()
    #if xTODO
        if (!bRv) {
            kill(_s_exitTimeoutMsec);
            if (!bRv) {
                xTEST_FAIL;
            }
        }
    #endif
    }

    _clear(0U);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::setTag(
    culong_t &a_tag
)
{
    _tag = a_tag;
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
Thread::tag() const
{
    return _tag;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::create(
    cbool_t &a_isPaused,
    cuint_t &a_stackSizeBytes,
    void_t  *a_param
)
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), false);
#elif xENV_UNIX

#endif
    xTEST_NA(a_isPaused);
    xTEST_NA(a_stackSizeBytes);
    xTEST_NA(a_param);

    _param = a_param;

    // events
    _eventStarter = new Event(true, false);
    xTEST_PTR(_eventStarter);

    _eventStarter->create();
    _eventPause.create();
    _eventExit.create();

    // start
    _create_impl(a_stackSizeBytes);
    xTEST_EQ(isCurrent(_id), false);

    // states
    {
        _state.isCreated = true;
        _state.isRunning = true;

        if (a_isPaused) {
            pause();
        } else {
            resume();
        }
    }

    // construction is complete, start job entry
    _eventStarter->set();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::resume()
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    _eventPause.set();

    // states
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::pause()
{
#if   xENV_WIN
    xTEST_MSG_EQ(true, _handle.isValid(), String::cast(_handle.get()));
#elif xENV_UNIX

#endif

    _eventPause.reset();

    // states
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::exit()
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    _eventExit.set();

    // states
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a

        xCHECK_DO(isPaused(), resume());
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::kill(
    culong_t &a_timeoutMsec
)
{
    _kill_impl(a_timeoutMsec);
    _clear(0U);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::wait(
    culong_t &a_timeoutMsec
) const
{
    _wait_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: states
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::isCreated() const
{
    // _handle - n/a

    return _isCreated_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::isRunning() const
{
    // _handle - n/a

    return _isRunning_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::isPaused()
{
    // _handle - n/a

    return _isPaused_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::isExited()
{
    // _handle - n/a

    return _isExited_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: priority
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::setPriority(
    const ExPriority &a_priority
) const
{
    _setPriority_impl(a_priority);
}
//-------------------------------------------------------------------------------------------------
xINLINE Thread::ExPriority
Thread::priority() const
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    return _priority_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Thread::priorityString() const
{
    // n/a

    int_t iRv = priority();
    switch (iRv) {
    case tpIdle:
        return xT("Idle");
    case tpLowest:
        return xT("Lowest");
    case tpBelowNormal:
        return xT("Below normal");
    case tpNormal:
        return xT("Normal");
    case tpAboveNormal:
        return xT("Above normal");
    case tpHighest:
        return xT("Highest");
    case tpTimeCritical:
        return xT("Time critical");
    }

    return xT("N/A");
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::priorityUp() const
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    ExPriority tpOldLevel  = tpError;
    ExPriority tpiNewLevel = tpError;

    tpOldLevel = priority();
    switch (tpOldLevel) {
    case tpIdle:
        tpiNewLevel = tpLowest;
        break;
    case tpLowest:
        tpiNewLevel = tpBelowNormal;
        break;
    case tpBelowNormal:
        tpiNewLevel = tpNormal;
        break;
    case tpNormal:
        tpiNewLevel = tpAboveNormal;
        break;
    case tpAboveNormal:
        tpiNewLevel = tpHighest;
        break;
    case tpHighest:
        tpiNewLevel = tpTimeCritical;
        break;
    case tpTimeCritical:
        return;
        break;
    default:
        xTEST_FAIL;
        break;
    }

    setPriority(tpiNewLevel);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::priorityDown() const
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    ExPriority tpOldLevel  = tpError;
    ExPriority tpiNewLevel = tpError;

    tpOldLevel = priority();
    switch (tpOldLevel) {
    case tpIdle:
        return;
        break;
    case tpLowest:
        tpiNewLevel = tpIdle;
        break;
    case tpBelowNormal:
        tpiNewLevel = tpLowest;
        break;
    case tpNormal:
        tpiNewLevel = tpBelowNormal;
        break;
    case tpAboveNormal:
        tpiNewLevel = tpNormal;
        break;
    case tpHighest:
        tpiNewLevel = tpAboveNormal;
        break;
    case tpTimeCritical:
        tpiNewLevel = tpHighest;
        break;
    default:
        xTEST_FAIL;
        break;
    }

    setPriority(tpiNewLevel);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::isPriorityBoost() const
{
    return _isPriorityBoost_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::setPriorityBoost(
    cbool_t &a_isEnabled
) const
{
    _setPriorityBoost_impl(a_isEnabled);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: CPU
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::setCpuAffinity(
    cint_t &a_procNum
) const
{
    _setCpuAffinity_impl(a_procNum);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::setCpuIdeal(
    culong_t &a_idealCpu    ///< value is zero-based
) const
{
    _setCpuIdeal_impl(a_idealCpu);
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
Thread::cpuIdeal() const
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    return _cpuIdeal_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE ulong_t
Thread::cpuCount()
{
    ulong_t ulRv = SystemInfo().numOfCpus();
    xCHECK_RET(ulRv < 1UL || ulRv > 32UL, 1UL);

    // TODO: Thread::cpuCount() - make constant 32UL

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE Thread::handle_t
Thread::handle() const
{
    return _handle_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE Thread::id_t
Thread::id() const
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    return _id;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::isCurrent() const
{
    return isCurrent( currentId() );
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
Thread::exitStatus() const
{
    return _exitStatus_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::setDebugName(
    std::ctstring_t &a_name
) const
{
    xTEST_GR(_id, static_cast<id_t>( 0 ));
    xTEST_GR_EQ(a_name.size(), std::size_t(32)); // TODO: Thread::setDebugName() - MAX_NAME_SIZE = 32

    // TODO: Thread::setDebugName() - xCHECK_RET(!Debugger().isActive(), true);

    _setDebugName_impl(a_name);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE Thread::handle_t
Thread::open(
    culong_t &a_access,
    cbool_t  &a_isInheritHandle,
    culong_t &a_id
)
{
    xTEST_NA(a_access);
    xTEST_NA(a_isInheritHandle);
    xTEST_LESS(0UL, a_id);

    return _open_impl(a_access, a_isInheritHandle, a_id);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::isCurrent(
    const Thread::id_t &a_id
)
{
    return _isCurrent_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
xINLINE Thread::id_t
Thread::currentId()
{
    // n/a

    return _currentId_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE Thread::handle_t
Thread::currentHandle()
{
    // n/a

    return _currentHandle_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::currentYield()
{
    // n/a

    _currentYield_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::currentSleep(
    culong_t &a_timeoutMsec
)
{
    // n/a

    _currentSleep_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    protected: events
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE uint_t
Thread::onRun(
    void_t *a_param
) /* = 0 */
{
    xUNUSED(a_param);

    xTEST_MSG_FAIL(xT("It's virtual method"));

    uint_t uiRv = 0U;

#if xTEMP_DISABLED
    for ( ; ; ) {
        bool_t bRv = isTimeToExit();
        xCHECK_DO(bRv, break);

        //...
    }
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    protected: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::isTimeToExit()
{
    // n/a

    bool_t bRv = false;

    // exit
    bRv = isExited();
    xCHECK_RET(bRv, true);

    // pause / resume
    bRv = isPaused();
    xCHECK_RET(bRv, ! _waitResumption());

    // states
    // n/a

    return false;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE Thread::exit_status_t xSTDCALL
Thread::_s_jobEntry(
    void_t *a_param
)
{
    xTEST_PTR(a_param);

    culong_t waitVaildHandleTimeoutMsec = 500UL;
    culong_t notInfiniteTimeoutMsec     = 10000UL;

    Thread *self = static_cast<Thread *>( a_param );
    xTEST_PTR(self);

    // handle must be valid
    currentSleep(waitVaildHandleTimeoutMsec);

    Event::ExObjectState osRv = self->_eventStarter->wait(notInfiniteTimeoutMsec);
    xTEST_EQ(Event::osSignaled, osRv);

    xPTR_DELETE(self->_eventStarter);

    // if created suspended thread - wait for resumption
    if ( self->isPaused() ) {
        bool_t bRv = self->_waitResumption();
        xTEST_EQ(bRv, true);
    }

    uint_t exitStatus = 0U;
    {
        {
            // TODO: Thread::_s_jobEntry() - begin of thread function
        }

        // run thread function
        try {
            exitStatus = self->onRun(self->_param);
        }
        catch (std::exception &e) {
            std::string what = e.what();
            xTEST_MSG_FAIL(xS2TS(what));
        }
        catch (...) {
            xTEST_FAIL;
        }

        {
            // TODO: Thread::_s_jobEntry() - end of thread function
        }
    }

    self->_clear(exitStatus);
    xCHECK_DO(self->_isAutoDelete, xPTR_DELETE(self));

#if   xENV_WIN
    exit_status_t esRv = exitStatus;
#elif xENV_UNIX
    exit_status_t esRv = &exitStatus;
#endif

    return esRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Thread::_waitResumption()
{
    // states
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }

    Event::ExObjectState osRv = _eventPause.wait();
    xTEST_DIFF(Event::osFailed, osRv);
    xTEST_DIFF(Event::osTimeout, osRv);
    xTEST_EQ(Event::osSignaled, osRv);

    return (Event::osSignaled == osRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Thread::_clear(
    cuint_t &a_exitStatus
)
{
    _tag        = 0UL;

#if   xENV_WIN
    _handle.close();
#elif xENV_UNIX
    _handle     = 0UL;
#endif

    _id         = 0UL;
    _exitStatus = a_exitStatus;
    _param      = xPTR_NULL;

    // states
    _state.isCreated = false;
    _state.isRunning = false;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE int_t
Thread::_priorityMin()
{
    return _priorityMin_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE int_t
Thread::_priorityMax()
{
    return _priorityMax_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
