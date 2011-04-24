/**********************************************************************
*	vSaveImage.cpp	
*
***********************************************************************/


//---------------------------------------------------------------------------
void vSaveImage(TADOQuery *pADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pADOQuery);
	/*DEBUG*/xASSERT(false == csFieldName.IsEmpty());

	//-------------------------------------
	//������� ������
	const std::auto_ptr<TSavePictureDialog> apdlgSavePhoto(new TSavePictureDialog(0));
	/*DEBUG*/xASSERT(NULL != apdlgSavePhoto.get());

	apdlgSavePhoto->Name   = _T("dlgSavePhoto");
	apdlgSavePhoto->Title  = _T("��������� ���...");
	apdlgSavePhoto->Filter = _T("JPEG Image File (*.jpg;*.jpeg)|*.jpg;*.jpeg|"
								"All files       (*.*)|*.*");

	//-------------------------------------
	//������� �1 - ������� (����� PNG)
	////	if (!SavePictureDialog1->Execute()) {
	////		pADOQuery->Cancel();
	////		return;
	////	}
	////
	////	((TBlobField *)pADOQuery->FieldByName(csFieldName))->SaveToFile(SavePictureDialog1->FileName);

	//-------------------------------------
	//������� �2 - �� �������
	////	if (!SavePictureDialog1->Execute()) {
	////		pADOQuery->Cancel();
	////		return;
	////	}
	////
	////	pMemoryStream->Clear();
	////	((TBlobField *)pADOQuery->FieldByName(csFieldName))->SaveToStream(pMemoryStream);
	////	pPngImage->LoadFromStream(pMemoryStream);
	////	pPngImage->SaveToFile(SavePictureDialog1->FileName);

	//-------------------------------------
	//������� �3 - �� ������� (��� ������ ������� �����)
	if (!apdlgSavePhoto->Execute()) {
		pADOQuery->Cancel();
		return;
	}

	TField *pField = pADOQuery->FieldByName(csFieldName);
	std::auto_ptr<TStream>     apBlobStream(pADOQuery->CreateBlobStream(pField, bmRead));
	std::auto_ptr<TFileStream> apOutFile   (new TFileStream(apdlgSavePhoto->FileName + _T(".jpg") , fmCreate | fmShareExclusive));
	UCHAR *pucBuff = new UCHAR[apBlobStream->Size];
	__try {
		INT iReadBytes = 0;
		do {
		   iReadBytes = apBlobStream->Read(pucBuff, 1024);
		   apOutFile->Write(pucBuff, iReadBytes);
		}
		while (iReadBytes);
	} __finally {
		xDELETE_ARRAY(pucBuff);
	}
}
//---------------------------------------------------------------------------
