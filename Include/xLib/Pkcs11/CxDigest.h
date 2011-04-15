/****************************************************************************
* Class name:  CxDigest
* Description: Pkcs11 �����������
* File name:   CxDigest.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.03.2010 13:12:23
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxDigestH
#define xLib_Pkcs11_CxDigestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxDigest : public CxNonCopyable {
	public:
		                     CxDigest      (const CxPkcs11 &cPkcs11, const CxSession &cSession);
	                        ~CxDigest      ();
	   
	   	BOOL                 bMake	       (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);
		BOOL                 bEncryptUpdate(CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
		BOOL                 bFinal        (CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);		
		BOOL                 bInit	       (CK_MECHANISM_PTR pMechanism);
		BOOL                 bKey	       (CK_OBJECT_HANDLE hKey);	
		BOOL                 bUpdate       (CK_BYTE_PTR pPart, CK_ULONG ulPartLen);
	   	
	private:
		BOOL                 _m_bRes;
		CK_RV                _m_ulRes;

		CK_FUNCTION_LIST_PTR _m_pFunc;
		CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxDigestH
