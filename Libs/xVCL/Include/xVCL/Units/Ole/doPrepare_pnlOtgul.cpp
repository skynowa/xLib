/**********************************************************************
*   doPrepare_pnlOtgul()
*
***********************************************************************/

void __fastcall doPrepare_pnlOtgul() {
    //��������� ����
    if (FileExists("Base.txt")) {
        cboFIO->Items->LoadFromFile(ExtractFileDir(Application->ExeName) + "\\Base.txt");
    } else {
        StatusBar1->SimpleText = " ��� ���� � ���������.";
    }
    cboFIO->Text = "...�������...";
    cboFIO->DropDownCount = 20; //cboFIO->Items->Count;

    //���������
    cboStatus->Text = "����������";
    cboStatus->DropDownCount = cboStatus->Items->Count;

    //�
    cboTimeBegin->Text = "9-00";
    cboTimeBegin->DropDownCount = cboTimeBegin->Items->Count;

    //��
    cboTimeEnd->Text = "18-00";
    cboTimeEnd->DropDownCount = cboTimeEnd->Items->Count;

    //////////


    //����
    dtpDay->DateTime = Now().DateString();  

    ////cboDay->Text = Date().FormatString("dd");
    ////cboDay->DropDownCount = cboDay->Items->Count;

    //�����
    ////DateTimePicker1

    ////cboMonth->ItemIndex = StrToInt(Date().FormatString("mm")) - 1;
    ////cboMonth->DropDownCount = cboMonth->Items->Count;

    //�������
    cboReason->Text = "�� �������������� ����� ����";
    cboReason->DropDownCount = cboReason->Items->Count;

    //��� �������������
    cboAdvokat->Text = "������ �.�.";
    cboAdvokat->DropDownCount = cboAdvokat->Items->Count;
}