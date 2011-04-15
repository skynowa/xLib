/****************************************************************************
* Class name:  CxCpuUsage
* Description: cpu usage
* File name:   CxCpuUsage.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     07.02.2011 21:57:45
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_Win_CxCpuUsageH
#define xLib_Common_Win_CxCpuUsageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxCpuUsage : CxNonCopyable {
	public:
		              CxCpuUsage ();
		virtual      ~CxCpuUsage ();

		INT           GetCpuUsage();
		INT           GetCpuUsage(LPCTSTR pProcessName);
		INT           GetCpuUsage(DWORD dwProcessID);

		BOOL          EnablePerformaceCounters(BOOL bEnable = TRUE);

	private:
		bool		  m_bFirstTime;
		LONGLONG	  m_lnOldValue;
		LARGE_INTEGER m_OldPerfTime100nSec;
};
//---------------------------------------------------------------------------
#endif	//xLib_Common_Win_CxCpuUsageH

