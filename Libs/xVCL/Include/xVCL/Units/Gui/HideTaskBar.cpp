/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::HideTaskBar(bool bHideFlag) {
    HWND hWnd;
	hWnd = FindWindow("Shell_TrayWnd",NULL);
    
	// �������� ������
    if (bHideFlag == true) {
	    ShowWindow(hWnd, SW_HIDE);
    } else {
        ShowWindow(hWnd, SW_SHOW);
    }
}      
