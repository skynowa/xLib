/**********************************************************************
*	Класс  CEToken (CYug_eToken.h)
*
***********************************************************************/


#ifndef CYug_eTokenH
#define CYug_eTokenH
//---------------------------------------------------------------------------
#include <pkcs11.h>
#include <eTSAPI.h>
#include <otp-pkcs11.h>

#include <stdio.h>
#include <stdlib.h>
#include <mbstring.h>   //_mbscpy _mbscat
#include <winscard.h>   //vEnumReaderList
#include <wincrypt.h>   //vEnumReaderList
#include <iostream>     //STL vEnumReaderList
#include <iomanip>      //STL vEnumReaderList
#include <vector>       //STL vEnumReaderList
#include <memory>       //smart pointer
#include <string.h>     //test

#include <system.hpp>   //AnsiString
#include <Classes.hpp>  //TStringList
//#include <SysUtils.hpp> 
//---------------------------------------------------------------------------
#define DEBUG_(MSG)       MessageBox(0, AnsiString(MSG).c_str(), "Отладка",    MB_OK)
#define MSG_WARNING(MSG)  MessageBox(0, AnsiString(MSG).c_str(), "Внимание",   MB_OK + MB_ICONSTOP        + MB_TOPMOST)
#define MSG_INFO(MSG)     MessageBox(0, AnsiString(MSG).c_str(), "Информация", MB_OK + MB_ICONINFORMATION + MB_TOPMOST)

#define APPLICATION_TITLE "eToken"
#define LOG_FILE          "___Log.txt"
#define EMPTY_MSG         "отсутствует"
#define ETPKCS11_PATH     "DLL\\eTPKCS11.dll"	//путь к eTPKCS11.dll
#define ETSAPI_PATH       "DLL\\eTSAPI.dll"     //путь к eTSAPI.dll
#define TRUE_MSG          "да"   //FALSE_MSG >= TRUE_MSG
#define FALSE_MSG         "нет"
#define TOKEN_NON_PRESENT  - 1
//---------------------------------------------------------------------------
class CEToken {
	public:
	    /*+*/CEToken();
		/*+*/~CEToken();
		
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
		

