#include "resource.h"
#include "CMyApp.h"
//---------------------------------------------------------------------------
/*virtual */INT CMyApp::InitInstance() {
	m_pMainDlg = new CMyCDlg;
	HWND hWnd = m_pMainDlg->Create(IDD_DIALOG_MAIN, 0, NULL);
	if (!hWnd) {
		return FALSE;
	}

	::ShowWindow(hWnd, SW_SHOW);
	::UpdateWindow(hWnd);

	return TRUE;		
}
//---------------------------------------------------------------------------
/*virtual */INT CMyApp::Run() {
	MSG msg = {0};

	while (::IsWindow(m_pMainDlg->m_hWnd) && ::GetMessage(&msg, NULL, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return (INT)msg.wParam;
}
//---------------------------------------------------------------------------