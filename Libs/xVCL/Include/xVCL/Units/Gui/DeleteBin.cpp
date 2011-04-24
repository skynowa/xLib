/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::DeleteBin() {
	TRegistry *pReg = new TRegistry(KEY_ALL_ACCESS);
	tString asKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{645FF040-5081-101B-9F08-00AA002F954E}\\";
	if (pReg) {
		if (pReg->KeyExists(asKey)) {   //?oia oaaeeou "Ei?ceio", iaiaoiaeii ?oia auei ?oi oaaeyou (ee?? ?aano?a)
			pReg->CreateKey(asKey);
		}
		pReg->RootKey = HKEY_LOCAL_MACHINE;
		pReg->DeleteKey(asKey);
		pReg->CloseKey();
	}
	delete pReg;
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);   //iaiiaeyai ?aa. noie
}
