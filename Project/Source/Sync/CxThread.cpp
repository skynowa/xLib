/**
 * \file  CxThread.cpp
 * \brief thread
 */


#include <xLib/Sync/CxThread.h>

#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Sync/CxProcess.h>


xNAMESPACE_BEGIN(NxLib)

#if xOS_ENV_UNIX
    // constants
    const ulong_t CxThread::_ms_culStillActiveTimeout;
    const ulong_t CxThread::_ms_culExitTimeout;
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxThread::CxThread(
    const bool &a_cbIsAutoDelete
) :
    m_ulTag          (0UL),

    // data
    _m_hThread       (),
    _m_ulId          (0UL),
    _m_uiExitStatus  (0U),
    _m_pvParam       (NULL),
    _m_cbIsAutoDelete(a_cbIsAutoDelete),

    // flags
    _m_bIsCreated    (false),
    _m_bIsRunning    (false),
    /*_m_bIsPaused*/// n/a
    /*_m_bIsExited*/// n/a

    //
    ///_vOnExit      (NULL),

    // other
    _m_pevStarter    (NULL),
    _m_evPause       (false, false),
    _m_evExit        (true,  false)
{
}
//---------------------------------------------------------------------------
/*virtual*/
CxThread::~CxThread() {
    /*DEBUG*/

    //-------------------------------------
    // close thread, if it still running
    bool bRv = bIsRunning();
    if (true == bRv) {
        bRv = bExit();
        if (false == bRv) {
            bRv = bKill(_ms_culExitTimeout);
            if (false == bRv) {
                /*DEBUG*/xASSERT(false);
            }
        }
    }

    //-------------------------------------
    // state flags
    _vSetStatesDefault();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: actions
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxThread::bCreate(
    const bool   &a_cbIsPaused,
    const uint_t &a_cuiStackSize,
    void         *a_pvParam
)
{
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false == _m_hThread.bIsValid(), false);
#elif xOS_ENV_UNIX

#endif
    /*DEBUG*/// cbIsPaused   - n/a
    /*DEBUG*/// cuiStackSize - n/a
    /*DEBUG*/// pvParam      - n/a

    bool bRv = false;

    _m_pvParam = a_pvParam;

    //-------------------------------------
    // _m_evStarter
    _m_pevStarter = new CxEvent(true, false);
    /*DEBUG*/xASSERT_RET(NULL != _m_pevStarter, false);

    //-------------------------------------
    // start
#if   xOS_ENV_WIN
    id_t ulId = 0UL;

    HANDLE hRv = reinterpret_cast<HANDLE>( ::_beginthreadex(NULL, a_cuiStackSize, _s_uiJobEntry, this, 0U, (uint_t *)&ulId) );
    /*DEBUG*/xASSERT_RET(NULL != hRv, false);
    /*DEBUG*/xASSERT_RET(0UL  <  ulId, false);

    bRv = _m_hThread.bSet(hRv);
    /*DEBUG*/xASSERT_RET(true  == bRv,                  false);
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);

    _m_ulId = ulId;
#elif xOS_ENV_UNIX
    int            iRv = - 1;
    id_t           ulId;
    pthread_attr_t paAttributes; // n/a - {{0}}

    iRv = ::pthread_attr_init(&paAttributes);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);

    iRv = ::pthread_attr_setdetachstate(&paAttributes, PTHREAD_CREATE_JOINABLE); //PTHREAD_CREATE_DETACHED
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);

    if (0 != cuiStackSize) {
        //TODO: size_t size = PTHREAD_STACK_MIN + 0x4000;
        iRv = ::pthread_attr_setstacksize(&paAttributes, a_cuiStackSize);
        /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);
    }

    iRv = ::pthread_create(&ulId, &paAttributes, &_s_uiJobEntry, this);
    /*DEBUG*/xASSERT_MSG_RET(0   == iRv, CxLastError::sFormat(iRv), false);
    /*DEBUG*/xASSERT_MSG_RET(0UL <  ulId, CxLastError::sFormat(iRv), false);

    iRv = ::pthread_attr_destroy(&paAttributes);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);

    _m_hThread = ulId;  //TODO: is it right?
    _m_ulId    = ulId;
