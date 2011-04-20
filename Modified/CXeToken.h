/**********************************************************************
*   CXeToken.h   (RTE 4.53)
*
***********************************************************************/


////#pragma warning(disable: 4267)	//'initializing' : conversion from 'size_t' to 'CK_ULONG', possible loss of data

#ifndef XLib_CXeTokenH
#define XLib_CXeTokenH
//---------------------------------------------------------------------------
#include <XLib/Common.h>
#include <XLib/Fso/CXDll.h>
#include <XLib/Log/CXTraceLog.h>
#include <XLib/CXString.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>     
#include <mbstring.h>   //_mbscpy _mbscat
#include <winscard.h>   //vEnumReaderList
#include <wincrypt.h>   //vEnumReaderList
#include <iostream>     //STL vEnumReaderList
#include <iomanip>      //STL vEnumReaderList
#include <vector>       //STL vEnumReaderList
#include <memory>       //smart pointer
#include <map>

#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <map>

#include "D:/XLib/Test/CXeToken/SDK 4.53/pkcs11.h"
#include "D:/XLib/Test/CXeToken/SDK 4.53/eTSAPI.h"
#include "D:/XLib/Test/CXeToken/SDK 4.53/otp-pkcs11.h"
//---------------------------------------------------------------------------
typedef std::map< std::string, std::string, std::less<std::string> > TStringMap;
//---------------------------------------------------------------------------
class CXeToken : public CXNonCopyable {
	public:
		struct stTokenInfo {
			std::string sCkaSapiCardId;
			std::string sCkaSapiCardType;
			std::string sCkaSapiCardVersion;
			std::string sCkaSapiCaseModel;
			std::string sCkaSapiColor;
			std::string sCkaSapiFips;
			std::string sCkaSapiFipsSupported;
			std::string sCkaSapiFwRevision;
			std::string sCkaSapiFwVersion;
			std::string sCkaSapiHasBattery;
			std::string sCkaSapiHasLcd;
			std::string sCkaSapiHasSo;
			std::string sCkaSapiHasUser;
			std::string sCkaSapiHmacSha1;
			std::string sCkaSapiHmacSha1Supported;
			std::string sCkaSapiHwInternal;
			std::string sCkaSapiHwVersion;
			std::string sCkaSapiInitPinReq;
			std::string sCkaSapiMayInit;
			std::string sCkaSapiModel;
			std::string sCkaSapiProductionDate;
			std::string sCkaSapiProductName;
			std::string sCkaSapiRealColor;
			std::string sCkaSapiRsa2048;
			std::string sCkaSapiRsa2048Supported;
			std::string sCkaSapiSerial;
			std::string sCkaSapiTokenId;
			std::string sClockOnToken;
			std::string sDualCryptoOperations;
			std::string sFirmwareVersionMajor;
			std::string sFirmwareVersionMinor;
			std::string sFreePrivateMemory;
			std::string sFreePublicMemory;
			std::string sHardwareVersionMajor;
			std::string sHardwareVersionMinor;
			std::string sHasProtectedAuthenticationPath;
			std::string sIsWriteProtected;
			std::string sLabel;
			std::string sLoginRequired;
			std::string sManufacturerId;
			std::string sMaxPinLen;
			std::string sMaxRwSessionCount;
			std::string sMaxSessionCcount;
			std::string sMinPinLen;
			std::string sModel2;
			std::string sRandomNumberGenerator;
			std::string sRestoreKeyNotNeeded;
			std::string sRsaMechanismMaxKeySize;
			std::string sSerialNumber;
			std::string sSessionCount;
			std::string sTotalPrivateMemory;
			std::string sTotalPublicMemory;
			std::string sUsersPinIsSet;
		};
		
		/*+*/CXeToken();
		/*+*/~CXeToken();
		
		//-------------------------------------
		//GENERAL-PURPOSE FUNCTIONS
		/*+#C_Initialize*/
		/*+#C_Finalize*/
		/*#C_GetInfo*/
		/*#C_GetFunctionList*/
		
		/*+*/BOOL bInitialize();
		/*+*/BOOL bFinalize();
		
		//-------------------------------------
		//SLOT AND TOKEN MANAGEMENT FUNCTIONS
		/*#C_GetSlotList*/
		/*#C_GetSlotInfo*/
		/*+#C_GetTokenInfo*/
		/*+#C_WaitForSlotEvent*/
		/*#C_GetMechanismList*/
		/*#C_GetMechanismInfo*/
		/*#C_InitToken*/
		/*#C_InitPIN*/
		/*#C_SetPIN*/

