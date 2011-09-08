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
#include <xLib/Log/xLogs.h>

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

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
            #if defined(xOS_WIN)
                tpError        = THREAD_PRIORITY_ERROR_RETURN,
                tpIdle         = THREAD_PRIORITY_IDLE,
                tpLowest       = THREAD_PRIORITY_LOWEST,
                tpBelowNormal  = THREAD_PRIORITY_BELOW_NORMAL,
                tpNormal       = THREAD_PRIORITY_NORMAL,
                tpAboveNormal  = THREAD_PRIORITY_ABOVE_NORMAL,
                tpHighest      = THREAD_PRIORITY_HIGHEST,
                tpTimeCritical = THREAD_PRIORITY_TIME_CRITICAL
            #elif defined(xOS_LINUX)
                tpError        = - 1,
                tpIdle,
                tpLowest,
                tpBelowNormal,
                tpNormal,
                tpAboveNormal,
                tpHighest,
                tpTimeCritical
            #endif
	    };

    #if defined(xOS_WIN)
        typedef HANDLE    TxHandle; ///< handle
        typedef DWORD     TxId;     ///< ID
    #elif defined(xOS_LINUX)
        typedef pthread_t TxHandle; ///< handle
        typedef pthread_t TxId;     ///< ID
    #endif

        volatile LONG             m_ulTag;    ///< tag

                                  CxThread              (const BOOL cbAutoDelete);
            ///< constructor
        virtual                  ~CxThread              () = 0;
            ///< destructor

        //actions
        BOOL                      bCreate               (const BOOL cbIsPaused, const UINT cuiStackSize, VOID *pvParam);
            ///< start
        BOOL                      bResume               ();
            ///< resume
        BOOL                      bPause                ();
            ///< pause
        BOOL                      bExit                 (const ULONG culTimeout);
            ///< exit (set flag "exit")
        BOOL                      bKill                 (const ULONG culTimeout);
            ///< kill
        BOOL                      bWait                 (const ULONG culTimeout) const;
            ///< wait

        //flags
        BOOL                      bIsCreated            () const;
            ///< is created
        BOOL                      bIsRunning            () const;
            ///< is runnig
        BOOL                      bIsPaused             ();
            ///< is paused
        BOOL                      bIsExited             ();
            ///< is exited (is set flag "exit")

    #if defined(xOS_WIN)
        //messages
        BOOL                      bPostMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< post message from thread to window
        BOOL                      bSendMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< send message from thread to window
        BOOL                      bPostThreadMessage    (UINT uiMsg, UINT uiParam1, LONG liParam2) const;
            ///< post message from thread to thread
        BOOL                      bTryPostThreadMessage (UINT uiMsg, UINT uiParam1, LONG liParam2, ULONG ulAttemps, ULONG ulAttempTimeout) const;
            ///< try post message from thread to thread
        BOOL                      bMessageWaitQueue     (UINT uiMsg, UINT *puiParam1, LONG *pliParam2) const;
            ///< waiting for message with params from other thread
        BOOL                      bMessageWaitQueue     (const std::vector<UINT> &cvecuiMsg, UINT *puiMsg, UINT *puiParam1, LONG *pliParam2) const;
            ///< waiting for message with params from other thread
    #endif

        //priority
        BOOL                      bSetPriority          (const EPriority ctpPriority) const;
            ///< set priority
        EPriority                 tpGetPriority         () const;
            ///< get priotity
        std::tstring              sGetPriorityString    () const;
            ///< get priority as string
        BOOL                      bPriorityUp           () const;
            ///< increase priority on one level
        BOOL                      bPriorityDown         () const;
            ///< decrease priority on one level
        BOOL                      bIsPriorityBoost      () const;
            ///< get priority boost control state of the specified thread
        BOOL                      bSetPriorityBoost     (const BOOL cbIsEnabled) const;
            ///< disables or enables the ability of the system to temporarily boost the priority of a thread

        //CPU
        BOOL                      bSetAffinityMask      (const INT ciProcNum) const;
            ///< set processor affinity mask
        BOOL                      bSetIdealCpu          (const ULONG culIdealCpu) const;
            ///< sets preferred processor for a thread
        ULONG                     ulGetIdealCpu         () const;
            ///< get current ideal processor without changing it
        static ULONG              ulGetCpuCount         ();
            ///< get CPU count on machine

        //other
        TxHandle                  hGet                  () const;
            ///< get handle
        TxId                      ulGetId               () const;
            ///< get ID
        BOOL                      bIsCurrent            () const;
            ///< is current
        ULONG                     ulGetExitCode         () const;
            ///< get termination status
        BOOL                      bSetDebugName         (const std::tstring &csName) const;
            ///< set name your threads in the debugger thread list

        //static
        static TxHandle           hOpen                 (const ULONG culAccess, const BOOL cbInheritHandle, const ULONG culId);
            ///< opens an existing thread object
        static TxId               ulGetCurrId           ();
            ///< get the thread identifier of the calling thread
        static BOOL               bIsCurrent            (const TxId culId);
            ///< is current id
        static TxHandle           hGetCurrHandle        ();
            ///< get pseudo handle for the calling thread
        ////static BOOL               bSetPriority          (const TxHandle chHandle, const EPriority ctpPriority);
            ///< set priority
        static BOOL               bYield                ();
            ///< yield
        static BOOL               bSleep                (const ULONG culMsec);
            ///< sleep

        //callbacks
        VOID                      vAttachHandler_OnEnter(SClosureT<VOID(CxThread *pthSender)> vCallback);
            ///<
        VOID                      vAttachHandler_OnExit (SClosureT<VOID(CxThread *pthSender)> vCallback);
            ///<

    protected:
        //events
        virtual UINT              uiOnRun               (VOID *pvParam) = 0;
            ///< work thread function, must be overrided
        //--virtual VOID          vOnEnter              ();
        //--virtual VOID          vOnExit               ();

        BOOL                      bIsTimeToExit         ();
            ///< is need to exit from work thread function

    private:
        mutable BOOL              _m_bRes;                    ///< for private use

        //constants
        const ULONG               _m_culStillActiveTimeout;   ///< still active timeout (msec)
        const ULONG               _m_culExitTimeout;          ///< exit timeout (msec)


        //thread data
    #if defined(xOS_WIN)
        CxHandle                  _m_hThread;                 ///< native handle
    #elif defined(xOS_LINUX)
        TxHandle                  _m_hThread;                 ///< native handle
    #endif

        TxId                      _m_ulId;                    ///< ID
        UINT                      _m_uiExitCode;              ///< exit code
        VOID                     *_m_pvParam;                 ///< param for work function
        const BOOL                _m_cbIsAutoDelete;          ///< is autodelete thread object

        //flags
        //TODO: make struct SFlags
        BOOL                      _m_bIsCreated;              ///< is created
        BOOL                      _m_bIsRunning;              ///< is running
        /*BOOL                    _m_bIsPaused;*/// n/a
        /*BOOL                    _m_bIsExited;*/// n/a

        //other
        CxEvent                   _m_evPause;                 ///< pause event
        CxEvent                  *_m_pevStarter;              ///< starter event
        CxEvent                   _m_evExit;                  ///< exit event
        //HANDLE                  _m_hParentHandle;           ///<
        //HANDLE                  _m_hParentId;               ///<

        CxTraceLog                _m_clLog;                   ///< trace log

    #if defined(xOS_WIN)
        typedef UINT    TExitCode;
    #elif defined(xOS_LINUX)
        typedef VOID *  TExitCode;
    #endif

        static TExitCode xSTDCALL _s_uiJobEntry     (VOID *pvParam);
            ///< callback
        BOOL                      _bWaitResumption  ();
            ///< waiting for reset pause
        VOID                      _vMembersClear    ();
            ///< clear all class members
        VOID                      _vSetStatesDefault();
            ///< set states as default
        BOOL                      _bSetDebugNameA   (const std::string &csName) const;
            ///< set name your threads in the debugger thread list (ansi)

        //callbacks
        SClosureT<VOID(CxThread *pthSender)> _m_vCallback_OnEnter;
        BOOL                                 _m_bFlag_OnEnter;

        SClosureT<VOID(CxThread *pthSender)> _m_vCallback_OnExit;
        BOOL                                 _m_bFlag_OnExit;

        VOID                      _vHandler_OnEnter(CxThread *pthSender);
        VOID                      _vHandler_OnExit (CxThread *pthSender);
};

