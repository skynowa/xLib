/***********************************************************************
*   
*
************************************************************************/

void __fastcall HostToComboBoxEx() {
    TSHFileInfo SFI;
    cboeHost->Images         = new TImageList(this);
    cboeHost->Images->Handle = SHGetFileInfo(NULL, 0, &SFI, sizeof(SFI), SHGFI_SYSICONINDEX|SHGFI_SMALLICON);

    SHGetFileInfo("\\\\127.0.0.1\\", 0, &SFI, sizeof(SFI), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    cboeHost->ItemsEx->AddItem(
        "Administrator",
        SFI.iIcon,    //определяем соответствующую иконку
        SFI.iIcon,    //определяем соответствующую иконку
        0,
        0,
        0
    );

    cboeHost->ItemIndex = 0;
}
