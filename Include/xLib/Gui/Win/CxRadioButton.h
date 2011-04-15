/****************************************************************************
* Class name:  CxRadioButton
* Description: 
* File name:   CxRadioButton.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.07.2009 21:38:38
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxRadioButtonH
#define XLib_Gui_CxRadioButtonH
//---------------------------------------------------------------------------
#include <XLib/GUI/CxWindow.h>
#include <XLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxRadioButton: public CxButtonBase {
	public:
		//-------------------------------------
		//константы

		//состояния
		enum ECheckState {
			csUknown    = - 1,
			csChecked	= BST_CHECKED,
			csUnchecked	= BST_UNCHECKED,	
		};	

			        CxRadioButton();
		virtual    ~CxRadioButton();
			
	    BOOL        bCreateRes   (INT iID, CxWindow *pwndParent);

		//-------------------------------------
		//сообщения
		ECheckState bstGetState  ();							
		BOOL        bSetState    (CxRadioButton::ECheckState csCheckState);					

		//-------------------------------------
		//события
};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxRadioButtonH