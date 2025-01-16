/**
 * \file  Thread.h
 * \brief thread
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Sync/Event.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class Thread
    /// thread
{
public:
#if   xENV_WIN
    using handle_t = HANDLE;	///< handle
    using id_t     = DWORD;     ///< ID
#elif xENV_UNIX
    using handle_t = pthread_t; ///< handle
    using id_t     = pthread_t;	///< ID
#endif
    xUSING_CONST(handle_t);
    xUSING_CONST(id_t);

    enum class Priority
        /// priotity
    {
    #if   xENV_WIN
        tpError        = THREAD_PRIORITY_ERROR_RETURN,
        tpIdle         = THREAD_PRIORITY_IDLE,
        tpLowest       = THREAD_PRIORITY_LOWEST,
        tpBelowNormal  = THREAD_PRIORITY_BELOW_NORMAL,
        tpNormal       = THREAD_PRIORITY_NORMAL,
        tpAboveNormal  = THREAD_PRIORITY_ABOVE_NORMAL,
        tpHighest      = THREAD_PRIORITY_HIGHEST,
        tpTimeCritical = THREAD_PRIORITY_TIME_CRITICAL
    #elif xENV_UNIX
        tpError        = - 1,
        tpIdle         ,
        tpLowest       = 10,
        tpBelowNormal  ,
        tpNormal       ,
        tpAboveNormal  ,
        tpHighest      ,
        tpTimeCritical
    #endif
    };
    xUSING_CONST(Priority);

///\name ctors, dtor
///\{
	explicit  Thread(cbool_t isAutoDelete);
	// BUG: Thread:: ~Thread() - must pure virtual
	virtual  ~Thread() /* = 0*/;

	xNO_COPY_ASSIGN(Thread);
///\}

    // actions
    void_t  setTag(culong_t tag);
        ///< set data tag
    ulong_t tag() const;
        ///< get data tag
    void_t  create(cbool_t isPaused, cuint_t stackSizeBytes, void_t *param);
        ///< start
    void_t  resume();
        ///< resume
    void_t  pause();
        ///< pause
    void_t  exit();
        ///< exit (set flag "exit")
    void_t  kill(culong_t timeoutMsec);
        ///< kill
    void_t  wait(culong_t timeoutMsec) const;
        ///< wait

    // flags
    bool_t isCreated() const;
        ///< is created
    bool_t isRunning() const;
        ///< is running
    bool_t isPaused();
        ///< is paused
    bool_t isExited();
        ///< is exited (is set flag "exit")

#if xENV_WIN
    // messages
    void_t postMessage(HWND wnd, uint_t msg, uint_t param1, long_t param2) const;
        ///< post message from thread to window
    void_t sendMessage(HWND wnd, uint_t msg, uint_t param1, long_t param2) const;
        ///< send message from thread to window
    void_t postThreadMessage(uint_t msg, uint_t param1, long_t param2) const;
        ///< post message from thread to thread
    bool_t tryPostThreadMessage(uint_t msg, uint_t param1, long_t param2, ulong_t attempsNum,
                ulong_t attempTimeoutMsec) const;
        ///< try post message from thread to thread
    void_t messageWaitQueue(uint_t msg, uint_t *param1, long_t *param2) const;
        ///< waiting for message with params from other thread
    void_t messageWaitQueue(const std::vector<uint_t> &msgs, uint_t *msg, uint_t *param1,
                long_t *param2) const;
        ///< waiting for message with params from other thread
