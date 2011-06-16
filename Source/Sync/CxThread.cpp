/****************************************************************************
* Class name:  CxThread
* Description: thread
* File name:   CxThread.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     22.11.2009 13:59:34
*
*****************************************************************************/


#include <xLib/Sync/CxThread.h>

#include <xLib/Common/CxSystemInfo.h>

#if defined(xOS_WIN)
    #include <xLib/Gui/Win/Dialogs/CxMsgBoxT.h>
#elif defined(xOS_LINUX)

#endif

#if !defined(_MT)
    #define _MT
#endif

#if defined(_MT) || defined(_DLL)
    #include <process.h>
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxThread
CxThread::CxThread(
    BOOL bIsPaused,
    BOOL bIsAutoDelete
) :
    _m_bRes                 (FALSE),

    //consts
    _m_culStillActiveTimeout(2),
    _m_culExitTimeout       (5000),

    //data
    _m_hThread              (),
    _m_ulID                 (0),
    _m_uiExitCode           (0),
    _m_pvParam              (NULL),
    _m_cbIsAutoDelete       (bIsAutoDelete),

    //flags
    _m_bIsCreated           (FALSE),
    _m_bIsRunning           (FALSE),
    _m_bIsPaused            (bIsPaused/*TRUE == bIsPaused ? CREATE_SUSPENDED : 0*/),
    /*_m_bIsSleeping*/// n/a
    /*_m_bIsExited*///   n/a

    //
    ///_vOnExit             (NULL),

    //other
    _m_pevStarter           (NULL),
    _m_clLog                (FALSE),

    m_ulTag                 (0)
{
    ////this->hMainThread   = ::GetCurrentThread();
    ////this->hMainThreadId = ::GetCurrentThreadId();
}
//---------------------------------------------------------------------------
//DONE: ~CxThread
/*virtual*/
CxThread::~CxThread() {
    /*DEBUG*/

    //-------------------------------------
    //закрываем поток, если он активный - ??? typa na vsykiy sluchay???
    _m_bRes = bIsRunning();
    if (TRUE == _m_bRes) {
        _m_bRes = bExit(_m_culExitTimeout);
        if (FALSE == _m_bRes) {
            _m_bRes = bKill(_m_culExitTimeout);
        }
    }

    //-------------------------------------
    //флаги состояний потока
    _vSetStatesDefault();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: actions
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bCreate (creation)
BOOL
CxThread::bCreate(
    UINT  uiStackSize,
    VOID *pvParam
)
{
    /*DEBUG*/xASSERT_RET(FALSE == _m_hThread.bIsValid(), FALSE);
    /*DEBUG*///uiStackSize  - n/a
    /*DEBUG*///ptfStartAddr - n/a
    /*DEBUG*///pvParam      - n/a

    HANDLE hRes = NULL;

    _m_pvParam = pvParam;

    //-------------------------------------
    //_m_evStarter
    _m_pevStarter = new CxEvent();
    /*DEBUG*/xASSERT_RET(NULL != _m_pevStarter, FALSE);

    _m_bRes = _m_pevStarter->bCreate(NULL, TRUE, TRUE, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

#if defined(_MT)
    hRes = reinterpret_cast<HANDLE>( _beginthreadex(NULL, uiStackSize, _s_uiStartFunc, this, 0, (UINT *)&_m_ulID) );
#else
    hRes = ::CreateThread(NULL, uiStackSize, xreinterpret_cast<LPTHREAD_START_ROUTINE>(_s_uiStartFunc), this, 0, &_m_ulID);
#endif

    //-------------------------------------
    //WatchDog
    /*WatchDog*/ULONG ulLastError = CxLastError::ulGet();
    /*WatchDog*/xCHECK_DO(8 == ulLastError, CxMsgBoxT::iShow(CxLastError::sFormat(ulLastError), xT("WatchDog"), MB_OK); return FALSE);


    /*DEBUG*/xASSERT_RET(NULL != hRes,    FALSE);
    /*DEBUG*/xASSERT_RET(0    <  _m_ulID, FALSE);

    _m_hThread.bSet(hRes);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    //-------------------------------------
    //_m_evPause
    _m_bRes = _m_evPause.bCreate(NULL, FALSE, FALSE, NULL);      //_m_bIsPaused
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = _m_evExit.bCreate(NULL, FALSE, FALSE, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //flags
    _m_bIsCreated = TRUE;
    _m_bIsRunning = TRUE;
    /*_m_bIsPaused*///    n/a
    if (TRUE == _m_bIsPaused) {
        //set flag - "pause"
        _m_bRes = _m_evPause.bSet();
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }
    /*_m_bIsSleeping*///  n/a
    /*_m_bIsExited*///    n/a

    //-------------------------------------
    //спускай курок после инициализации
    _m_bRes = _m_pevStarter->bSet();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bResume (resumption)
BOOL
CxThread::bResume() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    _m_bRes = _m_evPause.bSet();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //flags
    /*_m_bIsCreated*///   n/a
    /*_m_bIsRunning*///   n/a
    /*_m_bIsPaused*///    n/a
    /*_m_bIsSleeping*///  n/a
    /*_m_bIsExited*///    n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bPause (pause)
BOOL
CxThread::bPause() {
    /*DEBUG*/xASSERT_MSG_RET(FALSE != _m_hThread.bIsValid(), CxString::lexical_cast(_m_hThread.hGet()).c_str(), FALSE);

    _m_bRes = _m_evPause.bReset();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //flags
    /*_m_bIsCreated*///   n/a
    /*_m_bIsRunning*///   n/a
    /*_m_bIsPaused*///    n/a
    /*_m_bIsSleeping*///  n/a
    /*_m_bIsExited*///    n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bExit (exit - set flag "exit")
BOOL
CxThread::bExit(
    ULONG ulTimeout
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*///ulTimeout - n/a

    _m_bRes = _m_evExit.bSet();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //flags
    /*_m_bIsExited*///   n/a
    /*_m_bIsCreated*///  n/a
    /*_m_bIsRunning*///  n/a
    /*_m_bIsPaused*/    xCHECK_DO(TRUE == bIsPaused(),   bResume()       ); //если поток приостановленный (bPause) - возобновляем
    /*_m_bIsSleeping*/    xCHECK_DO(TRUE == bIsSleeping(), bSleeperWakeUp());    //если поток спит             (bSleep) - будим
                                                                            //если ожидает чего-то
    //-------------------------------------
    //TODO: waiting oneself
    //--bRes = bWait(ulTimeout);
    //--/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bKill (killing)
BOOL
CxThread::bKill(
    ULONG ulTimeout
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*///ulTimeout - n/a

    ULONG ulRes = 0;

    _m_uiExitCode = 0;
    _m_bRes = ::TerminateThread(_m_hThread.hGet(), _m_uiExitCode);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    for (;;) {
        ulRes = ulGetExitCode();
        xCHECK_DO(STILL_ACTIVE != ulRes, break);

        _m_bRes = bSleep(_m_culStillActiveTimeout);
        /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, break);
    }

    //-------------------------------------
    //TODO: waiting oneself
    //--bRes = bWait(ulTimeout);
    //--/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //clening members
    _m_bRes = _m_hThread.bClose();
    /*DEBUG*/xASSERT(FALSE != _m_bRes);

    _m_ulID       = 0;
    _m_uiExitCode = ulRes;    //saving value
    _m_pvParam    = NULL;
    //_m_bIsAutoDelete - n/a

    //-------------------------------------
    //flags
    _vSetStatesDefault();

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bWait (waiting)
BOOL
CxThread::bWait(
    ULONG ulTimeout
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*///ulTimeout - n/a

    //-------------------------------------
    //flags
    //?????????

    /*DEBUG*/xASSERT(CxThread::ulGetCurrId() != _m_ulID);        //TODO: ?????
    xCHECK_RET(CxThread::ulGetCurrId() == _m_ulID, TRUE);        //TODO: ?????

    ULONG ulRes = WAIT_FAILED;
    ulRes = ::WaitForSingleObject(_m_hThread.hGet(), ulTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: flags
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsCreated (is created)
BOOL
CxThread::bIsCreated() const {
    /*DEBUG*/// _m_hThread - n/a

    return _m_bIsCreated && (FALSE != _m_hThread.bIsValid());
}
//---------------------------------------------------------------------------
//DONE: bIsRunning (is running)
BOOL
CxThread::bIsRunning() const {
    /*DEBUG*/// _m_hThread - n/a

    ULONG ulRes = 0;
    ::GetExitCodeThread(_m_hThread.hGet(), &ulRes);
    /*DEBUG*/// n/a

    BOOL bCond1 = ( FALSE         != _m_hThread.bIsValid()                       );
    BOOL bCond2 = ( 0L            <  _m_ulID                                     );
    BOOL bCond3 = ( TRUE          == _m_bIsRunning                               );
    BOOL bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_m_hThread.hGet(), 0) );
    BOOL bCond5 = ( STILL_ACTIVE  == ulRes                                       );

    _m_bRes = bCond1 && bCond2 && bCond3 && bCond4 && bCond5;

    return _m_bRes;
}
//---------------------------------------------------------------------------
//DONE: bIsPaused (is paused)
BOOL
CxThread::bIsPaused() const {
    /*DEBUG*/// _m_hThread - n/a

    return (FALSE == _m_evPause.bIsSignaled()) && (FALSE != _m_hThread.bIsValid());
    ////return !_m_evPause.bIsSignaled() && (FALSE != _m_hThread.bIsValid());
}
//---------------------------------------------------------------------------
//DONE: bIsSleeping (is sleeping)
BOOL
CxThread::bIsSleeping() const {
    /*DEBUG*/// _m_hThread - n/a

    return _m_slSleeper.bIsSleeping() && (FALSE != _m_hThread.bIsValid());
}
//---------------------------------------------------------------------------
//DONE: bIsExited (is set flag "exit")
BOOL
CxThread::bIsExited() const {
    /*DEBUG*/// _m_hThread - n/a

    return _m_evExit.bIsSignaled() && (FALSE != _m_hThread.bIsValid());
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: messages
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bPostMessage (send message from thread to window)
BOOL
CxThread::bPostMessage(
    HWND hHwnd,
    UINT uiMsg,
    UINT uiParam1,
    LONG liParam2
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != hHwnd,                 FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != ::IsWindow(hHwnd),     FALSE);

    _m_bRes = ::PostMessage(hHwnd, uiMsg, static_cast<WPARAM>(uiParam1), static_cast<LPARAM>(liParam2));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSendMessage (send message from thread to window)
BOOL
CxThread::bSendMessage(
    HWND hHwnd,
    UINT uiMsg,
    UINT uiParam1,
    LONG liParam2
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != hHwnd,                 FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != ::IsWindow(hHwnd),     FALSE);

    ::SendMessage(hHwnd, uiMsg, static_cast<WPARAM>(uiParam1), static_cast<LPARAM>(liParam2));
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(0 == ::GetLastError(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bPostThreadMessage (send message to thread)
BOOL
CxThread::bPostThreadMessage(
    UINT uiMsg,
    UINT uiParam1,
    LONG liParam2
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    _m_bRes = ::PostThreadMessage(ulGetId(), uiMsg, static_cast<WPARAM>(uiParam1), static_cast<LPARAM>(liParam2));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bTryPostThreadMessage (trying send message to thread)
BOOL
CxThread::bTryPostThreadMessage(
    UINT  uiMsg,
    UINT  uiParam1,
    LONG  liParam2,
    ULONG ulAttemps,
    ULONG ulAttempTimeout
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    for (ULONG i = 0; i < ulAttemps; ++ i) {
        _m_bRes = ::PostThreadMessage(ulGetId(), uiMsg, static_cast<WPARAM>(uiParam1), static_cast<LPARAM>(liParam2));

        xCHECK_RET(TRUE  == _m_bRes, TRUE);
        xCHECK_DO (FALSE == _m_bRes, ::Sleep(ulAttempTimeout));
    }

    return FALSE;
}
//---------------------------------------------------------------------------
//DONE: bMessageWaitQueue (waiting for message with params from other thread)
BOOL
CxThread::bMessageWaitQueue(
    UINT  uiMsg,
    UINT *puiParam1,
    LONG *pliParam2
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(0     <  uiMsg,                 FALSE);

    std::vector<UINT> vecuiMsg;
    vecuiMsg.push_back(uiMsg);

    _m_bRes = bMessageWaitQueue(vecuiMsg, NULL, puiParam1, pliParam2);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bMessageWaitQueue (waiting for message with params from other thread)
BOOL
CxThread::bMessageWaitQueue(
    const std::vector<UINT> &cvecuiMsg,
    UINT                    *puiMsg,
    UINT                    *puiParam1,
    LONG                    *pliParam2
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(false == cvecuiMsg.empty(),     FALSE);

    MSG msgMsg = {0};

    while ((_m_bRes = ::GetMessage(&msgMsg, NULL, 0, 0 ))) {
        /*DEBUG*/xASSERT_RET(- 1 != _m_bRes, FALSE);

        for (size_t i = 0; i < cvecuiMsg.size(); ++ i) {
            if (cvecuiMsg.at(i) == msgMsg.message) {

                xCHECK_DO(NULL != puiMsg,    *puiMsg    = msgMsg.message                  );
                xCHECK_DO(NULL != puiParam1, *puiParam1 = static_cast<UINT>(msgMsg.wParam));
                xCHECK_DO(NULL != pliParam2, *pliParam2 = static_cast<LONG>(msgMsg.lParam));

                return TRUE;
            }
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: priority
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bSetPriority (seeting priority)
BOOL
CxThread::bSetPriority(
    EPriority tpPriority
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    _m_bRes = ::SetThreadPriority(_m_hThread.hGet(), tpPriority);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: iGetPriority (get priotity)
CxThread::EPriority
CxThread::tpGetPriority() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), tpPRIORITY_ERROR);

    CxThread::EPriority tpRes = tpPRIORITY_ERROR;

    tpRes = static_cast<EPriority>(::GetThreadPriority(_m_hThread.hGet()));
    /*DEBUG*/xASSERT_RET(tpPRIORITY_ERROR != tpRes, tpPRIORITY_ERROR);

    return tpRes;
}
//---------------------------------------------------------------------------
//DONE: sGetPriorityString (get priority as string)
tString
CxThread::sGetPriorityString() const {
    /*DEBUG*/// n/a

    INT iRes = tpGetPriority();
    switch (iRes) {
        case tpPRIORITY_IDLE:           return xT("Idle");
        case tpPRIORITY_LOWEST:         return xT("Lowest");
        case tpPRIORITY_BELOW_NORMAL:   return xT("Below normal");
        case tpPRIORITY_NORMAL:         return xT("Normal");
        case tpPRIORITY_ABOVE_NORMAL:   return xT("Above normal");
        case tpPRIORITY_HIGHEST:        return xT("Highest");
        case tpPRIORITY_TIME_CRITICAL:	return xT("Time critical");
    }

    return xT("N/A");
}
//---------------------------------------------------------------------------
//DONE: bPriorityUp (increase priority on one level)
BOOL
CxThread::bPriorityUp() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    EPriority tpOldLevel  = tpPRIORITY_ERROR;
    EPriority tpiNewLevel = tpPRIORITY_ERROR;

    tpOldLevel = tpGetPriority();
    switch (tpOldLevel) {
        case tpPRIORITY_IDLE:           tpiNewLevel = tpPRIORITY_LOWEST;        break;
        case tpPRIORITY_LOWEST:         tpiNewLevel = tpPRIORITY_BELOW_NORMAL;  break;
        case tpPRIORITY_BELOW_NORMAL:   tpiNewLevel = tpPRIORITY_NORMAL;        break;
        case tpPRIORITY_NORMAL:         tpiNewLevel = tpPRIORITY_ABOVE_NORMAL;	break;
        case tpPRIORITY_ABOVE_NORMAL:   tpiNewLevel = tpPRIORITY_HIGHEST;       break;
        case tpPRIORITY_HIGHEST:        tpiNewLevel = tpPRIORITY_TIME_CRITICAL; break;
        case tpPRIORITY_TIME_CRITICAL:	return TRUE;                            break;

        default:            /*xASSERT*/xASSERT_RET(FALSE, tpPRIORITY_NORMAL);   break;
    }

    return bSetPriority(tpiNewLevel);
}
//---------------------------------------------------------------------------
//DONE: bPriorityDown (decrease priority on one level)
BOOL
CxThread::bPriorityDown() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    EPriority tpOldLevel  = tpPRIORITY_ERROR;
    EPriority tpiNewLevel = tpPRIORITY_ERROR;

    tpOldLevel = tpGetPriority();
    switch (tpOldLevel) {
        case tpPRIORITY_IDLE:           return TRUE;                            break;
        case tpPRIORITY_LOWEST:         tpiNewLevel = tpPRIORITY_IDLE;          break;
        case tpPRIORITY_BELOW_NORMAL:   tpiNewLevel = tpPRIORITY_LOWEST;        break;
        case tpPRIORITY_NORMAL:         tpiNewLevel = tpPRIORITY_BELOW_NORMAL;	break;
        case tpPRIORITY_ABOVE_NORMAL:   tpiNewLevel = tpPRIORITY_NORMAL;        break;
        case tpPRIORITY_HIGHEST:        tpiNewLevel = tpPRIORITY_ABOVE_NORMAL;  break;
        case tpPRIORITY_TIME_CRITICAL:	tpiNewLevel = tpPRIORITY_HIGHEST;       break;

        default:            /*xASSERT*/xASSERT_RET(FALSE, tpPRIORITY_NORMAL);   break;
    }

    return bSetPriority(tpiNewLevel);
}
//---------------------------------------------------------------------------
//DONE: bIsPriorityBoost (Retrieves the priority boost control state of the specified thread)
BOOL
CxThread::bIsPriorityBoost() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    BOOL bDisablePriorityBoost = TRUE;

    _m_bRes = ::GetThreadPriorityBoost(_m_hThread.hGet(), &bDisablePriorityBoost);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //bDisablePriorityBoost == TRUE  - dynamic boosting is disabled
    //bDisablePriorityBoost == FALSE - normal behavior

    return ! bDisablePriorityBoost;
}
//---------------------------------------------------------------------------
//DONE: bSetPriorityBoost (Disables or enables the ability of the system to temporarily boost the priority of a thread)
BOOL
CxThread::bSetPriorityBoost(
    BOOL bIsEnabled
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    _m_bRes = ::SetThreadPriorityBoost(_m_hThread.hGet(), ! bIsEnabled);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: CPU
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bSetAffinityMask (Sets a processor affinity mask for the specified thread)
BOOL
CxThread::bSetAffinityMask(
    DWORD_PTR pulMask
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    DWORD_PTR pulRes = 0;

    pulRes = ::SetThreadAffinityMask(_m_hThread.hGet(), pulMask);    //ERROR_INVALID_PARAMETER
    /*DEBUG*/xASSERT_RET(0 != pulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetIdealProcessor (Sets a preferred processor for a thread, ulIdealProcessor - this value is zero-based)
BOOL
CxThread::bSetIdealCPU(
    ULONG ulIdealCPU
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    ULONG ulRes = (ULONG) - 1;

    ulRes = ::SetThreadIdealProcessor(_m_hThread.hGet(), ulIdealCPU);
    /*DEBUG*/xASSERT_RET((ULONG) - 1 != ulRes, FALSE);

    //TODO: xASSERT_RET
    ///*DEBUG*/xASSERT_RET(ulIdealCPU != ulRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: ulGetIdealProcessor (current ideal processor without changing it)
ULONG
CxThread::ulGetIdealCPU() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), 0);

    ULONG ulRes = (ULONG) - 1;

    ulRes = ::SetThreadIdealProcessor(_m_hThread.hGet(), MAXIMUM_PROCESSORS);
    /*DEBUG*/xASSERT_RET((ULONG) - 1 != ulRes, FALSE);

    return ulRes;
}
//---------------------------------------------------------------------------
//DONE: ulGetCPUCount (CPU's number on machine)
ULONG
CxThread::ulGetCPUCount() const {
    /*DEBUG*///_m_hThread - n/a

    ULONG ulRes = 0;

    ulRes = CxSystemInfo::ulGetNumOfCPUs();
    xCHECK_RET(ulRes < 1 || ulRes > 32, 1);

    return ulRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: hGetHandle (get handle)
HANDLE
CxThread::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), NULL);

    return _m_hThread.hGet();
}
//---------------------------------------------------------------------------
//DONE: ulGetId (get id)
ULONG
CxThread::ulGetId() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), 0);

    return _m_ulID;
}
//---------------------------------------------------------------------------
//DONE: bGetExitCode (Retrieves the termination status of the specified thread)
ULONG
CxThread::ulGetExitCode() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), 0);

    ULONG ulRes = 0;

    _m_bRes = ::GetExitCodeThread(_m_hThread.hGet(), &ulRes);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, ulRes);

    return ulRes;
}
//---------------------------------------------------------------------------
//DONE: bSetDebugName (Name your threads in the VC debugger thread list)
BOOL
CxThread::bSetDebugName(
    const tString &csName
) const
{
    /*DEBUG*/

    //convert to Ansi
    std::string asName(csName.begin(), csName.end());

    _m_bRes = _bSetDebugNameA(asName);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: static
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: hOpen (Opens an existing thread object.)
/*static*/
HANDLE
CxThread::hOpen(
    ULONG ulAccess,
    BOOL  bInheritHandle,
    ULONG ulId
)
{
    /*DEBUG*///ulAccess       - n/a
    /*DEBUG*///bInheritHandle - n/a
    /*DEBUG*/xASSERT_RET(0 < ulId, NULL);

    HANDLE hRes = NULL;

    hRes = ::OpenThread(ulAccess, bInheritHandle, ulId);
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
//---------------------------------------------------------------------------
//DONE: ulGetCurrId (Retrieves the thread identifier of the calling thread.)
/*static*/
ULONG
CxThread::ulGetCurrId() {
    /*DEBUG*/// n/a

    ULONG ulRes = 0;

    ulRes = ::GetCurrentThreadId();
    /*DEBUG*/xASSERT_RET(0 < ulRes, 0);

    return ulRes;
}
//---------------------------------------------------------------------------
//DONE: hGetCurrHandle (Retrieves a pseudo handle for the calling thread)
/*static*/
HANDLE
CxThread::hGetCurrHandle() {
    /*DEBUG*/// n/a

    HANDLE hRes = NULL;

    hRes = ::GetCurrentThread();
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    return hRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: callbacks
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: vAttachHandler_OnEnter ()
VOID
CxThread::vAttachHandler_OnEnter(
    SClosureT<VOID(CxThread *pthSender)> vCallback
)
{
    _m_vCallback_OnEnter = vCallback;
    //_m_bFlag_OnEnter  = TRUE;
}
//---------------------------------------------------------------------------
//TODO: vDetachHandler_OnEnter ()
////VOID vDetachHandler_OnEnter(CxThread *pthSender) {
////    //_m_bFlag_OnEnter         = FALSE;
////    _m_Callback_OnEnter.p_this = NULL;
////}
//---------------------------------------------------------------------------
//DONE: vAttachHandler_OnExit ()
VOID
CxThread::vAttachHandler_OnExit(
    SClosureT<VOID(CxThread *pthSender)> vCallback
)
{
    _m_vCallback_OnExit = vCallback;
    //_m_bFlag_OnExit    = TRUE;
}
//---------------------------------------------------------------------------
//TODO: vDetachHandler_OnExit ()
////VOID vDetachHandler_OnExit(CxThread *pthSender) {
////    //_m_bFlag_OnExit         = FALSE;
////    _m_Callback_OnExit.p_this = NULL;
////}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected
*
*****************************************************************************/

/****************************************************************************
*    protected: events
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: uiOnRun (thread function)    //must override this
/*virtual*/
UINT
CxThread::uiOnRun(
    VOID *pvParam
) /* = 0*/
{
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(FALSE, 0);

    /*UINT uiRes = 0;

    for (;;) {
        //-------------------------------------
        //is time to exit from thread?
        bRes = bIsTimeToExit();
        xCHECK_DO(TRUE == bRes, break);

        //...
    }

    return uiRes;*/

    return 0;
}
//---------------------------------------------------------------------------
//DONE: vOnEnter (event about construction of thread)    //must override this
/*virtual*/
//--VOID
//--CxThread::vOnEnter() {
//--    /*DEBUG*/// n/a
//--    /*DEBUG*/xASSERT_DO(FALSE, return);
//--
//--    return;
//--}
//---------------------------------------------------------------------------
//DONE: vOnExit (event about destruction of thread)    //must override this
/*virtual*/
//--VOID
//--CxThread::vOnExit() {
//--    /*DEBUG*/// n/a
//--    /*DEBUG*/xASSERT_DO(FALSE, return);
//--
//--    return;
//--}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bYield (уступить ресурсы другому потоку, который готов к исполнению на !текущем процессоре!)
BOOL
CxThread::bYield() const {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    ::SwitchToThread();
    /*DEBUG*/// n/a

    //-------------------------------------
    //flags
    //n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSleep (Suspends the execution of the current thread until the time-out interval elapses)
BOOL
CxThread::bSleep(
    ULONG ulTimeout
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*///ulTimeout - n/a

    //-------------------------------------
    //flags
    /*_m_bIsCreated*///   n/a
    /*_m_bIsRunning*///   n/a
    /*_m_bIsPaused*///    n/a
    /*_m_bIsSleeping*///  n/a
    /*_m_bIsExited*///    n/a

    _m_bRes = _m_slSleeper.bSleep(ulTimeout);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //flags
    /*_m_bIsCreated*///   n/a
    /*_m_bIsRunning*///   n/a
    /*_m_bIsPaused*///    n/a
    /*_m_bIsSleeping*///  n/a
    /*_m_bIsExited*///    n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSleeperWakeUp (interrupting bSleep - wake up)
BOOL
CxThread::bSleeperWakeUp() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    _m_bRes = _m_slSleeper.bWakeUp();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //flags
    /*_m_bIsCreated*///   n/a
    /*_m_bIsRunning*///   n/a
    /*_m_bIsPaused*///    n/a
    /*_m_bIsSleeping*///  n/a
    /*_m_bIsExited*///    n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsTimeToExit (is need to exit from thread)
BOOL
CxThread::bIsTimeToExit() {
    /*DEBUG*/// n/a

    //-------------------------------------
    //exit
    ///bSleep(1);

    _m_bRes = bIsExited();
    xCHECK_RET(FALSE != _m_bRes, TRUE);

    //-------------------------------------
    //pause / resume
    ///bSleep(1);

    _m_bRes = bIsPaused();
    xCHECK_RET(FALSE != _m_bRes, !_bWaitResumption());

    //-------------------------------------
    //flags
    // n/a

    return FALSE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _s_uiStartFunc (callback)
/*static*/
UINT WINAPI
CxThread::_s_uiStartFunc(
    VOID *pvParam
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvParam, 0);

    UINT uiRes = 0;
    BOOL bRes  = FALSE;

    CxThread *pthThis = static_cast<CxThread *>(pvParam);
    /*DEBUG*/xASSERT_RET(NULL != pthThis, 0);

    //-------------------------------------
    //handle must be valid
    //::Sleep(5);
    bRes = pthThis->_m_pevStarter->bWait(/*+INFINITE*/10000);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    /*CxMacros::*/xPTR_DELETE(pthThis->_m_pevStarter);

    /*DEBUG*/xASSERT_RET(FALSE != pthThis->_m_hThread.bIsValid(), 0);

    //-------------------------------------
    //создан ли приостановленный поток?
    xCHECK_DO(TRUE == pthThis->bIsPaused(), pthThis->_bWaitResumption());

    {
        //-------------------------------------
        //begin of thread function
        try {
            //--pthThis->vOnEnter();
            pthThis->_vHandler_OnEnter(pthThis);
        }
        catch (...) {
            /*DEBUG*/xASSERT(FALSE);
        }
        /*DEBUG*/xASSERT_RET(FALSE != pthThis->_m_hThread.bIsValid(), 0);

        //-------------------------------------
        //executing of thread function
        try {
            uiRes = pthThis->uiOnRun(pthThis->_m_pvParam);
        }
        catch (std::exception &e) {
            std::string asWhat = e.what();
            xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());
        }
        catch (...) {
            /*DEBUG*/xASSERT(FALSE);
        }
        /*DEBUG*/xASSERT_RET(FALSE != pthThis->_m_hThread.bIsValid(), 0);

        //-------------------------------------
        //eind of thread function
        try {
            //--pthThis->vOnExit();
            pthThis->_vHandler_OnExit(pthThis);
        }
        catch (...) {
            /*DEBUG*/xASSERT(FALSE);
        }
        /*DEBUG*/xASSERT_RET(FALSE != pthThis->_m_hThread.bIsValid(), 0);
    }

    //-------------------------------------
    //clean members (is need to close???)
    bRes = pthThis->_m_hThread.bClose();
    /*DEBUG*/xASSERT(FALSE != bRes);

    pthThis->_m_ulID       = 0;
    pthThis->_m_uiExitCode = uiRes;    //???
    pthThis->_m_pvParam    = NULL;
    //pthThis->_m_bIsAutoDelete - n/a

    //-------------------------------------
    //flags
    pthThis->_vSetStatesDefault();

    //-------------------------------------
    //autodeleting oneself
    xCHECK_DO(TRUE == pthThis->_m_cbIsAutoDelete, /*CxMacros::*/xPTR_DELETE(pthThis));

    return uiRes;
}
//---------------------------------------------------------------------------
//DONE: _bWaitForResume (waiting for reset pause)
BOOL
CxThread::_bWaitResumption() {
    /*DEBUG*/

    ULONG ulRes = 0;

    //-------------------------------------
    //flags
    /*_m_bIsCreated*///   n/a
    /*_m_bIsRunning*///   n/a
    /*_m_bIsPaused*///    n/a
    /*_m_bIsSleeping*///  n/a
    /*_m_bIsExited*///    n/a

    ulRes = ::WaitForSingleObject(_m_evPause.hGetHandle(), INFINITE);
    /*DEBUG*///- n/a

    return TRUE;

    /*
    //a mechanism for terminating thread should be implemented
    //not allowing the method to be run from the main thread
    if (::GetCurrentThreadId () == this->hMainThreadId) {
        return 0;
    } else {
        ::MessageBoxW (0, xT("I'm running in a different thread!"), xT("CMyThread"), MB_OK);

        return 0;
    }
    */
}
//---------------------------------------------------------------------------
//DONE: _vSetStatesDefault ()
VOID
CxThread::_vSetStatesDefault() {
    /*DEBUG*/// n/a

    //-------------------------------------
    //flags
    _m_bIsCreated  = FALSE;
    _m_bIsRunning  = FALSE;
    /*_m_bIsPaused*///   n/a
    /*_m_bIsSleeping*/// n/a
    /*_m_bIsExited*///   n/a
}
//---------------------------------------------------------------------------
//DONE: _bSetDebugNameA (Name your threads in the VC debugger thread list)
BOOL
CxThread::_bSetDebugNameA(
    const std::string &csName
) const
{
    /////*DEBUG*/xASSERT_RET(0    <  _m_ulID,       FALSE);
    /////*DEBUG*/xASSERT_RET(32   >  csName.size(), FALSE); //MAX_NAME_SIZE 32

    const DWORD MS_VC_EXCEPTION = 0x406D1388;

    #pragma pack(push,8)
    struct tagTHREADNAME_INFO {
        DWORD  dwType;      //must be 0x1000
        LPCSTR szName;      //pointer to name (in user addr space)
        DWORD  dwThreadID;  //thread ID (-1 = caller thread)
        DWORD  dwFlags;     //reserved for future use, must be zero
    };
    #pragma pack(pop)

    tagTHREADNAME_INFO tiInfo = {0};
    tiInfo.dwType     = 0x1000;
    tiInfo.szName     = csName.c_str();
    tiInfo.dwThreadID = ulGetId();
    tiInfo.dwFlags    = 0;

    __try {
        ::RaiseException(MS_VC_EXCEPTION, 0, sizeof(tiInfo) / sizeof(ULONG_PTR), (ULONG_PTR *)&tiInfo);
        /*DEBUG*/// n/a
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        //n/a
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    callbacks
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: vHandler_OnEnter ()
VOID
CxThread::_vHandler_OnEnter(
    CxThread *pthSender
)
{
    //если произошел щелчкок мышки на нашей кнопке...
    //if (TRUE == _m_bFlag_OnEnter) {
    xCHECK_DO(NULL == _m_vCallback_OnEnter, return);

    _m_vCallback_OnEnter(pthSender);
}
//---------------------------------------------------------------------------
//DONE: vHandler_OnExit ()
VOID
CxThread::_vHandler_OnExit(
    CxThread *pthSender
)
{
    //если произошел щелчкок мышки на нашей кнопке...
    //if (TRUE == _m_bFlag_OnExit) {
    xCHECK_DO(NULL == _m_vCallback_OnExit, return)

    _m_vCallback_OnExit(pthSender);
}
//---------------------------------------------------------------------------
