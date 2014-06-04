/**
 * \file  CxDebugger_unix.inl
 * \brief debugger
 */


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
inline void_t
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
