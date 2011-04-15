#include "CxThreadPool_GUI.h"
//---------------------------------------------------------------------------
#include "CWorkThread.h"
//---------------------------------------------------------------------------
HINSTANCE g_hInstance  = NULL; 
HWND g_hDlgMain        = NULL;                   

HWND g_hBtnCreate      = NULL;                   
HWND g_hBtnResume      = NULL;                   
HWND g_hBtnPause       = NULL;     
HWND g_hBtnExit        = NULL;
HWND g_hBtnKill        = NULL;
HWND g_hBtnWait        = NULL;

HWND g_hBtnCreateGroup = NULL;
HWND g_hBtnResumeGroup = NULL;
HWND g_hBtnPauseGroup  = NULL;       
HWND g_hBtnExitGroup   = NULL;
HWND g_hBtnKillGroup   = NULL;
HWND g_hBtnWaitGroup   = NULL;

HWND g_hLbLog          = NULL;
HWND g_hEdtMaxTasks    = NULL;
//---------------------------------------------------------------------------
BOOL                       g_bRes    = FALSE;
INT                        g_iRes    = - 1;
UINT                       g_uiRes   = 0;
ULONG                      g_ulRes   = 0;
ULONGLONG                  g_ullRes  = 0UL;
HANDLE                     g_hRes    = NULL;
HWND                       g_hwndRes = NULL;
std::string                g_sRes;
CxTraceLog                 g_clLog(FALSE);

CxThreadPool<CWorkThread> *thpTP     = NULL;
std::vector<tString>       vecsFileContent;
tString                    sFilePath = _T("C:/test.txt");
//////#define CRASH_SOMETIMES 10/(rand()%10)





//---------------------------------------------------------------------------
//
VOID vProcessMessages() {
	MSG msgMsg = {0};

	while (::PeekMessage(&msgMsg, NULL, 0, 0, PM_REMOVE)) {
		::TranslateMessage(&msgMsg); 
		::DispatchMessage (&msgMsg); 
	}
}
//---------------------------------------------------------------------------
//инициализация GUI
VOID vInitGUI() {
	g_hBtnCreate      = ::GetDlgItem(g_hDlgMain, IDC_btnCreate);                   
	g_hBtnResume      = ::GetDlgItem(g_hDlgMain, IDC_btnResume);                    
	g_hBtnPause       = ::GetDlgItem(g_hDlgMain, IDC_btnPause);      
	g_hBtnExit        = ::GetDlgItem(g_hDlgMain, IDC_btnExit); 
	g_hBtnKill        = ::GetDlgItem(g_hDlgMain, IDC_btnKill); 
	g_hBtnWait        = ::GetDlgItem(g_hDlgMain, IDC_btnWait); 

	g_hBtnCreateGroup = ::GetDlgItem(g_hDlgMain, IDC_btnCreateGroup); 
	g_hBtnResumeGroup = ::GetDlgItem(g_hDlgMain, IDC_btnResumeGroup); 
	g_hBtnPauseGroup  = ::GetDlgItem(g_hDlgMain, IDC_btnPauseGroup);        
	g_hBtnExitGroup   = ::GetDlgItem(g_hDlgMain, IDC_btnExitGroup); 
	g_hBtnKillGroup   = ::GetDlgItem(g_hDlgMain, IDC_btnKillGroup); 
	g_hBtnWaitGroup   = ::GetDlgItem(g_hDlgMain, IDC_btnWaitGroup); 

	g_hLbLog          = ::GetDlgItem(g_hDlgMain, IDC_lbLog); 
	g_hEdtMaxTasks    = ::GetDlgItem(g_hDlgMain, IDC_edtMaxTasks); 
	::SetWindowText(g_hEdtMaxTasks, _T("4"));
}
//---------------------------------------------------------------------------
VOID vBtnResume_OnClick() {

}
//---------------------------------------------------------------------------  
VOID vBtnPause_OnClick() {

}
//---------------------------------------------------------------------------
VOID vBtnExit_OnClick() {

}
//---------------------------------------------------------------------------
VOID vBtnKill_OnClick() {

}
//---------------------------------------------------------------------------
VOID vBtnWait_OnClick() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*	Group
*
*****************************************************************************/

