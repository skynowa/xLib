/****************************************************************************
*	CXWnd
*
*****************************************************************************/


#include <Xlib/WinControls/CXWnd.h>
#include <XLib/Debug/xassert.h>

#pragma comment(lib, "comctl32.lib")
//---------------------------------------------------------------------------
CXWnd::CXWnd() :
	_m_hWnd        (NULL),
	_m_hMenu       (NULL),
	_m_sClassName  ("CXWnd"),
	_m_DefaultFont (hfCreateDefaultFont()),
	_m_sText       ("")
{
	OnClose        = NULL;
	OnDestroy      = NULL;
	OnNotify       = NULL;
	OnCreate       = NULL;
	OnCommand      = NULL;
}
//---------------------------------------------------------------------------
//Window Procedure called by windows (static)  
LRESULT CALLBACK CXWnd::BaseWindowProc(HWND hWnd, UINT uiMgs, WPARAM wParam, LPARAM lParam) {
	/*DEBUG*/XASSERT(::IsWindow(hWnd));

	//A pointer to the current class (this) is saved into the window with
	//SetWindowLongPtr. Why ? Because WndProc is called as a static method (it's not supposed to be a class method at first)
	//The message handling is then deferred to OnMessage which can use the this pointer.
	CXWnd *pWnd       = NULL;
	BOOL   bProcessed = FALSE;

	if (/*WM_NCCREATE*/WM_CREATE == uiMgs) {
		CREATESTRUCT *pCS = (CREATESTRUCT*)lParam;

		pWnd = (CXWnd *)pCS->lpCreateParams;
		pliSetLongPtr/*::SetWindowLongPtr*/(hWnd, GWLP_USERDATA, (LONG_PTR)pWnd);
	} else {
		pWnd = (CXWnd *)pliGetLongPtr/*::GetWindowLongPtr*/(hWnd, GWLP_USERDATA);  //WND
	}

	if (NULL == pWnd) {
		if (TRUE == bIsDialog(hWnd)) {
			//диалог
			return pWnd->WindowProc(hWnd, uiMgs, wParam, lParam, &bProcessed);
		} else {
			//окно
			return ::DefWindowProc(hWnd, uiMgs, wParam, lParam);
		}
	} else {
		return pWnd->WindowProc(hWnd, uiMgs, wParam, lParam, &bProcessed);
	} 
}
//---------------------------------------------------------------------------
//Window Procedure
LRESULT CXWnd::WindowProc(HWND hWnd, UINT uiMgs, WPARAM wParam, LPARAM lParam, PBOOL pbProcessed) {
	/*DEBUG*/XASSERT(::IsWindow(hWnd));

	if (FALSE == bOnMessage(hWnd, uiMgs, wParam, lParam, pbProcessed)) {
		if (FALSE != bIsDialog(hWnd)) {
			//диалог
			return 0;
		} else {
			//окно
			return ::DefWindowProc(hWnd, uiMgs, wParam, lParam);
		}
	} else {
		return 0;  
	} 
}
//---------------------------------------------------------------------------
BOOL CXWnd::bOnMessage(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam, PBOOL pbProcessed) {
	///////*DEBUG*/XASSERT(::IsWindow(hWnd));

	//////switch (uiMsg) { 
	//////	case WM_CREATE:
	//////		{
	//////			if (NULL != OnCreate) {
	//////				OnCreate(wParam, lParam);
	//////			} 
	//////		}
	//////		return TRUE;

		//////case WM_COMMAND:
		//////	{	
		//////		MessageBox(0, "WM_COMMAND", "", MB_OK);
		//////		//if (NULL != OnCommand) {
		//////			OnCommand(wParam, lParam);
		//////		//} 
		//////	}
		//////	return TRUE;

	//////	case WM_MOUSEMOVE:
	//////		{
	//////			////if (NULL != OnMouseMove) {
	//////			////	OnMouseMove(wParam, (INT)LOWORD(lParam), (INT)HIWORD(lParam));
	//////			////} 
	//////		}
	//////		return TRUE;

	//////	case WM_NOTIFY:
	//////		{
	//////			if (NULL != OnNotify) {
	//////				OnNotify(wParam, lParam);
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_LBUTTONUP:
	//////		{
	//////			if (NULL != OnMouseLeftUp) {
	//////				OnMouseLeftUp(wParam, (INT)LOWORD(lParam), (INT)HIWORD(lParam));
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_LBUTTONDBLCLK:
	//////		{
	//////			if (NULL != OnDoubleClick) {
	//////				OnDoubleClick();
	//////			}
	//////		} 
	//////		return TRUE;

	//////	case WM_MOVE:
	//////		{
	//////			////_m_iLeft = LOWORD(lParam);
	//////			////_m_iTop  = HIWORD(lParam);
	//////		}
	//////		return TRUE;

	//////	case WM_CHAR:
	//////		{
	//////			if (NULL != OnChar) {
	//////				OnChar(wParam, lParam);
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_KEYDOWN:
	//////		{
	//////			if (NULL != OnKeyDown) {
	//////				OnKeyDown(wParam, lParam);
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_KEYUP:
	//////		{
	//////			if (NULL != OnKeyUp) {
	//////				OnKeyUp(wParam, lParam);
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_DEADCHAR:
	//////		{
	//////			if (NULL != OnDeadChar) {
	//////				OnDeadChar(wParam, lParam);
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_CONTEXTMENU:
	//////		{
	//////			if (NULL != OnContextMenu) {
	//////				OnContextMenu((HWND)wParam, LOWORD(lParam), HIWORD(lParam));
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_SIZE:
	//////		{
	//////			//if (NULL != OnResize) {
	//////			//	_m_iWidth  = LOWORD(lParam); //_rect.right-_rect.left;
	//////			//	_m_iHeight = HIWORD(lParam); //_rect.bottom-_rect.top;

	//////			//	OnResize(_m_iWidth, _m_iHeight, wParam);
	//////			//} 
	//////		}
	//////		return TRUE;

	//////	case WM_SIZING:
	//////		{
	//////			if (NULL != OnResizing) {
	//////				OnResizing(wParam, (LPRECT)lParam);
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_TIMER:
	//////		{
	//////			if (NULL != OnTimer) {
	//////				OnTimer(wParam, lParam);
	//////			} 
	//////		}
	//////		return TRUE;

	//////	case WM_CLOSE:
	//////		{
	//////			if (NULL != OnClose) {
	//////				OnClose();
	//////			} 
	//////		}
	//////	    return TRUE;

	//////	case WM_DESTROY:
	//////		{
	//////			if (NULL != OnDestroy) {
	//////				OnDestroy();
	//////			} 
	//////			::PostQuitMessage(0); 
	//////		}
	//////		return TRUE;

	//////	default:
	//////		return FALSE;
	//////}

	////return TRUE;


	//This may be overridden to process messages.
	////*pbProcessed = FALSE;
	
	return NULL;
}
//---------------------------------------------------------------------------
BOOL CXWnd::bInitCommonControls(ULONG ulFlags) {
	BOOL bRes = FALSE;

	INITCOMMONCONTROLSEX iccx = {0};
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC  = ulFlags;
	
	bRes = ::InitCommonControlsEx(&iccx);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
INT CXWnd::iGetID() {
	/*DEBUG*/XASSERT(::IsWindow(_m_hWnd));

	INT iRes = 0;

	iRes = ::GetDlgCtrlID(_m_hWnd);
	/*DEBUG*/XASSERT_RET(0 != iRes, 0);

	return iRes;
}
//---------------------------------------------------------------------------
BOOL CXWnd::bSetText(const std::string &csText) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	
	BOOL bRes = FALSE;

	_m_sText = csText;
	bRes = ::SetWindowText(_m_hWnd, csText.c_str());
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
std::string CXWnd::sGetText() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), "");
	
	std::string sRes   = "";
	const INT   ciSize = ::GetWindowTextLength(_m_hWnd);
	if (ciSize > 0) {
		sRes.resize(ciSize + 1);
		::GetWindowText(_m_hWnd, &sRes[0], ciSize + 1);
		sRes.resize(ciSize);
	}

	return sRes;
}
//---------------------------------------------------------------------------
HWND CXWnd::GetHandle() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), NULL);
	
	return this->_m_hWnd;
}
//---------------------------------------------------------------------------
HFONT CXWnd::GetFont() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), NULL);
	
	return (HFONT)SendMessage(WM_GETFONT, 0, 0);
}
//---------------------------------------------------------------------------
BOOL CXWnd::SetFont(HFONT hFont) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	
	return (BOOL)SendMessage(WM_SETFONT, (WPARAM)hFont, FALSE);
}
//---------------------------------------------------------------------------
HFONT CXWnd::hfCreateDefaultFont() {
	/*DEBUG*///??XASSERT_RET(bIsWindow(), NULL);
	
	HFONT hRes = NULL;

	hRes = ::CreateFont(- 11, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma");
	/*DEBUG*/XASSERT_RET(NULL != hRes, NULL);

	return hRes;
}
//---------------------------------------------------------------------------
BOOL CXWnd::SetDefaultFont() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	
	return SetFont(_m_DefaultFont);
}
//---------------------------------------------------------------------------
LOGFONT CXWnd::GetLogicalFont() {
	/*DEBUG*///////////XASSERT_RET(bIsWindow(), (LPVOID)NULL);  ??????????????????????
	BOOL bRes = FALSE;

	LOGFONT lfFont = {0};
	bRes = ::GetObject(GetFont(), sizeof(LOGFONT), &lfFont);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, lfFont);

	return lfFont;
}
//---------------------------------------------------------------------------
INT CXWnd::GetWidth() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), - 1);
	
	return _m_iWidth;
}
//---------------------------------------------------------------------------
INT CXWnd::GetHeight() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), - 1);
	
	return _m_iHeight;
}
//---------------------------------------------------------------------------
INT CXWnd::GetLeft() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), - 1);
	
	return _m_iLeft;
}
//---------------------------------------------------------------------------
INT CXWnd::GetTop() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), - 1);
	
	return _m_iTop;
}
//---------------------------------------------------------------------------
BOOL CXWnd::bSetWindowPos(HWND hWndInsertAfter, INT X, INT Y, INT cx, INT cy, UINT uFlags) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);

	BOOL bRes = FALSE;

	_m_iLeft   = X;
	_m_iTop    = Y;
	_m_iWidth  = cx;
	_m_iHeight = cy;

	bRes = ::SetWindowPos(_m_hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CXWnd::bSetSize(INT Width, INT Height) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	
	BOOL bRes = FALSE;

	_m_iWidth  = Width;
	_m_iHeight = Height;
	
	bRes = bSetWindowPos(NULL, 0, 0, Width, Height, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	return bRes;	
}
//---------------------------------------------------------------------------
BOOL CXWnd::bSetPos(INT Left, INT Top) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);

	BOOL bRes = FALSE;
	
	_m_iLeft = Left;
	_m_iTop  = Top;

	bRes = bSetWindowPos(NULL, Left, Top, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	return bRes;
}
//---------------------------------------------------------------------------
BOOL CXWnd::Align(HWND hParent, HWND hChild) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	
	BOOL bRes = FALSE;

	RECT rect = {0};		
	bRes = ::GetClientRect(hParent, &rect);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	bRes = ::MoveWindow(hChild, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CXWnd::SetRect(RECT Rect) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);

	BOOL bRes = FALSE;
	
	_m_iWidth  = Rect.right  - Rect.left;
	_m_iHeight = Rect.bottom - Rect.top;
	_m_iLeft   = Rect.left;
	_m_iTop    = Rect.top;

	bRes = bSetWindowPos(NULL, _m_iLeft, _m_iTop, _m_iWidth, _m_iHeight, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	return TRUE;
}
//---------------------------------------------------------------------------
RECT CXWnd::GetRect() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), RECT()); 
	
	RECT rectRes = {0};

	BOOL bRes = FALSE;
	bRes = ::GetWindowRect(_m_hWnd, &rectRes);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, RECT());    

	return rectRes;
}
//---------------------------------------------------------------------------
BOOL CXWnd::bDestroy() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);

	BOOL bRes = FALSE;

	bRes = ::DestroyWindow(_m_hWnd);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CXWnd::Close() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);

	return (BOOL)SendMessage(WM_CLOSE, NULL, NULL);
}
//---------------------------------------------------------------------------
BOOL CXWnd::Enable(BOOL Enabled) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need

	return ::EnableWindow(_m_hWnd, Enabled);
}
//---------------------------------------------------------------------------
HMENU CXWnd::GetMenu() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), HMENU());  
	
	return _m_hMenu;
}
//---------------------------------------------------------------------------
BOOL CXWnd::SetMenu(HMENU Value) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	
	_m_hMenu = Value;

	return TRUE;
}
//---------------------------------------------------------------------------
HWND CXWnd::SetFocus() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need

	return ::SetFocus(_m_hWnd);
}
//---------------------------------------------------------------------------
BOOL CXWnd::SetRedraw(BOOL Redraw) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	
	return (BOOL)SendMessage(WM_SETREDRAW, Redraw, NULL);
}
//---------------------------------------------------------------------------
BOOL CXWnd::Invalidate(BOOL bErase) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need
	
	return ::InvalidateRect(_m_hWnd, NULL, bErase);
}
//---------------------------------------------------------------------------
BOOL CXWnd::Invalidate(LPRECT Rect, BOOL bErase) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need
	
	return ::InvalidateRect(_m_hWnd, Rect, bErase);
}
//---------------------------------------------------------------------------
BOOL CXWnd::Validate() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need
	
	return ::ValidateRect(_m_hWnd, NULL);
}
//---------------------------------------------------------------------------
BOOL CXWnd::Validate(LPRECT Rect) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need
	
	return ::ValidateRect(_m_hWnd, Rect);
}
//---------------------------------------------------------------------------
BOOL CXWnd::bShow(INT iCmdShow) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need
	
	INT iRes = - 1;
	/*iCmdShow
		SW_FORCEMINIMIZE
		SW_HIDE
		SW_MAXIMIZE
		SW_MINIMIZE
		SW_RESTORE
		SW_SHOW
		SW_SHOWDEFAULT
		SW_SHOWMAXIMIZED
		SW_SHOWMINIMIZED
		SW_SHOWMINNOACTIVE
		SW_SHOWNA
		SW_SHOWNOACTIVATE
		SW_SHOWNORMAL*/

	iRes = ::ShowWindow(_m_hWnd, iCmdShow);
	/*DEBUG*/XASSERT_RET(0 == iRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CXWnd::bUpdate() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);

	BOOL bRes = FALSE;

	bRes = ::UpdateWindow(_m_hWnd);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CXWnd::bMove(INT X, INT Y, INT nWidth, INT nHeight, BOOL bRepaint) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need

	return ::MoveWindow(_m_hWnd, X, Y, nWidth, nHeight, bRepaint);
}
//---------------------------------------------------------------------------
BOOL CXWnd::IsVisible() {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need
	
	return ::IsWindowVisible(_m_hWnd);
}
//---------------------------------------------------------------------------
BOOL CXWnd::bIsWindow() {
	/*DEBUG*///--XASSERT(bIsWindow(_m_hWnd));
	/*DEBUG*///not need

	return ::IsWindow(_m_hWnd);
}
//---------------------------------------------------------------------------
BOOL CXWnd::bIsDialog(HWND hWnd) {
	/*DEBUG*/////XASSERT(bIsWindow(_m_hWnd));
	/*DEBUG*///

	UINT uiRes = 0;

	uiRes = ::GetClassWord(hWnd, GCW_ATOM);
	/*DEBUG*/XASSERT_RET(0 != uiRes, FALSE);
	
	CHECK_RET(32770 != uiRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
LRESULT CXWnd::SendMessage(UINT uiMsg, WPARAM wParam, LPARAM lParam) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need ???????

	//int __fastcall Perform(unsigned Msg, int WParam, int LParam);
	return ::SendMessage(_m_hWnd, uiMsg, wParam, lParam);
}
//---------------------------------------------------------------------------
LRESULT CXWnd::PostMessage(UINT uiMsg, WPARAM wParam, LPARAM lParam) {
	/*DEBUG*/XASSERT_RET(bIsWindow(), FALSE);
	/*DEBUG*///not need ???????

	//int __fastcall Perform(unsigned Msg, int WParam, int LParam);
	return ::PostMessage(_m_hWnd, uiMsg, wParam, lParam);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
LONG_PTR CXWnd::pliSetLongPtr(HWND hWnd, INT iIndex, LONG_PTR pliNewLong) {
	LONG_PTR pliRes = NULL;
	
	pliRes = ::SetWindowLongPtr(hWnd, iIndex, pliNewLong);
	/*DEBUG*///XASSERT_RET(0 != pliRes, 0);

	return pliRes;
}
LONG_PTR CXWnd::pliGetLongPtr(HWND hWnd, INT iIndex) {
	LONG_PTR pliRes = NULL;

	pliRes = ::GetWindowLongPtr(hWnd, iIndex);
	/*DEBUG*///XASSERT_RET(0 != pliRes, 0);

	return pliRes;
}
//---------------------------------------------------------------------------
LONG CXWnd::liSetLong(HWND hWnd, INT iIndex, LONG liNewLong) {
	LONG liRes = 0;

	liRes = ::SetWindowLong(hWnd, iIndex, liNewLong);
	/*DEBUG*///XASSERT_RET(0 != liRes, 0);

	return liRes;
}
LONG CXWnd::liGetLong(HWND hWnd, INT iIndex) {
	LONG liRes = 0;

	liRes = ::GetWindowLong(hWnd, iIndex);
	/*DEBUG*///XASSERT_RET(0 != liRes, 0);

	return liRes;
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

//---------------------------------------------------------------------------