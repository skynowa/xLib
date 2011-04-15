/****************************************************************************
* Class name:  CxRebar
* Description: работа с ребаром
* File name:   CxRebar.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     24.07.2009 11:20:41
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxRebarH
#define XLib_Gui_CxRebarH
//---------------------------------------------------------------------------
#include <XLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxRebar : public CxWindow {
	public:
		enum AlignFlags	{
			AlignTop    = CCS_TOP,
			AlignBottom = CCS_BOTTOM,
			AlignLeft   = CCS_LEFT,
			AlignRight  = CCS_RIGHT,
		};

			 CxRebar ();
			~CxRebar();

		HWND Create(HWND hwndOwner,AlignFlags afFlag);
		VOID InsertBand(HWND hClientWnd,TCHAR* szName);
		BOOL DeleteBand(int numBand);
		VOID AutoSize();
};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxRebarH