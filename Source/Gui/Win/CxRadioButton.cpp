/****************************************************************************
* Class name:  CxRadioButton
* Description: 
* File name:   CxRadioButton.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.07.2009 21:38:38
*
*****************************************************************************/



#include <xLib/Gui/CxRadioButton.h>

#include <xLib/GUI/CxWindowImpl.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxRadioButton
CxRadioButton::CxRadioButton() {
    LOG();

    //-------------------------------------
    //переопределяем параметры окна
    _m_sClassName     = xCXRADIOBUTTON_CONTROL_CLASS;
    _m_ulStyle        = xCXRADIOBUTTON_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXRADIOBUTTON_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXRADIOBUTTON_DEFAULT_WIDTH;
    _m_iHeight        = xCXRADIOBUTTON_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;
}
//---------------------------------------------------------------------------
//DONE: ~CxRadioButton
/*virtual*/
CxRadioButton::~CxRadioButton() {
    LOG();
    
    /*DEBUG*/xASSERT_DO(NULL != _m_pwndParent, return);
    _m_bRes = reinterpret_cast<CxWindowImpl *>(_m_pwndParent)->m_vecpContainer.bRemove(this);
    xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxRadioButton::bCreateRes(INT iID, CxWindow *pwndParent) {
    /*DEBUG*/xASSERT_RET(0 < iID,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

    _m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName, 
                                CxResources::sGetText  (iID), 
                                CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID), 
                                CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID), 
                                CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
                                this);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    сообщения
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: lpGetState (Gets the check state of a radio button or check box)
CxRadioButton::ECheckState CxRadioButton::bstGetState() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, csUknown);

    ECheckState csRes = csUknown;

    csRes = static_cast<ECheckState>( pSendMessage(BM_GETCHECK, 0, 0) );
    /*DEBUG*/xASSERT_RET(csRes == csChecked || csRes == csUnchecked, csUknown);

    return csRes;    
} 
//---------------------------------------------------------------------------
//DONE: bSetState (Sets the check state of a radio button or check box)
BOOL CxRadioButton::bSetState(CxRadioButton::ECheckState csCheckState) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///csCheckState

    pSendMessage(BM_SETCHECK, csCheckState, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------