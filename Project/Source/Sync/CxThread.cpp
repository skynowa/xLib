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

#if !xOS_ENV_WIN
    // constants
    culong_t CxThread::_ms_culStillActiveTimeout;
    culong_t CxThread::_ms_culExitTimeout;
#endif


/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxThread::CxThread(
    cbool_t &a_cbIsAutoDelete
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
//------------------------------------------------------------------------------
/* virtual */
CxThread::~CxThread() {


    //-------------------------------------
    // close thread, if it still running
    bool_t bRv = isRunning();
    if (bRv) {
        exit();

        // TODO: CxThread::~CxThread()
        //if (!bRv) {
        //    vKill(_ms_culExitTimeout);
        //    if (!bRv) {
        //        xTEST_FAIL;
        //    }
        //}
    }

    //-------------------------------------
    // state flags
    _setStatesDefault();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: actions
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxThread::create(
    cbool_t &a_cbIsPaused,
    cuint_t &a_cuiStackSize,
    void_t  *a_pvParam
)
{
#if xOS_ENV_WIN
    xTEST_EQ(false, _m_hThread.isValid());
#else

#endif
    // cbIsPaused   - n/a
    // cuiStackSize - n/a
    // pvParam      - n/a

    _m_pvParam = a_pvParam;

    //-------------------------------------
    // events
    _m_pevStarter = new CxEvent(true, false);
    xTEST_PTR(_m_pevStarter);

    _m_pevStarter->create();
    _m_evPause.create();
    _m_evExit.create();

    //-------------------------------------
    // start
#if xOS_ENV_WIN
    id_t id = 0UL;

    HANDLE hRv = reinterpret_cast<HANDLE>( ::_beginthreadex(NULL, a_cuiStackSize, _s_jobEntry, this, 0U, (uint_t *)&id) );
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
    xTEST_LESS(0UL, id);

    _m_hThread.set(hRv);
    xTEST_EQ(true, _m_hThread.isValid());

    _m_ulId = id;
#else
    int_t          iRv = - 1;
    id_t           id;
    pthread_attr_t paAttributes; // n/a - {{0}}

    iRv = ::pthread_attr_init(&paAttributes);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_attr_setdetachstate(&paAttributes, PTHREAD_CREATE_JOINABLE); //PTHREAD_CREATE_DETACHED
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    if (0 != a_cuiStackSize) {
        //TODO: size_t size = PTHREAD_STACK_MIN + 0x4000;
        iRv = ::pthread_attr_setstacksize(&paAttributes, a_cuiStackSize);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_create(&id, &paAttributes, &_s_jobEntry, this);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    xTEST_MSG_EQ(true, 0UL < id, CxLastError::format(iRv));

    iRv = ::pthread_attr_destroy(&paAttributes);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    _m_hThread = id;  // TODO: is it right?
    _m_ulId    = id;
#endif
    xTEST_EQ(false, CxCurrentThread::isCurrent(_m_ulId));

    //-------------------------------------
    // flags
    {
        _m_bIsCreated = true;
        _m_bIsRunning = true;
        /*_m_bIsPaused*/// n/a

        if (a_cbIsPaused) {
            pause();
        } else {
            resume();
        }

        /*_m_bIsExited*/// n/a
    }

    //-------------------------------------
    // construction is complete, start job entry
    _m_pevStarter->set();
}
//------------------------------------------------------------------------------
void_t
CxThread::resume() {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
#else

#endif

    _m_evPause.set();

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a
}
//------------------------------------------------------------------------------
void_t
CxThread::pause() {
#if xOS_ENV_WIN
    xTEST_MSG_EQ(true, _m_hThread.isValid(), CxString::cast(_m_hThread.get()));
#else

#endif

    _m_evPause.reset();

    //-------------------------------------
    //flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a
}
//------------------------------------------------------------------------------
void_t
CxThread::exit() {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
#else

#endif

    _m_evExit.set();

    //-------------------------------------
    //flags
    /*_m_bIsExited*///  n/a
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*/    xCHECK_DO(isPaused(), resume()); //если поток приостановленный (bPause) - возобновляем
                                                                   //если ожидает чего-то
}
//------------------------------------------------------------------------------
void_t
CxThread::kill(
    culong_t &a_culTimeout
)
{
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
    //ulTimeout - n/a

    _m_uiExitStatus = 0U;

    BOOL blRes = ::TerminateThread(_m_hThread.get(), _m_uiExitStatus);
    xTEST_DIFF(FALSE, blRes);

    xFOREVER {
        ulRv = exitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        CxCurrentThread::sleep(a_culTimeout);
    }
#else
    int_t iRv = ::pthread_kill(_m_ulId, SIGALRM);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    CxCurrentThread::sleep(a_culTimeout);
#endif

    //-------------------------------------
    // clean members
#if xOS_ENV_WIN
    _m_hThread.close();
#else
    _m_hThread = 0UL;
#endif

    _m_ulId         = 0UL;
    _m_uiExitStatus = ulRv;    //saving value
    _m_pvParam      = NULL;
    //_m_cbIsAutoDelete - n/a

    //-------------------------------------
    //flags
    _setStatesDefault();
}
//------------------------------------------------------------------------------
void_t
CxThread::wait(
    culong_t &a_culTimeout
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
    //ulTimeout - n/a

    //-------------------------------------
    //flags
    //?????????

    xTEST_DIFF(CxCurrentThread::id(), _m_ulId);
    xCHECK_DO(CxCurrentThread::id() == _m_ulId, return);

    DWORD ulRv = ::WaitForSingleObject(_m_hThread.get(), a_culTimeout);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);
#else
    // TODO: thread must not be detached
    // FIX:  a_culTimeout
    int_t iRv = ::pthread_join(_m_ulId, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: flags
*
*******************************************************************************/

//------------------------------------------------------------------------------
bool_t
CxThread::isCreated() const {
    // _m_hThread - n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = (_m_bIsCreated) && (_m_hThread.isValid());
#else
    bRv = (_m_bIsCreated) && (0UL   != _m_hThread);
#endif

    return bRv;
}
//------------------------------------------------------------------------------
bool_t
CxThread::isRunning() const {
    // _m_hThread - n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    DWORD ulRv = 0UL;

    (void_t)::GetExitCodeThread(_m_hThread.get(), &ulRv);

    bool_t bCond1 = ( false         != _m_hThread.isValid()                         );
    bool_t bCond2 = ( 0UL           <  _m_ulId                                       );
    bool_t bCond3 = ( true          == _m_bIsRunning                                 );
    bool_t bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_m_hThread.get(), 0UL) );
    bool_t bCond5 = ( STILL_ACTIVE  == ulRv                                          );

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5;
#else
    bool_t bCond1 = ( 0UL           != _m_hThread                                    );
    bool_t bCond2 = ( 0UL           <  _m_ulId                                       );
    bool_t bCond3 = ( true          == _m_bIsRunning                                 );

    #if xTODO
        bool_t bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_m_hThread.get(), 0UL) );
        bool_t bCond5 = ( STILL_ACTIVE  == ulRv                                         );
    #endif

    bRv = bCond1 && bCond2 && bCond3 /*&& bCond4 && bCond5*/;
#endif

    return bRv;
}
//------------------------------------------------------------------------------
bool_t
CxThread::isPaused() {
    // _m_hThread - n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = !_m_evPause.isSignaled() && _m_hThread.isValid();
#else
    bRv = !_m_evPause.isSignaled() /*&& (0UL   != _m_hThread)*/;
#endif

    return bRv;
}
//------------------------------------------------------------------------------
bool_t
CxThread::isExited() {
    // _m_hThread - n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = _m_evExit.isSignaled() && _m_hThread.isValid();
#else
    bRv = _m_evExit.isSignaled() && (0UL   != _m_hThread);
#endif

    return bRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: messages
*
*******************************************************************************/

//------------------------------------------------------------------------------
#if xOS_ENV_WIN

void_t
CxThread::postMessage(
    HWND   a_hHwnd,
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    xTEST_EQ(true, _m_hThread.isValid());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, a_hHwnd);
    xTEST_DIFF(FALSE, ::IsWindow(a_hHwnd));

    BOOL blRes = ::PostMessage(a_hHwnd, a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    xTEST_DIFF(FALSE, blRes);
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

void_t
CxThread::sendMessage(
    HWND   a_hHwnd,
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    xTEST_EQ(true, _m_hThread.isValid());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, a_hHwnd);
    xTEST_DIFF(FALSE, ::IsWindow(a_hHwnd));

    (void_t)::SendMessage(a_hHwnd, a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    xTEST_EQ(0UL, CxLastError::get());
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

void_t
CxThread::postThreadMessage(
    uint_t a_uiMsg,
    uint_t a_uiParam1,
    long_t a_liParam2
) const
{
    xTEST_EQ(true, _m_hThread.isValid());

    BOOL blRes = ::PostThreadMessage(id(), a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));
    xTEST_DIFF(FALSE, blRes);
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

bool_t
CxThread::tryPostThreadMessage(
    uint_t  a_uiMsg,
    uint_t  a_uiParam1,
    long_t  a_liParam2,
    ulong_t a_ulAttemps,
    ulong_t a_ulAttempTimeout
) const
{
    xTEST_EQ(true, _m_hThread.isValid());

    for (ulong_t i = 0UL; i < a_ulAttemps; ++ i) {
        BOOL blRes = ::PostThreadMessage(id(), a_uiMsg, static_cast<WPARAM>( a_uiParam1 ), static_cast<LPARAM>( a_liParam2 ));

        xCHECK_RET(FALSE != blRes, true);
        xCHECK_DO (FALSE == blRes, CxCurrentThread::sleep(a_ulAttempTimeout));
    }

    return false;
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

void_t
CxThread::messageWaitQueue(
    uint_t  a_uiMsg,
    uint_t *a_puiParam1,
    long_t *a_pliParam2
) const
{
    xTEST_EQ(true, _m_hThread.isValid());
    xTEST_LESS(0U, a_uiMsg);

    std::vector<uint_t> vuiMsg;
    vuiMsg.push_back(a_uiMsg);

    messageWaitQueue(vuiMsg, NULL, a_puiParam1, a_pliParam2);
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

void_t
CxThread::messageWaitQueue(
    const std::vector<uint_t> &a_cvuiMsg,
    uint_t                    *a_puiMsg,
    uint_t                    *a_puiParam1,
    long_t                    *a_pliParam2
) const
{
    xTEST_EQ(true, _m_hThread.isValid());
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
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: priority
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
int_t
CxThread::_priorityMin() {
    int_t iRv = - 1;

#if xOS_ENV_WIN
    iRv = THREAD_PRIORITY_IDLE;
#else
    iRv = ::sched_get_priority_min(SCHED_FIFO);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#endif

    return iRv;
}
//------------------------------------------------------------------------------
/* static */
int_t
CxThread::_priorityMax() {
    int_t iRv = - 1;

#if xOS_ENV_WIN
    iRv = THREAD_PRIORITY_TIME_CRITICAL;
#else
    iRv = ::sched_get_priority_max(SCHED_FIFO);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#endif

    return iRv;
}
//------------------------------------------------------------------------------
void_t
CxThread::setPriority(
    const ExPriority &a_ctpPriority
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());

    BOOL blRes = ::SetThreadPriority(_m_hThread.get(), a_ctpPriority);
    xTEST_DIFF(FALSE, blRes);
#else
    if (!CxSystemInfo::isUserAdmin()) {
        CxTracer() << xT("::: xLib: warning (CxThread::vSetPriority fail, need root) :::");
        return;
    }

    sched_param spParam = {0};

    spParam.sched_priority = a_ctpPriority;

    int_t iRv = ::pthread_setschedparam(id(), SCHED_FIFO, &spParam);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
CxThread::ExPriority
CxThread::priority() const {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
#else

#endif

    CxThread::ExPriority tpRes = tpError;

#if xOS_ENV_WIN
    tpRes = static_cast<ExPriority>( ::GetThreadPriority(_m_hThread.get()) );
    xTEST_DIFF(tpError, tpRes);
#else
    sched_param spParam  = {0};
    int_t         iPolicy  = SCHED_FIFO;

    int_t iRv = ::pthread_getschedparam(id(), &iPolicy, &spParam);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    tpRes = static_cast<ExPriority>( spParam.sched_priority );
#endif

    return tpRes;
}
//------------------------------------------------------------------------------
std::tstring_t
CxThread::priorityString() const {
    // n/a

    int_t iRv = priority();
    switch (iRv) {
        case tpIdle:
            return xT("Idle");
        case tpLowest:
            return xT("Lowest");
        case tpBelowNormal:
            return xT("Below normal");
        case tpNormal:
            return xT("Normal");
        case tpAboveNormal:
            return xT("Above normal");
        case tpHighest:
            return xT("Highest");
        case tpTimeCritical:
            return xT("Time critical");
    }

    return xT("N/A");
}
//------------------------------------------------------------------------------
void_t
CxThread::priorityUp() const {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
#else

#endif

    ExPriority tpOldLevel  = tpError;
    ExPriority tpiNewLevel = tpError;

    tpOldLevel = priority();
    switch (tpOldLevel) {
        case tpIdle:
            tpiNewLevel = tpLowest;
            break;
        case tpLowest:
            tpiNewLevel = tpBelowNormal;
            break;
        case tpBelowNormal:
            tpiNewLevel = tpNormal;
            break;
        case tpNormal:
            tpiNewLevel = tpAboveNormal;
            break;
        case tpAboveNormal:
            tpiNewLevel = tpHighest;
            break;
        case tpHighest:
            tpiNewLevel = tpTimeCritical;
            break;
        case tpTimeCritical:
            return;
            break;
        default:
            xTEST_FAIL;
            break;
    }

    setPriority(tpiNewLevel);
}
//------------------------------------------------------------------------------
void_t
CxThread::priorityDown() const {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
#else

#endif

    ExPriority tpOldLevel  = tpError;
    ExPriority tpiNewLevel = tpError;

    tpOldLevel = priority();
    switch (tpOldLevel) {
        case tpIdle:
            return;
            break;
        case tpLowest:
            tpiNewLevel = tpIdle;
            break;
        case tpBelowNormal:
            tpiNewLevel = tpLowest;
            break;
        case tpNormal:
            tpiNewLevel = tpBelowNormal;
            break;
        case tpAboveNormal:
            tpiNewLevel = tpNormal;
            break;
        case tpHighest:
            tpiNewLevel = tpAboveNormal;
            break;
        case tpTimeCritical:
            tpiNewLevel = tpHighest;
            break;
        default:
            xTEST_FAIL;
            break;
    }

    setPriority(tpiNewLevel);
}
//------------------------------------------------------------------------------
bool_t
CxThread::isPriorityBoost() const {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());

    BOOL blDisablePriorityBoost = TRUE;

    BOOL blRes = ::GetThreadPriorityBoost(_m_hThread.get(), &blDisablePriorityBoost);
    xTEST_DIFF(FALSE, blRes);

    //bDisablePriorityBoost == true  - dynamic boosting is disabled
    //bDisablePriorityBoost == false - normal behavior

    return ! blDisablePriorityBoost;
#else
    return false;
#endif
}
//------------------------------------------------------------------------------
void_t
CxThread::setPriorityBoost(
    cbool_t &a_cbIsEnabled
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());

    BOOL blRes = ::SetThreadPriorityBoost(_m_hThread.get(), ! a_cbIsEnabled);
    xTEST_DIFF(FALSE, blRes);
#else
    return;
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: CPU
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxThread::setCpuAffinity(
    cint_t &a_ciProcNum
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());

    DWORD_PTR pdwMask = 0;

    #if xARCH_X86
        pdwMask = 1UL  << a_ciProcNum;
    #else
        pdwMask = 1i64 << a_ciProcNum;
    #endif

    DWORD_PTR pdwRv = ::SetThreadAffinityMask(_m_hThread.get(), pdwMask);
    #if xARCH_X86
        xTEST_DIFF(0UL, pdwRv);
    #else
        xTEST_PTR(pdwRv);
    #endif

    xTEST_EQ(true, ERROR_INVALID_PARAMETER != pdwRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        cpu_set_t csCpuSet;
    #elif xOS_FREEBSD
        cpuset_t  csCpuSet;
    #endif

    CPU_ZERO(&csCpuSet);
    (void_t)CPU_SET(a_ciProcNum, &csCpuSet);

    int_t iRv = ::pthread_setaffinity_np(id(), sizeof(csCpuSet), &csCpuSet);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif
}
//------------------------------------------------------------------------------
void_t
CxThread::setCpuIdeal(
    culong_t &a_culIdealCpu    ///< value is zero-based
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());

    DWORD ulRv = (DWORD) - 1;

    ulRv = ::SetThreadIdealProcessor(_m_hThread.get(), a_culIdealCpu);
    xTEST_DIFF((DWORD) - 1, ulRv);
#else
    xNOT_IMPLEMENTED;
#endif
}
//------------------------------------------------------------------------------
ulong_t
CxThread::cpuIdeal() const {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
#else

#endif

    ulong_t ulRv = (ulong_t) - 1;

#if xOS_ENV_WIN
    ulRv = ::SetThreadIdealProcessor(_m_hThread.get(), MAXIMUM_PROCESSORS);
    xTEST_DIFF((ulong_t) - 1, ulRv);
#else

#endif

    return ulRv;
}
//------------------------------------------------------------------------------
/* static */
ulong_t
CxThread::cpuCount() {
    ulong_t ulRv = CxSystemInfo::numOfCpus();
    xCHECK_RET(ulRv < 1UL || ulRv > 32UL, 1UL);

    return ulRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: other
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxThread::handle_t
CxThread::handle() const {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());

    return _m_hThread.get();
#else
    return _m_hThread;
#endif
}
//------------------------------------------------------------------------------
CxThread::id_t
CxThread::id() const {
#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());
#else

#endif

    return _m_ulId;
}
//------------------------------------------------------------------------------
bool_t
CxThread::isCurrent() const {
    return CxCurrentThread::isCurrent( CxCurrentThread::id() );
}
//------------------------------------------------------------------------------
ulong_t
CxThread::exitStatus() const {
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    xTEST_EQ(true, _m_hThread.isValid());

    BOOL blRes = ::GetExitCodeThread(_m_hThread.get(), &ulRv);
    xTEST_DIFF(FALSE, blRes);
#else
    ulRv = _m_uiExitStatus;
#endif

    return ulRv;
}
//bool_t
///*CxThread::*/bPost() {
//
//long_t sys_tgkill (int_t tgid, int_t pid, int_t sig);
//}

//------------------------------------------------------------------------------
void_t
CxThread::setDebugName(
    std::ctstring_t &a_csName
) const
{
    ////xTEST_LESS(0, _m_ulId);
    ////xTEST_GR(32, a_csName.size()); //MAX_NAME_SIZE 32

    //// TODO: xCHECK_RET(!CxDebugger().bIsActive(), true);

#if xOS_ENV_WIN
    #if xCOMPILER_MS || xCOMPILER_CODEGEAR
        const DWORD culMsVcException = 0x406D1388;

    #pragma pack(push, 8)
        struct tagTHREADNAME_INFO {
            DWORD  dwType;      // must be 0x1000
            LPCSTR pszName;     // pointer to name (in user addr space)
            DWORD  dwThreadID;  // thread ID (-1 = caller thread)
            DWORD  dwFlags;     // reserved for future use, must be zero
        };
    #pragma pack(pop)

        tagTHREADNAME_INFO tiInfo = {0};
        tiInfo.dwType     = 0x1000;
    #if xUNICODE
        // TODO: vSetDebugName, convert from Unicode to Ansi
        //// tiInfo.pszName    = xTS2S(csName).c_str();
        tiInfo.pszName    = "[Unknown]";
    #else
        tiInfo.pszName    = a_csName.c_str();
    #endif
        tiInfo.dwThreadID = id();
        tiInfo.dwFlags    = 0;

        __try {
            (void_t)::RaiseException(culMsVcException, 0, sizeof(tiInfo) / sizeof(ULONG_PTR), (ULONG_PTR *)&tiInfo);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            //n/a
        }
    #elif xCOMPILER_MINGW
        // TODO: bSetDebugName
    #else
        // TODO: bSetDebugName
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t iRv = ::prctl(PR_SET_NAME, a_csName.c_str(), 0, 0, 0);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
         (void_t)pthread_set_name_np(id(), a_csName.c_str());
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: static
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
CxThread::handle_t
CxThread::open(
    culong_t &a_culAccess,
    cbool_t  &a_cbInheritHandle,
    culong_t &a_culId
)
{
    //ulAccess       - n/a
    //bInheritHandle - n/a
    xTEST_LESS(0UL, a_culId);

#if xOS_ENV_WIN
    handle_t hRv = ::OpenThread(a_culAccess, a_cbInheritHandle, a_culId);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#else
    //TODO: hOpen
    handle_t hRv = 0;
#endif

    return hRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    protected: events
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
uint_t
CxThread::onRun(
    void_t *a_pvParam
) /* = 0*/
{
    // n/a
    xTEST_MSG_FAIL(xT("It's virtual method"));

    uint_t uiRes = 0U;

    #if xTEMP_DISABLED
        xFOREVER {
            bool_t bRv = isTimeToExit();
            xCHECK_DO(bRv, break);

            //...
        }
    #endif

    return uiRes;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    protected: other
*
*******************************************************************************/

//------------------------------------------------------------------------------
bool_t
CxThread::isTimeToExit() {
    // n/a

    bool_t bRv = false;

    //-------------------------------------
    //exit
    bRv = isExited();
    xCHECK_RET(bRv, true);

    //-------------------------------------
    //pause / resume
    bRv = isPaused();
    xCHECK_RET(bRv, ! _waitResumption());

    //-------------------------------------
    //flags
    // n/a

    return false;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
CxThread::exit_status_t xSTDCALL
CxThread::_s_jobEntry(
    void_t *pvParam
)
{
    xTEST_PTR(pvParam);

    uint_t uiRes = 0U;
    bool_t   bRv  = false;     xUNUSED(bRv);

    CxThread *pthThis = static_cast<CxThread *>( pvParam );
    xTEST_PTR(pthThis);

    //-------------------------------------
    // handle must be valid
    ////CxCurrentThread::sleep(500UL);

    CxEvent::ExObjectState osRes = pthThis->_m_pevStarter->wait(10000UL);   // not infinite timeout
    xTEST_EQ(CxEvent::osSignaled, osRes);

    xPTR_DELETE(pthThis->_m_pevStarter);

    //-------------------------------------
    // if created suspended thread - wait for resumption
    if (pthThis->isPaused()) {
        bRv = pthThis->_waitResumption();
        xTEST_EQ(true, bRv);
    }

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
            uiRes = pthThis->onRun(pthThis->_m_pvParam);
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
#if xOS_ENV_WIN
    pthThis->_m_hThread.close();
#else
    // TODO: _m_hThread.vClose()
#endif

    pthThis->_m_ulId         = 0UL;
    pthThis->_m_uiExitStatus = uiRes;    //???
    pthThis->_m_pvParam      = NULL;
    // pthThis->_m_cbIsAutoDelete - n/a

    //-------------------------------------
    // flags
    pthThis->_setStatesDefault();

#if xOS_ENV_WIN
    exit_status_t esExitStatus = pthThis->_m_uiExitStatus;
#else
    exit_status_t esExitStatus = &pthThis->_m_uiExitStatus;
#endif

    //-------------------------------------
    // auto delete oneself
    xCHECK_DO(pthThis->_m_cbIsAutoDelete, xPTR_DELETE(pthThis));

    return esExitStatus;
}
//------------------------------------------------------------------------------
bool_t
CxThread::_waitResumption() {
    //-------------------------------------
    // flags
    /*_m_bIsCreated*/// n/a
    /*_m_bIsRunning*/// n/a
    /*_m_bIsPaused*///  n/a
    /*_m_bIsExited*///  n/a

    CxEvent::ExObjectState osRes = _m_evPause.wait();
    xTEST_DIFF(CxEvent::osFailed, osRes);
    xTEST_DIFF(CxEvent::osTimeout, osRes);
    xTEST_EQ(CxEvent::osSignaled, osRes);

    return (CxEvent::osSignaled == osRes);
}
//------------------------------------------------------------------------------
void_t
CxThread::_setStatesDefault() {
    // n/a

    //-------------------------------------
    // flags
    _m_bIsCreated  = false;
    _m_bIsRunning  = false;
    /*_m_bIsPaused*/// n/a
    /*_m_bIsExited*/// n/a
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
