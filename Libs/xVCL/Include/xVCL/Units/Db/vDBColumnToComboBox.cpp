/**********************************************************************
*	vDBColumnToPickList -
*
***********************************************************************/


//---------------------------------------------------------------------------
void vDBColumnToComboBox(TComboBox *pCbb, TADOConnection *pADOConnection, const String &csTableName, const String &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pCbb);
	/*DEBUG*/xASSERT(NULL  != pADOConnection);
	/*DEBUG*/xASSERT(false == csTableName.IsEmpty());
    /*DEBUG*/xASSERT(false == csFieldName.IsEmpty());

	std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(NULL));
    /*DEBUG*/xASSERT(NULL != apqryTmp.get());

	try {
		apqryTmp->Close();
        apqryTmp->Connection = pADOConnection;
		apqryTmp->SQL->Text = _T("SELECT ") + csFieldName + _T(" FROM ") + csTableName; //+ _T("  ORDER BY ") + csFieldName + _T(" ASC;"); 	//ShowMessage(apqryTmp->SQL->Text);
		apqryTmp->Open();
        apqryTmp->First();
        pCbb->Clear();
        
		while (! apqryTmp->Eof) {
			if (false == apqryTmp->FieldByName(csFieldName)->IsNull) {
                pCbb->Items->Add(apqryTmp->FieldByName(csFieldName)->Value);
            }
            apqryTmp->Next();
		}
        apqryTmp->Close();

        pCbb->DropDownCount = 40;
    } catch (Exception &exception) {
        Application->ShowException(&exception); //дубликаты записей, и др.
    }
}
//---------------------------------------------------------------------------