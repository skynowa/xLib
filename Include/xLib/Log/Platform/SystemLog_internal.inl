/**
 * \file  SystemLog_internal.inl
 * \brief logging to system log
 */


#include <xLib/Internal/Internal.h>


/**************************************************************************************************
*    public
*
**************************************************************************************************/

namespace xl::internal::enums
{

constexpr Types<ILog::Level, std::ssize_t, 6> levels
{{
#if   xENV_WIN
    {ILog::Level::Trace,    EVENTLOG_SUCCESS},
    {ILog::Level::Debug,    EVENTLOG_SUCCESS},
    {ILog::Level::Info,     EVENTLOG_INFORMATION_TYPE},
    {ILog::Level::Warning,  EVENTLOG_WARNING_TYPE},
    {ILog::Level::Error,    EVENTLOG_ERROR_TYPE},
    {ILog::Level::Critical, EVENTLOG_ERROR_TYPE}
#elif xENV_UNIX
    {ILog::Level::Trace,    LOG_NOTICE},  // normal but significant condition
    {ILog::Level::Debug,    LOG_DEBUG},   // debug-level messages
    {ILog::Level::Info,     LOG_INFO},    // informational
    {ILog::Level::Warning,  LOG_WARNING}, // warning conditions
    {ILog::Level::Error,    LOG_ERR},     // error conditions
    {ILog::Level::Critical, LOG_CRIT}     // critical conditions
#endif
}};
//-------------------------------------------------------------------------------------------------

} // namespace
