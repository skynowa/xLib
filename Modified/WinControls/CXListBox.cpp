/****************************************************************************
*	CXListBox
*
*****************************************************************************/


#include <Xlib/WinControls/CXListBox.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXListBox::CXListBox() {
	_m_sClassName = "LISTBOX";
	_m_iLeft      = 0; 
	_m_iTop       = 0;
	_m_iWidth     = 200;
	_m_iHeight    = 200;
}
//---------------------------------------------------------------------------
BOOL CXListBox::Create(HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles) {
	_m_hWnd = ::CreateWindowEx(
					dwExStyles,
					_m_sClassName.c_str(),  
					_m_sText.c_str(),           
					WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | WS_VSCROLL | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | dwStyles,  
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

	SetDefaultFont();
	Subclass();

	return TRUE;}
//---------------------------------------------------------------------------
LRESULT CXListBox::AddString(LPARAM lString) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_ADDSTRING, NULL, lString);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::ResetContent() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_RESETCONTENT, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::AddFile(LPARAM lFileName) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_ADDFILE, NULL, lFileName);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::DeleteString(WPARAM wStartIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_DELETESTRING, wStartIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::FindString(WPARAM wStartIndex, LPARAM lString) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_FINDSTRING, wStartIndex, lString);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::FindStringExact(WPARAM wStartIndex, LPARAM lString) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_FINDSTRINGEXACT, wStartIndex, lString);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetAnchorIndex() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETANCHORINDEX, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetCaretIndex() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETCARETINDEX, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetCount() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETCOUNT, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetCurSel() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETCURSEL, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetHorizontalExtent() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETHORIZONTALEXTENT, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetItemData(WPARAM wItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETITEMDATA, wItemIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetItemHeight(WPARAM wItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETITEMHEIGHT, wItemIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetItemRect(WPARAM wItemIndex, LPARAM lRect) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETITEMRECT, wItemIndex, lRect);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetListBoxInfo() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETLISTBOXINFO, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetLocale() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETLOCALE, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetSel(WPARAM wItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETSEL, wItemIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetSelCount() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETSELCOUNT, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetSelItems(LPARAM lItems) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETSELITEMS, NULL, lItems);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetText(WPARAM wItemIndex, LPARAM lItems) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETTEXT, wItemIndex, lItems);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetTextLen(WPARAM wItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETTEXTLEN, wItemIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::GetTopIndex() {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_GETTOPINDEX, NULL, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::InitStorage(WPARAM wItemsCount, LPARAM lMem) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_INITSTORAGE, wItemsCount, lMem);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::InsertString(WPARAM wItemIndex, LPARAM lString) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_INSERTSTRING, wItemIndex, lString);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::ItemFromPoint(LPARAM lPoint) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_ITEMFROMPOINT, NULL, lPoint);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SelectString(WPARAM wStartIndex, LPARAM lString) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SELECTSTRING, wStartIndex, lString);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SelItemRange(WPARAM wOption, LPARAM lFirstLastItems) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SELITEMRANGE, wOption, lFirstLastItems);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SelItemRangeEx(WPARAM wFirstItem, LPARAM lLastItem) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SELITEMRANGEEX, wFirstItem, lLastItem);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetAnchorIndex(WPARAM wItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETANCHORINDEX, wItemIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetCaretIndex(WPARAM wItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETCARETINDEX, wItemIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetColumnWidth(WPARAM wWidth) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETCOLUMNWIDTH, wWidth, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetCount(WPARAM wCount) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETCOUNT, wCount, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetCurSel(WPARAM wItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETCURSEL, wItemIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetHorizontalExtent(WPARAM wScrollWidth) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETHORIZONTALEXTENT, wScrollWidth, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetItemData(WPARAM wItemIndex, LPARAM lValue) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETITEMDATA, wItemIndex, lValue);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetItemHeight(WPARAM wItemIndex, LPARAM lHeight) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETITEMHEIGHT, wItemIndex, lHeight);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetLocale(WPARAM wLocaleIdentifier) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETLOCALE, wLocaleIdentifier, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetSel(WPARAM wSelOption, LPARAM lItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETSEL, wSelOption, lItemIndex);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetTabStops(WPARAM wTabStopsNum, LPARAM lTabStopsArr) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETTABSTOPS, wTabStopsNum, lTabStopsArr);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::SetTopIndex(WPARAM wItemIndex) {
	/*DEBUG*/XASSERT(bIsWindow());

	return SendMessage(LB_SETTOPINDEX, wItemIndex, NULL);
}
//---------------------------------------------------------------------------
LRESULT CXListBox::VScroll(WPARAM wPos) {
	/*DEBUG*/XASSERT(bIsWindow());

    return SendMessage(WM_VSCROLL, MAKEWORD(wPos, 0), 0);
}
//---------------------------------------------------------------------------