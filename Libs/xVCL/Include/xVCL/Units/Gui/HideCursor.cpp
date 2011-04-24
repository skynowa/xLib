/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::HideCursor(bool bHideFlag) {
    if (bHideFlag == true) {
	    SetSystemCursor(LoadCursor(HInstance, "CURSOR_EMPTY"), OCR_NORMAL);
    } else {
        SetSystemCursor(LoadCursor(HInstance, "CURSOR_DEFAULT"), OCR_NORMAL);
        //SetSystemCursor(GetCursor(), OCR_NORMAL);
    }
}      
