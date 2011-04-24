/**********************************************************************
*   DOS �� ���������?
*
***********************************************************************/

bool bIsDosEncoding(const tString &csFilePath) {
    //������ ����
    TStringList* pList = new TStringList;
    pList->LoadFromFile(csFilePath);
    tString asFile = pList->Text;    //������ ���� ����
    delete pList;

    tString asDosChars = "���������������������������������������������";    //���-������ �������
    int iCountSovpadeniya = 0;   //���-�� ����������
    int iMaxSovpadeniy    = asFile.Length() / (1000 * 6); //����. ����� ���������� (���� ������, �� ����� - ���)
    int iZoom             = 1;   //�� ������� ��� ��������� ����� ������

    for (int i = 1; i <= asDosChars.Length(); i ++) {    Application->ProcessMessages();
        for (int j = 1; j < asFile.Length() / iZoom; j ++) {    Application->ProcessMessages();
            if (asFile[j] == asDosChars[i]) {
                iCountSovpadeniya ++;
                if (iCountSovpadeniya > iMaxSovpadeniy) {
                    return true;
                }
            }
        }
    }
    return false;
}
