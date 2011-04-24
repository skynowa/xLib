/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::DisableDesktop(bool bDisableFlag)  {
    HWND hDesktop = FindWindow("ProgMan", NULL);
    EnableWindow(hDesktop, !bDisableFlag);
}