		/*+*/AnsiString asReadTokenInfo();
		/*+*/int        iInsertedTokens();
		/*-*/int        iSlots();
		/*+*/unsigned long int      dwWaitForSlotEvent         ();
		/*-*///переименовать токен
		/*+*/AnsiString asGetLibraryInfo                       ();
        /*+*/char      *pszGetTokenInfoFast                    (unsigned long int ulSlotId);
		/*+*/AnsiString asGetTokenInfo		   			       (DWORD dwSlotId);
		/*+*/AnsiString asGetPRODUCT_NAME                      (DWORD dwSlotId);
		/*+*/AnsiString asGetMODEL                             (DWORD dwSlotId);
        /*+*/AnsiString asGetFW_VERSION                        (DWORD dwSlotId);
        /*+*/AnsiString asGetFW_REVISION                       (DWORD dwSlotId);
        /*+*/AnsiString asGetHW_VERSION                        (DWORD dwSlotId);
        /*+*/AnsiString asGetHW_INTERNAL                       (DWORD dwSlotId);
        /*+*/AnsiString asGetPRODUCTION_DATE                   (DWORD dwSlotId);
        /*+*/AnsiString asGetCASE_MODEL                        (DWORD dwSlotId);
        /*+*/AnsiString asGetTOKEN_ID                          (DWORD dwSlotId);
        /*+*/AnsiString asGetCARD_ID                           (DWORD dwSlotId);
        /*+*/AnsiString asGetCARD_TYPE                         (DWORD dwSlotId);
        /*+*/AnsiString asGetCARD_VERSION                      (DWORD dwSlotId);
        /*+*/AnsiString asGetSERIAL                            (DWORD dwSlotId);
        /*+*/AnsiString asGetCOLOR                             (DWORD dwSlotId);
        /*+*/AnsiString asGetHAS_BATTERY                       (DWORD dwSlotId);
        /*+*/AnsiString asGetHAS_LCD                           (DWORD dwSlotId);
        /*+*/AnsiString asGetHAS_USER                          (DWORD dwSlotId);
        /*+*/AnsiString asGetHAS_SO                            (DWORD dwSlotId);
        /*+*/AnsiString asGetFIPS                              (DWORD dwSlotId);
        /*+*/AnsiString asGetFIPS_SUPPORTED                    (DWORD dwSlotId);
        /*+*/AnsiString asGetINIT_PIN_REQ                      (DWORD dwSlotId);
        /*+*/AnsiString asGetRSA_2048                          (DWORD dwSlotId);
        /*+*/AnsiString asGetRSA_2048_SUPPORTED                (DWORD dwSlotId);
        /*+*/AnsiString asGetHMAC_SHA1                         (DWORD dwSlotId);
        /*+*/AnsiString asGetHMAC_SHA1_SUPPORTED               (DWORD dwSlotId);
        /*+*/AnsiString asGetREAL_COLOR                        (DWORD dwSlotId);
        /*+*/AnsiString asGetMAY_INIT                          (DWORD dwSlotId);
        /*+*/AnsiString asGetLABEL                             (DWORD dwSlotId);
        /*+*/AnsiString asGetMANUFACTURER_ID                   (DWORD dwSlotId);
        /*+*/AnsiString asGetMODEL_2                           (DWORD dwSlotId);
        /*+*/AnsiString asGetSERIAL_NUMBER                     (DWORD dwSlotId);
        /*+*/AnsiString asGetHARDWARE_VERSION_MAJOR            (DWORD dwSlotId);
        /*+*/AnsiString asGetHARDWARE_VERSION_MINOR            (DWORD dwSlotId);
        /*+*/AnsiString asGetFIRMWARE_VERSION_MAJOR            (DWORD dwSlotId);
        /*+*/AnsiString asGetFIRMWARE_VERSION_MINOR            (DWORD dwSlotId);
        /*+*/AnsiString asGetSESSION_COUNT                     (DWORD dwSlotId);
        /*+*/AnsiString asGetMAX_SESSION_COUNT                 (DWORD dwSlotId);
        /*+*/AnsiString asGetMAX_RW_SESSION_COUNT              (DWORD dwSlotId);
        /*+*/AnsiString asGetMIN_PIN_LEN                       (DWORD dwSlotId);
        /*+*/AnsiString asGetMAX_PIN_LEN                       (DWORD dwSlotId);
        /*+*/AnsiString asGetFREE_PUBLIC_MEMORY                (DWORD dwSlotId);
        /*+*/AnsiString asGetTOTAL_PUBLIC_MEMORY               (DWORD dwSlotId);
        /*+*/AnsiString asGetFREE_PRIVATE_MEMORY               (DWORD dwSlotId);
        /*+*/AnsiString asGetTOTAL_PRIVATE_MEMORY              (DWORD dwSlotId);
        /*+*/AnsiString asGetRANDOM_NUMBER_GENERATOR           (DWORD dwSlotId);
        /*+*/AnsiString asGetIS_WRITE_PROTECTED                (DWORD dwSlotId);
        /*+*/AnsiString asGetLOGIN_REQUIRED                    (DWORD dwSlotId);
        /*+*/AnsiString asGetUSERS_PIN_IS_SET                  (DWORD dwSlotId);
        /*+*/AnsiString asGetRESTORE_KEY_NOT_NEEDED            (DWORD dwSlotId);
        /*+*/AnsiString asGetCLOCK_ON_TOKEN                    (DWORD dwSlotId);
        /*+*/AnsiString asGetHAS_PROTECTED_AUTHENTICATION_PATH (DWORD dwSlotId);
        /*+*/AnsiString asGetDUAL_CRYPTO_OPERATIONS            (DWORD dwSlotId);
        /*+*/AnsiString asGetRSA_MECHANISM_MAX_KEY_SIZE        (DWORD dwSlotId);
		
		/*-*/AnsiString bChangeUserPin  (const AnsiString &casOldUserPin, const AnsiString &casNewUserPin);
		/*-*/AnsiString bChangeSOPin    (const AnsiString &casOldSOPin,   const AnsiString &casNewSOPin);
		/*-*/bool       bInitializeToken(const AnsiString &asFormatPass,  const AnsiString &asUserPass);

		
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
		
		/*-*/////Login();
		/*-*/////Logout();
		
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
		
		
		/*+*/bool		bIsDataObjectExists(unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/, unsigned char *pszLabel, unsigned char *pszValue);
		/*+*/char      *asGetDataObject    (unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/); //new
		/*+*/bool       bCreateDataObject  (unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/, unsigned char *pszLabel, unsigned char *pszValue);
		/*+*/bool 	    bDeleteDataObject  (unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/);
		/*+*/bool 	    bChangeDataObject  (unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/, unsigned char *pszNewLabel, unsigned char *pszNewValue);
		/*+*/bool 	    bClearDataObject   (unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/);
		/*-*/////ExportObject();
		/*-*/////CopyObject();
		/*-*/////ImportObject();
		
