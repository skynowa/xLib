/**********************************************************************
*   doPrepare_pnlOtpusk()
*
***********************************************************************/

void __fastcall doPrepare_pnlOtpusk() {
    //��������� ����
    if (FileExists("Base.txt")) {
        cboFIO_2->Items->LoadFromFile("Base.txt");
    } else {
        StatusBar1->SimpleText = " ��� ���� � ���������.";
    }
    cboFIO_2->Text = "...�������...";
    cboFIO_2->DropDownCount = cboFIO_2->Items->Count;

    //���������
    cboStatus_2->Text = "����������";
    cboStatus_2->DropDownCount = 20; //cboStatus_2->Items->Count;

    //�
    dtpDayBegin_2->DateTime = Now().DateString();
    ////cboDayBegin_2->Text = Date().FormatString("dd");
    ////cboDayBegin_2->DropDownCount = cboDayBegin_2->Items->Count;
    ////cboMonthBegin_2->ItemIndex = StrToInt(Date().FormatString("mm")) - 1;
    ////cboMonthBegin_2->DropDownCount = cboMonthBegin_2->Items->Count;

    //��
    dtpDayEnd_2->DateTime = Now().DateString();  
    ////cboDayEnd_2->Text = Date().FormatString("dd");
    ////cboDayEnd_2->DropDownCount = cboDayEnd_2->Items->Count;
    ////cboMonthEnd_2->ItemIndex = StrToInt(Date().FormatString("mm")) - 1;
    ////cboMonthEnd_2->DropDownCount = cboMonthEnd_2->Items->Count;

    //�������
    cboReason_2->Text = "";
    cboReason_2->DropDownCount = cboReason->Items->Count;

    //��� �������������
    cboAdvokat_2->Text = "������ �.�.";
    cboAdvokat_2->DropDownCount = cboAdvokat_2->Items->Count;
}