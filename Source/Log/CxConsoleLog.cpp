/****************************************************************************
* Class name:  CxConsoleLog
* Description: logging to console
* File name:   CxConsoleLog.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:53:59
*
*****************************************************************************/


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
//DONE: CxConsoleLog (constructor)
CxConsoleLog::CxConsoleLog(BOOL bIsUseTimeStr) :
	_m_bIsUseTimeStr(bIsUseTimeStr)
{
	
}
//---------------------------------------------------------------------------
//DONE: ~CxConsoleLog (destructor)
CxConsoleLog::~CxConsoleLog() {

}
//---------------------------------------------------------------------------
//DONE: bWrite (write)
BOOL
CxConsoleLog::bWrite(LPCTSTR pcszFormat, ...) {
	/*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

	//-------------------------------------
	//time
	tString sTime;

	if (TRUE == _m_bIsUseTimeStr) {
		sTime = xT("[") + CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime) + xT("] ");
	} else {
		sTime = xT("");
	}

	//-------------------------------------
	//comment
	tString sParam;
	va_list palArgs = NULL;

	va_start(palArgs, pcszFormat);
	sParam = CxString::sFormatV(pcszFormat, palArgs);
	va_end(palArgs);	

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
