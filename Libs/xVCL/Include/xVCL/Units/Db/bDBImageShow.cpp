/**********************************************************************
*	vShowImage.cpp	
*
***********************************************************************/


//---------------------------------------------------------------------------
void vShowImage(TImage* pImage, TADOQuery* pADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pImage);
	/*DEBUG*/xASSERT(NULL  != pADOQuery);
	/*DEBUG*/xASSERT(false == csFieldName.IsEmpty());

	//-------------------------------------
	//удаляем старую картинку (BC++ 6.0 - RAD2009: работает, RAD2010 - ошибка)
	pImage->Picture->Assign(NULL);
	pImage->Repaint();

//	Graphics::TBitmap *bmp = new Graphics::TBitmap();
//	pImage->Picture->Assign(bmp);

	//pImage->Picture->Bitmap = NULL;

	std::auto_ptr<TMemoryStream> apMS(new TMemoryStream());
	/*debug*/xASSERT(NULL != apMS.get());

	//-------------------------------------
	//Вариант №1: BMP + JPEG
	std::auto_ptr<TJPEGImage> apJPEGImage(new TJPEGImage());
	/*debug*/xASSERT(NULL != apJPEGImage.get());

	try {
		//JPEG
		apMS->Clear();
		((TBlobField*)pADOQuery->FieldByName(csFieldName))->SaveToStream(apMS.get());
		if ((NULL == apMS.get()) || (0 == apMS->Size)) {
			pImage->Visible = false;
			return;
		}
		pImage->Visible = true;
		apMS->Position  = 0;
		apJPEGImage->LoadFromStream(apMS.get());

		pImage->Picture->Assign((TPersistent *)apJPEGImage.get());
	} catch (...) {
		xASSERT_MSG(FALSE, xT("Используется не JPG/JPEG - формат картинки"));
		//BMP
		pImage->Picture->Assign(pADOQuery->FieldByName(csFieldName));
	}

	//-------------------------------------
	//Вариант №2: PNG
//	m_pMemoryStream->Clear();
//	((TBlobField*)pADOQuery->FieldByName(csFieldName))->SaveToStream(m_pMemoryStream);
//	if ((!m_pMemoryStream) || (m_pMemoryStream->Size == 0)) {
//		pImage->Visible = false;
//		return;
//	}
//	pImage->Visible = true;
//	m_pMemoryStream->Position = 0;
//	m_pPngImage->LoadFromStream(m_pMemoryStream);
//	pImage->Picture->Assign((TPersistent *)m_pPngImage);
}
//---------------------------------------------------------------------------



/*
		//ScrollBox1->HorzScrollBar->Range = jpg->Width;
		//ScrollBox1->VertScrollBar->Range = jpg->Height;
*/
