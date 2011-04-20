/****************************************************************************
* Class name:  CxStatusBar
* Description: ������ ���������
* File name:   CxStatusBar.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     26.07.2009 23:49:15
*
*****************************************************************************/



#include <xLib/Gui/CxStatusBar.h>

#include <xLib/GUI/CxApplication.h>


/****************************************************************************
*    public: static
*
*****************************************************************************/

std::vector<INT> CxStatusBar::CXItems::CXItem::m_veciWidths;


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxStatusBar (�����������)
CxStatusBar::CxStatusBar() {
    /*DEBUG*/

    LOG(); 

    //-------------------------------------
    //�������������� ��������� ����
    _m_sClassName     = xCXSTATUSBAR_CONTROL_CLASS;
    _m_ulStyle        = xCXSTATUSBAR_DEFAULT_WINDOW_STYLE | SBT_TOOLTIPS /*| SBARS_SIZEGRIP*/;
    _m_ulStyleEx      = xCXSTATUSBAR_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXSTATUSBAR_DEFAULT_WIDTH;
    _m_iHeight        = xCXSTATUSBAR_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;
    
    //TODO: _bInitCommonControls
    _bInitCommonControls(ICC_BAR_CLASSES);
}
//---------------------------------------------------------------------------
//TODO: - ~CxStatusBar (����������)
CxStatusBar::~CxStatusBar() {
    /*DEBUG*/

    LOG();
}
//---------------------------------------------------------------------------
//DONE: bCreateRes (�������� �� ��������)
BOOL CxStatusBar::bCreateRes(INT iID, CxWindow *pwndParent) {
    /*DEBUG*/xASSERT_RET(NULL == _m_hWnd, FALSE);
    /*DEBUG*/xASSERT_RET(0 < iID,         FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

    _m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName, CxResources::sGetText(iID), 
                                CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID), 
                                CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID), 
                                CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
                                this);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //���������� �������
    _m_bRes = m_Items.bSetParent(this);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsSimple (Checks a status bar control to determine if it is in simple mode)
