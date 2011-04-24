/**********************************************************************
*	curSummDBColumn.cpp -
*
***********************************************************************/


//---------------------------------------------------------------------------
Currency __fastcall TdmHomeBuh::curSummDBColumn(TADOConnection *pADOConnection, const tString &cusTableName, const tString &csFieldName) {
	Currency curRes = 0;

	TADOQuery *qryTmp =  new TADOQuery(NULL);

    try {
		qryTmp->Connection = pADOConnection;
		qryTmp->Close();
		qryTmp->SQL->Text = L"SELECT " + csFieldName + L" FROM " + cusTableName + L";";      //ShowMessage(qryTmp->SQL->Text);
		qryTmp->Open();
		qryTmp->First();
		while (! qryTmp->Eof) {
			if (false == qryTmp->FieldByName(csFieldName)->IsNull) {
				curRes += qryTmp->FieldByName(csFieldName)->AsCurrency;
            }
            qryTmp->Next();
        }
		qryTmp->Close();
	} catch (Exception &exception) {
		curRes = 0;
		Application->ShowException(&exception); //дубликаты записей, и др.
	}

	delete qryTmp; qryTmp = NULL;

	return curRes;
}
//---------------------------------------------------------------------------
