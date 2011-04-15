/****************************************************************************
* Class name:  CxGroupBox
* Description: 
* File name:   CxGroupBox.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.07.2009 21:10:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxGroupBoxH
#define XLib_Gui_CxGroupBoxH
//---------------------------------------------------------------------------
#include <XLib/GUI/CxWindow.h>
#include <XLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxGroupBox: public CxButtonBase {
	public:
		//-------------------------------------
		//константы

		         CxGroupBox();
		virtual ~CxGroupBox();

		BOOL     bCreateRes(INT iID, CxWindow *pwndParent);

		//-------------------------------------
		//сообщения
					

		//-------------------------------------
		//события
};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxGroupBoxH