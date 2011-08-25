/**
 * \file  CxListBox.cpp
 * \brief list box
 */


#include <xLib/Gui/CxListBox.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxListBox
CxListBox::CxListBox() {
    LOG();

    //-------------------------------------
    //переопределяем параметры окна
    _m_sClassName     = xCXLISTBOX_CONTROL_CLASS;
    _m_ulStyle        = xCXLISTBOX_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXLISTBOX_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXLISTBOX_DEFAULT_WIDTH;
    _m_iHeight        = xCXLISTBOX_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;

    //-------------------------------------
    //внутр
}
//---------------------------------------------------------------------------
//TODO: - ~CxListBox
CxListBox::~CxListBox() {
    LOG();
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxListBox::bCreateRes(INT iID, CxWindow *pwndParent) {
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
*    public: сообщения
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - iDir (Adds names to the list displayed by a list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iDir(UINT uiAttr, LPCTSTR pcszFileSpec) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///uiAttr
    /*DEBUG*///pcszFileSpec

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_Dir(_m_hWnd, uiAttr, pcszFileSpec) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bEnable (Enables or disables a list box control)
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bEnable(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///bFlag

    static_cast<BOOL>( ListBox_Enable(_m_hWnd, bFlag) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iFindItemData (Finds the first item in a list box that has the specified item data)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iFindItemData(INT iIndexStart, LPARAM plpData) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndexStart
    /*DEBUG*///plpData

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_FindItemData(_m_hWnd, iIndexStart, plpData) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iFindString (Finds the first string in a list box that begins with the specified string)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iFindString(INT iIndexStart, LPCTSTR pcszFind) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndexStart
    /*DEBUG*///pcszFind

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_FindString(_m_hWnd, iIndexStart, pcszFind) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iFindStringExact (Finds the first list box string that exactly matches the specified string, except that the search is not case sensitive)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iFindStringExact(INT iIndexStart, LPCTSTR pcszFind) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndexStart
    /*DEBUG*///pcszFind

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_FindStringExact(_m_hWnd, iIndexStart, pcszFind) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetCaretIndex (Retrieves the index of the list box item that has the focus rectangle in a multiple-selection list box)
#if (xWINVER >= xWIN32_95)
INT CxListBox::iGetCaretIndex() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, 0);

    INT iRes = 0;

    iRes = static_cast<INT>( ListBox_GetCaretIndex(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(0 != iRes, 0);

    return iRes;
}
#endif //xWIN32_95
//---------------------------------------------------------------------------
//TODO: - bGetCount (Gets the number of items in a list box)
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bGetCount() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    static_cast<BOOL>( ListBox_GetCount(_m_hWnd) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetCurSel (Gets the index of the currently selected item in a single-selection list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iGetCurSel() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_GetCurSel(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetHorizontalExtent (Gets the width that a list box can be scrolled horizontally (the scrollable width) if the list box has a horizontal scroll bar)
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bGetHorizontalExtent() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    static_cast<BOOL>( ListBox_GetHorizontalExtent(_m_hWnd) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - lpGetItemData (Gets the application-defined value associated with the specified list box item)
#if (xWINVER >= xWIN32_31)
LRESULT CxListBox::lpGetItemData(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex

    LRESULT lpRes = LB_ERR;

    lpRes = static_cast<LRESULT>( ListBox_GetItemData(_m_hWnd, iIndex) );
    /*DEBUG*/xASSERT_RET(LB_ERR != lpRes, LB_ERR);

    return lpRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetItemHeight (Retrieves the height of items in a list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iGetItemHeight(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_GetItemHeight(_m_hWnd, iIndex) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetItemRect  (Gets the dimensions of the rectangle that bounds a list box item as it is currently displayed in the list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iGetItemRect (INT iIndex, RECT *prcRect) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex
    /*DEBUG*///prcRect

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_GetItemRect (_m_hWnd, iIndex, prcRect) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - ulGetSel (Gets the selection state of an item)
#if (xWINVER >= xWIN32_31)
ULONG CxListBox::ulGetSel(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex

    ULONG ulRes = LB_ERR;

    ulRes = static_cast<ULONG>( ListBox_GetSel(_m_hWnd, iIndex) );
    /*DEBUG*/xASSERT_RET(LB_ERR != ulRes, LB_ERR);

    return ulRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetSelCount (Gets the count of selected items in a multiple-selection list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iGetSelCount() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_GetSelCount(_m_hWnd) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetSelItems (Gets the indexes of selected items in a multiple-selection list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iGetSelItems(INT iItems, INT *piItems) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iItems
    /*DEBUG*///piItems

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_GetSelItems(_m_hWnd, iItems, piItems) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iGetText  (Gets a string from a list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iGetText (INT iIndex, LPCTSTR pcszText) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex
    /*DEBUG*///pcszText

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_GetText (_m_hWnd, iIndex, pcszText) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetTextLen  (Gets the length of a string in a list box)
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bGetTextLen (INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///iIndex

    static_cast<BOOL>( ListBox_GetTextLen (_m_hWnd, iIndex) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bGetTopIndex  (Gets the index of the first visible item in a list box)
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bGetTopIndex () {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    static_cast<BOOL>( ListBox_GetTopIndex (_m_hWnd) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iInsertItemData  (Inserts item data to a list box at the specified location)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iInsertItemData (INT iIndex, LPARAM lpData) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex
    /*DEBUG*///lpData

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_InsertItemData (_m_hWnd, iIndex, lpData) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iInsertString (Adds a string to a list box at the specified location)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iInsertString(INT index, LPCSTR pcszText) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///index
    /*DEBUG*///pcszText

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_InsertString(_m_hWnd, index, pcszText) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bResetContent (Removes all items from a list box)
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bResetContent() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    static_cast<BOOL>( ListBox_ResetContent(_m_hWnd) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSelectItemData (Searches a list box for an item that has the specified item data)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSelectItemData(INT iIndexStart, LPARAM lpData) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndexStart
    /*DEBUG*///lpData

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SelectItemData(_m_hWnd, iIndexStart, lpData) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSelectString (Searches a list box for an item that begins with the characters in a specified string)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSelectString(INT iIndexStart, LPCTSTR pcszFind) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndexStart
    /*DEBUG*///pcszFind

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SelectString(_m_hWnd, iIndexStart, pcszFind) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSelItemRange (Selects or deselects one or more consecutive items in a multiple-selection list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSelItemRange(BOOL bFlag, INT iFirst, INT iLast) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///bFlag
    /*DEBUG*///iFirst
    /*DEBUG*///iLast

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SelItemRange(_m_hWnd, bFlag, iFirst, iLast) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetCaretIndex (Sets the focus rectangle to the item at the specified index in a multiple-selection list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSetCaretIndex(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SetCaretIndex(_m_hWnd, iIndex) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetColumnWidth (Sets the width of all columns in a multiple-column list box)
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bSetColumnWidth(INT iColumn) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///iColumn

    static_cast<VOID>( ListBox_SetColumnWidth(_m_hWnd, iColumn) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetCurSel (Sets the currently selected item in a single-selection list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSetCurSel(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SetCurSel(_m_hWnd, iIndex) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetHorizontalExtent (Set the width by which a list box can be scrolled horizontally (the scrollable width))
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bSetHorizontalExtent(INT iExtent) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///iExtent

    static_cast<VOID>( ListBox_SetHorizontalExtent(_m_hWnd, iExtent) );
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetItemData (Sets the application-defined value associated with the specified list box item)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSetItemData(INT iIndex, LPARAM lpData) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex
    /*DEBUG*///lpData

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SetItemData(_m_hWnd, iIndex, lpData) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetItemHeight (Sets the height of items in a list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSetItemHeight(INT iIndex, LPARAM lpHeight) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex
    /*DEBUG*///lpHeight

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SetItemHeight(_m_hWnd, iIndex, lpHeight) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iAddString (Adds a string to a list box.)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iAddString(LPCSTR pcszText) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///pcszText

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_AddString(_m_hWnd, pcszText) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iDeleteString (Deletes the item at the specified location in a list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iDeleteString(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_DeleteString(_m_hWnd, iIndex) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetSel (Selects or deselects an item in a multiple-selection list box)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSetSel(INT iIndex, BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex
    /*DEBUG*///bFlag

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SetSel(_m_hWnd, iIndex, bFlag) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - bSetTabStops (Sets the tab-stop positions in a list box)
#if (xWINVER >= xWIN32_31)
BOOL CxListBox::bSetTabStops(INT iTabs, INT *piTabs) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///iTabs
    /*DEBUG*///piTabs

    BOOL bRes = FALSE;

    bRes = static_cast<BOOL>( ListBox_SetTabStops(_m_hWnd, iTabs, piTabs) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return bRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------
//TODO: - iSetTopIndex (Ensures that the specified item in a list box is visible)
#if (xWINVER >= xWIN32_31)
INT CxListBox::iSetTopIndex(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, LB_ERR);
    /*DEBUG*///iIndex

    INT iRes = LB_ERR;

    iRes = static_cast<INT>( ListBox_SetTopIndex(_m_hWnd, iIndex) );
    /*DEBUG*/xASSERT_RET(LB_ERR != iRes, LB_ERR);

    return iRes;
}
#endif //xWIN32_31
//---------------------------------------------------------------------------




//////---------------------------------------------------------------------------
//////DONE: bAddString
////BOOL CxListBox::bAddString(const tString &csItem) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_ADDSTRING, NULL, (LPARAM)csItem.c_str());
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////DONE: bResetContent
////BOOL CxListBox::bResetContent() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_RESETCONTENT, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////DONE: bAddFile
////BOOL CxListBox::bAddFile(const tString &csFileName) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_ADDFILE, NULL, (LPARAM)csFileName.c_str());
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bDeleteString
////BOOL CxListBox::bDeleteString(INT iStartIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_DELETESTRING, (WPARAM)iStartIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO: - bDeleteString
////BOOL CxListBox::bDir(UINT uiDir) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    ////pSendMessage(LB_DIR, (WPARAM)uiDir, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bFindString
////BOOL CxListBox::bFindString(WPARAM wStartIndex, LPARAM lString) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_FINDSTRING, wStartIndex, lString);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bFindStringExact
////BOOL CxListBox::bFindStringExact(WPARAM wStartIndex, LPARAM lString) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_FINDSTRINGEXACT, wStartIndex, lString);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetAnchorIndex
////BOOL CxListBox::bGetAnchorIndex() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETANCHORINDEX, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetCaretIndex
////BOOL CxListBox::bGetCaretIndex() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETCARETINDEX, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetCount
////BOOL CxListBox::bGetCount() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETCOUNT, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetCurSel
////BOOL CxListBox::bGetCurSel() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETCURSEL, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetHorizontalExtent
////BOOL CxListBox::bGetHorizontalExtent() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETHORIZONTALEXTENT, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetItemData
////BOOL CxListBox::bGetItemData(WPARAM wItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETITEMDATA, wItemIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetItemHeight
////BOOL CxListBox::bGetItemHeight(WPARAM wItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETITEMHEIGHT, wItemIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetItemRect
////BOOL CxListBox::bGetItemRect(WPARAM wItemIndex, LPARAM lRect) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETITEMRECT, wItemIndex, lRect);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetListBoxInfo
////BOOL CxListBox::bGetListBoxInfo() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    ///////////////pSendMessage(LB_GETLISTBOXINFO, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetLocale
////BOOL CxListBox::bGetLocale() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETLOCALE, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetSel
////BOOL CxListBox::bGetSel(WPARAM wItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETSEL, wItemIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetSelCount
////BOOL CxListBox::bGetSelCount() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETSELCOUNT, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetSelItems
////BOOL CxListBox::bGetSelItems(LPARAM lItems) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETSELITEMS, NULL, lItems);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetText
////BOOL CxListBox::bGetText(WPARAM wItemIndex, LPARAM lItems) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETTEXT, wItemIndex, lItems);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetTextLen
////BOOL CxListBox::bGetTextLen(WPARAM wItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETTEXTLEN, wItemIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bGetTopIndex
////BOOL CxListBox::bGetTopIndex() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_GETTOPINDEX, NULL, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bInitStorage
////BOOL CxListBox::bInitStorage(WPARAM wItemsCount, LPARAM lMem) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_INITSTORAGE, wItemsCount, lMem);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bInsertString
////BOOL CxListBox::bInsertString(WPARAM wItemIndex, LPARAM lString) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_INSERTSTRING, wItemIndex, lString);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bItemFromPoint
////BOOL CxListBox::bItemFromPoint(LPARAM lPoint) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_ITEMFROMPOINT, NULL, lPoint);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSelectString
////BOOL CxListBox::bSelectString(WPARAM wStartIndex, LPARAM lString) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SELECTSTRING, wStartIndex, lString);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSelItemRange
////BOOL CxListBox::bSelItemRange(WPARAM wOption, LPARAM lFirstLastItems) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SELITEMRANGE, wOption, lFirstLastItems);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSelItemRangeEx
////BOOL CxListBox::bSelItemRangeEx(WPARAM wFirstItem, LPARAM lLastItem) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SELITEMRANGEEX, wFirstItem, lLastItem);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetAnchorIndex
////BOOL CxListBox::bSetAnchorIndex(WPARAM wItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETANCHORINDEX, wItemIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetCaretIndex
////BOOL CxListBox::bSetCaretIndex(WPARAM wItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETCARETINDEX, wItemIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetColumnWidth
////BOOL CxListBox::bSetColumnWidth(WPARAM wWidth) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETCOLUMNWIDTH, wWidth, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetCount
////BOOL CxListBox::bSetCount(WPARAM wCount) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETCOUNT, wCount, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetCurSel
////BOOL CxListBox::bSetCurSel(WPARAM wItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETCURSEL, wItemIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetHorizontalExtent
////BOOL CxListBox::bSetHorizontalExtent(WPARAM wScrollWidth) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETHORIZONTALEXTENT, wScrollWidth, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetItemData
////BOOL CxListBox::bSetItemData(WPARAM wItemIndex, LPARAM lValue) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETITEMDATA, wItemIndex, lValue);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetItemHeight
////BOOL CxListBox::bSetItemHeight(WPARAM wItemIndex, LPARAM lHeight) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETITEMHEIGHT, wItemIndex, lHeight);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetLocale
////BOOL CxListBox::bSetLocale(WPARAM wLocaleIdentifier) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETLOCALE, wLocaleIdentifier, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetSel
////BOOL CxListBox::bSetSel(WPARAM wSelOption, LPARAM lItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETSEL, wSelOption, lItemIndex);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetTabStops
////BOOL CxListBox::bSetTabStops(WPARAM wTabStopsNum, LPARAM lTabStopsArr) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETTABSTOPS, wTabStopsNum, lTabStopsArr);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bSetTopIndex
////BOOL CxListBox::bSetTopIndex(WPARAM wItemIndex) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    pSendMessage(LB_SETTOPINDEX, wItemIndex, NULL);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
//////TODO:  bVScroll
////BOOL CxListBox::bVScroll(WPARAM wPos) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    return pSendMessage(WM_VSCROLL, MAKEWORD(wPos, 0), 0);
////
////    return TRUE;
////}
//////---------------------------------------------------------------------------
