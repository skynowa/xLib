#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include <xLib/Gui/CxWaitCursor.h>
//---------------------------------------------------------------------------
BOOL                                    g_bRes    = FALSE;
INT                                     g_iRes    = - 1;
UINT                                    g_uiRes   = 0;
ULONG                                   g_ulRes   = 0;
ULONGLONG                               g_ullRes  = 0UL;
HANDLE                                  g_hRes    = INVALID_HANDLE_VALUE;
HWND                                    g_hwndRes = NULL;
std::string                             g_sRes    = "";
//---------------------------------------------------------------------------
INT main(int argc, char* argv[]) {
	/****************************************************************************
	* CxWaitCursor
	*
	*****************************************************************************/


	//-------------------------------------
	//[FUNCTION_NAME]
	{
		CxWaitCursor wcWaitCursor;
	}

	CxWaitCursor wcWaitCursor;

    std::cout << std::endl << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------