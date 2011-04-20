/****************************************************************************
* Class name:  CxButtonBase
* Description: работа с кнопкой
* File name:   CxButtonBase.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.07.2009 13:11:14
*
*****************************************************************************/


#include <xLib/Gui/CxButtonBase.h>

#include <xLib/GUI/CxApplication.h>
#include <xLib/GUI/CxWindowImpl.h>


//---------------------------------------------------------------------------
//DONE: CxButtonBase
CxButtonBase::CxButtonBase() {
    LOG();


    //-------------------------------------
    //переопределяем параметры окна
    /*
    в производных классах
    */
}
//---------------------------------------------------------------------------
//DONE: ~CxButtonBase
/*virtual*/
CxButtonBase::~CxButtonBase() {
    LOG();
}
//---------------------------------------------------------------------------
//DONE: bCreate
////BOOL CxButtonBase::bCreateRes(INT iID, CxWindow *pwndParent) {
////    /*DEBUG*/xASSERT_RET(0 < iID,            FALSE);
////    /*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);
////
////    _m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName, 
////                                CxResources::sGetText  (iID), 
////                                CxResources::iGetLeft  (iID), CxResources::iGetTop     (iID), 
////                                CxResources::iGetWidth (iID), CxResources::iGetHeight  (iID), 
////                                CxResources::ulGetStyle(iID), CxResources::ulGetStyleEx(iID),
////                                this);
////    xCHECK_RET(FALSE == _m_bRes, FALSE);
////
////    //////-------------------------------------
////    //////переопределяем поля класса
////    ////_m_pwndParent = pwndParent;
////
////    return TRUE;
////}
//---------------------------------------------------------------------------



/****************************************************************************
*    сообщения
*
*****************************************************************************/


//---------------------------------------------------------------------------
//TODO: - bSetAlignment ()
BOOL CxButtonBase::bSetAlignment(ETextAligment taTextAligment) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE); 

    _m_bRes = m_stStyle.bAdd(taTextAligment);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetNotify ()
BOOL CxButtonBase::bSetNotify(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE); 

    if (TRUE == bFlag) {
        _m_bRes = m_stStyle.bAdd(BS_NOTIFY);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
    } else {
        _m_bRes = m_stStyle.bRemove(BS_NOTIFY);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetFlat ()
BOOL CxButtonBase::bSetFlat(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE); 

    if (TRUE == bFlag) {
        _m_bRes = m_stStyle.bAdd(BS_FLAT);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
    } else {
        _m_bRes = m_stStyle.bRemove(BS_FLAT);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetMultiLine ()
BOOL CxButtonBase::bSetMultiLine(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE); 

    if (TRUE == bFlag) {
        _m_bRes = m_stStyle.bAdd(BS_MULTILINE);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
    } else {
        _m_bRes = m_stStyle.bRemove(BS_MULTILINE);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClick ()
BOOL CxButtonBase::bClick() {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    ////_m_bRes = bSetActive();
    /////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    ////_m_bRes = bPostMessage(BM_CLICK, 0, 0);
    /////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    //GetParent()->PostMessage(WM_COMMAND, MAKELONG (GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
    ///_m_bRes = _m_pwndParent->bPostMessage(WM_COMMAND, (WPARAM)MAKELONG(_m_iID, BN_CLICKED), (LPARAM)_m_hWnd);
    /////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 


    ////_m_bRes = ::PostMessage(GetWindowOwner(_m_hWnd), WM_COMMAND, (WPARAM)MAKELONG(_m_iID, BN_CLICKED), (LPARAM)_m_hWnd);
    /////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    _m_bRes = _m_pwndParent->bPostMessage(WM_COMMAND, (WPARAM)MAKELONG(::GetDlgCtrlID(_m_hWnd)/*_m_iID*/, BN_CLICKED), (LPARAM)_m_hWnd);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    return TRUE;
}
//---------------------------------------------------------------------------











/****************************************************************************
*    события
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: vSet_OnClick ()
VOID CxButtonBase::vSet_OnClick(SClosureT<VOID(CxButtonBase *pbtnSender)> vCallback) {
    _m_vCallback_OnClick = vCallback;
}
//---------------------------------------------------------------------------
//DONE: _vHandler_OnClick ()
VOID CxButtonBase::_vHandler_OnClick(CxButtonBase *pbtnSender)    {
    xCHECK_DO(NULL == _m_vCallback_OnClick, return); 

    _m_vCallback_OnClick(pbtnSender);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//DONE: vSet_OnDbClick ()
VOID CxButtonBase::vSet_OnDbClick(SClosureT<VOID(CxButtonBase *pbtnSender)> vCallback) {
    _m_vCallback_OnDbClick = vCallback;
}
//---------------------------------------------------------------------------
//DONE: _vHandler_OnClick ()
VOID CxButtonBase::_vHandler_OnDbClick(CxButtonBase *pbtnSender) {
    xCHECK_DO(NULL == _m_vCallback_OnDbClick, return); 

    _m_vCallback_OnDbClick(pbtnSender);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//DONE: vSet_OnKillFocus ()
VOID CxButtonBase::vSet_OnKillFocus(SClosureT<VOID(CxButtonBase *pbtnSender)> vCallback) {
    _m_vCallback_OnKillFocus = vCallback;
}
//---------------------------------------------------------------------------
//DONE: _vHandler_OnKillFocus()
VOID CxButtonBase::_vHandler_OnKillFocus(CxButtonBase *pbtnSender)    {
    xCHECK_DO(NULL == _m_vCallback_OnKillFocus, return); 

    _m_vCallback_OnKillFocus(pbtnSender);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//DONE: vSet_OnSetFocus ()
VOID CxButtonBase::vSet_OnSetFocus(SClosureT<VOID(CxButtonBase *pbtnSender)> vCallback) {
    _m_vCallback_OnSetFocus = vCallback;
}
//---------------------------------------------------------------------------
//DONE: _vHandler_OnSetFocus ()
VOID CxButtonBase::_vHandler_OnSetFocus(CxButtonBase *pbtnSender)    {
    xCHECK_DO(NULL == _m_vCallback_OnSetFocus, return); 

    _m_vCallback_OnSetFocus(pbtnSender);
}
//---------------------------------------------------------------------------