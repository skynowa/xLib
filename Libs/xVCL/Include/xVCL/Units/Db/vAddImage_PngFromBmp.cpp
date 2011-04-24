/**********************************************************************
*	vAddImage_PngFromBmp.cpp
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vAddImage_PngFromBmp(TImage *pImage, TADOQuery *pADOQuery, const tString &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pImage);
	/*DEBUG*/xASSERT(NULL  != pADOQuery);
    /*DEBUG*/xASSERT(false == csFieldName.IsEmpty()); 

	//-------------------------------------
	//создаем диалог
	const std::auto_ptr<TOpenPictureDialog> apdlgOpenPhoto(new TOpenPictureDialog(0));
	/*DEBUG*/xASSERT(NULL != apdlgOpenPhoto.get());

	apdlgOpenPhoto->Name   = _T("dlgOpenPhoto");
	apdlgOpenPhoto->Filter = _T("PNG Image File  (*.png)|*.png;|JPEG Image File (*.jpg)|*.jpg|JPE"
								"G Image File (*.jpeg)|*.jpeg|BMP  Image File (*.bmp)|*.bmp|All I"
								"mage Files    (*.png;*.jpg;*.jpeg;*.bmp;)|*.jpg;*.jpeg;*.bmp;*.p"
								"ng;|All files                (*.*)|*.*");

	if (!apdlgOpenPhoto->Execute()) {
        pADOQuery->Cancel();
        return;
	}

	//-------------------------------------
	//конвертим картинку
	std::auto_ptr<TPngImage>         apPng(new TPngImage);
	/*DEBUG*/xASSERT(NULL  != apPng.get());
	
	std::auto_ptr<Graphics::TBitmap> apBmp(new Graphics::TBitmap);
	/*DEBUG*/xASSERT(NULL  != apBmp.get());

	apBmp->LoadFromFile(apdlgOpenPhoto->FileName);
	apPng->Assign((TPersistent *)apBmp.get());
	apPng->SaveToStream(m_pMemoryStream);

	//-------------------------------------
	//вставляем какртинку
	pADOQuery->Edit();
	((TBlobField *)pADOQuery->FieldByName(csFieldName))->LoadFromStream(m_pMemoryStream);
	pADOQuery->Post();

	//-------------------------------------
	//показываем картинку
	vShowImage(pImage, pADOQuery, csFieldName);
}
//---------------------------------------------------------------------------
