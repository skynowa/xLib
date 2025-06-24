/**
 * \file  SystemLog_unix.inl
 * \brief logging to system log
 */


#if xOS_ANDROID
	#include <android/log.h>
	// libs: -llog
#endif

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
    (void_t)::openlog(xT2A(a_logName).c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
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
    const auto level_impl = static_cast<int_t>(
        internal::enums::levels.toImpl( static_cast<std::ssize_t>(a_level)) );

    (void_t)::syslog(level_impl, "%s", xT2A(a_msg).c_str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
