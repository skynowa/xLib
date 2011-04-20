/****************************************************************************
*	CXEdit
*
*****************************************************************************/


#include <Xlib/WinControls/CXEdit.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXEdit::CXEdit() {
	_m_sClassName = "EDIT";
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 100;
	_m_iHeight    = 20;
}
//---------------------------------------------------------------------------
BOOL CXEdit::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	_m_hWnd = ::CreateWindowEx(
					dwExStyles, 
					_m_sClassName.c_str(),	
					_m_sText.c_str(),					
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | dwStyles,		
					_m_iLeft,							
					_m_iTop,							
					_m_iWidth,							
					_m_iHeight,							
					hParent,							
					(HMENU)hmnuID,							
					(HINSTANCE)::GetWindowLong(hParent, GWL_HINSTANCE), 
					this); 

	if (_m_hWnd == NULL) {
		return FALSE;
	} 

	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------
LRESULT CXEdit::LimitText(UINT uiSize) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(EM_LIMITTEXT, uiSize, NULL);
}
//---------------------------------------------------------------------------

/*
void CopyEditToClipboard(HWND hWnd)
{
SendMessage(hWnd, EM_SETSEL, 0, 65535L);
SendMessage(hWnd, WM_COPY, 0 , 0);
SendMessage(hWnd, EM_SETSEL, 0, 0);
}
*/