/****************************************************************************
* Class name:  CxWaitCursor
* Description: wait cursor
* File name:   CxWaitCursor.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.06.2009 19:08:17
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Gui_CxWaitCursorH
#define xLib_Gui_CxWaitCursorH
//---------------------------------------------------------------------------
#include <xLib/xCommon.h>
//---------------------------------------------------------------------------
class CxWaitCursor : public CxNonCopyable {
	public:
		        CxWaitCursor();
	           ~CxWaitCursor();

		BOOL    bRestore    ();
		
	private:
		HCURSOR _m_hCursor;
};
//---------------------------------------------------------------------------
#endif	//xLib_Gui_CxWaitCursorH