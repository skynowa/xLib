/****************************************************************************
*
*
*****************************************************************************/


#include <Xlib/WinControls/CXRadioButton.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXRadioButton::CXRadioButton() {
	_m_sClassName = "BUTTON";
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 50;
	_m_iHeight    = 25;
}
//---------------------------------------------------------------------------
BOOL CXRadioButton::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	_m_hWnd = ::CreateWindowEx(
					dwExStyles,
					_m_sClassName.c_str(),  
					_m_sText.c_str(), 
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | /*BS_RADIOBUTTON*/BS_AUTORADIOBUTTON | dwStyles,  
					_m_iLeft,		
					_m_iTop,		
					_m_iWidth,		
					_m_iHeight,		
					hParent,		
					(HMENU)hmnuID,			
					(HINSTANCE)::GetWindowLong(hParent, GWL_HINSTANCE), 
					this); 

	if (NULL == _m_hWnd) {
		return FALSE;
	} 

	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CXRadioButton::IsChecked() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(BM_GETCHECK, 0, 0) == BST_CHECKED;
}
//---------------------------------------------------------------------------
void CXRadioButton::Check(BOOL bChecked) {
	/*DEBUG*/XASSERT(bIsWindow());

	SendMessage(BM_SETCHECK, bChecked ? BST_CHECKED : BST_UNCHECKED, 0);
}
//---------------------------------------------------------------------------