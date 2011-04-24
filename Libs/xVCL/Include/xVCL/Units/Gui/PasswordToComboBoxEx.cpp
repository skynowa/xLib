/***********************************************************************
*  
*
************************************************************************/

void __fastcall PasswordToComboBoxEx() {
//    TSHFileInfo SFI;
//    cboePassword->Images         = new TImageList(this);
//    cboePassword->Images->Handle = SHGetFileInfo(NULL, 0, &SFI, sizeof(SFI), SHGFI_SYSICONINDEX|SHGFI_SMALLICON);

//    SHGetFileInfo("*.*", 0, &SFI, sizeof(SFI), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    cboePassword->ItemsEx->AddItem(
        "875426",
        /*SFI.iIcon*/3,    //определяем соответствующую иконку
        /*SFI.iIcon*/3,    //определяем соответствующую иконку
        0,
        0,
        0
    );

    cboePassword->ItemIndex = 0;
}
