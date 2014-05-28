/**
 * \file   CxSystemLog.inl
 * \brief  logging to system log
 */


xNAMESPACE_BEGIN2(xlib, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxSystemLog::_construct_impl(
    std::ctstring_t &a_logName
)
{
    (void_t)::openlog(a_logName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxSystemLog::_destruct_impl()
{
    (void_t)::closelog();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxSystemLog::_write_impl(
    cExLevel        &a_level,
    std::ctstring_t &a_msg
) const
{
    cint_t level_impl = internal::enums::levels.toCross(a_level);

    (void_t)::syslog(level_impl, xT("%s"), a_msg.c_str());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, log)
