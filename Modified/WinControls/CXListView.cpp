/****************************************************************************
*	CXListView
*
*****************************************************************************/


#include <Xlib/WinControls/CXListView.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXListView::CXListView() {
	_m_sClassName = WC_LISTVIEW;
	_m_iLeft      = 0;
	_m_iTop       = 0;
	_m_iWidth     = 200;
	_m_iHeight    = 200;
	m_ColumnCount = 0;
	m_ItemCount   = 0;
	OnNMClick     = NULL;
	OnItemChanged = NULL;
	OnColumnClick = NULL;
}
//---------------------------------------------------------------------------
BOOL CXListView::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	if (FALSE == bInitCommonControls(ICC_LISTVIEW_CLASSES)) {
		return FALSE;
	}

	_m_hWnd = ::CreateWindowEx(
						dwExStyles, 
						_m_sClassName.c_str(), 
						NULL, 
						WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT | dwStyles,  
						_m_iLeft,	
						_m_iTop,	 
						_m_iWidth, 
						_m_iHeight, 
						hParent,	 
						(HMENU)hmnuID,			
						(HINSTANCE)::GetWindowLong(hParent, GWL_HINSTANCE), 
						this); 

	if (NULL == _m_hWnd) {
		return FALSE;
	} 

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

	SetDefaultFont();
	Subclass();

	return TRUE;
}
//---------------------------------------------------------------------------
INT CXListView::AddSmallIcon(HICON Icon) {
	return ImageList_AddIcon(m_hSmallImageList, Icon);
}
//---------------------------------------------------------------------------
INT CXListView::AddLargeIcon(HICON Icon) {
	return ImageList_AddIcon(m_hLargeImageList, Icon);
}
//---------------------------------------------------------------------------
BOOL CXListView::RemoveAllIcons() {
	return ImageList_RemoveAll(m_hLargeImageList) && ImageList_RemoveAll(m_hSmallImageList);
}
//---------------------------------------------------------------------------
INT CXListView::GetColumnCount() {
	return m_ColumnCount;
}
//---------------------------------------------------------------------------
INT CXListView::GetItemCount() {
	return m_ItemCount;
}
//---------------------------------------------------------------------------
BOOL CXListView::AddColumn(std::string Text) {
	return AddColumn(Text, 100);
}
//---------------------------------------------------------------------------
BOOL CXListView::AddColumn(std::string Text, INT Width) {
	/*DEBUG*/XASSERT(bIsWindow());

	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.pszText = (char*)Text.c_str();
	lvc.cx = Width;

	return ListView_InsertColumn(_m_hWnd, m_ColumnCount ++, &lvc) !=  - 1;
}
//---------------------------------------------------------------------------
BOOL CXListView::DeleteColumn(INT Index) {
	/*DEBUG*/XASSERT(bIsWindow());

	if (ListView_DeleteColumn(_m_hWnd, Index)) {
		m_ColumnCount --;
		return TRUE;
	} else {
		return FALSE;
	} 
}
//---------------------------------------------------------------------------
INT CXListView::AddItem(std::string Text) {
	return AddItem(Text, 0, 0);
}
//---------------------------------------------------------------------------
INT CXListView::AddItem(std::string Text, LPARAM lParam) {
	/*DEBUG*/XASSERT(bIsWindow());

	return AddItem(Text, lParam, 0);
}
//---------------------------------------------------------------------------
INT CXListView::AddItem(std::string Text, LPARAM lParam, INT Image) {
	/*DEBUG*/XASSERT(bIsWindow());

	LVITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.iItem = m_ItemCount;
	lvi.iSubItem = 0;
	lvi.pszText = (char*)Text.c_str();
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
BOOL CXListView::SetItem(std::string Text, INT Index, INT SubItem) {
	return SetItem(Text, Index, SubItem, 0);
}
//---------------------------------------------------------------------------
BOOL CXListView::SetItem(std::string Text, INT Index, INT SubItem, INT Image) {
	/*DEBUG*/XASSERT(bIsWindow());

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = Index;
	lvi.iImage = Image;
	lvi.iSubItem = SubItem;
	lvi.pszText = (char*)Text.c_str();

	return ListView_SetItem(_m_hWnd, &lvi) !=  - 1;
}
//---------------------------------------------------------------------------
BOOL CXListView::SortItems(PFNLVCOMPARE pfnCompare, LPARAM lParamSort) {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_SortItems(_m_hWnd, pfnCompare, lParamSort);
}
//---------------------------------------------------------------------------
VOID CXListView::AutoSizeColumns() {
	/*DEBUG*/XASSERT(bIsWindow());

	for (INT i = 0; i < m_ColumnCount; i ++) {
		ListView_SetColumnWidth(_m_hWnd, i, LVSCW_AUTOSIZE_USEHEADER);
	} 
}
//---------------------------------------------------------------------------
BOOL CXListView::DeleteAllItems() {
	/*DEBUG*/XASSERT(bIsWindow());

	return TRUE == ListView_DeleteAllItems(_m_hWnd);
}
//---------------------------------------------------------------------------
INT CXListView::GetSelectedCount() {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_GetSelectedCount(_m_hWnd);
}
//---------------------------------------------------------------------------
LPARAM CXListView::GetItemParam(INT Index) {
	/*DEBUG*/XASSERT(bIsWindow());

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
LPARAM CXListView::GetSelectedItemParam() {
	/*DEBUG*/XASSERT(bIsWindow());

	INT iSelIndex = ListView_GetNextItem(_m_hWnd, (WPARAM) - 1, LVNI_SELECTED);
	if (- 1 == iSelIndex) {
		return 0;
	}

	return GetItemParam(iSelIndex);
}
//---------------------------------------------------------------------------
POINT CXListView::GetOrigin() {
	/*DEBUG*/XASSERT(bIsWindow());

	POINT p;
	ListView_GetOrigin(_m_hWnd, &p);

	return p;
}
//---------------------------------------------------------------------------
BOOL CXListView::Scroll(INT x, INT y) {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_Scroll(_m_hWnd, x, y) == TRUE;
}
//---------------------------------------------------------------------------
INT CXListView::GetTopIndex() {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_GetTopIndex(_m_hWnd);
}
//---------------------------------------------------------------------------
BOOL CXListView::EnsureVisible(INT Index, BOOL PartialOK) {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_EnsureVisible(_m_hWnd, Index, PartialOK) == TRUE;
}
//---------------------------------------------------------------------------
VOID CXListView::SetExtendedListViewStyle(DWORD ExStyle) {
	/*DEBUG*/XASSERT(bIsWindow());

	ListView_SetExtendedListViewStyle(_m_hWnd, ExStyle);
}
//---------------------------------------------------------------------------
VOID CXListView::View(UINT View) {
	/*DEBUG*/XASSERT(bIsWindow());

	LONG nStyle = ::GetWindowLong(_m_hWnd, GWL_STYLE);
	if ((nStyle &LVS_TYPEMASK) != View) {
		::SetWindowLong(_m_hWnd, GWL_STYLE, (nStyle &~LVS_TYPEMASK) | View);
	} 
}
//---------------------------------------------------------------------------
UINT CXListView::View() {
	/*DEBUG*/XASSERT(bIsWindow());

	return ::GetWindowLong(_m_hWnd, GWL_STYLE) &LVS_TYPEMASK;
}
//---------------------------------------------------------------------------
INT CXListView::HitTest(INT x, INT y) {
	/*DEBUG*/XASSERT(bIsWindow());

	m_HitTestInfo.pt.x = x;
	m_HitTestInfo.pt.y = y;
	
	return ListView_HitTest(_m_hWnd, &m_HitTestInfo);
}
//---------------------------------------------------------------------------
INT CXListView::SubItemHitTest(INT x, INT y) {
	m_HitTestInfo.pt.x = x;
	m_HitTestInfo.pt.y = y;
	return ListView_SubItemHitTest(_m_hWnd, &m_HitTestInfo);
}
//---------------------------------------------------------------------------
std::string CXListView::GetItemText(INT Item, INT SubItem) {
	/*DEBUG*/XASSERT(bIsWindow());

	CHAR sText[1024];
	ListView_GetItemText(_m_hWnd, Item, SubItem, sText, 1024);

	return std::string(sText);
}
//---------------------------------------------------------------------------
BOOL CXListView::Arrange() {
	return Arrange(LVA_DEFAULT);
}
//---------------------------------------------------------------------------
BOOL CXListView::Arrange(UINT Code) {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_Arrange(_m_hWnd, Code);
}
//---------------------------------------------------------------------------
BOOL CXListView::SetColumnWidth(INT Column, INT Width) {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_SetColumnWidth(_m_hWnd, Column, Width);
}
//---------------------------------------------------------------------------
BOOL CXListView::GetColumnOrderArray(INT *Order) {
	/*DEBUG*/XASSERT(bIsWindow());

	if (Order == NULL) {
		Order = new INT[m_ColumnCount];
	} 
	
	return ListView_GetColumnOrderArray(_m_hWnd, m_ColumnCount, Order);
}
//---------------------------------------------------------------------------
BOOL CXListView::SetColumnOrderArray(INT *Order) {
	return ListView_SetColumnOrderArray(_m_hWnd, m_ColumnCount, Order);
}
//---------------------------------------------------------------------------
HIMAGELIST CXListView::LargeImageList() {
	return m_hLargeImageList;
}
//---------------------------------------------------------------------------
HIMAGELIST CXListView::SmallImageList() {
	return m_hSmallImageList;
}
//---------------------------------------------------------------------------
HICON CXListView::GetSelectedIcon(BOOL Small) {
	/*DEBUG*/XASSERT(bIsWindow());

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
INT CXListView::GetFirstSelectedIndex() {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_GetNextItem(_m_hWnd, (WPARAM) - 1, LVNI_SELECTED);
}
//---------------------------------------------------------------------------
VOID CXListView::SelectItem(INT Index) {
	/*DEBUG*/XASSERT(bIsWindow());

	ListView_SetItemState(_m_hWnd, Index, LVNI_SELECTED, LVNI_SELECTED);
}
//---------------------------------------------------------------------------
INT CXListView::HitTest(LPLVHITTESTINFO pinfo) {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_HitTest(_m_hWnd, pinfo);
}
//---------------------------------------------------------------------------
HWND CXListView::GetHeader() {
	/*DEBUG*/XASSERT(bIsWindow());

	return ListView_GetHeader(_m_hWnd);
}
//---------------------------------------------------------------------------