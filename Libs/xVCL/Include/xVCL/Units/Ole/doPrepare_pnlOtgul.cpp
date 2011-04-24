/**********************************************************************
*   doPrepare_pnlOtgul()
*
***********************************************************************/

void __fastcall doPrepare_pnlOtgul() {
    //загружаем базу
    if (FileExists("Base.txt")) {
        cboFIO->Items->LoadFromFile(ExtractFileDir(Application->ExeName) + "\\Base.txt");
    } else {
        StatusBar1->SimpleText = " Нет базы с фамилиями.";
    }
    cboFIO->Text = "...Выбрать...";
    cboFIO->DropDownCount = 20; //cboFIO->Items->Count;

    //должность
    cboStatus->Text = "кладовщика";
    cboStatus->DropDownCount = cboStatus->Items->Count;

    //с
    cboTimeBegin->Text = "9-00";
    cboTimeBegin->DropDownCount = cboTimeBegin->Items->Count;

    //по
    cboTimeEnd->Text = "18-00";
    cboTimeEnd->DropDownCount = cboTimeEnd->Items->Count;

    //////////


    //день
    dtpDay->DateTime = Now().DateString();  

    ////cboDay->Text = Date().FormatString("dd");
    ////cboDay->DropDownCount = cboDay->Items->Count;

    //месяц
    ////DateTimePicker1

    ////cboMonth->ItemIndex = StrToInt(Date().FormatString("mm")) - 1;
    ////cboMonth->DropDownCount = cboMonth->Items->Count;

    //причина
    cboReason->Text = "за переработанные ранее часы";
    cboReason->DropDownCount = cboReason->Items->Count;

    //хто ходатайствует
    cboAdvokat->Text = "Осьмук В.Л.";
    cboAdvokat->DropDownCount = cboAdvokat->Items->Count;
}