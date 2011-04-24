/**********************************************************************
*	bDBFileSave.cpp - ��������� ����� �� ��	
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: bDBFileSave (��������� ����� �� ��)
BOOL bDBFileSave(TADOQuery *pADOQuery, const String &csFieldName, const String &csNewFileName) {
	/*DEBUG*/xASSERT_RET(NULL  != pADOQuery,             FALSE);
	/*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE);
	/*DEBUG*/// csNewFileName - n/a

	//-------------------------------------
	//�������� �������
	const std::auto_ptr<TSaveDialog> apdlgSaveFile(new TSaveDialog(0));
	/*DEBUG*/xASSERT_RET(NULL != apdlgSaveFile.get(), FALSE);

	apdlgSaveFile->Name     = _T("dlgSaveFile");
	apdlgSaveFile->Filter   = _T("All files (*.*)|*.*");
	apdlgSaveFile->FileName = csNewFileName;

	xCHECK_RET(false == apdlgSaveFile->Execute(), TRUE);

	//-------------------------------------
	//���������� �����
	((TBlobField *)pADOQuery->FieldByName(csFieldName))->SaveToFile(apdlgSaveFile->FileName);

	return TRUE;
}
//---------------------------------------------------------------------------