/***********************************************************************
*  
*
************************************************************************/


void __fastcall TfrmMainServer::ReloadExplorer() {
    HWND hShell = FindWindow ("Progman", NULL);
    PostMessage(hShell, WM_QUIT, 0, 0L);
    ShellExecute(0, "open", "Explorer.exe", NULL, NULL, SW_SHOWNORMAL);
}
