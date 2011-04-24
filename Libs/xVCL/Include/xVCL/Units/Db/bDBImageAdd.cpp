/**********************************************************************
*	vAddImage.cpp	
*
***********************************************************************/


#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
void vAddImage(TImage *pImage, TADOQuery* pADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pImage);
	/*DEBUG*/xASSERT(NULL  != pADOQuery);
	/*DEBUG*/xASSERT(false == csFieldName.IsEmpty());

	//-------------------------------------
	//создаем диалог
	const std::auto_ptr<TOpenPictureDialog> apdlgOpenPhoto(new TOpenPictureDialog(0));
	/*DEBUG*/xASSERT(NULL != apdlgOpenPhoto.get());

	apdlgOpenPhoto->Title  = _T("Открыть...");
	apdlgOpenPhoto->Name   = _T("dlgOpenPhoto");
	apdlgOpenPhoto->Filter = _T("JPEG Image File (*.jpg;*.jpeg)|*.jpg;*.jpeg|"
								"All files       (*.*)|*.*");

	if (false == apdlgOpenPhoto->Execute()) {
        pADOQuery->Cancel();
        return;
	}

	//-------------------------------------
	//вариант 1
////    Repaint();
////	m_pMemoryStream->Clear();
////    m_pMemoryStream->LoadFromFile(OpenPictureDialog1->FileName);
////    pADOQuery->Edit();
////	((TBlobField *)pADOQuery->FieldByName(csFieldName))->LoadFromStream(m_pMemoryStream);
////    pADOQuery->Post();

	////////////////////?????Repaint();

	//-------------------------------------
	//вариант 2
	pADOQuery->Edit();
	((TBlobField *)pADOQuery->FieldByName(csFieldName))->LoadFromFile(apdlgOpenPhoto->FileName);
	pADOQuery->Post();

	//-------------------------------------
	//показываем картинку
	vShowImage(pImage, pADOQuery, csFieldName);
}
//---------------------------------------------------------------------------


/*
BOOL TfrmMain::bCompression(const String &csFilePath) {
	std::auto_ptr<TFileStream>         apInFile     (new TFileStream(csFilePath, fmOpenRead | fmShareExclusive));
	std::auto_ptr<TFileStream>         apOutFile    (new TFileStream(csFilePath + _T(".arh"), fmCreate | fmShareExclusive));
	std::auto_ptr<TZCompressionStream> apComprStream(new TZCompressionStream(Zlib::clMax, apOutFile.get()));

	apComprStream->CopyFrom(apInFile.get(), apInFile->Size);
	apComprStream->CompressionRate;

	return TRUE;
}
*/


/*
Как записать файл в Blob поле?

1)Через таблицу:
(table1.fieldbyname('ddd') as TBlobField).loadfromfile('dddss');

2) через параметры в запросе...
ADOquery1.sql.text:='Insert into myTable (a) Values (:b)';
ADOQuery1.parameters.parseSQL(ADOquery1.sql.text, true);
ADOQuery1.parameters.parambyname('b').LoadFromFile('MyFile');
ADOQuery1.execsql;
*/
