/**
 * \file  CxSystemLog.cpp
 * \brief logging to system log
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>

#if !xOS_ENV_WIN
    #include <syslog.h>
#endif


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
/* virtual */
inline void_t
CxSystemLog::write(
    ctchar_t *a_format, ...
) const
{
    xCHECK_DO(a_format == NULL, return);

    va_list args;
    xVA_START(args, a_format);
    write(lvInfo, a_format, args);
    xVA_END(args);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
CxSystemLog::write(
    cExLevel &a_level,
    ctchar_t *a_format, ...
) const
{
    xTEST_PTR(a_format);
#if xOS_ENV_WIN
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _sysLog);
#endif

    xCHECK_DO(!isEnabled(), return);

    //-------------------------------------
    // comment
    std::tstring_t message;
    va_list        args;

    xVA_START(args, a_format);
    message = CxString::formatV(a_format, args);
    xVA_END(args);

    //-------------------------------------
    // write
#if   xOS_ENV_WIN
    LPCTSTR strings = message.c_str();

    BOOL bRv = ::ReportEvent(_sysLog, a_level, 0, 0UL, NULL, 1, 0UL, &strings, NULL);
    xTEST_DIFF(FALSE, bRv);
#elif xOS_ENV_UNIX
    (void_t)::syslog(a_level, xT("%s"), message.c_str());
#endif
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
