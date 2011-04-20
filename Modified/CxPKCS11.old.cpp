/****************************************************************************
* Class name:  CxPKCS11
* Description: Aladdin eToken, PKCS #11
* File name:   CxPKCS11.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib, Aladdin eToken SDK
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     25.02.2010 13:31:54
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <XLib/PKCS11/CxPKCS11.h>

#include <XLib/PKCS11/CxUtils.h>


//////////#define WIN32_LEAN_AND_MEAN		//Exclude rarely-used content from Windows headers.


#define EMPTY_MSG_         _T("отсутствует")
#define ETPKCS11_PATH      _T("eTPKCS11.dll")	//путь к eTPKCS11.dll
#define ETSAPI_PATH        _T("C:/WINDOWS/system32/eTSAPI.dll")     //путь к eTSAPI.dll
#define TRUE_MSG           _T("да")   				//FALSE_MSG >= TRUE_MSG
#define FALSE_MSG          _T("нет")
#define TOKEN_NON_PRESENT  - 1
#define MAX_FINDED_OBJECTS 512



//---------------------------------------------------------------------------
//TODO: + объявление SAPI's функции
typedef CK_RV (* t_SAPI_GetTokenInfo)(CK_SLOT_ID, CK_ATTRIBUTE_PTR, CK_ULONG);
////t_SAPI_GetTokenInfo f_SAPI_GetTokenInfo = NULL; /*DIF: SDK 3.60*/
t_SAPI_GetTokenInfo _SAPI_GetTokenInfo = NULL;		/*DIF: SDK 4.53*/
//---------------------------------------------------------------------------



