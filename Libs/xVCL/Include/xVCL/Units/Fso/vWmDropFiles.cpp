/**********************************************************************
*   ��� ��������������
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vWmDropFiles(TWMDropFiles &Message) {
    //--- �������������� ---
    staInfo->SimpleText = "";
    //--- �������������� ---

	char szPath[256];   memset(szPath, 0, sizeof(szPath));
	HDROP hDrop = (HDROP)Message.Drop;
	int  iFiles = DragQueryFile(hDrop, -1, NULL, NULL);	//���������� ������,

	//���� ����� ������������� ���� ����, � ����� ����� ���������.
	for (int i = 0; i < iFiles; i ++) {
		DragQueryFile(hDrop, i, szPath, sizeof(szPath));
        pList->Add(szPath);  //������ ��� ���������������� �� ����� ����� (������� ����)
	}
	DragFinish(hDrop);

    btnStart->Click();
}
//---------------------------------------------------------------------------
