/**
 * \file  CxConsoleLog.cpp
 * \brief logging to console
 */


#include <xLib/Log/CxConsoleLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxAutoCriticalSection.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCriticalSection CxConsoleLog::_ms_csConsole;
//---------------------------------------------------------------------------
/*explicit*/
CxConsoleLog::CxConsoleLog(
    const bool cbIsUseTimeStr
) :
    _m_bIsUseTimeStr(cbIsUseTimeStr)
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxConsoleLog::~CxConsoleLog() {

}
//---------------------------------------------------------------------------
bool
CxConsoleLog::bWrite(
    const tchar_t *pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, false);

    //-------------------------------------
    //time
    std::tstring_t sTime;

    if (true == _m_bIsUseTimeStr) {
        sTime = xT("[") + CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime) + xT("] ");
    } else {
        sTime = xT("");
    }

    //-------------------------------------
    //comment
    std::tstring_t sParam;
    va_list      palArgs;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write
    /*LOCK*/CxAutoCriticalSection SL(_ms_csConsole);

    std::tcout << sTime << sParam << std::endl;

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
