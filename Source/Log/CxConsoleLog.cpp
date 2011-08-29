/**
 * \file  CxConsoleLog.cpp
 * \brief logging to console
 */


#include <xLib/Log/CxConsoleLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>

#if defined(xOS_WIN)
    #include <xLib/Sync/CxAutoCriticalSection.h>
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if defined(xOS_WIN)
    CxCriticalSection CxConsoleLog::_ms_csConsole;
#endif
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
    LPCTSTR pcszFormat, ...
)
{
    /*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

    //-------------------------------------
    //time
    std::tstring sTime;

    if (TRUE == _m_bIsUseTimeStr) {
        sTime = xT("[") + CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime) + xT("] ");
    } else {
        sTime = xT("");
    }

    //-------------------------------------
    //comment
    std::tstring sParam;
    va_list      palArgs;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write
#if defined(xOS_WIN)
    /*LOCK*/CxAutoCriticalSection SL(_ms_csConsole);
#endif

    std::tcout << sTime << sParam << std::endl;

    return TRUE;
}
//---------------------------------------------------------------------------
