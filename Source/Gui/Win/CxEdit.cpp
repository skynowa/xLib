/**
 * \file  CxEdit.cpp
 * \brief edit
 */


#include <xLib/Gui/Win/CxEdit.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxEdit
CxEdit::CxEdit() {
    LOG();

    //-------------------------------------
    //�������������� ��������� ����
    _m_sClassName     = xCXEDIT_CONTROL_CLASS;
    _m_ulStyle        = xCXEDIT_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXEDIT_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXEDIT_DEFAULT_WIDTH;
    _m_iHeight        = xCXEDIT_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;

    //-------------------------------------
    //�����
}
//---------------------------------------------------------------------------
//TODO: - ~CxEdit
CxEdit::~CxEdit() {
    LOG();
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxEdit::bCreateRes(INT iID, CxWindow *pwndParent) {
    /*DEBUG*/xASSERT_RET(0 < iID,         FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

    _m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName, CxResources::sGetText(iID),
                                CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID),
                                CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID),
                                CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
                                this);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: ���������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bCanUndo (Determines whether there are any actions in the undo queue of an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bCanUndo() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = static_cast<BOOL>( Edit_CanUndo(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bEmptyUndoBuffer (Resets the undo flag of an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bEmptyUndoBuffer() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    static_cast<VOID>( Edit_EmptyUndoBuffer(_m_hWnd) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bEnable (Enables or disables an edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bEnable(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///bFlag

    static_cast<BOOL>( Edit_Enable(_m_hWnd, bFlag) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bFormatLines (Sets a flag that determines whether text retrieved from a multiline edit control includes soft line-break characters)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bFormatLines(BOOL bIsAddEOL) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///bIsAddEOL

    static_cast<VOID>( Edit_FmtLines(_m_hWnd, bIsAddEOL) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetCueBannerText (Gets the text that is displayed as a textual cue, or tip, in an edit control)
#if (xWINVER >= xWIN32_XP)
BOOL CxEdit::bGetCueBannerText(LPCWSTR pcwczText, LONG liTextSize) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///pcwczText
    /*DEBUG*///liTextSize

    _m_bRes = static_cast<BOOL>( Edit_GetCueBannerText(_m_hWnd, pcwczText, liTextSize) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - iGetFirstVisibleLine (Gets the index of the uppermost visible line in a multiline edit or rich edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iGetFirstVisibleLine() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);

    INT iRes = - 1;

    iRes = static_cast<INT>( Edit_GetFirstVisibleLine(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - hGetHandle (Gets a handle to the memory currently allocated for the text of a multiline edit control)
#if (xWINVER >= xWIN32_31)
HLOCAL CxEdit::hGetHandle() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);

    HLOCAL hRes = 0;

    hRes = static_cast<HLOCAL>( Edit_GetHandle(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(0 != hRes, 0);

    return hRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetLine (Retrieves a line of text from an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iGetLine(INT iLine, LPTSTR pszText, INT iTextSize) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);
    /*DEBUG*///iLine
    /*DEBUG*///pszText
    /*DEBUG*///iTextSize

    INT iRes = 0;

    iRes = static_cast<INT>( Edit_GetLine(_m_hWnd, iLine, pszText, iTextSize) );
    /*DEBUG*/xASSERT_RET(0 != iRes, 0);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetLineCount (Gets the number of lines in the text of an edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iGetLineCount() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 1);

    INT iRes = 1;

    iRes = static_cast<INT>( Edit_GetLineCount(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(1 != iRes, 1);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetModify (Gets the state of an edit or rich edit control's modification flag)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bGetModify() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = static_cast<BOOL>( Edit_GetModify(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetPasswordChar (Gets the password character for an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bGetPasswordChar() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    static_cast<BOOL>( Edit_GetPasswordChar(_m_hWnd) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetRect (Gets the formatting rectangle of an edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bGetRect(RECT *prcRect) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///prcRect

    static_cast<VOID>( Edit_GetRect(_m_hWnd, prcRect) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - ulGetSel (Gets the starting and ending character positions of the current selection in an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
ULONG CxEdit::ulGetSel() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);

    ULONG ulRes = - 1;

    ulRes = static_cast<ULONG>( Edit_GetSel(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(- 1 != ulRes, - 1);

    return ulRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetText (Gets the text of an edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iGetText(LPTSTR pszText, INT iTextSize) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);
    /*DEBUG*///pszText
    /*DEBUG*///iTextSize

    INT iRes = 0;

    iRes = static_cast<INT>( Edit_GetText(_m_hWnd, pszText, iTextSize) );
    /*DEBUG*/xASSERT_RET(0 != iRes, 0);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetTextLength (Gets the number of characters in the text of an edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iGetTextLength() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);

    INT iRes = 0;

    iRes = static_cast<INT>( Edit_GetTextLength(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(0 != iRes, 0);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - procGetWordBreakProc (Retrieves the address of an edit or rich edit control's Wordwrap function)
#if (xWINVER >= xWIN32_31)
EDITWORDBREAKPROC CxEdit::procGetWordBreakProc() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    EDITWORDBREAKPROC procRes = NULL;

    procRes = static_cast<EDITWORDBREAKPROC>( Edit_GetWordBreakProc(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(NULL != procRes, NULL);

    return procRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bHideBalloonTip (Hides any balloon tip associated with an edit control)
#if (xWINVER >= xWIN32_XP)
BOOL CxEdit::bHideBalloonTip() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = static_cast<BOOL>( Edit_HideBalloonTip(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bLimitText (Limits the length of text that can be entered into an edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bLimitText(INT iMaxTextSize) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///iMaxTextSize

    static_cast<VOID>( Edit_LimitText(_m_hWnd, iMaxTextSize) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iLineFromChar (Gets the index of the line that contains the specified character index in a multiline edit or rich edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iLineFromChar(INT iChar) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);
    /*DEBUG*///iChar

    INT iRes = - 1;

    iRes = static_cast<INT>( Edit_LineFromChar(_m_hWnd, iChar) );
    /*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iLineIndex (Gets the character index of the first character of a specified line in a multiline edit or rich edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iLineIndex(INT iLineIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);
    /*DEBUG*///iLineIndex

    INT iRes = - 1;

    iRes = static_cast<INT>( Edit_LineIndex(_m_hWnd, iLineIndex) );
    /*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iLineLength (Retrieves the length, in characters, of a line in an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iLineLength(INT iLineIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, - 1);
    /*DEBUG*///iLineIndex

    INT iRes = - 1;

    iRes = static_cast<INT>( Edit_LineLength(_m_hWnd, iLineIndex) );
    /*DEBUG*/xASSERT_RET(- 1 != iRes, - 1);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bReplaceSel (Replaces the selected text in an edit control or a rich edit control with the specified text)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bReplaceSel(LPCTSTR pcszNewText) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///pcszNewText

    static_cast<VOID>( Edit_ReplaceSel(_m_hWnd, pcszNewText) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bScroll (Scrolls the text vertically in a multiline edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bScroll(INT iVert, INT iHorz) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///iVert
    /*DEBUG*///iHorz

    static_cast<VOID>( Edit_Scroll(_m_hWnd, iVert, iHorz) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bScrollCaret (Scrolls the caret into view in an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bScrollCaret() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    static_cast<BOOL>( Edit_ScrollCaret(_m_hWnd) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetCueBannerText (ets the text that is displayed as the textual cue, or tip, for an edit control)
#if (xWINVER >= xWIN32_XP)
BOOL CxEdit::bSetCueBannerText(LPCWSTR pcwszText) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///pcwszText

    _m_bRes = static_cast<BOOL>( Edit_SetCueBannerText(_m_hWnd, pcwszText) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bSetCueBannerTextFocused (Sets the text that is displayed as the textual cue, or tip, for an edit control)
#if (xWINVER >= xWIN32_VISTA)
BOOL CxEdit::bSetCueBannerTextFocused(LPCWSTR pcwszText, BOOL bDrawFocused) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///pcwszText
    /*DEBUG*///bDrawFocused

    _m_bRes = static_cast<BOOL>( Edit_SetCueBannerTextFocused(_m_hWnd, pcwszText, bDrawFocused) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - bSetHandle (Sets the handle of the memory that will be used by a multiline edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetHandle(HLOCAL hHandle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///hHandle

    static_cast<VOID>( Edit_SetHandle(_m_hWnd, hHandle) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetModify (Sets or clears the modification flag for an edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetModify(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///bFlag

    static_cast<VOID>( Edit_SetModify(_m_hWnd, bFlag) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetPasswordChar (Sets or removes the password character for an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetPasswordChar(UINT uiChar) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///uiChar

    static_cast<VOID>( Edit_SetPasswordChar(_m_hWnd, uiChar) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetReadOnly (Sets or removes the read-only style (ES_READONLY) of an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetReadOnly(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///bFlag

    _m_bRes = static_cast<BOOL>( Edit_SetReadOnly(_m_hWnd, bFlag) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetRect (Sets the formatting rectangle of an edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetRect(RECT *prcRect) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///prcRect

    static_cast<VOID>( Edit_SetRect(_m_hWnd, prcRect) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetRectNoPaint (Sets the formatting rectangle of a multiline edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetRectNoPaint(RECT *prcRect) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///prcRect

    static_cast<VOID>( Edit_SetRectNoPaint(_m_hWnd, prcRect) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetSel (Selects a range of characters in an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetSel(INT iStartPos, INT iEndPos) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///iStartPos
    /*DEBUG*///iEndPos

    static_cast<VOID>( Edit_SetSel(_m_hWnd, iStartPos, iEndPos) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetTabStops (Sets the tab stops in a multiline edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetTabStops(INT iTabs, INT *puiTabs) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///iTabs
    /*DEBUG*///puiTabs

    static_cast<VOID>( Edit_SetTabStops(_m_hWnd, iTabs, puiTabs) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetText (Sets the text of an edit control)
#if (xWINVER >= xWIN32_31)
INT CxEdit::iSetText(LPTSTR pszText) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);
    /*DEBUG*///pszText

    INT iRes = 0;

    iRes = static_cast<INT>( Edit_SetText(_m_hWnd, pszText) );
    /*DEBUG*/xASSERT_RET(0 != iRes, 0);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetWordBreakProc (Replaces an edit control's default Wordwrap function with an application-defined Wordwrap function)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bSetWordBreakProc(EDITWORDBREAKPROC pfnWordBreak) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///pfnWordBreak

    static_cast<VOID>( Edit_SetWordBreakProc(_m_hWnd, pfnWordBreak) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bShowBalloonTip (Displays a balloon tip associated with an edit control)
#if (xWINVER >= xWIN32_XP)
BOOL CxEdit::bShowBalloonTip(EDITBALLOONTIP *pEditBalloonTip) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///pEditBalloonTip

    _m_bRes = static_cast<BOOL>( Edit_ShowBalloonTip(_m_hWnd, pEditBalloonTip) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_XP
//---------------------------------------------------------------------------
//TODO: - bUndo (Undoes the last operation in the undo queue of an edit or rich edit control)
#if (xWINVER >= xWIN32_31)
BOOL CxEdit::bUndo() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = static_cast<BOOL>( Edit_Undo(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
#endif












//////---------------------------------------------------------------------------
//////TODO: - bLimitText
////LRESULT CxEdit::bLimitText(UINT uiSize) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    return pSendMessage(EM_LIMITTEXT, uiSize, NULL);
////}
//////---------------------------------------------------------------------------














/*
VOID CxEdit::CopyEditToClipboard() {
    pSendMessage(EM_SETSEL, 0, 65535L);
    pSendMessage(WM_COPY,   0, 0);
    pSendMessage(EM_SETSEL, 0, 0);
}
*/
//---------------------------------------------------------------------------
