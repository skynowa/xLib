/****************************************************************************
* Class name:  CxCheckBox
* Description: 
* File name:   CxCheckBox.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     24.07.2009 11:47:59
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxCheckBoxH
#define XLib_Gui_CxCheckBoxH
//---------------------------------------------------------------------------
#include <XLib/GUI/CxWindow.h>
#include <XLib/GUI/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxCheckBox: public CxButtonBase {
	public:
		//-------------------------------------
		//константы

		//состояния
		enum ECheckState {
			csUknown    = - 1,
			csChecked	= BST_CHECKED,
			csGrayed    = BST_INDETERMINATE, 
			csUnchecked = BST_UNCHECKED,	
		};	

			        CxCheckBox     ();
		virtual    ~CxCheckBox     ();

		BOOL        bCreateRes     (INT iID, CxWindow *pwndParent);

		//-------------------------------------
		//сообщения
		ECheckState csGetState     ();							
		BOOL        bSetState      (CxCheckBox::ECheckState csCheckState);
		BOOL        bSetAllowGrayed(BOOL bFlag);

		//-------------------------------------
		//события

};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxCheckBoxH