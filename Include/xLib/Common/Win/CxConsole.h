/****************************************************************************
* Class name:  CxConsole
* Description: console
* File name:   CxConsole.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     09.09.2010 10:06:20
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Coomon_Win_CxConsoleH
#define xLib_Coomon_Win_CxConsoleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxConsole : public CxNonCopyable {
	public:
			                            CxConsole     (); 
		virtual                        ~CxConsole     ();

		BOOL                            bSetTextColor (UINT uiColor); 
		BOOL                            bEnableClose  (BOOL bFlag); 
		tString                         sGetTitle     (); 
		BOOL                            bSetTitle     (const tString &csTitle); 
		BOOL                            bSetFullScreen();
		BOOL                            bClear        (); 


		tString                         sRead         ();
		BOOL	                        bWrite  	  (const tString &csStr);
		BOOL	                        bWriteLine	  (const tString &csStr);
		BOOL                            bWriteErrLine (const tString &csStr); 
		BOOL                            bCenterWindow ();
		BOOL                            bPrompt       (const tString &csPrompt, tString *psAnswer);

	private:
		BOOL                            _m_bRes;
		HWND                            _m_hWnd; 
		HMENU                           _m_hMenu; 
		CxHandleT<INVALID_HANDLE_VALUE> _m_hStdIn; 
		CxHandleT<INVALID_HANDLE_VALUE> _m_hStdOut; 

		HWND                     	    hGetWndHandle (); 
		HMENU                    		hGetMenuHandle(BOOL bRevert); 
 
};
//---------------------------------------------------------------------------
#endif	//xLib_Coomon_Win_CxConsoleH
