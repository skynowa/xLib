/**********************************************************************
*	vImportData -
*
***********************************************************************/


//---------------------------------------------------------------------------
void vExportData(TADOConnection *pADOConnection, const String &csFilePath, const String &usMode) {
    TStringList *pList = new TStringList();

    //-------------------------------------
    //������
	String asSQLStr = L"SELECT * FROM TN_INFO";

    //-------------------------------------
    //��������� ������
    TADOQuery *qryTmp =  new TADOQuery(NULL);
    qryTmp->Connection = pADOConnection;

    qryTmp->Close();
    qryTmp->SQL->Text = asSQLStr;

    try {
        qryTmp->Open();

        qryTmp->First();
        while (! qryTmp->Eof) {
            pList->Add(
				qryTmp->FieldByName(L"FN_URL")->AsString      + L"|" +
				qryTmp->FieldByName(L"FN_LOGIN")->AsString    + L"|" +
				qryTmp->FieldByName(L"FN_PASSWORD")->AsString + L"|" +
				qryTmp->FieldByName(L"FN_EMAIL")->AsString
            );
            qryTmp->Next();
        }
    } catch (Exception &exception) {
        Application->ShowException(&exception); //��������� �������, � ��.
    }

    pList->SaveToFile(csFilePath);

    delete qryTmp; qryTmp = NULL;
    delete pList;  pList  = NULL;
}
//---------------------------------------------------------------------------

