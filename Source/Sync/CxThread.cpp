/**
 * \file  CxThread.cpp
 * \brief thread
 */


#include <xLib/Sync/CxThread.h>

#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Sync/CxProcess.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxThread::CxThread(
    const BOOL cbIsAutoDelete
) :
    m_ulTag                 (0UL),

    //data
    _m_hThread              (),
    _m_ulId                 (0UL),
    _m_uiExitStatus         (0U),
    _m_pvParam              (NULL),
    _m_cbIsAutoDelete       (cbIsAutoDelete),

    //flags
    _m_bIsCreated           (FALSE),
    _m_bIsRunning           (FALSE),
    /*_m_bIsPaused*/// n/a
    /*_m_bIsExited*/// n/a

    //
    ///_vOnExit             (NULL),

    //other
    _m_pevStarter           (NULL),
    _m_evPause              (FALSE, FALSE),
    _m_evExit               (TRUE,  FALSE)
{
}
//---------------------------------------------------------------------------
/*virtual*/
CxThread::~CxThread() {
    /*DEBUG*/

    //-------------------------------------
    //close thread, if it still running
    BOOL bRes = bIsRunning();
    if (TRUE == bRes) {
        bRes = bExit();
        if (FALSE == bRes) {
            bRes = bKill(_ms_culExitTimeout);
            if (FALSE == bRes) {
                /*DEBUG*/xASSERT_DO(FALSE != bRes, /*nothing*/);
            }
        }
    }

    //-------------------------------------
    //state flags
    _vSetStatesDefault();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: actions
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxThread::bCreate(
    const BOOL cbIsPaused,
    const UINT cuiStackSize,
    void       *pvParam
)
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE == _m_hThread.bIsValid(), FALSE);
#elif xOS_ENV_UNIX

#endif
    /*DEBUG*/// cbIsPaused   - n/a
    /*DEBUG*/// cuiStackSize - n/a
    /*DEBUG*/// pvParam      - n/a

    BOOL bRes = FALSE;

    _m_pvParam = pvParam;

    //-------------------------------------
    //_m_evStarter
    _m_pevStarter = new CxEvent(TRUE, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_pevStarter, FALSE);

    //-------------------------------------
    //start
#if xOS_ENV_WIN
    HANDLE hRes = NULL;
    TxId   ulId = 0;

    hRes = reinterpret_cast<HANDLE>( _beginthreadex(NULL, cuiStackSize, _s_uiJobEntry, this, 0U, (UINT *)&ulId) );
    /*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);
    /*DEBUG*/xASSERT_RET(0    <  ulId, FALSE);

    bRes = _m_hThread.bSet(hRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,                  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    _m_ulId = ulId;
#elif xOS_ENV_UNIX
    int            iRes = - 1;
    TxId           ulId;
    pthread_attr_t paAttributes; // n/a - {{0}}

    iRes = ::pthread_attr_init(&paAttributes);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);

    iRes = ::pthread_attr_setdetachstate(&paAttributes, PTHREAD_CREATE_JOINABLE); //PTHREAD_CREATE_DETACHED
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);

    if (0 != cuiStackSize) {
        iRes = ::pthread_attr_setstacksize(&paAttributes, cuiStackSize);
        /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
    }

    iRes = ::pthread_create(&ulId, &paAttributes, &_s_uiJobEntry, this);
    /*DEBUG*/xASSERT_MSG_RET(0   == iRes, CxLastError::sFormat(iRes), FALSE);
    /*DEBUG*/xASSERT_MSG_RET(0UL <  ulId, CxLastError::sFormat(iRes), FALSE);

    iRes = ::pthread_attr_destroy(&paAttributes);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);

    _m_hThread = ulId;  //TODO: is it right?
    _m_ulId    = ulId;
