/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::ArrangeDesktopIcons() {
    HWND       hDesktop;

    hDesktop = FindWindow("ProgMan", 0);
    hDesktop = GetWindow(hDesktop, GW_CHILD);
    hDesktop = GetWindow(hDesktop, GW_CHILD);

    SendMessage(hDesktop, LVM_ARRANGE, LVA_ALIGNLEFT, 0);
}      
