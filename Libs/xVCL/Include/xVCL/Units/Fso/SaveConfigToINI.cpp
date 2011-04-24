/***********************************************************************
*   Сохраняем настройки в ini-файле
*
************************************************************************/


void __fastcall SaveConfigToINI() {
	//создаём и записываем в ini-файл
	TIniFile *pINI	= new TIniFile(ChangeFileExt(Application->ExeName, ".INI"));

	//секция [Settings]
	pINI->WriteString("Settings", "CurrentLink", "");
	pINI->WriteString("Settings", "Share", "");
	pINI->WriteString("Settings", "User", "");
	pINI->WriteString("Settings", "Password", "");


	delete pINI;
}
