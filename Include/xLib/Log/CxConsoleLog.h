/****************************************************************************
* Class name:  CxConsoleLog
* Description: logging to console
* File name:   CxConsoleLog.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.06.2009 17:53:59
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Log_CxConsoleLogH
#define xLib_Log_CxConsoleLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxConsoleLog : public CxNonCopyable {
	public:	
		                         CxConsoleLog(BOOL bIsUseTimeStr);
		virtual                 ~CxConsoleLog();

		BOOL                     bWrite      (LPCTSTR pcszFormat, ...); 
		
	private:		
    #if defined(xOS_WIN)
        static CxCriticalSection _ms_csConsole;
    #elif defined(xOS_LINUX)

    #endif

		BOOL                     _m_bIsUseTimeStr;
};
//---------------------------------------------------------------------------
#endif	//xLib_Log_CxConsoleLogH
