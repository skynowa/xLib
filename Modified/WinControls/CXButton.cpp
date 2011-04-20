/****************************************************************************
*
*
*****************************************************************************/


#include <Xlib/WinControls/CXButton.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXButton::CXButton() {
	_m_sClassName = "BUTTON";
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 75;
	_m_iHeight    = 23;

	////OnCommand     = NULL;
}
//---------------------------------------------------------------------------
BOOL CXButton::bCreate(HWND hParent, HMENU hmnuID, ULONG ulStyles, ULONG ulExStyles) {
	_m_hWnd = ::CreateWindowEx(
						ulExStyles, 
						_m_sClassName.c_str(),	
						_m_sText.c_str(),					
						WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ulStyles,		
						_m_iLeft,							
						_m_iTop,							
						_m_iWidth,							
						_m_iHeight,							
						hParent,							
						hmnuID,							
						(HINSTANCE)::GetWindowLong(hParent, GWL_HINSTANCE), 
						this); 

	/*DEBUG*/XASSERT_RET(NULL != _m_hWnd, FALSE);

	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------
//	g_Edt.bInit(g_hDlgMain, IDC_EDIT1);
BOOL CXButton::bCreateRes(HWND hParent, INT iResID) {
	_m_hWnd = ::GetDlgItem(hParent, iResID);
	/*DEBUG*/XASSERT_RET(NULL != _m_hWnd, FALSE);
	
	
	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------