/**
 * \file  CxSystemLog.cpp
 * \brief logging to system log
 */


#include <xLib/Log/CxSystemLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>

#if defined(xOS_ENV_WIN)

#elif defined(xOS_ENV_UNIX)
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
    _m_bIsEnable(true)
{

#if defined(xOS_ENV_WIN)
    //HANDLE OpenEventLog(__in  LPCTSTR lpUNCServerName, __in  LPCTSTR lpSourceName);
#elif defined(xOS_ENV_UNIX)
    //(void)::openlog(csLogName.c_str(), int __option, int __facility);

    //int setlogmask (int __mask) __THROW;
#endif

}
//---------------------------------------------------------------------------
/*virtual*/
CxSystemLog::~CxSystemLog() {
#if defined(xOS_ENV_WIN)
    //BOOL CloseEventLog(__inout  HANDLE hEventLog);
#elif defined(xOS_ENV_UNIX)
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

    xCHECK_RET(false == _m_bIsEnable, true);


    //-------------------------------------
    //comment
    std::tstring_t sMessage;
    va_list        alArgs;

    xVA_START(alArgs, pcszFormat);
    sMessage = CxString::sFormatV(pcszFormat, alArgs);
    xVA_END(alArgs);

    //-------------------------------------
    //data
    std::tstring_t sData;

    sData = CxString::sFormat(
                xT("[%s] %s"),
                CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime).c_str(),
                sMessage.c_str()
    );

    //-------------------------------------
    //write
#if xOS_ENV_WIN

#elif xOS_ENV_UNIX
    (void)::syslog(lvLevel, "%s", sData.c_str());
#endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
