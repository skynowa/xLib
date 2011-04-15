/****************************************************************************
* Class name:  CxUtils
* Description: Pkcs11 utils
* File name:   CxUtils.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.03.2010 13:15:59
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CXUtilsH
#define xLib_Pkcs11_CXUtilsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxUtils : public CxNonCopyable {
	public:
        static tString sErrorStr(CK_RV ulCode);

	private:
			           CxUtils  ();
			          ~CxUtils  ();
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CXUtilsH
