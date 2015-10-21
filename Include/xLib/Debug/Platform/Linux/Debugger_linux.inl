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
xINLINE bool_t
Debugger::_isActive_impl() const
{
    // TODO: [Android] ::getsid
#if xTODO_ANDROID
    // if ppid != sid, some process spawned our app, probably a debugger
    bool_t bRv = ( ::getsid(::getpid()) != ::getppid() );
    xCHECK_RET(!bRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
