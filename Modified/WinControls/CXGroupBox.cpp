/****************************************************************************
*
*
*****************************************************************************/


#include <Xlib/WinControls/CXGroupBox.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXGroupBox::CXGroupBox() {
	_m_sClassName = "BUTTON";
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 50;
	_m_iHeight    = 50;
}
//---------------------------------------------------------------------------
BOOL CXGroupBox::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	_m_hWnd = ::CreateWindowEx(
				dwExStyles,
		        _m_sClassName.c_str(),  
				_m_sText.c_str(),      
				WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_GROUPBOX | dwStyles,  
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