		//-------------------------------------
		//ENCRYPTION FUNCTIONS
		/*#C_EncryptInit*/
		/*#C_Encrypt*/
		/*#C_EncryptUpdate*/
		/*#C_EncryptFinal*/
        /*-*/AnsiString asEncryptFileDES(); //(DWORD dwSlotId, const AnsiString& casPlainText, const AnsiString& casPin);
        /*-*/AnsiString asEncryptDES3();

		//-------------------------------------
		//DECRYPTION FUNCTIONS
		/*#C_DecryptInit*/
		/*#C_Decrypt*/
		/*#C_DecryptUpdate*/
		/*#C_DecryptFinal*/
        /*-*/AnsiString asDecryptDES(/*char **argv*/);
        /*-*/AnsiString asDecryptDES3(/*char **argv*/);
		
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
		/*-*/AnsiString asGetCertificate(DWORD dwSlotId);
		/*-*/bool       bCreateSelfCertificate(char *pszReaderName, char *pszPassword, char *pszSubject, char *pszOrganization, char *pszCountry) ;
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
		/*-*/////AnsiString asGeneratePassword();							//генерировать пароль
		/*-*/////bool bChangePassword(const AnsiString &asNewPassword);	    //поменять пароль
		AnsiString asEncryptDES3Text();


        /*+*/unsigned char *asEncryptTextDES(unsigned char *pucUserPIN,    unsigned long int  ulUserPINLen,
                                             unsigned char *pucKey,        unsigned long int  uiKeyLen,
                                             unsigned char *pucIv,         unsigned long int  uiIvLen,
                                             unsigned char *pucPlainText,  unsigned long int  uiPlainTextLen,
                                             unsigned char *pucCipherText, unsigned long int &ulCipherTextLen);

        /*+*/unsigned char *asDecryptTextDES(unsigned char *pucUserPIN,    unsigned long int   ulUserPINLen,
                                             unsigned char *pucKey,        unsigned long int   uiKeyLen,
                                             unsigned char *pucIv,         unsigned long int   uiIvLen,
                                             unsigned char *pucPlainText,  unsigned long int  &uiPlainTextLen,
                                             unsigned char *pucCipherText, unsigned long int   ulCipherTextLen);
		
		unsigned long int  *uiGetSlotList(/*unsigned long int &ulSlotCount*/);
        TStringList        *vEnumReaderList();
        unsigned long       ulGetSlotInfo(DWORD dwSlotId);



   private:
        bool                   bWasInit;
        CK_FUNCTION_LIST_PTR   pFunctionList;
		
		/*+*/bool              bLoadPKCS11();
        /*+*/bool              bLoadETSAPI();
        ////--void                                   GetSlotList(CK_SLOT_ID_PTR &pSlotList, CK_ULONG &nSlotCount);
		//bInitializeToken()
		/*-*/unsigned long     dwSelectSlot(char *readerName);
		/*-*/CK_OBJECT_HANDLE  hFindObject(CK_SESSION_HANDLE hSess, CK_ATTRIBUTE * t, CK_ULONG size);
		/*-*/void              vGenKeyPair();
		/*-*/unsigned long int dwLocateToken();
		/*-*/bool              bCheckPinPolicy(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject);

		/*+*/AnsiString 	   asEtokenErrorString(DWORD dwRV);

        /*+*/CK_RV             symmetric_encryption(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hKey,
                                                    CK_MECHANISM mechanism, CK_CHAR *data, CK_ULONG data_sz,
                                                    CK_CHAR **encryptedData, CK_ULONG *encryptedData_sz);
        /*-*/CK_RV             symmetric_decryption(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hKey,
                                                    CK_MECHANISM mechanism, CK_CHAR *data, CK_ULONG data_sz,
                                                    CK_CHAR **decryptedData, CK_ULONG *decryptedData_sz);
        /*+*/unsigned long int ulStringLength(char *pcString);
        /*+*/long int          lIntLen(long int lDigit);    //pszGetTokenInfoFast
};
//---------------------------------------------------------------------------
#endif