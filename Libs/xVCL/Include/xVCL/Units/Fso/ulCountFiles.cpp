/**********************************************************************
*	считаем все файлы (для полосы прогресса)(принимаем корневую папку [txtInFolder->Text+"\\"])
*
***********************************************************************/


//---------------------------------------------------------------------------
unsigned long int __fastcall ulCountFiles(tString asFolderPath) {	//TODO: Принимаем корневую папку
    TSearchRec sr;  memset(&sr, 0, sizeof(sr));

	if (FindFirst(asFolderPath + "*.*", faAnyFile, sr) == 0) {
		do {
			Application->ProcessMessages();
			if (sr.Attr & faDirectory) {
				if (sr.Name != ".") { //папки
                    if (sr.Name != "..") { //ShowMessage(sr.Name);
						ulCountFiles(asFolderPath + sr.Name + "\\");
					}
			    }
			} else {  //файлы
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
