/****************************************************************************
* Class name:  CxPKCS11
* Description: Aladdin eToken, PKCS #11
* File name:   CxPKCS11.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib, Aladdin eToken SDK
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     25.02.2010 13:31:54
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_CxPKCS11H
#define XLib_CxPKCS11H
//---------------------------------------------------------------------------
#include <XLib/xCommon.h>
#include <XLib/Fso/CxStdioFile.h>
#include <XLib/Fso/CxDll.h>
#include <XLib/Log/CxTraceLog.h>
#include <XLib/Debug/CxPerform.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>     
#include <mbstring.h>   //_mbscpy _mbscat
#include <winscard.h>   //vEnumReaderList
#include <wincrypt.h>   //vEnumReaderList
#include <iostream>     //STL vEnumReaderList
#include <iomanip>      //STL vEnumReaderList
#include <vector>       //STL vEnumReaderList
#include <memory>    
#include <map>
#include <fstream>
//---------------------------------------------------------------------------
#include <XLib/PKCS11/Common.h>
//---------------------------------------------------------------------------
class CxPKCS11 : public CxNonCopyable {
	public:
		typedef std::map<tString, tString> TStringMap;
		
		         CxPKCS11        ();
		virtual ~CxPKCS11        ();
		
		//-------------------------------------
		//Initialize
		BOOL bInitialize         ();	/*C_Initialize*/
		BOOL bFinalize           ();	/*C_Finalize*/
        BOOL bIsInitialized      () const;

		CK_FUNCTION_LIST_PTR pGetFuncList() const;
		
		//-------------------------------------
		//Slot
		BOOL bGetSlotList        (CK_BBOOL bTokenPresent, CK_SLOT_ID_PTR pSlotList, CK_ULONG_PTR pulCount);	/*C_GetSlotList*/
		BOOL bGetSlotInfo        (CK_SLOT_ID slotID, CK_SLOT_INFO_PTR pInfo);								/*C_GetSlotInfo*/	
		BOOL bWaitForSlotEvent   (CK_FLAGS flags, CK_SLOT_ID_PTR pSlot, CK_VOID_PTR pRserved);				/*C_WaitForSlotEvent*/	

		//-------------------------------------
		//Session
		BOOL bOpenSession        (CK_SLOT_ID slotID, CK_FLAGS flags, CK_VOID_PTR pApplication, CK_NOTIFY Notify, CK_SESSION_HANDLE_PTR phSession);	/*C_OpenSession*/		
		BOOL bGetSessionInfo     (CK_SESSION_HANDLE hSession, CK_SESSION_INFO_PTR pInfo);	/*C_GetSessionInfo*/		
		BOOL bSetOperationState	 (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pOperationState, CK_ULONG ulOperationStateLen, CK_OBJECT_HANDLE hEncryptionKey, CK_OBJECT_HANDLE hAuthenticationKey);/*C_SetOperationState*/	
		BOOL bGetOperationState  (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pOperationState, CK_ULONG_PTR pulOperationStateLen);/*C_GetOperationState*/
		BOOL bCloseSession       (CK_SESSION_HANDLE hSession);	/*C_CloseSession*/		
		BOOL bCloseAllSessions   (CK_SLOT_ID slotID);	/*C_CloseAllSessions*/		

		//-------------------------------------
		//Login
		BOOL bLogin              (CK_SESSION_HANDLE hSession, CK_USER_TYPE userType, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);	/*C_Login*/	
		BOOL bLogout             (CK_SESSION_HANDLE hSession);	/*C_Logout*/
		
		//-------------------------------------
		//Info
		BOOL bGetInfo            (CK_INFO_PTR pInfo);	/*C_GetInfo*/
		BOOL bGetTokenInfo       (CK_SLOT_ID slotID, CK_TOKEN_INFO_PTR pInfo);	/*C_GetTokenInfo*/
				
		//-------------------------------------
		//Pin
		BOOL bInitToken          (CK_SLOT_ID slotID, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen, CK_UTF8CHAR_PTR pLabel);	/*C_InitToken*/		
		BOOL bInitPIN            (CK_SESSION_HANDLE hSession, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);		/*C_InitPIN*/
		BOOL bSetPIN             (CK_SESSION_HANDLE hSession, CK_UTF8CHAR_PTR pOldPin, CK_ULONG ulOldLen, CK_UTF8CHAR_PTR pNewPin, CK_ULONG ulNewLen);	/*C_SetPIN*/		

		//Utils
		////tString sChangeUserPin  (const AnsiString &casOldUserPin, const AnsiString &casNewUserPin);
		////tString sChangeSOPin    (const AnsiString &casOldSOPin,   const AnsiString &casNewSOPin);
		
        //-------------------------------------
		//Mechanism
		BOOL bGetMechanismInfo   (CK_SLOT_ID slotID, CK_MECHANISM_TYPE type, CK_MECHANISM_INFO_PTR pInfo);	/*C_GetMechanismInfo*/	
		BOOL bGetMechanismList   (CK_SLOT_ID slotID, CK_MECHANISM_TYPE_PTR pMechanismList, CK_ULONG_PTR pulCount);	/*C_GetMechanismList*/			
		
		//-------------------------------------
		//Object
		BOOL bCreateObject	     (CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phObject);	/*C_CreateObject*/	
		BOOL bGetObjectSize	     (CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject, CK_ULONG_PTR pulSize);	/*C_GetObjectSize*/	
		BOOL bCopyObject	     (CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phNewObject);	/*C_CopyObject*/		

		BOOL bFindObjectsInit    (CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR  pTemplate, CK_ULONG ulCount);	/*C_FindObjectsInit*/				
		BOOL bFindObjects	     (CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount, CK_ULONG_PTR pulObjectCount);	/*C_FindObjects*/
		BOOL bFindObjectsFinal   (CK_SESSION_HANDLE hSession);		/*C_FindObjectsFinal*/			

		BOOL bDestroyObject	     (CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject);	/*C_DestroyObject*/

		BOOL bGetAttributeValue  (CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);	/*C_GetAttributeValue*/	
		BOOL bSetAttributeValue  (CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount);	/*C_SetAttributeValue*/	
		
		//Utils
		BOOL bUtil_FindObjects   (CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, std::vector<CK_OBJECT_HANDLE> *pvecObjectHandles);	

		//-------------------------------------
		//Key
		BOOL bGenerateKey	     (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phKey); 	/*C_GenerateKey*/        
		BOOL bGenerateKeyPair    (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pPublicKeyTemplate, CK_ULONG ulPublicKeyAttributeCount, CK_ATTRIBUTE_PTR pPrivateKeyTemplate, CK_ULONG ulPrivateKeyAttributeCount, CK_OBJECT_HANDLE_PTR phPublicKey, CK_OBJECT_HANDLE_PTR phPrivateKey); /*C_GenerateKeyPair*/
		BOOL bDeriveKey	         (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hBaseKey, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulAttributeCount, CK_OBJECT_HANDLE_PTR phKey); /*C_DeriveKey*/	
		BOOL bWrapKey	         (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hWrappingKey, CK_OBJECT_HANDLE hKey, CK_BYTE_PTR pWrappedKey, CK_ULONG_PTR pulWrappedKeyLen); /*C_WrapKey*/	
		BOOL bUnwrapKey	         (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hUnwrappingKey, CK_BYTE_PTR pWrappedKey, CK_ULONG ulWrappedKeyLen, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulAttributeCount, CK_OBJECT_HANDLE_PTR phKey); /*C_UnwrapKey*/	

		//-------------------------------------
		//Encrypt
		BOOL bEncrypt		     (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pEncryptedData, CK_ULONG_PTR pulEncryptedDataLen);	/*C_Encrypt*/
		BOOL bEncryptFinal		 (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pLastEncryptedPart, CK_ULONG_PTR pulLastEncryptedPartLen );	/*C_EncryptFinal*/	
		BOOL bEncryptInit		 (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR  pMechanism, CK_OBJECT_HANDLE hKey);	/*C_EncryptInit*/	
		BOOL bEncryptUpdate		 (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR  pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);	/*C_EncryptUpdate*/	
		BOOL bSeedRandom		 (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSeed, CK_ULONG ulSeedLen);	/*C_SeedRandom*/
		BOOL bGenerateRandom	 (CK_SESSION_HANDLE hSession, CK_BYTE_PTR RandomData, CK_ULONG ulRandomLen);	/*C_GenerateRandom*/

		//-------------------------------------
		//Decrypt
		BOOL bDecrypt	         (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedData, CK_ULONG ulEncryptedDataLen, CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen);/*C_Decrypt*/
		BOOL bDecryptDigestUpdate(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen );/*C_DecryptDigestUpdate*/		
		BOOL bDecryptFinal	     (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pLastPart, CK_ULONG_PTR pulLastPartLen);/*C_DecryptFinal*/
		BOOL bDecryptInit	     (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);/*C_DecryptInit*/	
		BOOL bDecryptUpdate	     (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen);/*C_DecryptUpdate*/	
		BOOL bDecryptVerifyUpdate(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen );/*C_DecryptVerifyUpdate*/	

		//-------------------------------------
		//Digest
		BOOL bDigest	         (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);/*C_Digest*/
		BOOL bDigestEncryptUpdate(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);	/*C_DigestEncryptUpdate*/
		BOOL bDigestFinal        (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);	/*C_DigestFinal*/	
		BOOL bDigestInit	     (CK_SESSION_HANDLE hSession,	CK_MECHANISM_PTR pMechanism);/*C_DigestInit*/
		BOOL bDigestKey	         (CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hKey);/*C_DigestKey*/	
		BOOL bDigestUpdate       (CK_SESSION_HANDLE hSession,	CK_BYTE_PTR pPart, CK_ULONG ulPartLen);/*C_DigestUpdate*/	

		//-------------------------------------
		//Sign	
		BOOL bSignInit	         (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);/*C_SignInit*/	
		BOOL bSign	             (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen);/*C_Sign*/	
		BOOL bSignUpdate	     (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen);/*C_SignUpdate*/
		BOOL bSignEncryptUpdate	 (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);/*C_SignEncryptUpdate*/	
		BOOL bSignFinal	         (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen);/*C_SignFinal*/			
		BOOL bSignRecoverInit	 (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);/*C_SignRecoverInit*/
		BOOL bSignRecover	     (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen);/*C_SignRecover*/
		
		//-------------------------------------
		//Verify
		BOOL bVerifyInit	     (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);/*C_VerifyInit*/
		BOOL bVerify	         (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen);  /*C_Verify*/	       
		BOOL bVerifyFinal	     (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen);    /*C_VerifyFinal*/
		BOOL bVerifyRecoverInit  (CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);/*C_VerifyRecoverInit*/	
		BOOL bVerifyRecover	     (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen, CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen);	/*C_VerifyRecover*/		
		BOOL bVerifyUpdate	     (CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart, CK_ULONG ulPartLen);    /*C_VerifyUpdate*/

		//-------------------------------------
		//Function
		BOOL bGetFunctionList	 (CK_FUNCTION_LIST_PTR_PTR ppFunctionList);	/*C_GetFunctionList*/	
		BOOL bGetFunctionStatus	 (CK_SESSION_HANDLE hSession); 				/*C_GetFunctionStatus*/	
		BOOL bCancelFunction     (CK_SESSION_HANDLE hSession);				/*C_CancelFunction*/
		BOOL bGetFunctionListEx  ();										/*ETC_GetFunctionListEx*/

		
		
		
		
		
		/////*+*/ULONG ulInsertedTokens               ();
		/////*-*/ULONG ulSlots                        ();
		/////*-*/ULONG *ulGetSlotList                 (/*ULONG &ulSlotCount*/);
		/////*-*/ULONG ulGetSlotType                  (ULONG ulSlotId);
		/////*+*/BOOL  bGetLibraryInfo                (TStringMap &smLibraryInfo);
		/////*+*/BOOL  bGetTokenInfo                  (ULONG ulSlotId, TStringMap &smInfo);
		

		//-------------------------------------
		// OBJECT MANAGEMENT FUNCTIONS
		/*+*/BOOL		 bIsDataObjectExists(ULONG ulSlotId, CHAR *pszUserPIN, CHAR *pszObjectName/*ID*/, CHAR *pszLabel, CHAR *pszValue);
		/*+*/tString 	 sGetDataObject     (ULONG ulSlotId, CHAR *pszUserPIN, CHAR *pszObjectName/*ID*/); //new
		/*+*/BOOL        bCreateDataObject  (ULONG ulSlotId, CHAR *pszUserPIN, CHAR *pszObjectName/*ID*/, CHAR *pszLabel, CHAR *pszValue);
		/*+*/BOOL 	     bDeleteDataObject  (ULONG ulSlotId, CHAR *pszUserPIN, CHAR *pszObjectName/*ID*/);
		/*+*/BOOL 	     bChangeDataObject  (ULONG ulSlotId, CHAR *pszUserPIN, CHAR *pszObjectName/*ID*/, CHAR *pszNewLabel, CHAR *pszNewValue);
		/*+*/BOOL 	     bClearDataObject   (ULONG ulSlotId, CHAR *pszUserPIN, CHAR *pszObjectName/*ID*/);
		/*-*/////ExportObject();
		/*-*/////CopyObject();
		/*-*/////ImportObject();
		
		//-------------------------------------
		//ENCRYPTION FUNCTIONS
		
		//DES
        /*+*/BOOL        bEncryptDES    (ULONG      ulSlotId,
                                                  CHAR     *pszUserPIN, 
                                         UCHAR     *pszKey,        ULONG  uiKeyLen,
                                         UCHAR     *pszIv,         ULONG  uiIvLen,
                                         UCHAR     *pszPlainText,  ULONG  uiPlainTextLen,
                                         UCHAR     *pszCipherText, ULONG &ulCipherTextLen);
		/*-*/BOOL        bDecryptDES   (ULONG      ulSlotId,
										CHAR               *pszUserPIN,    
										UCHAR      *pucKey,        ULONG  ulKeyLen,
										UCHAR      *pucIv,         ULONG  ulIvLen,
										UCHAR      *pucCipherText, ULONG  ulCipherTextLen,
										UCHAR      *pucPlainText,  ULONG &ulPlainTextLen);

    	/*-*/BOOL		 bEncryptFileDES(const tString &csFilePathIn, 
										 const tString &csFilePathOut,
										 CHAR              *pszUserPIN,    
										 UCHAR     *pszKey,        ULONG  uiKeyLen,
										 UCHAR     *pszIv,         ULONG  uiIvLen);
		/*-*/BOOL		 bDecryptFileDES(const tString &csFilePathIn, 
										 const tString &csFilePathOut,
										 CHAR              *pszUserPIN,    
										 UCHAR     *pszKey,        ULONG  uiKeyLen,
										 UCHAR     *pszIv,         ULONG  uiIvLen);
        
		//DES3
		/*+*/BOOL        bEncryptDES3   (ULONG      ulSlotId,
										          CHAR     *pszUserPIN,    
										 UCHAR     *pszKey,        ULONG  uiKeyLen,
										 UCHAR     *pszIv,         ULONG  uiIvLen,
										 UCHAR     *pszPlainText,  ULONG  uiPlainTextLen,
										 UCHAR     *pszCipherText, ULONG &ulCipherTextLen);
		/*+*/BOOL        bDecryptDES3   (ULONG      ulSlotId,
										          CHAR     *pszUserPIN,    
										 UCHAR     *pszKey,        ULONG  uiKeyLen,
										 UCHAR     *pszIv,         ULONG  uiIvLen,
										 UCHAR     *pszCipherText, ULONG  ulCipherTextLen,
										 UCHAR     *pszPlainText,  ULONG &uiPlainTextLen);
		
		/*-*/BOOL        bEncryptFileDES3   ();
		/*-*/BOOL        bDecryptFileDES3   ();

		//RSA
		/*-*/BOOL		 bGenerateRSAKeyPair(ULONG  ulSlotId,
									         CHAR          *pszUserPIN/*CK_SESSION_HANDLE hSession*/, 
											 /*CK_UTF8CHAR*/CHAR *pszPublicKeyLabel, 
											 CHAR          *pszPrivateKeyLabel, 
											 CK_ULONG       ulModulus,
											 UCHAR         *pucPlainText,  ULONG ulPlainTextLen,
										     UCHAR         *pucCipherText, ULONG &ulCipherTextLen
											 
											 
											 );	    ///*CK_UTF8CHAR*/CHAR *
		/*-*/BOOL        bEncryptRSA        ();
		/*-*/BOOL        bDecryptRSA        ();
		/*-*/BOOL        bEncryptFileRSA    ();
		/*-*/BOOL        bDecryptFileRSA    ();

		//-------------------------------------
		//RANDOM NUMBER GENERATION FUNCTIONS
		BOOL  bGenRandomBytes(ULONG  ulSlotId, UCHAR *pucBuff, ULONG ulBuffSize);	//[+]
		
		//-------------------------------------
		//GetCertificate
		/*-*/////tString sGetCertificate(DWORD dwSlotId);
		/*-*/////BOOL       bCreateSelfCertificate(CHAR *pszReaderName, CHAR *pszPassword, CHAR *pszSubject, CHAR *pszOrganization, CHAR *pszCountry) ;
		/*-*/////Generate(); //public key, private key
	
		//-------------------------------------
		//память
		//сколько всего
		//размер файла
		//сколько осталось

		//-------------------------------------
		/*-*/////BOOL bEnableUSB();										//доступен ли USB-порт
		/*-*/////RenameEToken(const AnsiString &asNewName);				//переименовать токен
		/*-*/////BOOL bIsSingleEtokenPresent(); 						//Отключите все прочие е Token.
		/*-*/////имя ридера
		
		/*-*///бэкап
		/*-*/////tString sGeneratePassword();							        //генерировать пароль
		/*-*/////BOOL        bChangePassword(const AnsiString &asNewPassword);	    //поменять пароль

   private:
		CxTraceLog           _m_tlLog;
        CK_FUNCTION_LIST_PTR _m_pFunc;
		BOOL                 _m_bRes;
		CK_RV                _m_ulRes;

        BOOL                 _m_bIsInit;
		
		CxDll				 _m_dllETPKCS11;
		CxDll				 _m_dllETSAPI;
		BOOL                 _bLoadETPKCS11();
        BOOL                 _bLoadETSAPI  ();
};
//---------------------------------------------------------------------------
#endif	//XLib_CxPKCS11H
