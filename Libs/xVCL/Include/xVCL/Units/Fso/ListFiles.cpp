/**********************************************************************
*   ���� ��� ����� (��������� �������� ����� [txtInFolder->Text + "\\"])   
*
***********************************************************************/


void __fastcall ListFiles(const tString &asFolderPath) {
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
					if (sr.Name != "..") {      //�����   //ShowMessage(sr.Name);
						ListFiles(asFolderPath + sr.Name + "\\");
					}
				}
			} else {                            //�����   //ShowMessage(sr.Name);
                tString asFilePath = asFolderPath + sr.Name;

                //���������� ��������
                ////frmMain->Caption = gauProgress->Progress;
                gauProgress->Progress ++;
                staInfo->SimpleText = "����:  " + MinimizeName(asFilePath, staInfo->Canvas, 180);

                //�������
                Convert(asFilePath);
			} //if
		} //do
		while(FindNext(sr) == 0);
		FindClose(sr);	
	}
}
