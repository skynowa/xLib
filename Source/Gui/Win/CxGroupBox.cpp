/****************************************************************************
* Class name:  CxGroupBox
* Description: 
* File name:   CxGroupBox.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.07.2009 21:10:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <XLib/Gui/CxGroupBox.h>

#include <XLib/GUI/CxWindowImpl.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxGroupBox
CxGroupBox::CxGroupBox() {
	LOG();

	//-------------------------------------
	//переопределяем параметры окна 
	_m_sClassName     = xCXGROUPBOX_CONTROL_CLASS;           
	_m_ulStyle        = xCXGROUPBOX_DEFAULT_WINDOW_STYLE;     
	_m_ulStyleEx      = xCXGROUPBOX_DEFAULT_WINDOW_STYLE_EX;

	_m_iLeft          = 0;
	_m_iTop           = 0;
	_m_iWidth         = xCXGROUPBOX_DEFAULT_WIDTH;     
	_m_iHeight        = xCXGROUPBOX_DEFAULT_HEIGHT;  

	_m_bIsControl     = TRUE;
}
//---------------------------------------------------------------------------
//TODO: - CxGroupBox
/*virtual*/
CxGroupBox::~CxGroupBox() {
	LOG();
	
	/*DEBUG*/xASSERT_DO(NULL != _m_pwndParent, return);
	_m_bRes = reinterpret_cast<CxWindowImpl *>(_m_pwndParent)->m_vecpContainer.bRemove(this);
	xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//TODO: + bCreateRes
BOOL CxGroupBox::bCreateRes(INT iID, CxWindow *pwndParent) {
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