#endif
    /*DEBUG*/xASSERT_RET(FALSE == CxCurrentThread::bIsCurrent(_m_ulId), FALSE);

    //-------------------------------------
    //flags
    {
        _m_bIsCreated = TRUE;
        _m_bIsRunning = TRUE;
        /*_m_bIsPaused*/// n/a

        if (FALSE != cbIsPaused) {
            bRes = bPause();
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        } else {
            bRes = bResume();
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }

        /*_m_bIsExited*/// n/a
    }

    //-------------------------------------
    //construction is complete, start job entry
    bRes = _m_pevStarter->bSet();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bResume() {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
#elif xOS_ENV_UNIX

#endif

    BOOL bRes = _m_evPause.bSet();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bPause() {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_MSG_RET(FALSE != _m_hThread.bIsValid(), CxString::lexical_cast(_m_hThread.hGet()).c_str(), FALSE);
#elif xOS_ENV_UNIX

#endif

    BOOL bRes = _m_evPause.bReset();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bExit() {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
#elif xOS_ENV_UNIX

#endif

    BOOL bRes = _m_evExit.bSet();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //flags
    /*_m_bIsExited*///  n/a
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*/    xCHECK_DO(TRUE == bIsPaused(), bResume()); //если поток приостановленный (bPause) - возобновляем
                                                                   //если ожидает чего-то
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bKill(
    const ULONG culTimeout
)
{
    BOOL  bRes  = FALSE;
    ULONG ulRes = 0UL;

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*///ulTimeout - n/a

    _m_uiExitStatus = 0U;
    bRes = ::TerminateThread(_m_hThread.hGet(), _m_uiExitStatus);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    for ( ; ; ) {
        ulRes = ulGetExitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRes, break);

        bRes = CxCurrentThread::bSleep(_ms_culStillActiveTimeout);
        /*DEBUG*/xASSERT_DO(FALSE != bRes, break);
    }
#elif xOS_ENV_UNIX
    int iRes = ::pthread_kill(_m_ulId, SIGALRM);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);

    bRes = CxCurrentThread::bSleep(_ms_culStillActiveTimeout);
    /*DEBUG*/xASSERT(FALSE != bRes);
#endif

    //-------------------------------------
    //clean members
#if xOS_ENV_WIN
    bRes = _m_hThread.bClose();
    /*DEBUG*/xASSERT(FALSE != bRes);
#elif xOS_ENV_UNIX
    _m_hThread = 0UL;
#endif

    _m_ulId         = 0UL;
    _m_uiExitStatus = ulRes;    //saving value
    _m_pvParam      = NULL;
    //_m_cbIsAutoDelete - n/a

    //-------------------------------------
    //flags
    _vSetStatesDefault();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bWait(
    const ULONG culTimeout
) const
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*///ulTimeout - n/a

    //-------------------------------------
    //flags
    //?????????

    /*DEBUG*/xASSERT(CxCurrentThread::ulGetId() != _m_ulId);
    xCHECK_RET(CxCurrentThread::ulGetId() == _m_ulId, TRUE);

    ULONG ulRes = WAIT_FAILED;
    ulRes = ::WaitForSingleObject(_m_hThread.hGet(), culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRes, FALSE);
#elif xOS_ENV_UNIX
    int iRes = ::pthread_join(_m_ulId, NULL);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: flags
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxThread::bIsCreated() const {
    /*DEBUG*/// _m_hThread - n/a

    bool bRes = false;

#if xOS_ENV_WIN
    bRes = (FALSE != _m_bIsCreated) && (FALSE != _m_hThread.bIsValid());
#elif xOS_ENV_UNIX
    bRes = (FALSE != _m_bIsCreated) && (0UL   != _m_hThread);
#endif

    return static_cast<BOOL>( bRes );
}
//---------------------------------------------------------------------------
BOOL
CxThread::bIsRunning() const {
    /*DEBUG*/// _m_hThread - n/a

    bool bRes = false;

#if xOS_ENV_WIN
    ULONG ulRes = 0;

    (void)::GetExitCodeThread(_m_hThread.hGet(), &ulRes);

    bool bCond1 = ( FALSE         != _m_hThread.bIsValid()                       );
    bool bCond2 = ( 0UL           <  _m_ulId                                     );
    bool bCond3 = ( TRUE          == _m_bIsRunning                               );
    bool bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_m_hThread.hGet(), 0) );
    bool bCond5 = ( STILL_ACTIVE  == ulRes                                       );

    bRes = bCond1 && bCond2 && bCond3 && bCond4 && bCond5;
#elif xOS_ENV_UNIX
    bool bCond1 = ( 0UL           != _m_hThread                                  );
    bool bCond2 = ( 0UL            <  _m_ulId                                    );
    bool bCond3 = ( TRUE          == _m_bIsRunning                               );

    #if xTODO
        bool bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_m_hThread.hGet(), 0) );
        bool bCond5 = ( STILL_ACTIVE  == ulRes                                       );
    #endif

    bRes = bCond1 && bCond2 && bCond3 /*&& bCond4 && bCond5*/;
