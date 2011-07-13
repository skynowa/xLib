/****************************************************************************
*	bTest_CxComboBox.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxComboBox ()
BOOL CWndMain::bTest_CxComboBox(CxComboBox &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);


	//CxComboBox::bCreateRes
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxComboBox::iFindStringExact
	{
		#if (xWINVER >= xWIN32_95)
		//INT iFindStringExact(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: iRes = iFindStringExact(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_95
	}

	//CxComboBox::bGetCount
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetCount();
		//TODO: bRes = bGetCount();
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bGetCueBannerText
	{
		#if (xWINVER >= xWIN32_VISTA)
		//BOOL bGetCueBannerText(LPWSTR pwszText, INT iTextSize);
		//TODO: bRes = bGetCueBannerText(LPWSTR pwszText, INT iTextSize);
		//TODO: xASSERT(FALSE != bRes);
		#endif //xWIN32_VISTA
	}

	//CxComboBox::iGetCurSel
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetCurSel();
		//TODO: iRes = iGetCurSel();
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bGetDroppedControlRect 
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetDroppedControlRect (RECT *prcRect);
		//TODO: bRes = bGetDroppedControlRect (RECT *prcRect);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iGetDroppedState
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetDroppedState();
		//TODO: iRes = iGetDroppedState();
		//TODO: xASSERT(FALSE != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::uiGetExtendedUI
	{
		#if (xWINVER >= xWIN32_31)
		//UINT uiGetExtendedUI();
		//TODO: uiRes = uiGetExtendedUI();
		//TODO: xASSERT(FALSE != uiRes);
		#endif //xWIN32_31
	}

	//CxComboBox::lpGetItemData
	{
		#if (xWINVER >= xWIN32_31)
		//LRESULT lpGetItemData(INT iIndex);
		//TODO: lpRes = lpGetItemData(INT iIndex);
		//TODO: xASSERT(? != lpRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bGetItemHeight
	{
		#if (xWINVER >= xWIN32_95)
		//BOOL bGetItemHeight();
		//TODO: bRes = bGetItemHeight();
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_95
	}

	//CxComboBox::iGetLBText
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetLBText(INT iIndex, LPCTSTR pcszText);
		//TODO: iRes = iGetLBText(INT iIndex, LPCTSTR pcszText);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bGetLBTextLen
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetLBTextLen(INT iIndex);
		//TODO: bRes = bGetLBTextLen(INT iIndex);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bGetMinVisible
	{
		#if (xWINVER >= xWIN32_XP)
		//BOOL bGetMinVisible();
		//TODO: bRes = bGetMinVisible();
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_XP
	}

	//CxComboBox::bGetText 
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetText (LPTSTR pszText, INT iTextSize);
		//TODO: bRes = bGetText (LPTSTR pszText, INT iTextSize);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bGetTextLength
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetTextLength();
		//TODO: bRes = bGetTextLength();
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iInsertItemData
	{
		#if (xWINVER >= xWIN32_31)
		//INT iInsertItemData(INT iIndex, LPARAM lpData);
		//TODO: iRes = iInsertItemData(INT iIndex, LPARAM lpData);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iInsertString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iInsertString(INT iIndex, LPCSTR pcszText);
		//TODO: iRes = iInsertString(INT iIndex, LPCSTR pcszText);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bLimitText
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bLimitText(INT iTextSize);
		//TODO: bRes = bLimitText(INT iTextSize);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iResetContent
	{
		#if (xWINVER >= xWIN32_31)
		//INT iResetContent();
		//TODO: iRes = iResetContent();
		//TODO: xASSERT(? != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iSelectItemData
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSelectItemData(INT iIndexStart, LPARAM lpData);
		//TODO: iRes = iSelectItemData(INT iIndexStart, LPARAM lpData);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iSelectString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSelectString(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: iRes = iSelectString(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bSetCueBannerText 
	{
		#if (xWINVER >= xWIN32_VISTA)
		//BOOL bSetCueBannerText (LPCWSTR pcwszText);
		//TODO: bRes = bSetCueBannerText (LPCWSTR pcwszText);
		//TODO: xASSERT(FALSE != bRes);
		#endif //xWIN32_VISTA
	}

	//CxComboBox::iSetCurSel
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetCurSel(INT iIndex);
		//TODO: iRes = iSetCurSel(INT iIndex);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iSetExtendedUI 
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetExtendedUI (UINT uiFlags);
		//TODO: iRes = iSetExtendedUI (UINT uiFlags);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iSetItemData
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetItemData(INT iIndex, LPARAM lpData);
		//TODO: iRes = iSetItemData(INT iIndex, LPARAM lpData);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iSetItemHeight
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetItemHeight(INT iIndex, INT iHeight);
		//TODO: iRes = iSetItemHeight(INT iIndex, INT iHeight);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bSetMinVisible
	{
		#if (xWINVER >= xWIN32_XP)
		//BOOL bSetMinVisible(INT iNum);
		//TODO: bRes = bSetMinVisible(INT iNum);
		//TODO: xASSERT(FALSE != bRes);
		#endif //xWIN32_XP
	}

	//CxComboBox::iSetText
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetText(LPTSTR pszText);
		//TODO: iRes = iSetText(LPTSTR pszText);
		//TODO: xASSERT(FALSE != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bShowDropdown
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bShowDropdown(BOOL bFlag);
		//TODO: bRes = bShowDropdown(BOOL bFlag);
		//TODO: xASSERT(FALSE != bRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iAddItemData
	{
		#if (xWINVER >= xWIN32_95)
		//INT iAddItemData(LPARAM lpData);
		//TODO: iRes = iAddItemData(LPARAM lpData);
		//TODO: xASSERT(NULL != iRes);
		#endif //xWIN32_95
	}

	//CxComboBox::iAddString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iAddString(LPCSTR pcszText);
		//TODO: iRes = iAddString(LPCSTR pcszText);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iDeleteString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iDeleteString(INT iIndex);
		//TODO: iRes = iDeleteString(INT iIndex);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iDir
	{
		#if (xWINVER >= xWIN32_31)
		//INT iDir(UINT uiAttr, LPCTSTR pcszFileSpec);
		//TODO: iRes = iDir(UINT uiAttr, LPCTSTR pcszFileSpec);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::bEnable
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bEnable(BOOL bFlag);
		//TODO: bRes = bEnable(BOOL bFlag);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iFindItemData
	{
		#if (xWINVER >= xWIN32_31)
		//INT iFindItemData(INT iIndexStart, LPARAM lpData);
		//TODO: iRes = iFindItemData(INT iIndexStart, LPARAM lpData);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxComboBox::iFindString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iFindString(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: iRes = iFindString(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: xASSERT(CB_ERR != iRes);
		#endif //xWIN32_31
	}

	return TRUE;
}
//---------------------------------------------------------------------------