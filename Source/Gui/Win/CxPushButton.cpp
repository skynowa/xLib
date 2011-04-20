/****************************************************************************
* Class name:  CxPushButton
* Description: 
* File name:   CxPushButton.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.07.2009 21:38:38
*
*****************************************************************************/



#include <xLib/Gui/CxPushButton.h>

#include <xLib/GUI/CxWindowImpl.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxPushButton
CxPushButton::CxPushButton(BOOL bRadioButtonLike) {
    LOG();

    //-------------------------------------
    //�������������� ��������� ����
    _m_sClassName     = xCXPUSHBUTTON_CONTROL_CLASS;
    _m_ulStyle        = (TRUE == bRadioButtonLike) ? xCXRADIOBUTTON_DEFAULT_WINDOW_STYLE | BS_PUSHLIKE : xCXPUSHBUTTON_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXPUSHBUTTON_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXPUSHBUTTON_DEFAULT_WIDTH;
    _m_iHeight        = xCXPUSHBUTTON_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;

    //-------------------------------------
    //�����.
    _m_vsViewStyle    = vsText;
}
//---------------------------------------------------------------------------
//DONE: ~CxPushButton
/*virtual*/
CxPushButton::~CxPushButton() {
    LOG();
    
    /*DEBUG*/xASSERT_DO(NULL != _m_pwndParent, return);
    _m_bRes = reinterpret_cast<CxWindowImpl *>(_m_pwndParent)->m_vecpContainer.bRemove(this);
    xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxPushButton::bCreateRes(INT iID, CxWindow *pwndParent) {
    /*DEBUG*/xASSERT_RET(0 < iID,            FALSE);
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


/****************************************************************************
*    public: ���������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bSetViewStyle ()
BOOL CxPushButton::bSetViewStyle(EViewStyle vsViewStyle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = m_stStyle.bModify(_m_vsViewStyle, vsViewStyle); 
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_vsViewStyle = vsViewStyle;

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetImage
BOOL CxPushButton::bSetImage(EImageType itImageType, HANDLE hImage) {
    HANDLE hRes = NULL;

    //hRes = (HANDLE)( pSendMessage(BM_SETIMAGE, (WPARAM)itImageType, (LPARAM)hImage) );
    ///*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    (HANDLE)pSendMessage(BM_SETIMAGE, static_cast<WPARAM>(itImageType), reinterpret_cast<LPARAM>(/*(HICON)*/hImage));
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: csGetState (Gets the check state of a radio button or check box)
CxPushButton::ECheckState CxPushButton::csGetState() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, csUknown);

    ECheckState bstRes = csUknown;

    bstRes = static_cast<ECheckState>( pSendMessage(BM_GETCHECK, 0, 0) );
    /*DEBUG*/xASSERT_RET(bstRes == csChecked || bstRes == csUnchecked, csUknown);

    return bstRes;    
} 
//---------------------------------------------------------------------------
//DONE: bSetState (Sets the check state of a radio button or check box)
BOOL CxPushButton::bSetState(CxPushButton::ECheckState csCheckState) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
    /*DEBUG*///csCheckState

    pSendMessage(BM_SETCHECK, csCheckState, 0);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------