#endif
    /*DEBUG*/xASSERT_RET(false == CxCurrentThread::bIsCurrent(_m_ulId), false);

    //-------------------------------------
    // flags
    {
        _m_bIsCreated = true;
        _m_bIsRunning = true;
        /*_m_bIsPaused*/// n/a

        if (false != a_cbIsPaused) {
            bRv = bPause();
            /*DEBUG*/xASSERT_RET(true == bRv, false);
        } else {
            bRv = bResume();
            /*DEBUG*/xASSERT_RET(true == bRv, false);
        }

        /*_m_bIsExited*/// n/a
    }

    //-------------------------------------
    // construction is complete, start job entry
    bRv = _m_pevStarter->bSet();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxThread::bResume() {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
#elif xOS_ENV_UNIX

#endif

    bool bRv = _m_evPause.bSet();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a

    return true;
}
//---------------------------------------------------------------------------
bool
CxThread::bPause() {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_MSG_RET(false != _m_hThread.bIsValid(), CxString::string_cast(_m_hThread.hGet()).c_str(), false);
#elif xOS_ENV_UNIX

#endif

    bool bRv = _m_evPause.bReset();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a

    return true;
}
//---------------------------------------------------------------------------
bool
CxThread::bExit() {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
#elif xOS_ENV_UNIX

#endif

    bool bRv = _m_evExit.bSet();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //flags
    /*_m_bIsExited*///  n/a
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*/    xCHECK_DO(true == bIsPaused(), bResume()); //если поток приостановленный (bPause) - возобновляем
                                                                   //если ожидает чего-то
    return true;
}
//---------------------------------------------------------------------------
bool
CxThread::bKill(
    const ulong_t &a_culTimeout
)
{
    bool    bRv  = false;
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
    /*DEBUG*///ulTimeout - n/a

    _m_uiExitStatus = 0U;

    BOOL blRes = ::TerminateThread(_m_hThread.hGet(), _m_uiExitStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    for ( ; ; ) {
        ulRv = ulGetExitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        bRv = CxCurrentThread::bSleep(a_culTimeout);
        /*DEBUG*/xASSERT_DO(true == bRv, break);
    }
#elif xOS_ENV_UNIX
    int iRv = ::pthread_kill(_m_ulId, SIGALRM);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);

    bRv = CxCurrentThread::bSleep(a_culTimeout);
    /*DEBUG*/xASSERT(true == bRv);
#endif

    //-------------------------------------
    // clean members
#if   xOS_ENV_WIN
    bRv = _m_hThread.bClose();
    /*DEBUG*/xASSERT(true == bRv);
#elif xOS_ENV_UNIX
    _m_hThread = 0UL;
#endif

    _m_ulId         = 0UL;
    _m_uiExitStatus = ulRv;    //saving value
    _m_pvParam      = NULL;
    //_m_cbIsAutoDelete - n/a

    //-------------------------------------
    //flags
    _vSetStatesDefault();

    return true;
}
//---------------------------------------------------------------------------
bool
CxThread::bWait(
    const ulong_t &a_culTimeout
) const
{
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
    /*DEBUG*///ulTimeout - n/a

    //-------------------------------------
    //flags
    //?????????

    /*DEBUG*/xASSERT(CxCurrentThread::ulGetId() != _m_ulId);
    xCHECK_RET(CxCurrentThread::ulGetId() == _m_ulId, true);

    DWORD ulRv = ::WaitForSingleObject(_m_hThread.hGet(), a_culTimeout);
    /*DEBUG*/xASSERT_RET(WAIT_OBJECT_0 == ulRv, false);
#elif xOS_ENV_UNIX
    // TODO: thread must not be detached
    // FIX:  a_culTimeout
    int iRv = ::pthread_join(_m_ulId, NULL);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: flags
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxThread::bIsCreated() const {
    /*DEBUG*/// _m_hThread - n/a

    bool bRv = false;

#if   xOS_ENV_WIN
    bRv = (true == _m_bIsCreated) && (false != _m_hThread.bIsValid());
#elif xOS_ENV_UNIX
    bRv = (true == _m_bIsCreated) && (0UL   != _m_hThread);
#endif

    return bRv;
}
//---------------------------------------------------------------------------
bool
CxThread::bIsRunning() const {
    /*DEBUG*/// _m_hThread - n/a

    bool bRv = false;

#if   xOS_ENV_WIN
    DWORD ulRv = 0UL;

    (void)::GetExitCodeThread(_m_hThread.hGet(), &ulRv);

    bool bCond1 = ( false         != _m_hThread.bIsValid()                         );
    bool bCond2 = ( 0UL           <  _m_ulId                                       );
    bool bCond3 = ( true          == _m_bIsRunning                                 );
    bool bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_m_hThread.hGet(), 0UL) );
    bool bCond5 = ( STILL_ACTIVE  == ulRv                                          );

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5;
#elif xOS_ENV_UNIX
    bool bCond1 = ( 0UL           != _m_hThread                                    );
    bool bCond2 = ( 0UL           <  _m_ulId                                       );
    bool bCond3 = ( true          == _m_bIsRunning                                 );

    #if xTODO
        bool bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_m_hThread.hGet(), 0UL) );
        bool bCond5 = ( STILL_ACTIVE  == ulRv                                          );
    #endif

    bRv = bCond1 && bCond2 && bCond3 /*&& bCond4 && bCond5*/;
