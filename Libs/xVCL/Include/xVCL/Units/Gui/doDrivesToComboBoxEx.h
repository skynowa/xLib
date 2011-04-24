/***********************************************************************
*	Заполняем ComboBoxEx именами, метками дисков
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
    DWORD dwNextFreeDriveLetter = GetLogicalDrives();    //функция возвращает битовую маску
    for (int i = 0; i < 26; i ++) {                   	 //проходимся циклом по битам
        int n = (dwNextFreeDriveLetter >> i) & 1;    	 //узнаём значение текущего бита
        tString asDriveLetter = (char)(65 + i);   	 //получаем литеру диска
        if (n) {
            //если единица - диск с номером i есть
            //tString path = tString((char)(65+i)) + ":\\";
            //tString out = "Диск " + DriveLetter + "\n";

            //ShowMessage(out);
            tString dl = tString((char)(65 + i)); // получаем литеру диска
            UINT drive_type = GetDriveType((dl + ":\\").c_str()); // узнаём тип диска
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
                iIconIndex = sfi.iIcon;    //определяем соответствующую иконку
        }

        asDriveLetter = pBuf;                                   //переводим имя в tString
        pBuf += (asDriveLetter.Length() + 1) * sizeof(TCHAR);   //смещаем указатель на имя следующего диска
        asDriveLetter = StringReplace(asDriveLetter, "\\", EmptyStr, TReplaceFlags());  //удаляем слэш из имени

        char *cDriveLabel = new char[255];  //метка диска
        cDriveLabel[0] = 0;


        unsigned __int64 FreeBytesAvailable;
        unsigned __int64 TotalNumberOfBytes;
        unsigned __int64 TotalNumberOfFreeBytes;
        char drive_label[30];
        char drive_fat[30];
        DWORD drive_sn;
        ////DWORD drive_name_size = sizeof(drive_label);

        // получаем данные о размерах
        bool Flag = ::GetDiskFreeSpaceEx(
                        asDriveLetter.c_str(),
                        (PULARGE_INTEGER)&FreeBytesAvailable,
                        (PULARGE_INTEGER)&TotalNumberOfBytes,
                        (PULARGE_INTEGER)&TotalNumberOfFreeBytes
        );

        if (Flag) {
           //ShowMessage("Свободно на диске: " + tString(TotalNumberOfFreeBytes));
           //ShowMessage("Всего на диске: " + tString(TotalNumberOfBytes));
        } else {
           //ShowMessage("Ошибка в GetDiskFreeSpaceEx");
        }

        GetVolumeInformation((asDriveLetter + "\\").c_str(), cDriveLabel, 255, &drive_sn, NULL, NULL, NULL, NULL);
        ////ShowMessage(drive_sn);


        //заполняем cboeLocalDrives
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

    //устанавливаем в cboeLocalDrives текущий диск
    for (int i = 0; i < cboeLocalDrives->Items->Count; i ++) {
        if (ExtractFileDrive(Application->ExeName) == cboeLocalDrives->Items->Strings[i].SetLength(2)) {     //ShowMessage(asCurrentFileDrive);
            cboeLocalDrives->ItemIndex = i;
        }
    }
}
