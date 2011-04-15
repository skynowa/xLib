/****************************************************************************
* Class name:  CxStyle
* Description: атрибуты файла
* File name:   CxStyle.cpp
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     06.04.2010 13:37:54
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Gui/CxStyle.h>



/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxStyle (comment)
CxStyle::CxStyle() : 
	_m_hWnd(NULL)
{
	/*DEBUG*/xASSERT_DO(NULL == _m_hWnd, return);
}
//---------------------------------------------------------------------------
//TODO: - ~CxStyle (comment)
CxStyle::~CxStyle() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - ~CxStyle (comment)
BOOL CxStyle::bSetOwner(HWND hWnd) {
	/*DEBUG*/xASSERT_RET(NULL != hWnd, FALSE);

	_m_hWnd = hWnd;
	
	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + atGet
/*static*/
CxStyle::TStyle CxStyle::stGet() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	return static_cast<TStyle>(::GetWindowLong(_m_hWnd, GWL_STYLE));
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + bSet
/*static*/
BOOL CxStyle::bSet(TStyle stValue) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stValue

	::SetWindowLong(_m_hWnd, GWL_STYLE, static_cast<ULONG>(stValue));
	/*DEBUG*/

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bAdd
/*static*/
BOOL CxStyle::bAdd(TStyle stValue) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stValue

	return bModify(static_cast<TStyle>(0), stValue);
}
//---------------------------------------------------------------------------
//TODO: + bRemove ()
/*static*/
BOOL CxStyle::bRemove(TStyle stValue)  {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stValue

	return bModify(stValue, static_cast<TStyle>(0));
}
//---------------------------------------------------------------------------
//TODO: + bModify
/*static*/
BOOL CxStyle::bModify(TStyle stRemoveValue, TStyle stAddValue) {	
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stRemoveValue
	/*DEBUG*/// stAddValue

	BOOL bRes = FALSE;
	
	//First we get the current window Attr.
	TStyle stValue = stGet();

	//Change bits.
	////stValue &= ~ulRemoveValue;
	////stValue |= ulAddValue;
	stValue = static_cast<TStyle>( static_cast<ULONG>(stValue) & ~stRemoveValue );
	stValue = static_cast<TStyle>( static_cast<ULONG>(stValue) |  stAddValue    );

	//Change the Attr.
	bSet(stValue);
	/*DEBUG*/
	
	bRes = ::InvalidateRect(_m_hWnd, NULL, TRUE);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
	
	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bIsExists ()
/*static*/
BOOL CxStyle::bIsExists(TStyle stValue) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stValue

	//////ULONG _ulAttr = 0xffffffff;
	//////	
	//////_m_bRes = bGetAttr(&_ulAttr);
	///////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	//////if (_ulAttr & ulAttr) {
	//////	return TRUE;
	//////}

	////////////////////if ((ulGetAttr() & BS_TYPEMASK) == stValue) {
	////////////////////	return TRUE;
	////////////////////}

	/*ULONG _ulAttr = ulGetAttr();
	if (_ulAttr & ulAttr) {
		return TRUE;
	}*/
	
	
	TStyle _atValue /*= faInvalid*/;
	
	_atValue = stGet();
	xCHECK_RET(_atValue & stValue, TRUE);

	return FALSE;
}
//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
//TODO: + atGet
/*static*/
CxStyle::TStyle CxStyle::stGetEx() {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	return static_cast<TStyle>(::GetWindowLong(_m_hWnd, GWL_EXSTYLE));
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + bSet
/*static*/
BOOL CxStyle::bSetEx(TStyle stValue) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stValue

	::SetWindowLong(_m_hWnd, GWL_EXSTYLE, static_cast<ULONG>(stValue));
	/*DEBUG*/

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bAdd
/*static*/
BOOL CxStyle::bAddEx(TStyle stValue) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stValue

	return bModifyEx(static_cast<TStyle>(0), stValue);
}
//---------------------------------------------------------------------------
//TODO: + bRemove ()
/*static*/
BOOL CxStyle::bRemoveEx(TStyle stValue)  {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stValue

	return bModifyEx(stValue, static_cast<TStyle>(0));
}
//---------------------------------------------------------------------------
//TODO: + bModify
/*static*/
BOOL CxStyle::bModifyEx(TStyle stRemoveValue, TStyle stAddValue) {	
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stRemoveValue
	/*DEBUG*/// stAddValue

	BOOL bRes = FALSE;

	//First we get the current window Attr.
	TStyle stValue = stGetEx();

	//Change bits.
	////stValue &= ~ulRemoveValue;
	////stValue |= ulAddValue;
	stValue = static_cast<TStyle>( static_cast<ULONG>(stValue) & ~stRemoveValue );
	stValue = static_cast<TStyle>( static_cast<ULONG>(stValue) |  stAddValue    );

	//Change the Attr.
	bSetEx(stValue);
	/*DEBUG*/

	bRes = ::InvalidateRect(_m_hWnd, NULL, TRUE);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bIsExists ()
/*static*/
BOOL CxStyle::bIsExistsEx(TStyle stValue) {
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);
	/*DEBUG*/// stValue

	//////ULONG _ulAttr = 0xffffffff;
	//////	
	//////_m_bRes = bGetAttr(&_ulAttr);
	///////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	//////if (_ulAttr & ulAttr) {
	//////	return TRUE;
	//////}

	////////////////////if ((ulGetAttr() & BS_TYPEMASK) == stValue) {
	////////////////////	return TRUE;
	////////////////////}

	/*ULONG _ulAttr = ulGetAttr();
	if (_ulAttr & ulAttr) {
	return TRUE;
	}*/


	TStyle _atValue /*= faInvalid*/;

	_atValue = stGetEx();
	xCHECK_RET(_atValue & stValue, TRUE);

	return FALSE;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    Private methods                                                          
*                                                                            
*****************************************************************************/









/****************************************************************************
*	Стили
*
*****************************************************************************/

//////---------------------------------------------------------------------------
//////TODO: + bGetStyle
////ULONG CxWindow::ulGetStyle() {
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	return static_cast<ULONG>( liGetWindowLong(GWL_STYLE) );
////	}
//////---------------------------------------------------------------------------
//////TODO: + bGetStyleEx
////ULONG CxWindow::ulGetStyleEx() {
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	return static_cast<ULONG>( liGetWindowLong(GWL_EXSTYLE));
////	}
//////---------------------------------------------------------------------------
//////TODO: + bAddStyle
////BOOL CxWindow::bAddStyle(ULONG ulStyle) {
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	return bModifyStyle(0, ulStyle);
////	}
//////---------------------------------------------------------------------------
//////TODO: + bAddStyleEx
////BOOL CxWindow::bAddStyleEx(ULONG ulStyleEx) {
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	return bModifyStyleEx(0, ulStyleEx);
////	}
//////---------------------------------------------------------------------------
//////TODO: + bRemoveStyle ()
////BOOL CxWindow::bRemoveStyle(ULONG ulStyle)  {
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	return bModifyStyleEx(ulStyle, 0);
////	}
//////---------------------------------------------------------------------------
//////TODO: + bRemoveStyleEx ()
////BOOL CxWindow::bRemoveStyleEx(ULONG ulStyleEx)  {
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	return bModifyStyleEx(ulStyleEx, 0);
////	}
//////---------------------------------------------------------------------------
//////TODO: + bModifyStyle
////BOOL CxWindow::bModifyStyle(ULONG ulRemoveStyle, ULONG ulAddStyle) {	
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	//First we get the current window style.
////	ULONG ulStyle = ulGetStyle();
////
////	//Change bits.
////	ulStyle &= ~ulRemoveStyle;
////	ulStyle |= ulAddStyle;
////
////	//Change the style.
////	liSetWindowLong(GWL_STYLE, ulStyle);
////	/*DEBUG*/
////
////	////_m_bRes = bSetPos(0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
////	/////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
////
////	_m_bRes = bInvalidateRect(NULL, TRUE);
////	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
////
////	return TRUE;
////
////	////liSetWindowLong(GWL_STYLE,
////	////	(liGetWindowLong(GWL_STYLE)&(~ulRemoveStyle))|ulAddStyle);
////
////
////	//SetWindowLong(Handle, GWL_STYLE, GetWindowLong(Handle, GWL_STYLE) xor WS_BORDER);
////	}
//////---------------------------------------------------------------------------
//////TODO: + bModifyStyleEx
////BOOL CxWindow::bModifyStyleEx(ULONG ulRemoveStyleEx, ULONG ulAddStyleEx) {	
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	//First we get the current window extended style.
////	ULONG ulStyleEx = ulGetStyleEx();
////
////	//Change bits.
////	ulStyleEx &= ~ulRemoveStyleEx;
////	ulStyleEx |= ulAddStyleEx;
////
////	//Change the extended style.
////	liSetWindowLong(GWL_EXSTYLE, ulStyleEx);
////	/*DEBUG*/
////
////	////_m_bRes = bSetPos(0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
////	/////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
////
////	_m_bRes = bInvalidateRect(NULL, TRUE);
////	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
////
////	return TRUE;
////	}
//////---------------------------------------------------------------------------
//////TODO: - bIsStyleExists ()
////BOOL CxWindow::bIsStyleExists(ULONG ulStyle) {
////	/*DEBUG*/xASSERT_RET(FALSE != bIsWindow(), FALSE);
////
////	//////ULONG _ulStyle = 0xffffffff;
////	//////	
////	//////_m_bRes = bGetStyle(&_ulStyle);
////	///////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
////
////	//////if (_ulStyle & ulStyle) {
////	//////	return TRUE;
////	//////}
////
////	if ((ulGetStyle() & BS_TYPEMASK) == ulStyle) {
////		return TRUE;
////	}
////
////	/*ULONG _ulStyle = ulGetStyle();
////	if (_ulStyle & ulStyle) {
////	    return TRUE;
////	}*/
////
////	return FALSE;
////}
//////---------------------------------------------------------------------------