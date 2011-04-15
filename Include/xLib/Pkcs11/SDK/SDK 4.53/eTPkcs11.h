#ifndef _ET_PKCS_11_H_INCLUDED_
#define _ET_PKCS_11_H_INCLUDED_

#include "cryptoki.h"

#pragma pack(push, etpkcs11, 1)

#include "otp-pkcs11.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ETCK_PKCS11EXT_MAJOR 1
#define ETCK_PKCS11EXT_MINOR 0

#define ETCKF_PROPERTY_THREAD              0x00000001

#define ETCKO_SHADOW_PRIVATE_KEY           0x80005001
#define ETCKH_TOKEN_OBJECT                 0x80005002
#define ETCKH_PIN_POLICY                   0x80005003
#define ETCKH_SO_UNLOCK                    0x80005004
#define ETCKH_PRIVATE_CACHING              0x80005005
#define ETCKH_2NDAUTH                      0x80005006
#define ETCKH_BATTERY                      0x80005007
#define ETCKH_CAPI                         0x80005008

#define ETCKM_PBA_LEGACY                   0x80006001

#define ETCKA_CAPI_KEY_CONTAINER           0x80001301 // CAPI container name
#define ETCKA_CAPI_KEYSIGNATURE            0x80001302

#define ETCKA_OWNER                        0x80001401
#define ETCKA_2NDAUTH_PIN                  0x80001402

#define ETCKA_PBA_MECHANISM                0x80001501
#define ETCKA_PBA_ITERATION                0x80001502
#define ETCKA_PBA_SALT                     0x80001503

#define ETCKA_CACHE_PRIVATE                0x80001601

#define ETCK_CACHE_OFF                     0x00000000
#define ETCK_CACHE_LOGIN                   0x00000001
#define ETCK_CACHE_ON                      0x00000002

#define ETCKA_2NDAUTH_CREATE               0x80001701

#define ETCK_2NDAUTH_PROMPT_NEVER          0x00000000
#define ETCK_2NDAUTH_PROMPT_CONDITIONAL    0x00000001
#define ETCK_2NDAUTH_PROMPT_ALWAYS         0x00000002
#define ETCK_2NDAUTH_MANDATORY             0x00000003

#define ETCKA_OTP_DURATION                 0x80001801
#define ETCKA_OTP_MAY_SET_DURATION         0x80001802

#define ETCKA_CAPI_DEFAULT_KC              0x80001901
#define ETCKA_CAPI_ENROLL_KC               0x80001902 
#define ETCKA_CAPI_AUX_KC                  0x80001903

  /* Token object's attributes */
#define ETCKA_PRODUCT_NAME                 0x80001101
#define ETCKA_MODEL                        0x80001102
#define ETCKA_FW_REVISION                  0x80001104
#define ETCKA_HW_INTERNAL                  0x80001106
#define ETCKA_PRODUCTION_DATE              0x80001107
#define ETCKA_CASE_MODEL                   0x80001108
#define ETCKA_TOKEN_ID                     0x80001109
#define ETCKA_CARD_ID                      0x8000110a
#define ETCKA_CARD_TYPE                    0x8000110b
#define ETCKA_CARD_VERSION                 0x8000110c
#define ETCKA_COLOR                        0x8000110e
#define ETCKA_RETRY_USER                   0x80001110
#define ETCKA_RETRY_SO                     0x80001111
#define ETCKA_RETRY_USER_MAX               0x80001112
#define ETCKA_RETRY_SO_MAX                 0x80001113
#define ETCKA_HAS_LCD                      0x8000111b
#define ETCKA_HAS_SO                       0x8000111d
#define ETCKA_FIPS                         0x8000111e
#define ETCKA_FIPS_SUPPORTED               0x8000111f
#define ETCKA_INIT_PIN_REQ                 0x80001120
#define ETCKA_RSA_2048                     0x80001121
#define ETCKA_RSA_2048_SUPPORTED           0x80001122
#define ETCKA_HMAC_SHA1                    0x80001123
#define ETCKA_HMAC_SHA1_SUPPORTED          0x80001124
#define ETCKA_REAL_COLOR                   0x80001125
#define ETCKA_MAY_INIT                     0x80001126
#define ETCKA_MASS_STORAGE_PRESENT         0x80001127
#define ETCKA_ONE_FACTOR                   0x80001128
#define ETCKA_RSA_AREA_SIZE                0x80001129
#define ETCKA_FORMAT_VERSION               0x8000112a
#define ETCKA_USER_PIN_AGE                 0x8000112b
#define ETCKA_CARDMODULE_AREA_SIZE         0x8000112c
#define ETCKA_HASHVAL                      0x8000112d
#define ETCKA_OS_NAME                      0x8000112e


