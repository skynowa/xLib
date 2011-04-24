/***********************************************************************
*   
*
************************************************************************/

void __fastcall ShareToComboBoxEx() {
    TSHFileInfo SFI;
    cboeShare->Images         = new TImageList(this);
    cboeShare->Images->Handle = SHGetFileInfo(NULL, 0, &SFI, sizeof(SFI), SHGFI_SYSICONINDEX|SHGFI_SMALLICON);

    SHGetFileInfo("C:\\", 0, &SFI, sizeof(SFI), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    cboeShare->ItemsEx->AddItem(
        "С",
        SFI.iIcon,    //определяем соответствующую иконку
        SFI.iIcon,    //определяем соответствующую иконку
        0,
        0,
        0
    );

    cboeShare->ItemIndex = 0;
}
