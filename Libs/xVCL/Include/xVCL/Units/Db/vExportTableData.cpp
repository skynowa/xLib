/**********************************************************************
*	vExportTableData -
*
***********************************************************************/


//#include "uHomeDB.h"

//---------------------------------------------------------------------------
//�������
void vExportTableData(TADOConnection *pADOConnection, const String &csTableName, const String &csFilePath, const String &csMode) {
    //-------------------------------------
    //�������� ������� -> TStringList
    TStringList *pFieldList = new TStringList;
	pADOConnection->GetFieldNames(csTableName, pFieldList);


    TStringList *pTableList = new TStringList();

    //-------------------------------------
    //������
	String sSQLStr = "SELECT * FROM " + csTableName + ";";

    //-------------------------------------
    //��������� ������
    TADOQuery *qryTmp =  new TADOQuery(NULL);
    qryTmp->Connection = pADOConnection;

    qryTmp->Close();
	qryTmp->SQL->Text = sSQLStr;

    try {
        //-------------------------------------
        //��������� �����
		String asTableHeader;
        for (int i = 0; i < pFieldList->Count; i ++) {
            asTableHeader += pFieldList->Strings[i] + "|";
        }
        //������� ��������� ������ - �����������
        asTableHeader.SetLength(asTableHeader.Length() - 1);

        pTableList->Add(asTableHeader);

        //-------------------------------------
        //��������� ������
        qryTmp->Open();
        qryTmp->First();
        while (! qryTmp->Eof) {
			String asTableLine;
            for (int i = 0; i < pFieldList->Count; i ++) {
                asTableLine += qryTmp->FieldByName(pFieldList->Strings[i])->AsString + "|";
            }
            //������� ��������� ������ - �����������
            asTableLine.SetLength(asTableLine.Length() - 1);
            pTableList->Add(asTableLine);

            qryTmp->Next();
        }
    } catch (Exception &exception) {
        Application->ShowException(&exception); //��������� �������, � ��.
    }

    pTableList->SaveToFile(csFilePath);

    delete qryTmp;      qryTmp     = NULL;
    delete pTableList;  pTableList = NULL;
    delete pFieldList;  pFieldList = NULL;
}
//---------------------------------------------------------------------------

