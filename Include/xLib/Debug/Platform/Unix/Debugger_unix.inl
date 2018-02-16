/**
 * \file  Debugger_unix.inl
 * \brief debugger
 */


#if   cmHAVE_PR_SET_DUMPABLE
    #include <sys/prctl.h>
#elif cmHAVE_RLIMIT_CORE
    #include <sys/resource.h>
#endif

#if cmHAVE_PT_DENY_ATTACH
    #include <sys/ptrace.h>
#endif


xNAMESPACE_BEGIN2(xl, debug)

/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Debugger::_coreDumpsEnable_impl(
    cbool_t &a_flag,
    bool_t  *a_isEnable
)
{
#if   cmHAVE_PR_SET_DUMPABLE
    culong_t isDumpable = a_flag ? 1UL : 0UL;

    int_t iRv = ::prctl(PR_SET_DUMPABLE, isDumpable);
    *a_isEnable = (iRv == 0);
#elif cmHAVE_RLIMIT_CORE
    rlimit limit;   Utils::structZeroT(limit);
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

    xBUILD_IMPL("Debugger::coreDumpsEnable()");
#endif

#if cmHAVE_PT_DENY_ATTACH
    // make sure ::setrlimit() and ::ptrace() succeeded
    cint_t isAttachable = a_flag ? PT_ATTACH : PT_DENY_ATTACH;

    iRv = ::ptrace(isAttachable, 0, 0, 0);
    *a_isEnable = *a_isEnable && (iRv == 0);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
Debugger::_breakPoint_impl() const
{
    int_t iRv = ::raise(SIGTRAP);
    xCHECK_DO(iRv == - 1, return);

    iRv = ::kill(::getpid(), SIGALRM);
    xCHECK_DO(iRv == - 1, return);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
