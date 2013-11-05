/**
 * \file  CxThread.cpp
 * \brief thread
 */


#include <xLib/Sync/CxThread.h>

#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/System/CxSystemInfo.h>
#include <xLib/Sync/CxProcess.h>
#include <xLib/Log/CxTracer.h>

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxThread::CxThread(
    cbool_t &a_isAutoDelete
) :
    tag          (0UL),

    // data
    _thread      (),
    _id          (0UL),
    _exitStatus  (0U),
    _param       (NULL),
    _isAutoDelete(a_isAutoDelete),

    // flags
    _isCreated   (false),
    _isRunning   (false),
    /*_isPaused*/// n/a
    /*_isExited*/// n/a

    //
    ///_vOnExit  (NULL),

    // other
    _eventStarter(NULL),
    _eventPause  (false, false),
    _eventExit   (true,  false)
{
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxThread::~CxThread()
{
    //-------------------------------------
    // close thread, if it still running
    bool_t bRv = isRunning();
    if (bRv) {
        exit();

        // TODO: CxThread::~CxThread()
        //if (!bRv) {
        //    kill(_s_exitTimeout);
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
xINLINE_HO void_t
CxThread::create(
    cbool_t &a_isPaused,
    cuint_t &a_stackSize,
    void_t  *a_param
)
{
#if xOS_ENV_WIN
    xTEST_EQ(false, _thread.isValid());
#else

#endif
    // cbIsPaused   - n/a
    // cuiStackSize - n/a
    // a_param      - n/a

    _param = a_param;

    //-------------------------------------
    // events
    _eventStarter = new CxEvent(true, false);
    xTEST_PTR(_eventStarter);

    _eventStarter->create();
    _eventPause.create();
    _eventExit.create();

    //-------------------------------------
    // start
#if xOS_ENV_WIN
    id_t id = 0UL;

    HANDLE hRv = reinterpret_cast<HANDLE>( ::_beginthreadex(NULL, a_stackSize, _s_jobEntry, this, 0U, (uint_t *)&id) );
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
    xTEST_LESS(0UL, id);

    _thread.set(hRv);
    xTEST_EQ(true, _thread.isValid());

    _id = id;
#else
    int_t          iRv = - 1;
    id_t           id;
    pthread_attr_t attrs; // n/a - {{0}}

    iRv = ::pthread_attr_init(&attrs);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE); //PTHREAD_CREATE_DETACHED
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    if (0 != a_stackSize) {
        //TODO: size_t size = PTHREAD_STACK_MIN + 0x4000;
        iRv = ::pthread_attr_setstacksize(&attrs, a_stackSize);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_create(&id, &attrs, &_s_jobEntry, this);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    xTEST_MSG_EQ(true, 0UL < id, CxLastError::format(iRv));

    iRv = ::pthread_attr_destroy(&attrs);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    _thread = id;  // TODO: is it right?
    _id     = id;
#endif
    xTEST_EQ(false, isCurrent(_id));

    //-------------------------------------
    // flags
    {
        _isCreated = true;
        _isRunning = true;
        /*_isPaused*/// n/a

        if (a_isPaused) {
            pause();
        } else {
            resume();
        }

        /*_isExited*/// n/a
    }

    //-------------------------------------
    // construction is complete, start job entry
    _eventStarter->set();
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::resume()
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#else

#endif

    _eventPause.set();

    //-------------------------------------
    //flags
    /*_isCreated*/// n/a
    /*_isRunning*/// n/a
    /*_isPaused*///  n/a
    /*_isExited*///  n/a
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::pause()
{
#if xOS_ENV_WIN
    xTEST_MSG_EQ(true, _thread.isValid(), CxString::cast(_thread.get()));
#else

#endif

    _eventPause.reset();

    //-------------------------------------
    //flags
    /*_isCreated*/// n/a
    /*_isRunning*/// n/a
    /*_isPaused*///  n/a
    /*_isExited*///  n/a
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::exit()
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#else

#endif

    _eventExit.set();

    //-------------------------------------
    //flags
    /*_isExited*///  n/a
    /*_isCreated*/// n/a
    /*_isRunning*/// n/a
    /*_isPaused*/    xCHECK_DO(isPaused(), resume()); //если поток приостановленный (bPause) - возобновляем
                                                                   //если ожидает чего-то
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::kill(
    culong_t &a_timeoutMsec
)
{
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
    //ulTimeout - n/a

    _exitStatus = 0U;

    BOOL blRes = ::TerminateThread(_thread.get(), _exitStatus);
    xTEST_DIFF(FALSE, blRes);

    xFOREVER {
        ulRv = exitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        currentSleep(a_timeoutMsec);
    }
#else
    int_t iRv = ::pthread_kill(_id, SIGALRM);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    currentSleep(a_timeoutMsec);
#endif

    //-------------------------------------
    // clean members
#if xOS_ENV_WIN
    _thread.close();
#else
    _thread = 0UL;
#endif

    _id         = 0UL;
    _exitStatus = ulRv;    //saving value
    _param      = NULL;
    //_isAutoDelete - n/a

    //-------------------------------------
    //flags
    _setStatesDefault();
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::wait(
    culong_t &a_timeoutMsec
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
    //ulTimeout - n/a

    //-------------------------------------
    //flags
    //?????????

    xTEST_DIFF(currentId(), _id);
    xCHECK_DO(currentId() == _id, return);

    DWORD ulRv = ::WaitForSingleObject(_thread.get(), a_timeoutMsec);
    xTEST_EQ(WAIT_OBJECT_0, ulRv);
#else
    // TODO: thread must not be detached
    // FIX:  a_timeoutMsec
    int_t iRv = ::pthread_join(_id, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: flags
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxThread::isCreated() const
{
    // _thread - n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = (_isCreated) && (_thread.isValid());
#else
    bRv = (_isCreated) && (0UL   != _thread);
#endif

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxThread::isRunning() const
{
    // _thread - n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    DWORD ulRv = 0UL;

    (void_t)::GetExitCodeThread(_thread.get(), &ulRv);

    bool_t bCond1 = ( false         != _thread.isValid()                         );
    bool_t bCond2 = ( 0UL           <  _id                                       );
    bool_t bCond3 = ( true          == _isRunning                                );
    bool_t bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_thread.get(), 0UL) );
    bool_t bCond5 = ( STILL_ACTIVE  == ulRv                                      );

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5;
#else
    bool_t bCond1 = ( 0UL           != _thread                                   );
    bool_t bCond2 = ( 0UL           <  _id                                       );
    bool_t bCond3 = ( true          == _isRunning                                );

#if xTODO
    bool_t bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_thread.get(), 0UL) );
    bool_t bCond5 = ( STILL_ACTIVE  == ulRv                                      );
#endif

    bRv = bCond1 && bCond2 && bCond3 /*&& bCond4 && bCond5*/;
#endif

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxThread::isPaused()
{
    // _thread - n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = !_eventPause.isSignaled() && _thread.isValid();
#else
    bRv = !_eventPause.isSignaled() /*&& (0UL   != _thread)*/;
#endif

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxThread::isExited()
{
    // _thread - n/a

    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = _eventExit.isSignaled() && _thread.isValid();
#else
    bRv = _eventExit.isSignaled() && (0UL != _thread);
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

xINLINE_HO void_t
CxThread::postMessage(
    HWND   a_wnd,
    uint_t a_msg,
    uint_t a_param1,
    long_t a_param2
) const
{
    xTEST_EQ(true, _thread.isValid());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, a_wnd);
    xTEST_DIFF(FALSE, ::IsWindow(a_wnd));

    BOOL blRes = ::PostMessage(a_wnd, a_msg, static_cast<WPARAM>( a_param1 ), static_cast<LPARAM>( a_param2 ));
    xTEST_DIFF(FALSE, blRes);
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xINLINE_HO void_t
CxThread::sendMessage(
    HWND   a_wnd,
    uint_t a_msg,
    uint_t a_param1,
    long_t a_param2
) const
{
    xTEST_EQ(true, _thread.isValid());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, a_wnd);
    xTEST_DIFF(FALSE, ::IsWindow(a_wnd));

    (void_t)::SendMessage(a_wnd, a_msg, static_cast<WPARAM>( a_param1 ), static_cast<LPARAM>( a_param2 ));
    xTEST_EQ(0UL, CxLastError::get());
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xINLINE_HO void_t
CxThread::postThreadMessage(
    uint_t a_msg,
    uint_t a_param1,
    long_t a_param2
) const
{
    xTEST_EQ(true, _thread.isValid());

    BOOL blRes = ::PostThreadMessage(id(), a_msg, static_cast<WPARAM>( a_param1 ), static_cast<LPARAM>( a_param2 ));
    xTEST_DIFF(FALSE, blRes);
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xINLINE_HO bool_t
CxThread::tryPostThreadMessage(
    uint_t  a_msg,
    uint_t  a_param1,
    long_t  a_param2,
    ulong_t a_attempsNum,
    ulong_t a_attempTimeoutMsec
) const
{
    xTEST_EQ(true, _thread.isValid());

    for (ulong_t i = 0UL; i < a_attempsNum; ++ i) {
        BOOL blRes = ::PostThreadMessage(id(), a_msg, static_cast<WPARAM>( a_param1 ), static_cast<LPARAM>( a_param2 ));

        xCHECK_RET(FALSE != blRes, true);
        xCHECK_DO (FALSE == blRes, currentSleep(a_attempTimeoutMsec));
    }

    return false;
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xINLINE_HO void_t
CxThread::messageWaitQueue(
    uint_t  a_msg,
    uint_t *a_param1,
    long_t *a_param2
) const
{
    xTEST_EQ(true, _thread.isValid());
    xTEST_LESS(0U, a_msg);

    std::vector<uint_t> msgs;
    msgs.push_back(a_msg);

    messageWaitQueue(msgs, NULL, a_param1, a_param2);
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xINLINE_HO void_t
CxThread::messageWaitQueue(
    const std::vector<uint_t> &a_msgs,
    uint_t                    *a_msg,
    uint_t                    *a_param1,
    long_t                    *a_param2
) const
{
    xTEST_EQ(true, _thread.isValid());
    xTEST_EQ(false, a_msgs.empty());

    BOOL blRes = FALSE;
    MSG  msg   = {0};

    while ((blRes = ::GetMessage(&msg, NULL, 0, 0 ))) {
        xTEST_DIFF(- 1, blRes);

        for (size_t i = 0; i < a_msgs.size(); ++ i) {
            xCHECK_DO(a_msgs.at(i) != msg.message, continue);

            CxUtils::ptrAssignT(a_msg,    msg.message                      );
            CxUtils::ptrAssignT(a_param1, static_cast<uint_t>( msg.wParam ));
            CxUtils::ptrAssignT(a_param2, static_cast<long_t>( msg.lParam ));

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
xINLINE_HO int_t
CxThread::_priorityMin()
{
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
xINLINE_HO int_t
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
xINLINE_HO void_t
CxThread::setPriority(
    const ExPriority &a_priority
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    BOOL blRes = ::SetThreadPriority(_thread.get(), a_priority);
    xTEST_DIFF(FALSE, blRes);
#else
    if (!CxSystemInfo().isUserAdmin()) {
        CxTracer() << xT("::: xLib: warning (CxThread::setPriority fail, need root) :::");
        return;
    }

    sched_param param = {0};
    param.sched_priority = a_priority;

    int_t iRv = ::pthread_setschedparam(id(), SCHED_FIFO, &param);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO CxThread::ExPriority
CxThread::priority() const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#else

#endif

    CxThread::ExPriority tpRes = tpError;

#if xOS_ENV_WIN
    tpRes = static_cast<ExPriority>( ::GetThreadPriority(_thread.get()) );
    xTEST_DIFF(tpError, tpRes);
#else
    sched_param param  = {0};
    int_t       policy = SCHED_FIFO;

    int_t iRv = ::pthread_getschedparam(id(), &policy, &param);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    tpRes = static_cast<ExPriority>( param.sched_priority );
#endif

    return tpRes;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxThread::priorityString() const
{
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
xINLINE_HO void_t
CxThread::priorityUp() const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
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
xINLINE_HO void_t
CxThread::priorityDown() const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
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
xINLINE_HO bool_t
CxThread::isPriorityBoost() const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    BOOL isDisablePriorityBoost = TRUE;

    BOOL blRes = ::GetThreadPriorityBoost(_thread.get(), &isDisablePriorityBoost);
    xTEST_DIFF(FALSE, blRes);

    //bDisablePriorityBoost == true  - dynamic boosting is disabled
    //bDisablePriorityBoost == false - normal behavior

    return ! isDisablePriorityBoost;
#else
    return false;
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::setPriorityBoost(
    cbool_t &a_isEnabled
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    BOOL blRes = ::SetThreadPriorityBoost(_thread.get(), ! a_isEnabled);
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
xINLINE_HO void_t
CxThread::setCpuAffinity(
    cint_t &a_procNum
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    DWORD_PTR mask = 0;

    #if xARCH_X86
        mask = 1UL  << a_procNum;
    #else
        mask = 1i64 << a_procNum;
    #endif

    DWORD_PTR pdwRv = ::SetThreadAffinityMask(_thread.get(), mask);
    #if xARCH_X86
        xTEST_DIFF(0UL, pdwRv);
    #else
        xTEST_PTR(pdwRv);
    #endif

    xTEST_EQ(true, ERROR_INVALID_PARAMETER != pdwRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        cpu_set_t cpuSet;
    #elif xOS_FREEBSD
        cpuset_t  cpuSet;
    #endif

    CPU_ZERO(&cpuSet);
    (void_t)CPU_SET(a_procNum, &cpuSet);

    int_t iRv = ::pthread_setaffinity_np(id(), sizeof(cpuSet), &cpuSet);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::setCpuIdeal(
    culong_t &a_idealCpu    ///< value is zero-based
) const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    DWORD ulRv = (DWORD) - 1;

    ulRv = ::SetThreadIdealProcessor(_thread.get(), a_idealCpu);
    xTEST_DIFF((DWORD) - 1, ulRv);
#else
    xNOT_IMPLEMENTED;
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxThread::cpuIdeal() const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#else

#endif

    ulong_t ulRv = (ulong_t) - 1;

#if xOS_ENV_WIN
    ulRv = ::SetThreadIdealProcessor(_thread.get(), MAXIMUM_PROCESSORS);
    xTEST_DIFF((ulong_t) - 1, ulRv);
#else

#endif

    return ulRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO ulong_t
CxThread::cpuCount()
{
    ulong_t ulRv = CxSystemInfo().numOfCpus();
    xCHECK_RET(ulRv < 1UL || ulRv > 32UL, 1UL);

    return ulRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: other
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO CxThread::handle_t
CxThread::handle() const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    return _thread.get();
#else
    return _thread;
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO CxThread::id_t
CxThread::id() const
{
#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#else

#endif

    return _id;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxThread::isCurrent() const
{
    return isCurrent( currentId() );
}
//------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxThread::exitStatus() const
{
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    BOOL blRes = ::GetExitCodeThread(_thread.get(), &ulRv);
    xTEST_DIFF(FALSE, blRes);
#else
    ulRv = _exitStatus;
#endif

    return ulRv;
}
//bool_t
///*CxThread::*/bPost() {
//
//long_t sys_tgkill (int_t tgid, int_t pid, int_t sig);
//}

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::setDebugName(
    std::ctstring_t &a_name
) const
{
    ////xTEST_LESS(0, _id);
    ////xTEST_GR(32, a_name.size()); //MAX_NAME_SIZE 32

    //// TODO: xCHECK_RET(!CxDebugger().bIsActive(), true);

#if xOS_ENV_WIN
    #if xCOMPILER_MS || xCOMPILER_CODEGEAR
        const DWORD msVcException = 0x406D1388;

    #pragma pack(push, 8)
        struct tagTHREADNAME_INFO {
            DWORD  dwType;      // must be 0x1000
            LPCSTR pszName;     // pointer to name (in user addr space)
            DWORD  dwThreadID;  // thread ID (-1 = caller thread)
            DWORD  dwFlags;     // reserved for future use, must be zero
        };
    #pragma pack(pop)

        tagTHREADNAME_INFO info = {0};
        info.dwType     = 0x1000;
    #if xUNICODE
        // TODO: vSetDebugName, convert from Unicode to Ansi
        //// info.pszName    = xTS2S(csName).c_str();
        info.pszName    = "[Unknown]";
    #else
        info.pszName    = a_name.c_str();
    #endif
        info.dwThreadID = id();
        info.dwFlags    = 0;

        __try {
            (void_t)::RaiseException(msVcException, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR *)&info);
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
        int_t iRv = ::prctl(PR_SET_NAME, a_name.c_str(), 0, 0, 0);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
         (void_t)pthread_set_name_np(id(), a_name.c_str());
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
xINLINE_HO CxThread::handle_t
CxThread::open(
    culong_t &a_access,
    cbool_t  &a_isInheritHandle,
    culong_t &a_id
)
{
    //ulAccess       - n/a
    //bInheritHandle - n/a
    xTEST_LESS(0UL, a_id);

#if xOS_ENV_WIN
    handle_t hRv = ::OpenThread(a_access, a_isInheritHandle, a_id);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#else
    // TODO: hOpen
    handle_t hRv = 0;
#endif

    return hRv;
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxThread::isCurrent(
    const CxThread::id_t &a_id
)
{
    bool_t bRv = false;

#if xOS_ENV_WIN
    bRv = (id() == a_id);
#else
    //TODO: If either thread1 or thread2 are not valid thread IDs, the behavior is undefined
    bRv = ::pthread_equal(currentId(), a_id);
#endif

    return bRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxThread::id_t
CxThread::currentId()
{
    // n/a

    id_t ulRv = 0UL;

#if xOS_ENV_WIN
    ulRv = ::GetCurrentThreadId();
    xTEST_LESS(0UL, ulRv);
#else
    ulRv = ::pthread_self();
    xTEST_EQ(true, 0UL < ulRv);
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxThread::handle_t
CxThread::currentHandle()
{
    // n/a

    handle_t hRv;

#if xOS_ENV_WIN
    hRv = ::GetCurrentThread();
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#else
    hRv = ::pthread_self();
    xTEST_EQ(true, 0 < hRv);
#endif

    return hRv;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::currentYield()
{
    // n/a

#if xOS_ENV_WIN
    (void_t)::SwitchToThread();
#else
    int_t iRv = ::sched_yield();
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::currentSleep(
    culong_t &a_timeoutMsec
)
{
    // n/a

#if xOS_ENV_WIN
    (void_t)::Sleep(a_timeoutMsec);
#else
    timespec timeSleep  = {0};
    timespec timeRemain = {0};

    timeSleep.tv_sec  = a_timeoutMsec / 1000;
    timeSleep.tv_nsec = (a_timeoutMsec % 1000) * (1000 * 1000);

    xFOREVER {
        int_t iRv = ::nanosleep(&timeSleep, &timeRemain);
        // n/a
        xCHECK_DO(!(- 1 == iRv && EINTR == CxLastError::get()), break);

        timeSleep = timeRemain;
    }
#endif
}
//------------------------------------------------------------------------------

/*******************************************************************************
*    protected: events
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO uint_t
CxThread::onRun(
    void_t *a_param
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
xINLINE_HO bool_t
CxThread::isTimeToExit()
{
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
xINLINE_HO CxThread::exit_status_t xSTDCALL
CxThread::_s_jobEntry(
    void_t *a_param
)
{
    xTEST_PTR(a_param);

    uint_t uiRes = 0U;
    bool_t bRv  = false;     xUNUSED(bRv);

    CxThread *self = static_cast<CxThread *>( a_param );
    xTEST_PTR(self);

    //-------------------------------------
    // handle must be valid
    currentSleep(500UL);

    CxEvent::ExObjectState osRes = self->_eventStarter->wait(10000UL);   // not infinite timeout
    xTEST_EQ(CxEvent::osSignaled, osRes);

    xPTR_DELETE(self->_eventStarter);

    //-------------------------------------
    // if created suspended thread - wait for resumption
    if (self->isPaused()) {
        bRv = self->_waitResumption();
        xTEST_EQ(true, bRv);
    }

    {
        //-------------------------------------
        // begin of thread function
        try {
            #if xTODO
                self->_vHandler_OnEnter(self);
            #endif
        }
        catch (...) {
            xTEST_FAIL;
        }

        //-------------------------------------
        // executing of thread function
        try {
            uiRes = self->onRun(self->_param);
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
                self->_vHandler_OnExit(self);
            #endif
        }
        catch (...) {
            xTEST_FAIL;
        }
    }

    //-------------------------------------
    // clean members (is need to close???)
#if xOS_ENV_WIN
    self->_thread.close();
#else
    // TODO: _thread.vClose()
#endif

    self->_id         = 0UL;
    self->_exitStatus = uiRes;    //???
    self->_param      = NULL;
    // self->_isAutoDelete - n/a

    //-------------------------------------
    // flags
    self->_setStatesDefault();

#if xOS_ENV_WIN
    exit_status_t esExitStatus = self->_exitStatus;
#else
    exit_status_t esExitStatus = &self->_exitStatus;
#endif

    //-------------------------------------
    // auto delete oneself
    xCHECK_DO(self->_isAutoDelete, xPTR_DELETE(self));

    return esExitStatus;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxThread::_waitResumption()
{
    //-------------------------------------
    // flags
    /*_isCreated*/// n/a
    /*_isRunning*/// n/a
    /*_isPaused*///  n/a
    /*_isExited*///  n/a

    CxEvent::ExObjectState osRes = _eventPause.wait();
    xTEST_DIFF(CxEvent::osFailed, osRes);
    xTEST_DIFF(CxEvent::osTimeout, osRes);
    xTEST_EQ(CxEvent::osSignaled, osRes);

    return (CxEvent::osSignaled == osRes);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxThread::_setStatesDefault()
{
    // n/a

    //-------------------------------------
    // flags
    _isCreated  = false;
    _isRunning  = false;
    /*_isPaused*/// n/a
    /*_isExited*/// n/a
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
