/****************************************************************************
* Class name:  CXCheckBox
* Description: 
* File name:   CXCheckBox.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     24.07.2009 11:47:59
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <Xlib/WinControls/CXCheckBox.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXCheckBox::CXCheckBox() {
	//-------------------------------------
	//Override class name and style attributes.
	_m_sClassName     = "BUTTON";
	////_m_ulStyle        = WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX;
	////_m_ulExStyle      = 0;

	_m_iLeft          = 0;
	_m_iTop           = 0;
	_m_iWidth         = 100;
	_m_iHeight        = 23;
}
//---------------------------------------------------------------------------
CXCheckBox::~CXCheckBox() {

}
//---------------------------------------------------------------------------
BOOL CXCheckBox::bIsChecked() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(BM_GETCHECK, 0, 0) == BST_CHECKED;
}
//---------------------------------------------------------------------------
BOOL CXCheckBox::bCheck(BOOL bChecked) {
	/*DEBUG*///XASSERT(this->bIsWindow());

	return SendMessage(BM_SETCHECK, bChecked ? BST_CHECKED : BST_UNCHECKED, 0);
}
//---------------------------------------------------------------------------