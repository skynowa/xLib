/****************************************************************************
* Class name:  CXCheckBox
* Description: 
* File name:   CXCheckBox.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     24.07.2009 11:47:59
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CXCheckBox_H
#define CXCheckBox_H
//---------------------------------------------------------------------------
#include <Xlib/WinControls/CXWnd.h>
//---------------------------------------------------------------------------
class CXCheckBox: public CXWnd {
	public:
					    CXCheckBox();
					   ~CXCheckBox();

		/*virtual*/BOOL bCreate   (INT iID, HWND hParent, INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulExStyle);
		BOOL            bIsChecked();
		BOOL            bCheck    (BOOL bChecked);
};
//---------------------------------------------------------------------------
#endif