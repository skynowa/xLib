#include "CMyCDlg.h"
#include "resource.h"

#include <XLib/GUI/CXApplication.h>
//---------------------------------------------------------------------------
CMyCDlg::CMyCDlg() :
	CXDialog() 
{

}
//---------------------------------------------------------------------------
CMyCDlg::CMyCDlg(SHORT TemplID, SHORT IconID, HWND hParent) :
	CXDialog(TemplID, IconID, hParent)
{
	LOG();
}
//---------------------------------------------------------------------------
CMyCDlg::~CMyCDlg() {
	LOG();
}
//---------------------------------------------------------------------------
X_BEGIN_MSG_MAP(CMyCDlg)
	X_CMD(IDC_bthCXButton,  OnCXButtonClick)
	X_CMD(IDC_BUTTON_ABOUT, OnButtonClick)
	X_CMD(IDC_BUTTON_MODAL, OnButtonClick);
	X_CMD(IDOK,             OnOK)
	X_CMD(IDCANCEL,         OnCancel)
X_END_MSG_MAP(CXDialog)
//---------------------------------------------------------------------------
INT CMyCDlg::OnInitial(WPARAM wParam, LPARAM lParam) {	/*virtual*/
	LOG();

	m_btnCXButton.bCreateRes(IDC_bthCXButton, hGetHandle());
	
	bMoveCenter();

	return FALSE;
}
//---------------------------------------------------------------------------
VOID CMyCDlg::OnDestroy(WPARAM wParam, LPARAM lParam) {    /*virtual*/
	//LOG();

	////::EnableWindow(_m_hParentWnd, TRUE);
	////::SetActiveWindow(_m_hParentWnd);
	////::UpdateWindow(_m_hParentWnd);
	////::DestroyWindow(_m_hWnd);

	CXApplication::vTerminate();
}
//---------------------------------------------------------------------------
VOID CMyCDlg::OnButtonClick(WORD id, LPARAM lParam) {
	if (IDC_BUTTON_MODAL == id)	{
		////CMyCDlg uldlgAbout(IDD_DIALOG_MAIN, m_IconID, _m_hWnd);
		////uldlgAbout.CreateModal();
	}

	//if (IDC_BUTTON_ABOUT == id) {
	//	m_pMyCDlg = new CMyCDlg;
	//	
	//	HWND hWnd = m_pMyCDlg->Create(IDD_ABOUTBOX, m_IconID, _m_hWnd);
	//	
	//	::ShowWindow(hWnd, SW_SHOW);
	//	::UpdateWindow(hWnd);
	//}
}
//---------------------------------------------------------------------------
VOID CMyCDlg::OnCXButtonClick(WORD id, LPARAM lParam) {
	LOG();
}
//---------------------------------------------------------------------------
VOID CMyCDlg::OnCancel(WORD id, LPARAM lParam) {
	LOG();

	::PostMessage(_m_hWnd, WM_DESTROY, 0, 0);
}
//---------------------------------------------------------------------------
VOID CMyCDlg::OnOK(WORD id, LPARAM lParam) {
	LOG();

	//::PostMessage(_m_hWnd, WM_CLOSE, NULL, NULL);
	::PostMessage(_m_hWnd, WM_DESTROY, 0, 0);
}
//---------------------------------------------------------------------------