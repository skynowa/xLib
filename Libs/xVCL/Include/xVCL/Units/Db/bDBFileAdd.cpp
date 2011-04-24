/**********************************************************************
*	bDBFileAdd.cpp - ���������� ���� � ��	
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: bDBFileAdd (���������� ���� � ��)
BOOL bDBFileAdd(TADOQuery *pADOQuery, const String &csFieldName, String *psNewFileName) {
	/*DEBUG*/xASSERT_RET(NULL  != pADOQuery,             FALSE);
	/*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE);
	/*DEBUG*/// psNewFileName - n/a

	//-------------------------------------
	//�������� �������
	const std::auto_ptr<TOpenDialog> apdlgOpenFile(new TOpenDialog(NULL));
	/*DEBUG*/xASSERT_RET(NULL != apdlgOpenFile.get(), FALSE);

	apdlgOpenFile->Name   = _T("dlgOpenFile");
	apdlgOpenFile->Filter = _T("All files (*.*)|*.*");
	
	xCHECK_RET(false == apdlgOpenFile->Execute(), TRUE);

	//-------------------------------------
	//���������� �����
    pADOQuery->Edit();
	((TBlobField *)pADOQuery->FieldByName(csFieldName))->LoadFromFile(apdlgOpenFile->FileName);
	pADOQuery->Post();

	if (NULL != psNewFileName) {
		(*psNewFileName) = ExtractFileName(apdlgOpenFile->FileName);
	}

	return TRUE;
}
//---------------------------------------------------------------------------

/*
��� �������� ���� � Blob ����?

1)����� �������:
(table1.fieldbyname('ddd') as TBlobField).loadfromfile('dddss');

2) ����� ��������� � �������...
ADOquery1.sql.text:='Insert into myTable (a) Values (:b)';
ADOQuery1.parameters.parseSQL(ADOquery1.sql.text, true);
ADOQuery1.parameters.parambyname('b').LoadFromFile('MyFile');
ADOQuery1.execsql;
*/
