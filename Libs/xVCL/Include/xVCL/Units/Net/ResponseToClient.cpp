/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::ResponseToClient() {
    try {
        NMMsg1->PostIt(SysErrorMessage(GetLastError()));
    } catch (...) {}
}

