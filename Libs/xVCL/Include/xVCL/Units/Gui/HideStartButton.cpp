/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::HideStartButton(bool bHideFlag) {
	HWND hWnd;
	hWnd = FindWindow("Shell_TrayWnd", NULL);
	hWnd = FindWindowEx(hWnd, NULL, "BUTTON", NULL);

	// �������� ������
    if (bHideFlag == true) {
	    ShowWindow(hWnd, SW_HIDE);
    } else {
        ShowWindow(hWnd, SW_SHOW);
    }
}