/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxPKCS11 ()
CxPKCS11::CxPKCS11() :
	_m_tlLog    (FALSE),
	_m_pFunc    (NULL),
	_m_bRes     (FALSE),
	_m_ulRes    (!CKR_OK),
	_m_bIsInit  (FALSE)
{
	xCHECK_DO(TRUE == ( !_bLoadETPKCS11() || !_bLoadETSAPI() ), return);

	_m_bRes = bInitialize();
	xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//TODO: - ~CxPKCS11 ()
CxPKCS11::~CxPKCS11() {
	_m_bRes = bFinalize();
	xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Initialize
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bInitialize ()
BOOL CxPKCS11::bInitialize() {
	/*DEBUG*/
	
    _m_ulRes = _m_pFunc->C_Initialize(0);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
	
	_m_bIsInit = TRUE; 
		
	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bFinalize ()
BOOL CxPKCS11::bFinalize() {
	/*DEBUG*/
	
	xCHECK_RET(FALSE == _m_bIsInit, FALSE);

	_m_ulRes = _m_pFunc->C_Finalize(0);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
	
	_m_bIsInit = FALSE;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bIsInit (проверка инициализации)
BOOL CxPKCS11::bIsInitialized() const {
	/*DEBUG*///not need

	return (TRUE == _m_bIsInit) && (NULL != _m_pFunc);
}
//---------------------------------------------------------------------------
//TODO: - pGetFuncList (получение указателя на список функций)
CK_FUNCTION_LIST_PTR CxPKCS11::pGetFuncList() const {
	/*DEBUG*///not need

	return _m_pFunc;
}
//---------------------------------------------------------------------------



/****************************************************************************
*	Slot
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetSlotList (btains a list of slots in the system)
BOOL CxPKCS11::bGetSlotList(
	CK_BBOOL       bTokenPresent,  /* only slots with tokens? */
	CK_SLOT_ID_PTR pSlotList,     /* receives array of slot IDs */
	CK_ULONG_PTR   pulCount       /* receives number of slots */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetSlotList(bTokenPresent, pSlotList, pulCount);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
		
	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetSlotInfo (obtains information about a particular slot in the system)
BOOL CxPKCS11::bGetSlotInfo(
	CK_SLOT_ID       slotID,  /* the ID of the slot */
	CK_SLOT_INFO_PTR pInfo    /* receives the slot information */
)
{
	/*DEBUG*/
	
	_m_ulRes = _m_pFunc->C_GetSlotInfo(slotID, pInfo);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
	
	return TRUE;	
}
//---------------------------------------------------------------------------
//TODO: - bWaitForSlotEvent (waits for a slot event (token insertion, removal, etc.) to occur)
BOOL CxPKCS11::bWaitForSlotEvent(
	CK_FLAGS flags,        /* blocking/nonblocking flag */
	CK_SLOT_ID_PTR pSlot,  /* location that receives the slot ID */
	CK_VOID_PTR pRserved   /* reserved.  Should be NULL_PTR */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_WaitForSlotEvent(flags, pSlot, pRserved);		
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
	
	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Session
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bOpenSession (opens a session between an application and a token)
BOOL CxPKCS11::bOpenSession(
		CK_SLOT_ID            slotID,        /* the slot's ID */
		CK_FLAGS              flags,         /* from CK_SESSION_INFO */
		CK_VOID_PTR           pApplication,  /* passed to callback */
		CK_NOTIFY             Notify,        /* callback function */
		CK_SESSION_HANDLE_PTR phSession      /* gets session handle */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_OpenSession(slotID, flags, pApplication, Notify, phSession);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetSessionInfo (obtains information about the session)
BOOL CxPKCS11::bGetSessionInfo(
	  CK_SESSION_HANDLE   hSession,  /* the session's handle */
	  CK_SESSION_INFO_PTR pInfo      /* receives session info */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetSessionInfo(hSession, pInfo);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetOperationState (restores the state of the cryptographic operation in a session)
BOOL CxPKCS11::bSetOperationState(
	CK_SESSION_HANDLE hSession,            /* session's handle */
	CK_BYTE_PTR      pOperationState,      /* holds state */
	CK_ULONG         ulOperationStateLen,  /* holds state length */
	CK_OBJECT_HANDLE hEncryptionKey,       /* en/decryption key */
	CK_OBJECT_HANDLE hAuthenticationKey    /* sign/verify key */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SetOperationState(hSession, pOperationState, ulOperationStateLen, hEncryptionKey, hAuthenticationKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetOperationState (obtains the state of the cryptographic operation in a session)
BOOL CxPKCS11::bGetOperationState(
	CK_SESSION_HANDLE hSession,             /* session's handle */
	CK_BYTE_PTR       pOperationState,      /* gets state */
	CK_ULONG_PTR      pulOperationStateLen  /* gets state length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetOperationState(hSession, pOperationState, pulOperationStateLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bCloseSession (closes a session between an application and a token)
BOOL CxPKCS11::bCloseSession(
	  CK_SESSION_HANDLE hSession  /* the session's handle */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_CloseSession(hSession);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bCloseAllSessions (closes all sessions with a token)
BOOL CxPKCS11::bCloseAllSessions(
	  CK_SLOT_ID slotID  /* the token's slot */
) 
{
	/*DEBUG*/

	_m_ulRes = 	_m_pFunc->C_CloseAllSessions(slotID);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Login
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bLogin (logs a user into a token)
BOOL CxPKCS11::bLogin(  
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_USER_TYPE      userType,  /* the user type */
	CK_UTF8CHAR_PTR   pPin,      /* the user's PIN */
	CK_ULONG          ulPinLen   /* the length of the PIN */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_Login(hSession, userType, pPin, ulPinLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bLogout (logs a user out from a token)
BOOL CxPKCS11::bLogout(
	CK_SESSION_HANDLE hSession  /* the session's handle */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_Logout(hSession); 
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Info
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetInfo (returns general information about Cryptoki)
BOOL CxPKCS11::bGetInfo(
	CK_INFO_PTR pInfo  /* location that receives information */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetInfo(pInfo); 
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetTokenInfo (obtains information about a particular token in the system)
BOOL CxPKCS11::bGetTokenInfo(
	CK_SLOT_ID        slotID,  /* ID of the token's slot */
	CK_TOKEN_INFO_PTR pInfo    /* receives the token information */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetTokenInfo(slotID, pInfo); 
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Pin
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bInitToken (initializes a token)
BOOL CxPKCS11::bInitToken(
	CK_SLOT_ID      slotID,    /* ID of the token's slot */
	CK_UTF8CHAR_PTR pPin,      /* the SO's initial PIN */
	CK_ULONG        ulPinLen,  /* length in bytes of the PIN */
	CK_UTF8CHAR_PTR pLabel     /* 32-byte token label (blank padded) */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_InitToken(slotID, pPin, ulPinLen, pLabel);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bInitPIN (initializes the normal user's PIN)
BOOL CxPKCS11::bInitPIN(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_UTF8CHAR_PTR   pPin,      /* the normal user's PIN */
	CK_ULONG          ulPinLen   /* length in bytes of the PIN */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_InitPIN(hSession, pPin, ulPinLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetPIN (modifies the PIN of the user who is logged in)
BOOL CxPKCS11::bSetPIN(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_UTF8CHAR_PTR   pOldPin,   /* the old PIN */
	CK_ULONG          ulOldLen,  /* length of the old PIN */
	CK_UTF8CHAR_PTR   pNewPin,   /* the new PIN */
	CK_ULONG          ulNewLen   /* length of the new PIN */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SetPIN(hSession, pOldPin, ulOldLen, pNewPin, ulNewLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Mechanism	
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetMechanismInfo (obtains information about a particular mechanism possibly supported by a token)
BOOL CxPKCS11::bGetMechanismInfo(
	CK_SLOT_ID            slotID,  /* ID of the token's slot */
	CK_MECHANISM_TYPE     type,    /* type of mechanism */
	CK_MECHANISM_INFO_PTR pInfo    /* receives mechanism info */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetMechanismInfo(slotID, type, pInfo);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetMechanismList (obtains a list of mechanism types supported by a token)
BOOL CxPKCS11::bGetMechanismList(
	CK_SLOT_ID            slotID,          /* ID of token's slot */
	CK_MECHANISM_TYPE_PTR pMechanismList,  /* gets mech. array */
	CK_ULONG_PTR          pulCount         /* gets # of mechs. */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetMechanismList(slotID, pMechanismList, pulCount);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Object	
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bCreateObject (creates a new object)
BOOL CxPKCS11::bCreateObject(
	CK_SESSION_HANDLE hSession,    /* the session's handle */
	CK_ATTRIBUTE_PTR  pTemplate,   /* the object's template */
	CK_ULONG          ulCount,     /* attributes in template */
	CK_OBJECT_HANDLE_PTR phObject  /* gets new object's handle. */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_CreateObject(hSession, pTemplate, ulCount, phObject);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetObjectSize (gets the size of an object in bytes)	
BOOL CxPKCS11::bGetObjectSize(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_OBJECT_HANDLE  hObject,   /* the object's handle */
	CK_ULONG_PTR      pulSize    /* receives size of object */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetObjectSize(hSession, hObject, pulSize);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bCopyObject (copies an object, creating a new object for the copy)
BOOL CxPKCS11::bCopyObject(
	CK_SESSION_HANDLE    hSession,    /* the session's handle */
	CK_OBJECT_HANDLE     hObject,     /* the object's handle */
	CK_ATTRIBUTE_PTR     pTemplate,   /* template for new object */
	CK_ULONG             ulCount,     /* attributes in template */
	CK_OBJECT_HANDLE_PTR phNewObject  /* receives handle of copy */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_CopyObject(hSession, hObject, pTemplate, ulCount, phNewObject);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bFindObjectsInit (initializes a search for token and session objects that match a template)
BOOL CxPKCS11::bFindObjectsInit(
	CK_SESSION_HANDLE hSession,   /* the session's handle */
	CK_ATTRIBUTE_PTR  pTemplate,  /* attribute values to match */
	CK_ULONG          ulCount     /* attrs in search template */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_FindObjectsInit(hSession, pTemplate, ulCount);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bFindObjects (continues a search for token and session objects that match a template, obtaining additional object handles)
BOOL CxPKCS11::bFindObjects(
	CK_SESSION_HANDLE    hSession,          /* session's handle */
	CK_OBJECT_HANDLE_PTR phObject,          /* gets obj. handles */
	CK_ULONG             ulMaxObjectCount,  /* max handles to get */
	CK_ULONG_PTR         pulObjectCount     /* actual # returned */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_FindObjects(hSession, phObject, ulMaxObjectCount, pulObjectCount );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bFindObjectsFinal (finishes a search for token and session objects)
BOOL CxPKCS11::bFindObjectsFinal(
	CK_SESSION_HANDLE hSession     /* the session's handle */
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_FindObjectsFinal(hSession);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}	
//---------------------------------------------------------------------------
//TODO: - bDestroyObject (destroys an object)
BOOL CxPKCS11::bDestroyObject(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_OBJECT_HANDLE  hObject   
) 
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DestroyObject(hSession, hObject);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetAttributeValue (obtains the value of one or more object attributes)
BOOL CxPKCS11::bGetAttributeValue(
	CK_SESSION_HANDLE hSession,   /* the session's handle */
	CK_OBJECT_HANDLE  hObject,    /* the object's handle */
	CK_ATTRIBUTE_PTR  pTemplate,  /* specifies attrs; gets vals */
	CK_ULONG          ulCount     /* attributes in template */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetAttributeValue(hSession, hObject, pTemplate, ulCount);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetAttributeValue (modifies the value of one or more object attributes)
BOOL CxPKCS11::bSetAttributeValue(
	CK_SESSION_HANDLE hSession,   /* the session's handle */
	CK_OBJECT_HANDLE  hObject,    /* the object's handle */
	CK_ATTRIBUTE_PTR  pTemplate,  /* specifies attrs and values */
	CK_ULONG          ulCount     /* attributes in template */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SetAttributeValue(hSession, hObject, pTemplate, ulCount);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bUtil_FindObjects (search for token and session objects that match a template, obtaining additional object handles)
BOOL CxPKCS11::bUtil_FindObjects(
	CK_SESSION_HANDLE              hSession,   			/* the session's handle */
	CK_ATTRIBUTE_PTR               pTemplate,  			/* attribute values to match */
	CK_ULONG                       ulCount,    			/* attrs in search template */
	std::vector<CK_OBJECT_HANDLE> *pvecObjectHandles	/* [out] handles to objects */
) 
{
	/*DEBUG*/

	_m_bRes = bFindObjectsInit(hSession, pTemplate, ulCount);	// To find all attributes, set ulCount to 0.
	xCHECK_RET(FALSE == _m_bRes, FALSE);

	CK_OBJECT_HANDLE hList[MAX_FINDED_OBJECTS] = {0};
	CK_ULONG         ulFound  = 0;
	
	_m_bRes = bFindObjects(hSession, &hList[0], MAX_FINDED_OBJECTS, &ulFound);
	xCHECK_RET(FALSE == _m_bRes, FALSE);

	_m_bRes = bFindObjectsFinal(hSession);
	xCHECK_RET(FALSE == _m_bRes, FALSE);

	xCHECK_RET(0 == ulFound, FALSE);
	
	//-------------------------------------
	//заполнение std::vector
	(*pvecObjectHandles).clear();
	for (CK_ULONG i = 0; i < ulFound; ++ i) {
    	(*pvecObjectHandles).push_back( hList[i] );
    }

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Key	
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGenerateKey (generates a secret key, creating a new key object)
BOOL CxPKCS11::bGenerateKey(
	CK_SESSION_HANDLE    hSession,    /* the session's handle */
	CK_MECHANISM_PTR     pMechanism,  /* key generation mech. */
	CK_ATTRIBUTE_PTR     pTemplate,   /* template for new key */
	CK_ULONG             ulCount,     /* # of attrs in template */
	CK_OBJECT_HANDLE_PTR phKey        /* gets handle of new key */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GenerateKey(hSession, pMechanism, pTemplate, ulCount, phKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}  
//---------------------------------------------------------------------------
//TODO: - bGenerateKeyPair (generates a public-key/private-key pair, creating new key objects)      
BOOL CxPKCS11::bGenerateKeyPair(
	CK_SESSION_HANDLE    hSession,                    /* session handle */
	CK_MECHANISM_PTR     pMechanism,                  /* key-gen mech. */
	CK_ATTRIBUTE_PTR     pPublicKeyTemplate,          /* template for pub key */
	CK_ULONG             ulPublicKeyAttributeCount,   /* # pub. attrs. */
	CK_ATTRIBUTE_PTR     pPrivateKeyTemplate,         /* template for priv. key */
	CK_ULONG             ulPrivateKeyAttributeCount,  /* # priv. attrs. */
	CK_OBJECT_HANDLE_PTR phPublicKey,                 /* gets pub. key handle */
	CK_OBJECT_HANDLE_PTR phPrivateKey    
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GenerateKeyPair(hSession, pMechanism, pPublicKeyTemplate, ulPublicKeyAttributeCount, pPrivateKeyTemplate, ulPrivateKeyAttributeCount, phPublicKey, phPrivateKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: - bDeriveKey (derives a key from a base key, creating a new key object)
BOOL CxPKCS11::bDeriveKey(
	CK_SESSION_HANDLE    hSession,          /* session's handle */
	CK_MECHANISM_PTR     pMechanism,        /* key deriv. mech. */
	CK_OBJECT_HANDLE     hBaseKey,          /* base key */
	CK_ATTRIBUTE_PTR     pTemplate,         /* new key template */
	CK_ULONG             ulAttributeCount,  /* template length */
	CK_OBJECT_HANDLE_PTR phKey 
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DeriveKey(hSession, pMechanism, hBaseKey, pTemplate, ulAttributeCount, phKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}  
//---------------------------------------------------------------------------
//TODO: - bWrapKey (wraps (i.e., encrypts) a key)
BOOL CxPKCS11::bWrapKey(
	CK_SESSION_HANDLE hSession,        /* the session's handle */
	CK_MECHANISM_PTR  pMechanism,      /* the wrapping mechanism */
	CK_OBJECT_HANDLE  hWrappingKey,    /* wrapping key */
	CK_OBJECT_HANDLE  hKey,            /* key to be wrapped */
	CK_BYTE_PTR       pWrappedKey,     /* gets wrapped key */
    CK_ULONG_PTR      pulWrappedKeyLen /* gets wrapped key size */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_WrapKey(hSession, pMechanism, hWrappingKey, hKey, pWrappedKey, pulWrappedKeyLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: - bUnwrapKey (unwraps (decrypts) a wrapped key, creating a new key object)
BOOL CxPKCS11::bUnwrapKey(
	CK_SESSION_HANDLE    hSession,          /* session's handle */
	CK_MECHANISM_PTR     pMechanism,        /* unwrapping mech. */
	CK_OBJECT_HANDLE     hUnwrappingKey,    /* unwrapping key */
	CK_BYTE_PTR          pWrappedKey,       /* the wrapped key */
	CK_ULONG             ulWrappedKeyLen,   /* wrapped key len */
	CK_ATTRIBUTE_PTR     pTemplate,         /* new key template */
	CK_ULONG             ulAttributeCount,  /* template length */
	CK_OBJECT_HANDLE_PTR phKey 
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_UnwrapKey(hSession, pMechanism, hUnwrappingKey, pWrappedKey, ulWrappedKeyLen, pTemplate, ulAttributeCount, phKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//--------------------------------------------------------------------------- 



/****************************************************************************
*	Encrypt	
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bEncrypt (encrypts single-part data)
BOOL CxPKCS11::bEncrypt(
	CK_SESSION_HANDLE hSession,            /* session's handle */
	CK_BYTE_PTR       pData,               /* the plaintext data */
	CK_ULONG          ulDataLen,           /* bytes of plaintext */
	CK_BYTE_PTR       pEncryptedData,      /* gets ciphertext */
	CK_ULONG_PTR      pulEncryptedDataLen  /* gets c-text size */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_Encrypt(hSession, pData, ulDataLen, pEncryptedData, pulEncryptedDataLen  );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: - bEncryptFinal (finishes a multiple-part encryption operation)
BOOL CxPKCS11::bEncryptFinal(
	CK_SESSION_HANDLE hSession,                /* session handle */
	CK_BYTE_PTR       pLastEncryptedPart,      /* last c-text */
	CK_ULONG_PTR      pulLastEncryptedPartLen  /* gets last size */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_EncryptFinal(hSession, pLastEncryptedPart, pulLastEncryptedPartLen );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: - bEncryptInit (initializes an encryption operation)
BOOL CxPKCS11::bEncryptInit(
	CK_SESSION_HANDLE hSession,    /* the session's handle */
	CK_MECHANISM_PTR  pMechanism,  /* the encryption mechanism */
	CK_OBJECT_HANDLE  hKey         /* handle of encryption key */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_EncryptInit(hSession, pMechanism, hKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: - bEncryptUpdate (continues a multiple-part encryption operation)
BOOL CxPKCS11::bEncryptUpdate(
	CK_SESSION_HANDLE hSession,           /* session's handle */
	CK_BYTE_PTR       pPart,              /* the plaintext data */
	CK_ULONG          ulPartLen,          /* plaintext data len */
	CK_BYTE_PTR       pEncryptedPart,     /* gets ciphertext */
	CK_ULONG_PTR      pulEncryptedPartLen /* gets c-text size */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_EncryptUpdate(hSession, pPart, ulPartLen, pEncryptedPart, pulEncryptedPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: - bSeedRandom (mixes additional seed material into the token's random number generator)
BOOL CxPKCS11::bSeedRandom(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_BYTE_PTR       pSeed,     /* the seed material */
	CK_ULONG          ulSeedLen  /* length of seed material */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SeedRandom(hSession, pSeed, ulSeedLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: - bGenerateRandom (generates random data)
BOOL CxPKCS11::bGenerateRandom(
	CK_SESSION_HANDLE hSession,    /* the session's handle */
	CK_BYTE_PTR       RandomData,  /* receives the random data */
	CK_ULONG          ulRandomLen  /* # of bytes to generate */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GenerateRandom(hSession, RandomData, ulRandomLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
} 
//---------------------------------------------------------------------------


/****************************************************************************
*	Decrypt
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bDecrypt (decrypts encrypted data in a single part)
BOOL CxPKCS11::bDecrypt(
	CK_SESSION_HANDLE hSession,           /* session's handle */
	CK_BYTE_PTR       pEncryptedData,     /* ciphertext */
	CK_ULONG          ulEncryptedDataLen, /* ciphertext length */
	CK_BYTE_PTR       pData,              /* gets plaintext */
	CK_ULONG_PTR      pulDataLen          /* gets p-text size */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_Decrypt(hSession, pEncryptedData, ulEncryptedDataLen, pData, pulDataLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDecryptDigestUpdate (continues a multiple-part decryption and digesting operation)
BOOL CxPKCS11::bDecryptDigestUpdate(
	CK_SESSION_HANDLE hSession,            /* session's handle */
	CK_BYTE_PTR       pEncryptedPart,      /* ciphertext */
	CK_ULONG          ulEncryptedPartLen,  /* ciphertext length */
	CK_BYTE_PTR       pPart,               /* gets plaintext */
	CK_ULONG_PTR      pulPartLen           /* gets plaintext len */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DecryptDigestUpdate(hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDecryptFinal (finishes a multiple-part decryption operation)	
BOOL CxPKCS11::bDecryptFinal(
	CK_SESSION_HANDLE hSession,       /* the session's handle */
	CK_BYTE_PTR       pLastPart,      /* gets plaintext */
	CK_ULONG_PTR      pulLastPartLen  /* p-text size */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DecryptFinal(hSession, pLastPart, pulLastPartLen );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDecryptInit (initializes a decryption operation)
BOOL CxPKCS11::bDecryptInit(
	CK_SESSION_HANDLE hSession,    /* the session's handle */
	CK_MECHANISM_PTR  pMechanism,  /* the decryption mechanism */
	CK_OBJECT_HANDLE  hKey         /* handle of decryption key */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DecryptInit(hSession, pMechanism, hKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDecryptUpdate (continues a multiple-part decryption operation)
BOOL CxPKCS11::bDecryptUpdate(
	CK_SESSION_HANDLE hSession,            /* session's handle */
	CK_BYTE_PTR       pEncryptedPart,      /* encrypted data */
	CK_ULONG          ulEncryptedPartLen,  /* input length */
	CK_BYTE_PTR       pPart,               /* gets plaintext */
	CK_ULONG_PTR      pulPartLen           /* p-text size */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DecryptUpdate(hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDecryptVerifyUpdate (continues a multiple-part decryption and verify operation)
BOOL CxPKCS11::bDecryptVerifyUpdate(
	CK_SESSION_HANDLE hSession,            /* session's handle */
	CK_BYTE_PTR       pEncryptedPart,      /* ciphertext */
	CK_ULONG          ulEncryptedPartLen,  /* ciphertext length */
	CK_BYTE_PTR       pPart,               /* gets plaintext */
	CK_ULONG_PTR      pulPartLen           /* gets p-text length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DecryptVerifyUpdate(hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Digest
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bDigest (digests data in a single part)
BOOL CxPKCS11::bDigest(
	CK_SESSION_HANDLE hSession,     /* the session's handle */
	CK_BYTE_PTR       pData,        /* data to be digested */
	CK_ULONG          ulDataLen,    /* bytes of data to digest */
	CK_BYTE_PTR       pDigest,      /* gets the message digest */
	CK_ULONG_PTR      pulDigestLen  /* gets digest length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_Digest(hSession, pData, ulDataLen, pDigest, pulDigestLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDigestEncryptUpdate (continues a multiple-part digesting and encryption operation)
BOOL CxPKCS11::bDigestEncryptUpdate(
	CK_SESSION_HANDLE hSession,            /* session's handle */
	CK_BYTE_PTR       pPart,               /* the plaintext data */
	CK_ULONG          ulPartLen,           /* plaintext length */
	CK_BYTE_PTR       pEncryptedPart,      /* gets ciphertext */
	CK_ULONG_PTR      pulEncryptedPartLen  /* gets c-text length */)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DigestEncryptUpdate(hSession, pPart, ulPartLen, pEncryptedPart, pulEncryptedPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}	
//---------------------------------------------------------------------------
//TODO: - bDigestFinal (finishes a multiple-part message-digesting operation)
BOOL CxPKCS11::bDigestFinal(
	CK_SESSION_HANDLE hSession,     /* the session's handle */
	CK_BYTE_PTR       pDigest,      /* gets the message digest */
	CK_ULONG_PTR      pulDigestLen  /* gets byte count of digest */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DigestFinal(hSession, pDigest, pulDigestLen );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}	
//---------------------------------------------------------------------------
//TODO: - bDigestInit (initializes a message-digesting operation)
BOOL CxPKCS11::bDigestInit(
	CK_SESSION_HANDLE hSession,   /* the session's handle */
	CK_MECHANISM_PTR  pMechanism  /* the digesting mechanism */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DigestInit(hSession,	pMechanism);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDigestKey (continues a multi-part message-digesting operation, by digesting the value of a secret key as part of the data already digested)
BOOL CxPKCS11::bDigestKey(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_OBJECT_HANDLE  hKey       /* secret key to digest */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DigestKey(hSession, hKey );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bDigestUpdate (continues a multiple-part message-digesting operation)
BOOL CxPKCS11::bDigestUpdate(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_BYTE_PTR       pPart,     /* data to be digested */
	CK_ULONG          ulPartLen  /* bytes of data to be digested */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_DigestUpdate(hSession, pPart, ulPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Sign
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bSignInit (initializes a signature (private key encryption) operation, where the signature is (will be) an appendix to the data, and plaintext cannot be recovered from the signature)
BOOL CxPKCS11::bSignInit(
	CK_SESSION_HANDLE hSession,    /* the session's handle */
	CK_MECHANISM_PTR  pMechanism,  /* the signature mechanism */
	CK_OBJECT_HANDLE  hKey         /* handle of signature key */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SignInit(hSession, pMechanism, hKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSign (signs (encrypts with private key) data in a single part, where the signature is (will be) an appendix to the data, and plaintext cannot be recovered from the signature)
BOOL CxPKCS11::bSign(
	CK_SESSION_HANDLE hSession,        /* the session's handle */
	CK_BYTE_PTR       pData,           /* the data to sign */
	CK_ULONG          ulDataLen,       /* count of bytes to sign */
	CK_BYTE_PTR       pSignature,      /* gets the signature */
	CK_ULONG_PTR      pulSignatureLen  /* gets signature length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_Sign(hSession, pData, ulDataLen, pSignature, pulSignatureLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSignUpdate (continues a multiple-part signature operation,where the signature is (will be) an appendix to the data, and plaintext cannot be recovered from the signature)
BOOL CxPKCS11::bSignUpdate(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_BYTE_PTR       pPart,     /* the data to sign */
	CK_ULONG          ulPartLen  /* count of bytes to sign */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SignUpdate(hSession, pPart, ulPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSignEncryptUpdate (continues a multiple-part signing and encryption operation)
BOOL CxPKCS11::bSignEncryptUpdate(
	CK_SESSION_HANDLE hSession,            /* session's handle */
	CK_BYTE_PTR       pPart,               /* the plaintext data */
	CK_ULONG          ulPartLen,           /* plaintext length */
	CK_BYTE_PTR       pEncryptedPart,      /* gets ciphertext */
	CK_ULONG_PTR      pulEncryptedPartLen  /* gets c-text length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SignEncryptUpdate(hSession, pPart, ulPartLen, pEncryptedPart, pulEncryptedPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSignFinal (finishes a multiple-part signature operation, returning the signature)
BOOL CxPKCS11::bSignFinal(
	CK_SESSION_HANDLE hSession,        /* the session's handle */
	CK_BYTE_PTR       pSignature,      /* gets the signature */
	CK_ULONG_PTR      pulSignatureLen  /* gets signature length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SignFinal(hSession, pSignature, pulSignatureLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSignRecoverInit (initializes a signature operation, where the data can be recovered from the signature)
BOOL CxPKCS11::bSignRecoverInit(
	CK_SESSION_HANDLE hSession,   /* the session's handle */
	CK_MECHANISM_PTR  pMechanism, /* the signature mechanism */
	CK_OBJECT_HANDLE  hKey        /* handle of the signature key */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SignRecoverInit(hSession, pMechanism, hKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSignRecover (signs data in a single operation, where the data can be recovered from the signature)
BOOL CxPKCS11::bSignRecover(
	CK_SESSION_HANDLE hSession,        /* the session's handle */
	CK_BYTE_PTR       pData,           /* the data to sign */
	CK_ULONG          ulDataLen,       /* count of bytes to sign */
	CK_BYTE_PTR       pSignature,      /* gets the signature */
	CK_ULONG_PTR      pulSignatureLen  /* gets signature length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_SignRecover(hSession, pData, ulDataLen, pSignature, pulSignatureLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Verify
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bVerifyInit (initializes a verification operation, where the signature is an appendix to the data, and plaintext cannot cannot be recovered from the signature (e.g. DSA))
BOOL CxPKCS11::bVerifyInit(
	CK_SESSION_HANDLE hSession,    /* the session's handle */
	CK_MECHANISM_PTR  pMechanism,  /* the verification mechanism */
	CK_OBJECT_HANDLE  hKey         /* verification key */ 
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyInit(hSession, pMechanism, hKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}	
//---------------------------------------------------------------------------
//TODO: - bVerify (verifies a signature in a single-part operation,  where the signature is an appendix to the data, and plaintext cannot be recovered from the signature)
BOOL CxPKCS11::bVerify(
	CK_SESSION_HANDLE hSession,       /* the session's handle */
	CK_BYTE_PTR       pData,          /* signed data */
	CK_ULONG          ulDataLen,      /* length of signed data */
	CK_BYTE_PTR       pSignature,     /* signature */
	CK_ULONG          ulSignatureLen  /* signature length*/
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_Verify(hSession, pData, ulDataLen, pSignature, ulSignatureLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bVerifyFinal (finishes a multiple-part verification operation, checking the signature)
BOOL CxPKCS11::bVerifyFinal(
	CK_SESSION_HANDLE hSession,       /* the session's handle */
	CK_BYTE_PTR       pSignature,     /* signature to verify */
	CK_ULONG          ulSignatureLen  /* signature length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyFinal(hSession, pSignature, ulSignatureLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bVerifyRecoverInit (initializes a signature verification operation, where the data is recovered from the signature)
BOOL CxPKCS11::bVerifyRecoverInit(
	CK_SESSION_HANDLE hSession,    /* the session's handle */
	CK_MECHANISM_PTR  pMechanism,  /* the verification mechanism */
	CK_OBJECT_HANDLE  hKey         /* verification key */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyRecoverInit(hSession, pMechanism, hKey );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bVerifyRecover (verifies a signature in a single-part operation, where the data is recovered from the signature)
BOOL CxPKCS11::bVerifyRecover(
	CK_SESSION_HANDLE hSession,        /* the session's handle */
	CK_BYTE_PTR       pSignature,      /* signature to verify */
	CK_ULONG          ulSignatureLen,  /* signature length */
	CK_BYTE_PTR       pData,           /* gets signed data */
	CK_ULONG_PTR      pulDataLen       /* gets signed data len */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyRecover(hSession, pSignature,ulSignatureLen, pData, pulDataLen );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bVerifyUpdate (continues a multiple-part verification operation, where the signature is an appendix to the data, and plaintext cannot be recovered from the signature)
BOOL CxPKCS11::bVerifyUpdate(
	CK_SESSION_HANDLE hSession,  /* the session's handle */
	CK_BYTE_PTR       pPart,     /* signed data */
	CK_ULONG          ulPartLen  /* length of signed data */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyUpdate(hSession, pPart, ulPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	Function	
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bGetFunctionList (returns the function list)
BOOL CxPKCS11::bGetFunctionList(
	CK_FUNCTION_LIST_PTR_PTR ppFunctionList  /* receives pointer to function list */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetFunctionList(ppFunctionList );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetFunctionStatus (is a legacy function; it obtains an updated status of a function running in parallel with an application)
BOOL CxPKCS11::bGetFunctionStatus(
	CK_SESSION_HANDLE hSession    /* the session's handle */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetFunctionStatus(hSession );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bCancelFunction (is a legacy function; it cancels a function running in parallel)
BOOL CxPKCS11::bCancelFunction(
	CK_SESSION_HANDLE hSession  /* the session's handle */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_CancelFunction(hSession);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetFunctionListEx (в SDK 4.53 этой функции нет)
BOOL CxPKCS11::bGetFunctionListEx(

)
{
	/*DEBUG*/

	////_m_ulRes = _m_pFunc->ETC_GetFunctionListEx();
	/////*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private static methods                                                         
*                                                                            
*****************************************************************************/

























/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + _bLoadETPKCS11 (Подгружаем eTPKCS11.dll и инициализируем PKCS#11)
BOOL CxPKCS11::_bLoadETPKCS11() {
    BOOL  bRes  = FALSE;
	ULONG ulRes = !CKR_OK;
	
	bRes = _m_dllETPKCS11.bLoad(ETPKCS11_PATH);
	xCHECK_RET(FALSE == bRes, FALSE);

    CK_C_GetFunctionList f_C_GetFunctionList = NULL;

	(FARPROC &)f_C_GetFunctionList = _m_dllETPKCS11.fpGetProcAddress("C_GetFunctionList");
    xCHECK_RET(NULL == f_C_GetFunctionList, FALSE);

    ulRes = f_C_GetFunctionList(&_m_pFunc);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - _bLoadETSAPI (Подгружаем eTSAPI.dll и приобретаем его необходимые методы)
BOOL CxPKCS11::_bLoadETSAPI() {
    BOOL bRes = FALSE;

	//FIX ME:
	bRes = _m_dllETSAPI.bLoad(ETSAPI_PATH);
	xCHECK_RET(FALSE == bRes, FALSE);

	////(FARPROC&)/*f*/_SAPI_GetTokenInfo = _m_dllETPKCS11.fpGetProcAddress("SAPI_GetLibraryInfo"/*"SAPI_GetTokenInfo"*/);
	////xCHECK_RET(NULL == /*f*/_SAPI_GetTokenInfo, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------






















/*

//---------------------------------------------------------------------------
//TODO: - FFFFFFFFFFFFF (CCCCCCCCCCCCCCCCCCCCCCCccc)
BOOL CxPKCS11::FFFFFFFFFFFFF(

)
{
	/DEBUG/

	_m_ulRes = _m_pFunc->XXXXXXXXXXXXX(XXXXXXXXXXXXXXXXXXXXXXX);
	/DEBUG/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}


*/