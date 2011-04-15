#include <windows.h>
#include "resource.h"
#include <XLib/GUI/CXApplication.h>

#include "CMyCDlg.h"
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	BOOL bRes = FALSE;

	CXApplication::bInit(hInstance, lpCmdLine);
	
	CMyCDlg dlgMain;
	bRes = dlgMain.bCreate(IDD_DIALOG_MAIN, 0, NULL);
	bRes = dlgMain.bShow(SW_SHOW);
	bRes = dlgMain.bUpdate();

	CXApplication::bRun();

	return 0;
}
//---------------------------------------------------------------------------