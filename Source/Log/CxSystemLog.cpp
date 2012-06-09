/**
 * \file  CxSystemLog.cpp
 * \brief logging to system log
 */


#include <xLib/Log/CxSystemLog.h>

#include <xLib/Filesystem/CxPath.h>

#if xOS_ENV_WIN

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
#if xOS_ENV_WIN
    _m_SysLog   (NULL),
#endif
    _m_bIsEnable(true)
{
    bool bRes = _bInit( CxPath::sGetFileBaseName(CxPath::sGetExe()) );
    /*DEBUG*/xASSERT_DO(true == bRes, return);
}
//---------------------------------------------------------------------------
CxSystemLog::CxSystemLog(
    const std::tstring_t &csLogName
) :
#if xOS_ENV_WIN
    _m_SysLog   (NULL),
#endif
    _m_bIsEnable(true)
{
    bool bRes = _bInit(csLogName);
    /*DEBUG*/xASSERT_DO(true == bRes, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxSystemLog::~CxSystemLog() {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_DO(NULL != _m_SysLog, return);

    BOOL bRes = ::DeregisterEventSource(_m_SysLog);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);

    _m_SysLog = NULL;
#elif xOS_ENV_UNIX
    (void)::closelog();
#endif
}
//---------------------------------------------------------------------------
bool
CxSystemLog::bSetEnabled(
    const bool cbFlag
)
{
    /*DEBUG*/// cbFlag - n/a

    _m_bIsEnable = cbFlag;

    return true;
}
//---------------------------------------------------------------------------
bool
CxSystemLog::bWrite(
    const ELevel   lvLevel,
    const tchar_t *pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, false);
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL != _m_SysLog,  false);
#endif

    xCHECK_RET(false == _m_bIsEnable, false);

    //-------------------------------------
    //comment
    std::tstring_t sMessage;
    va_list        alArgs;

    xVA_START(alArgs, pcszFormat);
    sMessage = CxString::sFormatV(pcszFormat, alArgs);
    xVA_END(alArgs);

    //-------------------------------------
    //write
#if xOS_ENV_WIN
    LPCTSTR pcszStrings = sMessage.c_str();

    BOOL bRes = ::ReportEvent(_m_SysLog, lvLevel, 0, 0UL, NULL, 1, 0UL, &pcszStrings, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);
#elif xOS_ENV_UNIX
    (void)::syslog(lvLevel, xT("%s"), sMessage.c_str());
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxSystemLog::_bInit(
    const std::tstring_t &csLogName
)
{
#if xOS_ENV_WIN
    _m_SysLog = ::RegisterEventSource(NULL, csLogName.c_str());
    /*DEBUG*/xASSERT_DO(NULL != _m_SysLog, false);
#elif xOS_ENV_UNIX
    (void)::openlog(csLogName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