		/*+*/unsigned long int ulInsertedTokens               ();
		/*-*/unsigned long int ulSlots                        ();
        /*-*/unsigned long int *ulGetSlotList                 (/*unsigned long int &ulSlotCount*/);
        /*-*/unsigned long     ulGetSlotType                  (unsigned long ulSlotId);
		/*+*/unsigned long int ulWaitForSlotEvent             ();
        /*+*/BOOL              bGetLibraryInfo                (TStringMap &smLibraryInfo);
        /*+*/BOOL              bGetTokenInfo                  (unsigned long int ulSlotId, TStringMap &smInfo);

		/*-*/////std::string sChangeUserPin  (const AnsiString &casOldUserPin, const AnsiString &casNewUserPin);
		/*-*/////std::string sChangeSOPin    (const AnsiString &casOldSOPin,   const AnsiString &casNewSOPin);
		/*-*/////BOOL        bInitializeToken(const AnsiString &asFormatPass,  const AnsiString &asUserPass);
		
		//-------------------------------------
		//SESSION MANAGEMENT FUNCTIONS
		/*#C_OpenSession*/
		/*#C_CloseSession*/
		/*#C_CloseAllSessions*/
		/*#C_GetSessionInfo*/
		/*#C_GetOperationState*/
		/*#C_SetOperationState*/
		/*#C_Login*/
		/*#C_Logout*/
		
		/*-*/////LoginUser();
		/*-*/////LogoutUser();
        /*-*/////LoginSO();
		/*-*/////LogoutSO();
		
		//-------------------------------------
		// OBJECT MANAGEMENT FUNCTIONS
		/*#C_CreateObject*/
		/*#C_CopyObject*/
		/*#C_DestroyObject*/
		/*#C_GetObjectSize*/
		/*#C_GetAttributeValue*/
		/*#C_SetAttributeValue*/
		/*#C_FindObjectsInit*/
		/*#C_FindObjects*/
		/*#C_FindObjectsFinal*/
		
		/*+*/BOOL		 bIsDataObjectExists(unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszLabel, char *pszValue);
		/*+*/std::string sGetDataObject     (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/); //new
		/*+*/BOOL        bCreateDataObject  (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszLabel, char *pszValue);
		/*+*/BOOL 	     bDeleteDataObject  (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/);
		/*+*/BOOL 	     bChangeDataObject  (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszNewLabel, char *pszNewValue);
		/*+*/BOOL 	     bClearDataObject   (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/);
		/*-*/////ExportObject();
		/*-*/////CopyObject();
		/*-*/////ImportObject();
		
		//-------------------------------------
		//ENCRYPTION FUNCTIONS
		/*#C_EncryptInit*/
		/*#C_Encrypt*/
		/*#C_EncryptUpdate*/
		/*#C_EncryptFinal*/
		
		//DES
        /*+*/BOOL        bEncryptDES    (unsigned long      ulSlotId,
                                                  char     *pszUserPIN, 
                                         unsigned char     *pszKey,        unsigned long int  uiKeyLen,
                                         unsigned char     *pszIv,         unsigned long int  uiIvLen,
                                         unsigned char     *pszPlainText,  unsigned long int  uiPlainTextLen,
                                         unsigned char     *pszCipherText, unsigned long int &ulCipherTextLen);
		/*-*/BOOL        bDecryptDES   (unsigned long      ulSlotId,
										char               *pszUserPIN,    
										unsigned char      *pucKey,        unsigned long int  ulKeyLen,
										unsigned char      *pucIv,         unsigned long int  ulIvLen,
										unsigned char      *pucCipherText, unsigned long int  ulCipherTextLen,
										unsigned char      *pucPlainText,  unsigned long int &ulPlainTextLen);

    	/*-*/BOOL		 bEncryptFileDES(const std::string &csFilePathIn, 
										 const std::string &csFilePathOut,
										 char              *pszUserPIN,    
										 unsigned char     *pszKey,        unsigned long int  uiKeyLen,
										 unsigned char     *pszIv,         unsigned long int  uiIvLen);
		/*-*/BOOL		 bDecryptFileDES(const std::string &csFilePathIn, 
										 const std::string &csFilePathOut,
										 char              *pszUserPIN,    
										 unsigned char     *pszKey,        unsigned long int  uiKeyLen,
										 unsigned char     *pszIv,         unsigned long int  uiIvLen);
        
		//DES3
		/*+*/BOOL        bEncryptDES3   (unsigned long      ulSlotId,
										          char     *pszUserPIN,    
										 unsigned char     *pszKey,        unsigned long int  uiKeyLen,
										 unsigned char     *pszIv,         unsigned long int  uiIvLen,
										 unsigned char     *pszPlainText,  unsigned long int  uiPlainTextLen,
										 unsigned char     *pszCipherText, unsigned long int &ulCipherTextLen);
		/*+*/BOOL        bDecryptDES3   (unsigned long      ulSlotId,
										          char     *pszUserPIN,    
										 unsigned char     *pszKey,        unsigned long int  uiKeyLen,
										 unsigned char     *pszIv,         unsigned long int  uiIvLen,
										 unsigned char     *pszCipherText, unsigned long int  ulCipherTextLen,
										 unsigned char     *pszPlainText,  unsigned long int &uiPlainTextLen);
		
