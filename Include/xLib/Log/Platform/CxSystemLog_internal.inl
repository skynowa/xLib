/**
 * \file  CxSystemLog_internal.inl
 * \brief logging to system log
 */


#include <xLib/Internal/xInternal.h>


/**************************************************************************************************
*    public
*
**************************************************************************************************/

xNAMESPACE2_BEGIN(xlib, log)

//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(internal, enums)

static Types<IxLog::ExLevel, ssize_t, 10> levels =
{{
#if   xOS_ENV_WIN
    {IxLog::lvUnknown,  - 1},
    {IxLog::lvEmerg,    EVENTLOG_ERROR_TYPE},
    {IxLog::lvAlert,    EVENTLOG_ERROR_TYPE},
    {IxLog::lvCritical, EVENTLOG_ERROR_TYPE},
    {IxLog::lvError,    EVENTLOG_ERROR_TYPE},
    {IxLog::lvWarning,  EVENTLOG_WARNING_TYPE},
    {IxLog::lvNotice,   EVENTLOG_SUCCESS},
    {IxLog::lvInfo,     EVENTLOG_INFORMATION_TYPE},
    {IxLog::lvDebug,    EVENTLOG_INFORMATION_TYPE},
    {IxLog::lvPlain,    EVENTLOG_INFORMATION_TYPE}
#elif xOS_ENV_UNIX
    {IxLog::lvUnknown,  - 1},
    {IxLog::lvEmerg,    0},
    {IxLog::lvAlert,    1},
    {IxLog::lvCritical, 2},
    {IxLog::lvError,    3},
    {IxLog::lvWarning,  4},
    {IxLog::lvNotice,   5},
    {IxLog::lvInfo,     6},
    {IxLog::lvDebug,    7},
    {IxLog::lvPlain,    6}
#endif
}};

xNAMESPACE2_END(internal, enums)
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, log)
