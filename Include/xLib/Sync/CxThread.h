/****************************************************************************
* Class name:  CxThread
* Description: thread
* File name:   CxThread.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     22.11.2009 13:59:34
*
*****************************************************************************/


#ifndef xLib_Sync_CxThreadH
#define xLib_Sync_CxThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/xClosure.h>
#include <xLib/Sync/CxEvent.h>
#include <xLib/Log/xLog.h>

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxThread :
    public CxNonCopyable
{
    public:
	    enum EPriority {
	        tpError        = THREAD_PRIORITY_ERROR_RETURN,
	        tpIdle         = THREAD_PRIORITY_IDLE,
	        tpLowest       = THREAD_PRIORITY_LOWEST,
	        tpBelowNormal  = THREAD_PRIORITY_BELOW_NORMAL,
	        tpNormal       = THREAD_PRIORITY_NORMAL,
	        tpAboveNormal  = THREAD_PRIORITY_ABOVE_NORMAL,
	        tpHighest      = THREAD_PRIORITY_HIGHEST,
	        tpTimeCritical = THREAD_PRIORITY_TIME_CRITICAL
	    };

        volatile LONG           m_ulTag;

                                CxThread              (const BOOL cbAutoDelete);
        virtual                ~CxThread              () = 0;

        //actions
        BOOL                    bCreate               (const BOOL cbIsPaused, const UINT cuiStackSize, VOID *pvParam);
        BOOL                    bResume               ();
        BOOL                    bPause                ();
        BOOL                    bExit                 (const ULONG culTimeout);
        BOOL                    bKill                 (const ULONG culTimeout);
        BOOL                    bWait                 (const ULONG culTimeout) const;

        //flags
        BOOL                    bIsCreated            () const;
        BOOL                    bIsRunning            () const;
        BOOL                    bIsPaused             () const;
        BOOL                    bIsExited             () const;

        //messages
        BOOL                    bPostMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
        BOOL                    bSendMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
        BOOL                    bPostThreadMessage    (UINT uiMsg, UINT uiParam1, LONG liParam2) const;
        BOOL                    bTryPostThreadMessage (UINT uiMsg, UINT uiParam1, LONG liParam2, ULONG ulAttemps, ULONG ulAttempTimeout) const;
        BOOL                    bMessageWaitQueue     (UINT uiMsg, UINT *puiParam1, LONG *pliParam2) const;
        BOOL                    bMessageWaitQueue     (const std::vector<UINT> &cvecuiMsg, UINT *puiMsg, UINT *puiParam1, LONG *pliParam2) const;

        //priority
        BOOL                    bSetPriority          (const EPriority ctpPriority) const;
        EPriority               tpGetPriority         () const;
        tString                 sGetPriorityString    () const;
        BOOL                    bPriorityUp           () const;
        BOOL                    bPriorityDown         () const;
        BOOL                    bIsPriorityBoost      () const;
        BOOL                    bSetPriorityBoost     (const BOOL cbIsEnabled) const;

        //CPU
        BOOL                    bSetAffinityMask      (DWORD_PTR pulMask) const;
        BOOL                    bSetIdealCPU          (const ULONG culIdealCPU) const;
        ULONG                   ulGetIdealCPU         () const;
        ULONG                   ulGetCPUCount         () const;    /*static ???*/

        //other
        HANDLE                  hGetHandle            () const;
        ULONG                   ulGetId               () const;
        ULONG                   ulGetExitCode         () const;
        BOOL                    bSetDebugName         (const tString &csName) const;
        //GetThreadLocale

        //static
        static HANDLE           hOpen                 (const ULONG culAccess, const BOOL cbInheritHandle, const ULONG culId);
        static ULONG            ulGetCurrId           ();
        static HANDLE           hGetCurrHandle        ();
        static BOOL             bYield                (); 
        static BOOL             bSleep                (const UINT cuiMsec);                   

        //callbacks
        VOID                    vAttachHandler_OnEnter(SClosureT<VOID(CxThread *pthSender)> vCallback);
        VOID                    vAttachHandler_OnExit (SClosureT<VOID(CxThread *pthSender)> vCallback);

    protected:
        //events
        virtual UINT            uiOnRun               (VOID *pvParam) = 0;
        //--virtual VOID        vOnEnter              ();
        //--virtual VOID        vOnExit               ();

        BOOL                    bIsTimeToExit         ();

    private:
        mutable BOOL            _m_bRes;

        //constants
        const ULONG             _m_culStillActiveTimeout;
        const ULONG             _m_culExitTimeout;

        //thread data
        CxHandle                _m_hThread;
        ULONG                   _m_ulID;
        UINT                    _m_uiExitCode;
        VOID                   *_m_pvParam;
        const BOOL              _m_cbIsAutoDelete;

        //flags
        BOOL                    _m_bIsCreated;
        BOOL                    _m_bIsRunning;
        /*BOOL                  _m_bIsPaused;*/// n/a
        /*BOOL                  _m_bIsExited;*///   n/a

        //other
        CxEvent                 _m_evPause;
        CxEvent                *_m_pevStarter;
        CxEvent                 _m_evExit;
        //HANDLE                _m_hParentHandle;
        //HANDLE                _m_hParentId;

        CxTraceLog              _m_clLog;

        static UINT WINAPI      _s_uiStartFunc    (VOID *pvParam);
        BOOL                    _bWaitResumption  ();
        VOID                    _vMembersClear    ();       //TODO: _vMembersClear
        VOID                    _vSetStatesDefault();
        BOOL                    _bSetDebugNameA   (const std::string &csName) const;

        //callbacks
        SClosureT<VOID(CxThread *pthSender)> _m_vCallback_OnEnter;
        BOOL                                 _m_bFlag_OnEnter;

        SClosureT<VOID(CxThread *pthSender)> _m_vCallback_OnExit;
        BOOL                                 _m_bFlag_OnExit;

        VOID                    _vHandler_OnEnter(CxThread *pthSender);
        VOID                    _vHandler_OnExit (CxThread *pthSender);
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxThreadH



/*
    *
    *    Info: Attaches a Thread Function
    *
    *    Used primarily for porting but can serve in developing generic thread objects
    *
    void Attach( LPTHREAD_START_ROUTINE lpThreadFunc ){
        m_pThreadFunc = lpThreadFunc;
    }

    *
    *    Info: Detaches the Attached Thread Function
    *
    *    Detaches the Attached Thread Function, If any.
    *    by resetting the thread function pointer to EntryPoint1
    *
    void  Detach( void ){
        m_pThreadFunc = CThread::EntryPoint;
    }
*/


/*
    static __int64 GetThreadCPUTime(DWORD id);

    __int64 CThread::GetThreadCPUTime(DWORD id)
    {
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

*/

/*
LPTHREADENTRY32
*/



/*
#include "uMailBrute.h"
#include <tlhelp32.h>

//---------------------------------------------------------------------------
unsigned short int __fastcall usCountProcessThreads() {
    DWORD dwPID               = GetCurrentProcessId();
    HANDLE        pThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwPID);  //������ � �������� ������
    bool          bIsok       = false;
    THREADENTRY32 ThrdEntry;                          //���������, ����������� �����
    ThrdEntry.dwSize = sizeof(THREADENTRY32);         //������ ������
    bIsok = Thread32First(pThreadSnap, &ThrdEntry);   //����� ������ �����
    unsigned short int usCountThreads = 0;            //� ������ �� ���� �������...
    while (bIsok) {
        if (ThrdEntry.th32OwnerProcessID == dwPID) {    //���������, ���� �� �������� ����������� �����
            usCountThreads ++;
        }
        bIsok = Thread32Next(pThreadSnap, &ThrdEntry);
    }
    CloseHandle(pThreadSnap);                         //�� �������� ������� ������
    return usCountThreads;
}
//---------------------------------------------------------------------------
*/
