/**********************************************************************
*	������� ��� ����� (��� ������ ���������)(��������� �������� ����� [txtInFolder->Text+"\\"])
*
***********************************************************************/


//---------------------------------------------------------------------------
unsigned long int __fastcall ulCountFiles(tString asFolderPath) {	//TODO: ��������� �������� �����
    TSearchRec sr;  memset(&sr, 0, sizeof(sr));

	if (FindFirst(asFolderPath + "*.*", faAnyFile, sr) == 0) {
		do {
			Application->ProcessMessages();
			if (sr.Attr & faDirectory) {
				if (sr.Name != ".") { //�����
                    if (sr.Name != "..") { //ShowMessage(sr.Name);
						ulCountFiles(asFolderPath + sr.Name + "\\");
					}
			    }
			} else {  //�����
				iCountFiles ++;
			}
		} 
		while(FindNext(sr) == 0);
		FindClose(sr);	
	}
    //ShowMessage(iCountFiles);
    return iCountFiles;
}
//---------------------------------------------------------------------------
