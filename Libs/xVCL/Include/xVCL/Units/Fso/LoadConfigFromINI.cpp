/***********************************************************************
*   Загружаем настройки с ini-файла (для формы)
*
************************************************************************/


void __fastcall LoadConfigFromINI() {
    //существует ли config.ini?
    if (!FileExists(ExtractFilePath(Application->ExeName) + "Config.ini")) {
        //ShowMessage("Файл конфигурации window.ini не найден!");
        Top = Screen->Height / 4;
        Left = Screen->Width / 4;
    } else {
		//читаем с ini-файла
		TStringList *pINIList = new TStringList;
        TIniFile *pINI = new TIniFile(ExtractFilePath(Application->ExeName) + "Config.ini");

        //секция [Window]
		Top                 = StrToInt(pINI->ReadString("Window", "Top", pINIList->Values["Top"]));
		Left                = StrToInt(pINI->ReadString("Window", "Left", pINIList->Values["Left"]));
        hkyHideShow->HotKey = TextToShortCut(pINI->ReadString("Window", "HotKey", pINIList->Values["HotKey"]));
        //секция [...]
        //секция [...]

		delete pINIList;
		delete pINI;
    }  
}
