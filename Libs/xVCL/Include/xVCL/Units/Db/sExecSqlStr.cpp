/**********************************************************************
*	sExecSqlStr.cpp - f_tmp - должно быть в SQL запросе
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: sExecSqlStr (выполнение запроса)
String sExecSqlStr(TADOConnection *pADOConnection, const String &csSqlStr, const String &csTempFieldName /*xT("f_tmp")*/) {
	/*DEBUG*/xASSERT_RET(NULL  != pADOConnection,     String());
	/*DEBUG*/xASSERT_RET(false == csSqlStr.IsEmpty(), String());
	
	String sRes;
	
	const std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(0));
	/*DEBUG*/xASSERT_RET(NULL != apqryTmp.get(), String());
	
    try {
		apqryTmp->Connection = pADOConnection;
        apqryTmp->Close();
        apqryTmp->SQL->Text  = csSqlStr;
        apqryTmp->Open();   

		sRes = apqryTmp->FieldByName(csTempFieldName)->AsString;
    } catch (Exception &e) {
        Application->ShowException(&e); //дубликаты записей, и др.
    } catch (...) {

	}

	/*DEBUG*/xASSERT_RET(false == sRes.IsEmpty(), String());

	return sRes;
}
//---------------------------------------------------------------------------