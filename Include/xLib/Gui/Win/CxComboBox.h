/**
 * \file  CxComboBox.h
 * \brief combobox
 */


#ifndef XLib_Gui_CxComboBoxH
#define XLib_Gui_CxComboBoxH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxComboBox : 
    public CxWindow 
    /// combobox    
{
    public:
        //-------------------------------------
        //константы

                CxComboBox();
               ~CxComboBox();
        BOOL    bCreateRes(INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //сообщения
        #if (xWINVER >= xWIN32_95)
            INT     iFindStringExact       (INT iIndexStart, LPCTSTR pcszFind);
        #endif //xWIN32_95
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetCount              ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_VISTA)
            BOOL    bGetCueBannerText      (LPWSTR pwszText, INT iTextSize);
        #endif //xWIN32_VISTA
        #if (xWINVER >= xWIN32_31)
            INT     iGetCurSel             ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetDroppedControlRect (RECT *prcRect);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iGetDroppedState       ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            UINT    uiGetExtendedUI        ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            LRESULT lpGetItemData          (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_95)
            BOOL    bGetItemHeight         ();
        #endif //xWIN32_95
        #if (xWINVER >= xWIN32_31)
            INT     iGetLBText             (INT iIndex, LPCTSTR pcszText);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetLBTextLen          (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_XP)
            BOOL    bGetMinVisible         ();
        #endif //xWIN32_XP
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetText               (LPTSTR pszText, INT iTextSize);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bGetTextLength         ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iInsertItemData        (INT iIndex, LPARAM lpData);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iInsertString          (INT iIndex, LPCSTR pcszText);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bLimitText             (INT iTextSize);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iResetContent          ();
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSelectItemData        (INT iIndexStart, LPARAM lpData);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSelectString          (INT iIndexStart, LPCTSTR pcszFind);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_VISTA)
            BOOL    bSetCueBannerText      (LPCWSTR pcwszText);
        #endif //xWIN32_VISTA
        #if (xWINVER >= xWIN32_31)
            INT     iSetCurSel             (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetExtendedUI         (UINT uiFlags);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetItemData           (INT iIndex, LPARAM lpData);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iSetItemHeight         (INT iIndex, INT iHeight);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_XP)
            BOOL    bSetMinVisible         (INT iNum);
        #endif //xWIN32_XP
        #if (xWINVER >= xWIN32_31)
            INT     iSetText               (LPTSTR pszText);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bShowDropdown          (BOOL bFlag);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_95)
            INT     iAddItemData           (LPARAM lpData);
        #endif //xWIN32_95
        #if (xWINVER >= xWIN32_31)
            INT     iAddString             (LPCSTR pcszText);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iDeleteString          (INT iIndex);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iDir                   (UINT uiAttr, LPCTSTR pcszFileSpec);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            BOOL    bEnable                (BOOL bFlag);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iFindItemData          (INT iIndexStart, LPARAM lpData);
        #endif //xWIN32_31
        #if (xWINVER >= xWIN32_31)
            INT     iFindString            (INT iIndexStart, LPCTSTR pcszFind);
        #endif //xWIN32_31


        ////BOOL    bAddString   (const tString &csItem);
        ////BOOL    bResetContent();
        ////BOOL    bSetCurSel   (WPARAM wIndex);
        ////BOOL    bLoadFromFile(const tString &csFilePath, INT iItemIndex = - 1);

        //-------------------------------------
        //события
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxComboBoxH
