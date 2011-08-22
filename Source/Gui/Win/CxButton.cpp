/****************************************************************************
* Class name:  CxButton
* Description: ������ � �������
* File name:   CxButton.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.07.2009 13:11:14
*
*****************************************************************************/


#include <xLib/Gui/CxButton.h>

#include <xLib/GUI/CxApplication.h>
#include <xLib/GUI/CxWindowImpl.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxButton
CxButton::CxButton() {
    LOG();

    //-------------------------------------
    //�������������� ��������� ����
    _m_sClassName     = xCXBUTTON_CONTROL_CLASS;
    _m_ulStyle        = xCXBUTTON_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXBUTTON_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXBUTTON_DEFAULT_WIDTH;
    _m_iHeight        = xCXBUTTON_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;

    //-------------------------------------
    //�����.
    _m_vsViewStyle    = vsText;
}
//---------------------------------------------------------------------------
//DONE: ~CxButton
/*virtual*/
CxButton::~CxButton() {
    LOG();

    /*DEBUG*/xASSERT_DO(NULL != _m_pwndParent, return);
    _m_bRes = reinterpret_cast<CxWindowImpl *>(_m_pwndParent)->m_vecpContainer.bRemove(this);
    xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bCreate
BOOL CxButton::bCreateRes(INT iID, CxWindow *pwndParent) {
    /*DEBUG*/xASSERT_RET(0 < iID,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

    _m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName,
                                CxResources::sGetText  (iID),
                                CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID),
                                CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID),
                                CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
                                this);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //////-------------------------------------
    //////�������������� ���� ������
    ////_m_pwndParent = pwndParent;

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    ���������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bSetStyle (Sets the style of a button)
////BOOL CxButton::bSetStyle(DWORD ulStyle, BOOL bRedraw) {
////    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
////    /*DEBUG*///ulStyle
////    /*DEBUG*///bRedraw
////
////    /*static_cast<BOOL>*/( Button_SetStyle(_m_hWnd, ulStyle, bRedraw) );
////    /*DEBUG*///n/a
////
////    return TRUE;
////}
//---------------------------------------------------------------------------
//TODO: - bSetViewStyle ()
BOOL CxButton::bSetViewStyle(EViewStyle vsViewStyle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = m_stStyle.bModify(_m_vsViewStyle, vsViewStyle);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_vsViewStyle = vsViewStyle;

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetImage
BOOL CxButton::bSetImage(EImageType itImageType, HANDLE hImage) {
    HANDLE hRes = NULL;

    //hRes = (HANDLE)( pSendMessage(BM_SETIMAGE, (WPARAM)itImageType, (LPARAM)hImage) );
    ////*DEBUG*/xASSERT_RET(NULL != hRes, FALSE);

    (HANDLE)pSendMessage(BM_SETIMAGE, static_cast<WPARAM>(itImageType), reinterpret_cast<LPARAM>(/*(HICON)*/hImage));
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------









/****************************************************************************
*    �������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: vSet_OnClick ()
VOID CxButton::vSet_OnClick(SClosureT<VOID(CxButton *pbtnSender)> vCallback) {
    _m_vCallback_OnClick = vCallback;
}
//---------------------------------------------------------------------------
//DONE: _vHandler_OnClick ()
VOID CxButton::_vHandler_OnClick(CxButton *pbtnSender)    {
    xCHECK_DO(NULL == _m_vCallback_OnClick, return);

    _m_vCallback_OnClick(pbtnSender);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//DONE: vSet_OnDbClick ()
VOID CxButton::vSet_OnDbClick(SClosureT<VOID(CxButton *pbtnSender)> vCallback) {
    _m_vCallback_OnDbClick = vCallback;
}
//---------------------------------------------------------------------------
//DONE: _vHandler_OnClick ()
VOID CxButton::_vHandler_OnDbClick(CxButton *pbtnSender) {
    xCHECK_DO(NULL == _m_vCallback_OnDbClick, return);

    _m_vCallback_OnDbClick(pbtnSender);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//DONE: vSet_OnKillFocus ()
VOID CxButton::vSet_OnKillFocus(SClosureT<VOID(CxButton *pbtnSender)> vCallback) {
    _m_vCallback_OnKillFocus = vCallback;
}
//---------------------------------------------------------------------------
//DONE: _vHandler_OnKillFocus()
VOID CxButton::_vHandler_OnKillFocus(CxButton *pbtnSender)    {
    xCHECK_DO(NULL == _m_vCallback_OnKillFocus, return);

    _m_vCallback_OnKillFocus(pbtnSender);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//DONE: vSet_OnSetFocus ()
VOID CxButton::vSet_OnSetFocus(SClosureT<VOID(CxButton *pbtnSender)> vCallback) {
    _m_vCallback_OnSetFocus = vCallback;
}
//---------------------------------------------------------------------------
//DONE: _vHandler_OnSetFocus ()
VOID CxButton::_vHandler_OnSetFocus(CxButton *pbtnSender)    {
    xCHECK_DO(NULL == _m_vCallback_OnSetFocus, return);

    _m_vCallback_OnSetFocus(pbtnSender);
}
//---------------------------------------------------------------------------