////xNAMESPACE_END(NxLib);
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxThreadH


#if xTODO
    /*
    *    Info: Attaches a Thread Function
    *
    *    Used primarily for porting but can serve in developing generic thread objects
    */
    void Attach( LPTHREAD_START_ROUTINE lpThreadFunc ){
        m_pThreadFunc = lpThreadFunc;
    }

    /*
    *    Info: Detaches the Attached Thread Function
    *
    *    Detaches the Attached Thread Function, If any.
    *    by resetting the thread function pointer to EntryPoint1
    */
    void  Detach( void ){
        m_pThreadFunc = CThread::EntryPoint;
    }
#endif


#if xTODO
    __int64 CThread::GetThreadCpuTime(DWORD id) {
        int result = 0;
        __int64 TimeTotal = 0;
        FILETIME CreationTime;
        FILETIME ExitTime;
        FILETIME KernelTime;
        FILETIME UserTime;
        ULARGE_INTEGER temp;

        HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, id);

        if (hThread != NULL) {

        ::GetThreadTimes(hThread, &CreationTime, &ExitTime, &KernelTime, &UserTime);

        temp.HighPart = KernelTime.dwHighDateTime;
        temp.LowPart = KernelTime.dwLowDateTime;
        TimeTotal = (__int64)temp.QuadPart;

        temp.HighPart = UserTime.dwHighDateTime;
        temp.LowPart = UserTime.dwLowDateTime;
        TimeTotal += (__int64)temp.QuadPart;

        CloseHandle(hThread);

        }

        return TimeTotal;
    }
#endif


#if xTODO
    LPTHREADENTRY32
#endif


#if xTODO
    #include "uMailBrute.h"
    #include <tlhelp32.h>

    unsigned short int __fastcall
    usCountProcessThreads() {
        DWORD dwPID               = GetCurrentProcessId();
        HANDLE        pThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwPID);
        bool          bIsok       = false;
        THREADENTRY32 ThrdEntry;
        ThrdEntry.dwSize = sizeof(THREADENTRY32);
        bIsok = Thread32First(pThreadSnap, &ThrdEntry);
        unsigned short int usCountThreads = 0;

        while (bIsok) {
            if (ThrdEntry.th32OwnerProcessID == dwPID) {
                usCountThreads ++;
            }
            bIsok = Thread32Next(pThreadSnap, &ThrdEntry);
        }
        CloseHandle(pThreadSnap);

        return usCountThreads;
    }
#endif
