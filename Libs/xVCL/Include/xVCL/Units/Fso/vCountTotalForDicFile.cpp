/***********************************************************************
*	���������� ����� ���-�� ������,  �����, ��������
*
************************************************************************/


//---------------------------------------------------------------------------
void __fastcall vCountTotalForDicFile() {
    //�������� Total-�
    lblTotalFiles->Caption = 0;
    lblTotalLines->Caption = 0;
    lblTotalSize->Caption  = "0 (Mb)";

    //����������
    for (int i = 0; i < lvwDicFiles->Items->Count; i ++) {  Application->ProcessMessages();
        //����� ������
        lblTotalFiles->Caption = lblTotalFiles->Caption.ToInt() + 1;
        //����� �����
        lblTotalLines->Caption = lblTotalLines->Caption.ToInt() + lvwDicFiles->Items->Item[i]->SubItems->Strings[0].ToInt();
        //����� ��������
        lblTotalSize->Caption = tString((lblTotalSize->Caption.SubString(0, lblTotalSize->Caption.Length() - 5)).ToDouble() + (lvwDicFiles->Items->Item[i]->SubItems->Strings[1]).ToDouble()) + " (Mb)";
    }
}
//---------------------------------------------------------------------------   
