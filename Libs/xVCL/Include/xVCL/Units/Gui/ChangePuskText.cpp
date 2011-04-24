/***********************************************************************
*   писать на "Пуске"
*
************************************************************************/


void __fastcall TfrmMainServer::ChangePuskText(const tString & asText) {
    HWND hWnd;
	hWnd = FindWindow("Shell_TrayWnd", NULL);
	hWnd = FindWindowEx(hWnd, NULL, "BUTTON", NULL);

    SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)asText.c_str());
}

