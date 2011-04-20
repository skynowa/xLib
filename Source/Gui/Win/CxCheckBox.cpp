/****************************************************************************
* Class name:  CxCheckBox
* Description: 
* File name:   CxCheckBox.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     24.07.2009 11:47:59
*
*****************************************************************************/


#include <xLib/Gui/CxCheckBox.h>

#include <xLib/GUI/CxWindowImpl.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCheckBox
CxCheckBox::CxCheckBox() {
    LOG();
    
    //-------------------------------------
    //переопределяем параметры окна
    _m_sClassName     = xCXCHECKBOX_CONTROL_CLASS;
    _m_ulStyle        = xCXCHECKBOX_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXCHECKBOX_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXCHECKBOX_DEFAULT_WIDTH;
    _m_iHeight        = xCXCHECKBOX_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;
}
//---------------------------------------------------------------------------
//DONE: ~CxCheckBox
CxCheckBox::~CxCheckBox() {
    LOG();
    
    /*DEBUG*/xASSERT_DO(NULL != _m_pwndParent, return);
    _m_bRes = reinterpret_cast<CxWindowImpl *>(_m_pwndParent)->m_vecpContainer.bRemove(this);
    xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxCheckBox::bCreateRes(INT iID, CxWindow *pwndParent) {
    /*DEBUG*/xASSERT_RET(0 < iID,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

    _m_bRes = CxWindow::bCreate(iID, pwndParent, _m_sClassName, CxResources::sGetText  (iID), 
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
CxCheckBox::ECheckState CxCheckBox::csGetState() {
    /*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), csUknown);

    ECheckState csRes = csUknown;

    csRes = static_cast<ECheckState>( pSendMessage(BM_GETCHECK, 0, 0) );
    /*DEBUG*/xASSERT_RET(csRes == csChecked || csRes == csGrayed || csRes == csUnchecked, csUknown);

    return csRes;    
} 
//---------------------------------------------------------------------------
//DONE: bSetState (Sets the check state of a radio button or check box)
BOOL CxCheckBox::bSetState(CxCheckBox::ECheckState csCheckState) {
    /*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
    /*DEBUG*///bstState

    ////xASSERT_RET(TRUE == bIsStyleExists(BS_AUTOCHECKBOX), TRUE);

    ////xCHECK_RET((TRUE == bIsStyleExists(BS_AUTOCHECKBOX)) && (csGrayed == csCheckState), TRUE);


    pSendMessage(BM_SETCHECK, csCheckState, 0);
    /*DEBUG*/// n/a
    
    ////Button_SetCheck(_m_hWnd, csCheckState);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetAllowGrayed ()
BOOL CxCheckBox::bSetAllowGrayed(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
    /*DEBUG*///bFlag - n/a
    
    if (FALSE == bFlag) {
        m_stStyle.bModify(BS_AUTO3STATE, BS_AUTOCHECKBOX);
    } else {
        m_stStyle.bModify(BS_AUTOCHECKBOX, BS_AUTO3STATE); 
    }

    return TRUE;
}
//---------------------------------------------------------------------------