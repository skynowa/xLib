/****************************************************************************
*	CXStatic
*
*****************************************************************************/


#include <Xlib/WinControls/CXStatic.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXStatic::CXStatic() {
	_m_sClassName = "STATIC";
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 75;
	_m_iHeight    = 20;
}
//---------------------------------------------------------------------------
BOOL CXStatic::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
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

	if (NULL == _m_hWnd) {
		return FALSE;
	} 

	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------