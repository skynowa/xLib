/****************************************************************************
* Class name:  CxBase64
* Description: Base64
* File name:   CxBase64.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     07.07.2009 12:22:00
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Crypt_CxBase64H
#define xLib_Crypt_CxBase64H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxBase64 : public CxNonCopyable {
	public:
        static std::string sEncode     (const std::string &csStr);
        static std::string sDecode     (const std::string &csStr);
        static BOOL        bIsCharValid(INT iChar);

	private:
};
//---------------------------------------------------------------------------
#endif	//xLib_Crypt_CxBase64H
