/***********************************************************************
*   ������. �������� �����
*
************************************************************************/


extern TfrmToolTip *frmToolTip;

void __fastcall TfrmToolTip::HideToolTip() {
    //��������
    AnimateWindow(frmToolTip->Handle, 280, AW_HIDE | AW_BLEND | AW_CENTER);
    frmToolTip->Hide();
    frmToolTip->Repaint();
}
