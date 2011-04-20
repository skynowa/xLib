/**********************************************************************
*   CYug_eToken.h   (RTE 4.53)
*
***********************************************************************/


#pragma warning(disable: 4267)	//'initializing' : conversion from 'size_t' to 'CK_ULONG', possible loss of data

#ifndef CYug_eTokenH
#define CYug_eTokenH
//---------------------------------------------------------------------------
#include "SDK 4.53\pkcs11.h"
#include "SDK 4.53\eTSAPI.h"
#include "SDK 4.53\otp-pkcs11.h"

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
//---------------------------------------------------------------------------
#define MSG_WARNING_(MSG)  MessageBox(0, (MSG).c_str(), "Внимание",   MB_OK + MB_ICONSTOP        + MB_TOPMOST)
#define MSG_INFO_(MSG)     MessageBox(0, (MSG).c_str(), "Информация", MB_OK + MB_ICONINFORMATION + MB_TOPMOST)

#define APPLICATION_TITLE "eToken"
#define EMPTY_MSG_         "отсутствует"
#define ETPKCS11_PATH     "DLL\\eTPKCS11.dll"	//путь к eTPKCS11.dll
#define ETSAPI_PATH       "DLL\\eTSAPI.dll"     //путь к eTSAPI.dll
#define TRUE_MSG          "да"   				//FALSE_MSG >= TRUE_MSG
#define FALSE_MSG         "нет"
#define TOKEN_NON_PRESENT  - 1

typedef std::map<std::string, std::string, std::less<std::string>> TStringMap;
//---------------------------------------------------------------------------
class CYug_eToken : public CXNonCopyable {
	public:
	    /*+*/CYug_eToken();
		/*+*/~CYug_eToken();
		
		//-------------------------------------
		//GENERAL-PURPOSE FUNCTIONS
		/*+#C_Initialize*/
		/*+#C_Finalize*/
		/*#C_GetInfo*/
		/*#C_GetFunctionList*/
		
		/*+*/bool bInitialize();
		/*+*/bool bFinalize();
		
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
        /*+*/bool              bGetLibraryInfo                (TStringMap &smLibraryInfo);
        /*+*/bool              bGetTokenInfo                  (unsigned long int ulSlotId, TStringMap &smInfo);

		/*-*/////std::string sChangeUserPin  (const AnsiString &casOldUserPin, const AnsiString &casNewUserPin);
		/*-*/////std::string sChangeSOPin    (const AnsiString &casOldSOPin,   const AnsiString &casNewSOPin);
		/*-*/////bool        bInitializeToken(const AnsiString &asFormatPass,  const AnsiString &asUserPass);
		
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
		
		/*+*/bool		 bIsDataObjectExists(unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszLabel, char *pszValue);
		/*+*/std::string sGetDataObject     (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/); //new
		/*+*/bool        bCreateDataObject  (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszLabel, char *pszValue);
		/*+*/bool 	     bDeleteDataObject  (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/);
		/*+*/bool 	     bChangeDataObject  (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszNewLabel, char *pszNewValue);
		/*+*/bool 	     bClearDataObject   (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/);
		/*-*/////ExportObject();
		/*-*/////CopyObject();
		/*-*/////ImportObject();
		
		//-------------------------------------
		//ENCRYPTION FUNCTIONS
		/*#C_EncryptInit*/
		/*#C_Encrypt*/
		/*#C_EncryptUpdate*/
		/*#C_EncryptFinal*/

        /*+*/bool        bEncryptDES(unsigned long  ulSlotId,
                                              char *pszUserPIN,    unsigned long int  ulUserPINLen,
                                     unsigned char *pszKey,        unsigned long int  uiKeyLen,
                                     unsigned char *pszIv,         unsigned long int  uiIvLen,
                                     unsigned char *pszPlainText,  unsigned long int  uiPlainTextLen,
                                     unsigned char *pszCipherText, unsigned long int &ulCipherTextLen);

