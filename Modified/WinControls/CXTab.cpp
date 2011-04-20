/**********************************************************************
*	Класс CXTab (CXTab.cpp)
*
***********************************************************************/


#include <Xlib/WinControls/CXTab.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXTab::CXTab() {	
	_m_sClassName = WC_TABCONTROL;
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 650;
	_m_iHeight    = 350;	
}
//---------------------------------------------------------------------------
BOOL CXTab::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
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

	/*DEBUG*/XASSERT_RET(NULL != _m_hWnd, FALSE);

	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------
VOID CXTab::vInsertTab(LPSTR lpCaption, INT iPos, INT iImage) {
	/*DEBUG*/XASSERT(bIsWindow());

	TCITEM tci = {0};		
	tci.pszText    = lpCaption;
	tci.cchTextMax = 20;
	tci.mask       = TCIF_IMAGE | TCIF_TEXT;
	tci.iImage     = iImage;
	
	SendMessage(TCM_INSERTITEM, (WPARAM)(int)iPos, (LPARAM)&tci);			//??????????

	tci.pszText    = lpCaption;
}
//---------------------------------------------------------------------------
VOID CXTab::vAddDlg(HWND hPageDlg, INT nPos) {
	/*DEBUG*/XASSERT(bIsWindow());

	BOOL bRes = FALSE;

	RECT rect = {0};		
	::GetClientRect(_m_hWnd, &rect);
	
	SendMessage(TCM_ADJUSTRECT, 0, (LPARAM)&rect);
	
	bRes = ::MoveWindow(hPageDlg, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
	/*DEBUG*/XASSERT(FALSE != bRes);


	TCITEM tci = {0};	 
	tci.mask   = TCIF_PARAM;
	tci.lParam = reinterpret_cast<LPARAM>(hPageDlg);
	SendMessage(TCM_SETITEM, (WPARAM)nPos, (LPARAM)&tci);
}
//---------------------------------------------------------------------------
BOOL CXTab::bShowTab(INT nPos, BOOL bShow) {	
	/*DEBUG*/XASSERT(bIsWindow());

	BOOL bRes = FALSE;

	TCITEM tci = {0};		
	tci.mask   = TCIF_PARAM;
	SendMessage(TCM_GETITEM, (WPARAM)nPos, (LPARAM)&tci);
	
	HWND hPageDlg = reinterpret_cast<HWND>(tci.lParam);
	/*DEBUG*/XASSERT_RET(NULL != hPageDlg, FALSE);

	bRes = ::ShowWindow(hPageDlg, bShow ? SW_SHOW : SW_HIDE);
	/*DEBUG*///not need ???

	bRes = ::EnableWindow(hPageDlg, bShow ? TRUE : FALSE);
	/*DEBUG*///not need ???

	return TRUE;
}
//---------------------------------------------------------------------------
LRESULT CXTab::iGetCurrSel() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(TCM_GETCURSEL, 0, 0);
}
//---------------------------------------------------------------------------
LRESULT CXTab::GetImageList()	{
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(TCM_GETIMAGELIST, NULL, NULL);
}
//---------------------------------------------------------------------------
HIMAGELIST CXTab::SetImageList(HIMAGELIST lImageList) {
	/*DEBUG*/XASSERT(bIsWindow());

// #define TCM_SETIMAGELIST        (TCM_FIRST + 3)
// #define TabCtrl_SetImageList(hwnd, himl) \
// 		(HIMAGELIST)SNDMSG((hwnd), TCM_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)(himl))

	return (HIMAGELIST)SendMessage(TCM_SETIMAGELIST, (WPARAM)NULL, (LPARAM)lImageList);
}
//---------------------------------------------------------------------------