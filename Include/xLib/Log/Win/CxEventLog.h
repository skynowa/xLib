/****************************************************************************
* Class name:  CxEventLog
* Description: logging to "Event Log"
* File name:   CxEventLog.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:52:35
*
*****************************************************************************/


#ifndef xLib_Log_CxEventLogH
#define xLib_Log_CxEventLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxEventLog : public CxNonCopyable {
	public:
		        CxEventLog();
	   virtual ~CxEventLog();

	private:
};
//---------------------------------------------------------------------------
#endif	//xLib_Log_CxEventLogH



//http://www.kernel.org/doc/man-pages/online/pages/man3/syslog.3.html
