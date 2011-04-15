/****************************************************************************
* Class name:  CxStatic
* Description: работа с статическим полем
* File name:   CxStatic.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     24.07.2009 11:20:41
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxStaticH
#define XLib_Gui_CxStaticH
//---------------------------------------------------------------------------
#include <XLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxStatic: public CxWindow {
	public:
		         CxStatic  ();
		virtual ~CxStatic  ();

		BOOL     bCreateRes(INT iID, CxWindow *pwndParent);
		
		//-------------------------------------
		//сообщения


		//-------------------------------------
		//события
};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxStaticH
