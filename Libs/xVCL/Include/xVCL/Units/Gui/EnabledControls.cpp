/***********************************************************************
*	Блокируем, разблокируем контролы
*
************************************************************************/


//void __fastcall BlockControls(bool Flag, tString Color);
void __fastcall EnabledControls(bool bFlag) {
    //fraVictim
    cboHost->Enabled                    = bFlag;
    btnHost->Enabled                    = bFlag;
    cboShare->Enabled                   = bFlag;
    cboUser->Enabled                    = bFlag;
    edtPassword->Enabled                = bFlag;

    //bvlBruteForce
    chkLatinCharsUpperAttack->Enabled   = bFlag;
    chkLatinCharsLowerAttack->Enabled   = bFlag;
    chkRussianCharsUpperAttack->Enabled = bFlag;
    chkRussianCharsLowerAttack->Enabled = bFlag;
    chkDigitsAttack->Enabled            = bFlag;
    chkSpecialCharsAttack->Enabled      = bFlag;
    cboSpecialCharsAttack->Enabled      = bFlag;
    chkCustomCharsAttack->Enabled       = bFlag;
    cboCustomCharsAttack->Enabled       = bFlag;
    chkSpaceCharAttack->Enabled         = bFlag;
    edtAttackFrom->Enabled              = bFlag;
    edtAttackTo->Enabled                = bFlag;
    edtMinChar->Enabled                 = bFlag;
    edtMaxChar->Enabled                 = bFlag;

    //bvlDictionary
    chkDicAttack->Enabled               = bFlag;
    lvwDicFiles->Enabled                = bFlag; if (bFlag == true) {lvwDicFiles->Color = clWhite;} else {lvwDicFiles->Color = clBtnFace;}
    btnAdd_lvwDicFiles->Enabled         = bFlag;
    btnDelete_lvwDicFiles->Enabled      = bFlag;
    btnMoveUp_lvwDicFiles->Enabled      = bFlag;
    btnMoveDown_lvwDicFiles->Enabled    = bFlag;
    btnBrowse_lvwDicFiles->Enabled      = bFlag;
    btnDeleteAll_lvwDicFiles->Enabled   = bFlag;

    //bvlAutoSave
    ledtAutoSaveFile->Enabled           = bFlag;
    btnSaveMenu->Enabled                = bFlag;
}         
