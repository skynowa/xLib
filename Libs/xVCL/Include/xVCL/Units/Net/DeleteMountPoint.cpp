/***********************************************************************
*   
*
************************************************************************/


void __fastcall DeleteMountPoint(const tString & asMountPointHost, const tString & asMountPointShare) {
    ////#if (WINVER == 1281)
        TRegistry *pReg = new TRegistry(KEY_ALL_ACCESS);
        tString asKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\\##" + asMountPointHost + "#" + asMountPointShare + "$" + "\\";
        ////ShowMessage(asKey);
        if (pReg) {
            if (pReg->KeyExists(asKey)) {
                pReg->RootKey = HKEY_CURRENT_USER;
                pReg->DeleteKey(asKey);
                pReg->CloseKey();
            }
        }
        delete pReg;
    ////#endif
}