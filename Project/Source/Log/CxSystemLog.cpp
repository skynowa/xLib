/**
 * \file  CxSystemLog.cpp
 * \brief logging to system log
 */


#include <xLib/Log/CxSystemLog.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>

#if xOS_ENV_UNIX
    #include <syslog.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxSystemLog::CxSystemLog() :
    _m_bIsEnable(true)
#if   xOS_ENV_WIN
    ,
    _m_SysLog   (NULL)
#endif
{
    _init( CxPath( CxPath::exe() ).fileBaseName() );
}
//------------------------------------------------------------------------------
CxSystemLog::CxSystemLog(
    const std::tstring_t &a_csLogName
) :
    _m_bIsEnable(true)
#if   xOS_ENV_WIN
    ,
    _m_SysLog   (NULL)
#endif
{
    _init(a_csLogName);
}
//------------------------------------------------------------------------------
/* virtual */
CxSystemLog::~CxSystemLog() {
#if   xOS_ENV_WIN
    xTEST_PTR(_m_SysLog);

    BOOL blRv = ::DeregisterEventSource(_m_SysLog);
    xTEST_DIFF(FALSE, blRv);

    _m_SysLog = NULL;
#elif xOS_ENV_UNIX
    (void)::closelog();
#endif
}
//------------------------------------------------------------------------------
void
CxSystemLog::setEnabled(
    cbool_t &a_cbFlag
)
{
    xTEST_NA(a_cbFlag);

    _m_bIsEnable = a_cbFlag;
}
//------------------------------------------------------------------------------
void
CxSystemLog::write(
    const ExLevel &a_lvLevel,
    ctchar_t *a_pcszFormat, ...
)
{
    xTEST_PTR(a_pcszFormat);
#if xOS_ENV_WIN
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_SysLog);
#endif

    xCHECK_DO(false == _m_bIsEnable, return);

    //-------------------------------------
    // comment
    std::tstring_t sMessage;
    va_list        alArgs;

    xVA_START(alArgs, a_pcszFormat);
    sMessage = CxString::formatV(a_pcszFormat, alArgs);
    xVA_END(alArgs);

    //-------------------------------------
    // write
#if   xOS_ENV_WIN
    LPCTSTR pcszStrings = sMessage.c_str();

    BOOL bRv = ::ReportEvent(_m_SysLog, a_lvLevel, 0, 0UL, NULL, 1, 0UL, &pcszStrings, NULL);
    xTEST_DIFF(FALSE, bRv);
#elif xOS_ENV_UNIX
    (void)::syslog(a_lvLevel, xT("%s"), sMessage.c_str());
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CxSystemLog::_init(
    const std::tstring_t &a_csLogName
)
{
#if   xOS_ENV_WIN
    _m_SysLog = ::RegisterEventSource(NULL, a_csLogName.c_str());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_SysLog);
#elif xOS_ENV_UNIX
    (void)::openlog(a_csLogName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
