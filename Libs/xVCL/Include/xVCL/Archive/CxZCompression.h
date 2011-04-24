/****************************************************************************
* Class name:  CxZCompression
* Description: архивирование с помощбю ZLib
* File name:   CxZCompression.h
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib, VCL
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     09.06.2010 10:55:58
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xVCL_Archive_CxZCompressionH
#define xVCL_Archive_CxZCompressionH
//---------------------------------------------------------------------------
#include <xVCL/xCommon.h>
#include <ZLib.hpp>
//---------------------------------------------------------------------------
class CxZCompression {
	public:
		static BOOL bCompress     (const String &csInFilePath, const String &csOutFilePath, Zlib::TCompressionLevel clLevel, BOOL bIsDeleteSource);
		static BOOL bDecompress   (const String &csInFilePath, const String &csOutFilePath, BOOL bIsDeleteSource);

	private: 
		            CxZCompression();
	               ~CxZCompression();
};
//---------------------------------------------------------------------------
#endif //xVCL_Archive_CxZCompressionH
