/**********************************************************************
*   ��� ��������������
*
***********************************************************************/

extern TStringList* pList;

void __fastcall WmDropFiles(TWMDropFiles &Message) {
    //--- �������������� ---
    staInfo->SimpleText = "";
    //--- �������������� ---

	char cPath[256];
	HDROP hDrop = (HDROP)Message.Drop;
	int iFiles = DragQueryFile(hDrop, -1, NULL, NULL);	//���������� ������,

	//���� ����� ������������� ���� ����, � ����� ����� ���������.
	for (int i = 0; i < iFiles; i ++) {
		DragQueryFile(hDrop, i, cPath, sizeof(cPath));
        pList->Add(cPath);  //������ ��� ���������������� �� ����� ����� (������� ����)
	}
	DragFinish(hDrop);

    btnStart->Click();
    ////btnTest->Click();
}
