/**
 * \file   SystemLog_internal.inl
 * \brief  logging to system log
 */


#include <xLib/Internal/Internal.h>


/**************************************************************************************************
*    public
*
**************************************************************************************************/

namespace xl::internal::enums
{

//-------------------------------------------------------------------------------------------------
static Types<ILog::Level, ssize_t, 10> levels =
{{
#if   xENV_WIN
    {ILog::Level::Unknown,  - 1},
    {ILog::Level::Emerg,    EVENTLOG_ERROR_TYPE},
    {ILog::Level::Alert,    EVENTLOG_ERROR_TYPE},
    {ILog::Level::Critical, EVENTLOG_ERROR_TYPE},
    {ILog::Level::Error,    EVENTLOG_ERROR_TYPE},
    {ILog::Level::Warning,  EVENTLOG_WARNING_TYPE},
    {ILog::Level::Notice,   EVENTLOG_SUCCESS},
    {ILog::Level::Info,     EVENTLOG_INFORMATION_TYPE},
    {ILog::Level::Debug,    EVENTLOG_INFORMATION_TYPE},
    {ILog::Level::Plain,    EVENTLOG_INFORMATION_TYPE}
#elif xENV_UNIX
    {ILog::Level::Unknown,  - 1},
    {ILog::Level::Emerg,    0},
    {ILog::Level::Alert,    1},
    {ILog::Level::Critical, 2},
    {ILog::Level::Error,    3},
    {ILog::Level::Warning,  4},
    {ILog::Level::Notice,   5},
    {ILog::Level::Info,     6},
    {ILog::Level::Debug,    7},
    {ILog::Level::Plain,    6}
#endif
}};
//-------------------------------------------------------------------------------------------------

} // namespace