#endif

    return bRv;
}
//---------------------------------------------------------------------------
bool
CxThread::bIsPaused() {
    /*DEBUG*/// _m_hThread - n/a

    bool bRv = false;

#if   xOS_ENV_WIN
    bRv = (!_m_evPause.bIsSignaled()) && (false != _m_hThread.bIsValid());
#elif xOS_ENV_UNIX
    bRv = (!_m_evPause.bIsSignaled()) /*&& (0UL   != _m_hThread)*/;
#endif

    return bRv;
}
//---------------------------------------------------------------------------
bool
CxThread::bIsExited() {
    /*DEBUG*/// _m_hThread - n/a

    bool bRv = false;

#if   xOS_ENV_WIN
    bRv = (true == _m_evExit.bIsSignaled()) && (false != _m_hThread.bIsValid());
#elif xOS_ENV_UNIX
    bRv = (true == _m_evExit.bIsSignaled()) && (0UL   != _m_hThread);
#endif

    return bRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: messages
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if xOS_ENV_WIN

bool
CxThread::bPostMessage(
    HWND   a_hHwnd,
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_hHwnd,               false);
    /*DEBUG*/xASSERT_RET(false != ::IsWindow(a_hHwnd),   false);

    BOOL blRes = ::PostMessage(a_hHwnd, a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

bool
CxThread::bSendMessage(
    HWND   a_hHwnd,
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_hHwnd,               false);
    /*DEBUG*/xASSERT_RET(false != ::IsWindow(a_hHwnd),   false);

    (void)::SendMessage(a_hHwnd, a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    /*DEBUG*/xASSERT_RET(0UL == CxLastError::ulGet(), false);

    return true;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

bool
CxThread::bPostThreadMessage(
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);

    BOOL blRes = ::PostThreadMessage(ulGetId(), a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

bool
CxThread::bTryPostThreadMessage(
    uint_t  a_uiMsg,
    uint_t  a_uiParam1,
    long_t  a_liParam2,
    ulong_t a_ulAttemps,
    ulong_t a_ulAttempTimeout
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);

    for (ulong_t i = 0UL; i < a_ulAttemps; ++ i) {
        BOOL blRes = ::PostThreadMessage(ulGetId(), a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));

        xCHECK_RET(FALSE != blRes, true);
        xCHECK_DO (FALSE == blRes, CxCurrentThread::bSleep(a_ulAttempTimeout));
    }

    return false;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

bool
CxThread::bMessageWaitQueue(
    uint_t  a_uiMsg,
    uint_t *a_puiParam1,
    long_t *a_pliParam2
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
    /*DEBUG*/xASSERT_RET(0     <  a_uiMsg,               false);

    std::vector<uint_t> vuiMsg;
    vuiMsg.push_back(a_uiMsg);

    bool bRv = bMessageWaitQueue(vuiMsg, NULL, a_puiParam1, a_pliParam2);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

bool
CxThread::bMessageWaitQueue(
    const std::vector<uint_t> &a_cvuiMsg,
    uint_t                    *a_puiMsg,
    uint_t                    *a_puiParam1,
    long_t                    *a_pliParam2
) const
{
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
    /*DEBUG*/xASSERT_RET(false == a_cvuiMsg.empty(),     false);

    BOOL blRes  = FALSE;
    MSG  msgMsg = {0};

    while ((blRes = ::GetMessage(&msgMsg, NULL, 0, 0 ))) {
        /*DEBUG*/xASSERT_RET(- 1 != blRes, false);

        for (size_t i = 0; i < a_cvuiMsg.size(); ++ i) {
            xCHECK_DO(a_cvuiMsg.at(i) != msgMsg.message, continue);

            xPTR_ASSIGN(a_puiMsg,    msgMsg.message                      );
            xPTR_ASSIGN(a_puiParam1, static_cast<uint_t>( msgMsg.wParam ));
            xPTR_ASSIGN(a_pliParam2, static_cast<long_t>( msgMsg.lParam ));

            return true;
        }
    }

    return true;
}

#endif
//---------------------------------------------------------------------------


/****************************************************************************
*    public: priority
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
int
CxThread::_iGetPriorityMin() {
    int iRv = - 1;

#if   xOS_ENV_WIN
    iRv = THREAD_PRIORITY_IDLE;
#elif xOS_ENV_UNIX
    iRv = ::sched_get_priority_min(SCHED_FIFO);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRv, CxLastError::sFormat(iRv), 0);
#endif

    return iRv;
}
//---------------------------------------------------------------------------
/*static*/
int
CxThread::_iGetPriorityMax() {
    int iRv = - 1;

#if   xOS_ENV_WIN
    iRv = THREAD_PRIORITY_TIME_CRITICAL;
#elif xOS_ENV_UNIX
    iRv = ::sched_get_priority_max(SCHED_FIFO);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRv, CxLastError::sFormat(iRv), 0);
#endif

    return iRv;
}
//---------------------------------------------------------------------------
bool
CxThread::bSetPriority(
    const ExPriority &a_ctpPriority
) const
{
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);

    BOOL blRes = ::SetThreadPriority(_m_hThread.hGet(), a_ctpPriority);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    #if xOS_ENV_UNIX
        xCHECK_RET(false == CxSystemInfo::bIsUserAnAdmin(), false);
    #endif

    sched_param spParam = {0};

    spParam.sched_priority = a_ctpPriority;

    int iRv = ::pthread_setschedparam(ulGetId(), SCHED_FIFO, &spParam);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
CxThread::ExPriority
CxThread::tpGetPriority() const {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), tpError);
#elif xOS_ENV_UNIX

#endif

    CxThread::ExPriority tpRes = tpError;

#if   xOS_ENV_WIN
    tpRes = static_cast<ExPriority>( ::GetThreadPriority(_m_hThread.hGet()) );
    /*DEBUG*/xASSERT_RET(tpError != tpRes, tpError);
#elif xOS_ENV_UNIX
    sched_param spParam  = {0};
    int         iPolicy  = SCHED_FIFO;

    int iRv = ::pthread_getschedparam(ulGetId(), &iPolicy, &spParam);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRv, CxLastError::sFormat(iRv), tpError);

    tpRes = static_cast<ExPriority>( spParam.sched_priority );
#endif

    return tpRes;
}
//---------------------------------------------------------------------------
std::tstring_t
CxThread::sGetPriorityString() const {
    /*DEBUG*/// n/a

    int iRv = tpGetPriority();
    switch (iRv) {
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
bool
CxThread::bPriorityUp() const {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
#elif xOS_ENV_UNIX

#endif

    ExPriority tpOldLevel  = tpError;
    ExPriority tpiNewLevel = tpError;

    tpOldLevel = tpGetPriority();
    switch (tpOldLevel) {
        case tpIdle:            tpiNewLevel = tpLowest;             break;
        case tpLowest:          tpiNewLevel = tpBelowNormal;        break;
        case tpBelowNormal:     tpiNewLevel = tpNormal;             break;
        case tpNormal:          tpiNewLevel = tpAboveNormal;        break;
        case tpAboveNormal:     tpiNewLevel = tpHighest;            break;
        case tpHighest:         tpiNewLevel = tpTimeCritical;       break;
        case tpTimeCritical:    return true;                        break;

        default:                /*DEBUG*/xASSERT_RET(false, false); break;
    }

    return bSetPriority(tpiNewLevel);
}
//---------------------------------------------------------------------------
bool
CxThread::bPriorityDown() const {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);
#elif xOS_ENV_UNIX

#endif

    ExPriority tpOldLevel  = tpError;
    ExPriority tpiNewLevel = tpError;

    tpOldLevel = tpGetPriority();
    switch (tpOldLevel) {
        case tpIdle:            return true;                        break;
        case tpLowest:          tpiNewLevel = tpIdle;               break;
        case tpBelowNormal:     tpiNewLevel = tpLowest;             break;
        case tpNormal:          tpiNewLevel = tpBelowNormal;        break;
        case tpAboveNormal:     tpiNewLevel = tpNormal;             break;
        case tpHighest:         tpiNewLevel = tpAboveNormal;        break;
        case tpTimeCritical:    tpiNewLevel = tpHighest;            break;

        default:                /*DEBUG*/xASSERT_RET(false, false); break;
    }

    return bSetPriority(tpiNewLevel);
}
//---------------------------------------------------------------------------
bool
CxThread::bIsPriorityBoost() const {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);

    BOOL blDisablePriorityBoost = TRUE;

    BOOL blRes = ::GetThreadPriorityBoost(_m_hThread.hGet(), &blDisablePriorityBoost);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    //bDisablePriorityBoost == true  - dynamic boosting is disabled
    //bDisablePriorityBoost == false - normal behavior

    return ! blDisablePriorityBoost;
#elif xOS_ENV_UNIX
    return false;
#endif
}
//---------------------------------------------------------------------------
bool
CxThread::bSetPriorityBoost(
    const bool &a_cbIsEnabled
) const
{
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);

    BOOL blRes = ::SetThreadPriorityBoost(_m_hThread.hGet(), ! a_cbIsEnabled);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
