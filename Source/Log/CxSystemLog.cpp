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
CxSystemLog::CxSystemLog(
    const std::tstring_t &csLogName
) :
#if   xOS_ENV_WIN
    _m_SysLog   (NULL),
#elif xOS_ENV_UNIX

#endif
    _m_bIsEnable(true)
{

#if xOS_ENV_WIN
    _m_SysLog = ::RegisterEventSource(NULL, csLogName.c_str());
    /*DEBUG*/xASSERT_DO(NULL != _m_SysLog, return);
#elif xOS_ENV_UNIX
    (void)::openlog(csLogName.c_str(), LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_USER);

    //int setlogmask (int __mask) __THROW;
#endif

}
//---------------------------------------------------------------------------
/*virtual*/
CxSystemLog::~CxSystemLog() {
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_DO(NULL != _m_SysLog, return);

    BOOL bRes = ::DeregisterEventSource(_m_SysLog);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
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
#if   xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL != _m_SysLog,  false);
#elif xOS_ENV_UNIX

#endif

    xCHECK_RET(false == _m_bIsEnable, true);

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
    #if xTODO
        BOOL bRes = ::ReportEvent(_m_SysLog, lvLevel,
          __in  WORD wCategory,
          __in  DWORD dwEventID,
          __in  PSID lpUserSid,
          __in  WORD wNumStrings,
          __in  DWORD dwDataSize,
          __in  LPCTSTR *lpStrings,
          __in  LPVOID lpRawData
        );
        /*DEBUG*/xASSERT_RET(FALSE != bRes, false);
    #endif

#elif xOS_ENV_UNIX
    (void)::syslog(lvLevel, xT("%s"), sMessage.c_str());
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
