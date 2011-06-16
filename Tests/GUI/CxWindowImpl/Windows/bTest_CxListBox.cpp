/****************************************************************************
*	bTest_CxListBox.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxListBox ()
BOOL CWndMain::bTest_CxListBox(CxListBox &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);


	//CxListBox::bCreateRes
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxListBox::iDir
	{
		#if (xWINVER >= xWIN32_31)
		//INT iDir(UINT uiAttr, LPCTSTR pcszFileSpec);
		//TODO: iRes = iDir(UINT uiAttr, LPCTSTR pcszFileSpec);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::bEnable
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bEnable(BOOL bFlag);
		//TODO: bRes = bEnable(BOOL bFlag);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::iFindItemData
	{
		#if (xWINVER >= xWIN32_31)
		//INT iFindItemData(INT iIndexStart, LPARAM plpData);
		//TODO: iRes = iFindItemData(INT iIndexStart, LPARAM plpData);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iFindString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iFindString(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: iRes = iFindString(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iFindStringExact
	{
		#if (xWINVER >= xWIN32_31)
		//INT iFindStringExact(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: iRes = iFindStringExact(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iGetCaretIndex
	{
		#if (xWINVER >= xWIN32_95)
		//INT iGetCaretIndex();
		//TODO: iRes = iGetCaretIndex();
		//TODO: xASSERT(0 != iRes);
		#endif //xWIN32_95
	}

	//CxListBox::bGetCount
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetCount();
		//TODO: bRes = bGetCount();
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::iGetCurSel
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetCurSel();
		//TODO: iRes = iGetCurSel();
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::bGetHorizontalExtent
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetHorizontalExtent();
		//TODO: bRes = bGetHorizontalExtent();
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::lpGetItemData
	{
		#if (xWINVER >= xWIN32_31)
		//LRESULT lpGetItemData(INT iIndex);
		//TODO: lpRes = lpGetItemData(INT iIndex);
		//TODO: xASSERT(? != lpRes);
		#endif //xWIN32_31
	}

	//CxListBox::iGetItemHeight
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetItemHeight(INT iIndex);
		//TODO: iRes = iGetItemHeight(INT iIndex);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iGetItemRect 
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetItemRect (INT iIndex, RECT *prcRect);
		//TODO: iRes = iGetItemRect (INT iIndex, RECT *prcRect);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::ulGetSel
	{
		#if (xWINVER >= xWIN32_31)
		//ULONG ulGetSel(INT iIndex);
		//TODO: ulRes = ulGetSel(INT iIndex);
		//TODO: xASSERT(LB_ERR != ulRes);
		#endif //xWIN32_31
	}

	//CxListBox::iGetSelCount
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetSelCount();
		//TODO: iRes = iGetSelCount();
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iGetSelItems
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetSelItems(INT iItems, INT *piItems);
		//TODO: iRes = iGetSelItems(INT iItems, INT *piItems);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iGetText 
	{
		#if (xWINVER >= xWIN32_31)
		//INT iGetText (INT iIndex, LPCTSTR pcszText);
		//TODO: iRes = iGetText (INT iIndex, LPCTSTR pcszText);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::bGetTextLen 
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetTextLen (INT iIndex);
		//TODO: bRes = bGetTextLen (INT iIndex);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::bGetTopIndex 
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bGetTopIndex ();
		//TODO: bRes = bGetTopIndex ();
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::iInsertItemData 
	{
		#if (xWINVER >= xWIN32_31)
		//INT iInsertItemData (INT iIndex, LPARAM lpData);
		//TODO: iRes = iInsertItemData (INT iIndex, LPARAM lpData);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iInsertString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iInsertString(INT index, LPCSTR pcszText);
		//TODO: iRes = iInsertString(INT index, LPCSTR pcszText);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::bResetContent
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bResetContent();
		//TODO: bRes = bResetContent();
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSelectItemData
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSelectItemData(INT iIndexStart, LPARAM lpData);
		//TODO: iRes = iSelectItemData(INT iIndexStart, LPARAM lpData);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSelectString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSelectString(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: iRes = iSelectString(INT iIndexStart, LPCTSTR pcszFind);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSelItemRange
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSelItemRange(BOOL bFlag, INT iFirst, INT iLast);
		//TODO: iRes = iSelItemRange(BOOL bFlag, INT iFirst, INT iLast);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSetCaretIndex
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetCaretIndex(INT iIndex);
		//TODO: iRes = iSetCaretIndex(INT iIndex);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::bSetColumnWidth
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bSetColumnWidth(INT iColumn);
		//TODO: bRes = bSetColumnWidth(INT iColumn);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSetCurSel
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetCurSel(INT iIndex);
		//TODO: iRes = iSetCurSel(INT iIndex);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::bSetHorizontalExtent
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bSetHorizontalExtent(INT iExtent);
		//TODO: bRes = bSetHorizontalExtent(INT iExtent);
		//TODO: xASSERT(not need != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSetItemData
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetItemData(INT iIndex, LPARAM lpData);
		//TODO: iRes = iSetItemData(INT iIndex, LPARAM lpData);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSetItemHeight
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetItemHeight(INT iIndex, LPARAM lpHeight);
		//TODO: iRes = iSetItemHeight(INT iIndex, LPARAM lpHeight);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iAddString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iAddString(LPCSTR pcszText);
		//TODO: iRes = iAddString(LPCSTR pcszText);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iDeleteString
	{
		#if (xWINVER >= xWIN32_31)
		//INT iDeleteString(INT iIndex);
		//TODO: iRes = iDeleteString(INT iIndex);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSetSel
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetSel(INT iIndex, BOOL bFlag);
		//TODO: iRes = iSetSel(INT iIndex, BOOL bFlag);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}

	//CxListBox::bSetTabStops
	{
		#if (xWINVER >= xWIN32_31)
		//BOOL bSetTabStops(INT iTabs, INT *piTabs);
		//TODO: bRes = bSetTabStops(INT iTabs, INT *piTabs);
		//TODO: xASSERT(FALSE != bRes);
		#endif //xWIN32_31
	}

	//CxListBox::iSetTopIndex
	{
		#if (xWINVER >= xWIN32_31)
		//INT iSetTopIndex(INT iIndex);
		//TODO: iRes = iSetTopIndex(INT iIndex);
		//TODO: xASSERT(LB_ERR != iRes);
		#endif //xWIN32_31
	}


	return TRUE;
}
//---------------------------------------------------------------------------