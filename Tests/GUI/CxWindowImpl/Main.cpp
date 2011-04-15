#include <windows.h>
#include <tchar.h>

#include <XLib/Gui/CxIcon.h>
#include <XLib/Gui/CxApplication.h>
#include <XLib/Gui/Resource.xrc.h>
#include <XLib/CxSystemInfo.h>

#include "Windows/CWndMain.h"

#include <vector>
#include <string>
#include <map>
#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
//---------------------------------------------------------------------------
INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, INT nCmdShow) {
	BOOL bRes = FALSE;

	//////bRes = IsXPThemed();
	
	////iMsgBox(CxSystemInfo::sFormatOSVerson(xWINVER));

	////xASSERT(FALSE);

	CxApplication::bInit(hInstance, lpCmdLine);
	
	CWndMain wndMain;     
	bRes = wndMain.bCreateRes(IDD_DIALOG1, NULL);
	bRes = wndMain.bMoveCenter(::GetDesktopWindow());
	bRes = wndMain.bShow(SW_SHOW);

	CxApplication::bRun();

	return 0;
}
//---------------------------------------------------------------------------