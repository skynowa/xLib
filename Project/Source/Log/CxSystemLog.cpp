/**
 * \file  CxSystemLog.cpp
 * \brief logging to system log
 */


#include <xLib/Log/CxSystemLog.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>

#if !xOS_ENV_WIN
    #include <syslog.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxSystemLog::CxSystemLog() :
    _isEnable(true)
#if xOS_ENV_WIN
    ,
    _sysLog  (NULL)
#endif
{
    _construct( CxPath( CxPath::exe() ).fileBaseName() );
}
//------------------------------------------------------------------------------
CxSystemLog::CxSystemLog(
    std::ctstring_t &a_logName
) :
    _isEnable(true)
#if xOS_ENV_WIN
    ,
    _sysLog   (NULL)
#endif
{
    _construct(a_logName);
}
//------------------------------------------------------------------------------
/* virtual */
CxSystemLog::~CxSystemLog()
{
#if xOS_ENV_WIN
    xTEST_PTR(_sysLog);

    BOOL blRv = ::DeregisterEventSource(_sysLog);
    xTEST_DIFF(FALSE, blRv);

    _sysLog = NULL;
#else
    (void_t)::closelog();
#endif
}
//------------------------------------------------------------------------------
void_t
CxSystemLog::setEnabled(
    cbool_t &a_flag
)
{
    xTEST_NA(a_flag);

    _isEnable = a_flag;
}
//------------------------------------------------------------------------------
void_t
CxSystemLog::write(
    const ExLevel &a_level,
    ctchar_t      *a_format, ...
)
{
    xTEST_PTR(a_format);
#if xOS_ENV_WIN
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _sysLog);
#endif

    xCHECK_DO(!_isEnable, return);

    //-------------------------------------
    // comment
    std::tstring_t sMessage;
    va_list        alArgs;

    xVA_START(alArgs, a_format);
    sMessage = CxString::formatV(a_format, alArgs);
    xVA_END(alArgs);

    //-------------------------------------
    // write
#if xOS_ENV_WIN
    LPCTSTR pcszStrings = sMessage.c_str();

    BOOL bRv = ::ReportEvent(_sysLog, a_level, 0, 0UL, NULL, 1, 0UL, &pcszStrings, NULL);
    xTEST_DIFF(FALSE, bRv);
#else
    (void_t)::syslog(a_level, xT("%s"), sMessage.c_str());
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxSystemLog::_construct(
    std::ctstring_t &a_logName
)
{
#if xOS_ENV_WIN
    _sysLog = ::RegisterEventSource(NULL, a_logName.c_str());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _sysLog);
#else
    (void_t)::openlog(a_logName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
