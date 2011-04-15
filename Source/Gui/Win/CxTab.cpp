/****************************************************************************
* Class name:  CxTab
* Description: закладки
* File name:   CxTab.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     23.07.2009 13:11:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/



#include <XLib/Gui/CxTab.h>

#include <XLib/GUI/Resource.xrc.h>
#include <XLib/CxString.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxTab
CxTab::CxTab() {	
	LOG();

	//-------------------------------------
	//переопределяем параметры окна
	_m_sClassName     = xCXTAB_CONTROL_CLASS;
	_m_ulStyle        = xCXTAB_DEFAULT_WINDOW_STYLE;
	_m_ulStyleEx      = xCXTAB_DEFAULT_WINDOW_STYLE_EX;

	_m_iLeft          = 0;
	_m_iTop           = 0;
	_m_iWidth         = xCXTAB_DEFAULT_WIDTH;
	_m_iHeight        = xCXTAB_DEFAULT_HEIGHT;

	_m_bIsControl     = TRUE;
}
//---------------------------------------------------------------------------
//TODO: + ~CxTab
CxTab::~CxTab() {
	LOG();

	for (size_t i = 0; i < _m_vecLayouts.size(); ++ i) {
		/*DEBUG*/xASSERT(NULL != _m_vecLayouts.at(i));

		xDELETE_PTR(_m_vecLayouts.at(i));
	}
}
//---------------------------------------------------------------------------
//TODO: + bCreateRes
BOOL CxTab::bCreateRes(INT iID, HWND hParent) {
	/*DEBUG*/xASSERT_RET(0 < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != hParent, FALSE);

	_m_bRes = _bInitCommonControls(ICC_TAB_CLASSES);
	xCHECK_RET(FALSE == _m_bRes, FALSE);

	_m_bRes = CxWindow::bCreate(iID, hParent, _m_sClassName, 
							    CxResources::sGetText  (iID), 
							    CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID), 
							    CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID), 
							    CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
							    this);
	xCHECK_RET(FALSE == _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CxTab::bInsertTab(INT iLayoutID, LPTSTR lpCaption, INT iPos, INT iImage) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd,    FALSE);
	/*DEBUG*/xASSERT_RET(NULL !=  lpCaption, FALSE);
	/*DEBUG*/xASSERT_RET(0    <= iPos,       FALSE);

	INT  iIndex = - 1;

	TCITEM tci = {0};		
	tci.pszText    = lpCaption;
	tci.cchTextMax = 20;
	tci.mask       = TCIF_IMAGE | TCIF_TEXT;
	tci.iImage     = iImage;
	
	iIndex = (INT)pSendMessage(TCM_INSERTITEM, (WPARAM)(INT)iPos, (LPARAM)&tci);			
	/*DEBUG*/xASSERT_RET(- 1 != iIndex, FALSE);	//Returns the index of the new tab if successful, or -1 otherwise.

	tci.pszText = lpCaption;
    
    
    /*-----------------------*/
    //создать Layout (окно)
    CxLayout *pwndLayout = new CxLayout();
	/*DEBUG*/xASSERT_RET(NULL != pwndLayout, FALSE);

	_m_bRes = pwndLayout->bCreateRes(iLayoutID/*IDD_WND_SHEET*/, this->hGetHandle());
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	/*DEBUG*/::SetWindowText(pwndLayout->hGetHandle(), CxString::lexical_cast(iIndex).c_str());

    //положить Layout на вкладку
	_m_bRes = bPutLayout(pwndLayout->hGetHandle(), iIndex);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_vecLayouts.push_back(pwndLayout); 
	pwndLayout = NULL;
    /*-----------------------*/

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL CxTab::bShowTab(INT iPos, BOOL bShow) {	
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/xASSERT_RET(0    <= iPos,    FALSE);

	TCITEM tci = {0};		
	tci.mask   = TCIF_PARAM;
	
	_m_bRes = (BOOL)pSendMessage(TCM_GETITEM, (WPARAM)(INT)iPos, (LPARAM)&tci);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	HWND hLayout = reinterpret_cast<HWND>(tci.lParam);
    /*DEBUG*/xASSERT_RET(NULL != hLayout, FALSE);

	_m_bRes = ::ShowWindow(hLayout, bShow ? SW_SHOW : SW_HIDE);
	/*DEBUG*///not need

	_m_bRes = ::EnableWindow(hLayout, bShow ? TRUE : FALSE);
	/*DEBUG*///not need

	return TRUE;
}
//---------------------------------------------------------------------------
INT CxTab::iGetCurSel() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	INT iRes = - 1;

	iRes = TabCtrl_GetCurSel(this->hGetHandle());
	////iRes = (INT)pSendMessage(TCM_GETCURSEL, 0, 0);	//Returns the index of the selected tab if successful, or -1 if no tab is selected.
	/*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);	    
	
	return iRes;
}
//---------------------------------------------------------------------------
LRESULT CxTab::GetImageList()	{
	/*DEBUG*/xASSERT(bIsWindow());

	return pSendMessage(TCM_GETIMAGELIST, NULL, NULL);
}
//---------------------------------------------------------------------------
HIMAGELIST CxTab::SetImageList(HIMAGELIST lImageList) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

// #define TCM_SETIMAGELIST        (TCM_FIRST + 3)
// #define TabCtrl_SetImageList(hwnd, himl) \
// 		(HIMAGELIST)SNDMSG((hwnd), TCM_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)(himl))

	return (HIMAGELIST)pSendMessage(TCM_SETIMAGELIST, (WPARAM)NULL, (LPARAM)lImageList);
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL CxTab::bPutLayout(HWND hLayout, INT iPos) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/xASSERT_RET(NULL != hLayout,  FALSE);
	/*DEBUG*/xASSERT_RET(0    <= iPos,    FALSE);

	RECT rect = {0};		
	_m_bRes = ::GetClientRect(_m_hWnd, &rect);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	pSendMessage(TCM_ADJUSTRECT, 0, (LPARAM)&rect);
	/*DEBUG*///not return value

	_m_bRes = ::MoveWindow(hLayout, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	TCITEM tci = {0};	 
	tci.mask   = TCIF_PARAM;
	tci.lParam = reinterpret_cast<LPARAM>(hLayout);

	_m_bRes = pSendMessage(TCM_SETITEM, (WPARAM)(INT)iPos, (LPARAM)&tci);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------