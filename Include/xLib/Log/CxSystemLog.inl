/**
 * \file   CxSystemLog.inl
 * \brief  logging to system log
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include "Platform/CxSystemLog_internal.inl"

#if xENV_UNIX
    #include <syslog.h>
#endif


xNAMESPACE2_BEGIN(xlib, log)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxSystemLog::CxSystemLog()
#if xENV_WIN
    :
    _handle(xPTR_NULL)
#endif
{
    _construct( CxPath( CxPath::exe() ).fileBaseName() );
}
//-------------------------------------------------------------------------------------------------
inline
CxSystemLog::CxSystemLog(
    std::ctstring_t &a_logName
)
#if xENV_WIN
    :
    _handle   (xPTR_NULL)
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

#if   xENV_WIN
    xTEST_PTR(_handle);

    BOOL blRv = ::DeregisterEventSource(_handle);
    xTEST_DIFF(blRv, FALSE);

    _handle = xPTR_NULL;
#elif xENV_UNIX
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
    xCHECK_DO(!isEnabled(),          return);
    xCHECK_DO(a_format == xPTR_NULL, return);

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
#if xENV_WIN
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
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
    #if   xENV_WIN
        WORD    level_impl = internal::enums::toCross(level);
        LPCTSTR strings    = msg.c_str();

        BOOL bRv = ::ReportEvent(_handle, level, 0, 0UL, xPTR_NULL, 1, 0UL, &strings, xPTR_NULL);
        xTEST_DIFF(bRv, FALSE);
    #elif xENV_UNIX
        cint_t level_impl = internal::enums::levels.toCross(level);

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
#if   xENV_WIN
    _handle = ::RegisterEventSource(xPTR_NULL, a_logName.c_str());
    xTEST_DIFF(_handle, xNATIVE_HANDLE_NULL);
#elif xENV_UNIX
    (void_t)::openlog(a_logName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, log)
