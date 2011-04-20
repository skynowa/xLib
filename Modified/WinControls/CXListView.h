/****************************************************************************
*	CXListView
*
*****************************************************************************/


#ifndef CXListView_H
#define CXListView_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXListView : public CXSubclassWnd {
	private:
		INT           m_ColumnCount;
		INT           m_ItemCount;
		HIMAGELIST    m_hLargeImageList; //image list for icon view 
		HIMAGELIST    m_hSmallImageList; //image list for other views 
	
	public:
		LVHITTESTINFO m_HitTestInfo;

		              CXListView              ();
		BOOL          Create                  (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
		HIMAGELIST    LargeImageList          ();
		HIMAGELIST    SmallImageList          ();
		INT           GetColumnCount          ();
		INT           GetItemCount            ();
		VOID          View                    (UINT View);
		UINT          View                    ();
		INT           AddSmallIcon            (HICON Icon);
		INT           AddLargeIcon            (HICON Icon);
		BOOL          RemoveAllIcons          ();
		HICON         GetSelectedIcon         (BOOL Small);
		INT           GetFirstSelectedIndex   ();
		VOID          SelectItem              (INT Index);
		BOOL          AddColumn               (std::string Text);
		BOOL          AddColumn               (std::string Text, INT Width);
		BOOL          DeleteColumn            (INT Index);
		INT           AddItem                 (std::string Text);
		INT           AddItem                 (std::string Text, LPARAM lParam);
		INT           AddItem                 (std::string Text, LPARAM lParam, INT Image);
		BOOL          SetItem                 (std::string Text, INT Index, INT SubItem);
		BOOL          SetItem                 (std::string Text, INT Index, INT SubItem, INT Image);
		BOOL          DeleteAllItems          ();
		BOOL          SortItems               (PFNLVCOMPARE pfnCompare, LPARAM lParamSort);
		BOOL          SetColumnWidth          (INT Column, INT Width);
		INT           HitTest                 (LPLVHITTESTINFO pinfo);
		VOID          AutoSizeColumns         ();
		BOOL          Arrange                 ();
		BOOL          Arrange                 (UINT Code);
		INT           GetSelectedCount        ();
		LPARAM        GetItemParam            (INT Index);
		LPARAM        GetSelectedItemParam    ();
		POINT         GetOrigin               ();
		BOOL          Scroll                  (INT x, INT y);
		INT           GetTopIndex             ();
		BOOL          EnsureVisible           (INT Index, BOOL PartialOK);
		VOID          SetExtendedListViewStyle(DWORD ExStyle);
		INT           HitTest                 (INT x, INT y);
		INT           SubItemHitTest          (INT x, INT y);
		std::string   GetItemText             (INT Item, INT SubItem);
		BOOL          GetColumnOrderArray     (INT *Order);
		BOOL          SetColumnOrderArray     (INT *Order);
		HWND          GetHeader               ();

		VOID          (*OnNMClick)            (LPNMITEMACTIVATE lpnmitem);
		VOID          (*OnItemChanged)        (LPNMLISTVIEW pNMLV);
		VOID          (*OnColumnClick)        (LPNMLISTVIEW pNMLV);
};
//---------------------------------------------------------------------------
#endif