/* Battery attributes */
#define ETCKA_BATTERY_VALUE                0x8000120a
#define ETCKA_BATTERY_HW_WARN1             0x8000120b
#define ETCKA_BATTERY_HW_WARN2             0x8000120c
#define ETCKA_BATTERY_HW_WARN3             0x8000120d
#define ETCKA_BATTERY_REPLACEABLE          0x8000120e


/* Password policy's attributes */
#define ETCKA_PIN_POLICY_TYPE              0x80001201
#define ETCKA_PIN_MIN_LEN                  0x80001202
#define ETCKA_PIN_MIX_CHARS                0x80001203
#define ETCKA_PIN_MAX_AGE                  0x80001204
#define ETCKA_PIN_MIN_AGE                  0x80001205
#define ETCKA_PIN_WARN_PERIOD              0x80001206
#define ETCKA_PIN_HISTORY_SIZE             0x80001207
#define ETCKA_PIN_PROXY                    0x80001208


/* Password policy's type */
#define ETCKPT_GENERAL_PIN_POLICY          0x00000001

/* Password problems */
#define ETCKF_PIN_MIN_LEN                  0x00000001
#define ETCKF_PIN_MIX_CHARS                0x00000002
#define ETCKF_PIN_MAX_AGE                  0x00000004
#define ETCKF_PIN_MIN_AGE                  0x00000008
#define ETCKF_PIN_WARN_PERIOD              0x00000010
#define ETCKF_PIN_HISTORY                  0x00000020
#define ETCKF_PIN_MUST_BE_CHANGED          0x00000040

/* Smartcard types */
#define ETCK_CARD_NONE                     0x00000000
#define ETCK_CARD_OS                       0x00000001
#define ETCK_CARD_JAVA_APPLET              0x00000002

/* Token cases  */
#define ETCK_CASE_NONE                     0x00000000
#define ETCK_CASE_CLASSIC                  0x00000001
#define ETCK_CASE_NG1                      0x00000002
#define ETCK_CASE_NG2                      0x00000003
#define ETCK_CASE_NG2_NOLCD                0x00000004



#define ETCK_FORMAT_VERSION_LEGACY         0
#define ETCK_FORMAT_VERSION_4_0            4
#define ETCK_FORMAT_VERSION_5_0            5


#define ETCK_IODEV_SOFTWARE_TOKEN_PLUGIN  1 // Plug software token in. Input: file name (UTF-8).
#define ETCK_IODEV_SOFTWARE_TOKEN_PLUGOUT 2 // Plug software token out. No I/O
#define ETCK_IODEV_FULL_NAME              3 // Get softtoken file name or reader name. Input: pointer, Input/Output:allocated length  Output: file name (UTF-8)
#define ETCK_IODEV_SOFTWARE_GET_EMULATE   4 // get EMULATE status. Output: CK_BBOOL
#define ETCK_IODEV_SOFTWARE_SET_EMULATE   5 // EMULATE on/off. Input: CK_BBOOL
#define ETCK_IODEV_CHECK_NAME             6 // Check fit to reader name. Input UTF-8 string

#define ETCK_IOCTL_PIN_EVALUATE           1
#define ETCK_IOCTL_CHECK_BROKEN_KEY       2
#define ETCK_IOCTL_PIN_GENERATE           3

typedef CK_ULONG ETCK_TRACKER_HANDLE;
typedef ETCK_TRACKER_HANDLE CK_PTR ETCK_TRACKER_HANDLE_PTR;

typedef struct tag_ETCK_FUNCTION_LIST_EX ETCK_FUNCTION_LIST_EX;
typedef ETCK_FUNCTION_LIST_EX CK_PTR ETCK_FUNCTION_LIST_EX_PTR;
typedef ETCK_FUNCTION_LIST_EX_PTR CK_PTR ETCK_FUNCTION_LIST_EX_PTR_PTR;

/*
ETC_GetFunctionListEx
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_GetFunctionListEx)
(
  ETCK_FUNCTION_LIST_EX_PTR_PTR ppFunctionListEx /* receives pointer to extention functions list */
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_GetFunctionListEx)
(
  ETCK_FUNCTION_LIST_EX_PTR_PTR ppFunctionListEx
);


/*
ETC_CreateTracker
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_CreateTracker)
(
  ETCK_TRACKER_HANDLE_PTR pTracker, 
  CK_VOID_PTR param /* NULL */
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_CreateTracker)
(
  ETCK_TRACKER_HANDLE_PTR pTracker, 
  CK_VOID_PTR param /* NULL */
);


/*
ETC_DestroyTracker
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_DestroyTracker)
(
  ETCK_TRACKER_HANDLE hTracker
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_DestroyTracker)
(
  ETCK_TRACKER_HANDLE hTracker
);


/*
ETC_BeginTRansaction
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_BeginTransaction)
(
  CK_SESSION_HANDLE hSession
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_BeginTransaction)
(
  CK_SESSION_HANDLE hSession
);


/*
ETC_EndTransaction
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_EndTransaction)
(
  CK_SESSION_HANDLE hSession
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_EndTransaction)
(
  CK_SESSION_HANDLE hSession
);



/*
ETC_GetProperty
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_GetProperty)
(
  CK_UTF8CHAR_PTR name, 
  CK_VOID_PTR pBuffer,
  CK_ULONG_PTR pulSize,
  CK_VOID_PTR pReserved /* NULL */
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_GetProperty)
(
  CK_UTF8CHAR_PTR name, 
  CK_VOID_PTR pBuffer,
  CK_ULONG_PTR pulSize,
  CK_VOID_PTR pReserved
);

/*
ETC_SetProperty
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_SetProperty)
(
  CK_UTF8CHAR_PTR name, 
  CK_VOID_PTR pBuffer,
  CK_ULONG ulSize,
  CK_ULONG flags,
  CK_VOID_PTR pReserved /* NULL */
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_SetProperty)
(
  CK_UTF8CHAR_PTR name, 
  CK_VOID_PTR pBuffer,
  CK_ULONG ulSize,
  CK_ULONG flags,
  CK_VOID_PTR pReserved
);

/*
ETC_PrepareSoftwareToken
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_PrepareSoftwareToken)
(
  CK_UTF8CHAR_PTR pFileName,
  CK_VOID_PTR param /* NULL */
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_PrepareSoftwareToken)
(
  CK_UTF8CHAR_PTR pFileName,
  CK_VOID_PTR param /* NULL */
);