#elif xOS_ENV_UNIX
    return false;
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: CPU
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxThread::bSetCpuAffinity(
    const int &a_ciProcNum
) const
{
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);

    DWORD_PTR dwMask;

    dwMask = 1UL << a_ciProcNum;

    DWORD_PTR uiRes = ::SetThreadAffinityMask(_m_hThread.hGet(), dwMask);
    /*DEBUG*/xASSERT_RET(0                       != uiRes, false);
    /*DEBUG*/xASSERT_RET(ERROR_INVALID_PARAMETER != uiRes, false);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        cpu_set_t csCpuSet;
    #elif xOS_FREEBSD
        cpuset_t  csCpuSet;
    #endif

    CPU_ZERO(&csCpuSet);
    (void)CPU_SET(a_ciProcNum, &csCpuSet);

    int iRv = ::pthread_setaffinity_np(ulGetId(), sizeof(csCpuSet), &csCpuSet);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRv, CxLastError::sFormat(iRv), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxThread::bSetCpuIdeal(
    const ulong_t &a_culIdealCpu    ///< value is zero-based
) const
{
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), false);

    DWORD ulRv = (DWORD) - 1;

    ulRv = ::SetThreadIdealProcessor(_m_hThread.hGet(), a_culIdealCpu);
    /*DEBUG*/xASSERT_RET((DWORD) - 1 != ulRv, false);
