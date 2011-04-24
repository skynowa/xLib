/**********************************************************************
*	bSqlStrToDBComboBox -
*
***********************************************************************/


#include <DBCtrls.hpp>

//---------------------------------------------------------------------------
//TODO: bSqlStrToDBComboBox 
BOOL bSqlStrToDBComboBox(TDBComboBox *pCbb, const String &csFieldName, TADOConnection *pADOConnection, const String &csSQLStr) {
	/*DEBUG*/xASSERT_RET(NULL  != pCbb,                  FALSE);
    /*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE); 
	/*DEBUG*/xASSERT_RET(NULL  != pADOConnection,        FALSE);
	/*DEBUG*/xASSERT_RET(false == csSQLStr.IsEmpty(),    FALSE);
	
	BOOL bRes = FALSE;

	const std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(0));
	/*DEBUG*/xASSERT_RET(NULL != apqryTmp.get(), FALSE);

	apqryTmp->Close();
    apqryTmp->Connection = pADOConnection;
	apqryTmp->SQL->Text  = csSQLStr;

    try {
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
    TADOQuery * qryTmp1 =  new TADOQuery(NULL);
    qryTmp1->Connection = frmMain->conCustomers;
    qryTmp1->SQL->Text = "Select * from TN_CUSTOMERS";
    qryTmp1->Open();

    qryTmp1->First();
    cbbCustomerName->Items->Clear();
    while (! qryTmp1->Eof) {
        cbbCustomerName->Items->Add(qryTmp1->FieldByName("FN_CUSTOMER_NAME")->Value);
        qryTmp1->Next();
    }
    qryTmp1->Close();

    delete qryTmp1; qryTmp1 = NULL;
    */
