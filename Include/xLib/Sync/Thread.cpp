/**
 * \file  Thread.cpp
 * \brief thread
 */


#include "Thread.h"

#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>
#include <xLib/Log/LogStream.h>
#include <xLib/System/Info/Cpu.h>
#include <xLib/System/User.h>

#if   xENV_WIN
    #include "Platform/Win/Thread_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Thread_unix.inl"
#endif


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Thread::Thread(
    cbool_t a_isAutoDelete
) :
    _isAutoDelete(a_isAutoDelete)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Thread::~Thread()
{
    // close thread, if it still running
    bool_t bRv = isRunning();
    if (bRv) {
        exit();

        // TODO: [skynowa] Thread::~Thread()
    #if xTODO
        kill(_s_exitTimeoutMsec);
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
void_t
Thread::setTag(
    culong_t a_tag
)
{
    _tag = a_tag;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::tag() const
{
    return _tag;
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::create(
    cbool_t  a_isPaused,
    cuint_t  a_stackSizeBytes,
    void_t  *a_param
)
{
    xTEST(!isHandleValid());
    xTEST_NA(a_isPaused);
    xTEST_NA(a_stackSizeBytes);
    xTEST_NA(a_param);

    _param = a_param;

    // events
    cbool_t isAutoReset {true};
	cbool_t isSignaled  {false};
    _eventStarter = new Event(isAutoReset, isSignaled);
    _eventStarter->create();

    _eventPause.create();
    _eventExit.create();

    // start
    _create_impl(a_stackSizeBytes);
    xTEST(!isCurrent(_id));

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
void_t
Thread::resume()
{
    xTEST(isHandleValid());

    _eventPause.set();

    // states
    {
        // _state.isCreated - n/a
        // _state.isRunning - n/a
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::pause()
{
    xTEST(isHandleValid());

    _eventPause.reset();

    // states
    {
        // _state.isCreated - n/a
        // _state.isRunning - n/a
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::exit()
{
    xTEST(isHandleValid());

    _eventExit.set();

    // states
    {
        // _state.isCreated - n/a
        // _state.isRunning - n/a

        xCHECK_DO(isPaused(), resume());
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::kill(
    culong_t a_timeoutMsec
)
{
    _kill_impl(a_timeoutMsec);
    _clear(0U);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::wait(
    culong_t a_timeoutMsec
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
bool_t
Thread::isCreated() const
{
    // _handle - n/a

    return _isCreated_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::isRunning() const
{
    // _handle - n/a

    return _isRunning_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::isPaused()
{
    // _handle - n/a

    return _isPaused_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
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
void_t
Thread::setPriority(
    cPriority a_priority
) const
{
    _setPriority_impl(a_priority);
}
//-------------------------------------------------------------------------------------------------
Thread::Priority
Thread::priority() const
{
    xTEST(isHandleValid());

    return _priority_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::priorityUp() const
{
    xTEST(isHandleValid());

    Priority tpOldLevel  = Priority::tpError;
    Priority tpiNewLevel = Priority::tpError;

    tpOldLevel = priority();
    switch (tpOldLevel) {
    case Priority::tpIdle:
        tpiNewLevel = Priority::tpLowest;
        break;
    case Priority::tpLowest:
        tpiNewLevel = Priority::tpBelowNormal;
        break;
    case Priority::tpBelowNormal:
        tpiNewLevel = Priority::tpNormal;
        break;
    case Priority::tpNormal:
        tpiNewLevel = Priority::tpAboveNormal;
        break;
    case Priority::tpAboveNormal:
        tpiNewLevel = Priority::tpHighest;
        break;
    case Priority::tpHighest:
        tpiNewLevel = Priority::tpTimeCritical;
        break;
    case Priority::tpTimeCritical:
        return;
        break;
    default:
        xTEST_FAIL;
        break;
    }

    setPriority(tpiNewLevel);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::priorityDown() const
{
    xTEST(isHandleValid());

    Priority tpOldLevel  = Priority::tpError;
    Priority tpiNewLevel = Priority::tpError;

    tpOldLevel = priority();
    switch (tpOldLevel) {
    case Priority::tpIdle:
        return;
        break;
    case Priority::tpLowest:
        tpiNewLevel = Priority::tpIdle;
        break;
    case Priority::tpBelowNormal:
        tpiNewLevel = Priority::tpLowest;
        break;
    case Priority::tpNormal:
        tpiNewLevel = Priority::tpBelowNormal;
        break;
    case Priority::tpAboveNormal:
        tpiNewLevel = Priority::tpNormal;
        break;
    case Priority::tpHighest:
        tpiNewLevel = Priority::tpAboveNormal;
        break;
    case Priority::tpTimeCritical:
        tpiNewLevel =Priority::tpHighest;
        break;
    default:
        xTEST_FAIL;
        break;
    }

    setPriority(tpiNewLevel);
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::isPriorityBoost() const
{
    return _isPriorityBoost_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::setPriorityBoost(
    cbool_t a_isEnabled
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
void_t
Thread::setCpuAffinity(
    cint_t a_procNum
) const
{
    _setCpuAffinity_impl(a_procNum);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::setCpuIdeal(
    culong_t a_idealCpu    ///< value is zero-based
) const
{
    _setCpuIdeal_impl(a_idealCpu);
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::cpuIdeal() const
{
    xTEST(isHandleValid());

    return _cpuIdeal_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
ulong_t
Thread::cpuCount()
{
    ulong_t ulRv = info::Cpu().num();
    xCHECK_RET(ulRv < 1UL || ulRv > 32UL, 1UL);

    // TODO: [skynowa] Thread::cpuCount() - make constant 32UL

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public: Checks
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Thread::isHandleValid() const
{
    return isHandleValid(_handle);
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::isIdValid() const
{
    return isIdValid(_id);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Thread::isHandleValid(
	chandle_t a_handle
)
{
	bool_t bRv {};

#if   xENV_WIN
	bRv = (a_handle != xNATIVE_HANDLE_NULL);
#elif xENV_UNIX
	#if xENV_APPLE
		bRv = (a_handle != nullptr);
	#else
		bRv = (a_handle > 0);
	#endif
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Thread::isIdValid(
	cid_t a_id
)
{
	bool_t bRv {};

#if   xENV_WIN
	bRv = (a_id > 0UL);
#elif xENV_UNIX
	#if xENV_APPLE
		bRv = (a_id != nullptr);
	#else
		bRv = (a_id > 0);
	#endif
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Thread::handle_t
Thread::handle() const
{
    return _handle_impl();
}
//-------------------------------------------------------------------------------------------------
Thread::id_t
Thread::id() const
{
    xTEST(isHandleValid());

    return _id;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::isCurrent() const
{
    return isCurrent( currentId() );
}
//-------------------------------------------------------------------------------------------------
ulong_t
Thread::exitStatus() const
{
    return _exitStatus_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::setDebugName(
    std::ctstring_t &a_name
) const
{
    xTEST(isIdValid());
    xTEST_LESS_EQ(a_name.size(), xTHREAD_NAME_LENGTH_MAX);

    std::tstring_t name = a_name;

    if (name.size() > xTHREAD_NAME_LENGTH_MAX) {
        name.resize(xTHREAD_NAME_LENGTH_MAX);
    }

    // TODO: [skynowa] Thread::setDebugName() - xCHECK_RET(!Debugger().isActive(), true);

    _setDebugName_impl(name);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
Thread::handle_t
Thread::open(
    culong_t  a_access,
    cbool_t   a_isInheritHandle,
    cid_t    &a_id
)
{
    xTEST_NA(a_access);
    xTEST_NA(a_isInheritHandle);
    xTEST(isIdValid(a_id));

    return _open_impl(a_access, a_isInheritHandle, a_id);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    protected: events
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
uint_t
Thread::onRun(
    void_t *a_param
) /* = 0 */
{
    xUNUSED(a_param);

    xTEST_FAIL_MSG(xT("It's virtual method"));

    uint_t uiRv {};

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
bool_t
Thread::isTimeToExit()
{
    // n/a

    bool_t bRv {};

    // exit
    bRv = isExited();
    xCHECK_RET(bRv, true);

    // pause / resume
    bRv = isPaused();
    xCHECK_RET(bRv, !_waitResumption());

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
Thread::exit_status_t xSTDCALL
Thread::_func(
    void_t *a_param
)
{
    xTEST_PTR(a_param);

    culong_t waitVaildHandleTimeoutMsec = 500UL;
    culong_t notInfiniteTimeoutMsec     = 10000UL;

    Thread *self = static_cast<Thread *>( a_param );
    xTEST_PTR(self);
    xCHECK_RET(self == nullptr, exit_status_t{}); // 0 - as error

    // handle must be valid
    currentSleep(waitVaildHandleTimeoutMsec);

    Event::ObjectState osRv = self->_eventStarter->wait(notInfiniteTimeoutMsec);
    xTEST(osRv == Event::ObjectState::osSignaled);

    Utils::ptrDeleteT(self->_eventStarter);

    // if created suspended thread - wait for resumption
    if ( self->isPaused() ) {
        bool_t bRv = self->_waitResumption();
        xTEST(bRv);
    }

    static uint_t exitStatus {};
    {
        {
            // TODO: [skynowa] Thread::_func() - begin of thread function
        }

        // run thread function
        try {
            exitStatus = self->onRun(self->_param);
        }
        catch (std::exception &a_exc) {
            std::cstring_t &what = a_exc.what();
            xTEST_FAIL_MSG(xA2T(what));
        }
        catch (...) {
            xTEST_FAIL;
        }

        {
            // TODO: [skynowa] Thread::_func() - end of thread function
        }
    }

    self->_clear(exitStatus);
    xCHECK_DO(self->_isAutoDelete, Utils::ptrDeleteT(self));

#if   xENV_WIN
    cexit_status_t esRv = exitStatus;
#elif xENV_UNIX
    cexit_status_t esRv = &exitStatus;
#endif

    return esRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Thread::_waitResumption()
{
    // states
    {
        // _state.isCreated - n/a
        // _state.isRunning - n/a
    }

    const Event::ObjectState osRv = _eventPause.wait();
    // TODO: [skynowa] StdStreamV2
    ///-- xTEST_DIFF(Event::ObjectState::osFailed, osRv);
    ///-- xTEST_DIFF(Event::ObjectState::osTimeout, osRv);
    ///-- xTEST_EQ(Event::ObjectState::osSignaled, osRv);

    return (Event::ObjectState::osSignaled == osRv);
}
//-------------------------------------------------------------------------------------------------
void_t
Thread::_clear(
    cuint_t a_exitStatus
)
{
    _tag        = 0UL;

#if   xENV_WIN
    ::CloseHandle(_handle);
    _handle = xNATIVE_HANDLE_NULL;
#elif xENV_UNIX
    _handle     = 0UL;
#endif

    _id         = 0UL;
    _exitStatus = a_exitStatus;
    _param      = nullptr;

    // states
    _state.isCreated = false;
    _state.isRunning = false;
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
Thread::_priorityMin()
{
    return _priorityMin_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
int_t
Thread::_priorityMax()
{
    return _priorityMax_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