		/*-*/BOOL        bEncryptFileDES3   ();
		/*-*/BOOL        bDecryptFileDES3   ();

		//RSA
		/*-*/BOOL		 bGenerateRSAKeyPair(unsigned long  ulSlotId,
									         char          *pszUserPIN/*CK_SESSION_HANDLE hSession*/, 
											 /*CK_UTF8CHAR*/char *pszPublicKeyLabel, 
											 char          *pszPrivateKeyLabel, 
											 CK_ULONG       ulModulus,
											 UCHAR         *pucPlainText,  ULONG ulPlainTextLen,
										     UCHAR         *pucCipherText, ULONG &ulCipherTextLen
											 
											 
											 );	    ///*CK_UTF8CHAR*/char *
		/*-*/BOOL        bEncryptRSA        ();
		/*-*/BOOL        bDecryptRSA        ();
		/*-*/BOOL        bEncryptFileRSA    ();
		/*-*/BOOL        bDecryptFileRSA    ();

		//-------------------------------------
		//DECRYPTION FUNCTIONS
		/*#C_DecryptInit*/
		/*#C_Decrypt*/
		/*#C_DecryptUpdate*/
		
		//-------------------------------------
		//MESSAGE DIGESTING FUNCTIONS
		/*#C_DigestInit*/
		/*#C_Digest*/
		/*#C_DigestUpdate*/
		/*#C_DigestKey*/
		/*#C_DigestFinal*/
		
		//-------------------------------------
		//SIGNING AND MACing FUNCTIONS
		/*#C_SignInit*/
		/*#C_Sign*/
		/*#C_SignUpdate*/
		/*#C_SignFinal*/
		/*#C_SignRecoverInit*/
		/*#C_SignRecover*/
		
		//-------------------------------------
		//FUNCTIONS FOR VERIFYING SIGNATURES AND MACs
		/*#C_VerifyInit*/
		/*#C_Verify*/
		/*#C_VerifyUpdate*/
		/*#C_VerifyFinal*/
		/*#C_VerifyRecoverInit*/
		/*#C_VerifyRecover*/
		
		//-------------------------------------
		//DUAL-FUNCTION CRYPTOGRAPHIC FUNCTIONS
		/*#C_DigestEncryptUpdate*/
		/*#C_DecryptDigestUpdate*/
		/*#C_SignEncryptUpdate*/
		/*#C_DecryptVerifyUpdate*/
		
		//-------------------------------------
		//KEY MANAGEMENT FUNCTIONS
		/*#C_GenerateKey*/
		/*#C_GenerateKeyPair*/
		/*#C_WrapKey*/
		/*#C_UnwrapKey*/
		/*#C_DeriveKey*/
		
		//-------------------------------------
		//RANDOM NUMBER GENERATION FUNCTIONS
		/*#C_SeedRandom*/
		/*#C_GenerateRandom*/
		BOOL  bGenRandomBytes(unsigned long  ulSlotId, unsigned char *pucBuff, unsigned long int ulBuffSize);	//[+]
		
		//-------------------------------------
		//PARALLEL FUNCTION MANAGEMENT FUNCTIONS
		/*#C_GetFunctionStatus*/
		/*#C_CancelFunction*/

		//-------------------------------------
		//GetCertificate
		/*-*/////std::string sGetCertificate(DWORD dwSlotId);
		/*-*/////BOOL       bCreateSelfCertificate(char *pszReaderName, char *pszPassword, char *pszSubject, char *pszOrganization, char *pszCountry) ;
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
		/*-*/////std::string sGeneratePassword();							        //генерировать пароль
		/*-*/////BOOL        bChangePassword(const AnsiString &asNewPassword);	    //поменять пароль

   private:
		CXTraceLog             _m_tlLog;
              
        BOOL                   _m_bIsInit;
        CK_FUNCTION_LIST_PTR   _m_pFunctionList;

		CXDll				   _m_dllETPKCS11;
		CXDll				   _m_dlllETSAPI;

        //-------------------------------------
		/*+*/BOOL              _bLoadPKCS11();
        /*+*/BOOL              _bLoadETSAPI();
		//bInitializeToken()
		/*-*/////unsigned long     dwSelectSlot(char *readerName);
		/*-*/////unsigned long int dwLocateToken();
		/*-*/////BOOL              bCheckPinPolicy(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject);

		/*+*///--AnsiString 	   asEtokenErrorString(unsigned long int ulRes);
        /*-*/std::string       _sEtokenErrorString(unsigned long int ulRes);
};
//---------------------------------------------------------------------------
#endif	//XLib_CXeTokenH