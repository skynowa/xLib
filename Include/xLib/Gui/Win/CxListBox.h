/**
 * \file  CxListBox.h
 * \brief list box
 */


#ifndef XLib_Gui_CxListBoxH
#define XLib_Gui_CxListBoxH
///---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
///---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxListBox :
    public CxWindow
    /// list box
{
    public:
        //-------------------------------------
        //���������

             CxListBox           ();
            ~CxListBox           ();

        BOOL bCreateRes(INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������
        #if (xWINVER >= xWIN32_31)
            INT     iDir                (UINT uiAttr, LPCTSTR pcszFileSpec);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bEnable             (BOOL bFlag);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iFindItemData       (INT iIndexStart, LPARAM plpData);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iFindString         (INT iIndexStart, LPCTSTR pcszFind);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iFindStringExact    (INT iIndexStart, LPCTSTR pcszFind);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_95)
            INT     iGetCaretIndex      ();
        #endif //xWIN32_95
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetCount           ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iGetCurSel          ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetHorizontalExtent();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            LRESULT lpGetItemData       (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iGetItemHeight      (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iGetItemRect        (INT iIndex, RECT *prcRect);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            ULONG   ulGetSel            (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iGetSelCount        ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iGetSelItems        (INT iItems, INT *piItems);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iGetText            (INT iIndex, LPCTSTR pcszText);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetTextLen         (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetTopIndex        ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iInsertItemData     (INT iIndex, LPARAM lpData);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iInsertString       (INT index, LPCSTR pcszText);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bResetContent       ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSelectItemData     (INT iIndexStart, LPARAM lpData);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSelectString       (INT iIndexStart, LPCTSTR pcszFind);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSelItemRange       (BOOL bFlag, INT iFirst, INT iLast);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetCaretIndex      (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bSetColumnWidth     (INT iColumn);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetCurSel          (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bSetHorizontalExtent(INT iExtent);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetItemData        (INT iIndex, LPARAM lpData);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetItemHeight      (INT iIndex, LPARAM lpHeight);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iAddString          (LPCSTR pcszText);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iDeleteString       (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetSel             (INT iIndex, BOOL bFlag);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bSetTabStops        (INT iTabs, INT *piTabs);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetTopIndex        (INT iIndex);
        #endif //xWIN32_31


        ////BOOL bAddString          (const tString &csItem);
        ////BOOL bResetContent       ();
        ////BOOL bAddFile            (const tString &csFileName);
        ////BOOL bDeleteString       (INT iStartIndex);
        ////BOOL bDir                (UINT uiDir);
        ////BOOL bFindString         (WPARAM wStartIndex, LPARAM lString);
        ////BOOL bFindStringExact    (WPARAM wStartIndex, LPARAM lString);
        ////BOOL bGetAnchorIndex     ();
        ////BOOL bGetCaretIndex      ();
        ////BOOL bGetCount           ();
        ////BOOL bGetCurSel          ();
        ////BOOL bGetHorizontalExtent();
        ////BOOL bGetItemData        (WPARAM wItemIndex);
        ////BOOL bGetItemHeight      (WPARAM wItemIndex);
        ////BOOL bGetItemRect        (WPARAM wItemIndex, LPARAM lRect);
        ////BOOL bGetListBoxInfo     ();
        ////BOOL bGetLocale          ();
        ////BOOL bGetSel             (WPARAM wItemIndex);
        ////BOOL bGetSelCount        ();
        ////BOOL bGetSelItems        (LPARAM lItems);
        ////BOOL bGetText            (WPARAM wItemIndex, LPARAM lItems);
        ////BOOL bGetTextLen         (WPARAM wItemIndex);
        ////BOOL bGetTopIndex        ();
        ////BOOL bInitStorage        (WPARAM wItemsCount, LPARAM lMem);
        ////BOOL bInsertString       (WPARAM wItemIndex, LPARAM lString);
        ////BOOL bItemFromPoint      (LPARAM lPoint);
        ////BOOL bSelectString       (WPARAM wStartIndex, LPARAM lString);
        ////BOOL bSelItemRange       (WPARAM wOption, LPARAM lFirstLastItems);
        ////BOOL bSelItemRangeEx     (WPARAM wFirstItem, LPARAM lLastItem);
        ////BOOL bSetAnchorIndex     (WPARAM wItemIndex);
        ////BOOL bSetCaretIndex      (WPARAM wItemIndex);
        ////BOOL bSetColumnWidth     (WPARAM wWidth);
        ////BOOL bSetCount           (WPARAM wCount);
        ////BOOL bSetCurSel          (WPARAM wItemIndex);
        ////BOOL bSetHorizontalExtent(WPARAM wScrollWidth);
        ////BOOL bSetItemData        (WPARAM wItemIndex, LPARAM lValue);
        ////BOOL bSetItemHeight      (WPARAM wItemIndex, LPARAM lHeight);
        ////BOOL bSetLocale          (WPARAM wLocaleIdentifier);
        ////BOOL bSetSel             (WPARAM wSelOption, LPARAM lItemIndex);
        ////BOOL bSetTabStops        (WPARAM wTabStopsNum, LPARAM lTabStopsArr);
        ////BOOL bSetTopIndex        (WPARAM wItemIndex);
        ////BOOL bVScroll            (WPARAM wPos);

        //-------------------------------------
        //�������
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxListBoxH
