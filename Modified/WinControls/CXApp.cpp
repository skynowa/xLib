/****************************************************************************
*	CXApp
*
*****************************************************************************/


#include <Xlib/WinControls/CXApp.h>
#include <XLib/Debug/xassert.h>
//---------------------------------------------------------------------------
CXApp::CXApp() :
	_m_hInstance (NULL),
	_m_hIcon     (NULL),
	_m_hAccel    (NULL)
{
	_m_sClassName = "CXApp";
	_m_iWidth     = 544;
	_m_iHeight    = 375;
	_m_iTop       = CW_USEDEFAULT;
	_m_iLeft      = CW_USEDEFAULT;
}
//---------------------------------------------------------------------------
//Create the window
BOOL CXApp::bCreate(HINSTANCE hInstance, INT iCmdShow) {  ///XASSERT(FALSE);
	BOOL bRes = FALSE;
	
	//-------------------------------------
	//The Window structure
	WNDCLASSEX wincl = {0};	

	wincl.hInstance     = hInstance;		
	wincl.lpszClassName = _m_sClassName.c_str();
	wincl.lpfnWndProc   = BaseWindowProc;	//This function is called by windows
	wincl.style         = CS_DBLCLKS;				//Catch double-clicks
	wincl.cbSize        = sizeof(WNDCLASSEX);
	wincl.hIcon         = _m_hIcon;	//LoadIcon (hInstance, 0);
	wincl.hIconSm       = NULL;		//LoadIcon (hInstance, 0);
	wincl.hCursor       = NULL;		//LoadCursor (NULL, IDC_ARROW);
	wincl.lpszMenuName  = NULL;
	wincl.cbClsExtra    = 256;		//No extra bytes after the window class
	wincl.cbWndExtra    = 0;		//dialog box not from resource file
	wincl.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	//-------------------------------------
	//Register the window class
	bRes = ::RegisterClassEx(&wincl);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE);

	//-------------------------------------
	//The class is registered, let's create the program
	_m_hWnd = ::CreateWindowEx(
				0,								//Extended possibilites for variation
				_m_sClassName.c_str(),			//Classname
				_m_sText.c_str(),				//Title Text
				WS_OVERLAPPEDWINDOW | DS_CENTER | WS_MINIMIZEBOX | WS_POPUP | WS_CAPTION | WS_SYSMENU,			//default window
				_m_iLeft, _m_iTop, 	            //The programs width
				_m_iWidth,_m_iHeight,			//and height in pixels
				HWND_DESKTOP,					//The window is a child-window to desktop
				_m_hMenu,						//Menu
				hInstance,						//Program Instance handler
				this);							//Pointer to the current class
	/*DEBUG*/XASSERT_RET(NULL != _m_hWnd, FALSE);

	//-------------------------------------
	//шрифт
	HFONT hFont = ::CreateFont(13, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Tahoma");
	SetFont(hFont);	////::SendMessage(_m_hWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)1);

	//-------------------------------------
	//Make the window visible on the screen
	bRes = bShow(iCmdShow);	
	CHECK_RET(FALSE == bRes, FALSE);
	
	bRes = bUpdate();
	CHECK_RET(FALSE == bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
////LRESULT CALLBACK MainProc(HWND hDlg, UINT message, UINT wParam, LONG lParam) {
////	switch(message)	{
////			case WM_COMMAND:
////			{
////				switch(LOWORD(wParam))	{
////					case 1003/*IDC_BUTTON1*/: 
////						MessageBox(0, "___IDC_BUTTON1___", "", MB_OK);
////						break;
////					}
////			}
////			break;
////		}
////
////	return 0;
////}
//---------------------------------------------------------------------------
BOOL CXApp::bCreateRes(HINSTANCE hInstance, INT iResID, INT iCmdShow) {
	BOOL bRes = FALSE;
	
	//-------------------------------------
	//The Window structure
	WNDCLASSEX wincl = {0};	

	wincl.hInstance     = hInstance;		
	wincl.lpszClassName = _m_sClassName.c_str();
	wincl.lpfnWndProc   = BaseWindowProc;	//This function is called by windows
	wincl.style         = CS_DBLCLKS;				//Catch double-clicks
	wincl.cbSize        = sizeof(WNDCLASSEX);
	wincl.hIcon         = _m_hIcon;					//LoadIcon (hInstance, 0);
	wincl.hIconSm       = NULL;						//LoadIcon (hInstance, 0);
	wincl.hCursor       = NULL;						//LoadCursor (NULL, IDC_ARROW);
	wincl.lpszMenuName  = NULL;
	wincl.cbClsExtra    = 256;					    //No extra bytes after the window class
	wincl.cbWndExtra    = DLGWINDOWEXTRA/*0*/;		//используем диалог с ресурса
	wincl.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	//-------------------------------------
	//Register the window class
	bRes = ::RegisterClassEx(&wincl);
	/*DEBUG*/XASSERT_RET(FALSE != bRes, FALSE)


	_m_hWnd = ::CreateDialog(hInstance, MAKEINTRESOURCE(iResID), NULL, (DLGPROC)/*MainProc*/BaseWindowProc);
	/*DEBUG*/XASSERT_RET(NULL != _m_hWnd, FALSE);

	//-------------------------------------
	//шрифт
	//...

	//-------------------------------------
	//Make the window visible on the screen
	bRes = bShow(iCmdShow);	
	CHECK_RET(FALSE == bRes, FALSE);

	bRes = bUpdate();
	CHECK_RET(FALSE == bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//Runs the window (waits for messages and processes them)
VOID CXApp::vRun() {
	INT  iRes = - 1;
	MSG  msg  = {0}; //Here messages to the application are saved

	//Вертушка
	while (iRes = ::GetMessage(&msg, NULL, 0, 0 )) {
		if (- 1 == iRes) {
			/*DEBUG*/XASSERT(FALSE);
		} else {
			::TranslateMessage(&msg);
			::DispatchMessage (&msg);
		}
	}

	////// Main message loop:
	////while (::GetMessage(&msg, NULL, 0, 0)) 
	////{
	////	////::TranslateMessage(&msg);
	////	////::DispatchMessage(&msg);
	////	////if (!::IsWindow(_m_hWnd) || !::IsDialogMessage(_m_hWnd, &msg)) 
	////	////{
	////	////	::TranslateMessage(&msg);
	////	////	::DispatchMessage(&msg);
	////	////}
	////}

	//////////while (::GetMessage(&msg, NULL, 0, 0)) {
	//////////	////if (NULL != _m_hAccel && ::TranslateAccelerator(_m_hWnd, _m_hAccel, &msg)) {
	//////////	////	continue;
	//////////	////} 
	//////////	//Translate virtual-key messages into character messages
	//////////	::TranslateMessage(&msg);
	//////////	//Send message to WindowProcedure
	//////////	::DispatchMessage(&msg);

	//////////	////if (!IsWindow(_m_hWnd) || !IsDialogMessage(_m_hWnd, &msg)) 
	//////////	////{ 
	//////////	////	TranslateMessage(&msg); 
	//////////	////	DispatchMessage(&msg); 
	//////////	////} 
	//////////}


}
/*
BOOL bRet;

while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) { 
	if (bRet == -1)	{
		// Handle the error and possibly exit
	}
	else if (!IsWindow(hwndGoto) || !IsDialogMessage(hwndGoto, &msg)) 
	{ 
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
} 
*/
/*
MSG    msg;
HACCEL hAccelTable;

hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_STEALTHDIALOG);

while (GetMessage(&msg, NULL, 0, 0)) {
	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) || !IsDialogMessage(msg.hwnd,&msg) ) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
return (int) msg.wParam;
*/
//---------------------------------------------------------------------------
HICON CXApp::hIcon() {
	return _m_hIcon;
}
//---------------------------------------------------------------------------
VOID CXApp::vIcon(HICON hIcon) {
	_m_hIcon = hIcon;
}
//---------------------------------------------------------------------------
HACCEL CXApp::hAccelerators() {
	return _m_hAccel;
}
//---------------------------------------------------------------------------
VOID CXApp::vAccelerators(HACCEL hAccel) {
	_m_hAccel = hAccel;
}
//---------------------------------------------------------------------------
BOOL CXApp::bIsMaximized() {
	return ::IsZoomed(_m_hWnd);
}
//---------------------------------------------------------------------------
VOID CXApp::vProcessMessages() {
	MSG msg = {0};

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		::TranslateMessage(&msg); 
		::DispatchMessage(&msg); 
	}
}
//---------------------------------------------------------------------------
BOOL CXApp::bSetPosScreenCenter() {
	BOOL bRes = FALSE;
	
	INT  iWidth  = 0; 
	INT  iHeight = 0; 
	INT  iLeft   = 0; 
	INT  iTop    = 0;
	RECT rcWin   = {0};

	//-------------------------------------
	//размер экрана
	HDC hDC = ::GetDC(0);
	iWidth  = ::GetDeviceCaps(hDC, HORZRES);
	iHeight = ::GetDeviceCaps(hDC, VERTRES);
	::ReleaseDC(0, hDC);

	::GetWindowRect(_m_hWnd, &rcWin);

	iLeft = (iWidth -  (rcWin.right  - rcWin.left + 1)) / 2;
	iTop  = (iHeight - (rcWin.bottom - rcWin.top  + 1)) / 2;

	bRes = bMove(iLeft, iTop, rcWin.right - rcWin.left + 1, rcWin.bottom - rcWin.top + 1, TRUE);

	return bRes;
}
//---------------------------------------------------------------------------