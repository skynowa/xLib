/**********************************************************************
*	vImportData -
*
***********************************************************************/


//---------------------------------------------------------------------------
void vExportData(TADOConnection *pADOConnection, const String &csFilePath, const String &usMode) {
    TStringList *pList = new TStringList();

    //-------------------------------------
    //запрос
	String asSQLStr = L"SELECT * FROM TN_INFO";

    //-------------------------------------
    //выполнить запрос
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
        Application->ShowException(&exception); //дубликаты записей, и др.
    }

    pList->SaveToFile(csFilePath);

    delete qryTmp; qryTmp = NULL;
    delete pList;  pList  = NULL;
}
//---------------------------------------------------------------------------

