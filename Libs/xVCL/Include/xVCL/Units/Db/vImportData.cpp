/**********************************************************************
*	vImportData -
*
***********************************************************************/


//---------------------------------------------------------------------------
void vImportData(TADOConnection *pADOConnection, const String &csFilePath) {
    TStringList *pList = new TStringList();
    pList->LoadFromFile(csFilePath);        

    for (int i = 0; i < pList->Count; i ++) {
		String usParam_1 = usSplitEx(pList->Strings[i], '|', 1);
		String usParam_2 = usSplitEx(pList->Strings[i], '|', 2);
		String usParam_3 = usSplitEx(pList->Strings[i], '|', 3);
		String usParam_4 = usSplitEx(pList->Strings[i], '|', 4);

        //-------------------------------------
        //запрос
        String usSQLStr =
		   L"INSERT \
                INTO \
            TN_INFO \
                ( \
                FN_URL, \
                FN_LOGIN, \
                FN_PASSWORD, \
                FN_EMAIL \
                ) \
            VALUES \
                ('" + \
				usParam_1 + L"','" + \
				usParam_2 + L"','" + \
				usParam_3 + L"','" + \
                usParam_4 + L"')";   //MessageBox(0, usSQLStr.c_str(), "", MB_OK);

        //-------------------------------------
        //выполнить запрос
        TADOQuery *qryTmp =  new TADOQuery(NULL);
        qryTmp->Connection = pADOConnection;

        qryTmp->Close();
		qryTmp->SQL->Text = usSQLStr;

        try {
			qryTmp->ExecSQL();
        } catch (Exception &exception) {
            Application->ShowException(&exception); //дубликаты записей, и др.
        }

        delete qryTmp; qryTmp = NULL;
    }

    delete pList; pList = NULL;

    //-------------------------------------
    //восстановить запрос 
}
//---------------------------------------------------------------------------