#endif

    return static_cast<BOOL>( bRes );
}
//---------------------------------------------------------------------------
BOOL
CxThread::bIsPaused() {
    /*DEBUG*/// _m_hThread - n/a

    bool bRes = false;

#if xOS_ENV_WIN
    bRes = (!_m_evPause.bIsSignaled()) && (FALSE != _m_hThread.bIsValid());
#elif xOS_ENV_UNIX
    bRes = (!_m_evPause.bIsSignaled()) /*&& (0UL   != _m_hThread)*/;
#endif

    return static_cast<BOOL>( bRes );
}
//---------------------------------------------------------------------------
BOOL
CxThread::bIsExited() {
    /*DEBUG*/// _m_hThread - n/a

    bool bRes = false;

#if xOS_ENV_WIN
    bRes = (_m_evExit.bIsSignaled()) && (FALSE != _m_hThread.bIsValid());
#elif xOS_ENV_UNIX
    bRes = (_m_evExit.bIsSignaled()) /*&& (0UL   != _m_hThread)*/;
#endif

    return static_cast<BOOL>( bRes );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: messages
*
*****************************************************************************/

#if xOS_ENV_WIN
//---------------------------------------------------------------------------
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

    BOOL bRes = ::PostMessage(hHwnd, uiMsg, static_cast<WPARAM>(uiParam1), static_cast<LPARAM>(liParam2));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
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

    (void)::SendMessage(hHwnd, uiMsg, static_cast<WPARAM>(uiParam1), static_cast<LPARAM>(liParam2));
    /*DEBUG*/xASSERT_RET(0UL == CxLastError::ulGet(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bPostThreadMessage(
    UINT uiMsg,
    UINT uiParam1,
    LONG liParam2
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    BOOL bRes = ::PostThreadMessage(ulGetId(), uiMsg, static_cast<WPARAM>(uiParam1), static_cast<LPARAM>(liParam2));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
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

    BOOL bRes = FALSE;

    for (ULONG i = 0UL; i < ulAttemps; ++ i) {
        bRes = ::PostThreadMessage(ulGetId(), uiMsg, static_cast<WPARAM>(uiParam1), static_cast<LPARAM>(liParam2));

        xCHECK_RET(TRUE  == bRes, TRUE);
        xCHECK_DO (FALSE == bRes, CxCurrentThread::bSleep(ulAttempTimeout));
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bMessageWaitQueue(
    UINT  uiMsg,
    UINT *puiParam1,
    LONG *pliParam2
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(0     <  uiMsg,                 FALSE);

    std::vector<UINT> vuiMsg;
    vuiMsg.push_back(uiMsg);

    BOOL bRes = bMessageWaitQueue(vuiMsg, NULL, puiParam1, pliParam2);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bMessageWaitQueue(
    const std::vector<UINT> &cvuiMsg,
    UINT                    *puiMsg,
    UINT                    *puiParam1,
    LONG                    *pliParam2
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(false == cvuiMsg.empty(),       FALSE);

    BOOL bRes   = FALSE;
    MSG  msgMsg = {0};

    while ((bRes = ::GetMessage(&msgMsg, NULL, 0, 0 ))) {
        /*DEBUG*/xASSERT_RET(- 1 != bRes, FALSE);

        for (size_t i = 0; i < cvuiMsg.size(); ++ i) {
            xCHECK_DO(cvuiMsg.at(i) != msgMsg.message, continue);

            xPTR_ASSIGN(puiMsg,    msgMsg.message                    );
            xPTR_ASSIGN(puiParam1, static_cast<UINT>( msgMsg.wParam ));
            xPTR_ASSIGN(pliParam2, static_cast<LONG>( msgMsg.lParam ));

            return TRUE;
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif


/****************************************************************************
*    public: priority
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
int
CxThread::_iGetPriorityMin() {
    int iRes = - 1;

#if xOS_ENV_WIN
    iRes = THREAD_PRIORITY_IDLE;
#elif xOS_ENV_UNIX
    iRes = ::sched_get_priority_min(SCHED_FIFO);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return iRes;
}
//---------------------------------------------------------------------------
/*static*/
int
CxThread::_iGetPriorityMax() {
    int iRes = - 1;

#if xOS_ENV_WIN
    iRes = THREAD_PRIORITY_TIME_CRITICAL;
#elif xOS_ENV_UNIX
    iRes = ::sched_get_priority_max(SCHED_FIFO);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return iRes;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bSetPriority(
    const EPriority ctpPriority
) const
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    BOOL bRes = ::SetThreadPriority(_m_hThread.hGet(), ctpPriority);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif xOS_ENV_UNIX
    #if xOS_ENV_UNIX
        xCHECK_RET(FALSE == CxSystemInfo::bIsUserAnAdmin(), FALSE);
    #endif

    sched_param spParam = {0};

    spParam.sched_priority = ctpPriority;

    int iRes = ::pthread_setschedparam(ulGetId(), SCHED_FIFO, &spParam);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
CxThread::EPriority
CxThread::tpGetPriority() const {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), tpError);
#elif xOS_ENV_UNIX

#endif

    CxThread::EPriority tpRes = tpError;

#if xOS_ENV_WIN
    tpRes = static_cast<EPriority>( ::GetThreadPriority(_m_hThread.hGet()) );
    /*DEBUG*/xASSERT_RET(tpError != tpRes, tpError);
#elif xOS_ENV_UNIX
    sched_param spParam  = {0};
    int         iPolicy  = SCHED_FIFO;

    int iRes = ::pthread_getschedparam(ulGetId(), &iPolicy, &spParam);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, CxLastError::sFormat(iRes), tpError);

    tpRes = static_cast<EPriority>( spParam.sched_priority );
#endif

    return tpRes;
}
//---------------------------------------------------------------------------
std::string_t
CxThread::sGetPriorityString() const {
    /*DEBUG*/// n/a

    int iRes = tpGetPriority();
    switch (iRes) {
        case tpIdle:            return xT("Idle");
        case tpLowest:          return xT("Lowest");
        case tpBelowNormal:     return xT("Below normal");
        case tpNormal:          return xT("Normal");
        case tpAboveNormal:     return xT("Above normal");
        case tpHighest:         return xT("Highest");
        case tpTimeCritical:    return xT("Time critical");
    }

    return xT("N/A");
}
//---------------------------------------------------------------------------
BOOL
CxThread::bPriorityUp() const {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
#elif xOS_ENV_UNIX

#endif

    EPriority tpOldLevel  = tpError;
    EPriority tpiNewLevel = tpError;

    tpOldLevel = tpGetPriority();
    switch (tpOldLevel) {
        case tpIdle:            tpiNewLevel = tpLowest;                 break;
        case tpLowest:          tpiNewLevel = tpBelowNormal;            break;
        case tpBelowNormal:     tpiNewLevel = tpNormal;                 break;
        case tpNormal:          tpiNewLevel = tpAboveNormal;            break;
        case tpAboveNormal:     tpiNewLevel = tpHighest;                break;
        case tpHighest:         tpiNewLevel = tpTimeCritical;           break;
        case tpTimeCritical:    return TRUE;                            break;

        default:                /*DEBUG*/xASSERT_RET(FALSE, FALSE);     break;
    }

    return bSetPriority(tpiNewLevel);
}
//---------------------------------------------------------------------------
BOOL
CxThread::bPriorityDown() const {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);
#elif xOS_ENV_UNIX

#endif

    EPriority tpOldLevel  = tpError;
    EPriority tpiNewLevel = tpError;

    tpOldLevel = tpGetPriority();
    switch (tpOldLevel) {
        case tpIdle:            return TRUE;                            break;
        case tpLowest:          tpiNewLevel = tpIdle;                   break;
        case tpBelowNormal:     tpiNewLevel = tpLowest;                 break;
        case tpNormal:          tpiNewLevel = tpBelowNormal;            break;
        case tpAboveNormal:     tpiNewLevel = tpNormal;                 break;
        case tpHighest:         tpiNewLevel = tpAboveNormal;            break;
        case tpTimeCritical:    tpiNewLevel = tpHighest;                break;

        default:                /*DEBUG*/xASSERT_RET(FALSE, FALSE);     break;
    }

    return bSetPriority(tpiNewLevel);
}
//---------------------------------------------------------------------------
BOOL
CxThread::bIsPriorityBoost() const {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    BOOL bDisablePriorityBoost = TRUE;

    BOOL bRes = ::GetThreadPriorityBoost(_m_hThread.hGet(), &bDisablePriorityBoost);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //bDisablePriorityBoost == TRUE  - dynamic boosting is disabled
    //bDisablePriorityBoost == FALSE - normal behavior

    return ! bDisablePriorityBoost;
#elif xOS_ENV_UNIX
    return FALSE;
#endif
}
//---------------------------------------------------------------------------
BOOL
CxThread::bSetPriorityBoost(
    const BOOL cbIsEnabled
) const
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    BOOL bRes = ::SetThreadPriorityBoost(_m_hThread.hGet(), ! cbIsEnabled);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
#elif xOS_ENV_UNIX
    return FALSE;
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: CPU
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxThread::bSetCpuAffinity(
    const int ciProcNum
) const
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    DWORD_PTR dwMask;

    dwMask = 1UL << ciProcNum;

    DWORD_PTR uiRes = ::SetThreadAffinityMask(_m_hThread.hGet(), dwMask);
    /*DEBUG*/xASSERT_RET(0                       != uiRes, FALSE);
    /*DEBUG*/xASSERT_RET(ERROR_INVALID_PARAMETER != uiRes, FALSE);
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        cpuset_t  csCpuSet;
    #else
        cpu_set_t csCpuSet;
    #endif

    CPU_ZERO(&csCpuSet);
    (void)CPU_SET(ciProcNum, &csCpuSet);

    int iRes = ::pthread_setaffinity_np(ulGetId(), sizeof(csCpuSet), &csCpuSet);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRes, CxLastError::sFormat(iRes), FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bSetCpuIdeal(
    const ULONG culIdealCpu    ///< value is zero-based
) const
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), FALSE);

    ULONG ulRes = (ULONG) - 1;

    ulRes = ::SetThreadIdealProcessor(_m_hThread.hGet(), culIdealCpu);
    /*DEBUG*/xASSERT_RET((ULONG) - 1 != ulRes, FALSE);

    //TODO: xASSERT_RET
    ////*DEBUG*/xASSERT_RET(ulIdealCpu != ulRes, FALSE);
#elif xOS_ENV_UNIX
    return FALSE;
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
ULONG
CxThread::ulGetCpuIdeal() const {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), 0UL);
#elif xOS_ENV_UNIX

#endif

    ULONG ulRes = (ULONG) - 1;

#if xOS_ENV_WIN
    ulRes = ::SetThreadIdealProcessor(_m_hThread.hGet(), MAXIMUM_PROCESSORS);
    /*DEBUG*/xASSERT_RET((ULONG) - 1 != ulRes, (ULONG) - 1);
#elif xOS_ENV_UNIX

#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
ULONG
CxThread::ulGetCpuCount() {
    ULONG ulRes = CxSystemInfo::ulGetNumOfCpus();
    xCHECK_RET(ulRes < 1UL || ulRes > 32UL, 1UL);

    return ulRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxThread::TxHandle
CxThread::hGet() const {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), TxHandle());

    return _m_hThread.hGet();
#elif xOS_ENV_UNIX
    return _m_hThread;
#endif
}
//---------------------------------------------------------------------------
CxThread::TxId
CxThread::ulGetId() const {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), 0);
#elif xOS_ENV_UNIX

#endif

    return _m_ulId;
}
//---------------------------------------------------------------------------
BOOL
CxThread::bIsCurrent() const {
    /*DEBUG*/

    return CxCurrentThread::bIsCurrent( CxCurrentThread::ulGetId() );
}
//---------------------------------------------------------------------------
ULONG
CxThread::ulGetExitStatus() const {
    ULONG ulRes = 0;

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(FALSE != _m_hThread.bIsValid(), 0UL);

    BOOL bRes = ::GetExitCodeThread(_m_hThread.hGet(), &ulRes);
    /*DEBUG*/xASSERT_RET(FALSE           != bRes,  ulRes);
    //--/*DEBUG*/xASSERT_RET(_m_uiExitStatus == ulRes, ulRes);
#elif xOS_ENV_UNIX
    ulRes = _m_uiExitStatus;
#endif

    return ulRes;
}
//BOOL
///*CxThread::*/bPost() {
//
//long sys_tgkill (int tgid, int pid, int sig);
//}

