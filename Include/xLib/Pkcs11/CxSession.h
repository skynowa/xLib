/****************************************************************************
* Class name:  CxSession
* Description: Pkcs11 ������
* File name:   CxSession.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.03.2010 13:04:46
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxSessionH
#define xLib_Pkcs11_CxSessionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxSession : public CxNonCopyable {
	public:
							 CxSession         (const CxPkcs11 &cPkcs11);
						    ~CxSession         ();

	   	CK_SESSION_HANDLE    hGetHandle        () const;
	    BOOL                 bOpen             (CK_SLOT_ID slotID, CK_FLAGS flags, CK_VOID_PTR pApplication, CK_NOTIFY Notify);		
		BOOL                 bGetInfo          (CK_SESSION_INFO_PTR pInfo);
		BOOL 			     bSetOperationState(CK_BYTE_PTR pOperationState, CK_ULONG ulOperationStateLen, CK_OBJECT_HANDLE hEncryptionKey, CK_OBJECT_HANDLE hAuthenticationKey);	
		BOOL 			     bGetOperationState(CK_BYTE_PTR pOperationState, CK_ULONG_PTR pulOperationStateLen);
		BOOL 			     bClose            ();		
		BOOL 	             bCloseAll         (CK_SLOT_ID slotID);	
		
	private:
		BOOL                 _m_bRes;
		CK_RV 				 _m_ulRes;

		CK_FUNCTION_LIST_PTR _m_pFunc;
		CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxSessionH
