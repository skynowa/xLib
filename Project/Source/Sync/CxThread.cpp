/**
 * \file  CxThread.cpp
 * \brief thread
 */


#include <xLib/Sync/CxThread.h>

#include <xLib/Common/CxString.h>
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
/* virtual */
CxThread::~CxThread() {
    

    //-------------------------------------
    // close thread, if it still running
    bool bRv = bIsRunning();
    if (true == bRv) {
        vExit();

        // TODO: CxThread::~CxThread()
        //if (false == bRv) {
        //    vKill(_ms_culExitTimeout);
        //    if (false == bRv) {
        //        xTEST_FAIL;
        //    }
        //}
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
void
CxThread::vCreate(
    const bool   &a_cbIsPaused,
    const uint_t &a_cuiStackSize,
    void         *a_pvParam
)
{
#if   xOS_ENV_WIN
    xTEST_EQ(false, _m_hThread.bIsValid());
#elif xOS_ENV_UNIX

#endif
    // cbIsPaused   - n/a
    // cuiStackSize - n/a
    // pvParam      - n/a

    _m_pvParam = a_pvParam;

    //-------------------------------------
    // events
    _m_pevStarter = new CxEvent(true, false);
    xTEST_PTR(_m_pevStarter);

    _m_pevStarter->vCreate();
    _m_evPause.vCreate();
    _m_evExit.vCreate();

    //-------------------------------------
    // start
#if   xOS_ENV_WIN
    id_t ulId = 0UL;

    HANDLE hRv = reinterpret_cast<HANDLE>( ::_beginthreadex(NULL, a_cuiStackSize, _s_uiJobEntry, this, 0U, (uint_t *)&ulId) );
    xTEST_DIFF(xNATIVE_HANDLE_INVALID, hRv);
    xTEST_LESS(0UL, ulId);

    _m_hThread.vSet(hRv);
    xTEST_EQ(true, _m_hThread.bIsValid());

    _m_ulId = ulId;
#elif xOS_ENV_UNIX
    int            iRv = - 1;
    id_t           ulId;
    pthread_attr_t paAttributes; // n/a - {{0}}

    iRv = ::pthread_attr_init(&paAttributes);
    xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));

    iRv = ::pthread_attr_setdetachstate(&paAttributes, PTHREAD_CREATE_JOINABLE); //PTHREAD_CREATE_DETACHED
    xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));

    if (0 != a_cuiStackSize) {
        //TODO: size_t size = PTHREAD_STACK_MIN + 0x4000;
        iRv = ::pthread_attr_setstacksize(&paAttributes, a_cuiStackSize);
        xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
    }

    iRv = ::pthread_create(&ulId, &paAttributes, &_s_uiJobEntry, this);
    xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
    xTEST_MSG_EQ(true, 0UL < ulId, CxLastError::sFormat(iRv));

    iRv = ::pthread_attr_destroy(&paAttributes);
    xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));

    _m_hThread = ulId;  // TODO: is it right?
    _m_ulId    = ulId;
#endif
    xTEST_EQ(false, CxCurrentThread::bIsCurrent(_m_ulId));

    //-------------------------------------
    // flags
    {
        _m_bIsCreated = true;
        _m_bIsRunning = true;
        /*_m_bIsPaused*/// n/a

        if (false != a_cbIsPaused) {
            vPause();
        } else {
            vResume();
        }

        /*_m_bIsExited*/// n/a
    }

    //-------------------------------------
    // construction is complete, start job entry
    _m_pevStarter->vSet();
}
//---------------------------------------------------------------------------
void
CxThread::vResume() {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
#elif xOS_ENV_UNIX

#endif

    _m_evPause.vSet();

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a
}
//---------------------------------------------------------------------------
void
CxThread::vPause() {
#if   xOS_ENV_WIN
    xTEST_MSG_EQ(true, _m_hThread.bIsValid(), CxString::string_cast(_m_hThread.hGet()));
#elif xOS_ENV_UNIX

#endif

    _m_evPause.vReset();

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a
}
//---------------------------------------------------------------------------
void
CxThread::vExit() {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
#elif xOS_ENV_UNIX

#endif

    _m_evExit.vSet();

    //-------------------------------------
    //flags
    /*_m_bIsExited*///  n/a
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*/    xCHECK_DO(true == bIsPaused(), vResume()); //если поток приостановленный (bPause) - возобновляем
                                                                   //если ожидает чего-то
}
//---------------------------------------------------------------------------
void
CxThread::vKill(
    const ulong_t &a_culTimeout
)
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
    //ulTimeout - n/a

    _m_uiExitStatus = 0U;

    BOOL blRes = ::TerminateThread(_m_hThread.hGet(), _m_uiExitStatus);
    xTEST_DIFF(FALSE, blRes);

    xFOREVER {
        ulRv = ulGetExitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        CxCurrentThread::vSleep(a_culTimeout);
    }
#elif xOS_ENV_UNIX
    int iRv = ::pthread_kill(_m_ulId, SIGALRM);
    xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));

    CxCurrentThread::vSleep(a_culTimeout);
#endif

    //-------------------------------------
    // clean members
#if   xOS_ENV_WIN
    _m_hThread.vClose();
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
}
//---------------------------------------------------------------------------
void
CxThread::vWait(
    const ulong_t &a_culTimeout
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
    //ulTimeout - n/a

    //-------------------------------------
    //flags
    //?????????

    xTEST_DIFF(CxCurrentThread::ulId(), _m_ulId);
    xCHECK_DO(CxCurrentThread::ulId() == _m_ulId, return);

    DWORD ulRv = ::WaitForSingleObject(_m_hThread.hGet(), a_culTimeout);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);
#elif xOS_ENV_UNIX
    // TODO: thread must not be detached
    // FIX:  a_culTimeout
    int iRv = ::pthread_join(_m_ulId, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: flags
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxThread::bIsCreated() const {
    // _m_hThread - n/a

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
    // _m_hThread - n/a

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
    // _m_hThread - n/a

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
    // _m_hThread - n/a

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
#if   xOS_ENV_WIN

void
CxThread::vPostMessage(
    HWND   a_hHwnd,
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    xTEST_EQ(true, _m_hThread.bIsValid());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, a_hHwnd);
    xTEST_DIFF(FALSE, ::IsWindow(a_hHwnd));

    BOOL blRes = ::PostMessage(a_hHwnd, a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    xTEST_DIFF(FALSE, blRes);
}

#endif
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

void
CxThread::vSendMessage(
    HWND   a_hHwnd,
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    xTEST_EQ(true, _m_hThread.bIsValid());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, a_hHwnd);
    xTEST_DIFF(FALSE, ::IsWindow(a_hHwnd));

    (void)::SendMessage(a_hHwnd, a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    xTEST_EQ(0UL, CxLastError::ulGet());
}

#endif
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

void
CxThread::vPostThreadMessage(
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    xTEST_EQ(true, _m_hThread.bIsValid());

    BOOL blRes = ::PostThreadMessage(ulGetId(), a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    xTEST_DIFF(FALSE, blRes);
}

#endif
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

bool
CxThread::bTryPostThreadMessage(
    uint_t  a_uiMsg,
    uint_t  a_uiParam1,
    long_t  a_liParam2,
    ulong_t a_ulAttemps,
    ulong_t a_ulAttempTimeout
) const
{
    xTEST_EQ(true, _m_hThread.bIsValid());

    for (ulong_t i = 0UL; i < a_ulAttemps; ++ i) {
        BOOL blRes = ::PostThreadMessage(ulGetId(), a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));

        xCHECK_RET(FALSE != blRes, true);
        xCHECK_DO (FALSE == blRes, CxCurrentThread::vSleep(a_ulAttempTimeout));
    }

    return false;
}

#endif
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

void
CxThread::vMessageWaitQueue(
    uint_t  a_uiMsg,
    uint_t *a_puiParam1,
    long_t *a_pliParam2
) const
{
    xTEST_EQ(true, _m_hThread.bIsValid());
    xTEST_LESS(0U, a_uiMsg);

    std::vector<uint_t> vuiMsg;
    vuiMsg.push_back(a_uiMsg);

    vMessageWaitQueue(vuiMsg, NULL, a_puiParam1, a_pliParam2);
}

#endif
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

void
CxThread::vMessageWaitQueue(
    const std::vector<uint_t> &a_cvuiMsg,
    uint_t                    *a_puiMsg,
    uint_t                    *a_puiParam1,
    long_t                    *a_pliParam2
) const
{
    xTEST_EQ(true, _m_hThread.bIsValid());
    xTEST_EQ(false, a_cvuiMsg.empty());

    BOOL blRes  = FALSE;
    MSG  msgMsg = {0};

    while ((blRes = ::GetMessage(&msgMsg, NULL, 0, 0 ))) {
        xTEST_DIFF(- 1, blRes);

        for (size_t i = 0; i < a_cvuiMsg.size(); ++ i) {
            xCHECK_DO(a_cvuiMsg.at(i) != msgMsg.message, continue);

            CxUtils::ptrAssignT(a_puiMsg,    msgMsg.message                      );
            CxUtils::ptrAssignT(a_puiParam1, static_cast<uint_t>( msgMsg.wParam ));
            CxUtils::ptrAssignT(a_pliParam2, static_cast<long_t>( msgMsg.lParam ));

            break;
        }
    }
}

#endif
//---------------------------------------------------------------------------


/****************************************************************************
*    public: priority
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
int
CxThread::_iPriorityMin() {
    int iRv = - 1;

#if   xOS_ENV_WIN
    iRv = THREAD_PRIORITY_IDLE;
#elif xOS_ENV_UNIX
    iRv = ::sched_get_priority_min(SCHED_FIFO);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::sFormat(iRv));
#endif

    return iRv;
}
//---------------------------------------------------------------------------
/* static */
int
CxThread::_iPriorityMax() {
    int iRv = - 1;

#if   xOS_ENV_WIN
    iRv = THREAD_PRIORITY_TIME_CRITICAL;
#elif xOS_ENV_UNIX
    iRv = ::sched_get_priority_max(SCHED_FIFO);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::sFormat(iRv));
#endif

    return iRv;
}
//---------------------------------------------------------------------------
void
CxThread::vSetPriority(
    const ExPriority &a_ctpPriority
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());

    BOOL blRes = ::SetThreadPriority(_m_hThread.hGet(), a_ctpPriority);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    if (false == CxSystemInfo::bIsUserAnAdmin()) {
        CxTracer() << xT("::: xLib: warning (CxThread::vSetPriority fail, need root) :::");
        return;
    }

    sched_param spParam = {0};

    spParam.sched_priority = a_ctpPriority;

    int iRv = ::pthread_setschedparam(ulGetId(), SCHED_FIFO, &spParam);
    xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));
#endif
}
//---------------------------------------------------------------------------
CxThread::ExPriority
CxThread::tpPriority() const {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
#elif xOS_ENV_UNIX

#endif

    CxThread::ExPriority tpRes = tpError;

#if   xOS_ENV_WIN
    tpRes = static_cast<ExPriority>( ::GetThreadPriority(_m_hThread.hGet()) );
    xTEST_DIFF(tpError, tpRes);
#elif xOS_ENV_UNIX
    sched_param spParam  = {0};
    int         iPolicy  = SCHED_FIFO;

    int iRv = ::pthread_getschedparam(ulGetId(), &iPolicy, &spParam);
    xTEST_MSG_EQ(0, iRv, CxLastError::sFormat(iRv));

    tpRes = static_cast<ExPriority>( spParam.sched_priority );
#endif

    return tpRes;
}
//---------------------------------------------------------------------------
std::tstring_t
CxThread::sPriorityString() const {
    // n/a

    int iRv = tpPriority();
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
void
CxThread::vPriorityUp() const {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
#elif xOS_ENV_UNIX

#endif

    ExPriority tpOldLevel  = tpError;
    ExPriority tpiNewLevel = tpError;

    tpOldLevel = tpPriority();
    switch (tpOldLevel) {
        case tpIdle:            tpiNewLevel = tpLowest;         break;
        case tpLowest:          tpiNewLevel = tpBelowNormal;    break;
        case tpBelowNormal:     tpiNewLevel = tpNormal;         break;
        case tpNormal:          tpiNewLevel = tpAboveNormal;    break;
        case tpAboveNormal:     tpiNewLevel = tpHighest;        break;
        case tpHighest:         tpiNewLevel = tpTimeCritical;   break;
        case tpTimeCritical:    return;                         break;

        default:                xTEST_FAIL;            break;
    }

    vSetPriority(tpiNewLevel);
}
//---------------------------------------------------------------------------
void
CxThread::vPriorityDown() const {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
#elif xOS_ENV_UNIX

#endif

    ExPriority tpOldLevel  = tpError;
    ExPriority tpiNewLevel = tpError;

    tpOldLevel = tpPriority();
    switch (tpOldLevel) {
        case tpIdle:            return;                         break;
        case tpLowest:          tpiNewLevel = tpIdle;           break;
        case tpBelowNormal:     tpiNewLevel = tpLowest;         break;
        case tpNormal:          tpiNewLevel = tpBelowNormal;    break;
        case tpAboveNormal:     tpiNewLevel = tpNormal;         break;
        case tpHighest:         tpiNewLevel = tpAboveNormal;    break;
        case tpTimeCritical:    tpiNewLevel = tpHighest;        break;

        default:                xTEST_FAIL;            break;
    }

    vSetPriority(tpiNewLevel);
}
//---------------------------------------------------------------------------
bool
CxThread::bIsPriorityBoost() const {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());

    BOOL blDisablePriorityBoost = TRUE;

    BOOL blRes = ::GetThreadPriorityBoost(_m_hThread.hGet(), &blDisablePriorityBoost);
    xTEST_DIFF(FALSE, blRes);

    //bDisablePriorityBoost == true  - dynamic boosting is disabled
    //bDisablePriorityBoost == false - normal behavior

    return ! blDisablePriorityBoost;
#elif xOS_ENV_UNIX
    return false;
#endif
}
//---------------------------------------------------------------------------
void
CxThread::vSetPriorityBoost(
    const bool &a_cbIsEnabled
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());

    BOOL blRes = ::SetThreadPriorityBoost(_m_hThread.hGet(), ! a_cbIsEnabled);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    return;
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: CPU
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxThread::vSetCpuAffinity(
    const int &a_ciProcNum
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());

    DWORD_PTR dwMask;

    dwMask = 1UL << a_ciProcNum;

    DWORD_PTR uiRes = ::SetThreadAffinityMask(_m_hThread.hGet(), dwMask);
    xTEST_PTR(uiRes);
    xTEST_EQ(true, ERROR_INVALID_PARAMETER != uiRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        cpu_set_t csCpuSet;
    #elif xOS_FREEBSD
        cpuset_t  csCpuSet;
    #endif

    CPU_ZERO(&csCpuSet);
    (void)CPU_SET(a_ciProcNum, &csCpuSet);

    int iRv = ::pthread_setaffinity_np(ulGetId(), sizeof(csCpuSet), &csCpuSet);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::sFormat(iRv));
