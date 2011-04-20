/****************************************************************************
*	CXSubclassWnd
*
*****************************************************************************/


#include <Xlib/WinControls/CXSubclassWnd.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXSubclassWnd::CXSubclassWnd() :
	_m_wpOrigWndProc(NULL)
{
}
//---------------------------------------------------------------------------
VOID CXSubclassWnd::Subclass() {
	//The "this" pointer is stored in a user window long
	pliSetLongPtr/*::SetWindowLongPtr*/(_m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	_m_wpOrigWndProc = /*(DLGPROC)*/(WNDPROC)liSetLong/*::SetWindowLong*/(_m_hWnd, GWL_WNDPROC/*DWLP_DLGPROC*/, (LONG)BaseWindowProc);
}
//---------------------------------------------------------------------------
//Window Procedure called by windows (static)
LRESULT CALLBACK CXSubclassWnd::BaseWindowProc(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam, PBOOL pbProcessed) {
	//The window procedure has to be static
	//Here I get the "this" pointer from the user window long and redirect to a non static member
	return ((CXSubclassWnd *)liGetLong/*::GetWindowLong*/(hWnd, GWLP_USERDATA))->WindowProc(hWnd, uiMessage, wParam, lParam, pbProcessed);
}
//---------------------------------------------------------------------------
//Window procedure
LRESULT CXSubclassWnd::WindowProc(HWND hWnd, UINT uiMessage, WPARAM wParam, LPARAM lParam, PBOOL pbProcessed) {
	bOnMessage(hWnd, uiMessage, wParam, lParam, pbProcessed);
	/*DEBUG*///not need
	
	return ::CallWindowProc(_m_wpOrigWndProc, hWnd, uiMessage, wParam, lParam);
	/*DEBUG*///not need
}
//---------------------------------------------------------------------------
//This method has to be overriden
BOOL CXSubclassWnd::bCreate(HWND hParent, HMENU hmnuID, ULONG ulStyles, ULONG ulExStyles) {
	return FALSE;
}
//---------------------------------------------------------------------------