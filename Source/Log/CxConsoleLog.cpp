/**
 * \file  CxConsoleLog.cpp
 * \brief logging to console
 */


#include <xLib/Log/CxConsoleLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxStdioFile.h>

#if defined(xOS_WIN)
    #include <xLib/Sync/CxAutoCriticalSection.h>
#elif defined(xOS_LINUX)

#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: static
#if defined(xOS_WIN)
    CxCriticalSection CxConsoleLog::_ms_csConsole;
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
//DONE: CxConsoleLog
CxConsoleLog::CxConsoleLog(BOOL bIsUseTimeStr) :
    _m_bIsUseTimeStr(bIsUseTimeStr)
{

}
//---------------------------------------------------------------------------
//DONE: ~CxConsoleLog
CxConsoleLog::~CxConsoleLog() {

}
//---------------------------------------------------------------------------
//DONE: bWrite (write)
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
    va_list palArgs;

    xVA_START(palArgs, pcszFormat);
    sParam = CxString::sFormatV(pcszFormat, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write
#if defined(xOS_WIN)
    /*LOCK*/CxAutoCriticalSection SL(_ms_csConsole);
#elif defined(xOS_LINUX)
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    ////--CxStdioFile::iPrintf(xT("%s%s\n"), sTime.c_str(), sParam.c_str());

    tcout << sTime << sParam << tendl;

    return TRUE;
}
//---------------------------------------------------------------------------
