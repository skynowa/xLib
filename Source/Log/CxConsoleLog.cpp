/**
 * \file  CxConsoleLog.cpp
 * \brief logging to console
 */


#include <xLib/Log/CxConsoleLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxAutoCriticalSection.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCriticalSection CxConsoleLog::_ms_csConsole;
//---------------------------------------------------------------------------
/*explicit*/
CxConsoleLog::CxConsoleLog(
    const BOOL cbIsUseTimeStr
) :
    _m_bIsUseTimeStr(cbIsUseTimeStr)
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxConsoleLog::~CxConsoleLog() {

}
//---------------------------------------------------------------------------
BOOL
CxConsoleLog::bWrite(
    const TCHAR *pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

    //-------------------------------------
    //time
    std::string_t sTime;

    if (TRUE == _m_bIsUseTimeStr) {
        sTime = xT("[") + CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime) + xT("] ");
    } else {
        sTime = xT("");
    }

    //-------------------------------------
    //comment
    std::string_t sParam;
    va_list      palArgs;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write
    /*LOCK*/CxAutoCriticalSection SL(_ms_csConsole);

    std::tcout << sTime << sParam << std::endl;

    return TRUE;
}
//---------------------------------------------------------------------------
