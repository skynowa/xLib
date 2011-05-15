/****************************************************************************
* Class name:  CxZCompression
* Description: архивирование с помощбю ZLib
* File name:   CxZCompression.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib, VCL
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     09.06.2010 10:55:58
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xVCL/Archive/CxZCompression.h>

#include <xLib/Filesystem/Win/CxFile.h>


/****************************************************************************
*    public
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bCompress
/*static*/
BOOL
CxZCompression::bCompress(const String &csInFilePath, const String &csOutFilePath, Zlib::TCompressionLevel clLevel, BOOL bIsDeleteSource) {
	{
		std::auto_ptr<TFileStream>         apfsIn   (new TFileStream        (csInFilePath,  fmOpenRead | fmShareExclusive));
		/*DEBUG*/xASSERT_RET(NULL != apfsIn.get(), FALSE);

		std::auto_ptr<TFileStream>         apfsOut  (new TFileStream        (csOutFilePath, fmCreate   | fmShareExclusive));
		/*DEBUG*/xASSERT_RET(NULL != apfsOut.get(), FALSE);

		std::auto_ptr<TZCompressionStream> apcsCompr(new TZCompressionStream(clLevel,       apfsOut.get()));
		/*DEBUG*/xASSERT_RET(NULL != apcsCompr.get(), FALSE);

		apcsCompr->CopyFrom(apfsIn.get(), apfsIn->Size);
		apcsCompr->CompressionRate;
	}

	xCHECK_DO(TRUE == bIsDeleteSource, CxFile::bDelete( xD2S(csInFilePath) ));

	return TRUE; 
}
//---------------------------------------------------------------------------
//TODO: bDecompress
/*static*/
BOOL
CxZCompression::bDecompress(const String &csInFilePath, const String &csOutFilePath, BOOL bIsDeleteSource) {
	{
		INT   iReaded           = 0;
		UCHAR szBuff[1024 * 32] = {0};

		std::auto_ptr<TFileStream>           apfsIn     (new TFileStream          (csInFilePath,  fmOpenRead | fmShareExclusive));
		/*DEBUG*/xASSERT_RET(NULL != apfsIn.get(), FALSE);

		std::auto_ptr<TFileStream>           apfsOut    (new TFileStream          (csOutFilePath, fmCreate   | fmShareExclusive));
		/*DEBUG*/xASSERT_RET(NULL != apfsOut.get(), FALSE);

		std::auto_ptr<TZDecompressionStream> apcsDecompr(new TZDecompressionStream(apfsIn.get()));
		/*DEBUG*/xASSERT_RET(NULL != apcsDecompr.get(), FALSE);

		do {
		   iReaded = apcsDecompr->Read(szBuff, 1024 * 32);
		   apfsOut->Write(szBuff, iReaded);
		}
		while (iReaded);
	}

	xCHECK_DO(TRUE == bIsDeleteSource, CxFile::bDelete( xD2S(csInFilePath) ));

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxZCompression (comment)
CxZCompression::CxZCompression() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - ~CxZCompression (comment)
CxZCompression::~CxZCompression() {
	//code
}
//---------------------------------------------------------------------------
