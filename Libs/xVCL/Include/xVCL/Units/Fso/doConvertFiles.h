/**********************************************************************
*   ��������� ���� (��������� ����)   
*
***********************************************************************/

void __fastcall doConvertFiles(tString asFilePath) {	
    Application->ProcessMessages();

    //��� ��������
    if (iFlagStop == 1) {
        btnStop->Visible = false;
        return;
    }

    gauProgress->Progress ++;
    staInfo->SimpleText = "����:  " + MinimizeName(asFilePath, staInfo->Canvas, 180);

	//��� ����� �� ���������
	tString asExt = ExtractFileExt(asFilePath).UpperCase();
	tString asFileName = ExtractFileExt(asFilePath).UpperCase();

	if (asExt == ".DOC" || asExt == ".RTF") {                    //ChangeFileExt( Application->ExeName, ".INI" )
        //DOC -> TXT
        Variant vWordBasic = Variant::CreateObject("Word.Basic");
        ////vWordBasic.Exec(PropertySet("Visible") << false);

        //���� �� ���������
        PROCESSENTRY32 PC32;
	    HANDLE hnd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	    if ((int)hnd == -1) {
		    return;
	    }
	    PC32.dwSize = sizeof(PC32);
	    int i = Process32First(hnd, &PC32);

        bool bIsWordExists = false; //������� WINWORD.EXE

        while (bIsWordExists == true) {
	        while (i) {
		        // PID �������� ������ �� PC32.th32ProcessID;
		        // ��� ����� ����� ExtractFileName(PC32.szExeFile);
		        i = Process32Next(hnd, &PC32);  //ShowMessage(tString(PC32.szExeFile));
                if (tString(PC32.szExeFile).UpperCase() == "WINWORD.EXE") {
                    bIsWordExists = true;
                }
	        };
        }
	    CloseHandle(hnd);

        vWordBasic.Exec(Procedure("FileOpen")   << asFilePath);                               Sleep(SLEEP_TIME);
        vWordBasic.Exec(Procedure("FileSaveAs") << ChangeFileExt(asFilePath, ".txt") << 3);   Sleep(SLEEP_TIME);
        vWordBasic.Exec(Procedure("AppClose"));

        //����� ������ read-only
        FileSetAttr(asFilePath, 0);
        //������� ����
        do {
            DeleteFile(asFilePath);
        }
        while (FileExists(asFilePath));
	}
}
