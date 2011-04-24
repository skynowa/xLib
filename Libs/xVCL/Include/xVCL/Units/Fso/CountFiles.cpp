/**********************************************************************
*	считаем все файлы (для полосы прогресса)(принимаем корневую папку [txtInFolder->Text+"\\"])
*
***********************************************************************/


unsigned int __fastcall CountFiles(const tString &asFolderPath) {	//TODO: Принимаем корневую папку
    TSearchRec sr;

	if (FindFirst(asFolderPath + "*.*", faAnyFile, sr) == 0) {
		do {
			Application->ProcessMessages();
			if (sr.Attr & faDirectory) {
				if (sr.Name != ".") { //папки
                    if (sr.Name != "..") { //ShowMessage(sr.Name);
						CountFiles(asFolderPath + sr.Name + "\\");
					}
			    }
			} else {  //файлы
                tString asFileExt = ExtractFileExt(ExtractFileName(asFolderPath + sr.Name)).UpperCase();
                if (asFileExt == ".HTM"   ||
                    asFileExt == ".HTML"  || 
                    asFileExt == ".HTA"   ||
                    asFileExt == ".PHTM"  ||
                    asFileExt == ".PHTML" ||
                    asFileExt == ".SHTM"  ||
                    asFileExt == ".SHTML" ||
                    asFileExt == ".SPM"   ||
                    asFileExt == ".SPML"  ||
                    asFileExt == ".STM"   ||
                    asFileExt == ".STML"  ||
                    asFileExt == ".ASP"   || 
                    asFileExt == ".PHP"	  ||
                    asFileExt == ".PHP3"  ||
                    asFileExt == ".PHP4"  ||
                    asFileExt == ".ASP"   ||
                    asFileExt == ".JSP"   ||
                    asFileExt == ".CFM"   ||
                    asFileExt == ".CFML"  ||
                    asFileExt == ".CGI"   ||
                    asFileExt == ".HTT"   ||
                    asFileExt == ".DHTML" ||
                    asFileExt == ".SPML"  ||
                    asFileExt == ".STML"  ||
                    asFileExt == ".JHTML" ||
                    asFileExt == ".ASA"   ||
                    asFileExt == ".ASPX"  ||
                    asFileExt == ".ASAX"  ||
                    asFileExt == ".ASCX"  ||
                    asFileExt == ".ASMX"
                ) {
    				iCountFiles ++;
                }
			} //if
		} //do
		while(FindNext(sr) == 0);
		FindClose(sr);	
	}
    //ShowMessage(iCountFiles);
    return iCountFiles;
}
