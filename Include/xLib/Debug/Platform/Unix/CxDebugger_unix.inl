/**
 * \file  CxDebugger.inl
 * \brief debugger
 */


#if   xENV_LINUX
    #if xTEMP_DISABLED
        #include <linux/kd.h>   // beep
        #include <X11/Xlib.h>   // beep -lX11
    #endif
#elif xENV_BSD
    #include <sys/user.h>
    #include <sys/proc.h>
#endif

#if   xHAVE_PR_SET_DUMPABLE
    #include <sys/prctl.h>
#elif xHAVE_RLIMIT_CORE
    #include <sys/resource.h>
#endif

#if xHAVE_PT_DENY_ATTACH
    #include <sys/ptrace.h>
#endif


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxDebugger::_isActive_impl() const
{
#if   xENV_LINUX
    // if ppid != sid, some process spawned our app, probably a debugger
    bool_t bRv = ( ::getsid(::getpid()) != ::getppid() );
    xCHECK_RET(!bRv, false);
#elif xENV_BSD
    int_t      mib[4];  xSTRUCT_ZERO(mib);
    kinfo_proc info;    xSTRUCT_ZERO(info);
    size_t     infoSize = 0;

    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PID;
    mib[3] = ::getpid();

    // if sysctl fails for some bizarre reason, we get a predictable result
    info.ki_flag = 0;

    infoSize = sizeof(info);

    int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), &info, &infoSize, xPTR_NULL, 0);
    xCHECK_RET(iRv == - 1, false);

    // we're being debugged if the P_TRACED flag is set.
    xCHECK_RET((info.ki_flag & P_TRACED) == 0, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void
CxDebugger::_coreDumpsEnable_impl(
    cbool_t &a_flag,
    bool_t  *a_isEnable
)
{
#if   xHAVE_PR_SET_DUMPABLE
    culong_t isDumpable = a_flag ? 1UL : 0UL;

    int_t iRv = ::prctl(PR_SET_DUMPABLE, isDumpable);
    *a_isEnable = (iRv == 0);
#elif xHAVE_RLIMIT_CORE
    rlimit limit;   xSTRUCT_ZERO(limit);
    if (a_flag) {
        limit.rlim_cur = RLIM_INFINITY;
        limit.rlim_max = RLIM_INFINITY;
    } else {
        limit.rlim_cur = 0;
        limit.rlim_max = 0;
    }

    int_t iRv = ::setrlimit(RLIMIT_CORE, &limit);
    *a_isEnable = (iRv == 0);
#else
    xUNUSED(a_flag);

    *a_isEnable = false;

    #pragma message("xLib: CxDebugger::coreDumpsEnable() - n/a")
#endif

#if xHAVE_PT_DENY_ATTACH
    // make sure ::setrlimit() and ::ptrace() succeeded
    cint_t isAttachable = a_flag ? PT_ATTACH : PT_DENY_ATTACH;

    iRv = ::ptrace(isAttachable, 0, 0, 0);
    *a_isEnable = *a_isEnable && (iRv == 0);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::_breakPoint_impl() const
{
    int_t iRv = ::raise(SIGTRAP);
    xCHECK_DO(iRv == - 1, return);

    iRv = ::kill(::getpid(), SIGALRM);
    xCHECK_DO(iRv == - 1, return);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