//---------------------------------------------------------------------------
BOOL
CxThread::bSetDebugName(
    const std::string_t &csName
) const
{
    /////*DEBUG*/xASSERT_RET(0  < _m_ulId,       FALSE);
    /////*DEBUG*/xASSERT_RET(32 > csName.size(), FALSE); //MAX_NAME_SIZE 32

    xCHECK_RET(FALSE == CxDebugger::bIsPresent(), TRUE);

#if xOS_ENV_WIN
    #if xCOMPILER_MS || xCOMPILER_CODEGEAR
        const DWORD culMsVcException = 0x406D1388;

    #pragma pack(push, 8)
        struct tagTHREADNAME_INFO {
            DWORD  dwType;      //must be 0x1000
            LPCSTR pszName;     //pointer to name (in user addr space)
            DWORD  dwThreadID;  //thread ID (-1 = caller thread)
            DWORD  dwFlags;     //reserved for future use, must be zero
        };
    #pragma pack(pop)

        tagTHREADNAME_INFO tiInfo = {0};
        tiInfo.dwType     = 0x1000;
    #if xUNICODE
        //TODO: bSetDebugName, convert from Unicode to Ansi
        ////tiInfo.pszName    = xTS2S(csName).c_str();
        tiInfo.pszName    = "[Unknown]";
    #else
        tiInfo.pszName    = csName.c_str();
    #endif
        tiInfo.dwThreadID = ulGetId();
        tiInfo.dwFlags    = 0;

        __try {
            (void)::RaiseException(culMsVcException, 0, sizeof(tiInfo) / sizeof(ULONG_PTR), (ULONG_PTR *)&tiInfo);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            //n/a
        }
    #elif xCOMPILER_MINGW32
        //TODO: bSetDebugName
    #else
        //TODO: bSetDebugName
    #endif
#elif xOS_FREEBSD
    (void)pthread_set_name_np(ulGetId(), csName.c_str());
#elif xOS_ENV_UNIX
    int iRes = ::prctl(PR_SET_NAME, csName.c_str(), 0, 0, 0);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
CxThread::TxHandle
CxThread::hOpen(
    const ULONG culAccess,
    const BOOL  cbInheritHandle,
    const ULONG culId
)
{
    /*DEBUG*///ulAccess       - n/a
    /*DEBUG*///bInheritHandle - n/a
    /*DEBUG*/xASSERT_RET(0UL < culId, TxHandle());

#if xOS_ENV_WIN
    TxHandle hRes = NULL;

    hRes = ::OpenThread(culAccess, cbInheritHandle, culId);
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);
#elif xOS_ENV_UNIX
    TxHandle hRes = 0;

    //TODO: hOpen
#endif

    return hRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected: events
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*virtual*/
UINT
CxThread::uiOnRun(
    void *pvParam
) /* = 0*/
{
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_MSG_RET(FALSE, xT("It's virtual method"), 0U);

    UINT uiRes = 0U;

    #if xTEMP_DISABLED
        for ( ; ; ) {
            BOOL bRes = bIsTimeToExit();
            xCHECK_DO(FALSE != bRes, break);

            //...
        }
    #endif

    return uiRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxThread::bIsTimeToExit() {
    /*DEBUG*/// n/a

    BOOL bRes = FALSE;

    //-------------------------------------
    //exit
    bRes = bIsExited();
    xCHECK_RET(FALSE != bRes, TRUE);

    //-------------------------------------
    //pause / resume
    bRes = bIsPaused();
    xCHECK_RET(FALSE != bRes, static_cast<BOOL>( !_bWaitResumption() ));

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
/*static*/
CxThread::TxExitStatus xSTDCALL
CxThread::_s_uiJobEntry(
    void *pvParam
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvParam, 0);

    UINT uiRes = 0;
    BOOL bRes  = FALSE;     xUNUSED(bRes);

    CxThread *pthThis = static_cast<CxThread *>( pvParam );
    /*DEBUG*/xASSERT_RET(NULL != pthThis, 0);

    //-------------------------------------
    //handle must be valid
    ////CxCurrentThread::bSleep(500UL);

    CxEvent::EObjectState osRes = pthThis->_m_pevStarter->osWait(5000UL);   // not infinite timeout
    xTEST_EQ(CxEvent::osSignaled, osRes);
    /*DEBUG*/xASSERT_RET(CxEvent::osSignaled == osRes, TxExitStatus());

    xPTR_DELETE(pthThis->_m_pevStarter);

    //-------------------------------------
    //if created suspended thread - wait for resumption
    xCHECK_DO(TRUE == pthThis->bIsPaused(), (void)pthThis->_bWaitResumption());

    {
        //-------------------------------------
        //begin of thread function
        try {
            #if xTODO
                pthThis->_vHandler_OnEnter(pthThis);
            #endif
        }
        catch (...) {
            /*DEBUG*/xASSERT(FALSE);
        }

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

        //-------------------------------------
        //end of thread function
        try {
            #if xTODO
                pthThis->_vHandler_OnExit(pthThis);
            #endif
        }
        catch (...) {
            /*DEBUG*/xASSERT(FALSE);
        }
    }

    //-------------------------------------
    //clean members (is need to close???)
#if xOS_ENV_WIN
    bRes = pthThis->_m_hThread.bClose();
    /*DEBUG*/xASSERT(FALSE != bRes);
#elif xOS_ENV_UNIX
    //TODO: _m_hThread.bClose()
#endif

    pthThis->_m_ulId         = 0UL;
    pthThis->_m_uiExitStatus = uiRes;    //???
    pthThis->_m_pvParam      = NULL;
    //pthThis->_m_cbIsAutoDelete - n/a

    //-------------------------------------
    //flags
    pthThis->_vSetStatesDefault();

    //-------------------------------------
    //auto delete oneself
    xCHECK_DO(TRUE == pthThis->_m_cbIsAutoDelete, xPTR_DELETE(pthThis));

#if xOS_ENV_WIN
    return  pthThis->_m_uiExitStatus;
#elif xOS_ENV_UNIX
    return &pthThis->_m_uiExitStatus;
#endif
}
//---------------------------------------------------------------------------
BOOL
CxThread::_bWaitResumption() {
    /*DEBUG*/

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a

    CxEvent::EObjectState osRes = _m_evPause.osWait();
    /*DEBUG*/xASSERT_RET(CxEvent::osFailed   != osRes, FALSE);
    /*DEBUG*/xASSERT_RET(CxEvent::osTimeout  != osRes, FALSE);
    /*DEBUG*/xASSERT_RET(CxEvent::osSignaled == osRes, FALSE);

    return static_cast<BOOL>( CxEvent::osSignaled == osRes );
}
//---------------------------------------------------------------------------
void
CxThread::_vSetStatesDefault() {
    /*DEBUG*/// n/a

    //-------------------------------------
    //flags
    _m_bIsCreated  = FALSE;
    _m_bIsRunning  = FALSE;
    /*_m_bIsPaused*/// n/a
    /*_m_bIsExited*/// n/a
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
