/***********************************************************************
*   ������. �������� �����
*
************************************************************************/


extern TfrmToolTip *frmToolTip;

void __fastcall TfrmToolTip::ShowToolTip() {
    //���� ������� - ������� ������� � ��������
    frmToolTip->MoveFormToTaskbar();
    //���������� �����
    frmToolTip->BringToFrontWindow(frmToolTip->Handle);
    //��������
    AnimateWindow(frmToolTip->Handle, 280, AW_ACTIVATE  | AW_BLEND /*| AW_CENTER*/);
    frmToolTip->Show();
    frmToolTip->Repaint();
}
