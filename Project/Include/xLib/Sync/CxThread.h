/**
 * \file  CxThread.h
 * \brief thread
 */


#ifndef xLib_Sync_CxThreadH
#define xLib_Sync_CxThreadH
//------------------------------------------------------------------------------
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

    volatile long_t      m_ulTag;    ///< tag

                         CxThread            (cbool_t &cbAutoDelete);
        ///< constructor
    virtual             ~CxThread            () /* BUG: = 0*/;
        ///< destructor

    // actions
    void                 create              (cbool_t &cbIsPaused, cuint_t &cuiStackSize, void *pvParam);
        ///< start
    void                 resume              ();
        ///< resume
    void                 pause               ();
        ///< pause
    void                 exit                ();
        ///< exit (set flag "exit")
    void                 kill                (culong_t &culTimeout);
        ///< kill
    void                 wait                (culong_t &culTimeout) const;
        ///< wait

    // flags
    bool_t                 isCreated           () const xWARN_UNUSED_RV;
        ///< is created
    bool_t                 isRunning           () const xWARN_UNUSED_RV;
        ///< is running
    bool_t                 isPaused            () xWARN_UNUSED_RV;
        ///< is paused
    bool_t                 isExited            () xWARN_UNUSED_RV;
        ///< is exited (is set flag "exit")

#if   xOS_ENV_WIN
    // messages
    void                 postMessage         (HWND hHwnd, uint_t uiMsg, uint_t uiParam1, long_t liParam2) const;
        ///< post message from thread to window
    void                 sendMessage         (HWND hHwnd, uint_t uiMsg, uint_t uiParam1, long_t liParam2) const;
        ///< send message from thread to window
    void                 postThreadMessage   (uint_t uiMsg, uint_t uiParam1, long_t liParam2) const;
        ///< post message from thread to thread
    bool_t                 tryPostThreadMessage(uint_t uiMsg, uint_t uiParam1, long_t liParam2, ulong_t ulAttemps, ulong_t ulAttempTimeout) const xWARN_UNUSED_RV;
        ///< try post message from thread to thread
    void                 messageWaitQueue    (uint_t uiMsg, uint_t *puiParam1, long_t *pliParam2) const;
        ///< waiting for message with params from other thread
    void                 messageWaitQueue    (const std::vector<uint_t> &cvuiMsg, uint_t *puiMsg, uint_t *puiParam1, long_t *pliParam2) const;
        ///< waiting for message with params from other thread
#endif

    // priority
    void                 setPriority         (const ExPriority &ctpPriority) const;
        ///< set priority (under Linux must use admin privilege)
    ExPriority           priority            () const xWARN_UNUSED_RV;
        ///< get priority
    std::tstring_t       priorityString      () const xWARN_UNUSED_RV;
        ///< get priority as string
    void                 priorityUp          () const;
        ///< increase priority on one level
    void                 priorityDown        () const;
        ///< decrease priority on one level
    bool_t                 isPriorityBoost     () const xWARN_UNUSED_RV;
        ///< get priority boost control state
    void                 setPriorityBoost    (cbool_t &cbIsEnabled) const;
        ///< disables or enables the ability of the system to temporarily boost the priority of a thread

    // CPU
    void                 setCpuAffinity      (cint_t &ciProcNum) const;
        ///< set processor affinity
    void                 setCpuIdeal         (culong_t &culIdealCpu) const;
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
    bool_t                 isCurrent           () const xWARN_UNUSED_RV;
        ///< is current
    ulong_t              exitStatus          () const xWARN_UNUSED_RV;
        ///< get termination status
    void                 setDebugName        (const std::tstring_t &csName) const;
        ///< set name your threads in the debugger thread list

    // static
    static handle_t      open                (culong_t &culAccess, cbool_t &cbInheritHandle, culong_t &culId) xWARN_UNUSED_RV;
        ///< opens an existing thread object

protected:
    // events
    virtual uint_t       onRun               (void *pvParam) /* BUG: = 0 */ xWARN_UNUSED_RV;
        ///< work thread function, must be override
    //--virtual void    vOnEnter              ();
    //--virtual void    vOnExit               ();

    bool_t                 isTimeToExit        () xWARN_UNUSED_RV;
        ///< is need to exit from work thread function

private:
    // constants
    static culong_t _ms_culStillActiveTimeout = 2UL;    ///< still active timeout (msec)
    static culong_t _ms_culExitTimeout        = 5000UL; ///< exit timeout (msec)

    // thread data
#if   xOS_ENV_WIN
    CxHandle             _m_hThread;                 ///< native handle
#elif xOS_ENV_UNIX
    handle_t             _m_hThread;                 ///< native handle
#endif

    id_t                 _m_ulId;                    ///< ID
    uint_t               _m_uiExitStatus;            ///< exit code
    void                *_m_pvParam;                 ///< param for job function
    cbool_t           _m_cbIsAutoDelete;          ///< is auto delete thread object

    // flags
    //TODO: make struct SFlags
    bool_t                 _m_bIsCreated;              ///< is created
    bool_t                 _m_bIsRunning;              ///< is running
    /*bool_t               _m_bIsPaused;*/// n/a
    /*bool_t               _m_bIsExited;*/// n/a

    // other
    CxEvent             *_m_pevStarter;              ///< starter event
    CxEvent              _m_evPause;                 ///< pause event
    CxEvent              _m_evExit;                  ///< exit event

#if   xOS_ENV_WIN
    typedef uint_t       exit_status_t;
#elif xOS_ENV_UNIX
    typedef void *       exit_status_t;
#endif

    static exit_status_t xSTDCALL
                         _s_jobEntry         (void *pvParam) xWARN_UNUSED_RV;
        ///< callback
    bool_t                 _waitResumption     () xWARN_UNUSED_RV;
        ///< waiting for reset pause
    void                 _setStatesDefault   ();
        ///< set states as default

    // static
    static int_t           _priorityMin        ();
    static int_t           _priorityMax        ();
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxThreadH
