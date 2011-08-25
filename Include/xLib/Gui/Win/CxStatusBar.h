/**
 * \file  CxStatusBar.h
 * \brief status bar
 */


#ifndef XLib_Gui_CxStatusBarH
#define XLib_Gui_CxStatusBarH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxStatusBar: public CxWindow {
    public:
        //������ (�����������)
        class CXItems {
            public:
                        CXItems    ();
                       ~CXItems    ();

                BOOL    bSetParent (CxStatusBar *pstaParent);
                BOOL    bAdd       ();
                BOOL    bSet       (INT iIndex, HICON hIcon, const tString &csText, const tString &csTipText, INT iWidth, UINT uiType);
                BOOL    bInsert    (INT iIndex, HICON hIcon, const tString &csText, const tString &csTipText, INT iWidth, UINT uiType);
                BOOL    bRemove    (INT iIndex);
                BOOL    bClear     ();
                BOOL    bUpdateAll ();
                tString sGetText   (INT iIndex);
                BOOL    bSetText   (INT iIndex, const tString &csText, UINT uiType);
                tString sGetTipText(INT iIndex);
                BOOL    bSetTipText(INT iIndex, const tString &csText);
                BOOL    bSetIcon   (INT iIndex, HICON hIcon);
                HICON   hGetIcon   (INT iIndex);
                BOOL    bSetWidth  (INT iIndex, INT iWidth);
                INT     iGetWidth  (INT iIndex);
                BOOL    bGetRect   (INT iIndex, RECT *prcRect);

            private:
                //������ (�����������)
                class CXItem {
                    public:
                        HICON                   m_hIcon;
                        tString                 m_sText;
                        tString                 m_sTipText;
                        INT                     m_iWidth;
                        UINT                    m_uiType;    //SBT_NOBORDERS, SBT_POPOUT, SBT_RTLREADING, SBT_OWNERDRAW

                        static std::vector<INT> m_veciWidths;

                        CXItem() :
                            m_hIcon(NULL), m_sText(), m_sTipText(), m_iWidth(0), m_uiType(0)
                        {
                        }

                    private:
                };

                BOOL                   _m_bRes;
                CxStatusBar           *_m_pstaParent;
                std::vector<CXItem *>  _m_vecpItems;
        };

        CXItems m_Items;    //������

                CxStatusBar      ();
               ~CxStatusBar      ();

        BOOL    bCreateRes       (INT iID, CxWindow *pwndParent);
        BOOL    bIsSimple           ();
        BOOL    bSetSimple          (BOOL bFlag);
        BOOL    bIsUnicodeFormat ();
        BOOL    bSetUnicodeFormat(BOOL bFlag);
        BOOL    bSetMinHeight    (INT iHeight);
        BOOL    bGetBorders      (INT *piHorz, INT *piVert, INT *piSpacing);
        BOOL    bSetBkColor      (COLORREF crColor);
      //BOOL    bSetParts        (INT iParts);
      //INT     iGetParts        (/*PARAMS*/);

    private:
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxStatusBarH
