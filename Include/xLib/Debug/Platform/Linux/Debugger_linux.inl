/**
 * \file  Debugger_linux.inl
 * \brief debugger
 */


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
Debugger::_isActive_impl() const
{
    // if ppid != sid, some process spawned our app, probably a debugger
    bool_t bRv = ( ::getsid(::getpid()) != ::getppid() );
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
