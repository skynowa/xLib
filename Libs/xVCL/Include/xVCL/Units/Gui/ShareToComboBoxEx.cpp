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
        "�",
        SFI.iIcon,    //���������� ��������������� ������
        SFI.iIcon,    //���������� ��������������� ������
        0,
        0,
        0
    );

    cboeShare->ItemIndex = 0;
}
