/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::RestoreMyDocuments() {
    TRegistry *pReg = new TRegistry(KEY_ALL_ACCESS);
    tString asKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{450D8FBA-AD25-11D0-98A8-0800361B1103}\\";
    if (pReg) {
        pReg->RootKey = HKEY_LOCAL_MACHINE;
        pReg->CreateKey(asKey);
        pReg->CloseKey();
    }
    delete pReg;
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);   //обновляем раб. стол
}
