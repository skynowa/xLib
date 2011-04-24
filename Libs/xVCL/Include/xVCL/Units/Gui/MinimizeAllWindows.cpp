/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::MinimizeAllWindows() {
    keybd_event(VK_LWIN, 0, 0 ,0);
    keybd_event('M', 0, 0 ,0);
    keybd_event('M', 0, KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP,0);
}
