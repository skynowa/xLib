/**
 * \file  Debugger_bsd.inl
 * \brief debugger
 */


namespace xl::debug
{

/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Debugger::_isActive_impl() const
{
    const u_int mibSize = 4;
    int_t       mib[mibSize] {};
    kinfo_proc  info {};
    size_t      infoSize = 0;

    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PID;
    mib[3] = ::getpid();

    // if sysctl fails for some bizarre reason, we get a predictable result
    info.ki_flag = 0;

    infoSize = sizeof(info);

    int_t iRv = ::sysctl(mib, mibSize, &info, &infoSize, nullptr, 0);
    xCHECK_RET(iRv == - 1, false);

    // we're being debugged if the P_TRACED flag is set.
    xCHECK_RET((info.ki_flag & P_TRACED) == 0, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
