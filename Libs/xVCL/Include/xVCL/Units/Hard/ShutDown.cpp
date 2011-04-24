/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::ShutDown() {
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	//Get a token for this process.
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		//ShowMessage("OpenProcessToken");
	}
	//Get the LUID for the shutdown privilege.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1; // one privilege to set
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	//Get the shutdown privilege for this process.
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	//Cannot test the return value of AdjustTokenPrivileges.
	if (GetLastError() != ERROR_SUCCESS) {
		//ShowMessage("AdjustTokenPrivileges");
	}
	//Shut down the system and force all applications to close.
	if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0)) {
		//ShowMessage("ExitWindowsEx");
	}
}
