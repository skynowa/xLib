/****************************************************************************
* Class name:  CxProgressBar
* Description: индикатор выполнения
* File name:   CxProgressBar.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.07.2009 11:05:22
*
*****************************************************************************/


#include <xLib/Gui/CxProgressBar.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxProgressBar
CxProgressBar::CxProgressBar() {
    LOG();

    //-------------------------------------
    //переопределяем параметры окна
    _m_sClassName     = xCXPROGRESSBAR_CONTROL_CLASS;
    _m_ulStyle        = xCXPROGRESSBAR_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXPROGRESSBAR_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXPROGRESSBAR_DEFAULT_WIDTH;
    _m_iHeight        = xCXPROGRESSBAR_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;
    
    //TODO: _bInitCommonControls
    _bInitCommonControls(ICC_PROGRESS_CLASS);

    //-------------------------------------
    //внутр
    _m_vsViewStyle    = vsDefault;
}
//---------------------------------------------------------------------------
//TODO: - ~CxProgressBar
CxProgressBar::~CxProgressBar() {
    LOG();
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxProgressBar::bCreateRes(INT iID, CxWindow *pwndParent) {
    /*DEBUG*/xASSERT_RET(0 < iID,         FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

    _m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName, CxResources::sGetText(iID), 
                                CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID), 
                                CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID), 
                                CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
                                this);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetViewStyle ()
BOOL CxProgressBar::bSetViewStyle(EViewStyle vsViewStyle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = m_stStyle.bModify(_m_vsViewStyle, vsViewStyle);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    _m_vsViewStyle = vsViewStyle;

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: сообщения
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - uiGetPos (Retrieves the current position of the progress bar)
#if (xWINVER >= xWIN32_2K)
UINT CxProgressBar::uiGetPos() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    return xSNDMSG(UINT, PBM_GETPOS, 0, 0);
    /*DEBUG*/// n/a 
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - PBM_SETPOS (Sets the current position for a progress bar and redraws the bar to reflect the new position)
#if (xWINVER >= xWIN32_2K)
BOOL CxProgressBar::bSetPos(UINT uiPos) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

     xSNDMSG(UINT, PBM_SETPOS, uiPos, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetDeltaPos    (Advances the current position of a progress bar by a specified increment and redraws the bar to reflect the new position)
#if (xWINVER >= xWIN32_2K)  
BOOL CxProgressBar::bSetDeltaPos(INT iDelta) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    INT iRes = - 1;

    iRes = xSNDMSG(INT, PBM_DELTAPOS, iDelta, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - stGetState (Gets the state of the progress bar)
#if (xWINVER >= xWIN32_VISTA)
CxProgressBar::EState CxProgressBar::stGetState() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, stError);

    return xSNDMSG(EState, PBM_GETSTATE, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - bSetState    (Sets the state of the progress bar)
#if (xWINVER >= xWIN32_VISTA)
BOOL CxProgressBar::bSetState(EState stState) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(EState, PBM_SETSTATE, stState, 0);
    /*DEBUG*/// n/a 

    return TRUE;
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - crGetBarColor (Gets the color of the progress bar)
#if (xWINVER >= xWIN32_VISTA)  
COLORREF CxProgressBar::crGetBarColor() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    return xSNDMSG(INT, PBM_GETBARCOLOR, 0, 0);
    /*DEBUG*/// n/a
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - bSetBarColor (Sets the color of the progress indicator bar in the progress bar control)
#if (xWINVER >= xWIN32_2K)
BOOL CxProgressBar::bSetBarColor(COLORREF crColor /*= CLR_DEFAULT*/) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(COLORREF, PBM_SETBARCOLOR, 0, crColor);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - crGetBkColor (Gets the background color of the progress bar)
#if (xWINVER >= xWIN32_VISTA)  
COLORREF CxProgressBar::crGetBkColor() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    return xSNDMSG(COLORREF, PBM_GETBKCOLOR, 0, 0);
    /*DEBUG*/// n/a 
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - bSetBkColor (Sets the background color in the progress bar)
#if (xWINVER >= xWIN32_2K)
BOOL CxProgressBar::bSetBkColor(COLORREF crColor /*= CLR_DEFAULT*/) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(COLORREF, PBM_SETBKCOLOR, 0, crColor);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bGetRange (Retrieves information about the current high and low limits of a given progress bar control)
#if (xWINVER >= xWIN32_2K)
BOOL CxProgressBar::bGetRange(INT *piMin, INT *piMax) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    PBRANGE pbrRange = {0};

    xSNDMSG(INT, PBM_GETRANGE, TRUE, &pbrRange);
    /*DEBUG*/ 

    if (NULL != piMin) {
        *piMin = pbrRange.iLow;
    }

    if (NULL != piMax) {
        *piMax = pbrRange.iHigh;
    }

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetRange    (Sets the minimum and maximum values for a progress bar and redraws the bar to reflect the new range)
#if (xWINVER >= xWIN32_2K)
BOOL CxProgressBar::bSetRange(USHORT usMin, USHORT usMax) {    //FIX: USHORT usMin, USHORT usMax
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(UINT, PBM_SETRANGE, 0, MAKELPARAM(usMin, usMax));
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetRange32 (Sets the range of a progress bar control to a 32-bit value)
#if (xWINVER >= xWIN32_2K)
BOOL CxProgressBar::bSetRange32(INT iMin, INT iMax) {  //FIX: INT iMin, INT iMax
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE); 

    xSNDMSG(INT, PBM_SETRANGE32, iMin, iMax);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - uiGetStep (Retrieves the step increment from a progress bar) (??? n/i ???)
#if (xWINVER >= xWIN32_VISTA)
UINT CxProgressBar::uiGetStep() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    return xSNDMSG(UINT, PBM_GETSTEP, 0, 0);
    /*DEBUG*/// n/a 
}
#endif //xWIN32_VISTA
//---------------------------------------------------------------------------
//TODO: - bSetStep (Specifies the step increment for a progress bar)
#if (xWINVER >= xWIN32_2K)
BOOL CxProgressBar::bSetStep(UINT uiStep) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(UINT, PBM_SETSTEP, uiStep, 0);
    /*DEBUG*/// n/a 

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bStepIt (Advances the current position for a progress bar by the step increment and redraws the bar to reflect the new position)
#if (xWINVER >= xWIN32_2K)
BOOL CxProgressBar::bStepIt() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    xSNDMSG(UINT, PBM_STEPIT, 0, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
#endif //xWIN32_2K
//---------------------------------------------------------------------------
//TODO: - bSetMarquee (Sets the progress bar to marquee mode)
#if (xWINVER >= xWIN32_S03)
BOOL CxProgressBar::bSetMarquee(BOOL bIsOn, ULONG ulMilliSeconds) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = xSNDMSG(BOOL, PBM_SETMARQUEE, bIsOn, ulMilliSeconds);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    return TRUE;
}
#endif //xWIN32_S03
//---------------------------------------------------------------------------




//////---------------------------------------------------------------------------
////INT CxProgressBar::GetMaxValue() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    return pSendMessage(PBM_GETRANGE, (WPARAM)0, (LPARAM)0);
////}
//////---------------------------------------------------------------------------
////INT CxProgressBar::GetMinValue() {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////
////    return pSendMessage(PBM_GETRANGE, (WPARAM)1, (LPARAM)0);
////}
//////---------------------------------------------------------------------------


