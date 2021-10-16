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

//-------------------------------------------------------------------------------------------------
static
constexpr Types<ILog::Level, std::ssize_t, 7U> levels
{{
#if   xENV_WIN
    {ILog::Level::Off,     -1},
    {ILog::Level::Trace,   EVENTLOG_SUCCESS},
    {ILog::Level::Debug,   EVENTLOG_SUCCESS},
    {ILog::Level::Info,    EVENTLOG_INFORMATION_TYPE},
    {ILog::Level::Warning, EVENTLOG_WARNING_TYPE},
    {ILog::Level::Error,   EVENTLOG_ERROR_TYPE},
    {ILog::Level::Fatal,   EVENTLOG_ERROR_TYPE}
#elif xENV_UNIX
    {ILog::Level::Off,     -1},
    {ILog::Level::Trace,   0},
    {ILog::Level::Debug,   2},
    {ILog::Level::Info,    3},
    {ILog::Level::Warning, 4},
    {ILog::Level::Error,   5},
    {ILog::Level::Fatal,   6}
#endif
}};
//-------------------------------------------------------------------------------------------------

} // namespace
