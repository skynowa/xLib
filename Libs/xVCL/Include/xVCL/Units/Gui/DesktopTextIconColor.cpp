/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::DesktopTextIconColor(int iTextColor) {
    HWND hwnd;
    //Get the handle of Program Manager 
    hwnd = FindWindow("ProgMan", NULL); 
    //Get first child window : SHELLDLL_DefView 
    hwnd = GetWindow(hwnd, GW_CHILD);
    //Get the handle of the ListView 
    hwnd = GetWindow(hwnd, GW_CHILD);
    if (hwnd)  {
        //NULL = error
        //Get the TextColor and save it
        int iOldTextColor = ::SendMessage(hwnd, LVM_GETTEXTCOLOR, 0, 0);
        //If the text color is already the right color, do nothing
        if (iOldTextColor != iTextColor) {
            //TextColor holds the desired color ((long)0x00FFFFFF for white)
            ::SendMessage(hwnd,LVM_SETTEXTCOLOR, (WPARAM)0, (LPARAM)iTextColor);
            //Repaint the desktop
            InvalidateRect(hwnd,NULL,TRUE);
        }
        //If background color is already no background color, do nothing
        //CLR_NONE = no background color
        if (::SendMessage(hwnd, LVM_GETTEXTBKCOLOR, 0, 0) != (int)CLR_NONE) {
            ::SendMessage(hwnd, LVM_SETTEXTBKCOLOR, (WPARAM)0, (LPARAM)CLR_NONE);
            InvalidateRect(hwnd,NULL,TRUE);
        }
    } 
}      
