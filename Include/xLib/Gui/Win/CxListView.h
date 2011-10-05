/**
 * \file  CxListView.h
 * \brief list view
 */


#ifndef XLib_Gui_CxListViewH
#define XLib_Gui_CxListViewH
//---------------------------------------------------------------------------
#include <xLib/Gui/Win/CxWindow.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxListView :
    public CxWindow
    /// list view
{
    private:
        INT           m_ColumnCount;
        INT           m_ItemCount;
        HIMAGELIST    m_hLargeImageList; //image list for icon view
        HIMAGELIST    m_hSmallImageList; //image list for other views

    public:
        LVHITTESTINFO m_HitTestInfo;

                      CxListView              ();
                     ~CxListView              ();
        BOOL          bCreateRes              (INT iID, CxWindow *pwndParent);

        BOOL          Create                  (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
        HIMAGELIST    LargeImageList          ();
        HIMAGELIST    SmallImageList          ();
        INT           GetColumnCount          ();
        INT           GetItemCount            ();
        BOOL          View                    (UINT View);
        UINT          View                    ();
        INT           AddSmallIcon            (HICON Icon);
        INT           AddLargeIcon            (HICON Icon);
        BOOL          RemoveAllIcons          ();
        HICON         GetSelectedIcon         (BOOL Small);
        INT           GetFirstSelectedIndex   ();
        BOOL          SelectItem              (INT Index);
        BOOL          AddColumn               (tString Text);
        BOOL          AddColumn               (tString Text, INT Width);
        BOOL          DeleteColumn            (INT Index);
        INT           AddItem                 (tString Text);
        INT           AddItem                 (tString Text, LPARAM lParam);
        INT           AddItem                 (tString Text, LPARAM lParam, INT Image);
        BOOL          SetItem                 (tString Text, INT Index, INT SubItem);
        BOOL          SetItem                 (tString Text, INT Index, INT SubItem, INT Image);
        BOOL          DeleteAllItems          ();
        BOOL          SortItems               (PFNLVCOMPARE pfnCompare, LPARAM lParamSort);
        BOOL          SetColumnWidth          (INT Column, INT Width);
        INT           HitTest                 (LPLVHITTESTINFO pinfo);
        BOOL          AutoSizeColumns         ();
        BOOL          Arrange                 ();
        BOOL          Arrange                 (UINT Code);
        INT           GetSelectedCount        ();
        LPARAM        GetItemParam            (INT Index);
        LPARAM        GetSelectedItemParam    ();
        POINT         GetOrigin               ();
        BOOL          Scroll                  (INT x, INT y);
        INT           GetTopIndex             ();
        BOOL          EnsureVisible           (INT Index, BOOL PartialOK);
        BOOL          SetExtendedListViewStyle(DWORD ExStyle);
        INT           HitTest                 (INT x, INT y);
        INT           SubItemHitTest          (INT x, INT y);
        tString   GetItemText             (INT Item, INT SubItem);
        BOOL          GetColumnOrderArray     (INT *Order);
        BOOL          SetColumnOrderArray     (INT *Order);
        HWND          GetHeader               ();

        ////VOID          (*OnNMClick)            (LPNMITEMACTIVATE lpnmitem);
        ////VOID          (*OnItemChanged)        (LPNMLISTVIEW pNMLV);
        ////VOID          (*OnColumnClick)        (LPNMLISTVIEW pNMLV);
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxListViewH
