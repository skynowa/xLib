/**
 * \file  Debugger_bsd.inl
 * \brief debugger
 */


xNAMESPACE_BEGIN2(xl, debug)

/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Debugger::_isActive_impl() const
{
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

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