BOOL CxStatusBar::bIsSimple() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, SB_ISSIMPLE, 0, 0);
    /*DEBUG*/// n/a 

    return _m_bRes;
}
//---------------------------------------------------------------------------
//DONE: bSetSimple (Specifies whether a status window displays simple text or displays all window parts set by a previous SB_SETPARTS message.)
BOOL CxStatusBar::bSetSimple(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*/// bFlag - n/a

    xSNDMSG(BOOL, SB_SIMPLE, bFlag, 0);
    /*DEBUG*/// n/a 

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetUnicodeFormat (Sets the Unicode character format flag for the control. This message allows you to change the character set used by the control at run time rather than having to re-create the control. )
BOOL CxStatusBar::bSetUnicodeFormat(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*/// bFlag - n/a

    xSNDMSG(BOOL, SB_SETUNICODEFORMAT, bFlag, 0);
    /*DEBUG*/// n/a 

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsUnicodeFormat (Retrieves the Unicode character format flag for the control)
BOOL CxStatusBar::bIsUnicodeFormat() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes =  xSNDMSG(BOOL, SB_GETUNICODEFORMAT, 0, 0);
    /*DEBUG*/// n/a 

    return _m_bRes;
}
//---------------------------------------------------------------------------
//DONE: bSetMinHeight (Sets the minimum height of a status window's drawing area)
BOOL CxStatusBar::bSetMinHeight(INT iHeight) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*/// iHeight - n/a 

    xSNDMSG(VOID, SB_SETMINHEIGHT, iHeight, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetBorders (Retrieves the current widths of the horizontal and vertical borders of a status window. )
BOOL CxStatusBar::bGetBorders(INT *piHorz, INT *piVert, INT *piSpacing) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*/// piHorz    - n/a
    /*DEBUG*/// piVert    - n/a
    /*DEBUG*/// piSpacing - n/a

    INT ariBorderWidths[3] = {0};

    _m_bRes = xSNDMSG(BOOL, SB_GETBORDERS, 0, &ariBorderWidths);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    if (NULL != piHorz) {
        *piHorz = ariBorderWidths[0];
    }
    if (NULL != piVert) {
        *piVert = ariBorderWidths[1];
    }
    if (NULL != piSpacing) {
        *piSpacing = ariBorderWidths[2];
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetBkColor (Sets the background color in a status bar)
BOOL CxStatusBar::bSetBkColor(COLORREF crColor) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*/// crColor - n/a

    xSNDMSG(COLORREF, SB_SETBKCOLOR, 0, crColor);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - iGetParts (Retrieves a count of the parts in a status window. The message also retrieves the coordinate of the right edge of the specified number of parts. )
////INT CxStatusBar::iGetParts(/*PARAMS*/) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    INT iRes = 0;
////
////    ////_m_bRes = static_cast<BOOL>( xSNDMSG((UINT)SB_GETPARTS, (WPARAM)xxxx, (LPARAM)xxxx) );
////    /////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
////
////    return iRes;
////}
//---------------------------------------------------------------------------
//TODO: - bSetParts (Sets the number of parts in a status window and the coordinate of the right edge of each part)
////BOOL CxStatusBar::bSetParts(INT iParts) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////    /*DEBUG*///iParts <= 256
////
////    ////m_iNumParts = iParts;
////
////    ////m_veciParts.resize(m_iNumParts);
////
////    ////_m_bRes = xSNDMSG(BOOL, SB_SETPARTS, m_iNumParts, &m_veciParts);
////    /////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
////
////    return TRUE;
////}
//---------------------------------------------------------------------------


/****************************************************************************
*    ����� CXItems - ������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CXItems (�����������)
CxStatusBar::CXItems::CXItems() :
    _m_bRes      (FALSE),
    _m_pstaParent(NULL),
    _m_vecpItems ()
{
    /*DEBUG*/xASSERT_DO(FALSE == _m_bRes,              return);
    /*DEBUG*/xASSERT_DO(NULL  == _m_pstaParent,        return);
    /*DEBUG*/xASSERT_DO(TRUE  == _m_vecpItems.empty(), return);
}
//---------------------------------------------------------------------------
//DONE: ~CXItems (����������)
CxStatusBar::CXItems::~CXItems() {
    /*DEBUG*/xASSERT_DO(NULL != _m_pstaParent, return);

    for (INT i = 0; i < (INT)_m_vecpItems.size(); ++ i) {
        xDELETE_PTR(_m_vecpItems.at(i));
    }    
}
//---------------------------------------------------------------------------
//DONE: bSetParent (��������� ��������� CxStatusBar-�)
BOOL CxStatusBar::CXItems::bSetParent(CxStatusBar *pstaParent) {
    /*DEBUG*/// _m_pstaParent - n/a
    /*DEBUG*/xASSERT_RET(NULL != pstaParent, FALSE);

    _m_pstaParent = pstaParent;       

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bAdd (���������� ������� ������)
BOOL CxStatusBar::CXItems::bAdd() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);

    CXItem::m_veciWidths.resize(CXItem::m_veciWidths.size() + 1);
    _m_bRes = xSNDMSG_API(BOOL, _m_pstaParent->hGetHandle(), SB_SETPARTS, CXItem::m_veciWidths.size(), &CXItem::m_veciWidths.at(0));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //��������� ����������
    CXItem *pItem = new CXItem();
    /*DEBUG*/xASSERT_RET(NULL != pItem, FALSE);

    pItem->m_hIcon    = NULL;
    pItem->m_sText    = xT("");
    pItem->m_sTipText = xT("");
    pItem->m_iWidth   = 0;
    pItem->m_uiType   = 0;

    _m_vecpItems.push_back(pItem);

    //-------------------------------------
    //���������� ���������
    _m_bRes = bUpdateAll();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSet (���������)
BOOL CxStatusBar::CXItems::bSet(INT iIndex, HICON hIcon, const tString &csText, const tString &csTipText, INT iWidth, UINT uiType) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????
    /*DEBUG*///hIcon     - n/a
    /*DEBUG*///csText    - n/a
    /*DEBUG*///csTipText - n/a
    /*DEBUG*///iWidth    - n/a
    /*DEBUG*///uiType    - n/a

    //-------------------------------------
    //��������� ����������
    _m_vecpItems.at(iIndex)->m_hIcon    = hIcon;
    _m_vecpItems.at(iIndex)->m_sText    = csText;
    _m_vecpItems.at(iIndex)->m_sTipText = csTipText;
    _m_vecpItems.at(iIndex)->m_iWidth   = iWidth;
    _m_vecpItems.at(iIndex)->m_uiType   = uiType;

    //-------------------------------------
    //���������� ���������
    _m_bRes = bUpdateAll();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bInsert (�������)
BOOL CxStatusBar::CXItems::bInsert(INT iIndex, HICON hIcon, const tString &csText, const tString &csTipText, INT iWidth, UINT uiType) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????
    /*DEBUG*///hIcon     - n/a
    /*DEBUG*///csText    - n/a
    /*DEBUG*///csTipText - n/a
    /*DEBUG*///iWidth    - n/a
    /*DEBUG*///uiType    - n/a

    //-------------------------------------
    //���������� ������� ������
    CXItem::m_veciWidths.insert(CXItem::m_veciWidths.begin() + iIndex, 0);
    _m_bRes = xSNDMSG_API(BOOL, _m_pstaParent->hGetHandle(), SB_SETPARTS, CXItem::m_veciWidths.size(), &CXItem::m_veciWidths.at(0));
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //-------------------------------------
    //��������� ����������
    CXItem *pItem = new CXItem();
    /*DEBUG*/xASSERT_RET(NULL != pItem, FALSE);

    pItem->m_hIcon    = hIcon;
    pItem->m_sText    = csText;
    pItem->m_sTipText = csTipText;
    pItem->m_iWidth   = iWidth;
    pItem->m_uiType   = uiType;

    _m_vecpItems.insert(_m_vecpItems.begin() + iIndex, pItem);

    //-------------------------------------
    //���������� ���������
    _m_bRes = bUpdateAll();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRemove (��������)
BOOL CxStatusBar::CXItems::bRemove(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex - n/a  ???????

    //-------------------------------------
    //��������� ����������
    CXItem::m_veciWidths.erase(CXItem::m_veciWidths.begin() + iIndex);
    xDELETE_PTR(_m_vecpItems.at(iIndex));    _m_vecpItems.erase(_m_vecpItems.begin() + iIndex);    

    //-------------------------------------
    //���������� ���������
    _m_bRes = bUpdateAll();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (�������� ����)
BOOL CxStatusBar::CXItems::bClear()  {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);

    //-------------------------------------
    //��������� ����������
    CXItem::m_veciWidths.clear();
    for (INT i = 0; i < (INT)_m_vecpItems.size(); ++ i) {xDELETE_PTR(_m_vecpItems.at(i));}    _m_vecpItems.clear();

    //-------------------------------------
    //���������� ���������
    _m_bRes = bUpdateAll();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bUpdateAll (���������� ����)
BOOL CxStatusBar::CXItems::bUpdateAll() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);

    //-------------------------------------
    //���� ���� ������ ��� ������
    if (true == _m_vecpItems.empty()) {            
        /*DEBUG*/xASSERT_RET(true == CXItem::m_veciWidths.empty(), FALSE);

        CXItem::m_veciWidths.resize(1);
        CXItem::m_veciWidths.at(0) = 0;

        _m_bRes = xSNDMSG_API(BOOL, _m_pstaParent->hGetHandle(), SB_SETPARTS, CXItem::m_veciWidths.size(), &CXItem::m_veciWidths.at(0));
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }

    //-------------------------------------
    //���������� �������
    for (INT i = 0, _iWidth = 0; i < (INT)_m_vecpItems.size(); ++ i) {
        _m_bRes = bSetIcon   (i, _m_vecpItems.at(i)->m_hIcon);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = bSetText   (i, _m_vecpItems.at(i)->m_sText, _m_vecpItems.at(i)->m_uiType);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = bSetTipText(i, _m_vecpItems.at(i)->m_sTipText);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _iWidth += _m_vecpItems.at(i)->m_iWidth;
        _m_bRes = bSetWidth  (i, _iWidth);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }

    //-------------------------------------
    //�������� ��������� ������
    if (0 != _m_vecpItems.size()) {
        _m_bRes = bSetWidth(_m_vecpItems.size() - 1, - 1);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetText (The SB_GETTEXT message retrieves the text from the specified part of a status window)
tString CxStatusBar::CXItems::sGetText(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex - n/a  ???????

    tString sRes;
    ULONG   ulRes;

    ulRes = xSNDMSG_API(ULONG, _m_pstaParent->hGetHandle(), SB_GETTEXTLENGTH, iIndex, 0);
    /*DEBUG*/// n/a

    sRes.resize(LOWORD(ulRes));

    ulRes = xSNDMSG_API(ULONG, _m_pstaParent->hGetHandle(), SB_GETTEXT, iIndex, &sRes.at(0));
    /*DEBUG*/xASSERT_RET(sRes.size() == LOWORD(ulRes), tString());

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bSetText (The SB_SETTEXT message sets the text in the specified part of a status window)
BOOL CxStatusBar::CXItems::bSetText(INT iIndex, const tString &csText, UINT uiType) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????
    /*DEBUG*///csText    - n/a
    /*DEBUG*///uiType    - n/a

    _m_bRes = xSNDMSG_API(BOOL, _m_pstaParent->hGetHandle(), SB_SETTEXT, iIndex | uiType, csText.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bGetTipText (Retrieves the tooltip text for a part in a status bar. The status bar must be created with the SBT_TOOLTIPS style to enable tooltips)
tString CxStatusBar::CXItems::sGetTipText(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????

    tString sRes(256, xT('\0'));

    xSNDMSG_API(VOID, _m_pstaParent->hGetHandle(), SB_GETTIPTEXT, MAKEWPARAM(iIndex, 256/*FIX: nSize*/), &sRes.at(0));
    /*DEBUG*/// n/a

    return sRes.assign(sRes.c_str());
}
//---------------------------------------------------------------------------
//DONE: bSetTipText (Sets the tooltip text for a part in a status bar. The status bar must have been created with the SBT_TOOLTIPS style to enable tooltips.)
BOOL CxStatusBar::CXItems::bSetTipText(INT iIndex, const tString &csText) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????
    /*DEBUG*///csText    - n/a

    xSNDMSG_API(VOID, _m_pstaParent->hGetHandle(), SB_SETTIPTEXT, iIndex, csText.c_str());
    /*DEBUG*/// n/a 

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: hGetIcon (Retrieves the icon for a part in a status bar)
HICON CxStatusBar::CXItems::hGetIcon(INT iIndex) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex - n/a  ???????

    HICON hIcon = NULL;

    hIcon = xSNDMSG_API(HICON, _m_pstaParent->hGetHandle(), SB_GETICON, iIndex, 0);
    /*DEBUG*/xASSERT_RET(NULL != hIcon, NULL); 

    return hIcon;
}
//---------------------------------------------------------------------------
//DONE: bSetIcon (Sets the icon for a part in a status bar)
BOOL CxStatusBar::CXItems::bSetIcon(INT iIndex, HICON hIcon) {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????
    /*DEBUG*///hIcon     - n/a

    _m_bRes = xSNDMSG_API(BOOL, _m_pstaParent->hGetHandle(), SB_SETICON, iIndex, hIcon/*NULL*/);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetWidth (Sets the width for a part in a status bar)
BOOL CxStatusBar::CXItems::bSetWidth(INT iIndex, INT iWidth)  {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????
    /*DEBUG*///iWidth    - n/a
    xCHECK_RET(iIndex >= (INT)CXItem::m_veciWidths.size(), FALSE);

    CXItem::m_veciWidths.at(iIndex) = iWidth;

    _m_bRes = xSNDMSG_API(BOOL, _m_pstaParent->hGetHandle(), SB_SETPARTS, CXItem::m_veciWidths.size(), &CXItem::m_veciWidths.at(0));

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: iGetWidth (Gets the width for a part in a status bar)
INT CxStatusBar::CXItems::iGetWidth(INT iIndex)  {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????

    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);

    INT iRes = 0;

    RECT rcRect = {0};

    _m_bRes = bGetRect(iIndex, &rcRect);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    iRes = rcRect.right - rcRect.left;

    return iRes;
}
//---------------------------------------------------------------------------
//DONE: bGetRect (Retrieves the bounding rectangle of a part in a status window)
BOOL CxStatusBar::CXItems::bGetRect(INT iIndex, RECT *prcRect)  {
    /*DEBUG*/xASSERT_RET(NULL != _m_pstaParent, FALSE);
    /*DEBUG*///iIndex    - n/a  ???????
    /*DEBUG*/xASSERT_RET(NULL != prcRect, FALSE);

    _m_bRes = xSNDMSG_API(BOOL, _m_pstaParent->hGetHandle(), SB_GETRECT, iIndex, prcRect);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    return TRUE;
}
//---------------------------------------------------------------------------