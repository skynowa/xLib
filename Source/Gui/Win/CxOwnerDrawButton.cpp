/****************************************************************************
* Class name:  CxOwnerDrawButton
* Description: 
* File name:   CxOwnerDrawButton.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.07.2009 21:38:38
*
*****************************************************************************/



#include <xLib/Gui/CxOwnerDrawButton.h>

#include <xLib/GUI/CxWindowImpl.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxOwnerDrawButton
CxOwnerDrawButton::CxOwnerDrawButton() {
	/*DEBUG*/

	LOG();

	//-------------------------------------
	//переопределяем параметры окна
	_m_sClassName     = xCXOWNERDRAWBUTTON_CONTROL_CLASS;
	_m_ulStyle        = xCXOWNERDRAWBUTTON_DEFAULT_WINDOW_STYLE;
	_m_ulStyleEx      = xCXOWNERDRAWBUTTON_DEFAULT_WINDOW_STYLE_EX;

	_m_iLeft          = 0;
	_m_iTop           = 0;
	_m_iWidth         = xCXOWNERDRAWBUTTON_DEFAULT_WIDTH;
	_m_iHeight        = xCXOWNERDRAWBUTTON_DEFAULT_HEIGHT;

	_m_bIsControl     = TRUE;
}
//---------------------------------------------------------------------------
//DONE: ~CxOwnerDrawButton
/*virtual*/
CxOwnerDrawButton::~CxOwnerDrawButton() {
	LOG();
	
	/*DEBUG*/xASSERT_DO(NULL != _m_pwndParent, return);
	_m_bRes = reinterpret_cast<CxWindowImpl *>(_m_pwndParent)->m_vecpContainer.bRemove(this);
	xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bCreateRes
BOOL CxOwnerDrawButton::bCreateRes(INT iID, CxWindow *pwndParent) {
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
*	сообщения
*
*****************************************************************************/
