/**
 * \file  CxThread.h
 * \brief thread
 */


#ifndef xLib_Sync_CxThreadH
#define xLib_Sync_CxThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxEvent.h>

#if xOS_ENV_WIN
    #include <xLib/Common/Win/CxHandleT.h>
#endif
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxThread :
    public CxNonCopyable
    /// thread
{
    public:
        enum EPriority
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

    #if xOS_ENV_WIN
        typedef HANDLE    TxHandle; ///< handle
        typedef DWORD     TxId;     ///< ID
    #elif xOS_ENV_UNIX
        typedef pthread_t TxHandle; ///< handle
        typedef pthread_t TxId;     ///< ID
    #endif

        volatile LONG       m_ulTag;    ///< tag

                            CxThread              (const bool cbAutoDelete);
            ///< constructor
        virtual            ~CxThread              () = 0;
            ///< destructor

        //actions
        bool                bCreate               (const bool cbIsPaused, const UINT cuiStackSize, void *pvParam);
            ///< start
        bool                bResume               ();
            ///< resume
        bool                bPause                ();
            ///< pause
        bool                bExit                 ();
            ///< exit (set flag "exit")
        bool                bKill                 (const ULONG culTimeout);
            ///< kill
        bool                bWait                 (const ULONG culTimeout) const;
            ///< wait

        //flags
        bool                bIsCreated            () const;
            ///< is created
        bool                bIsRunning            () const;
            ///< is runnig
        bool                bIsPaused             ();
            ///< is paused
        bool                bIsExited             ();
            ///< is exited (is set flag "exit")

    #if xOS_ENV_WIN
        //messages
        bool                bPostMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< post message from thread to window
        bool                bSendMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< send message from thread to window
        bool                bPostThreadMessage    (UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< post message from thread to thread
        bool                bTryPostThreadMessage (UINT uiMsg, UINT uiParam1, LONG liParam2, ULONG ulAttemps, ULONG ulAttempTimeout) const;
            ///< try post message from thread to thread
        bool                bMessageWaitQueue     (UINT uiMsg, UINT *puiParam1, LONG *pliParam2) const;
            ///< waiting for message with params from other thread
        bool                bMessageWaitQueue     (const std::vector<UINT> &cvuiMsg, UINT *puiMsg, UINT *puiParam1, LONG *pliParam2) const;
            ///< waiting for message with params from other thread
    #endif

        //priority
        bool                bSetPriority          (const EPriority ctpPriority) const;
            ///< set priority (under Linux must use admin privilege)
        EPriority           tpGetPriority         () const;
            ///< get priotity
        std::tstring        sGetPriorityString    () const;
            ///< get priority as string
        bool                bPriorityUp           () const;
            ///< increase priority on one level
        bool                bPriorityDown         () const;
            ///< decrease priority on one level
        bool                bIsPriorityBoost      () const;
            ///< get priority boost control state
        bool                bSetPriorityBoost     (const bool cbIsEnabled) const;
            ///< disables or enables the ability of the system to temporarily boost the priority of a thread

        //CPU
        bool                bSetCpuAffinity       (const int ciProcNum) const;
            ///< set processor affinity
        bool                bSetCpuIdeal          (const ULONG culIdealCpu) const;
            ///< sets preferred processor for a thread
        ULONG               ulGetCpuIdeal         () const;
            ///< get current ideal processor without changing it
        static ULONG        ulGetCpuCount         ();
            ///< get CPU count on machine

        //other
        TxHandle            hGet                  () const;
            ///< get handle
        TxId                ulGetId               () const;
            ///< get ID
        bool                bIsCurrent            () const;
            ///< is current
        ULONG               ulGetExitStatus       () const;
            ///< get termination status
        bool                bSetDebugName         (const std::tstring &csName) const;
            ///< set name your threads in the debugger thread list

        //static
        static TxHandle     hOpen                 (const ULONG culAccess, const bool cbInheritHandle, const ULONG culId);
            ///< opens an existing thread object

    protected:
        //events
        virtual UINT        uiOnRun               (void *pvParam) = 0;
            ///< work thread function, must be overrided
        //--virtual void    vOnEnter              ();
        //--virtual void    vOnExit               ();

        bool                bIsTimeToExit         ();
            ///< is need to exit from work thread function

    private:
        //constants
        static const ULONG  _ms_culStillActiveTimeout = 2UL;    ///< still active timeout (msec)
        static const ULONG  _ms_culExitTimeout        = 5000UL; ///< exit timeout (msec)


        //thread data
    #if xOS_ENV_WIN
        CxHandle            _m_hThread;                 ///< native handle
    #elif xOS_ENV_UNIX
        TxHandle            _m_hThread;                 ///< native handle
    #endif

        TxId                _m_ulId;                    ///< ID
        UINT                _m_uiExitStatus;            ///< exit code
        void               *_m_pvParam;                 ///< param for job function
        const bool          _m_cbIsAutoDelete;          ///< is autodelete thread object

        //flags
        //TODO: make struct SFlags
        bool                _m_bIsCreated;              ///< is created
        bool                _m_bIsRunning;              ///< is running
        /*bool              _m_bIsPaused;*/// n/a
        /*bool              _m_bIsExited;*/// n/a

        //other
        CxEvent            *_m_pevStarter;              ///< starter event
        CxEvent             _m_evPause;                 ///< pause event
        CxEvent             _m_evExit;                  ///< exit event

    #if xOS_ENV_WIN
        typedef UINT     TxExitStatus;
    #elif xOS_ENV_UNIX
        typedef void *   TxExitStatus;
    #endif

        static TxExitStatus xSTDCALL
                            _s_uiJobEntry     (void *pvParam);
            ///< callback
        bool                _bWaitResumption  ();
            ///< waiting for reset pause
        void                _vSetStatesDefault();
            ///< set states as default

        //static
        static int          _iGetPriorityMin ();
        static int          _iGetPriorityMax ();
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxThreadH
