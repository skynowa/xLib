/**********************************************************************
*	bDBFileDelete.cpp - �������� ����� �� ��	
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: bDBFileDelete (�������� ����� �� ��)
BOOL bDBFileDelete(TADOQuery *pADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT_RET(NULL  != pADOQuery,             FALSE);
	/*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE);

	//-------------------------------------
	//�������� �����
	pADOQuery->Edit();
	pADOQuery->FieldByName(csFieldName)->Clear();
	pADOQuery->Post();

	return TRUE;
}
//---------------------------------------------------------------------------

/*
UPDATE MyTable

Set MyBlobField = Null

WHERE SomeField = 'Somevalue'
*/
