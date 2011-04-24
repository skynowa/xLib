/***********************************************************************
*   Сохраняем настройки в ini-файле
*
************************************************************************/


void __fastcall SaveVictimToINI() {
    //---------------------
//    //зополняем глоб. переменные статистики      //заполнять ли переменные??????
//    asHost                 = cboHost->Text;      //они уже заполнены
//    asShare                = cboShare->Text;
//    asUser                 = cboUser->Text;
//    asPassword             = edtPassword->Text;
//    ////asTypeOfAttack         =
//    asAttackFrom           = edtAttackFrom->Text;
//    asAttackTo             = edtAttackTo->Text;
//
//    asPosition             = prgStatusAttack->Position;
//    asStat_TotalProgress   = lblStatusAttack->Caption;
//    asCurrentPassword =
//    asStat_TotalPasswords  =
//    asStat_DonePasswords   =
//    asSpeed                =
//    asStat_ErrorCode       =
//    asStat_TimeDone        =
    //---------------------



	/*if (FileExists(txtAutoSaveFile->Text)) {
        int iResult = MessageBox(NULL, ("Файл: " + txtAutoSaveFile->Text + " уже существует.\nПерезаписать?\n").c_str(), "LAN Hack++", 3 | 48 | 256 | 0 | 262144);
        switch (iResult) {
	        case 6: //да - Перезаписать
	        break;
			 
	        case 7: //нет - Не перезаписывать (создать новый)
	        break;
			
	        case 2: //отмена
	        break;
        }
    } else {*/

        //создаём и записываем в ini-файл
        TIniFile *pINI = new TIniFile(ledtAutoSaveFile->Text);

        //секция [Victim]
        pINI->WriteString("Victim", "Host",     asHost);
        pINI->WriteString("Victim", "Share",    asShare);
        pINI->WriteString("Victim", "User",     asUser);

        //секция [Brute]
        //(A-Z)
        if (chkLatinCharsUpperAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "LatinCharsUpper");  
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }
        //(a-z)
        if (chkLatinCharsLowerAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "LatinCharsLower");
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }
        //(А-Я)
        if (chkRussianCharsUpperAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "RussianCharsUpper");
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }
        //(а-я)
        if (chkRussianCharsLowerAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "RussianCharsLower");
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }
        //(0-9)
        if (chkDigitsAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "Digits");
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }
        //Special symbols
        if (chkSpecialCharsAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "SpecialChars");
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }
        //Custom
        if (chkCustomCharsAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "CustomChars");
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }
        //Space
        if (chkSpaceCharAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "SpaceChar");
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }
        //Dictionary files
        if (chkDicAttack->Checked == true) {
            pINI->WriteString("Brute", "TypeOfAttack", "Dic");
            pINI->WriteString("Brute", "From",         asAttackFrom);
            pINI->WriteString("Brute", "To",           asAttackTo);
        }

	    //секция [Statistic]
        pINI->WriteString("Statistic", "Position",         asPosition);
        pINI->WriteString("Statistic", "Total progress",   asTotalProgress);
        pINI->WriteString("Statistic", "Current password", asCurrentPassword);
        pINI->WriteString("Statistic", "Total passwords",  asTotalPasswords);
        pINI->WriteString("Statistic", "Done passwords",   asDonePasswords);
        pINI->WriteString("Statistic", "Speed",            asSpeed);
        pINI->WriteString("Statistic", "Error code",       asErrorCode);
        pINI->WriteString("Statistic", "Time done",        asDoneTime);
        pINI->WriteString("Statistic", "Time remain",      asRemainTime);

        ////pINI->Flush();

        delete pINI;
    /*}*/
}
