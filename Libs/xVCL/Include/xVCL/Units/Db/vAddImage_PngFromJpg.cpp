/**********************************************************************
*	vAddImage_PngFromJpg.cpp
*
***********************************************************************/


#include <vcl.h>
#pragma hdrstop

#include "uMain.h"
//---------------------------------------------------------------------------
void __fastcall vAddImage_PngFromJpg(TImage *pImage, TADOQuery *pADOQuery, const tString &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pImage);
	/*DEBUG*/xASSERT(NULL  != pADOQuery);
    /*DEBUG*/xASSERT(false == csFieldName.IsEmpty()); 

	//-------------------------------------
	//создаем диалог
	const std::auto_ptr<TOpenPictureDialog> apdlgOpenPhoto(new TOpenPictureDialog(this));
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
	std::auto_ptr<TPngImage>         apPng (new TPngImage);
	/*DEBUG*/xASSERT(NULL  != apPng.get());
	
	std::auto_ptr<Graphics::TBitmap> apBmp (new Graphics::TBitmap);
	/*DEBUG*/xASSERT(NULL  != apBmp.get());
	
	std::auto_ptr<TJPEGImage>        apJpeg(new TJPEGImage);
	/*DEBUG*/xASSERT(NULL  != apJpeg.get());

	//JPG -> BMP
	apJpeg->LoadFromFile(apdlgOpenPhoto->FileName);
	apBmp->Assign((TPersistent *)apJpeg.get());
	apBmp->SaveToStream(m_pMemoryStream);

	//BMP -> PNG
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
