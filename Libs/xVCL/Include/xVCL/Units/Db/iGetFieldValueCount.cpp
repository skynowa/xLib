/**********************************************************************
*	iGetFieldValueCount.cpp -
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: iGetFieldValueCount ()
INT iGetFieldValueCount(TADOConnection *pADOConnection, const String &csTableName, const String &csFiledName, const String &csFieldValue) {
	/*DEBUG*/xASSERT_RET(NULL  != pADOConnection,         - 1);
	/*DEBUG*/xASSERT_RET(false == csTableName.IsEmpty(),  - 1);
	/*DEBUG*////xASSERT_RET(false == csFieldValue.IsEmpty(), - 1);

	INT iRes = - 1;

	try {
		std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(NULL));
		/*DEBUG*/xASSERT_RET(NULL != apqryTmp.get(), - 1);

		String sSqlStr;

		sSqlStr = xT("SELECT COUNT(") + csFiledName + xT(") AS f_records_count FROM ") + csTableName + xT(" WHERE ") + csFiledName + xT("='") + csFieldValue + xT("';");
		
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
//TODO: iGetFieldValueCount ()
INT iGetFieldValueCount(
	TADOConnection *pADOConnection, 
	const String &csTableName, 
	const String &csFiledName,  const String &csFieldValue, 
	const String &csFiledName2, const String &csFieldValue2
) {
	/*DEBUG*/xASSERT_RET(NULL  != pADOConnection,         - 1);
	/*DEBUG*/xASSERT_RET(false == csTableName.IsEmpty(),  - 1);
	/*DEBUG*////xASSERT_RET(false == csFieldValue.IsEmpty(), - 1);

	INT iRes = - 1;

	try {
		std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(NULL));
		/*DEBUG*/xASSERT_RET(NULL != apqryTmp.get(), - 1);

		String sSqlStr;

		sSqlStr = xT("SELECT COUNT(") + csFiledName + xT(") AS f_records_count FROM ") + 
				  csTableName + 
				  xT(" WHERE ") + csFiledName  + xT("='") + csFieldValue  + xT("'") + 
				  xT(" AND ")   + csFiledName2 + xT("='") + csFieldValue2 + xT("';");
		////iMsgBox(sSqlStr.c_str());
		
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

