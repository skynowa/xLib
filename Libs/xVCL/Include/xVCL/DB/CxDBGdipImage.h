/****************************************************************************
* Class name:  CxDBGdipImage
* Description: отображение картинки из БД 
* File name:   CxDBGdipImage.h
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     20.05.2010 11:57:56
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxXVCL_Classes_Db_DBGdipImageH
#define CxXVCL_Classes_Db_DBGdipImageH
//---------------------------------------------------------------------------
#include <xVCL/xCommon.h>
#include <xVCL/Classes/Gui/CxGdipImage.h>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class CxDBGdipImage : public CxNonCopyable {
	public:
		//encoder type
		enum EEncoderType {
			etBmp  = 0, 
			etJpeg = 1, 
			etGif  = 2, 
			etTiff = 3, 
			etPng  = 4
		};

		static BOOL   bShow        (CxGdipImage *pImage, TADOQuery *pADOQuery, const String &csFieldName);
		static BOOL   bShowNo      (CxGdipImage *pImage); 
		static BOOL   bSave        (CxGdipImage *pImage, TADOQuery *pADOQuery, const String &csFieldName); 
		static BOOL   bAdd   	   (CxGdipImage *pImage, TADOQuery *pADOQuery, const String &csFieldName, BOOL bIsDeleteSourceFile);
		static BOOL   bDelete      (CxGdipImage *pImage, TADOQuery *pADOQuery, const String &csFieldName);

	private:
		static BOOL   _ms_bRes;
		static String _ms_sFilesFilter;

					  CxDBGdipImage();
				     ~CxDBGdipImage();
};
//---------------------------------------------------------------------------
#endif //CxXVCL_Classes_Db_DBGdipImageH
