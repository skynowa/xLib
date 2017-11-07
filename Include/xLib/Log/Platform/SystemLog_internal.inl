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
    {ILog::lvUnknown,  - 1},
    {ILog::lvEmerg,    EVENTLOG_ERROR_TYPE},
    {ILog::lvAlert,    EVENTLOG_ERROR_TYPE},
    {ILog::lvCritical, EVENTLOG_ERROR_TYPE},
    {ILog::lvError,    EVENTLOG_ERROR_TYPE},
    {ILog::lvWarning,  EVENTLOG_WARNING_TYPE},
    {ILog::lvNotice,   EVENTLOG_SUCCESS},
    {ILog::lvInfo,     EVENTLOG_INFORMATION_TYPE},
    {ILog::lvDebug,    EVENTLOG_INFORMATION_TYPE},
    {ILog::lvPlain,    EVENTLOG_INFORMATION_TYPE}
#elif xENV_UNIX
    {ILog::lvUnknown,  - 1},
    {ILog::lvEmerg,    0},
    {ILog::lvAlert,    1},
    {ILog::lvCritical, 2},
    {ILog::lvError,    3},
    {ILog::lvWarning,  4},
    {ILog::lvNotice,   5},
    {ILog::lvInfo,     6},
    {ILog::lvDebug,    7},
    {ILog::lvPlain,    6}
#endif
}};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, internal, enums)
