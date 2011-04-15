/****************************************************************************
* Class name:  CxWndLog
* Description: logging to window
* File name:   CxWndLog.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.06.2009 17:44:10
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Log_CxWndLogH
#define xLib_Log_CxWndLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxWndLog : public CxNonCopyable {
	public:
		//window classes
		enum EWindowClass {
			wcListBox
		};	

								 CxWndLog(EWindowClass wcWC);
		virtual 				~CxWndLog();

   		BOOL                     bWrite  (HWND hWnd, LPCTSTR pcszFormat, ...);
   		
   	private:	
   		EWindowClass             _m_eWC;
   		static CxCriticalSection _ms_csListBox;  //Mutex
};
//---------------------------------------------------------------------------
#endif
