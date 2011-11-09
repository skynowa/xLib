/**
 * \file  CxThread.h
 * \brief thread
 */


#ifndef xLib_Sync_CxThreadH
#define xLib_Sync_CxThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/xClosure.h>
#include <xLib/Sync/CxEvent.h>

#if defined(xOS_ENV_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#endif
//---------------------------------------------------------------------------
////xNAMESPACE_BEGIN(NxLib)

class CxThread :
    public CxNonCopyable
    /// thread
{
    public:
        enum EPriority
            /// priotity
        {
            #if defined(xOS_ENV_WIN)
                tpError        = THREAD_PRIORITY_ERROR_RETURN,
                tpIdle         = THREAD_PRIORITY_IDLE,
                tpLowest       = THREAD_PRIORITY_LOWEST,
                tpBelowNormal  = THREAD_PRIORITY_BELOW_NORMAL,
                tpNormal       = THREAD_PRIORITY_NORMAL,
                tpAboveNormal  = THREAD_PRIORITY_ABOVE_NORMAL,
                tpHighest      = THREAD_PRIORITY_HIGHEST,
                tpTimeCritical = THREAD_PRIORITY_TIME_CRITICAL
            #elif defined(xOS_ENV_UNIX)
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

    #if defined(xOS_ENV_WIN)
        typedef HANDLE    TxHandle; ///< handle
        typedef DWORD     TxId;     ///< ID
    #elif defined(xOS_ENV_UNIX)
        typedef pthread_t TxHandle; ///< handle
        typedef pthread_t TxId;     ///< ID
    #endif

        volatile LONG       m_ulTag;    ///< tag

                            CxThread              (const BOOL cbAutoDelete);
            ///< constructor
        virtual            ~CxThread              () = 0;
            ///< destructor

        //actions
        BOOL                bCreate               (const BOOL cbIsPaused, const UINT cuiStackSize, void *pvParam);
            ///< start
        BOOL                bResume               ();
            ///< resume
        BOOL                bPause                ();
            ///< pause
        BOOL                bExit                 ();
            ///< exit (set flag "exit")
        BOOL                bKill                 (const ULONG culTimeout);
            ///< kill
        BOOL                bWait                 (const ULONG culTimeout) const;
            ///< wait

        //flags
        BOOL                bIsCreated            () const;
            ///< is created
        BOOL                bIsRunning            () const;
            ///< is runnig
        BOOL                bIsPaused             ();
            ///< is paused
        BOOL                bIsExited             ();
            ///< is exited (is set flag "exit")

    #if defined(xOS_ENV_WIN)
        //messages
        BOOL                bPostMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< post message from thread to window
        BOOL                bSendMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< send message from thread to window
        BOOL                bPostThreadMessage    (UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< post message from thread to thread
        BOOL                bTryPostThreadMessage (UINT uiMsg, UINT uiParam1, LONG liParam2, ULONG ulAttemps, ULONG ulAttempTimeout) const;
            ///< try post message from thread to thread
        BOOL                bMessageWaitQueue     (UINT uiMsg, UINT *puiParam1, LONG *pliParam2) const;
            ///< waiting for message with params from other thread
        BOOL                bMessageWaitQueue     (const std::vector<UINT> &cvuiMsg, UINT *puiMsg, UINT *puiParam1, LONG *pliParam2) const;
            ///< waiting for message with params from other thread
    #endif

        //priority
        BOOL                bSetPriority          (const EPriority ctpPriority) const;
            ///< set priority (under Linux must use admin privilege)
        EPriority           tpGetPriority         () const;
            ///< get priotity
        std::string_t        sGetPriorityString    () const;
            ///< get priority as string
        BOOL                bPriorityUp           () const;
            ///< increase priority on one level
        BOOL                bPriorityDown         () const;
            ///< decrease priority on one level
        BOOL                bIsPriorityBoost      () const;
            ///< get priority boost control state
        BOOL                bSetPriorityBoost     (const BOOL cbIsEnabled) const;
            ///< disables or enables the ability of the system to temporarily boost the priority of a thread

        //CPU
        BOOL                bSetCpuAffinity       (const int ciProcNum) const;
            ///< set processor affinity
        BOOL                bSetCpuIdeal          (const ULONG culIdealCpu) const;
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
        BOOL                bIsCurrent            () const;
            ///< is current
        ULONG               ulGetExitStatus       () const;
            ///< get termination status
        BOOL                bSetDebugName         (const std::string_t &csName) const;
            ///< set name your threads in the debugger thread list

        //static
        static TxHandle     hOpen                 (const ULONG culAccess, const BOOL cbInheritHandle, const ULONG culId);
            ///< opens an existing thread object

        //callbacks
        void                vAttachHandler_OnEnter(SClosureT<void(CxThread *pthSender)> vCallback);
            ///<
        void                vAttachHandler_OnExit (SClosureT<void(CxThread *pthSender)> vCallback);
            ///<

    protected:
        //events
        virtual UINT        uiOnRun               (void *pvParam) = 0;
            ///< work thread function, must be overrided
        //--virtual void    vOnEnter              ();
        //--virtual void    vOnExit               ();

        BOOL                bIsTimeToExit         ();
            ///< is need to exit from work thread function

    private:
        //constants
        static const ULONG  _ms_culStillActiveTimeout = 2UL;    ///< still active timeout (msec)
        static const ULONG  _ms_culExitTimeout        = 5000UL; ///< exit timeout (msec)


        //thread data
    #if defined(xOS_ENV_WIN)
        CxHandle            _m_hThread;                 ///< native handle
    #elif defined(xOS_ENV_UNIX)
        TxHandle            _m_hThread;                 ///< native handle
    #endif

        TxId                _m_ulId;                    ///< ID
        UINT                _m_uiExitStatus;            ///< exit code
        void               *_m_pvParam;                 ///< param for job function
        const BOOL          _m_cbIsAutoDelete;          ///< is autodelete thread object

        //flags
        //TODO: make struct SFlags
        BOOL                _m_bIsCreated;              ///< is created
        BOOL                _m_bIsRunning;              ///< is running
        /*BOOL              _m_bIsPaused;*/// n/a
        /*BOOL              _m_bIsExited;*/// n/a

        //other
        CxEvent            *_m_pevStarter;              ///< starter event
        CxEvent             _m_evPause;                 ///< pause event
        CxEvent             _m_evExit;                  ///< exit event

    #if defined(xOS_ENV_WIN)
        typedef UINT     TxExitStatus;
    #elif defined(xOS_ENV_UNIX)
        typedef void *   TxExitStatus;
    #endif

        static TxExitStatus xSTDCALL
                            _s_uiJobEntry     (void *pvParam);
            ///< callback
        BOOL                _bWaitResumption  ();
            ///< waiting for reset pause
        void                _vSetStatesDefault();
            ///< set states as default

        //callbacks
        SClosureT<void(CxThread *pthSender)> _m_vCallback_OnEnter;
        BOOL                                 _m_bFlag_OnEnter;

        SClosureT<void(CxThread *pthSender)> _m_vCallback_OnExit;
        BOOL                                 _m_bFlag_OnExit;

        void                _vHandler_OnEnter(CxThread *pthSender);
        void                _vHandler_OnExit (CxThread *pthSender);

        //static
        static int          _iGetPriorityMin ();
        static int          _iGetPriorityMax ();
};

////xNAMESPACE_END(NxLib);
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxThreadH
