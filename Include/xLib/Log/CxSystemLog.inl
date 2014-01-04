/**
 * \file  CxSystemLog.cpp
 * \brief logging to system log
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Internal/xInternal.h>

#if xOS_ENV_UNIX
    #include <syslog.h>
#endif

xNAMESPACE3_BEGIN(NxLib, NxInternal, NxEnum)

static Types<10> levels =
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

    #if xTEMP_DISABLED
        EVENTLOG_AUDIT_FAILURE  // Failure Audit event
        EVENTLOG_AUDIT_SUCCESS  // Success Audit event
    #endif
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

xNAMESPACE3_END(NxLib, NxInternal, NxEnum)


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxSystemLog::CxSystemLog()
#if xOS_ENV_WIN
    :
    _sysLog  (NULL)
#endif
{
    _construct( CxPath( CxPath::exe() ).fileBaseName() );
}
//-------------------------------------------------------------------------------------------------
inline
CxSystemLog::CxSystemLog(
    std::ctstring_t &a_logName
)
#if xOS_ENV_WIN
    :
    _sysLog   (NULL)
#endif
{
    _construct(a_logName);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxSystemLog::~CxSystemLog()
{
    write(xT("%s"), _oss.str().c_str());

#if   xOS_ENV_WIN
    xTEST_PTR(_sysLog);

    BOOL blRv = ::DeregisterEventSource(_sysLog);
    xTEST_DIFF(FALSE, blRv);

    _sysLog = NULL;
#elif xOS_ENV_UNIX
    (void_t)::closelog();
#endif
}
//-------------------------------------------------------------------------------------------------
template<class T>
inline CxSystemLog &
CxSystemLog::operator << (const T &valueT)
{
    _oss << valueT;
    return *this;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxSystemLog::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(),     return);
    xCHECK_DO(a_format == NULL, return);

    std::tstring_t msg;

    va_list args;
    xVA_START(args, a_format);
    msg = CxString::formatV(a_format, args);
    xVA_END(args);

    write(lvPlain, xT("%s"), msg.c_str());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxSystemLog::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);
    xTEST_PTR(a_format);
#if xOS_ENV_WIN
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _sysLog);
#endif

    ExLevel level = lvUnknown;
    {
        xCHECK_DO(a_level == lvPlain, level = lvInfo);
    }

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = CxString::formatV(a_format, args);
        xVA_END(args);
    }

    // write
    {
    #if   xOS_ENV_WIN
        WORD    level_impl = NxInternal::NxEnum::toCross<WORD>(level);
        LPCTSTR strings    = msg.c_str();

        BOOL bRv = ::ReportEvent(_sysLog, level, 0, 0UL, NULL, 1, 0UL, &strings, NULL);
        xTEST_DIFF(FALSE, bRv);
    #elif xOS_ENV_UNIX
        cint_t level_impl = NxInternal::NxEnum::levels.toCross<cint_t>(level);

        (void_t)::syslog(level_impl, xT("%s"), msg.c_str());
    #endif
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxSystemLog::_construct(
    std::ctstring_t &a_logName
)
{
#if   xOS_ENV_WIN
    _sysLog = ::RegisterEventSource(NULL, a_logName.c_str());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _sysLog);
#elif xOS_ENV_UNIX
    (void_t)::openlog(a_logName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
