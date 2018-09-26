/**
 * \file   SystemLog.inl
 * \brief  logging to system log
 */


xNAMESPACE_BEGIN2(xl, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
SystemLog::_construct_impl(
    std::ctstring_t &a_logName
)
{
    (void_t)::openlog(xT2A(a_logName).c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
}
//-------------------------------------------------------------------------------------------------
void_t
SystemLog::_destruct_impl()
{
    (void_t)::closelog();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
SystemLog::_write_impl(
    cLevel          &a_level,
    std::ctstring_t &a_msg
) const
{
    cint_t level_impl = static_cast<int_t>(
    	internal::enums::levels.toCross( static_cast<::ssize_t>(a_level)) );

    (void_t)::syslog(level_impl, "%s", xT2A(a_msg).c_str());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, log)
