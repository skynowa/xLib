/***********************************************************************
*	��������� ComboBoxEx �������, ������� ������
*
************************************************************************/

void __fastcall doDrivesToComboBoxEx() {  //DONE: doDrivesToComboBoxEx()
    cboeLocalDrives->Items->Clear();

    DWORD dwBufLen = GetLogicalDriveStrings(0, NULL);
    if (!dwBufLen) {
            return; //error
    }

    TCHAR *Buf = new TCHAR[dwBufLen], *pBuf = Buf;
    if (!GetLogicalDriveStrings(dwBufLen, Buf)) {
            return; //error
    }


    tString asDriveLetter = "";

    ///////
    DWORD dwNextFreeDriveLetter = GetLogicalDrives();    //������� ���������� ������� �����
    for (int i = 0; i < 26; i ++) {                   	 //���������� ������ �� �����
        int n = (dwNextFreeDriveLetter >> i) & 1;    	 //����� �������� �������� ����
        tString asDriveLetter = (char)(65 + i);   	 //�������� ������ �����
        if (n) {
            //���� ������� - ���� � ������� i ����
            //tString path = tString((char)(65+i)) + ":\\";
            //tString out = "���� " + DriveLetter + "\n";

            //ShowMessage(out);
            tString dl = tString((char)(65 + i)); // �������� ������ �����
            UINT drive_type = GetDriveType((dl + ":\\").c_str()); // ����� ��� �����
            if (drive_type == DRIVE_CDROM) {
                ////ShowMessage(drive_type);
            }
        }
    }

    ////////////
    TSHFileInfo sfi;
    
    while (*pBuf) {  
        int iIconIndex = -1;

        if (SHGetFileInfo(pBuf, 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX|SHGFI_SMALLICON)) {
                iIconIndex = sfi.iIcon;    //���������� ��������������� ������
        }

        asDriveLetter = pBuf;                                   //��������� ��� � tString
        pBuf += (asDriveLetter.Length() + 1) * sizeof(TCHAR);   //������� ��������� �� ��� ���������� �����
        asDriveLetter = StringReplace(asDriveLetter, "\\", EmptyStr, TReplaceFlags());  //������� ���� �� �����

        char *cDriveLabel = new char[255];  //����� �����
        cDriveLabel[0] = 0;


        unsigned __int64 FreeBytesAvailable;
        unsigned __int64 TotalNumberOfBytes;
        unsigned __int64 TotalNumberOfFreeBytes;
        char drive_label[30];
        char drive_fat[30];
        DWORD drive_sn;
        ////DWORD drive_name_size = sizeof(drive_label);

        // �������� ������ � ��������
        bool Flag = ::GetDiskFreeSpaceEx(
                        asDriveLetter.c_str(),
                        (PULARGE_INTEGER)&FreeBytesAvailable,
                        (PULARGE_INTEGER)&TotalNumberOfBytes,
                        (PULARGE_INTEGER)&TotalNumberOfFreeBytes
        );

        if (Flag) {
           //ShowMessage("�������� �� �����: " + tString(TotalNumberOfFreeBytes));
           //ShowMessage("����� �� �����: " + tString(TotalNumberOfBytes));
        } else {
           //ShowMessage("������ � GetDiskFreeSpaceEx");
        }

        GetVolumeInformation((asDriveLetter + "\\").c_str(), cDriveLabel, 255, &drive_sn, NULL, NULL, NULL, NULL);
        ////ShowMessage(drive_sn);


        //��������� cboeLocalDrives
        cboeLocalDrives->ItemsEx->AddItem(
            asDriveLetter + " " + cDriveLabel + "  " + /*tString(drive_sn)*/"   [Free: " + TotalNumberOfFreeBytes / 1000000 + " Mb]",
            iIconIndex,
            iIconIndex,
            0,
            0,
            0
        );
    }

    delete[] Buf;

    //������������� � cboeLocalDrives ������� ����
    for (int i = 0; i < cboeLocalDrives->Items->Count; i ++) {
        if (ExtractFileDrive(Application->ExeName) == cboeLocalDrives->Items->Strings[i].SetLength(2)) {     //ShowMessage(asCurrentFileDrive);
            cboeLocalDrives->ItemIndex = i;
        }
    }
}
