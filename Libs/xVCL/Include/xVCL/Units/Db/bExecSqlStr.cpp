/**********************************************************************
*	bExecSqlStr.cpp - выполнение запроса
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: bExecSqlStr (выполнение запроса)
BOOL bExecSqlStr(TADOConnection *pADOConnection, const String &csSqlStr, BOOL bIsSelectMode) {
	/*DEBUG*/xASSERT_RET(NULL  != pADOConnection,     FALSE);
	/*DEBUG*/xASSERT_RET(false == csSqlStr.IsEmpty(), FALSE);
	/*DEBUG*/// bIsSelectMode - n/a

	BOOL bRes = FALSE;

	try {
		std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(NULL));
		/*DEBUG*/xASSERT_RET(NULL != apqryTmp.get(), FALSE);

		apqryTmp->Close();
		apqryTmp->Connection = pADOConnection;
		apqryTmp->SQL->Text  = csSqlStr;

        if (TRUE == bIsSelectMode) {
           apqryTmp->Open();
        } else {
           apqryTmp->ExecSQL();
        }

		bRes = TRUE;
    } catch (Exception &e) {
        Application->ShowException(&e);     //дубликаты записей, и др.

		bRes = FALSE;
    } catch (...) {
		/*DEBUG*/xASSERT(FALSE);

		bRes = FALSE;
	}

	return bRes;
}
//---------------------------------------------------------------------------

