/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::SwitchOnMonitor(bool bHideFlag)  {
    if (bHideFlag == true) {
        SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    } else {
        SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, -1);
    }
}      