#endif
}
//---------------------------------------------------------------------------
void
CxThread::vSetCpuIdeal(
    const ulong_t &a_culIdealCpu    ///< value is zero-based
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());

    DWORD ulRv = (DWORD) - 1;

    ulRv = ::SetThreadIdealProcessor(_m_hThread.hGet(), a_culIdealCpu);
    xTEST_DIFF((DWORD) - 1, ulRv);
#elif xOS_ENV_UNIX
    xNOT_IMPLEMENTED;
#endif
}
//---------------------------------------------------------------------------
ulong_t
CxThread::ulCpuIdeal() const {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
#elif xOS_ENV_UNIX

#endif

    ulong_t ulRv = (ulong_t) - 1;

#if   xOS_ENV_WIN
    ulRv = ::SetThreadIdealProcessor(_m_hThread.hGet(), MAXIMUM_PROCESSORS);
    xTEST_DIFF((ulong_t) - 1, ulRv);
#elif xOS_ENV_UNIX

#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
ulong_t
CxThread::ulCpuCount() {
    ulong_t ulRv = CxSystemInfo::ulNumOfCpus();
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
CxThread::hHandle() const {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());

    return _m_hThread.hGet();
#elif xOS_ENV_UNIX
    return _m_hThread;
#endif
}
//---------------------------------------------------------------------------
CxThread::id_t
CxThread::ulGetId() const {
#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());
#elif xOS_ENV_UNIX

#endif

    return _m_ulId;
}
//---------------------------------------------------------------------------
bool
CxThread::bIsCurrent() const {
    

    return CxCurrentThread::bIsCurrent( CxCurrentThread::ulId() );
}
//---------------------------------------------------------------------------
ulong_t
CxThread::ulGetExitStatus() const {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.bIsValid());

    BOOL blRes = ::GetExitCodeThread(_m_hThread.hGet(), &ulRv);
    xTEST_DIFF(FALSE, blRes);
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
void
CxThread::vSetDebugName(
    const std::tstring_t &a_csName
) const
{
    ////xTEST_LESS(0, _m_ulId);
    ////xTEST_GR(32, a_csName.size()); //MAX_NAME_SIZE 32

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
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
         (void)pthread_set_name_np(ulGetId(), a_csName.c_str());
    #endif
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
CxThread::handle_t
CxThread::hOpen(
    const ulong_t &a_culAccess,
    const bool    &a_cbInheritHandle,
    const ulong_t &a_culId
)
{
    //ulAccess       - n/a
    //bInheritHandle - n/a
    xTEST_LESS(0UL, a_culId);

#if   xOS_ENV_WIN
    handle_t hRv = ::OpenThread(a_culAccess, a_cbInheritHandle, a_culId);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
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
/* virtual */
uint_t
CxThread::uiOnRun(
    void *a_pvParam
) /* = 0*/
{
    // n/a
    xTEST_MSG_FAIL(xT("It's virtual method"));

    uint_t uiRes = 0U;

    #if xTEMP_DISABLED
        xFOREVER {
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
    // n/a

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
/* static */
CxThread::exit_status_t xSTDCALL
CxThread::_s_uiJobEntry(
    void *pvParam
)
{
    xTEST_PTR(pvParam);

    uint_t uiRes = 0U;
    bool   bRv  = false;     xUNUSED(bRv);

    CxThread *pthThis = static_cast<CxThread *>( pvParam );
    xTEST_PTR(pthThis);

    //-------------------------------------
    // handle must be valid
    ////CxCurrentThread::bSleep(500UL);

    CxEvent::ExObjectState osRes = pthThis->_m_pevStarter->osWait(10000UL);   // not infinite timeout
    xTEST_EQ(CxEvent::osSignaled, osRes);

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
            xTEST_FAIL;
        }

        //-------------------------------------
        // executing of thread function
        try {
            uiRes = pthThis->uiOnRun(pthThis->_m_pvParam);
        }
        catch (std::exception &e) {
            std::string asWhat = e.what();
            xTEST_MSG_FAIL(xS2TS(asWhat));
        }
        catch (...) {
            xTEST_FAIL;
        }

        //-------------------------------------
        // end of thread function
        try {
            #if xTODO
                pthThis->_vHandler_OnExit(pthThis);
            #endif
        }
        catch (...) {
            xTEST_FAIL;
        }
    }

    //-------------------------------------
    // clean members (is need to close???)
#if   xOS_ENV_WIN
    pthThis->_m_hThread.vClose();
#elif xOS_ENV_UNIX
    // TODO: _m_hThread.vClose()
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
    

    //-------------------------------------
    // flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a

    CxEvent::ExObjectState osRes = _m_evPause.osWait();
    xTEST_DIFF(CxEvent::osFailed, osRes);
    xTEST_DIFF(CxEvent::osTimeout, osRes);
    xTEST_EQ(CxEvent::osSignaled, osRes);

    return (CxEvent::osSignaled == osRes);
}
//---------------------------------------------------------------------------
void
CxThread::_vSetStatesDefault() {
    // n/a

    //-------------------------------------
    // flags
    _m_bIsCreated  = false;
    _m_bIsRunning  = false;
    /*_m_bIsPaused*/// n/a
    /*_m_bIsExited*/// n/a
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
