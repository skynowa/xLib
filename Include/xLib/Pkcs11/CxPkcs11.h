/****************************************************************************
* Class name:  CxPkcs11
* Description: Aladdin eToken, PKCS #11
* File name:   CxPkcs11.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.02.2010 13:31:54
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxPkcs11H
#define xLib_Pkcs11_CxPkcs11H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Filesystem/CxDll.h>
//---------------------------------------------------------------------------
class CxPkcs11 : public CxNonCopyable {
	public:
		                     CxPkcs11        ();
		virtual             ~CxPkcs11        ();
		
		CK_FUNCTION_LIST_PTR pGetFuncList    () const;
		
   private:
		BOOL                 _m_bRes;
		CK_RV                _m_ulRes;

		CK_FUNCTION_LIST_PTR _m_pFunc;
		CxDll				 _m_dllETPkcs11;

		BOOL                 _bLoadETPkcs11  ();
		BOOL                 bInitialize     ();	
		BOOL                 bFinalize       ();	
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxPkcs11H
