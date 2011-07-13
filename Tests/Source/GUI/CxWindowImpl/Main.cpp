#include <windows.h>
#include <tchar.h>

#include <xLib/Gui/CxIcon.h>
#include <xLib/Gui/CxApplication.h>
#include <xLib/Gui/Resource.xrc.h>
#include <xLib/CxSystemInfo.h>

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