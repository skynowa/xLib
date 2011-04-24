/**********************************************************************
*	iGetRecordsCount.cpp -
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: iGetRecordsCount ()
INT iGetRecordsCount(TADOConnection *pADOConnection, const String &csTableName, const String &csSqlStrWhere) {
	/*DEBUG*/xASSERT_RET(NULL  != pADOConnection,         - 1);
	/*DEBUG*/xASSERT_RET(false == csTableName.IsEmpty(),  - 1);
	/*DEBUG*/// csSqlStrWhere - n/a

	INT iRes = - 1;

	try {
		std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(NULL));
		/*DEBUG*/xASSERT_RET(NULL != apqryTmp.get(), - 1);

		String sSqlStr;

		//SELECT COUNT(*) AS NumberOfOrders FROM Orders
		if (true == csSqlStrWhere.IsEmpty()) {
			sSqlStr = xT("SELECT COUNT(*) AS f_records_count FROM ") + csTableName + xT(";");
		} else {
			sSqlStr = xT("SELECT COUNT(*) AS f_records_count FROM ") + csTableName + xT(" ") + csSqlStrWhere + xT(";");
		}
		
		apqryTmp->Connection = pADOConnection;
		apqryTmp->Active     = false;
		apqryTmp->SQL->Text  = sSqlStr;
		apqryTmp->Active     = true;

		iRes = apqryTmp->FieldByName(xT("f_records_count"))->AsInteger;
    } catch (Exception &e) {
        Application->ShowException(&e);     //дубликаты записей, и др.

		iRes = - 1;
    } catch (...) {
		iRes = - 1;
	}

	/*DEBUG*/xASSERT_RET(0 <= iRes, - 1);

	return iRes;
}
//---------------------------------------------------------------------------

