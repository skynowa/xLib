/**
 * \file  CxThread.h
 * \brief thread
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
#include <xLib/Sync/CxEvent.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxThread :
    public CxNonCopyable
    /// thread
{
public:
    enum ExPriority
        /// priotity
    {
        #if xOS_ENV_WIN
            tpError        = THREAD_PRIORITY_ERROR_RETURN,
            tpIdle         = THREAD_PRIORITY_IDLE,
            tpLowest       = THREAD_PRIORITY_LOWEST,
            tpBelowNormal  = THREAD_PRIORITY_BELOW_NORMAL,
            tpNormal       = THREAD_PRIORITY_NORMAL,
            tpAboveNormal  = THREAD_PRIORITY_ABOVE_NORMAL,
            tpHighest      = THREAD_PRIORITY_HIGHEST,
            tpTimeCritical = THREAD_PRIORITY_TIME_CRITICAL
        #else
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

#if xOS_ENV_WIN
    typedef HANDLE    handle_t; ///< handle
    typedef DWORD     id_t;     ///< ID
#else
    typedef pthread_t handle_t; ///< handle
    typedef pthread_t id_t;     ///< ID
#endif

    volatile long_t      m_ulTag;    ///< tag

                         CxThread            (cbool_t &cbAutoDelete);
        ///< constructor
    virtual             ~CxThread            () /* BUG: = 0*/;
        ///< destructor

    // actions
    void_t               create              (cbool_t &cbIsPaused, cuint_t &cuiStackSize, void_t *pvParam);
        ///< start
    void_t               resume              ();
        ///< resume
    void_t               pause               ();
        ///< pause
    void_t               exit                ();
        ///< exit (set flag "exit")
    void_t               kill                (culong_t &culTimeout);
        ///< kill
    void_t               wait                (culong_t &culTimeout) const;
        ///< wait

    // flags
    bool_t               isCreated           () const xWARN_UNUSED_RV;
        ///< is created
    bool_t               isRunning           () const xWARN_UNUSED_RV;
        ///< is running
    bool_t               isPaused            () xWARN_UNUSED_RV;
        ///< is paused
    bool_t               isExited            () xWARN_UNUSED_RV;
        ///< is exited (is set flag "exit")

#if xOS_ENV_WIN
    // messages
    void_t               postMessage         (HWND hHwnd, uint_t uiMsg, uint_t uiParam1, long_t liParam2) const;
        ///< post message from thread to window
    void_t               sendMessage         (HWND hHwnd, uint_t uiMsg, uint_t uiParam1, long_t liParam2) const;
        ///< send message from thread to window
    void_t               postThreadMessage   (uint_t uiMsg, uint_t uiParam1, long_t liParam2) const;
        ///< post message from thread to thread
    bool_t               tryPostThreadMessage(uint_t uiMsg, uint_t uiParam1, long_t liParam2, ulong_t ulAttemps, ulong_t ulAttempTimeout) const xWARN_UNUSED_RV;
        ///< try post message from thread to thread
    void_t               messageWaitQueue    (uint_t uiMsg, uint_t *puiParam1, long_t *pliParam2) const;
        ///< waiting for message with params from other thread
    void_t               messageWaitQueue    (const std::vector<uint_t> &cvuiMsg, uint_t *puiMsg, uint_t *puiParam1, long_t *pliParam2) const;
        ///< waiting for message with params from other thread
#endif

    // priority
    void_t               setPriority         (const ExPriority &ctpPriority) const;
        ///< set priority (under Linux must use admin privilege)
    ExPriority           priority            () const xWARN_UNUSED_RV;
        ///< get priority
    std::tstring_t       priorityString      () const xWARN_UNUSED_RV;
        ///< get priority as string
    void_t               priorityUp          () const;
        ///< increase priority on one level
    void_t               priorityDown        () const;
        ///< decrease priority on one level
    bool_t               isPriorityBoost     () const xWARN_UNUSED_RV;
        ///< get priority boost control state
    void_t               setPriorityBoost    (cbool_t &cbIsEnabled) const;
        ///< disables or enables the ability of the system to temporarily boost the priority of a thread

    // CPU
    void_t               setCpuAffinity      (cint_t &ciProcNum) const;
        ///< set processor affinity
    void_t               setCpuIdeal         (culong_t &culIdealCpu) const;
        ///< sets preferred processor for a thread
    ulong_t              cpuIdeal            () const xWARN_UNUSED_RV;
        ///< get current ideal processor without changing it
    static ulong_t       cpuCount            () xWARN_UNUSED_RV;
        ///< get CPU count on machine

    // other
    handle_t             handle              () const xWARN_UNUSED_RV;
        ///< get handle
    id_t                 id                  () const xWARN_UNUSED_RV;
        ///< get ID
    bool_t               isCurrent           () const xWARN_UNUSED_RV;
        ///< is current
    ulong_t              exitStatus          () const xWARN_UNUSED_RV;
        ///< get termination status
    void_t               setDebugName        (std::ctstring_t &csName) const;
        ///< set name your threads in the debugger thread list

    // static
    static handle_t      open                (culong_t &culAccess, cbool_t &cbInheritHandle, culong_t &culId) xWARN_UNUSED_RV;
        ///< opens an existing thread object

protected:
    // events
    virtual uint_t       onRun               (void_t *pvParam) /* BUG: = 0 */ xWARN_UNUSED_RV;
        ///< work thread function, must be override
    //--virtual void_t    vOnEnter              ();
    //--virtual void_t    vOnExit               ();

    bool_t               isTimeToExit        () xWARN_UNUSED_RV;
        ///< is need to exit from work thread function

private:
    // constants
    static culong_t      _ms_culStillActiveTimeout = 2UL;    ///< still active timeout (msec)
    static culong_t      _ms_culExitTimeout        = 5000UL; ///< exit timeout (msec)

    // thread data
#if xOS_ENV_WIN
    CxHandle             _m_hThread;                 ///< native handle
#else
    handle_t             _m_hThread;                 ///< native handle
#endif

    id_t                 _m_ulId;                    ///< ID
    uint_t               _m_uiExitStatus;            ///< exit code
    void_t              *_m_pvParam;                 ///< param for job function
    cbool_t              _m_cbIsAutoDelete;          ///< is auto delete thread object

    // flags
    //TODO: make struct SFlags
    bool_t               _m_bIsCreated;              ///< is created
    bool_t               _m_bIsRunning;              ///< is running
    /*bool_t             _m_bIsPaused;*/// n/a
    /*bool_t             _m_bIsExited;*/// n/a

    // other
    CxEvent             *_m_pevStarter;              ///< starter event
    CxEvent              _m_evPause;                 ///< pause event
    CxEvent              _m_evExit;                  ///< exit event

#if xOS_ENV_WIN
    typedef uint_t       exit_status_t;
#else
    typedef void_t *     exit_status_t;
#endif

    static exit_status_t xSTDCALL
                         _s_jobEntry         (void_t *pvParam) xWARN_UNUSED_RV;
        ///< callback
    bool_t               _waitResumption     () xWARN_UNUSED_RV;
        ///< waiting for reset pause
    void_t               _setStatesDefault   ();
        ///< set states as default

    // static
    static int_t         _priorityMin        ();
    static int_t         _priorityMax        ();
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
