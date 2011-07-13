// Test.cpp : Defines the entry point for the application.
//

#include "Test.h"

#include <windows.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <commctrl.h>
#include <xLib/Gui/Dialogs/CxInputBox.h>
//---------------------------------------------------------------------------
HINSTANCE        g_hInstance  = NULL; 
HWND             g_hMainWnd   = NULL; 

int     WINAPI   WinMain     (HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow); 
LRESULT CALLBACK lpMainProc  (HWND hWnd, UINT message, UINT wParam, LONG lParam);
BOOL             bRegWndClass(HINSTANCE hInstance);
//---------------------------------------------------------------------------
BOOL bRegWndClass(HINSTANCE hInstance) {
	BOOL bRes = FALSE;

	//-------------------------------------
	//The Window structure
	WNDCLASSEX wcex = {0};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= lpMainProc;
	wcex.cbClsExtra		= 256;
	wcex.cbWndExtra		= DLGWINDOWEXTRA/*0*/;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= ::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "TestWindowClass";
	wcex.hIconSm		= NULL;

	//-------------------------------------
	//Register the window class
	bRes = ::RegisterClassEx(&wcex);
	assert(FALSE != bRes);

	return TRUE;
}
//---------------------------------------------------------------------------
LRESULT CALLBACK lpMainProc(HWND hWnd, UINT uiMsg, UINT wParam, LONG lParam) {
	INT wmId    = - 1;
	INT wmEvent = - 1;
	
	CxInputBox ibBox;
	CxInputBox::EModalResult mrRes;
	
	
	switch (uiMsg) {
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			switch (wmId) {
				case IDC_btnTest:
					mrRes = ibBox.mrShowModal(xT("Caption"), xT("Prompt"), xT("Some text"));
					switch (mrRes) {
						case CxInputBox::mrOk:		{ iMsgBox(ibBox.sGetText(), xT("CxInputBox::mrOk")    ); }    break;
						case CxInputBox::mrCancel:	{ iMsgBox(ibBox.sGetText(), xT("CxInputBox::mrCancel")); }    break;

						default:                    { xASSERT(FALSE);                                        }    break;
					}
					break;

				case IDC_btnExit:
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

	//bRes = bRegWndClass(g_hInstance);
	//assert(FALSE != bRes);

	//-------------------------------------
	//Создаем диалог
	g_hMainWnd = ::CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_dlgMain), NULL, (DLGPROC)lpMainProc);
	assert(NULL != g_hMainWnd);

	//-------------------------------------
	//...........

	bRes = ::ShowWindow(g_hMainWnd, SW_SHOW);
	assert(FALSE == bRes);

	bRes = ::UpdateWindow(g_hMainWnd);
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