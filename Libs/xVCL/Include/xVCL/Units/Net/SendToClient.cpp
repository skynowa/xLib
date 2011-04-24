/***********************************************************************
*   
*
************************************************************************/
    

void __fastcall TfrmMainServer::SendToClient(const tString & asMsg) {
    try {
        NMMsg1->PostIt(asMsg);
    } catch (...) {}
}
