/**********************************************************************
*	Класс CXTimer (CXTimer.cpp)
*
***********************************************************************/


#include <Xlib/WinControls/CXTimer.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXTimer::CXTimer() {	
	_m_sClassName = WC_TABCONTROL;
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 650;
	_m_iHeight    = 350;	
}
//---------------------------------------------------------------------------
BOOL CXTimer::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	if (FALSE == bInitCommonControls(ICC_TAB_CLASSES)) {
		return FALSE;
	}

	_m_hWnd = ::CreateWindowEx(
						dwExStyles, 
						_m_sClassName.c_str(), 
						NULL, 
						WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | dwStyles,  
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