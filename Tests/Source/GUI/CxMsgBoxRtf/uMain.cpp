/****************************************************************************
*	CxMsgBoxRtf
*
*****************************************************************************/


#include <xLib/xCommon.h>
#include <xLib/Gui/Dialogs/CxMsgBoxRtf.h>
//---------------------------------------------------------------------------
INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION|WS_VISIBLE
	//DialogBoxWindow(g_hInst, L"PREVED!", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 200, 200, 200, 100, NULL/*Handle*/, DialogProc, 0);
	tString sRTF = xT("{\\rtf1\\ansi\\ansicpg1251\\deff0\\deflang1049{\\fonttbl{\\f0\\fswiss\\fprq2\\fcharset0 Arial;}{\\f1\\fswiss\\fcharset204{\\*\\fname Arial;}Arial CYR;}}")
		           xT("{\\colortbl ;\\red255\\green0\\blue0;}")
		           xT("\\viewkind4\\uc1\\pard\\cf1\\lang1033\\ul\\b\\i\\f0\\fs20 Simple RTF\\cf0\\lang1049\\ulnone\\b0\\i0\\f1\\par}");

	int iRes = CxMsgBoxRtf::iShow(NULL, sRTF, xT("Заголовок"));
	



	MSG msg = {0};
	while (::GetMessage(&msg, NULL, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return 0;
}
//---------------------------------------------------------------------------