//---------------------------------------------------------------------------
VOID vBtnCreateGroup_OnClick() {
	//-------------------------------------
	//uiMaxTasks
	UINT    uiMaxRunningTasks = 0;
	tString sMaxTasks;
	size_t  uiTextSize        = 0;
	
	sMaxTasks.resize(25);
	uiTextSize = ::GetWindowText(g_hEdtMaxTasks, &sMaxTasks.at(0), sMaxTasks.size());
	sMaxTasks.resize(uiTextSize);
	uiMaxRunningTasks = CxString::lexical_cast<UINT>(sMaxTasks);
	
	//-------------------------------------
	//читаем файл в std::vector
	g_bRes = CxStdioFile::bReadFile(sFilePath, &vecsFileContent);
	xASSERT(FALSE != g_bRes);


	//-------------------------------------
	//запускаем пул
	thpTP = new CxThreadPool<CWorkThread>(TRUE, TRUE, 	TRUE, TRUE/*FALSE*/);
	xASSERT(NULL != thpTP);
	
	g_bRes = thpTP->bCreateGroup(0, 0, &vecsFileContent, uiMaxRunningTasks/*всего заданий*/, uiMaxRunningTasks/*макс. кол-во раб. потоков*/);
	xASSERT(FALSE != g_bRes);

	g_bRes = thpTP->bResumeGroup();        
	xASSERT(FALSE != g_bRes);
}
//--------------------------------------------------------------------------- 
VOID vBtnResumeGroup_OnClick() {
	g_bRes = thpTP->bResumeGroup();
	xASSERT(FALSE != g_bRes);
}
//---------------------------------------------------------------------------  
VOID vBtnPauseGroup_OnClick() {
	g_bRes = thpTP->bPauseGroup();
	xASSERT(FALSE != g_bRes);
}
//--------------------------------------------------------------------------- 
VOID vBtnExitGroup_OnClick() {
	g_bRes = thpTP->bExitGroup(/*INFINITE*/5000);
	xASSERT(FALSE != g_bRes);
}
//--------------------------------------------------------------------------- 
VOID vBtnKillGroup_OnClick() {
	g_bRes = thpTP->bKillGroup(5000);         
	xASSERT(FALSE != g_bRes);
}
//---------------------------------------------------------------------------   
VOID vBtnWaitGroup_OnClick() {
	g_bRes = thpTP->bWaitGroup(5000);
	xASSERT(FALSE != g_bRes);
}
//---------------------------------------------------------------------------
VOID vBtnCreate_OnClick() {
	UINT    uiMaxRunningTasks = 0;
	tString sMaxTasks;
	size_t  uiTextSize        = 0;

	sMaxTasks.resize(25);
	uiTextSize = ::GetWindowText(g_hEdtMaxTasks, &sMaxTasks.at(0), sMaxTasks.size());
	sMaxTasks.resize(uiTextSize);
	uiMaxRunningTasks = CxString::lexical_cast<UINT>(sMaxTasks);

	g_bRes = thpTP->bSetMaxTasks(uiMaxRunningTasks);
	xASSERT(FALSE != g_bRes);

	////for (int i = 0; i < 1000000; ++ i) {
	////	vBtnCreateGroup_OnClick();	
	////	for (int i = 0; i < 5 * 100; ++ i) {
	////		::Sleep(10);
	////		vProcessMessages();
	////	}

	////	vBtnExitGroup_OnClick();
	////	for (int i = 0; i < 5 * 100; ++ i) {
	////		::Sleep(10);
	////		vProcessMessages();
	////	}
	////}
}
//---------------------------------------------------------------------------
int     WINAPI   WinMain     (HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow); 
LRESULT CALLBACK lpMainProc  (HWND hWnd, UINT message, UINT wParam, LONG lParam);
//---------------------------------------------------------------------------
LRESULT CALLBACK lpMainProc(HWND hWnd, UINT uiMsg, UINT wParam, LONG lParam) {
	INT wmId    = - 1;
	INT wmEvent = - 1;

	switch (uiMsg) {
		case WM_CREATE: {
			}
    		break;
 
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			switch (wmId) {
				case IDC_btnCreate: 
					vBtnCreate_OnClick();
					break;
				case IDC_btnResume: 
					vBtnResume_OnClick();
					break;                    
				case IDC_btnPause: 
					vBtnPause_OnClick();
					break;
				case IDC_btnExit: 
					vBtnExit_OnClick();
					break;
				case IDC_btnKill: 
					vBtnKill_OnClick();
					break;
				case IDC_btnWait: 
					vBtnWait_OnClick();
					break;
				case IDC_btnCreateGroup: 
					vBtnCreateGroup_OnClick();
					break;
				case IDC_btnResumeGroup: 
					vBtnResumeGroup_OnClick();
					break;
				case IDC_btnPauseGroup: 
					vBtnPauseGroup_OnClick();
					break;
				case IDC_btnExitGroup: 
					vBtnExitGroup_OnClick();
					break;
				case IDC_btnKillGroup: 
					vBtnKillGroup_OnClick();
					break;
				case IDC_btnWaitGroup: 
					vBtnWaitGroup_OnClick();
					break;
				case IDC_btnQuit:
					::DestroyWindow(hWnd);
					break;
			}
			break;

		case WM_CLOSE: 
			::DestroyWindow(hWnd); 
			break;

		case WM_DESTROY:
			::PostQuitMessage(0);
			break;

			/////default:
			////	return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
			////return ::DefDlgProc(hWnd, uiMsg, wParam, lParam);
	}

	return 0;
}
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	INT  iRes = - 1;
	BOOL bRes = FALSE;
	MSG  msg  = {0};

	g_hInstance = hInstance;
	assert(0 != g_hInstance);

	//-------------------------------------
	//Создаем диалог
	g_hDlgMain = ::CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_dlgMain), NULL, (DLGPROC)lpMainProc);
	assert(NULL != g_hDlgMain);

	vInitGUI();

	//-------------------------------------
	//...........

	bRes = ::ShowWindow(g_hDlgMain, SW_SHOW);
	assert(FALSE == bRes);

	bRes = ::UpdateWindow(g_hDlgMain);
	assert(FALSE != bRes);

	//-------------------------------------
	//Вертушка
	while (iRes = ::GetMessage(&msg, NULL, 0, 0 )) {
		if (- 1 == iRes) {
			assert(false);
		} else {
			::TranslateMessage(&msg);
			::DispatchMessage (&msg);
		}
	}

	return (INT)msg.wParam;;
}
//---------------------------------------------------------------------------