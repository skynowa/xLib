/****************************************************************************
* Class name:  CxListView
* Description: 
* File name:   CxListView.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.07.2009 12:12:03
*
*****************************************************************************/


#include <xLib/Gui/CxListView.h>

//---------------------------------------------------------------------------
CxListView::CxListView() : 
    m_ColumnCount(0),
    m_ItemCount  (0)
{
    LOG();

    //-------------------------------------
    //переопределяем параметры окна
    _m_sClassName     = xCXLISTVIEW_CONTROL_CLASS;
    _m_ulStyle        = xCXLISTVIEW_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXLISTVIEW_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXLISTVIEW_DEFAULT_WIDTH;
    _m_iHeight        = xCXLISTVIEW_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;

    
    //TODO: _bInitCommonControls
    _bInitCommonControls(ICC_LISTVIEW_CLASSES);
    
    //HICON hiconItem;     //icon for list-view items 

    //Create the full-sized icon image lists. 
    m_hLargeImageList = ImageList_Create(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), ILC_MASK | ILC_COLOR16, 1, 1);
    m_hSmallImageList = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), ILC_MASK | ILC_COLOR16, 1, 1);

    //Add an icon to each image list.  
    /*hiconItem = NULL;//LoadIcon (NULL, IDI_APPLICATION);
    ImageList_AddIcon(hLarge, hiconItem); 
    ImageList_AddIcon(hSmall, hiconItem); 
    DestroyIcon(hiconItem); */

    ListView_SetImageList(_m_hWnd, m_hLargeImageList, LVSIL_NORMAL);
    ListView_SetImageList(_m_hWnd, m_hSmallImageList, LVSIL_SMALL);
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxListView::bCreateRes(INT iID, CxWindow *pwndParent) {
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
CxListView::~CxListView() {
    LOG();
}
//---------------------------------------------------------------------------
INT CxListView::AddSmallIcon(HICON Icon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ImageList_AddIcon(m_hSmallImageList, Icon);
}
//---------------------------------------------------------------------------
INT CxListView::AddLargeIcon(HICON Icon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ImageList_AddIcon(m_hLargeImageList, Icon);
}
//---------------------------------------------------------------------------
BOOL CxListView::RemoveAllIcons() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ImageList_RemoveAll(m_hLargeImageList) && ImageList_RemoveAll(m_hSmallImageList);
}
//---------------------------------------------------------------------------
INT CxListView::GetColumnCount() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return m_ColumnCount;
}
//---------------------------------------------------------------------------
INT CxListView::GetItemCount() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return m_ItemCount;
}
//---------------------------------------------------------------------------
BOOL CxListView::AddColumn(tString Text) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return AddColumn(Text, 100);
}
//---------------------------------------------------------------------------
BOOL CxListView::AddColumn(tString Text, INT Width) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH;
    lvc.pszText = (LPTSTR)Text.c_str();    //char *
    lvc.cx = Width;

    return ListView_InsertColumn(_m_hWnd, m_ColumnCount ++, &lvc) !=  - 1;
}
//---------------------------------------------------------------------------
BOOL CxListView::DeleteColumn(INT Index) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    if (ListView_DeleteColumn(_m_hWnd, Index)) {
        m_ColumnCount --;
        return TRUE;
    } else {
        return FALSE;
    } 
}
//---------------------------------------------------------------------------
INT CxListView::AddItem(tString Text) {
    return AddItem(Text, 0, 0);
}
//---------------------------------------------------------------------------
INT CxListView::AddItem(tString Text, LPARAM lParam) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return AddItem(Text, lParam, 0);
}
//---------------------------------------------------------------------------
INT CxListView::AddItem(tString Text, LPARAM lParam, INT Image) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    LVITEM lvi;
    lvi.mask = LVIF_TEXT | LVIF_PARAM;
    lvi.iItem = m_ItemCount;
    lvi.iSubItem = 0;
    lvi.pszText = (LPTSTR)Text.c_str();
    if (lParam != 0) {
        lvi.mask |= LVIF_PARAM;
        lvi.lParam = lParam;
    }
    if (Image != 0) {
        lvi.mask |= LVIF_IMAGE;
        lvi.iImage = Image;
    }
    
    INT i = ListView_InsertItem(_m_hWnd, &lvi);
    if (i !=  - 1) {
        m_ItemCount ++;
    } 
    
    return i;
}
//---------------------------------------------------------------------------
BOOL CxListView::SetItem(tString Text, INT Index, INT SubItem) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return SetItem(Text, Index, SubItem, 0);
}
//---------------------------------------------------------------------------
BOOL CxListView::SetItem(tString Text, INT Index, INT SubItem, INT Image) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    LVITEM lvi;
    lvi.mask = LVIF_TEXT;
    lvi.iItem = Index;
    lvi.iImage = Image;
    lvi.iSubItem = SubItem;
    lvi.pszText = (LPTSTR)Text.c_str();

    return ListView_SetItem(_m_hWnd, &lvi) !=  - 1;
}
//---------------------------------------------------------------------------
BOOL CxListView::SortItems(PFNLVCOMPARE pfnCompare, LPARAM lParamSort) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_SortItems(_m_hWnd, pfnCompare, lParamSort);
}
//---------------------------------------------------------------------------
BOOL CxListView::AutoSizeColumns() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    for (INT i = 0; i < m_ColumnCount; i ++) {
        ListView_SetColumnWidth(_m_hWnd, i, LVSCW_AUTOSIZE_USEHEADER);
    } 
    
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL CxListView::DeleteAllItems() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return TRUE == ListView_DeleteAllItems(_m_hWnd);
}
//---------------------------------------------------------------------------
INT CxListView::GetSelectedCount() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_GetSelectedCount(_m_hWnd);
}
//---------------------------------------------------------------------------
LPARAM CxListView::GetItemParam(INT Index) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    LVITEM lvi;
    lvi.iItem = Index;
    lvi.iSubItem = 0;
    lvi.mask = LVIF_PARAM;
    if (ListView_GetItem(_m_hWnd, &lvi)) {
        return lvi.lParam;
    } else {
        return 0;
    } 
}
//---------------------------------------------------------------------------
LPARAM CxListView::GetSelectedItemParam() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    INT iSelIndex = ListView_GetNextItem(_m_hWnd, (WPARAM) - 1, LVNI_SELECTED);
    if (- 1 == iSelIndex) {
        return 0;
    }

    return GetItemParam(iSelIndex);
}
//---------------------------------------------------------------------------
POINT CxListView::GetOrigin() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, POINT());

    POINT p;
    ListView_GetOrigin(_m_hWnd, &p);

    return p;
}
//---------------------------------------------------------------------------
BOOL CxListView::Scroll(INT x, INT y) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_Scroll(_m_hWnd, x, y) == TRUE;
}
//---------------------------------------------------------------------------
INT CxListView::GetTopIndex() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_GetTopIndex(_m_hWnd);
}
//---------------------------------------------------------------------------
BOOL CxListView::EnsureVisible(INT Index, BOOL PartialOK) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_EnsureVisible(_m_hWnd, Index, PartialOK) == TRUE;
}
//---------------------------------------------------------------------------
BOOL CxListView::SetExtendedListViewStyle(DWORD ExStyle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    ListView_SetExtendedListViewStyle(_m_hWnd, ExStyle);
    
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL CxListView::View(UINT View) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    LONG nStyle = ::GetWindowLong(_m_hWnd, GWL_STYLE);
    if ((nStyle &LVS_TYPEMASK) != View) {
        ::SetWindowLong(_m_hWnd, GWL_STYLE, (nStyle &~LVS_TYPEMASK) | View);
    } 
    
    return TRUE;
}
//---------------------------------------------------------------------------
UINT CxListView::View() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ::GetWindowLong(_m_hWnd, GWL_STYLE) &LVS_TYPEMASK;
}
//---------------------------------------------------------------------------
INT CxListView::HitTest(INT x, INT y) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    m_HitTestInfo.pt.x = x;
    m_HitTestInfo.pt.y = y;
    
    return ListView_HitTest(_m_hWnd, &m_HitTestInfo);
}
//---------------------------------------------------------------------------
INT CxListView::SubItemHitTest(INT x, INT y) {
    m_HitTestInfo.pt.x = x;
    m_HitTestInfo.pt.y = y;
    return ListView_SubItemHitTest(_m_hWnd, &m_HitTestInfo);
}
//---------------------------------------------------------------------------
tString CxListView::GetItemText(INT Item, INT SubItem) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    TCHAR sText[1024] = {0};
    ListView_GetItemText(_m_hWnd, Item, SubItem, sText, 1024);

    return tString(sText);
}
//---------------------------------------------------------------------------
BOOL CxListView::Arrange() {
    return Arrange(LVA_DEFAULT);
}
//---------------------------------------------------------------------------
BOOL CxListView::Arrange(UINT Code) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_Arrange(_m_hWnd, Code);
}
//---------------------------------------------------------------------------
BOOL CxListView::SetColumnWidth(INT Column, INT Width) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_SetColumnWidth(_m_hWnd, Column, Width);
}
//---------------------------------------------------------------------------
BOOL CxListView::GetColumnOrderArray(INT *Order) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    if (Order == NULL) {
        Order = new INT[m_ColumnCount];
    } 
    
    return ListView_GetColumnOrderArray(_m_hWnd, m_ColumnCount, Order);
}
//---------------------------------------------------------------------------
BOOL CxListView::SetColumnOrderArray(INT *Order) {
    return ListView_SetColumnOrderArray(_m_hWnd, m_ColumnCount, Order);
}
//---------------------------------------------------------------------------
HIMAGELIST CxListView::LargeImageList() {
    return m_hLargeImageList;
}
//---------------------------------------------------------------------------
HIMAGELIST CxListView::SmallImageList() {
    return m_hSmallImageList;
}
//---------------------------------------------------------------------------
HICON CxListView::GetSelectedIcon(BOOL Small) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    INT iSelIndex = ListView_GetNextItem(_m_hWnd, (WPARAM) - 1, LVNI_SELECTED);
    if (iSelIndex ==  - 1) {
        return 0;
    } 

    LVITEM lvi;
    lvi.iItem = iSelIndex;
    lvi.iSubItem = 0;
    lvi.mask = LVIF_IMAGE;
    if (!ListView_GetItem(_m_hWnd, &lvi)) {
        return 0;
    } 

    HICON Icon = ImageList_GetIcon(Small ? m_hSmallImageList : m_hLargeImageList, lvi.iImage, ILD_NORMAL);

    return Icon;
}
//---------------------------------------------------------------------------
INT CxListView::GetFirstSelectedIndex() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_GetNextItem(_m_hWnd, (WPARAM) - 1, LVNI_SELECTED);
}
//---------------------------------------------------------------------------
BOOL CxListView::SelectItem(INT Index) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    ListView_SetItemState(_m_hWnd, Index, LVNI_SELECTED, LVNI_SELECTED);
    
    return TRUE;
}
//---------------------------------------------------------------------------
INT CxListView::HitTest(LPLVHITTESTINFO pinfo) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_HitTest(_m_hWnd, pinfo);
}
//---------------------------------------------------------------------------
HWND CxListView::GetHeader() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, NULL);

    return ListView_GetHeader(_m_hWnd);
}
//---------------------------------------------------------------------------