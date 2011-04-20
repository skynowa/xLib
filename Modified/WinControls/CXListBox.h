/****************************************************************************
*	CXListBox
*
*****************************************************************************/


#ifndef CXListBox_H
#define CXListBox_H
///---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
// #include <windows.h>
// #include <commctrl.h>
//---------------------------------------------------------------------------
class CXListBox: public CXSubclassWnd {
	private:
	
	public:
		        CXListBox          ();
		BOOL    Create             (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
		LRESULT AddString          (LPARAM lString);
		LRESULT ResetContent       ();
		LRESULT AddFile            (LPARAM lFileName);
		LRESULT DeleteString       (WPARAM wStartIndex);
		LRESULT FindString         (WPARAM wStartIndex, LPARAM lString);
		LRESULT FindStringExact    (WPARAM wStartIndex, LPARAM lString);
		LRESULT GetAnchorIndex     ();
		LRESULT GetCaretIndex      ();
		LRESULT GetCount           ();
		LRESULT GetCurSel          ();
		LRESULT GetHorizontalExtent();
		LRESULT GetItemData        (WPARAM wItemIndex);
		LRESULT GetItemHeight      (WPARAM wItemIndex);
		LRESULT GetItemRect        (WPARAM wItemIndex, LPARAM lRect);
		LRESULT GetListBoxInfo     ();
		LRESULT GetLocale          ();
		LRESULT GetSel             (WPARAM wItemIndex);
		LRESULT GetSelCount        ();
		LRESULT GetSelItems        (LPARAM lItems);
		LRESULT GetText            (WPARAM wItemIndex, LPARAM lItems);
		LRESULT GetTextLen         (WPARAM wItemIndex);
		LRESULT GetTopIndex        ();
		LRESULT InitStorage        (WPARAM wItemsCount, LPARAM lMem);
		LRESULT InsertString       (WPARAM wItemIndex, LPARAM lString);
		LRESULT ItemFromPoint      (LPARAM lPoint);
		LRESULT SelectString       (WPARAM wStartIndex, LPARAM lString);
		LRESULT SelItemRange       (WPARAM wOption, LPARAM lFirstLastItems);
		LRESULT SelItemRangeEx     (WPARAM wFirstItem, LPARAM lLastItem);
		LRESULT SetAnchorIndex     (WPARAM wItemIndex);
		LRESULT SetCaretIndex      (WPARAM wItemIndex);
		LRESULT SetColumnWidth     (WPARAM wWidth);
		LRESULT SetCount           (WPARAM wCount);
		LRESULT SetCurSel          (WPARAM wItemIndex);
		LRESULT SetHorizontalExtent(WPARAM wScrollWidth);
		LRESULT SetItemData        (WPARAM wItemIndex, LPARAM lValue);
		LRESULT SetItemHeight      (WPARAM wItemIndex, LPARAM lHeight);
		LRESULT SetLocale          (WPARAM wLocaleIdentifier);
		LRESULT SetSel             (WPARAM wSelOption, LPARAM lItemIndex);
		LRESULT SetTabStops        (WPARAM wTabStopsNum, LPARAM lTabStopsArr);
		LRESULT SetTopIndex        (WPARAM wItemIndex);
		LRESULT VScroll            (WPARAM wPos);
};
//---------------------------------------------------------------------------
#endif
