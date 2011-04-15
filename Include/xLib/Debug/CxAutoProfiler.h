/****************************************************************************
* Class name:  CxAutoProfiler
* Description: auto code profiling
* File name:   CxAutoProfiler.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     05.07.2010 16:27:50
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Debug_CxAutoProfilerH
#define xLib_Debug_CxAutoProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxProfiler.h>
//---------------------------------------------------------------------------
class CxAutoProfiler : public CxNonCopyable {
	public:
		           CxAutoProfiler(const tString &csFilePath, CxProfiler::EMode pmMode, LPCTSTR pcszComment, ...);
	    virtual   ~CxAutoProfiler();
	
	private:
		CxProfiler _m_pfProfiler;
		tString    _m_sComment;
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxAutoProfilerH
