/***********************************************************************
*   
*
************************************************************************/

void __fastcall UserToComboBoxEx() {
    TSHFileInfo SFI;
    cboeUser->Images         = new TImageList(this);
    cboeUser->Images->Handle = SHGetFileInfo(NULL, 0, &SFI, sizeof(SFI), SHGFI_SYSICONINDEX|SHGFI_SMALLICON);

    SHGetFileInfo("\\\\127.0.0.1\\", 0, &SFI, sizeof(SFI), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    cboeUser->ItemsEx->AddItem(
        "Administrator",
        SFI.iIcon,         //определяем соответствующую иконку
        SFI.iIcon,         //определяем соответствующую иконку
        0,
        0,
        0
    );

    cboeUser->ItemIndex = 0;
}
