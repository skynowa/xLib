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
#include <xLib/Common/Win/CxHandle.h>
#include <xLib/Sync/CxEvent.h>
#include <xLib/Sync/CxSleeper.h>
#include <xLib/Log/xLog.h>
//---------------------------------------------------------------------------
class CxThread : public CxNonCopyable {
    public:
        enum EPriority {
            tpPRIORITY_ERROR         = THREAD_PRIORITY_ERROR_RETURN,
            tpPRIORITY_IDLE          = THREAD_PRIORITY_IDLE,
            tpPRIORITY_LOWEST        = THREAD_PRIORITY_LOWEST,
            tpPRIORITY_BELOW_NORMAL  = THREAD_PRIORITY_BELOW_NORMAL,
            tpPRIORITY_NORMAL        = THREAD_PRIORITY_NORMAL,
            tpPRIORITY_ABOVE_NORMAL  = THREAD_PRIORITY_ABOVE_NORMAL,
            tpPRIORITY_HIGHEST       = THREAD_PRIORITY_HIGHEST,
            tpPRIORITY_TIME_CRITICAL = THREAD_PRIORITY_TIME_CRITICAL
        };

    private:
        mutable BOOL            _m_bRes;

        //constants
        const ULONG             _m_culStillActiveTimeout;   //таймаут проверки активности
        const ULONG             _m_culExitTimeout;          //таймаут выхода / уничтожения

        //thread data
        CxHandle                _m_hThread;                 //хендл
        ULONG                   _m_ulID;                    //ID
        UINT                    _m_uiExitCode;              //код возврата
        VOID                   *_m_pvParam;                 //параметр для раьочей функции
        const BOOL              _m_cbIsAutoDelete;          //флаг самоудаления

        //flags
        BOOL                    _m_bIsCreated;              //флаг создания
        BOOL                    _m_bIsRunning;              //флаг активности
        BOOL                    _m_bIsPaused;               //флаг паузы
        /*BOOL                  _m_bIsSleeping;*/// n/a     //флаг сна
        /*BOOL                  _m_bIsExited;*///   n/a     //флаг выхода

        //other
        CxEvent                 _m_evPause;                 //события для паузы
        CxEvent                *_m_pevStarter;              //события для корректного запуска потока
        CxSleeper               _m_slSleeper;               //слипер
        CxEvent                 _m_evExit;                  //события для выхода
        //HANDLE                _m_hParentHandle;
        //HANDLE                _m_hParentId;

        CxTraceLog                _m_clLog;                 //лог

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

    public:
        volatile LONG           m_ulTag;

                                CxThread              (BOOL bIsPaused, BOOL bAutoDelete);
        virtual                ~CxThread              () = 0;

        //actions
        BOOL                    bCreate               (UINT uiStackSize, VOID *pvParam);
        BOOL                    bResume               ();
        BOOL                    bPause                ();
        BOOL                    bExit                 (ULONG ulTimeout);
        BOOL                    bKill                 (ULONG ulTimeout);
        BOOL                    bWait                 (ULONG ulTimeout) const;

        //flags
        BOOL                    bIsCreated            () const;
        BOOL                    bIsRunning            () const;
        BOOL                    bIsPaused             () const;
        BOOL                    bIsSleeping           () const;
        BOOL                    bIsExited             () const;

        //messages
        BOOL                    bPostMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
        BOOL                    bSendMessage          (HWND hHwnd, UINT uiMsg, UINT uiParam1, LONG liParam2) const;
        BOOL                    bPostThreadMessage    (UINT uiMsg, UINT uiParam1, LONG liParam2) const;
        BOOL                    bTryPostThreadMessage (UINT uiMsg, UINT uiParam1, LONG liParam2, ULONG ulAttemps, ULONG ulAttempTimeout) const;
        BOOL                    bMessageWaitQueue     (UINT uiMsg, UINT *puiParam1, LONG *pliParam2) const;
        BOOL                    bMessageWaitQueue     (const std::vector<UINT> &cvecuiMsg, UINT *puiMsg, UINT *puiParam1, LONG *pliParam2) const;

        //priority
        BOOL                    bSetPriority          (EPriority tpPriority) const;
        EPriority               tpGetPriority         () const;
        tString                 sGetPriorityString    () const;
        BOOL                    bPriorityUp           () const;
        BOOL                    bPriorityDown         () const;
        BOOL                    bIsPriorityBoost      () const;
        BOOL                    bSetPriorityBoost     (BOOL bIsEnabled) const;

        //CPU
        BOOL                    bSetAffinityMask      (DWORD_PTR pulMask) const;
        BOOL                    bSetIdealCPU          (ULONG ulIdealCPU) const;
        ULONG                   ulGetIdealCPU         () const;
        ULONG                   ulGetCPUCount         () const;    /*static ???*/

        //other
        HANDLE                  hGetHandle            () const;
        ULONG                   ulGetId               () const;
        ULONG                   ulGetExitCode         () const;
        BOOL                    bSetDebugName         (const tString &csName) const;
        //GetThreadLocale

        //static
        static HANDLE           hOpen                 (ULONG ulAccess, BOOL bInheritHandle, ULONG ulId);
        static ULONG            ulGetCurrId           ();
        static HANDLE           hGetCurrHandle        ();

        //callbacks
        VOID                    vAttachHandler_OnEnter(SClosureT<VOID(CxThread *pthSender)> vCallback);
        VOID                    vAttachHandler_OnExit (SClosureT<VOID(CxThread *pthSender)> vCallback);

    protected:
        //events
        virtual UINT            uiOnRun               (VOID *pvParam) = 0;
        //--virtual VOID        vOnEnter              ();
        //--virtual VOID        vOnExit               ();

        BOOL                    bYield                () const;             /*static ???*/
        BOOL                    bSleep                (ULONG ulTimeout);    /*static ???*/
        BOOL                    bSleeperWakeUp        ();                   /*static ???*/

        BOOL                    bIsTimeToExit         ();
};
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
