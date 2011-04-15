/****************************************************************************
* Class name:  CxEncrypt
* Description: Pkcs11 ����������
* File name:   CxEncrypt.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.03.2010 13:10:51
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxEncryptH
#define xLib_Pkcs11_CxEncryptH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxEncrypt : public CxNonCopyable {
	public:
		                     CxEncrypt      (const CxPkcs11 &cPkcs11, const CxSession &cSession);
	                        ~CxEncrypt      ();
	   
	   	BOOL                 bInit	        (CK_MECHANISM_PTR  pMechanism, CK_OBJECT_HANDLE hKey);
		BOOL                 bMake    		(CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pEncryptedData, CK_ULONG_PTR pulEncryptedDataLen);	
		BOOL                 bUpdate	    (CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR  pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);	
		BOOL                 bFinal	        (CK_BYTE_PTR pLastEncryptedPart, CK_ULONG_PTR pulLastEncryptedPartLen );	
			
		//Utils
		BOOL                 bMakeFile      (const tString &csInFilePath, const tString &csOutFilePath, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);		
	   	
	private:
		BOOL                 _m_bRes;
		CK_RV                _m_ulRes;

		CK_FUNCTION_LIST_PTR _m_pFunc;
		CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxEncryptH
