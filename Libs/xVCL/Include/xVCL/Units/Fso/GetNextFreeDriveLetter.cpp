/*********************************************************************************************************
*	������� ��������� ��������� ����� �����
*
**********************************************************************************************************/


tString __fastcall GetNextFreeDriveLetter() {
	DWORD dwNextFreeDriveLetter = GetLogicalDrives();    //������� ���������� ������� �����
	for (int i = 0; i < 26; i ++) {                   	 //���������� ������ �� �����
		int n = (dwNextFreeDriveLetter >> i) & 1;    	 //����� �������� �������� ����
		tString asDriveLetter = (char)(65 + i);   	 //�������� ������ �����
		if (n) {
			//���� ������� - ���� � ������� i ����
			//tString path = tString((char)(65+i)) + ":\\";
			//tString out = "���� " + DriveLetter + "\n";
			//ShowMessage(out);
		} else {
			if (asDriveLetter > 'B') {
				return asDriveLetter;
			}
		}
	}
    return 0;
}

