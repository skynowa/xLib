/****************************************************************************
*	bTest_CxEdit.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: bTest_CxEdit ()
BOOL CWndMain::bTest_CxEdit(CxEdit &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	
	//CxEdit::bCreateRes
	{
		_m_bRes = m_edtEdit1.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//CxEdit::bCanUndo
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bCanUndo();
		//TODO: _m_bRes = m_Object.bCanUndo();
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bEmptyUndoBuffer
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bEmptyUndoBuffer();
		//TODO: _m_bRes = m_Object.bEmptyUndoBuffer();
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bEnable
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bEnable(BOOL bFlag);
		//TODO: _m_bRes = m_Object.bEnable(BOOL bFlag);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bFormatLines
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bFormatLines(BOOL bIsAddEOL);
		//TODO: _m_bRes = m_Object.bFormatLines(BOOL bIsAddEOL);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bGetCueBannerText
	{
		#if (xWINVER >= xWIN32_XP)
		//Syntax: BOOL bGetCueBannerText(LPCWSTR pcwczText, LONG liTextSize);
		//TODO: _m_bRes = m_Object.bGetCueBannerText(LPCWSTR pcwczText, LONG liTextSize);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_XP
	}

	//CxEdit::iGetFirstVisibleLine
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iGetFirstVisibleLine();
		//TODO: _m_iRes = m_Object.iGetFirstVisibleLine();
		//TODO: xASSERT(- 1 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::hGetHandle
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: HLOCAL hGetHandle();
		//TODO: _m_hRes = m_Object.hGetHandle();
		//TODO: xASSERT(0 != _m_hRes);
		#endif //xWIN32_31
	}

	//CxEdit::iGetLine
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iGetLine(INT iLine, LPTSTR pszText, INT iTextSize);
		//TODO: _m_iRes = m_Object.iGetLine(INT iLine, LPTSTR pszText, INT iTextSize);
		//TODO: xASSERT(0 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::iGetLineCount
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iGetLineCount();
		//TODO: _m_iRes = m_Object.iGetLineCount();
		//TODO: xASSERT(1 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::bGetModify
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bGetModify();
		//TODO: _m_bRes = m_Object.bGetModify();
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::szGetPasswordChar
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: TCHAR szGetPasswordChar();
		//TODO: _m_szRes = m_Object.szGetPasswordChar();
		//TODO: xASSERT(not need != _m_szRes);
		#endif //xWIN32_31
	}

	//CxEdit::bGetRect
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bGetRect(RECT *prcRect);
		//TODO: _m_bRes = m_Object.bGetRect(RECT *prcRect);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::ulGetSel
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: ULONG ulGetSel();
		//TODO: _m_ulRes = m_Object.ulGetSel();
		//TODO: xASSERT(- 1 != _m_ulRes);
		#endif //xWIN32_31
	}

	//CxEdit::iGetText
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iGetText(LPTSTR pszText, INT iTextSize);
		//TODO: _m_iRes = m_Object.iGetText(LPTSTR pszText, INT iTextSize);
		//TODO: xASSERT(0 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::iGetTextLength
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iGetTextLength();
		//TODO: _m_iRes = m_Object.iGetTextLength();
		//TODO: xASSERT(0 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::procGetWordBreakProc
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: EDITWORDBREAKPROC procGetWordBreakProc();
		//TODO: _m_procRes = m_Object.procGetWordBreakProc();
		//TODO: xASSERT(NULL != _m_procRes);
		#endif //xWIN32_31
	}

	//CxEdit::bHideBalloonTip
	{
		#if (xWINVER >= xWIN32_XP)
		//Syntax: BOOL bHideBalloonTip();
		//TODO: _m_bRes = m_Object.bHideBalloonTip();
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_XP
	}

	//CxEdit::bLimitText
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bLimitText(INT iMaxTextSize);
		//TODO: _m_bRes = m_Object.bLimitText(INT iMaxTextSize);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::iLineFromChar
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iLineFromChar(INT iChar);
		//TODO: _m_iRes = m_Object.iLineFromChar(INT iChar);
		//TODO: xASSERT(- 1 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::iLineIndex
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iLineIndex(INT iLineIndex);
		//TODO: _m_iRes = m_Object.iLineIndex(INT iLineIndex);
		//TODO: xASSERT(- 1 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::iLineLength
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iLineLength(INT iLineIndex);
		//TODO: _m_iRes = m_Object.iLineLength(INT iLineIndex);
		//TODO: xASSERT(- 1 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::bReplaceSel
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bReplaceSel(LPCTSTR pcszNewText);
		//TODO: _m_bRes = m_Object.bReplaceSel(LPCTSTR pcszNewText);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bScroll
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bScroll(INT iVert, INT iHorz);
		//TODO: _m_bRes = m_Object.bScroll(INT iVert, INT iHorz);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bScrollCaret
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bScrollCaret();
		//TODO: _m_bRes = m_Object.bScrollCaret();
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetCueBannerText
	{
		#if (xWINVER >= xWIN32_XP)
		//Syntax: BOOL bSetCueBannerText(LPCWSTR pcwszText);
		//TODO: _m_bRes = m_Object.bSetCueBannerText(LPCWSTR pcwszText);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_XP
	}

	//CxEdit::bSetCueBannerTextFocused
	{
		#if (xWINVER >= xWIN32_VISTA)
		//Syntax: BOOL bSetCueBannerTextFocused(LPCWSTR pcwszText, BOOL bDrawFocused);
		//TODO: _m_bRes = m_Object.bSetCueBannerTextFocused(LPCWSTR pcwszText, BOOL bDrawFocused);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_VISTA
	}

	//CxEdit::bSetHandle
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetHandle(HLOCAL hHandle);
		//TODO: _m_bRes = m_Object.bSetHandle(HLOCAL hHandle);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetModify
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetModify(BOOL bFlag);
		//TODO: _m_bRes = m_Object.bSetModify(BOOL bFlag);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetPasswordChar
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetPasswordChar(UINT uiChar);
		//TODO: _m_bRes = m_Object.bSetPasswordChar(UINT uiChar);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetReadOnly
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetReadOnly(BOOL bFlag);
		//TODO: _m_bRes = m_Object.bSetReadOnly(BOOL bFlag);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetRect
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetRect(RECT *prcRect);
		//TODO: _m_bRes = m_Object.bSetRect(RECT *prcRect);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetRectNoPaint
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetRectNoPaint(RECT *prcRect);
		//TODO: _m_bRes = m_Object.bSetRectNoPaint(RECT *prcRect);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetSel
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetSel(INT iStartPos, INT iEndPos);
		//TODO: _m_bRes = m_Object.bSetSel(INT iStartPos, INT iEndPos);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetTabStops
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetTabStops(INT iTabs, INT *puiTabs);
		//TODO: _m_bRes = m_Object.bSetTabStops(INT iTabs, INT *puiTabs);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::iSetText
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: INT iSetText(LPTSTR pszText);
		//TODO: _m_iRes = m_Object.iSetText(LPTSTR pszText);
		//TODO: xASSERT(0 != _m_iRes);
		#endif //xWIN32_31
	}

	//CxEdit::bSetWordBreakProc
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bSetWordBreakProc(EDITWORDBREAKPROC pfnWordBreak);
		//TODO: _m_bRes = m_Object.bSetWordBreakProc(EDITWORDBREAKPROC pfnWordBreak);
		//TODO: xASSERT(not need != _m_bRes);
		#endif //xWIN32_31
	}

	//CxEdit::bShowBalloonTip
	{
		#if (xWINVER >= xWIN32_XP)
		//Syntax: BOOL bShowBalloonTip(EDITBALLOONTIP *pEditBalloonTip);
		//TODO: _m_bRes = m_Object.bShowBalloonTip(EDITBALLOONTIP *pEditBalloonTip);
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_XP
	}

	//CxEdit::bUndo
	{
		#if (xWINVER >= xWIN32_31)
		//Syntax: BOOL bUndo();
		//TODO: _m_bRes = m_Object.bUndo();
		//TODO: xASSERT(FALSE != _m_bRes);
		#endif //xWIN32_31
	}

	return TRUE;
}
//---------------------------------------------------------------------------