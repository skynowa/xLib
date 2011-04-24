/***********************************************************************
*	Äטאכמד מבחמנא סועט
*
************************************************************************/


void __fastcall BrowseNetwork() {
    LPITEMIDLIST P;
    char cFolderName[MAX_PATH];

    BROWSEINFO BInfo;
    SHGetSpecialFolderLocation(Handle, CSIDL_NETWORK, &P);
    BInfo.hwndOwner      = frmMain->Handle;
    BInfo.pidlRoot       = P;
    BInfo.pszDisplayName = cFolderName;
    BInfo.lpszTitle      = "Choose the victim...";
    BInfo.ulFlags        = BIF_BROWSEFORCOMPUTER;
    BInfo.lpfn           = NULL;
    BInfo.lParam         = 0;
    BInfo.iImage         = 0;

    if (SHBrowseForFolder(&BInfo) != NULL) {
        cboHost->Text = BInfo.pszDisplayName;
        cboUser->Text = BInfo.pszDisplayName;
        ledtAutoSaveFile->Text = ExtractFilePath(Application->ExeName) + cboHost->Text + ".ini";
    }
}
