/***********************************************************************
*   ��������� ��������� � ini-�����
*
************************************************************************/


void __fastcall SaveConfigToINI() {
	//������ � ���������� � ini-����
	TIniFile *pINI	= new TIniFile(ChangeFileExt(Application->ExeName, ".INI"));

	//������ [Settings]
	pINI->WriteString("Settings", "CurrentLink", "");
	pINI->WriteString("Settings", "Share", "");
	pINI->WriteString("Settings", "User", "");
	pINI->WriteString("Settings", "Password", "");


	delete pINI;
}
