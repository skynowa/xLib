/****************************************************************************
* Class name:  CxDbLog
* Description: logging to DB
* File name:   CxDbLog.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.06.2009 17:55:15
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Log_CxDbLogH
#define xLib_Log_CxDbLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxDbLog : public CxNonCopyable {
	public:
		        CxDbLog();
	   virtual ~CxDbLog();

	private:
};
//---------------------------------------------------------------------------
#endif	//xLib_Log_CxDbLogH
