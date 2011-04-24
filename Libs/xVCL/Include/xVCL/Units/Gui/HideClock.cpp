/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::HideClock(bool bHideFlag) {
	HWND hClockWnd = FindWindowEx(FindWindowEx(FindWindowEx(NULL, NULL, "Shell_TrayWnd", NULL), NULL, "TrayNotifyWnd", NULL), NULL, "TrayClockWClass", NULL);
	if (hClockWnd) {
        if (bHideFlag == true) {
            ShowWindow(hClockWnd, SW_HIDE);
        } else {
            ShowWindow(hClockWnd, SW_SHOW);
        }
    }
}
