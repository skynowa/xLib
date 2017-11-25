/**
 * \file  Debugger_win.inl
 * \brief debugger
 */


xNAMESPACE_BEGIN2(xl, debug)

/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Debugger::_isActive_impl() const
{
    // local debugger
    BOOL blRv = ::IsDebuggerPresent();
    xCHECK_RET(blRv != FALSE, true);

    // remote debugger
    BOOL isRemoteDebuggerPresent = FALSE;

    blRv = ::CheckRemoteDebuggerPresent(::GetCurrentProcess(), &isRemoteDebuggerPresent);
    xCHECK_RET(blRv == FALSE || isRemoteDebuggerPresent == FALSE, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Debugger::_coreDumpsEnable_impl(
    cbool_t &a_flag,
    bool_t  *a_isEnable
)
{
    xUNUSED(a_flag);

    // MSDN: MiniDumpWriteDump, http://www.debuginfo.com/
    *a_isEnable = true;

    #pragma message("xLib: Debugger::coreDumpsEnable() - n/a")
}
//-------------------------------------------------------------------------------------------------
void_t
Debugger::_breakPoint_impl() const
{
    (void_t)::DebugBreak();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
