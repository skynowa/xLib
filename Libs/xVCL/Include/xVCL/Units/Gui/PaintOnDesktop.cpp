/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::PaintOnDesktop(const tString &asText) {
    HDC hdc = CreateDC(TEXT(asText.c_str()), NULL, NULL, NULL);
    Rectangle(hdc, 100,100, 200, 200);
    DeleteDC (hdc);
}
