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
    write(xT("%s\n"), _oss.str().c_str());

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
        LPCTSTR strings = msg.c_str();

        BOOL bRv = ::ReportEvent(_sysLog, level, 0, 0UL, NULL, 1, 0UL, &strings, NULL);
        xTEST_DIFF(FALSE, bRv);
    #elif xOS_ENV_UNIX
        (void_t)::syslog(level, xT("%s"), msg.c_str());
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
