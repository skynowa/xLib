/****************************************************************************
* Class name:  CxKey
* Description: Pkcs11 key
* File name:   CxKey.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:10:29
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxKeyH
#define xLib_Pkcs11_CxKeyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxKey : public CxNonCopyable {
	public:
		                     CxKey        (const CxPkcs11 &cPkcs11, const CxSession &cSession);
	                        ~CxKey        ();

	   	BOOL                 bGenerate	  (CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pTemplate,          CK_ULONG         ulCount,                   CK_OBJECT_HANDLE_PTR phKey); 	      
		BOOL                 bGeneratePair(CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pPublicKeyTemplate, CK_ULONG         ulPublicKeyAttributeCount, CK_ATTRIBUTE_PTR     pPrivateKeyTemplate, CK_ULONG             ulPrivateKeyAttributeCount, CK_OBJECT_HANDLE_PTR phPublicKey,      CK_OBJECT_HANDLE_PTR phPrivateKey); 
		BOOL                 bDerive	  (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hBaseKey,           CK_ATTRIBUTE_PTR pTemplate,                 CK_ULONG             ulAttributeCount,    CK_OBJECT_HANDLE_PTR phKey); 
		BOOL                 bWrap	      (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hWrappingKey,       CK_OBJECT_HANDLE hKey,                      CK_BYTE_PTR          pWrappedKey,         CK_ULONG_PTR         pulWrappedKeyLen);
		BOOL                 bUnwrap	  (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hUnwrappingKey,     CK_BYTE_PTR      pWrappedKey,               CK_ULONG             ulWrappedKeyLen,     CK_ATTRIBUTE_PTR     pTemplate,                  CK_ULONG             ulAttributeCount, CK_OBJECT_HANDLE_PTR phKey); 

		BOOL                 bSeedRandom	(CK_BYTE_PTR pSeed,       CK_ULONG ulSeedLen);	
		BOOL                 bGenerateRandom(CK_BYTE_PTR pRandomData, CK_ULONG ulRandomLen);	

	private:
		BOOL                 _m_bRes;
		CK_RV                _m_ulRes;

		CK_FUNCTION_LIST_PTR _m_pFunc;
		CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxKeyH
