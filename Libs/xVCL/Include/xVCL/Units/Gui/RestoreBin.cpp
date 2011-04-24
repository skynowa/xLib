/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::RestoreBin() {
    TRegistry *pReg = new TRegistry(KEY_ALL_ACCESS);
    tString asKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{645FF040-5081-101B-9F08-00AA002F954E}\\";
    if (pReg) {
        pReg->RootKey = HKEY_LOCAL_MACHINE;
        pReg->CreateKey(asKey);
        pReg->CloseKey();
    }
    delete pReg;
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);   //обновляем раб. стол
}
