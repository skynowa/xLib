/****************************************************************************
* Class name:  CxDecrypt
* Description: Pkcs11 ������������
* File name:   CxDecrypt.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.03.2010 13:11:10
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxDecryptH
#define xLib_Pkcs11_CxDecryptH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxDecrypt : public CxNonCopyable {
	public:
		                      CxDecrypt    (const CxPkcs11 &cPkcs11, const CxSession &cSession);
	                         ~CxDecrypt    ();

		BOOL                  bInit	       (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);	   
	   	BOOL                  bMake	       (CK_BYTE_PTR pEncryptedData, CK_ULONG ulEncryptedDataLen, CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen);
		BOOL                  bUpdate	   (CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen);
		BOOL                  bFinal	   (CK_BYTE_PTR pLastPart, CK_ULONG_PTR pulLastPartLen);
		
		BOOL                  bDigestUpdate(CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen );
		BOOL                  bVerifyUpdate(CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen );
   	
		//Utils
		BOOL                  bMakeFile    (const tString &csInFilePath, const tString &csOutFilePath, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
		
	private:
		BOOL                  _m_bRes;
		CK_RV                 _m_ulRes;

		CK_FUNCTION_LIST_PTR _m_pFunc;
		CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxDecryptH
