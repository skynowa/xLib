/****************************************************************************
* Class name:  CxDBGdipImage
* Description: ����������� �������� �� �� 
* File name:   CxDBGdipImage.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     20.05.2010 11:57:56
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <XVCL\Classes\DB\CxDBGdipImage.h>

#include <XLib\Fso\CxFile.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bShow
/*static*/ 
BOOL CxDBGdipImage::bShow(CxGdipImage *pgimgImage, TADOQuery *pqryADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT_RET(NULL  != pgimgImage,   FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pqryADOQuery, FALSE);
	/*DEBUG*/// csFieldName - n/a

	if (
		NULL == pqryADOQuery->FindField(csFieldName)           ||
		true == pqryADOQuery->FieldByName(csFieldName)->IsNull	
	) 
	{
		_ms_bRes = CxDBGdipImage::bShowNo(pgimgImage);
		/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

		return TRUE;
	} 

	std::auto_ptr<TMemoryStream> apMS(new TMemoryStream());
	/*DEBUG*/xASSERT_RET(NULL != apMS.get(), FALSE);

	try {
		( static_cast<TBlobField*>(pqryADOQuery->FieldByName(csFieldName)) )->SaveToStream(apMS.get());
		/*DEBUG*/xASSERT_RET((NULL != apMS.get()) && (0 < apMS->Size), FALSE);

		apMS->Position  = 0;
		_ms_bRes = pgimgImage->bLoadFromStream(apMS.get());
		/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);
	} catch (...) {
		/*DEBUG*/xASSERT_RET(FALSE, FALSE);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bShowNo
/*static*/
BOOL CxDBGdipImage::bShowNo(CxGdipImage *pgimgImage) {
	/*DEBUG*/xASSERT_RET(NULL != pgimgImage, FALSE);

	//-------------------------------------
	//������ �� �����
	const String csPhotoTextNo = xT("���");

	_ms_bRes = pgimgImage->bClear();
	/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

	_ms_bRes = pgimgImage->bSetText(csPhotoTextNo);
	/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO:	bSave
/*static*/ 
BOOL CxDBGdipImage::bSave(CxGdipImage *pgimgImage, TADOQuery *pqryADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT_RET(NULL  != pgimgImage,            FALSE);	/*----------*/
	/*DEBUG*/xASSERT_RET(NULL  != pqryADOQuery,          FALSE);
	/*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE);

	//-------------------------------------
	//������� ������
	const std::auto_ptr<TSavePictureDialog> apdlgSavePhoto(new TSavePictureDialog(0));
	/*DEBUG*/xASSERT_RET(NULL != apdlgSavePhoto.get(), FALSE);

	apdlgSavePhoto->Name        = xT("dlgSavePhoto");
	apdlgSavePhoto->Title       = xT("��������� ���...");
	apdlgSavePhoto->Filter      = _ms_sFilesFilter;
	apdlgSavePhoto->FilterIndex = 6;	//�������������� �����

	//--if (false == apdlgSavePhoto->Execute()) {
	//--	pqryADOQuery->Cancel();
	//--	return TRUE;
	//--}
	xCHECK_RET(false == apdlgSavePhoto->Execute(), TRUE);

	//���������� ������������ ����� �� ������� �������
	String sFileExt;	
	switch (apdlgSavePhoto->FilterIndex) {
		case 1:	 { sFileExt = xT(".bmp");  }    	break;
		case 2:	 { sFileExt = xT(".jpeg"); }    	break;
		case 3:	 { sFileExt = xT(".gif");  }    	break;
		case 4:	 { sFileExt = xT(".tiff"); }    	break;
		case 5:	 { sFileExt = xT(".png");  }    	break;
		case 6:	 { sFileExt = xT(".png");  }    	break;	//�������������� ����� - png
		case 7:	 { sFileExt = xT(".png");  }    	break;	//��� �����            - png
    	
    	default: { xASSERT_RET(FALSE, FALSE); }	    break;
    }

	//-------------------------------------
	//������� �1 - ������� (����� PNG)
	////	((TBlobField *)pqryADOQuery->FieldByName(csFieldName))->SaveToFile(SavePictureDialog1->FileName);

	//-------------------------------------
	//������� �2 - �� �������
	////	pMemoryStream->Clear();
	////	((TBlobField *)pqryADOQuery->FieldByName(csFieldName))->SaveToStream(pMemoryStream);
	////	pPngImage->LoadFromStream(pMemoryStream);
	////	pPngImage->SaveToFile(SavePictureDialog1->FileName);

	//-------------------------------------
	//������� �3 - ������� (��� ������ ������� �����)
	////TField *pField = pqryADOQuery->FieldByName(csFieldName);
	////std::auto_ptr<TStream>     apBlobStream(pqryADOQuery->CreateBlobStream(pField, bmRead));
	////std::auto_ptr<TFileStream> apOutFile   (new TFileStream(apdlgSavePhoto->FileName + sFileExt, fmCreate | fmShareExclusive));
	////UCHAR *pucBuff = new UCHAR[apBlobStream->Size];
	/////*DEBUG*/xASSERT_RET(NULL != pucBuff, FALSE);
	////__try {
	////	INT iReadBytes = 0;
	////	do {
	////	   iReadBytes = apBlobStream->Read(pucBuff, 1024);
	////	   apOutFile->Write(pucBuff, iReadBytes);
	////	}
	////	while (iReadBytes);
	////} __finally {
	////	xDELETE_ARRAY(pucBuff);
	////}

	//-------------------------------------
	//������� �4 - (� ������� GDI+)
	CxGdipImage::EEncoderType etType;
	etType = static_cast<CxGdipImage::EEncoderType>( apdlgSavePhoto->FilterIndex - 1 );
	
	_ms_bRes = pgimgImage->bSaveToFile(apdlgSavePhoto->FileName + sFileExt, etType);
	/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bDelete
/*static*/ 
BOOL CxDBGdipImage::bAdd(CxGdipImage *pgimgImage, TADOQuery *pqryADOQuery, const String &csFieldName, BOOL bIsDeleteSourceFile) {
	/*DEBUG*/xASSERT_RET(NULL  != pgimgImage,            FALSE);	
	/*DEBUG*/xASSERT_RET(NULL  != pqryADOQuery,          FALSE);
	/*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE);
	/*DEBUG*/// bIsDeleteSourceFile - n/a

	//-------------------------------------
	//������� ������
	const std::auto_ptr<TOpenPictureDialog> apdlgOpenPhoto(new TOpenPictureDialog(0));
	/*DEBUG*/xASSERT_RET(NULL != apdlgOpenPhoto.get(), FALSE);

	apdlgOpenPhoto->Title  		= xT("�������...");
	apdlgOpenPhoto->Name   		= xT("dlgOpenPhoto");
	apdlgOpenPhoto->Filter 		= _ms_sFilesFilter;
	apdlgOpenPhoto->FilterIndex = 6;	//�������������� �����

	//--if (false == apdlgOpenPhoto->Execute()) {
    //--    pqryADOQuery->Cancel();
    //--    return TRUE;
	//--}
	xCHECK_RET(false == apdlgOpenPhoto->Execute(), TRUE);




	//-------------------------------------
	//������� � JPEG
	const std::auto_ptr<TMemoryStream> apmsCompress(new TMemoryStream());
	/*DEBUG*/xASSERT_RET(NULL != apmsCompress.get(), FALSE);
	
	apmsCompress->LoadFromFile(apdlgOpenPhoto->FileName);

	apmsCompress->Position = 0;
	_ms_bRes = pgimgImage->bLoadFromStream(apmsCompress.get());
	/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

	apmsCompress->Clear();
	apmsCompress->Position = 0;
	_ms_bRes = pgimgImage->bSaveToStream(apmsCompress.get(), CxGdipImage::etJpeg);
	/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

	

	//-------------------------------------
	//������� 1
	pqryADOQuery->Edit();
	apmsCompress->Position = 0;
	((TBlobField *)pqryADOQuery->FieldByName(csFieldName))->LoadFromStream(apmsCompress.get());
	pqryADOQuery->Post();

	//-------------------------------------
	//������� 2
	////pqryADOQuery->Edit();
	////((TBlobField *)pqryADOQuery->FieldByName(csFieldName))->LoadFromFile(apdlgOpenPhoto->FileName);
	////pqryADOQuery->Post();

	//-------------------------------------
	//���������� ��������
	_ms_bRes = bShow(pgimgImage, pqryADOQuery, csFieldName);
	/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

	//-------------------------------------
	//�������� ���������� �����
	xCHECK_DO(TRUE == bIsDeleteSourceFile, CxFile::bDelete( xD2S(apdlgOpenPhoto->FileName) ));

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bDelete
/*static*/ 
BOOL CxDBGdipImage::bDelete(CxGdipImage *pgimgImage, TADOQuery *pqryADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT_RET(NULL  != pgimgImage,            FALSE);	
	/*DEBUG*/xASSERT_RET(NULL  != pqryADOQuery,          FALSE);
	/*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE);

	pqryADOQuery->Edit();
	pqryADOQuery->FieldByName(csFieldName)->Clear();
	pqryADOQuery->Post();

	_ms_bRes = pgimgImage->bDestroy();
	/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

	_ms_bRes = CxDBGdipImage::bShowNo(pgimgImage);
	/*DEBUG*/xASSERT_RET(FALSE != _ms_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------








/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

BOOL   CxDBGdipImage::_ms_bRes         = FALSE;
String CxDBGdipImage::_ms_sFilesFilter = xT("BMP ����� (*.bmp)|*.bmp|")         \
										 xT("JPG/JPEG ����� (*.jpg;*.jpeg)|*.jpg;*.jpeg|")  \
										 xT("GIF ����� (*.gif)|*.gif|")         \
										 xT("TIFF ����� (*.tiff)|*.tiff|")        \
										 xT("PNG ����� (*.png)|*.png|")         \
										 xT("�������������� ����� (*.*)|*.bmp;*.jpg;*.jpeg;*.gif;*.tiff;*.png|")         \
										 xT("��� ����� (*.*)|*.*"); 

//---------------------------------------------------------------------------
//TODO: - CxDBGdipImage (comment)
CxDBGdipImage::CxDBGdipImage() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - ~CxDBGdipImage (comment)
CxDBGdipImage::~CxDBGdipImage() {
	//code
}
//---------------------------------------------------------------------------

