/****************************************************************************
* Class name:  CxRadioButton
* Description: 
* File name:   CxRadioButton.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.07.2009 21:38:38
*
*****************************************************************************/


#ifndef XLib_Gui_CxRadioButtonH
#define XLib_Gui_CxRadioButtonH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/GUI/CxButtonBase.h>
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