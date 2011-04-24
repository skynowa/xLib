/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::StandByMonitor(bool bStandByFlag)  {
    if (bStandByFlag == true) {
        SendMessage(/*Application->Handle*/HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 0);
    } else {
        SendMessage(/*Application->Handle*/HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, -1);
    }
}

