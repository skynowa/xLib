/**
 * \file  SystemLog.inl
 * \brief logging to system log
 */


#include <android/log.h>
// libs: -llog


namespace xl::log
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
SystemLog::_ctor_impl(
    std::ctstring_t &a_logName
)
{
    (void_t)::openlog(a_logName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
}
//-------------------------------------------------------------------------------------------------
void_t
SystemLog::_dtor_impl()
{
    (void_t)::closelog();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
SystemLog::_write_impl(
    cLevel           a_level,
    std::ctstring_t &a_msg
) const
{
    cint_t level_impl = internal::enums::levels.toCross(a_level);

    (void_t)::syslog(level_impl, xT("%s"), a_msg.c_str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
