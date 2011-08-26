/**
 * \file  CxTab.h
 * \brief tab
 */


#ifndef XLib_Gui_CxTabH
#define XLib_Gui_CxTabH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
#include <xLib/Gui/CxWindowImpl.h>
#include <xLib/GUI/CxLayout.h>
//---------------------------------------------------------------------------
////class CxTab;
//---------------------------------------------------------------------------
////class CxLayout : public CxWindowImpl {
////    public:
////          CxLayout(const CxTab *ptabParentTab) {
////              /*DEBUG*/xASSERT(NULL != ptabParentTab);
////
////              _m_ptabParentTab = ptabParentTab;
////
////
////              _m_ulStyle   =  WS_CHILD | WS_TABSTOP | WS_CAPTION;
////              _m_ulStyleEx = WS_EX_CONTROLPARENT;
////
////          };
////         ~CxLayout() {};
////
////        //X_DECLARE_MSG_MAP()
////        X_BEGIN_MSG_MAP(CxLayout)
////            /*X_CMD(m_CxButton3.iGetID(), OnTest)*/
////            /*X_CMD(m_CxButton4.iGetID(), OnTest)*/
////        X_END_MSG_MAP(CxWindowImpl)
////
////        VOID       OnCreate    (WPARAM wParam, LPARAM lParam) {};    /*virtual*/
////        VOID       OnNotify    (WPARAM wParam, LPARAM lParam) {
////            //-------------------------------------
////            //Tab
////            LPNMHDR lpnmhdr = reinterpret_cast<LPNMHDR>(lParam);
////            switch (lpnmhdr->code) {
////                 case TCN_SELCHANGE:
////                     {
////                     LRESULT nSel = _m_ptabParentTab->iGetCurrSel();
////                     switch (nSel) {
////                         case 0:
////                             {
////                             _m_ptabParentTab->bShowTab(0, TRUE);
////                             _m_ptabParentTab->bShowTab(1, FALSE);
////                             }
////                             break;
////                         case 1:
////                             {
////                             _m_ptabParentTab->bShowTab(0, FALSE);
////                             _m_ptabParentTab->bShowTab(1, TRUE);
////                             }
////                             break;
////                         }
////                     }
////                     break;
////            }
////        };    /*virtual*/
////        VOID       OnSize      (WPARAM wParam, LPARAM lParam) {};    /*virtual*/
////        VOID       OnTest      (WORD   id,     LPARAM lParam) {};
////
////    private:
////        const CxTab *_m_ptabParentTab;
////
////};
//////---------------------------------------------------------------------------
////CxLayout::CxLayout() {
////
////}
//////---------------------------------------------------------------------------
////CxLayout::~CxLayout() {
////
////}
//////---------------------------------------------------------------------------
////X_BEGIN_MSG_MAP(CxLayout)
////    /*X_CMD(m_CxButton3.iGetID(), OnTest)*/
////    /*X_CMD(m_CxButton4.iGetID(), OnTest)*/
////X_END_MSG_MAP(CxWindowImpl)
//////---------------------------------------------------------------------------
////VOID CxLayout::OnCreate(WPARAM wParam, LPARAM lParam) {
////    BOOL bRes = FALSE;
////
////    ////bRes = m_CxButton3.bCreateRes(IDC_btnCxButton3, hGetHandle());
////    /////*DEBUG*/xASSERT(TRUE == bRes);
////
////    ////bRes = m_CxButton4.bCreateRes(IDC_btnCxButton4, hGetHandle());
////    /////*DEBUG*/xASSERT(TRUE == bRes);
////}
//////---------------------------------------------------------------------------
////VOID CxLayout::OnNotify(WPARAM wParam, LPARAM lParam) {
////
////}
//////---------------------------------------------------------------------------
////VOID CxLayout::OnSize(WPARAM wParam, LPARAM lParam) {
////
////}
//////---------------------------------------------------------------------------
////VOID CxLayout::OnTest(WORD id, LPARAM) {
////    ::MessageBox(_m_hWnd, "xxxxxxxxxxxxxxx", "Test", 0);
////}
//////---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class CxTab : 
    public CxWindow 
    /// tab
{
    public:
///////////////////////////////////////////////////////////////////////////////////////////////
        ////class CxLayout : public CxWindowImpl {
        ////    public:
        ////        CxLayout() {
        ////            _m_ulStyle   = WS_CHILD | WS_TABSTOP | WS_CAPTION;
        ////            _m_ulStyleEx = WS_EX_CONTROLPARENT;

        ////        };
        ////        ~CxLayout() {};

        ////        //xDECLARE_MSG_MAP()
        ////        ////////xBEGIN_MSG_MAP(CxLayout)
        ////        ////////    /*xCMD(m_CxButton3.iGetID(), OnTest)*/
        ////        ////////    /*xCMD(m_CxButton4.iGetID(), OnTest)*/
        ////        ////////xEND_MSG_MAP(CxWindowImpl)

        ////        VOID OnCreate(WPARAM wParam, LPARAM lParam) {};    /*virtual*/
        ////        VOID OnNotify(WPARAM wParam, LPARAM lParam) {};    /*virtual*/
        ////        VOID OnSize  (WPARAM wParam, LPARAM lParam) {};    /*virtual*/
        ////        VOID OnTest  (WORD   id,     LPARAM lParam) {};

        ////    private:

        ////};
////////////////////////////////////////////////////////////////////////////////////////////////
                    CxTab       ();
                   ~CxTab       ();
        BOOL        bCreateRes  (INT iID, HWND hParent);
        BOOL        bInsertTab  (INT iLayoutID, LPTSTR lpCaption, INT iPos, INT iImage);
        BOOL        bShowTab    (INT iPos, BOOL bFlag);
        INT         iGetCurSel  ();
        LRESULT     GetImageList();
        HIMAGELIST  SetImageList(HIMAGELIST lImageList);

    private:
        std::vector<CxLayout *> _m_vecLayouts;
        BOOL        bPutLayout   (HWND hPageDlg, INT iPos);
};
//---------------------------------------------------------------------------
#endif //XLib_Gui_CxTabH


/*
    TCM_ADJUSTRECT            TabCtrl_AdjustRect
    TCM_DELETEALLITEMS        TabCtrl_DeleteAllItems
    TCM_DELETEITEM            TabCtrl_DeleteItem
    TCM_DESELECTALL            TabCtrl_DeselectAll
    TCM_GETCURFOCUS            TabCtrl_GetCurFocus
    TCM_GETCURSEL            TabCtrl_GetCurSel
    TCM_GETEXTENDEDSTYLE    TabCtrl_GetExtendedStyle
    TCM_GETIMAGELIST        TabCtrl_GetImageList
    TCM_GETITEM                TabCtrl_GetItem
    TCM_GETITEMCOUNT        TabCtrl_GetItemCount
    TCM_GETITEMRECT            TabCtrl_GetItemRect
    TCM_GETROWCOUNT            TabCtrl_GetRowCount
    TCM_GETTOOLTIPS            TabCtrl_GetToolTips
    TCM_GETUNICODEFORMAT    TabCtrl_GetUnicodeFormat
    TCM_HIGHLIGHTITEM        TabCtrl_HighlightItem
    TCM_HITTEST                TabCtrl_HitTest
    TCM_INSERTITEM            TabCtrl_InsertItem
    TCM_REMOVEIMAGE            TabCtrl_RemoveImage
    TCM_SETCURFOCUS            TabCtrl_SetCurFocus
    TCM_SETCURSEL            TabCtrl_SetCurSel
    TCM_SETEXTENDEDSTYLE    TabCtrl_SetExtendedStyle
    TCM_SETIMAGELIST        TabCtrl_SetImageList
    TCM_SETITEM                TabCtrl_SetItem
    TCM_SETITEMEXTRA        TabCtrl_SetItemExtra
    TCM_SETITEMSIZE            TabCtrl_SetItemSize
    TCM_SETMINTABWIDTH        TabCtrl_SetMinTabWidth
    TCM_SETPADDING            TabCtrl_SetPadding
    TCM_SETTOOLTIPS            TabCtrl_SetToolTips
    TCM_SETUNICODEFORMAT    TabCtrl_SetUnicodeFormat
*/
