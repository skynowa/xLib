/**
 * \file  Debugger_linux.inl
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
    // ANDROID: ::getsid
#if xTODO_ANDROID
    // if ppid != sid, some process spawned our app, probably a debugger
    bool_t bRv = ( ::getsid(::getpid()) != ::getppid() );
    xCHECK_RET(!bRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
