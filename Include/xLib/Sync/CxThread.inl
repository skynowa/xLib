/**
 * \file  CxThread.cpp
 * \brief thread
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/System/CxSystemInfo.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE2_BEGIN(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
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
    _state       (),

    //
    ///_vOnExit  (NULL),

    // other
    _eventStarter(NULL),
    _eventPause  (false, false),
    _eventExit   (true,  false)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxThread::~CxThread()
{
    //-------------------------------------
    // close thread, if it still running
    bool_t bRv = isRunning();
    if (bRv) {
        exit();

        // TODO: CxThread::~CxThread()
    #if xTODO
        if (!bRv) {
            kill(_s_exitTimeout);
            if (!bRv) {
                xTEST_FAIL;
            }
        }
    #endif
    }

    //-------------------------------------
    // state flags
    _setStatesDefault();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::create(
    cbool_t &a_isPaused,
    cuint_t &a_stackSize,
    void_t  *a_param
)
{
#if   xOS_ENV_WIN
    xTEST_EQ(false, _thread.isValid());
#elif xOS_ENV_UNIX

#endif
    xTEST_NA(a_isPaused);
    xTEST_NA(a_stackSize);
    xTEST_NA(a_param);

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
#if   xOS_ENV_WIN
    id_t id = 0UL;

    HANDLE hRv = reinterpret_cast<HANDLE>( ::_beginthreadex(NULL, a_stackSize, _s_jobEntry, this,
        0U, (uint_t *)&id) );
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
    xTEST_LESS(0UL, id);

    _thread.set(hRv);
    xTEST_EQ(true, _thread.isValid());

    _id = id;
#elif xOS_ENV_UNIX
    int_t          iRv = - 1;
    id_t           hid;
    pthread_attr_t attrs; xSTRUCT_ZERO(attrs);

    iRv = ::pthread_attr_init(&attrs);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    iRv = ::pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE); //PTHREAD_CREATE_DETACHED
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    if (a_stackSize != 0U) {
        //TODO: size_t size = PTHREAD_STACK_MIN + 0x4000;
        iRv = ::pthread_attr_setstacksize(&attrs, a_stackSize);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    iRv = ::pthread_create(&hid, &attrs, &_s_jobEntry, this);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    xTEST_MSG_EQ(true, 0UL < hid, CxLastError::format(iRv));

    iRv = ::pthread_attr_destroy(&attrs);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    _thread = hid;  // TODO: CxThread::create() - is it right?
    _id     = hid;
#endif
    xTEST_EQ(false, isCurrent(_id));

    //-------------------------------------
    // flags
    {
        _state.isCreated = true;
        _state.isRunning = true;

        if (a_isPaused) {
            pause();
        } else {
            resume();
        }
    }

    // construction is complete, start job entry
    _eventStarter->set();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::resume()
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#elif xOS_ENV_UNIX

#endif

    _eventPause.set();

    //-------------------------------------
    // flags
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::pause()
{
#if   xOS_ENV_WIN
    xTEST_MSG_EQ(true, _thread.isValid(), CxString::cast(_thread.get()));
#elif xOS_ENV_UNIX

#endif

    _eventPause.reset();

    //-------------------------------------
    // flags
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::exit()
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#elif xOS_ENV_UNIX

#endif

    _eventExit.set();

    //-------------------------------------
    // flags
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a

        xCHECK_DO(isPaused(), resume());
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::kill(
    culong_t &a_timeoutMsec
)
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
    xTEST_NA(a_timeoutMsec);

    _exitStatus = 0U;

    BOOL blRv = ::TerminateThread(_thread.get(), _exitStatus);
    xTEST_DIFF(FALSE, blRv);

    xFOREVER {
        ulRv = exitStatus();
        xCHECK_DO(STILL_ACTIVE != ulRv, break);

        currentSleep(a_timeoutMsec);
    }
#elif xOS_ENV_UNIX
    int_t iRv = ::pthread_kill(_id, SIGALRM);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    currentSleep(a_timeoutMsec);
#endif

    // clean members
    {
    #if   xOS_ENV_WIN
        _thread.close();
    #elif xOS_ENV_UNIX
        _thread = 0UL;
    #endif

        _id         = 0UL;
        _exitStatus = static_cast<uint_t>( ulRv );  // saving value
        _param      = NULL;
        //_isAutoDelete - n/a

        // flags
        _setStatesDefault();
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::wait(
    culong_t &a_timeoutMsec
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
    xTEST_NA(a_timeoutMsec);

    //-------------------------------------
    // flags
    xTEST_DIFF(currentId(), _id);
    xCHECK_DO(currentId() == _id, return);

    DWORD dwRv = ::WaitForSingleObject(_thread.get(), a_timeoutMsec);
    xTEST_EQ(WAIT_OBJECT_0, dwRv);
#elif xOS_ENV_UNIX
    xUNUSED(a_timeoutMsec);

    // TODO: thread must not be detached
    // FIX:  a_timeoutMsec
    int_t iRv = ::pthread_join(_id, NULL);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: flags
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isCreated() const
{
    // _thread - n/a

    bool_t bRv = false;

#if   xOS_ENV_WIN
    bRv = (_state.isCreated) && (_thread.isValid());
#elif xOS_ENV_UNIX
    bRv = (_state.isCreated) && (0UL != _thread);
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isRunning() const
{
    // _thread - n/a

    bool_t bRv = false;

#if   xOS_ENV_WIN
    DWORD ulRv = 0UL;

    (void_t)::GetExitCodeThread(_thread.get(), &ulRv);

    bool_t bCond1 = ( false         != _thread.isValid()                         );
    bool_t bCond2 = ( 0UL           <  _id                                       );
    bool_t bCond3 = ( true          == _state.isRunning                          );
    bool_t bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_thread.get(), 0UL) );
    bool_t bCond5 = ( STILL_ACTIVE  == ulRv                                      );

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5;
#elif xOS_ENV_UNIX
    bool_t bCond1 = ( 0UL           != _thread                                   );
    bool_t bCond2 = ( 0UL           <  _id                                       );
    bool_t bCond3 = ( true          == _state.isRunning                          );

#if xTODO
    bool_t bCond4 = ( WAIT_OBJECT_0 != ::WaitForSingleObject(_thread.get(), 0UL) );
    bool_t bCond5 = ( STILL_ACTIVE  == ulRv                                      );
#endif

    bRv = bCond1 && bCond2 && bCond3 /*&& bCond4 && bCond5*/;
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isPaused()
{
    // _thread - n/a

    bool_t bRv = false;

#if   xOS_ENV_WIN
    bRv = !_eventPause.isSignaled() && _thread.isValid();
#elif xOS_ENV_UNIX
    bRv = !_eventPause.isSignaled() /*&& (0UL != _thread)*/;
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isExited()
{
    // _thread - n/a

    bool_t bRv = false;

#if   xOS_ENV_WIN
    bRv = _eventExit.isSignaled() && _thread.isValid();
#elif xOS_ENV_UNIX
    bRv = _eventExit.isSignaled() && (0UL != _thread);
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: messages
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline void_t
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

    BOOL blRv = ::PostMessage(a_wnd, a_msg, static_cast<WPARAM>( a_param1 ),
        static_cast<LPARAM>( a_param2 ));
    xTEST_DIFF(FALSE, blRv);
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline void_t
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

    (void_t)::SendMessage(a_wnd, a_msg, static_cast<WPARAM>( a_param1 ),
        static_cast<LPARAM>( a_param2 ));
    xTEST_EQ(0UL, CxLastError::get());
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline void_t
CxThread::postThreadMessage(
    uint_t a_msg,
    uint_t a_param1,
    long_t a_param2
) const
{
    xTEST_EQ(true, _thread.isValid());

    BOOL blRv = ::PostThreadMessage(id(), a_msg, static_cast<WPARAM>( a_param1 ),
        static_cast<LPARAM>( a_param2 ));
    xTEST_DIFF(FALSE, blRv);
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline bool_t
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
        BOOL blRv = ::PostThreadMessage(id(), a_msg, static_cast<WPARAM>( a_param1 ),
            static_cast<LPARAM>( a_param2 ));

        xCHECK_RET(FALSE != blRv, true);
        xCHECK_DO (FALSE == blRv, currentSleep(a_attempTimeoutMsec));
    }

    return false;
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline void_t
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
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline void_t
CxThread::messageWaitQueue(
    const std::vector<uint_t> &a_msgs,
    uint_t                    *a_msg,
    uint_t                    *a_param1,
    long_t                    *a_param2
) const
{
    xTEST_EQ(true, _thread.isValid());
    xTEST_EQ(false, a_msgs.empty());

    BOOL blRv = FALSE;
    MSG  msg  = {0};

    while ((blRv = ::GetMessage(&msg, NULL, 0, 0 ))) {
        xTEST_DIFF(- 1, blRv);

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
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: priority
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxThread::_priorityMin()
{
    int_t iRv = - 1;

#if   xOS_ENV_WIN
    iRv = THREAD_PRIORITY_IDLE;
#elif xOS_ENV_UNIX
    iRv = ::sched_get_priority_min(SCHED_FIFO);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#endif

    return iRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxThread::_priorityMax()
{
    int_t iRv = - 1;

#if   xOS_ENV_WIN
    iRv = THREAD_PRIORITY_TIME_CRITICAL;
#elif xOS_ENV_UNIX
    iRv = ::sched_get_priority_max(SCHED_FIFO);
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#endif

    return iRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::setPriority(
    const ExPriority &a_priority
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    BOOL blRv = ::SetThreadPriority(_thread.get(), a_priority);
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    if (!CxSystemInfo().isUserAdmin()) {
        CxTrace() << xT("::: xLib: warning (CxThread::setPriority fail, need root) :::");
        return;
    }

    sched_param param = {0};
    param.sched_priority = a_priority;

    int_t iRv = ::pthread_setschedparam(id(), SCHED_FIFO, &param);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline CxThread::ExPriority
CxThread::priority() const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#elif xOS_ENV_UNIX

#endif

    CxThread::ExPriority tpRv = tpError;

#if   xOS_ENV_WIN
    tpRv = static_cast<ExPriority>( ::GetThreadPriority(_thread.get()) );
    xTEST_DIFF(tpError, tpRv);
#elif xOS_ENV_UNIX
    sched_param param  = {0};
    int_t       policy = SCHED_FIFO;

    int_t iRv = ::pthread_getschedparam(id(), &policy, &param);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    tpRv = static_cast<ExPriority>( param.sched_priority );
#endif

    return tpRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
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
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::priorityUp() const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#elif xOS_ENV_UNIX

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
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::priorityDown() const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#elif xOS_ENV_UNIX

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
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isPriorityBoost() const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    BOOL isDisablePriorityBoost = TRUE;

    BOOL blRv = ::GetThreadPriorityBoost(_thread.get(), &isDisablePriorityBoost);
    xTEST_DIFF(FALSE, blRv);

    // isDisablePriorityBoost == TRUE  - dynamic boosting is disabled
    // isDisablePriorityBoost == FALSE - normal behavior

    return ! isDisablePriorityBoost;
#elif xOS_ENV_UNIX
    return false;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::setPriorityBoost(
    cbool_t &a_isEnabled
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    BOOL blRv = ::SetThreadPriorityBoost(_thread.get(), ! a_isEnabled);
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    xUNUSED(a_isEnabled);

    return;
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: CPU
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::setCpuAffinity(
    cint_t &a_procNum
) const
{
#if   xOS_ENV_WIN
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
#elif xOS_ENV_APPLE
    xNOT_IMPLEMENTED
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::setCpuIdeal(
    culong_t &a_idealCpu    ///< value is zero-based
) const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    DWORD dwRv = (DWORD) - 1;

    dwRv = ::SetThreadIdealProcessor(_thread.get(), a_idealCpu);
    xTEST_DIFF((DWORD) - 1, dwRv);
#elif xOS_ENV_UNIX
    xUNUSED(a_idealCpu);

    xNOT_IMPLEMENTED;
#endif
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxThread::cpuIdeal() const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#elif xOS_ENV_UNIX

#endif

    ulong_t ulRv = (ulong_t) - 1;

#if   xOS_ENV_WIN
    ulRv = ::SetThreadIdealProcessor(_thread.get(), MAXIMUM_PROCESSORS);
    xTEST_DIFF((ulong_t) - 1, ulRv);
#elif xOS_ENV_UNIX

#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
CxThread::cpuCount()
{
    ulong_t ulRv = CxSystemInfo().numOfCpus();
    xCHECK_RET(ulRv < 1UL || ulRv > 32UL, 1UL);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxThread::handle_t
CxThread::handle() const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    return _thread.get();
#elif xOS_ENV_UNIX
    return _thread;
#endif
}
//-------------------------------------------------------------------------------------------------
inline CxThread::id_t
CxThread::id() const
{
#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());
#elif xOS_ENV_UNIX

#endif

    return _id;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isCurrent() const
{
    return isCurrent( currentId() );
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxThread::exitStatus() const
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    xTEST_EQ(true, _thread.isValid());

    BOOL blRv = ::GetExitCodeThread(_thread.get(), &ulRv);
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    ulRv = _exitStatus;
#endif

    return ulRv;
}
//bool_t
///*CxThread::*/bPost() {
//
//long_t sys_tgkill (int_t tgid, int_t pid, int_t sig);
//}

//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::setDebugName(
    std::ctstring_t &a_name
) const
{
    ////xTEST_LESS(0, _id);
    ////xTEST_GR(32, a_name.size()); // MAX_NAME_SIZE 32

    //// TODO: xCHECK_RET(!CxDebugger().isActive(), true);

#if   xOS_ENV_WIN
    #if xCOMPILER_MS || xCOMPILER_CODEGEAR
        const DWORD msVcException = 0x406D1388;

    #pragma pack(push, 8)
        struct tagTHREADNAME_INFO
        {
            DWORD  dwType;      // must be 0x1000
            LPCSTR pszName;     // pointer to name (in user addr space)
            DWORD  dwThreadID;  // thread ID (-1 = caller thread)
            DWORD  dwFlags;     // reserved for future use, must be zero
        };
    #pragma pack(pop)

        tagTHREADNAME_INFO info = {0};
        info.dwType = 0x1000;
    #if xUNICODE
        // TODO: CxThread::setDebugName() - convert from Unicode to Ansi
        //// info.pszName    = xTS2S(csName).c_str();
        info.pszName    = "[Unknown]";
    #else
        info.pszName    = a_name.c_str();
    #endif
        info.dwThreadID = id();
        info.dwFlags    = 0;

        __try {
            (void_t)::RaiseException(msVcException, 0, sizeof(info) / sizeof(ULONG_PTR),
                (ULONG_PTR *)&info);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            //n/a
        }
    #elif xCOMPILER_MINGW
        // TODO: CxThread::setDebugName() - xCOMPILER_MINGW
    #else
        // TODO: CxThread::setDebugName() - other
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t iRv = ::prctl(PR_SET_NAME, a_name.c_str(), 0, 0, 0);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
         (void_t)pthread_set_name_np(id(), a_name.c_str());
    #endif
#elif xOS_ENV_APPLE
    // TODO: CxThread::setDebugName() - Mac
    xNOT_IMPLEMENTED
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline CxThread::handle_t
CxThread::open(
    culong_t &a_access,
    cbool_t  &a_isInheritHandle,
    culong_t &a_id
)
{
    xTEST_NA(a_access);
    xTEST_NA(a_isInheritHandle);
    xTEST_LESS(0UL, a_id);

#if   xOS_ENV_WIN
    handle_t hRv = ::OpenThread(a_access, a_isInheritHandle, a_id);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#elif xOS_ENV_UNIX
    xUNUSED(a_access);
    xUNUSED(a_isInheritHandle);

    // TODO: CxThread::open()
    handle_t hRv = 0;
#endif

    return hRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isCurrent(
    const CxThread::id_t &a_id
)
{
    bool_t bRv = false;

#if   xOS_ENV_WIN
    bRv = (currentId() == a_id);
#elif xOS_ENV_UNIX
    bRv = ::pthread_equal(currentId(), a_id);
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline CxThread::id_t
CxThread::currentId()
{
    // n/a

    id_t ulRv = 0UL;

#if   xOS_ENV_WIN
    ulRv = ::GetCurrentThreadId();
    xTEST_LESS(0UL, ulRv);
#elif xOS_ENV_UNIX
    ulRv = ::pthread_self();
    xTEST_EQ(true, 0UL < ulRv);
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxThread::handle_t
CxThread::currentHandle()
{
    // n/a

    handle_t hRv;

#if   xOS_ENV_WIN
    hRv = ::GetCurrentThread();
    xTEST_DIFF(xNATIVE_HANDLE_NULL, hRv);
#elif xOS_ENV_UNIX
    hRv = ::pthread_self();
    xTEST_EQ(true, 0 < hRv);
#endif

    return hRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::currentYield()
{
    // n/a

#if   xOS_ENV_WIN
    (void_t)::SwitchToThread();
#elif xOS_ENV_UNIX
    int_t iRv = ::sched_yield();
    xTEST_MSG_DIFF(- 1, iRv, CxLastError::format(iRv));
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::currentSleep(
    culong_t &a_timeoutMsec
)
{
    // n/a

#if   xOS_ENV_WIN
    (void_t)::Sleep(a_timeoutMsec);
#elif xOS_ENV_UNIX
    timespec timeSleep  = {0, 0};
    timespec timeRemain = {0, 0};

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
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    protected: events
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
inline uint_t
CxThread::onRun(
    void_t *a_param
) /* = 0*/
{
    xUNUSED(a_param);

    xTEST_MSG_FAIL(xT("It's virtual method"));

    uint_t uiRv = 0U;

    #if xTEMP_DISABLED
        xFOREVER {
            bool_t bRv = isTimeToExit();
            xCHECK_DO(bRv, break);

            //...
        }
    #endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    protected: other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::isTimeToExit()
{
    // n/a

    bool_t bRv = false;

    //-------------------------------------
    // exit
    bRv = isExited();
    xCHECK_RET(bRv, true);

    //-------------------------------------
    // pause / resume
    bRv = isPaused();
    xCHECK_RET(bRv, ! _waitResumption());

    //-------------------------------------
    // flags
    // n/a

    return false;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline CxThread::exit_status_t xSTDCALL
CxThread::_s_jobEntry(
    void_t *a_param
)
{
    xTEST_PTR(a_param);

    uint_t uiRv = 0U;
    bool_t bRv  = false;

    CxThread *self = static_cast<CxThread *>( a_param );
    xTEST_PTR(self);

    //-------------------------------------
    // handle must be valid
    currentSleep(500UL);

    CxEvent::ExObjectState osRv = self->_eventStarter->wait(10000UL);   // not infinite timeout
    xTEST_EQ(CxEvent::osSignaled, osRv);

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
            uiRv = self->onRun(self->_param);
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
#if   xOS_ENV_WIN
    self->_thread.close();
#elif xOS_ENV_UNIX
    // TODO: CxThread::_s_jobEntry() - close thread
    // _thread.close()
#endif

    self->_id         = 0UL;
    self->_exitStatus = uiRv;    // ???
    self->_param      = NULL;
    // self->_isAutoDelete - n/a

    //-------------------------------------
    // flags
    self->_setStatesDefault();

#if   xOS_ENV_WIN
    exit_status_t esExitStatus = self->_exitStatus;
#elif xOS_ENV_UNIX
    exit_status_t esExitStatus = &self->_exitStatus;
#endif

    //-------------------------------------
    // auto delete oneself
    xCHECK_DO(self->_isAutoDelete, xPTR_DELETE(self));

    return esExitStatus;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThread::_waitResumption()
{
    //-------------------------------------
    // flags
    {
        /* _state.isCreated */// n/a
        /* _state.isRunning */// n/a
    }

    CxEvent::ExObjectState osRv = _eventPause.wait();
    xTEST_DIFF(CxEvent::osFailed, osRv);
    xTEST_DIFF(CxEvent::osTimeout, osRv);
    xTEST_EQ(CxEvent::osSignaled, osRv);

    return (CxEvent::osSignaled == osRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThread::_setStatesDefault()
{
    // n/a

    //-------------------------------------
    // flags
    {
        _state.isCreated  = false;
        _state.isRunning  = false;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, sync)
