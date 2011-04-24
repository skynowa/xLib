/**********************************************************************
*	bSqlStrToComboBox -
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: bSqlStrToComboBox
BOOL bSqlStrToComboBox(TComboBox *pCbb, const String &csFieldName, TADOConnection *pADOConnection, const String &csSQLStr) {
	/*DEBUG*/xASSERT_RET(NULL  != pCbb,                  FALSE);
	/*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pADOConnection,        FALSE);
	/*DEBUG*/xASSERT_RET(false == csSQLStr.IsEmpty(),    FALSE);

	BOOL bRes = FALSE;

	try {
		const std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(0));
		/*DEBUG*/xASSERT_RET(NULL != apqryTmp.get(), FALSE);

		apqryTmp->Close();
		apqryTmp->Connection = pADOConnection;
		apqryTmp->SQL->Text  = csSQLStr;

        apqryTmp->Open();
        apqryTmp->First();
        pCbb->Items->Clear();
        
        while (! apqryTmp->Eof) {
            if (false == apqryTmp->FieldByName(csFieldName)->IsNull) {
                pCbb->Items->Add(apqryTmp->FieldByName(csFieldName)->Value);
            }                
            apqryTmp->Next();
        }
        
        apqryTmp->Close();

		pCbb->DropDownCount = 40;

		bRes = TRUE;
    } catch (Exception &exception) {
        Application->ShowException(&exception); //дубликаты записей, и др.

		bRes = FALSE;
    } catch (...) {
		bRes = FALSE;
	}

	return bRes;
}
//---------------------------------------------------------------------------
/*
    //заполняем cbbCustomerName
    TADOQuery * apqryTmp1 =  new TADOQuery(NULL);
    apqryTmp1->Connection = frmMain->conCustomers;
    apqryTmp1->SQL->Text = "Select * from TN_CUSTOMERS";
    apqryTmp1->Open();

    apqryTmp1->First();
    cbbCustomerName->Items->Clear();
    while (! apqryTmp1->Eof) {
        cbbCustomerName->Items->Add(apqryTmp1->FieldByName("FN_CUSTOMER_NAME")->Value);
        apqryTmp1->Next();
    }
    apqryTmp1->Close();

    delete apqryTmp1; apqryTmp1 = NULL;
    */
