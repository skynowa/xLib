/**
 * \file  CxThread.inl
 * \brief thread
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/System/CxSystemInfo.h>
#include <xLib/Log/CxTrace.h>

#if   xENV_WIN
    #include "Platform/Win/CxThread_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxThread_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxThread_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxThread_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxThread_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxThread::CxThread(
    cbool_t &a_isAutoDelete
) :
    tag          (0UL),

    // data
    _handle      (),
    _id          (0UL),
    _exitStatus  (0U),
    _param       (xPTR_NULL),
    _isAutoDelete(a_isAutoDelete),

    // flags
    _state       (),

    // other
    _eventStarter(xPTR_NULL),
    _eventPause  (false, false),
    _eventExit   (true,  false)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxThread::~CxThread()
{
    // close thread, if it still running
    bool_t bRv = isRunning();
    if (bRv) {
        exit();

        // TODO: CxThread::~CxThread()
    #if xTODO
        if (!bRv) {
            kill(_s_exitTimeout);
            if (!bRv) {
                xTEST_FAIL;
            }
        }
    #endif
    }

    // state flags
    _setStatesDefault();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::create(
    cbool_t &a_isPaused,
    cuint_t &a_stackSize,
    void_t  *a_param
)
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), false);
#elif xENV_UNIX

#endif
    xTEST_NA(a_isPaused);
    xTEST_NA(a_stackSize);
    xTEST_NA(a_param);

    _param = a_param;

    // events
    _eventStarter = new CxEvent(true, false);
    xTEST_PTR(_eventStarter);

    _eventStarter->create();
    _eventPause.create();
    _eventExit.create();

    // start
    _create_impl(a_stackSize);
    xTEST_EQ(isCurrent(_id), false);

    // flags
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
inline void_t
CxThread::resume()
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    _eventPause.set();

    // flags
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::pause()
{
#if   xENV_WIN
    xTEST_MSG_EQ(true, _handle.isValid(), CxString::cast(_handle.get()));
#elif xENV_UNIX

#endif

    _eventPause.reset();

    // flags
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::exit()
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    _eventExit.set();

    // flags
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a

        xCHECK_DO(isPaused(), resume());
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::kill(
    culong_t &a_timeoutMsec
)
{
    _kill_impl(a_timeoutMsec);

    // clean members
    {
        ulong_t ulRv = 0UL;

    #if   xENV_WIN
        _handle.close();
    #elif xENV_UNIX
        _handle = 0UL;
    #endif

        _id         = 0UL;
        _exitStatus = static_cast<uint_t>( ulRv );  // saving value
        _param      = xPTR_NULL;
        //_isAutoDelete - n/a

        // flags
        _setStatesDefault();
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::wait(
    culong_t &a_timeoutMsec
) const
{
    _wait_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: flags
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isCreated() const
{
    // _handle - n/a

    return _isCreated_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isRunning() const
{
    // _handle - n/a

    return _isRunning_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isPaused()
{
    // _handle - n/a

    return _isPaused_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isExited()
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
inline void_t
CxThread::setPriority(
    const ExPriority &a_priority
) const
{
    _setPriority_impl(a_priority);
}
//-------------------------------------------------------------------------------------------------
inline CxThread::ExPriority
CxThread::priority() const
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    return _priority_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxThread::priorityString() const
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
inline void_t
CxThread::priorityUp() const
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
inline void_t
CxThread::priorityDown() const
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
inline bool_t
CxThread::isPriorityBoost() const
{
    return _isPriorityBoost_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::setPriorityBoost(
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
inline void_t
CxThread::setCpuAffinity(
    cint_t &a_procNum
) const
{
    _setCpuAffinity_impl(a_procNum);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::setCpuIdeal(
    culong_t &a_idealCpu    ///< value is zero-based
) const
{
    _setCpuIdeal_impl(a_idealCpu);
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxThread::cpuIdeal() const
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    return _cpuIdeal_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
CxThread::cpuCount()
{
    ulong_t ulRv = CxSystemInfo().numOfCpus();
    xCHECK_RET(ulRv < 1UL || ulRv > 32UL, 1UL);

    // TODO: CxThread::cpuCount() - make constant 32UL

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxThread::handle_t
CxThread::handle() const
{
    return _handle_impl();
}
//-------------------------------------------------------------------------------------------------
inline CxThread::id_t
CxThread::id() const
{
#if   xENV_WIN
    xTEST_EQ(_handle.isValid(), true);
#elif xENV_UNIX

#endif

    return _id;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isCurrent() const
{
    return isCurrent( currentId() );
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxThread::exitStatus() const
{
    return _exitStatus_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::setDebugName(
    std::ctstring_t &a_name
) const
{
    xTEST_GR(_id, 0UL);
    xTEST_GR_EQ(a_name.size(), std::size_t(32)); // TODO: CxThread::setDebugName() - MAX_NAME_SIZE = 32

    // TODO: CxThread::setDebugName() - xCHECK_RET(!CxDebugger().isActive(), true);

    _setDebugName_impl(a_name);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline CxThread::handle_t
CxThread::open(
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
inline bool_t
CxThread::isCurrent(
    const CxThread::id_t &a_id
)
{
    return _isCurrent_impl(a_id);
}
//-------------------------------------------------------------------------------------------------
inline CxThread::id_t
CxThread::currentId()
{
    // n/a

    return _currentId_impl();
}
//-------------------------------------------------------------------------------------------------
inline CxThread::handle_t
CxThread::currentHandle()
{
    // n/a

    return _currentHandle_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::currentYield()
{
    // n/a

    _currentYield_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::currentSleep(
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
inline uint_t
CxThread::onRun(
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
inline bool_t
CxThread::isTimeToExit()
{
    // n/a

    bool_t bRv = false;

    // exit
    bRv = isExited();
    xCHECK_RET(bRv, true);

    // pause / resume
    bRv = isPaused();
    xCHECK_RET(bRv, ! _waitResumption());

    // flags
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
inline CxThread::exit_status_t xSTDCALL
CxThread::_s_jobEntry(
    void_t *a_param
)
{
    xTEST_PTR(a_param);

    uint_t uiRv = 0U;
    bool_t bRv  = false;

    CxThread *self = static_cast<CxThread *>( a_param );
    xTEST_PTR(self);

    // handle must be valid
    currentSleep(500UL);

    CxEvent::ExObjectState osRv = self->_eventStarter->wait(10000UL);   // not infinite timeout
    xTEST_EQ(CxEvent::osSignaled, osRv);

    xPTR_DELETE(self->_eventStarter);

    // if created suspended thread - wait for resumption
    if (self->isPaused()) {
        bRv = self->_waitResumption();
        xTEST_EQ(bRv, true);
    }

    {
        // begin of thread function
        try {
            #if xTODO
                self->_vHandler_OnEnter(self);
            #endif
        }
        catch (...) {
            xTEST_FAIL;
        }

        // executing of thread function
        try {
            uiRv = self->onRun(self->_param);
        }
        catch (std::exception &e) {
            std::string asWhat = e.what();
            xTEST_MSG_FAIL(xS2TS(asWhat));
        }
        catch (...) {
            xTEST_FAIL;
        }

        // end of thread function
        try {
            #if xTODO
                self->_vHandler_OnExit(self);
            #endif
        }
        catch (...) {
            xTEST_FAIL;
        }
    }

    // clean members (is need to close ???)
    // TODO: CxThread::_s_jobEntry() - add CxThread::dataClear()
    {
    #if   xENV_WIN
        self->_handle.close();
    #elif xENV_UNIX
        // TODO: CxThread::_s_jobEntry() - close thread
        // _handle.close()
    #endif

        self->_id         = 0UL;
        self->_exitStatus = uiRv;    // ???
        self->_param      = xPTR_NULL;
        // self->_isAutoDelete - n/a

        // flags
        self->_setStatesDefault();
    }

#if   xENV_WIN
    exit_status_t esExitStatus = self->_exitStatus;
#elif xENV_UNIX
    exit_status_t esExitStatus = &self->_exitStatus;
#endif

    xCHECK_DO(self->_isAutoDelete, xPTR_DELETE(self));

    return esExitStatus;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_waitResumption()
{
    // flags
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }

    CxEvent::ExObjectState osRv = _eventPause.wait();
    xTEST_DIFF(CxEvent::osFailed, osRv);
    xTEST_DIFF(CxEvent::osTimeout, osRv);
    xTEST_EQ(CxEvent::osSignaled, osRv);

    return (CxEvent::osSignaled == osRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_setStatesDefault()
{
    // n/a

    // flags
    {
        _state.isCreated = false;
        _state.isRunning = false;
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxThread::_priorityMin()
{
    return _priorityMin_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxThread::_priorityMax()
{
    return _priorityMax_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
