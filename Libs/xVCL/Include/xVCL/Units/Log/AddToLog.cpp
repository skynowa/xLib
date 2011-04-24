/***********************************************************************
*   ��������� ������ � lvwLog � ����������
*
************************************************************************/


void __fastcall AddToLog(const int &iImageIndex, const tString &asLine) {
    lvwLog->Items->Add();
    lvwLog->Items->Item[lvwLog->Items->Count - 1]->StateIndex = iImageIndex;    //��������� ���������
    lvwLog->Items->Item[lvwLog->Items->Count - 1]->SubItems->Add(Now().CurrentTime());
    lvwLog->Items->Item[lvwLog->Items->Count - 1]->SubItems->Add(asLine);

    //������������ ������ ����
    SendMessage(lvwLog->Handle, WM_VSCROLL, MAKEWORD(SB_LINEDOWN, 0), 0);
}
