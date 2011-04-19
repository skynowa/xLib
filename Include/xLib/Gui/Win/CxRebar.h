/****************************************************************************
* Class name:  CxRebar
* Description: работа с ребаром
* File name:   CxRebar.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     24.07.2009 11:20:41
*
*****************************************************************************/


#ifndef XLib_Gui_CxRebarH
#define XLib_Gui_CxRebarH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
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