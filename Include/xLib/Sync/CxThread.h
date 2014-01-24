/**
 * \file  CxThread.h
 * \brief thread
 */


#pragma once

#ifndef xLib_CxThreadH
#define xLib_CxThreadH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
#include <xLib/Sync/CxEvent.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, sync)

class CxThread
    /// thread
{
public:
    enum ExPriority
        /// priotity
    {
        #if   xOS_ENV_WIN
            tpError        = THREAD_PRIORITY_ERROR_RETURN,
            tpIdle         = THREAD_PRIORITY_IDLE,
            tpLowest       = THREAD_PRIORITY_LOWEST,
            tpBelowNormal  = THREAD_PRIORITY_BELOW_NORMAL,
            tpNormal       = THREAD_PRIORITY_NORMAL,
            tpAboveNormal  = THREAD_PRIORITY_ABOVE_NORMAL,
            tpHighest      = THREAD_PRIORITY_HIGHEST,
            tpTimeCritical = THREAD_PRIORITY_TIME_CRITICAL
        #elif xOS_ENV_UNIX
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

#if   xOS_ENV_WIN
    typedef HANDLE    handle_t; ///< handle
    typedef DWORD     id_t;     ///< ID
#elif xOS_ENV_UNIX
    typedef pthread_t handle_t; ///< handle
    typedef pthread_t id_t;     ///< ID
#endif

    volatile long_t tag;    ///< tag

                    CxThread(cbool_t &isAutoDelete);
        ///< constructor
    // BUG: CxThread:: ~CxThread() - must pure virtual
    virtual        ~CxThread() /* = 0*/;
        ///< destructor

    // actions
    void_t          create(cbool_t &isPaused, cuint_t &stackSize, void_t *param);
        ///< start
    void_t          resume();
        ///< resume
    void_t          pause();
        ///< pause
    void_t          exit();
        ///< exit (set flag "exit")
    void_t          kill(culong_t &timeoutMsec);
        ///< kill
    void_t          wait(culong_t &timeoutMsec) const;
        ///< wait

    // flags
    bool_t          isCreated() const xWARN_UNUSED_RV;
        ///< is created
    bool_t          isRunning() const xWARN_UNUSED_RV;
        ///< is running
    bool_t          isPaused() xWARN_UNUSED_RV;
        ///< is paused
    bool_t          isExited() xWARN_UNUSED_RV;
        ///< is exited (is set flag "exit")

#if xOS_ENV_WIN
    // messages
    void_t          postMessage(HWND wnd, uint_t msg, uint_t param1, long_t param2) const;
        ///< post message from thread to window
    void_t          sendMessage(HWND wnd, uint_t msg, uint_t param1, long_t param2) const;
        ///< send message from thread to window
    void_t          postThreadMessage(uint_t msg, uint_t param1, long_t param2) const;
        ///< post message from thread to thread
    bool_t          tryPostThreadMessage(uint_t msg, uint_t param1, long_t param2,
                        ulong_t attempsNum, ulong_t attempTimeoutMsec) const xWARN_UNUSED_RV;
        ///< try post message from thread to thread
    void_t          messageWaitQueue(uint_t msg, uint_t *param1, long_t *param2) const;
        ///< waiting for message with params from other thread
    void_t          messageWaitQueue(const std::vector<uint_t> &msgs, uint_t *msg, uint_t *param1,
                        long_t *param2) const;
        ///< waiting for message with params from other thread
#endif

    // priority
    void_t          setPriority(const ExPriority &priority) const;
        ///< set priority (under Linux must use admin privilege)
    ExPriority      priority() const xWARN_UNUSED_RV;
        ///< get priority
    std::tstring_t  priorityString() const xWARN_UNUSED_RV;
        ///< get priority as string
    void_t          priorityUp() const;
        ///< increase priority on one level
    void_t          priorityDown() const;
        ///< decrease priority on one level
    bool_t          isPriorityBoost() const xWARN_UNUSED_RV;
        ///< get priority boost control state
    void_t          setPriorityBoost(cbool_t &isEnabled) const;
        ///< disables/enables the ability of the system to temporarily boost the priority of a thread

    // CPU
    void_t          setCpuAffinity(cint_t &procNum) const;
        ///< set processor affinity
    void_t          setCpuIdeal(culong_t &idealCpu) const;
        ///< sets preferred processor for a thread
    ulong_t         cpuIdeal() const xWARN_UNUSED_RV;
        ///< get current ideal processor without changing it
    static
    ulong_t         cpuCount() xWARN_UNUSED_RV;
        ///< get CPU count on machine

    // other
    handle_t        handle() const xWARN_UNUSED_RV;
        ///< get handle
    id_t            id() const xWARN_UNUSED_RV;
        ///< get ID
    bool_t          isCurrent() const xWARN_UNUSED_RV;
        ///< is current
    ulong_t         exitStatus() const xWARN_UNUSED_RV;
        ///< get termination status
    void_t          setDebugName(std::ctstring_t &name) const;
        ///< set name your threads in the debugger thread list

    // static
    static
    handle_t        open(culong_t &access, cbool_t &isInheritHandle, culong_t &id) xWARN_UNUSED_RV;
        ///< opens an existing thread object

    // current thread
    static
    bool_t          isCurrent(const CxThread::id_t &id) xWARN_UNUSED_RV;
        ///< is current id
    static
    id_t            currentId() xWARN_UNUSED_RV;
        ///< get the thread identifier of the calling thread
    static
    handle_t        currentHandle() xWARN_UNUSED_RV;
        ///< get pseudo handle for the calling thread
    static
    void_t          currentYield();
        ///< yield
    static
    void_t          currentSleep(culong_t &timeoutMsec);
        ///< sleep

protected:
    // events
    // BUG: CxThread::onRun() - must pure virtual
    virtual uint_t  onRun               (void_t *param) /* = 0 */ xWARN_UNUSED_RV;
        ///< work thread function, must be override
    //--virtual void_t    vOnEnter              ();
    //--virtual void_t    vOnExit               ();

    bool_t          isTimeToExit() xWARN_UNUSED_RV;
        ///< is need to exit from work thread function

private:
    // constants
    static
    culong_t        _s_stillActiveTimeout = 2UL;
        ///< still active timeout (msec)
    static
    culong_t        _s_exitTimeout = 5000UL;
        ///< exit timeout (msec)

    // thread data
#if   xOS_ENV_WIN
    CxHandle        _thread;                 ///< native handle
#elif xOS_ENV_UNIX
    handle_t        _thread;                 ///< native handle
#endif

    id_t            _id;                    ///< ID
    uint_t          _exitStatus;            ///< exit code
    void_t         *_param;                 ///< param for job function
    cbool_t         _isAutoDelete;          ///< is auto delete thread object

    struct State
        ///< thread state flags
    {
        bool_t isCreated;  ///< is created
        bool_t isRunning;  ///< is running

        State() : isCreated(false), isRunning(false) {}
    } _state;

    // other
    CxEvent        *_eventStarter;              ///< starter event
    CxEvent         _eventPause;                 ///< pause event
    CxEvent         _eventExit;                  ///< exit event

#if   xOS_ENV_WIN
    typedef uint_t   exit_status_t;
#elif xOS_ENV_UNIX
    typedef void_t * exit_status_t;
#endif

    static
    exit_status_t xSTDCALL _s_jobEntry(void_t *param) xWARN_UNUSED_RV;
        ///< callback
    bool_t          _waitResumption() xWARN_UNUSED_RV;
        ///< waiting for reset pause
    void_t          _setStatesDefault();
        ///< set states as default

    // static
    static
    int_t           _priorityMin();
        ///<
    static
    int_t           _priorityMax();
        ///<

    xNO_COPY_ASSIGN(CxThread)
};

xNAMESPACE2_END(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxThread.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxThreadH
