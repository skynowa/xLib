/***********************************************************************
*   ��������� ��������� � ini-����� (��� �����)
*
************************************************************************/


void __fastcall LoadConfigFromINI() {
    //���������� �� config.ini?
    if (!FileExists(ExtractFilePath(Application->ExeName) + "Config.ini")) {
        //ShowMessage("���� ������������ window.ini �� ������!");
        Top = Screen->Height / 4;
        Left = Screen->Width / 4;
    } else {
		//������ � ini-�����
		TStringList *pINIList = new TStringList;
        TIniFile *pINI = new TIniFile(ExtractFilePath(Application->ExeName) + "Config.ini");

        //������ [Window]
		Top                 = StrToInt(pINI->ReadString("Window", "Top", pINIList->Values["Top"]));
		Left                = StrToInt(pINI->ReadString("Window", "Left", pINIList->Values["Left"]));
        hkyHideShow->HotKey = TextToShortCut(pINI->ReadString("Window", "HotKey", pINIList->Values["HotKey"]));
        //������ [...]
        //������ [...]

		delete pINIList;
		delete pINI;
    }  
}
