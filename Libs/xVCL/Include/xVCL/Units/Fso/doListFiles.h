/**********************************************************************
*   ���� ��� ����� (��������� �������� ����� [txtInFolder->Text + "\\"])   
*
***********************************************************************/

void __fastcall doListFiles(tString asFolderPath) {
    Application->ProcessMessages();

    TSearchRec sr;
	if (FindFirst(asFolderPath + "*.*", faAnyFile, sr) == 0) {
		do {
            Application->ProcessMessages();

            //��� ��������
            if (iFlagStop == 1) {
                btnStop->Visible = false;
                return;
            }

			//��� �������� //if (cmdConvert->Caption=="�������"){break;}
			if (sr.Attr & faDirectory) {
				if (sr.Name != ".") {
					if (sr.Name != "..") {    //�����   //ShowMessage(sr.Name);
						doListFiles(asFolderPath + sr.Name + "\\");
					}
				}
			} else {  //�����   //ShowMessage(sr.Name);
                gauProgress->Progress ++;
                staInfo->SimpleText = "����:  " + MinimizeName(asFolderPath + sr.Name, staInfo->Canvas, 180);

                //��� ����� �� ���������
                tString asExt = ExtractFileExt(sr.Name).UpperCase();
                tString asFileName = ExtractFileExt(sr.Name).UpperCase();

                if (asExt == ".DOC" || asExt == ".RTF") { 
			        //DOC -> TXT
                    Variant vWordBasic = Variant::CreateObject("Word.Basic");
                    vWordBasic.Exec(Procedure("FileOpen")   << asFolderPath + sr.Name);                               Sleep(SLEEP_TIME);
                    vWordBasic.Exec(Procedure("FileSaveAs") << ChangeFileExt(asFolderPath + sr.Name, ".txt") << 3);   Sleep(SLEEP_TIME);
                    vWordBasic.Exec(Procedure("AppClose"));

                    //����� ������ read-only
                    FileSetAttr(asFolderPath + sr.Name, 0);
                    //������� ����
                    do {
                        DeleteFile(asFolderPath + sr.Name);
                    }
                    while (FileExists(asFolderPath + sr.Name));
	            }
			} //if
		} //do
		while(FindNext(sr) == 0);
		FindClose(sr);	
	}
}
