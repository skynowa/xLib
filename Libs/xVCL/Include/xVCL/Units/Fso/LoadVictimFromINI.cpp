/***********************************************************************
*   Загружаем настройки с ini-файла
*
************************************************************************/


void __fastcall LoadVictimFromINI() {
    //читаем с ini-файла
    TStringList* pINIList = new TStringList;
	TIniFile*    pINI     = new TIniFile(ledtAutoSaveFile->Text);
    pINI->ReadSectionValues("Victim", pINIList);

    //---------------------
    //зополняем глоб. переменные статистики
    asHost                 = pINI->ReadString("Victim",    "Host",             pINIList->Values["Host"]);
    asShare                = pINI->ReadString("Victim",    "Share",            pINIList->Values["Share"]);
    asUser                 = pINI->ReadString("Victim",    "User",             pINIList->Values["User"]);
    asTypeOfAttack         = pINI->ReadString("Brute",     "TypeOfAttack",     pINIList->Values["TypeOfAttack"]);
    asAttackFrom           = pINI->ReadString("Brute",     "From",             pINIList->Values["From"]);
    asAttackTo             = pINI->ReadString("Brute",     "To",               pINIList->Values["To"]);
    asPosition             = pINI->ReadString("Statistic", "Position",         pINIList->Values["Position"]);
    asTotalProgress        = pINI->ReadString("Statistic", "Total progress",   pINIList->Values["Total progress"]);;
    asCurrentPassword      = pINI->ReadString("Statistic", "Current password", pINIList->Values["Current password"]);
    asTotalPasswords       = pINI->ReadString("Statistic", "Total passwords",  pINIList->Values["Total passwords"]);
    asDonePasswords        = pINI->ReadString("Statistic", "Done passwords",   pINIList->Values["Done passwords"]);	 //int iCountCheckedPasswords = 0;    //кол-во перебранных паролей
    asSpeed                = pINI->ReadString("Statistic", "Speed",            pINIList->Values["Speed"]);
    asErrorCode            = pINI->ReadString("Statistic", "Error code",       pINIList->Values["Error code"]);
    asDoneTime             = pINI->ReadString("Statistic", "Time done",        pINIList->Values["Time done"]);   //определено в таймере
    //---------------------

    //секция [Victim]
	cboHost->Text     = asHost;
    cboShare->Text    = asShare;
	cboUser->Text     = asUser;

    //секция [Brute]

    //(A-Z)
    if (asTypeOfAttack == "LatinCharsUpper") {
        chkLatinCharsUpperAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

		//полоса прогресса (prgMain)
		//prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Progress", pINIList->Values["prgStatusAttack->Position"]));
    }
    //(a-z)
	if (asTypeOfAttack == "LatinCharsLower") {
        chkLatinCharsLowerAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

        //полоса прогресса (prgMain)
		//prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Progress", pINIList->Values["prgStatusAttack->Position"]));

	}
    //(А-Я)
	if (asTypeOfAttack == "RussianCharsUpper") {
        chkRussianCharsUpperAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

        //полоса прогресса (prgMain)
		//prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Progress", pINIList->Values["prgStatusAttack->Position"]));
	}
    //(а-я)
	if (asTypeOfAttack == "RussianCharsLower") {
        chkRussianCharsLowerAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

       	//полоса прогресса (prgMain)
	   	//prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Progress", pINIList->Values["prgStatusAttack->Position"]));
	}
    //(0-9)
	if (asTypeOfAttack == "Digits") {
        chkDigitsAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

       	//полоса прогресса (prgMain)
		prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Position", pINIList->Values["prgStatusAttack->Position"]));
	}         
    //Special symbols
	if (asTypeOfAttack == "SpecialChars") {
        chkSpecialCharsAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

        //полоса прогресса (prgMain)
		//prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Progress", pINIList->Values["prgStatusAttack->Position"]));
	}
    //Custom
	if (asTypeOfAttack == "CustomChars") {
        chkCustomCharsAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

        //полоса прогресса (prgMain)
		//prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Progress", pINIList->Values["prgStatusAttack->Position"]));
	}
    //Space
	if (asTypeOfAttack == "SpaceChar") {
        chkSpaceCharAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

        //полоса прогресса (prgMain)
		//prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Progress", pINIList->Values["prgStatusAttack->Position"]));
	}
    //Dictionary files
	if (asTypeOfAttack == "Dic") {
        chkDicAttack->Checked = true;
        edtAttackFrom->Text = asAttackFrom;
        edtAttackTo->Text   = asAttackTo;

       	//полоса прогресса (prgMain)
		//prgStatusAttack->Max            = edtAttackTo->Text.ToInt() - edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Min            = edtAttackFrom->Text.ToInt();
		//prgStatusAttack->Position       = StrToInt(pINI->ReadString("Statistic", "Progress", pINIList->Values["prgStatusAttack->Position"]));
	}

	//секция [Statistic]
    prgStatusAttack->Position     = asPosition.ToIntDef(0);
    lblStatusAttack->Caption      = asTotalProgress;
	lblS_CurrentPassword->Caption = asCurrentPassword;
	lblS_TotalPasswords->Caption  = asTotalPasswords;
	lblS_DonePasswords->Caption   = asDonePasswords;
	lblS_Speed->Caption           = asSpeed;
	lblS_ErrorCode->Caption       = asErrorCode;
	lblS_TimeDone->Caption        = asDoneTime;

	delete pINIList;
    delete pINI;
}
