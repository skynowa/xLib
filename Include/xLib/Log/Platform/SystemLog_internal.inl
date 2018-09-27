/**
 * \file   SystemLog_internal.inl
 * \brief  logging to system log
 */


#include <xLib/Internal/Internal.h>


/**************************************************************************************************
*    public
*
**************************************************************************************************/

xNAMESPACE_BEGIN3(xl, internal, enums)

//-------------------------------------------------------------------------------------------------
static Types<ILog::Level, ssize_t, 10> levels =
{{
#if   xENV_WIN
    {ILog::Level::lvUnknown,  - 1},
    {ILog::Level::lvEmerg,    EVENTLOG_ERROR_TYPE},
    {ILog::Level::lvAlert,    EVENTLOG_ERROR_TYPE},
    {ILog::Level::lvCritical, EVENTLOG_ERROR_TYPE},
    {ILog::Level::lvError,    EVENTLOG_ERROR_TYPE},
    {ILog::Level::lvWarning,  EVENTLOG_WARNING_TYPE},
    {ILog::Level::lvNotice,   EVENTLOG_SUCCESS},
    {ILog::Level::lvInfo,     EVENTLOG_INFORMATION_TYPE},
    {ILog::Level::lvDebug,    EVENTLOG_INFORMATION_TYPE},
    {ILog::Level::lvPlain,    EVENTLOG_INFORMATION_TYPE}
#elif xENV_UNIX
    {ILog::Level::lvUnknown,  - 1},
    {ILog::Level::lvEmerg,    0},
    {ILog::Level::lvAlert,    1},
    {ILog::Level::lvCritical, 2},
    {ILog::Level::lvError,    3},
    {ILog::Level::lvWarning,  4},
    {ILog::Level::lvNotice,   5},
    {ILog::Level::lvInfo,     6},
    {ILog::Level::lvDebug,    7},
    {ILog::Level::lvPlain,    6}
#endif
}};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, internal, enums)