#elif xOS_ENV_UNIX
    return false;
#endif

    return true;
}
//---------------------------------------------------------------------------
ulong_t
CxThread::ulGetCpuIdeal() const {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), 0UL);
#elif xOS_ENV_UNIX

#endif

    ulong_t ulRv = (ulong_t) - 1;

#if   xOS_ENV_WIN
    ulRv = ::SetThreadIdealProcessor(_m_hThread.hGet(), MAXIMUM_PROCESSORS);
    /*DEBUG*/xASSERT_RET((ulong_t) - 1 != ulRv, 0UL);
#elif xOS_ENV_UNIX

#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxThread::ulGetCpuCount() {
    ulong_t ulRv = CxSystemInfo::ulGetNumOfCpus();
    xCHECK_RET(ulRv < 1UL || ulRv > 32UL, 1UL);

    return ulRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: other
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxThread::handle_t
CxThread::hGet() const {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), handle_t());

    return _m_hThread.hGet();
#elif xOS_ENV_UNIX
    return _m_hThread;
#endif
}
//---------------------------------------------------------------------------
CxThread::id_t
CxThread::ulGetId() const {
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), 0);
#elif xOS_ENV_UNIX

#endif

    return _m_ulId;
}
//---------------------------------------------------------------------------
bool
CxThread::bIsCurrent() const {
    /*DEBUG*/

    return CxCurrentThread::bIsCurrent( CxCurrentThread::ulGetId() );
}
//---------------------------------------------------------------------------
ulong_t
CxThread::ulGetExitStatus() const {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(false != _m_hThread.bIsValid(), 0UL);

    BOOL blRes = ::GetExitCodeThread(_m_hThread.hGet(), &ulRv);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, ulRv);
