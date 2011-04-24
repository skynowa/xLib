/***********************************************************************
*	��������� ComboBoxEx �������, ������� ������
*
************************************************************************/

void __fastcall doDrivesToSpeedButton() {  //DONE: doDrivesToSpeedButton()
    ////cboeLocalDrives->Items->Clear();

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
//  DWORD dwNextFreeDriveLetter = GetLogicalDrives();    //������� ���������� ������� �����
//	for (int i = 0; i < 26; i ++) {                   	 //���������� ������ �� �����
//		int n = (dwNextFreeDriveLetter >> i) & 1;    	 //����� �������� �������� ����
//		tString asDriveLetter = (char)(65 + i);   	 //�������� ������ �����
//		if (n) {
//			//���� ������� - ���� � ������� i ����
//			//tString path = tString((char)(65+i)) + ":\\";
//			//tString out = "���� " + DriveLetter + "\n";
//
//			//ShowMessage(out);
//            tString dl = tString((char)(65 + i)); // �������� ������ �����
//            UINT drive_type = GetDriveType((dl + ":\\").c_str()); // ����� ��� �����
//            if (drive_type == DRIVE_CDROM) {
//                ////ShowMessage(drive_type);
//            }
//
//
//
//		}
//	}


    ////////////
    TSHFileInfo sfi;
    int iFlag = 0;

    while (*pBuf) {
        //���������� ��������������� ������
        int iIconIndex = -1;

        if (SHGetFileInfo(pBuf, 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX|SHGFI_SMALLICON)) {
                iIconIndex = sfi.iIcon;
        }

        asDriveLetter = pBuf;                                   //��������� ��� � tString
        pBuf += (asDriveLetter.Length() + 1) * sizeof(TCHAR);   //������� ��������� �� ��� ���������� �����
        asDriveLetter = StringReplace(asDriveLetter, "\\", EmptyStr, TReplaceFlags());  //������� ���� �� �����

        unsigned __int64 uiFreeBytesAvailable;
        unsigned __int64 uiTotalNumberOfBytes;
        unsigned __int64 uiTotalNumberOfFreeBytes;
        char             cDrive_Label[30];
        char             cDrive_Fat[30];
        DWORD            cDrive_SN;
        ////DWORD Rrive_Name_Size = sizeof(cDrive_Label);

        //�������� ������ � ��������
        bool bFlag = ::GetDiskFreeSpaceEx (
                         asDriveLetter.c_str(),
                         (PULARGE_INTEGER)&uiFreeBytesAvailable,
                         (PULARGE_INTEGER)&uiTotalNumberOfBytes,
                         (PULARGE_INTEGER)&uiTotalNumberOfFreeBytes
        );
        
        if (bFlag) {
           //ShowMessage("�������� �� �����: " + tString(uiTotalNumberOfBytes));
           //ShowMessage("����� �� �����: " + tString(uiTotalNumberOfBytes));
        } else {
           //ShowMessage("������ � GetDiskFreeSpaceEx");
        }

        GetVolumeInformation((asDriveLetter + "\\").c_str(), cDrive_Label, 255, &cDrive_SN, NULL, NULL, NULL, NULL);


        //��������� �������� ������ ������
        iFlag ++;
        switch (iFlag) {
            case 1:
                {
                    Graphics::TBitmap *pBitmap1 = new Graphics::TBitmap();
                    pBitmap1->Transparent = true;

                    cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap1);
                    sbtnDisk1->Glyph   = pBitmap1;
                    sbtnDisk1->Caption = asDriveLetter.Delete(2, 1);
                    sbtnDisk1->Hint    = "�����: "    + tString(cDrive_Label) + '\n' + 
                                         "��������: " + tString(uiTotalNumberOfFreeBytes / 1000000) + " Mb";
                    sbtnDisk1->Visible = true;

                    delete pBitmap1;
                }
            break;

            case 2:
                {
                    Graphics::TBitmap *pBitmap2 = new Graphics::TBitmap();
                    pBitmap2->Transparent = true;

                    cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap2);
                    sbtnDisk2->Glyph   = pBitmap2;
                    sbtnDisk2->Caption = asDriveLetter.Delete(2, 1);
                    sbtnDisk2->Hint    = "�����: "    + tString(cDrive_Label) + '\n' +
                                         "��������: " + tString(uiTotalNumberOfFreeBytes / 1000000) + " Mb";
                    sbtnDisk2->Visible = true;

                    delete pBitmap2;
                } 
            break;

            case 3:
                {
                    Graphics::TBitmap *pBitmap3 = new Graphics::TBitmap();
                    pBitmap3->Transparent = true;

                    cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap3);
                    sbtnDisk3->Glyph   = pBitmap3;
                    sbtnDisk3->Caption = asDriveLetter.Delete(2, 1);
                    sbtnDisk3->Hint    = "�����: "    + tString(cDrive_Label) + '\n' +
                                         "��������: " + tString(uiTotalNumberOfFreeBytes / 1000000) + " Mb";
                    sbtnDisk3->Visible = true;

                    delete pBitmap3;
                }
            break;

            case 4:
                {
                    Graphics::TBitmap *pBitmap4 = new Graphics::TBitmap();
                    pBitmap4->Transparent = true;

                    cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap4);
                    sbtnDisk4->Glyph   = pBitmap4;
                    sbtnDisk4->Caption = asDriveLetter.Delete(2, 1);
                    sbtnDisk4->Hint    = "�����: "    + tString(cDrive_Label) + '\n' +
                                         "��������: " + tString(uiTotalNumberOfFreeBytes / 1000000) + " Mb";
                    sbtnDisk4->Visible = true;

                    delete pBitmap4;
                } 
            break;

            case 5:
                {
                    Graphics::TBitmap *pBitmap5 = new Graphics::TBitmap();
                    pBitmap5->Transparent = true;

                    cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap5);
                    sbtnDisk5->Glyph   = pBitmap5;
                    sbtnDisk5->Caption = asDriveLetter.Delete(2, 1);
                    sbtnDisk5->Hint    = "�����: "    + tString(cDrive_Label) + '\n' +
                                         "��������: " + tString(uiTotalNumberOfFreeBytes / 1000000) + " Mb";
                    sbtnDisk5->Visible = true;

                    delete pBitmap5;
                }
            break;

            case 6:
                {
                    Graphics::TBitmap *pBitmap6 = new Graphics::TBitmap();
                    pBitmap6->Transparent = true;

                    cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap6);
                    sbtnDisk6->Glyph   = pBitmap6;
                    sbtnDisk6->Caption = asDriveLetter.Delete(2, 1);
                    sbtnDisk6->Hint    = "�����: "    + tString(cDrive_Label) + '\n' +
                                         "��������: " + tString(uiTotalNumberOfFreeBytes / 1000000) + " Mb";
                    sbtnDisk6->Visible = true;

                    delete pBitmap6;
                }
            break;

            case 7:
                {
                    Graphics::TBitmap *pBitmap7 = new Graphics::TBitmap();
                    pBitmap7->Transparent = true;

                    cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap7);
                    sbtnDisk7->Glyph   = pBitmap7;
                    sbtnDisk7->Caption = asDriveLetter.Delete(2, 1);
                    sbtnDisk7->Hint    = "�����: "    + tString(cDrive_Label) + '\n' +
                                         "��������: " + tString(uiTotalNumberOfFreeBytes / 1000000) + " Mb";
                    sbtnDisk7->Visible = true;

                    delete pBitmap7;
                }
            break;

            case 8:
                {
                    Graphics::TBitmap *pBitmap8 = new Graphics::TBitmap();
                    pBitmap8->Transparent = true;

                    cboeLocalDrives->Images->GetBitmap(iIconIndex, pBitmap8);
                    sbtnDisk8->Glyph   = pBitmap8;
                    sbtnDisk8->Caption = asDriveLetter.Delete(2, 1);
                    sbtnDisk8->Hint    = "�����: "    + tString(cDrive_Label) + '\n' +
                                         "��������: " + tString(uiTotalNumberOfFreeBytes / 1000000) + " Mb";
                    sbtnDisk8->Visible = true;

                    delete pBitmap8;
                } 
            break;

        }
    }
    delete[] Buf;
}           
