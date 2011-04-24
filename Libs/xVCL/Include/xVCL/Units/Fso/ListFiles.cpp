/**********************************************************************
*   ищем все папки (принимаем корневую папку [txtInFolder->Text + "\\"])   
*
***********************************************************************/


void __fastcall ListFiles(const tString &asFolderPath) {
    Application->ProcessMessages();

    TSearchRec sr;
	if (FindFirst(asFolderPath + "*.*", faAnyFile, sr) == 0) {
		do {
            Application->ProcessMessages();

            //для останова
            if (iFlagStop == 1) {
                btnStop->Visible = false;
                return;
            }

			//для останова //if (cmdConvert->Caption=="Конверт"){break;}
			if (sr.Attr & faDirectory) {
				if (sr.Name != ".") {
					if (sr.Name != "..") {      //папки   //ShowMessage(sr.Name);
						ListFiles(asFolderPath + sr.Name + "\\");
					}
				}
			} else {                            //файлы   //ShowMessage(sr.Name);
                tString asFilePath = asFolderPath + sr.Name;

                //показываем прогресс
                ////frmMain->Caption = gauProgress->Progress;
                gauProgress->Progress ++;
                staInfo->SimpleText = "Файл:  " + MinimizeName(asFilePath, staInfo->Canvas, 180);

                //конверт
                Convert(asFilePath);
			} //if
		} //do
		while(FindNext(sr) == 0);
		FindClose(sr);	
	}
}
