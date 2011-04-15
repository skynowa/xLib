/****************************************************************************
* Class name:  CxOwnerDrawButton
* Description: 
* File name:   CxOwnerDrawButton.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.07.2009 21:38:38
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxOwnerDrawButtonH
#define XLib_Gui_CxOwnerDrawButtonH
//---------------------------------------------------------------------------
#include <XLib/GUI/CxWindow.h>
#include <XLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxOwnerDrawButton: public CxButtonBase {
	public:
		//-------------------------------------
		//константы

			     CxOwnerDrawButton();
		virtual ~CxOwnerDrawButton();
			
	    BOOL     bCreateRes       (INT iID, CxWindow *pwndParent);

		//-------------------------------------
		//сообщения


		//-------------------------------------
		//события

};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxOwnerDrawButtonH