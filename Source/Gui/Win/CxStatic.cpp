/****************************************************************************
* Class name:  CxStatic
* Description: работа с статическим полем
* File name:   CxStatic.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     24.07.2009 11:20:41
*
*****************************************************************************/



#include <xLib/Gui/CxStatic.h>

#include <xLib/GUI/CxWindowImpl.h>

//---------------------------------------------------------------------------
//TODO: - CxStatic
CxStatic::CxStatic() {
    LOG();

    //-------------------------------------
    //переопределяем параметры окна
    _m_sClassName     = xCXSTATIC_CONTROL_CLASS;
    _m_ulStyle        = xCXSTATIC_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXSTATIC_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXSTATIC_DEFAULT_WIDTH;
    _m_iHeight        = xCXSTATIC_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;
}
//---------------------------------------------------------------------------
//TODO: - ~CxStatic
CxStatic::~CxStatic() {
    LOG();
    
    /*DEBUG*/xASSERT_DO(NULL != _m_pwndParent, return);
    _m_bRes = reinterpret_cast<CxWindowImpl *>(_m_pwndParent)->m_vecpContainer.bRemove(this);
    xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxStatic::bCreateRes(INT iID, CxWindow *pwndParent) {
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