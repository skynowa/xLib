/**********************************************************************
*   DisplayIEImages
*
***********************************************************************/

void __fastcall DisplayIEImages(bool bEnable) {
    TRegistry *pReg = new TRegistry(KEY_ALL_ACCESS);

    tString asShow = "";
    if (bEnable == true) {
        asShow = "yes";
    }
    if (bEnable == false) {
        asShow = "no";
    }

    //ShowMessage(asShow);

    tString asKey = "Software\\Microsoft\\Internet Explorer\\Main";

    if (pReg) {
        if (pReg->OpenKey(asKey, false)) {
	        pReg->RootKey = HKEY_CURRENT_USER;
            pReg->WriteString("Display Inline Images", asShow);
    	    pReg->CloseKey();
        }
    }

    delete pReg;
}