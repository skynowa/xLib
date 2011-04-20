/****************************************************************************
* Class name:  CxPicture
* Description: картинка
* File name:   CxPicture.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     20.07.2010 20:40:41
*
*****************************************************************************/



#include <xLib/Gui/CxPicture.h>

#include <xLib/GUI/CxWindowImpl.h>

//---------------------------------------------------------------------------
//TODO: - CxPicture
CxPicture::CxPicture() {
    LOG();

    //-------------------------------------
    //переопределяем параметры окна
    _m_sClassName     = xCXPICTURE_CONTROL_CLASS;
    _m_ulStyle        = xCXPICTURE_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx      = xCXPICTURE_DEFAULT_WINDOW_STYLE_EX;

    _m_iLeft          = 0;
    _m_iTop           = 0;
    _m_iWidth         = xCXPICTURE_DEFAULT_WIDTH; 
    _m_iHeight        = xCXPICTURE_DEFAULT_HEIGHT;

    _m_bIsControl     = TRUE;

    //-------------------------------------
    //внутр.
    _m_vsViewStyle    = vsBitmap/*vsUknown*/;
}
//---------------------------------------------------------------------------
//TODO: - ~CxPicture
CxPicture::~CxPicture() {
    LOG();
    
    /*DEBUG*/xASSERT_DO(NULL != _m_pwndParent, return);
    _m_bRes = reinterpret_cast<CxWindowImpl *>(_m_pwndParent)->m_vecpContainer.bRemove(this);
    xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxPicture::bCreateRes(INT iID, CxWindow *pwndParent) {
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
*    public: сообщения
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bSetViewStyle (установка стиля)
BOOL CxPicture::bSetViewStyle(EViewStyle vsViewStyle) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

    _m_bRes = m_stStyle.bModify(_m_vsViewStyle, vsViewStyle);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE); 

    _m_vsViewStyle = vsViewStyle;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetImage (установка изображения)
BOOL CxPicture::bSetImage(EImageType itImageType, HANDLE hImage) {
    /*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
        
    xSNDMSG(HANDLE, STM_SETIMAGE, itImageType, hImage);
    /*DEBUG*/// n/a

    return TRUE;
}
//---------------------------------------------------------------------------