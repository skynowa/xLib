/**********************************************************************
*   ищем все папки (принимаем корневую папку [txtInFolder->Text + "\\"])   
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vListFiles(const tString &casFolderPath) {
    Application->ProcessMessages();

    TSearchRec sr;   memset(&sr, 0, sizeof(sr));
	if (FindFirst(casFolderPath + "*.*", faAnyFile, sr) == 0) {
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
					if (sr.Name != "..") {    //папки   //ShowMessage(sr.Name);
						vListFiles(casFolderPath + sr.Name + "\\");
					}
				}
			} else {  //файлы   //ShowMessage(sr.Name);
                gauProgress->Progress ++;
                staInfo->SimpleText = "Файл:  " + MinimizeName(casFolderPath + sr.Name, staInfo->Canvas, 180);

                bool bRes = bConvertHtmlToText(CppWebBrowser1, casFolderPath + sr.Name, ChangeFileExt(casFolderPath + sr.Name, ".txt"), true); //конвертим
                if (bRes == false) {
                    MessageBox(0, ("Не могу конвертировать файл:\n" + casFolderPath + sr.Name).c_str(), Application->Title.c_str(), MB_OK + MB_ICONSTOP);
                }

			}
		} 
		while(FindNext(sr) == 0);
		FindClose(sr);	
	}
}
//---------------------------------------------------------------------------
