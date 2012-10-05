/**
 * \file  CxSystemLog.cpp
 * \brief logging to system log
 */


#include <xLib/Log/CxSystemLog.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>

#if   xOS_ENV_WIN
    xNA
#elif xOS_ENV_UNIX
    #include <syslog.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSystemLog::CxSystemLog() :
    _m_bIsEnable(true)
#if   xOS_ENV_WIN
    ,
    _m_SysLog   (NULL)
#endif
{
    _vInit( CxPath::sGetFileBaseName(CxPath::sGetExe()) );
}
//---------------------------------------------------------------------------
CxSystemLog::CxSystemLog(
    const std::tstring_t &a_csLogName
) :
    _m_bIsEnable(true)
#if   xOS_ENV_WIN
    ,
    _m_SysLog   (NULL)
#endif
{
    _vInit(a_csLogName);
}
//---------------------------------------------------------------------------
/* virtual */
CxSystemLog::~CxSystemLog() {
#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_PTR(_m_SysLog);

    BOOL bRv = ::DeregisterEventSource(_m_SysLog);
    /*DEBUG*/xTEST_DIFF(FALSE, bRv);

    _m_SysLog = NULL;
#elif xOS_ENV_UNIX
    (void)::closelog();
#endif
}
//---------------------------------------------------------------------------
void
CxSystemLog::vSetEnabled(
    const bool &cbFlag
)
{
    /*DEBUG*/// cbFlag - n/a

    _m_bIsEnable = cbFlag;
}
//---------------------------------------------------------------------------
void
CxSystemLog::vWrite(
    const ExLevel &a_lvLevel,
    const tchar_t *a_pcszFormat, ...
)
{
    /*DEBUG*/xTEST_PTR(a_pcszFormat);
#if   xOS_ENV_WIN
    /*DEBUG*/xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_SysLog);
#endif

    xCHECK_DO(false == _m_bIsEnable, return /* false */);  // TODO: CxSystemLog::vWrite

    //-------------------------------------
    //comment
    std::tstring_t sMessage;
    va_list        alArgs;

    xVA_START(alArgs, a_pcszFormat);
    sMessage = CxString::sFormatV(a_pcszFormat, alArgs);
    xVA_END(alArgs);

    //-------------------------------------
    //write
#if   xOS_ENV_WIN
    LPCTSTR pcszStrings = sMessage.c_str();

    BOOL bRv = ::ReportEvent(_m_SysLog, a_lvLevel, 0, 0UL, NULL, 1, 0UL, &pcszStrings, NULL);
    /*DEBUG*/xTEST_DIFF(FALSE, bRv);
#elif xOS_ENV_UNIX
    (void)::syslog(a_lvLevel, xT("%s"), sMessage.c_str());
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxSystemLog::_vInit(
    const std::tstring_t &a_csLogName
)
{
#if   xOS_ENV_WIN
    _m_SysLog = ::RegisterEventSource(NULL, a_csLogName.c_str());
    /*DEBUG*/xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_SysLog);
#elif xOS_ENV_UNIX
    (void)::openlog(a_csLogName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
