/**
 * \file  CxDebugger.inl
 * \brief debugger
 */


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxDebugger::_isActive_impl() const
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
inline void
CxDebugger::_coreDumpsEnable_impl(
    cbool_t &a_flag,
    bool_t  *a_isEnable
)
{
    xUNUSED(a_flag);

    // MSDN: MiniDumpWriteDump, http://www.debuginfo.com/
    *a_isEnable = true;

    #pragma message("xLib: CxDebugger::coreDumpsEnable() - n/a")
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDebugger::_breakPoint_impl() const
{
    (void_t)::DebugBreak();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
