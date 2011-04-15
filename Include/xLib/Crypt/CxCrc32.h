/****************************************************************************
* Class name:  CxCrc32
* Description: Crc32
* File name:   CxCrc32.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     13.09.2010 12:25:59
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Crypt_CxCrc32H
#define xLib_Crypt_CxCrc32H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxCrc32 : public CxNonCopyable {
	public:
		static ULONG   ulCalc        (UCHAR *pucBuff, ULONG ulSize);
		static ULONG   ulCalcFile    (const tString &csFilePath);
		
		static ULONG   ulCalcFast    (UCHAR *pucBuff, ULONG ulSize);
		static ULONG   ulCalcFileFast(const tString &csFilePath);

		static tString sFormatHex    (ULONG ulCrc32);   

	private:
                       CxCrc32       ();
        virtual       ~CxCrc32       ();
};
//---------------------------------------------------------------------------
#endif	//xLib_Crypt_CxCrc32H
