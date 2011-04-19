/****************************************************************************
* Class name:  CXDialog
* Description: работа с окнами
* File name:   CXDialog.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.07.2009 13:10:17
*
*****************************************************************************/


#include <xLib/Gui/CXDialog.h>

#include <xLib/GUI/xCommon.h>
#include <xLib/GUI/CxApplication.h>
//---------------------------------------------------------------------------
CXDialog::CXDialog() :
	_m_siTemplID  (0),
	_m_siIconID   (0)
{
	_m_hParentWnd = NULL;
}
//---------------------------------------------------------------------------
CXDialog::CXDialog(SHORT TemplID, SHORT siIconID, HWND hParentWnd) : 
	_m_siTemplID(TemplID),
	_m_siIconID (siIconID)	
{
	_m_hParentWnd = hParentWnd;
}
//---------------------------------------------------------------------------
CXDialog::~CXDialog() {

}
//---------------------------------------------------------------------------
//TODO: Карта сообщений
xBEGIN_MSG_MAP(CXDialog)
	xMSG(WM_INITDIALOG, OnInitial);
	xMSG(WM_PAINT,      OnPaint);
	xMSG(WM_COMMAND,    OnCommand);
	xMSG(WM_NOTIFY,     OnNotify);
	xMSG(WM_SIZE,       OnSize);
	xMSG(WM_CLOSE,      OnClose);    
	xMSG(WM_DESTROY,    OnDestroy);  
xEND_MSG_MAP_NOPARENT
//---------------------------------------------------------------------------
INT CXDialog::CreateModal() {
	INT iRes = - 1;

	iRes = (INT)::DialogBoxParam(CxApplication::hGetInstance(), (LPCTSTR)_m_siTemplID, _m_hParentWnd, (DLGPROC)_s_pWndProc, LPARAM(this));
	/*DEBUG*/xASSERT_RET(- 1 != iRes, iRes);
	/*DEBUG*/xASSERT_RET(0   != iRes, iRes);

	return iRes;
}
//---------------------------------------------------------------------------
BOOL CXDialog::bCreate(SHORT TemplID, SHORT IconID, HWND hParent) {
	_m_siTemplID  = TemplID;
	_m_siIconID   = IconID;
	_m_hParentWnd = hParent;

	_m_hWnd = ::CreateDialogParam(CxApplication::hGetInstance(), (LPCTSTR)_m_siTemplID, _m_hParentWnd, (DLGPROC)_s_pWndProc, LPARAM(this));
	/*DEBUG*/xASSERT_RET(NULL != _m_hWnd, FALSE);

	if (0 != _m_siIconID) {
		pSendMessage(WM_SETICON, WPARAM(ICON_SMALL), (LPARAM)::LoadIcon(CxApplication::hGetInstance(), (LPCTSTR)_m_siIconID));
	}

	return TRUE;
}
//---------------------------------------------------------------------------
INT CXDialog::OnInitial(WPARAM wParam, LPARAM lParam) {		/*virtual*/
	return FALSE;
}
//---------------------------------------------------------------------------
VOID CXDialog::OnPaint(WPARAM wParam, LPARAM lParam) {		/*virtual*/ 

}
//---------------------------------------------------------------------------
VOID CXDialog::OnCommand(WPARAM wParam, LPARAM lParam) {	/*virtual*/ 

}
//---------------------------------------------------------------------------
VOID CXDialog::OnNotify(WPARAM wParam, LPARAM lParam) {		/*virtual*/ 

}
//---------------------------------------------------------------------------
VOID CXDialog::OnSize(WPARAM wParam, LPARAM lParam) {		/*virtual*/ 

}
//---------------------------------------------------------------------------
VOID CXDialog::OnClose(WPARAM wParam, LPARAM lParam) {		/*virtual*/ 

}
//---------------------------------------------------------------------------
VOID CXDialog::OnDestroy(WPARAM wParam, LPARAM lParam) {	/*virtual*/ 

}
//---------------------------------------------------------------------------