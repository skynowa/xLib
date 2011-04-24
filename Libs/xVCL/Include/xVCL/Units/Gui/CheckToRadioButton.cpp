/***********************************************************************
*   
*
************************************************************************/


//---------------------------------------------------------------------------
void __fastcall chkDicAttackClick(TObject *Sender) {
    if (chkDicAttack->Checked == true) {
        chkLatinCharsUpperAttack->Checked   = false;
        chkLatinCharsLowerAttack->Checked   = false;
        chkRussianCharsUpperAttack->Checked = false;
        chkRussianCharsLowerAttack->Checked = false;
        chkDigitsAttack->Checked            = false;
        chkSpecialCharsAttack->Checked      = false;
        chkCustomCharsAttack->Checked       = false;
        chkSpaceCharAttack->Checked         = false;
        //chkDicAttack->Checked               = false;

        //блокируем вкладку
        bvlDictionary->Enabled              = true;
        lvwDicFiles->Enabled                = true; lvwDicFiles->Color = clWhite;
        btnAdd_lvwDicFiles->Enabled         = true;
        btnDelete_lvwDicFiles->Enabled      = true;
        btnMoveUp_lvwDicFiles->Enabled      = true;
        btnMoveDown_lvwDicFiles->Enabled    = true;
        btnBrowse_lvwDicFiles->Enabled      = true;
        btnDeleteAll_lvwDicFiles->Enabled   = true;
    } else {
        bvlDictionary->Enabled              = false;
        lvwDicFiles->Enabled                = false;   lvwDicFiles->Color = clBtnFace;
        btnAdd_lvwDicFiles->Enabled         = false;
        btnDelete_lvwDicFiles->Enabled      = false;
        btnMoveUp_lvwDicFiles->Enabled      = false;
        btnMoveDown_lvwDicFiles->Enabled    = false;
        btnBrowse_lvwDicFiles->Enabled      = false;
        btnDeleteAll_lvwDicFiles->Enabled   = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall chkLatinCharsUpperAttackClick(TObject *Sender) {
    if (chkLatinCharsUpperAttack->Checked == true) {
        //chkLatinCharsUpperAttack->Checked   = false;
        chkLatinCharsLowerAttack->Checked   = false;
        chkRussianCharsUpperAttack->Checked = false;
        chkRussianCharsLowerAttack->Checked = false;
        chkDigitsAttack->Checked            = false;
        chkSpecialCharsAttack->Checked      = false;
        chkCustomCharsAttack->Checked       = false;
        chkSpaceCharAttack->Checked         = false;
        chkDicAttack->Checked               = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall chkLatinCharsLowerAttackClick(TObject *Sender) {
    if (chkLatinCharsLowerAttack->Checked == true) {
        chkLatinCharsUpperAttack->Checked   = false;
        //chkLatinCharsLowerAttack->Checked   = false;
        chkRussianCharsUpperAttack->Checked = false;
        chkRussianCharsLowerAttack->Checked = false;
        chkDigitsAttack->Checked            = false;
        chkSpecialCharsAttack->Checked      = false;
        chkCustomCharsAttack->Checked       = false;
        chkSpaceCharAttack->Checked         = false;
        chkDicAttack->Checked               = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall chkRussianCharsUpperAttackClick(TObject *Sender) {
    if (chkRussianCharsUpperAttack->Checked == true) {
        chkLatinCharsUpperAttack->Checked   = false;
        chkLatinCharsLowerAttack->Checked   = false;
        //chkRussianCharsUpperAttack->Checked = false;
        chkRussianCharsLowerAttack->Checked = false;
        chkDigitsAttack->Checked            = false;
        chkSpecialCharsAttack->Checked      = false;
        chkCustomCharsAttack->Checked       = false;
        chkSpaceCharAttack->Checked         = false;
        chkDicAttack->Checked               = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall chkRussianCharsLowerAttackClick(TObject *Sender) {
    if (chkRussianCharsLowerAttack->Checked == true) {
        chkLatinCharsUpperAttack->Checked   = false;
        chkLatinCharsLowerAttack->Checked   = false;
        chkRussianCharsUpperAttack->Checked = false;
        //chkRussianCharsLowerAttack->Checked = false;
        chkDigitsAttack->Checked            = false;
        chkSpecialCharsAttack->Checked      = false;
        chkCustomCharsAttack->Checked       = false;
        chkSpaceCharAttack->Checked         = false;
        chkDicAttack->Checked               = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall chkDigitsAttackClick(TObject *Sender) {
    if (chkDigitsAttack->Checked == true) {
        chkLatinCharsUpperAttack->Checked   = false;
        chkLatinCharsLowerAttack->Checked   = false;
        chkRussianCharsUpperAttack->Checked = false;
        chkRussianCharsLowerAttack->Checked = false;
        //chkDigitsAttack->Checked            = false;
        chkSpecialCharsAttack->Checked      = false;
        chkCustomCharsAttack->Checked       = false;
        chkSpaceCharAttack->Checked         = false;
        chkDicAttack->Checked               = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall chkSpecialCharsAttackClick(TObject *Sender) {
    if (chkSpecialCharsAttack->Checked == true) {
        chkLatinCharsUpperAttack->Checked   = false;
        chkLatinCharsLowerAttack->Checked   = false;
        chkRussianCharsUpperAttack->Checked = false;
        chkRussianCharsLowerAttack->Checked = false;
        chkDigitsAttack->Checked            = false;
        //chkSpecialCharsAttack->Checked      = false;
        chkCustomCharsAttack->Checked       = false;
        chkSpaceCharAttack->Checked         = false;
        chkDicAttack->Checked               = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall chkCustomCharsAttackClick(TObject *Sender) {
    if (chkCustomCharsAttack->Checked == true) {
        chkLatinCharsUpperAttack->Checked   = false;
        chkLatinCharsLowerAttack->Checked   = false;
        chkRussianCharsUpperAttack->Checked = false;
        chkRussianCharsLowerAttack->Checked = false;
        chkDigitsAttack->Checked            = false;
        chkSpecialCharsAttack->Checked      = false;
        //chkCustomCharsAttack->Checked       = false;
        chkSpaceCharAttack->Checked         = false;
        chkDicAttack->Checked               = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall chkSpaceCharAttackClick(TObject *Sender) {
    if (chkSpaceCharAttack->Checked == true) {
        chkLatinCharsUpperAttack->Checked   = false;
        chkLatinCharsLowerAttack->Checked   = false;
        chkRussianCharsUpperAttack->Checked = false;
        chkRussianCharsLowerAttack->Checked = false;
        chkDigitsAttack->Checked            = false;
        chkSpecialCharsAttack->Checked      = false;
        chkCustomCharsAttack->Checked       = false;
        //chkSpaceCharAttack->Checked         = false;
        chkDicAttack->Checked               = false;
    }
}
//---------------------------------------------------------------------------