#endif

    // priority
    void_t   setPriority(cPriority priority) const;
        ///< set priority (under Linux must use admin privilege)
    Priority priority() const;
        ///< get priority
    void_t   priorityUp() const;
        ///< increase priority on one level
    void_t   priorityDown() const;
        ///< decrease priority on one level
    bool_t   isPriorityBoost() const;
        ///< get priority boost control state
    void_t   setPriorityBoost(cbool_t isEnabled) const;
        ///< disables/enables the ability of the system to temporarily boost the priority of a thread

    // CPU
    void_t  setCpuAffinity(cint_t procNum) const;
        ///< set processor affinity
    void_t  setCpuIdeal(culong_t idealCpu) const;
        ///< sets preferred processor for a thread
    ulong_t cpuIdeal() const;
        ///< get current ideal processor without changing it
    static ulong_t cpuCount();
        ///< get CPU count on machine

    // Checks
    bool_t isHandleValid() const;
    bool_t isIdValid() const;

    static bool_t isHandleValid(chandle_t handle);
    static bool_t isIdValid(cid_t id);

    // other
    handle_t handle() const;
        ///< get handle
    id_t     id() const;
        ///< get ID
    bool_t   isCurrent() const;
        ///< is current
    ulong_t  exitStatus() const;
        ///< get termination status
    void_t   setDebugName(std::ctstring_t &name) const;
        ///< set name your threads in the debugger thread list

    // static
    static handle_t open(culong_t access, cbool_t isInheritHandle, cid_t &id);
        ///< opens an existing thread object

    // current thread
    static bool_t   isCurrent(cid_t id);
        ///< is current id
    static id_t     currentId();
        ///< get the thread identifier of the calling thread
    static handle_t currentHandle();
        ///< get pseudo handle for the calling thread
    static void_t   currentYield();
        ///< yield
    static void_t   currentSleep(culong_t timeoutMsec);
        ///< sleep

protected:
    // BUG: Thread::onRun() - must pure virtual
    virtual uint_t  onRun(void_t *param) /* = 0 */;
        ///< work thread function, must be override

    // events
    bool_t isTimeToExit();
        ///< is need to exit from work thread function

private:
#if   xENV_WIN
    using exit_status_t = uint_t;
#elif xENV_UNIX
    using exit_status_t = void_t *;
#endif
    xUSING_CONST(exit_status_t);

    // constants
    static culong_t _s_stillActiveTimeoutMsec = 2UL;
        ///< still active timeout (msec)
    static culong_t _s_exitTimeoutMsec = 5000UL;
        ///< exit timeout (msec)

    // thread data
    volatile ulong_t _tag {};          ///< data tag
    handle_t         _handle {};       ///< native handle
    id_t             _id {};           ///< ID
    uint_t           _exitStatus {};   ///< exit code
    void_t          *_param {};        ///< param for job function
    cbool_t          _isAutoDelete {}; ///< is auto delete thread object

    struct State
        ///< thread state flags
    {
        bool_t isCreated {};  ///< is created
        bool_t isRunning {};  ///< is running
    } _state;

    // other
    Event *_eventStarter {};            ///< starter event
    Event  _eventPause {false, false};  ///< pause event
    Event  _eventExit {true,  false};   ///< exit event

    static exit_status_t xSTDCALL _func(void_t *param);
        ///< callback
    bool_t _waitResumption();
        ///< waiting for reset pause
    void_t _clear(cuint_t a_exitStatus);
        ///< clear class data

    // static
    static int_t _priorityMin();
    static int_t _priorityMax();

xPLATFORM_IMPL:
    void_t   _create_impl(cuint_t stackSizeBytes);
    void_t   _kill_impl(culong_t timeoutMsec);
    void_t   _wait_impl(culong_t timeoutMsec) const;
    bool_t   _isCreated_impl() const;
    bool_t   _isRunning_impl() const;
    bool_t   _isPaused_impl() const;
    bool_t   _isExited_impl() const;
    void_t   _setPriority_impl(cPriority priority) const;
    Priority _priority_impl() const;
    bool_t   _isPriorityBoost_impl() const;
    void_t   _setPriorityBoost_impl(cbool_t isEnabled) const;
    void_t   _setCpuAffinity_impl(cint_t procNum) const;
    void_t   _setCpuIdeal_impl(culong_t idealCpu) const;
    ulong_t  _cpuIdeal_impl() const;
    handle_t _handle_impl() const;
    ulong_t  _exitStatus_impl() const;
    void_t   _setDebugName_impl(std::ctstring_t &name) const;

    static handle_t _open_impl(culong_t access, cbool_t isInheritHandle, cid_t &id);
    static bool_t   _isCurrent_impl(cid_t &id);
    static id_t     _currentId_impl();
    static handle_t _currentHandle_impl();
    static void_t   _currentYield_impl();
    static void_t   _currentSleep_impl(culong_t timeoutMsec);
    static int_t    _priorityMin_impl();
    static int_t    _priorityMax_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------
