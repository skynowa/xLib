/***********************************************************************
*	������� ��������� ����, ���� ��� ����
*
************************************************************************/

void __fastcall RemoveComboBox() {
    if (edtFromTo_lvwDicFiles) {
		delete edtFromTo_lvwDicFiles;
    }
    edtFromTo_lvwDicFiles = NULL;
}
