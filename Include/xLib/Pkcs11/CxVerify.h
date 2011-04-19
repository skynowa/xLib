/****************************************************************************
* Class name:  CxVerify
* Description: Pkcs11 verify
* File name:   CxVerify.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:14:22
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxVerifyH
#define xLib_Pkcs11_CxVerifyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxVerify : public CxNonCopyable {
	public:
		                     CxVerify    (const CxPkcs11 &cPkcs11, const CxSession &cSession);
	                        ~CxVerify    ();
	
		BOOL                 bInit	     (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
		BOOL                 bMake	     (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen);         
		BOOL                 bFinal	     (CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen);    
		BOOL                 bRecoverInit(CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
		BOOL                 bRecover	 (CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen, CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen);		
		BOOL                 bUpdate	 (CK_BYTE_PTR pPart, CK_ULONG ulPartLen);   
	private:
		BOOL                 _m_bRes;
		CK_RV                _m_ulRes;

		CK_FUNCTION_LIST_PTR _m_pFunc;
		CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxVerifyH
