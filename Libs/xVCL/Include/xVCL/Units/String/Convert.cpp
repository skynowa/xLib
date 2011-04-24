/**********************************************************************
*   Функция конверт ()
*
***********************************************************************/


void __fastcall Convert(const tString &asFilePath) {
    tString asFileExt = ExtractFileExt(ExtractFileName(asFilePath)).UpperCase();
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
        //----------------------------------------
        //читаем файл в переменную
        TStringList* pList = new TStringList;
        pList->LoadFromFile(asFilePath);

        //----------------------------------------
        //выбираем текст из <title>...</title>
        TRegExpr *pR = new TRegExpr;
        {
            pR->ModifierI = true;
            pR->ModifierM = false;
            pR->ModifierS = true;
            pR->ModifierX = false;
            pR->ModifierG = false;
            pR->ModifierR = true;

            //pR->Expression = "<title>.*</title>";
            pR->Expression = cboTag1->Text + ".*" + cboTag2->Text;
        }

        tString asNewFileName = "";

        if (pR->Exec(pList->Text)) {
            int iStartPos = 8;
            int iEndPos   = pR->Match[0].Length() - 15;
            asNewFileName = Trim(ReplaceFatalSymbols(pR->Match[0].SubString(iStartPos, iEndPos)));   //ShowMessage(asNewFileName);

            //длина имени файла 60 символов
            if (chkCutFileName->Checked == true) {
                if (asNewFileName.Length() > 60) {
                    asNewFileName.SetLength(60);
                }
            }                            
        }
        pR->Free();


        //переименовываем файл
        if (!RenameFile(asFilePath, FileExistsEx(ExtractFileDir(asFilePath) + "\\" +  asNewFileName + ".html"))) {
            MessageBox(NULL, ("Не могу переименовать файл:\n" + asFilePath).c_str(), Application->Title.c_str(), 0 | 16 | 0 | 0 | 262144);
        }

        delete pList;
    }
}