        /*+*/bool        bDecryptDES(unsigned long  ulSlotId,
                                              char *pszUserPIN,    unsigned long int  ulUserPINLen,
                                     unsigned char *pszKey,        unsigned long int  uiKeyLen,
                                     unsigned char *pszIv,         unsigned long int  uiIvLen,
                                     unsigned char *pszPlainText,  unsigned long int &uiPlainTextLen,
                                     unsigned char *pszCipherText, unsigned long int  ulCipherTextLen);

		std::string CYug_eToken::sDecryptTextDES(unsigned long ulSlotId,
			char *pszUserPIN,    unsigned long int  ulUserPINLen,
			char *pszKey,        unsigned long int  uiKeyLen,
			char *pszIv,         unsigned long int  uiIvLen,
			char *pszPlainText,  unsigned long int &uiPlainTextLen,
			char *pszCipherText, unsigned long int  ulCipherTextLen);

        /*-*/std::string sEncryptFileDES();
        /*-*/std::string sDecryptFileDES();
        
		/////*-*/std::string sEncryptTextDES3(unsigned long ulSlotId,
  ////                                        unsigned char *pszUserPIN,    unsigned long int  ulUserPINLen,
  ////                                        unsigned char *pszKey,        unsigned long int  uiKeyLen,
  ////                                        unsigned char *pszIv,         unsigned long int  uiIvLen,
  ////                                        unsigned char *pszPlainText,  unsigned long int  uiPlainTextLen,
  ////                                        unsigned char *pszCipherText, unsigned long int &ulCipherTextLen);
  ////      /*-*/std::string sDecryptTextDES3(const unsigned long ulSlotId,
  ////                                        const unsigned char *pszUserPIN,    unsigned long int  ulUserPINLen,
  ////                                        const unsigned char *pszKey,        unsigned long int  uiKeyLen,
  ////                                        const unsigned char *pszIv,         unsigned long int  uiIvLen,
  ////                                              unsigned char *pszPlainText,  unsigned long int &uiPlainTextLen,
  ////                                        const unsigned char *pszCipherText, unsigned long int  ulCipherTextLen);
        /*-*/////std::string sEncryptFileDES3();
        /*-*/////std::string sDecryptFileDES3();

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
		
		//-------------------------------------
		//PARALLEL FUNCTION MANAGEMENT FUNCTIONS
		/*#C_GetFunctionStatus*/
		/*#C_CancelFunction*/

		//-------------------------------------
		//GetCertificate
		/*-*/////std::string sGetCertificate(DWORD dwSlotId);
		/*-*/////bool       bCreateSelfCertificate(char *pszReaderName, char *pszPassword, char *pszSubject, char *pszOrganization, char *pszCountry) ;
		/*-*/////Generate(); //public key, private key
	
		//-------------------------------------
		//память
		//сколько всего
		//размер файла
		//сколько осталось

		//-------------------------------------
		/*-*/////bool bEnableUSB();										//доступен ли USB-порт
		/*-*/////RenameEToken(const AnsiString &asNewName);				//переименовать токен
		/*-*/////bool bIsSingleEtokenPresent(); 						//Отключите все прочие е Token.
		/*-*/////имя ридера
		
		/*-*///бэкап
		/*-*/////std::string sGeneratePassword();							        //генерировать пароль
		/*-*/////bool        bChangePassword(const AnsiString &asNewPassword);	    //поменять пароль

   private:
        bool                   m_bWasInit;
        CK_FUNCTION_LIST_PTR   m_pFunctionList;

        //-------------------------------------
		/*+*/bool              bLoadPKCS11();
        /*+*/bool              bLoadETSAPI();
		//bInitializeToken()
		/*-*/////unsigned long     dwSelectSlot(char *readerName);
		/*-*/////unsigned long int dwLocateToken();
		/*-*/////bool              bCheckPinPolicy(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject);

		/*+*///--AnsiString 	   asEtokenErrorString(unsigned long int ulRV);
        /*-*/std::string       sEtokenErrorString(unsigned long int ulRV);
};
//---------------------------------------------------------------------------
#endif