/*
ETC_SingleLogonGetPin
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_SingleLogonGetPin)
(
  CK_SESSION_HANDLE hSession, 
  CK_CHAR_PTR       pPin,     
  CK_ULONG_PTR      ulPinLen  
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_SingleLogonGetPin)
(
  CK_SESSION_HANDLE hSession, 
  CK_CHAR_PTR       pPin,     
  CK_ULONG_PTR      ulPinLen  
);



/*
ETC_CreateVirtualSession
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_CreateVirtualSession)
(
  CK_SESSION_HANDLE_PTR phSession
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_CreateVirtualSession)
(
  CK_SESSION_HANDLE_PTR phSession
);


/*
ETC_InitTokenInit
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_InitTokenInit)
(
  CK_SLOT_ID             slotID,        
  CK_UTF8CHAR_PTR        pPin,          
  CK_ULONG               ulPinLen,      
	CK_ULONG               ulRetryCounter,
  CK_UTF8CHAR_PTR        pLabel,        
  CK_SESSION_HANDLE_PTR  phSession      
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_InitTokenInit)
(
  CK_SLOT_ID             slotID,        
  CK_UTF8CHAR_PTR        pPin,          
  CK_ULONG               ulPinLen,      
	CK_ULONG               ulRetryCounter,
  CK_UTF8CHAR_PTR        pLabel,        
  CK_SESSION_HANDLE_PTR  phSession      
);

/*
ETC_InitTokenFinal
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_InitTokenFinal)
(
  CK_SESSION_HANDLE hSession
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_InitTokenFinal)
(
  CK_SESSION_HANDLE hSession
);

/*
ETC_InitPIN
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_InitPIN)
(
  CK_SESSION_HANDLE hSession,        
  CK_UTF8CHAR_PTR   pPin,            
  CK_ULONG          ulPinLen,        
	CK_ULONG          ulRetryCounter,  
	CK_BBOOL          toBeChanged      
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_InitPIN)
(
  CK_SESSION_HANDLE hSession,        
  CK_UTF8CHAR_PTR   pPin,            
  CK_ULONG          ulPinLen,        
	CK_ULONG          ulRetryCounter,  
	CK_BBOOL          toBeChanged      
);

/*
ETC_UnlockGetChallenge
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_UnlockGetChallenge)
( 
  CK_SESSION_HANDLE hSession, 
  CK_VOID_PTR       pChallenge, 
  CK_ULONG_PTR      pulChallengeLen 
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_UnlockGetChallenge)
(
  CK_SESSION_HANDLE hSession, 
  CK_VOID_PTR       pChallenge, 
  CK_ULONG_PTR      pulChallengeLen 
);

/*
ETC_UnlockComplete
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_UnlockComplete)
(
  CK_SESSION_HANDLE hSession,        
  CK_VOID_PTR       pResponse, 
  CK_ULONG          ulResponse,
  CK_UTF8CHAR_PTR   pPin,            
  CK_ULONG          ulPinLen,        
	CK_ULONG          ulRetryCounter,  
	CK_BBOOL          toBeChanged      
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_UnlockComplete)
(
  CK_SESSION_HANDLE hSession,        
  CK_VOID_PTR       pResponse, 
  CK_ULONG          ulResponse,
  CK_UTF8CHAR_PTR   pPin,            
  CK_ULONG          ulPinLen,        
	CK_ULONG          ulRetryCounter,  
	CK_BBOOL          toBeChanged      
);

/*
ETC_DeviceIOCTL
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_DeviceIOCTL)
(
  CK_SLOT_ID slotId, 
  CK_ULONG code, 
  CK_VOID_PTR pInput, 
  CK_ULONG ulInputLength, 
  CK_VOID_PTR pOutput, 
  CK_ULONG_PTR pulOutputLength 
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_DeviceIOCTL)
(
  CK_SLOT_ID slotId, 
  CK_ULONG code, 
  CK_VOID_PTR pInput, 
  CK_ULONG ulInputLength, 
  CK_VOID_PTR pOutput, 
  CK_ULONG_PTR pulOutputLength 
);

/*
ETC_TokenIOCTL
*/
CK_DECLARE_FUNCTION(CK_RV, ETC_TokenIOCTL)
(
  CK_SESSION_HANDLE hSession, 
  CK_OBJECT_HANDLE hObject,
  CK_ULONG code, 
  CK_VOID_PTR pInput, 
  CK_ULONG ulInputLength, 
  CK_VOID_PTR pOutput, 
  CK_ULONG_PTR pulOutputLength 
);

typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, CK_ETC_TokenIOCTL)
(
  CK_SESSION_HANDLE hSession, 
  CK_OBJECT_HANDLE hObject,
  CK_ULONG code, 
  CK_VOID_PTR pInput, 
  CK_ULONG ulInputLength, 
  CK_VOID_PTR pOutput, 
  CK_ULONG_PTR pulOutputLength 
);

typedef struct tag_ETCK_FUNCTION_LIST_EX 
{
  CK_VERSION                    version;  /* Cryptoki extension version */
  unsigned short                flags;
  CK_ETC_GetFunctionListEx      ETC_GetFunctionListEx;
  CK_ETC_DeviceIOCTL            ETC_DeviceIOCTL;
  CK_ETC_TokenIOCTL             ETC_TokenIOCTL;
  CK_ETC_CreateTracker          ETC_CreateTracker;
  CK_ETC_DestroyTracker         ETC_DestroyTracker;
  CK_ETC_BeginTransaction       ETC_BeginTransaction;
  CK_ETC_EndTransaction         ETC_EndTransaction;
  CK_ETC_GetProperty            ETC_GetProperty;
  CK_ETC_SetProperty            ETC_SetProperty;
  CK_ETC_CreateVirtualSession   ETC_CreateVirtualSession;
  CK_ETC_PrepareSoftwareToken   ETC_PrepareSoftwareToken;
	CK_ETC_SingleLogonGetPin			ETC_SingleLogonGetPin;
  CK_ETC_InitTokenInit          ETC_InitTokenInit;
  CK_ETC_InitTokenFinal         ETC_InitTokenFinal;
  CK_ETC_InitPIN                ETC_InitPIN;
  CK_ETC_UnlockGetChallenge     ETC_UnlockGetChallenge;
  CK_ETC_UnlockComplete         ETC_UnlockComplete;
} CK_FUNCTION_LIST_EX ;

#ifdef __cplusplus
}
#endif

#pragma pack(pop, etpkcs11)

#endif

