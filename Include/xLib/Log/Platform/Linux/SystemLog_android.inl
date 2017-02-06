/**
+ * \file   SystemLog.inl
 * \brief  logging to system log
 */


#include <android/log.h>
// libs: -llog


xNAMESPACE_BEGIN2(xl, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
SystemLog::_construct_impl(
    std::ctstring_t &a_logName
)
{
    (void_t)::openlog(a_logName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SystemLog::_destruct_impl()
{
    (void_t)::closelog();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
SystemLog::_write_impl(
    cExLevel        &a_level,
    std::ctstring_t &a_msg
) const
{
    cint_t level_impl = internal::enums::levels.toCross(a_level);

    (void_t)::syslog(level_impl, xT("%s"), a_msg.c_str());


    int_t iRv = ::__android_log_write(level_impl, const char *tag, a_msg.c_str());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, log)
