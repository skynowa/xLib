/***********************************************************************
*	—оздать текстовое поле
*
************************************************************************/

void __fastcall CreateComboBox(const int &iTop, const int &iLeft) {
    edtFromTo_lvwDicFiles = new TEdit(lvwDicFiles);
    //edtFromTo_lvwDicFiles->Name = "edt";
    edtFromTo_lvwDicFiles->Parent = lvwDicFiles;
    //edtFromTo_lvwDicFiles->Font->Height = 10;
    edtFromTo_lvwDicFiles->Height = 18;
    edtFromTo_lvwDicFiles->Width = lvwDicFiles->Columns->Items[2]->Width + 4;
    edtFromTo_lvwDicFiles->Top = iTop;
    edtFromTo_lvwDicFiles->Left = iLeft;
    /*lstvwDictionaryFiles->Columns->Items[0]->Width + \
    lstvwDictionaryFiles->Columns->Items[1]->Width + \
    lstvwDictionaryFiles->Columns->Items[2]->Width + 6;*/
    edtFromTo_lvwDicFiles->BorderStyle = bsNone;
    edtFromTo_lvwDicFiles->BevelKind = bkFlat;
    edtFromTo_lvwDicFiles->Enabled = true;

    //событи€
    edtFromTo_lvwDicFiles->OnExit = ComboBoxExit;
    edtFromTo_lvwDicFiles->OnKeyDown = ComboBoxKeyDown;

    //заполн€ем ComboBox
    int iSelIndex = lvwDicFiles->Selected->Index;
    edtFromTo_lvwDicFiles->Text = lvwDicFiles->Items->Item[iSelIndex]->SubItems->Strings[2];

    edtFromTo_lvwDicFiles->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall ComboBoxExit(TObject *Sender) {
    //--- проверка ---
    //--- проверка ---
    
    //записуем в €чейки ListView
    int iSelIndex = lvwDicFiles->Selected->Index;
    lvwDicFiles->Items->Item[iSelIndex]->SubItems->Strings[2] = edtFromTo_lvwDicFiles->Text;
    ////lvwDicFiles->Items->Item[iSelIndex]->SubItems->Strings[3] = edtFromTo_lvwDicFiles->Text;

    ///edtFromTo_lvwDicFiles->Hide();
    RemoveComboBox();
}
//---------------------------------------------------------------------------
void __fastcall ComboBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
     if (Key == 13) {
        /////lvwDicFiles->SetFocus();
        edtFromTo_lvwDicFiles->Hide();
     }
    /*if (Key == 13) {    //если нажали "Enter"
        //записуем в €чейки ListView
        if (edtFromTo_lvwDicFiles->Text == "") {
            MessageBox(NULL, "Range is not proper set", "LAN Hack++", 0 | 16 | 0 | 0 | 262144); return;
        }
        int iSelIndex = lvwDicFiles->Selected->Index;
        lvwDicFiles->Items->Item[iSelIndex]->SubItems->Strings[2] = edtFromTo_lvwDicFiles->Text;
        ////lvwDicFiles->Items->Item[iSelIndex]->SubItems->Strings[3] = edtFromTo_lvwDicFiles->Text;

        //lvwDicFiles->SetFocus();
        //doRemoveComboBox();
    } */
}
//---------------------------------------------------------------------------