#elif xOS_ENV_UNIX
    ulRv = _m_uiExitStatus;
#endif

    return ulRv;
}
//bool
///*CxThread::*/bPost() {
//
//long_t sys_tgkill (int tgid, int pid, int sig);
//}

//---------------------------------------------------------------------------
bool
CxThread::bSetDebugName(
    const std::tstring_t &a_csName
) const
{
    /////*DEBUG*/xASSERT_RET(0  < _m_ulId,         false);
    /////*DEBUG*/xASSERT_RET(32 > a_csName.size(), false); //MAX_NAME_SIZE 32

    //// TODO: xCHECK_RET(false == CxDebugger().bIsActive(), true);

#if   xOS_ENV_WIN
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
        tiInfo.pszName    = a_csName.c_str();
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
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int iRv = ::prctl(PR_SET_NAME, a_csName.c_str(), 0, 0, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, false);
    #elif xOS_FREEBSD
         (void)pthread_set_name_np(ulGetId(), a_csName.c_str());
    #endif
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
CxThread::handle_t
CxThread::hOpen(
    const ulong_t &a_culAccess,
    const bool    &a_cbInheritHandle,
    const ulong_t &a_culId
)
{
    /*DEBUG*///ulAccess       - n/a
    /*DEBUG*///bInheritHandle - n/a
    /*DEBUG*/xASSERT_RET(0UL < a_culId, handle_t());

#if   xOS_ENV_WIN
    handle_t hRv = ::OpenThread(a_culAccess, a_cbInheritHandle, a_culId);
    /*DEBUG*/xASSERT_RET(NULL != hRv, NULL);
#elif xOS_ENV_UNIX
    //TODO: hOpen
    handle_t hRv = 0;
#endif

    return hRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected: events
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*virtual*/
uint_t
CxThread::uiOnRun(
    void *a_pvParam
) /* = 0*/
{
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_MSG_RET(false, xT("It's virtual method"), 0U);

    uint_t uiRes = 0U;

    #if xTEMP_DISABLED
        for ( ; ; ) {
            bool bRv = bIsTimeToExit();
            xCHECK_DO(true == bRv, break);

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
bool
CxThread::bIsTimeToExit() {
    /*DEBUG*/// n/a

    bool bRv = false;

    //-------------------------------------
    //exit
    bRv = bIsExited();
    xCHECK_RET(true == bRv, true);

    //-------------------------------------
    //pause / resume
    bRv = bIsPaused();
    xCHECK_RET(true == bRv, ! _bWaitResumption());

    //-------------------------------------
    //flags
    // n/a

    return false;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
CxThread::exit_status_t xSTDCALL
CxThread::_s_uiJobEntry(
    void *pvParam
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvParam, 0);

    uint_t uiRes = 0U;
    bool   bRv  = false;     xUNUSED(bRv);

    CxThread *pthThis = static_cast<CxThread *>( pvParam );
    /*DEBUG*/xASSERT_RET(NULL != pthThis, 0);

    //-------------------------------------
    // handle must be valid
    ////CxCurrentThread::bSleep(500UL);

    CxEvent::ExObjectState osRes = pthThis->_m_pevStarter->osWait(5000UL);   // not infinite timeout
    xTEST_EQ(CxEvent::osSignaled, osRes);
    /*DEBUG*/xASSERT_RET(CxEvent::osSignaled == osRes, exit_status_t());

    xPTR_DELETE(pthThis->_m_pevStarter);

    //-------------------------------------
    // if created suspended thread - wait for resumption
    xCHECK_DO(true == pthThis->bIsPaused(), (void)pthThis->_bWaitResumption());

    {
        //-------------------------------------
        // begin of thread function
        try {
            #if xTODO
                pthThis->_vHandler_OnEnter(pthThis);
            #endif
        }
        catch (...) {
            /*DEBUG*/xASSERT(false);
        }

        //-------------------------------------
        // executing of thread function
        try {
            uiRes = pthThis->uiOnRun(pthThis->_m_pvParam);
        }
        catch (std::exception &e) {
            std::string asWhat = e.what();
            xASSERT_MSG(false, xS2TS(asWhat).c_str());
        }
        catch (...) {
            /*DEBUG*/xASSERT(false);
        }

        //-------------------------------------
        // end of thread function
        try {
            #if xTODO
                pthThis->_vHandler_OnExit(pthThis);
            #endif
        }
        catch (...) {
            /*DEBUG*/xASSERT(false);
        }
    }

    //-------------------------------------
    // clean members (is need to close???)
#if xOS_ENV_WIN
    bRv = pthThis->_m_hThread.bClose();
    /*DEBUG*/xASSERT(true == bRv);
#elif xOS_ENV_UNIX
    //TODO: _m_hThread.bClose()
#endif

    pthThis->_m_ulId         = 0UL;
    pthThis->_m_uiExitStatus = uiRes;    //???
    pthThis->_m_pvParam      = NULL;
    // pthThis->_m_cbIsAutoDelete - n/a

    //-------------------------------------
    // flags
    pthThis->_vSetStatesDefault();

#if   xOS_ENV_WIN
    exit_status_t esExitStatus = pthThis->_m_uiExitStatus;
#elif xOS_ENV_UNIX
    exit_status_t esExitStatus = &pthThis->_m_uiExitStatus;
#endif

    //-------------------------------------
    // auto delete oneself
    xCHECK_DO(true == pthThis->_m_cbIsAutoDelete, xPTR_DELETE(pthThis));

    return esExitStatus;
}
//---------------------------------------------------------------------------
bool
CxThread::_bWaitResumption() {
    /*DEBUG*/

    //-------------------------------------
    // flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a

    CxEvent::ExObjectState osRes = _m_evPause.osWait();
    /*DEBUG*/xASSERT_RET(CxEvent::osFailed   != osRes, false);
    /*DEBUG*/xASSERT_RET(CxEvent::osTimeout  != osRes, false);
    /*DEBUG*/xASSERT_RET(CxEvent::osSignaled == osRes, false);

    return (CxEvent::osSignaled == osRes);
}
//---------------------------------------------------------------------------
void
CxThread::_vSetStatesDefault() {
    /*DEBUG*/// n/a

    //-------------------------------------
    // flags
    _m_bIsCreated  = false;
    _m_bIsRunning  = false;
    /*_m_bIsPaused*/// n/a
    /*_m_bIsExited*/// n/a
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
