/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::DeleteMyDocuments() {
    TRegistry *pReg = new TRegistry(KEY_ALL_ACCESS);
    tString asKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{450D8FBA-AD25-11D0-98A8-0800361B1103}\\";
    if (pReg) {
        if (pReg->KeyExists(asKey)) {   //чтоб удалить "Мои документы", необходимо чтоб было что удалять (ключ реестра)
            pReg->CreateKey(asKey);
        }
        pReg->RootKey = HKEY_LOCAL_MACHINE;
        pReg->DeleteKey(asKey);
        pReg->CloseKey();
    }
    delete pReg;
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);   //обновляем раб. стол
}
