/**********************************************************************
*   CXeToken.cpp  (RTE 4.53)
*
***********************************************************************/


#define WIN32_LEAN_AND_MEAN		//Exclude rarely-used content from Windows headers.

#define MSG_WARNING(MSG)  ::MessageBox(0, (MSG).c_str(), "Внимание",   MB_OK + MB_ICONSTOP        + MB_TOPMOST)
#define MSG_INFO(MSG)     ::MessageBox(0, (MSG).c_str(), "Информация", MB_OK + MB_ICONINFORMATION + MB_TOPMOST)
#define APPLICATION_TITLE "eToken"
#define EMPTY_MSG_        "отсутствует"
#define ETPKCS11_PATH     "C:/WINDOWS/system32/eTPKCS11.dll"	//путь к eTPKCS11.dll
#define ETSAPI_PATH       "C:/WINDOWS/system32/eTSAPI.dll"     //путь к eTSAPI.dll
#define TRUE_MSG          "да"   				//FALSE_MSG >= TRUE_MSG
#define FALSE_MSG         "нет"
#define TOKEN_NON_PRESENT - 1
#define ZERO_DATA(x)      memset((void *)&x, 0, sizeof(x))
	
#include <XLib/CXeToken.h>
//---------------------------------------------------------------------------
//DONE: объявление SAPI's функции
typedef CK_RV (* t_SAPI_GetTokenInfo)(CK_SLOT_ID, CK_ATTRIBUTE_PTR, CK_ULONG);
////t_SAPI_GetTokenInfo f_SAPI_GetTokenInfo = NULL; /*DIF: SDK 3.60*/
t_SAPI_GetTokenInfo _SAPI_GetTokenInfo = NULL;		/*DIF: SDK 4.53*/
//---------------------------------------------------------------------------
//DONE: CXeToken
CXeToken::CXeToken() : 
	_m_tlLog        (FALSE),
    _m_pFunctionList(NULL),
	_m_bIsInit      (FALSE)
{
}
//---------------------------------------------------------------------------
//DONE: ~CXeToken
CXeToken::~CXeToken() {

}
//---------------------------------------------------------------------------
//DONE: bInitialize (Инициализируем DLL-ки (eTPKCS11.dll, eTSAPI.dll))
BOOL CXeToken::bInitialize() {
    BOOL bRes = FALSE;
	
	if (!_bLoadPKCS11() || !_bLoadETSAPI()) {
		_m_pFunctionList = NULL;
        _m_bIsInit      = FALSE;

		return FALSE;
    } 

    _m_bIsInit = TRUE; 

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bFinalize (Финализируем DLL-ки (eTPKCS11.dll, eTSAPI.dll))
BOOL CXeToken::bFinalize() {  //закрыть PKCS #11 библиотеку
    ULONG ulRes = !CKR_OK;
	
	if (!_m_bIsInit) {
		return FALSE;
	}     

	ulRes = _m_pFunctionList->C_Finalize(0);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	
	_m_pFunctionList = NULL;
	_m_bIsInit       = FALSE;

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bLoadPKCS11 (Подгружаем eTPKCS11.dll и инициализируем PKCS#11)
BOOL CXeToken::_bLoadPKCS11() {
    ULONG ulRes = !CKR_OK;
	
	HINSTANCE hLib = ::LoadLibrary(ETPKCS11_PATH);
    if (!hLib) {
        MessageBox(0, "Невозможно подгрузить etpkcs11.dll", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return FALSE;
    }

    CK_C_GetFunctionList f_C_GetFunctionList = NULL;
    (FARPROC&)f_C_GetFunctionList = ::GetProcAddress(hLib, "C_GetFunctionList");
    if (!f_C_GetFunctionList) {
        MessageBox(0, "C_GetFunctionList не найдена", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return FALSE;
    }

    ulRes = f_C_GetFunctionList(&_m_pFunctionList);
	if (ulRes != CKR_OK) {
		MSG_WARNING("C_GetFunctionList ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }
	
    ulRes = _m_pFunctionList->C_Initialize(0);
	if (ulRes != CKR_OK) {
		MSG_WARNING("C_Initialize ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bLoadETSAPI (Подгружаем eTSAPI.dll и приобретаем его необходимые методы)
BOOL CXeToken::_bLoadETSAPI() {
    HINSTANCE hLib = LoadLibrary(ETSAPI_PATH);
    if (!hLib) {
        MessageBox(0, "Невозможно подгрузить etsapi.dll", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return FALSE;
    }

    (FARPROC&)/*f*/_SAPI_GetTokenInfo = GetProcAddress(hLib, "SAPI_GetTokenInfo");
    if (!/*f*/_SAPI_GetTokenInfo) {
        MessageBox(0, "SAPI_GetTokenInfo не найдена", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/**********************************************************************
*   SLOT AND TOKEN MANAGEMENT FUNCTIONS
*
***********************************************************************/

//---------------------------------------------------------------------------
//TODO: ulGetSlotList()
ULONG *CXeToken::ulGetSlotList(/*ULONG &ulSlotCount*/) {
    ULONG ciSLOTS_NOT_PRESENT = - 1;

    ///std::string sSlots = "";
	if (!_m_bIsInit) {return NULL/*(ULONG *)ciSLOTS_NOT_PRESENT*/;}	//????????????

	ULONG ulRes    = !CKR_OK;
    ////////////ULONG uiAllSlots;  // = (unsigned int *)ciSLOTS_NOT_PRESENT;	//?????????????

    //получаем список слотов
    CK_SLOT_ID_PTR    pSlots      = NULL;
    ULONG ulSlotCount = 0;

    ulRes = _m_pFunctionList->C_GetSlotList(TRUE, NULL, &ulSlotCount);
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_GetSlotList ошибка --->" + _sEtokenErrorString(ulRes));
        return NULL/*(ULONG *)ciSLOTS_NOT_PRESENT*/;
    }
    if (ulSlotCount < 1) {
        MessageBox(0, "Нет вставленного eToken", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return NULL/*(ULONG *)ciSLOTS_NOT_PRESENT*/;
    }
    pSlots = new CK_SLOT_ID[ulSlotCount];
    ulRes = _m_pFunctionList->C_GetSlotList(TRUE, pSlots, &ulSlotCount);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_GetSlotList ошибка ---> " + _sEtokenErrorString(ulRes));
        return NULL/*(ULONG *)ciSLOTS_NOT_PRESENT*/;
    }

    ////ulSlotCount = nSlotCount;
    return pSlots;

//--    delete []pSlots;    pSlots = NULL;
//--    return uiAllSlots;
}
//---------------------------------------------------------------------------
//TODO: iInsertedTokens (Получаем количество вставленных токенов)
ULONG CXeToken::ulInsertedTokens() {
    if (!_m_bIsInit) {return 0;}

    ULONG ulRes        = !CKR_OK;
    ULONG ulSlotCount = 0;

    ulRes = _m_pFunctionList->C_GetSlotList(TRUE, NULL, &ulSlotCount);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_GetSlotList ошибка ---> " + _sEtokenErrorString(ulRes));
        return 0;
    }

    return ulSlotCount;
}
//---------------------------------------------------------------------------
////TODO: dwSelectSlot
////#include <memory.h>
////#include <string.h>
////
////#include <algorithm>
////using namespace std;
////
//////Global variables.
////CK_FUNCTION_LIST_PTR   _m_pFunctionList;
////CK_C_GetFunctionList   pGFL  = 0;
////CK_SESSION_HANDLE      session;
////CK_SLOT_ID*            slots;
////unsigned long          slot_count;
////
////unsigned long CXeToken::dwSelectSlot(char* readerName) {
////    ULONG ulRes = !CKR_OK;
////
////	//Get all the occupied slots.
////	unsigned long slot_index = 0;
////
////    //Get all the occupied slots
////	ulRes = _m_pFunctionList->C_GetSlotList(TRUE, NULL, &slot_count);
////	if (ulRes == CKR_OK) {
////		if (slot_count < 1)	{
////			//--leave ("No eToken is available.\n");
////		}
////
////		slots = new CK_SLOT_ID [slot_count];
////		ulRes = _m_pFunctionList->C_GetSlotList (TRUE, slots, &slot_count);
////		if (ulRes != CKR_OK) {
////			//--leave ("C_GetSlotList failed...\n");
////		}
////	} else {
////		//--leave ("C_GetSlotList failed...\n");
////	}
////  
////	//Get the selected slot information.
////	BOOL bFound = FALSE;
////	std::transform(readerName, readerName + strlen(readerName), readerName, tolower);
////	for (slot_index; slot_index < slot_count; slot_index++)	{
////		CK_SLOT_INFO slot_info;
////		
////		ulRes = _m_pFunctionList->C_GetSlotInfo (slots[slot_index], &slot_info);
////		if (ulRes != CKR_OK)	{
////			//--leave ("C_GetSlotInfo failed.\n");
////		}
////	   	std::transform(slot_info.slotDescription,slot_info.slotDescription + sizeof(slot_info.slotDescription),slot_info.slotDescription,tolower);
////	    if (memcmp((void*)slot_info.slotDescription, readerName, min(strlen(readerName), sizeof(slot_info.slotDescription))) == 0) {    
////			bFound = TRUE;
////			break;  
////	    }
////	}
////	return bFound? slot_index : 0; //If not found, work with slot 0.
////}
//---------------------------------------------------------------------------
//TODO: ulGetSlotInfo
unsigned long CXeToken::ulGetSlotType(ULONG ulSlotId) {
    ULONG   ulRes               = CKR_OK;
    
    const ULONG culKnownInfo       = 0;
    const ULONG culTokenNotPresent = 1;
    const ULONG culTokenPresent    = 3;
    const ULONG culRemovableDevice = 2;
    const ULONG culHardwareSlot    = 4;
	
	//-------------------------------------
	//если токен был вынят - выход
    if (!_m_bIsInit) {return culKnownInfo;}

	CK_SLOT_INFO siSI;
	ulRes = _m_pFunctionList->C_GetSlotInfo(ulSlotId, &siSI);                 //////////////////////???????
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_GetSlotInfo ошибка ---> " + _sEtokenErrorString(ulRes));
		return culKnownInfo;
	}

	//-------------------------------------
	//Токен извлечен (CKF_TOKEN_PRESENT     0x00000001)
	if (!(siSI.flags & CKF_TOKEN_PRESENT)) {
		return culTokenNotPresent;
	}

	//-------------------------------------
	//Токен - съёмное устройство (CKF_REMOVABLE_DEVICE  0x00000002)
	if (!(siSI.flags & CKF_REMOVABLE_DEVICE)) {
		return culRemovableDevice;
	}

    //-------------------------------------
	//Токен вставлен (CKF_TOKEN_PRESENT     0x00000001)
    if ((siSI.flags & CKF_TOKEN_PRESENT)) {
        return culTokenPresent;
	}

	//-------------------------------------
	//Токен - хадверный слот (CKF_HW_SLOT   0x00000004)
	if (!(siSI.flags & CKF_HW_SLOT)) {
		return culHardwareSlot;
	}

    return culKnownInfo;
}
//---------------------------------------------------------------------------
//DONE: dwWaitForSlotEvent (Ждём вставки/извлечения токена)
ULONG CXeToken::ulWaitForSlotEvent() {
    if (!_m_bIsInit) {
		return TOKEN_NON_PRESENT;
	}

    ULONG ulRes    = !CKR_OK;
	ULONG ulSlotId = TOKEN_NON_PRESENT;

    ulRes = _m_pFunctionList->C_WaitForSlotEvent(0, &ulSlotId, 0);
	if (ulRes != CKR_OK) {
        return TOKEN_NON_PRESENT;
    } else {
        return ulSlotId;
    }
}
//---------------------------------------------------------------------------
//DONE: sGetLibraryInfo (Информация о PKCS#11 библиотеке)
BOOL CXeToken::bGetLibraryInfo(TStringMap &smLibraryInfo) {
    if (FALSE == _m_bIsInit) {
		return FALSE;
	}

    ULONG   ulRes        = !CKR_OK;
	std::string         sLibraryInfo = "";
    
	CK_INFO info;	ZERO_DATA(info);
	ulRes = _m_pFunctionList->C_GetInfo(&info);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_GetInfo ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }

	smLibraryInfo["CRYPTOKI_VERSION_MAJOR"] = lexical_cast((unsigned int)info.cryptokiVersion.major);                            //unsigned char ???
	smLibraryInfo["CRYPTOKI_VERSION_MINOR"] = lexical_cast((unsigned int)info.cryptokiVersion.minor);                            //unsigned char ???
	smLibraryInfo["MANUFACTURER_ID"]        = sTrimSpace(lexical_cast((unsigned char *)info.manufacturerID).substr(0, 32));      //%.32s
	smLibraryInfo["LIBRARY_DESCRIPTION"]    = sTrimSpace(lexical_cast((unsigned char *)info.libraryDescription).substr(0, 32));  //%.32s
	smLibraryInfo["LIBRARY_VERSION_MAJOR"]  = lexical_cast((unsigned int)info.libraryVersion.major);                             //unsigned char ???
	smLibraryInfo["LIBRARY_VERSION_MINOR"]  = lexical_cast((unsigned int)info.libraryVersion.minor);                             //unsigned char ???

	return TRUE;
}
//---------------------------------------------------------------------------


/**********************************************************************
*	Объекты
*
***********************************************************************/

//--------------------------------------------------------------------------
//DONE: bIsDataObjectExists
BOOL CXeToken::bIsDataObjectExists(unsigned long ulSlotId, char *pszUserPIN, char *pszApplication/*ID*/, char *pszLabel, char *pszValue) {
   	ULONG ulRes         = !CKR_OK;

    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }

    //-------------------------------------
    //логинимся
    ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }

	//-------------------------------------
    //ищем объект
    CK_OBJECT_HANDLE  hObject    = NULL;
    ULONG ulFoundObj = 0;
    
    ULONG ulClass    = CKO_DATA;
    BOOL              bTrue      = CK_TRUE;

    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)       },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)         },
        {CKA_APPLICATION, pszApplication, strlen(pszApplication)}
    };

	////ULONG	//ULONG
	////size_t	//unsigned int

    //-------------------------------------
    //инициализируем поиск объектов
	ulRes = _m_pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjectsInit ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
	}

    //-------------------------------------
	//Find matching objects. There should be only a single match as there is only one on the eToken.
	ulRes = _m_pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjects ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
	}

    //-------------------------------------
    //Clean up the search.
    ulRes = _m_pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjectsFinal ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //делогинимся
    ulRes = _m_pFunctionList->C_Logout(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //закрываем сессию
    ulRes = _m_pFunctionList->C_CloseSession(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (ulFoundObj < 1) {
		return FALSE;
	}

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE: sGetDataObject
std::string CXeToken::sGetDataObject(ULONG ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/) {
    ULONG  ulRes = CKR_OK;
    std::string        sRes = "";
 
    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + _sEtokenErrorString(ulRes));
        return NULL;
    }

    //-------------------------------------
    //логинимся
    ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
        return NULL;
    }

	//-------------------------------------
    //ищем объект
    ULONG ulFoundObj = 0;

    CK_OBJECT_HANDLE  hObject    = NULL;
    ULONG ulClass    = CKO_DATA;
    BOOL              bTrue      = CK_TRUE;

    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)      },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)        },
        {CKA_APPLICATION, pszObjectName,  strlen(pszObjectName)}
    };

    //-------------------------------------
    //инициализируем поиск объектов
	ulRes = _m_pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjectsInit ошибка ---> " + _sEtokenErrorString(ulRes));
        return NULL;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRes = _m_pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjects ошибка ---> " + _sEtokenErrorString(ulRes));
        return NULL;
	}
    //Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (ulFoundObj < 1) {
		goto lDone;
	}

    //-------------------------------------
	//найден объект с нужным шаблоном
    {
        CK_ATTRIBUTE pDataTamplate[] = {
            {CKA_APPLICATION, NULL, 0},
            {CKA_LABEL,       NULL, 0},
            {CKA_VALUE,       NULL, 0}
        };

        //Get data issuer, subject, and value attributes
        ulRes = _m_pFunctionList->C_GetAttributeValue(hSession, hObject, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
        if (ulRes != CKR_OK) {
            MSG_WARNING("C_GetAttributeValue ошибка ---> " + _sEtokenErrorString(ulRes));
            goto lDone;
        }

        ULONG ulApplicationLen = pDataTamplate[0].ulValueLen;
        char             *pszApplication   = new char[ulApplicationLen];
        pDataTamplate[0].pValue = pszApplication;

        ULONG  ulLabelLen	   = pDataTamplate[1].ulValueLen;
        char              *pszLabel        = new char[ulLabelLen];
        pDataTamplate[1].pValue = pszLabel;

        ULONG  ulValueLen      = pDataTamplate[2].ulValueLen;
        char              *pszValue	       = new char[ulValueLen];
        pDataTamplate[2].pValue = pszValue;


        //-------------------------------------
        //получаем данные   //если CKA_LABEL == 3_Test_Login (выводит лишний символ)
        ulRes = _m_pFunctionList->C_GetAttributeValue(hSession, hObject, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
        if (ulRes != CKR_OK) {
            MSG_WARNING("C_GetAttributeValue ошибка ---> " + _sEtokenErrorString(ulRes));

            delete[] pszApplication;
            delete[] pszLabel;
            delete[] pszValue;

            goto lDone;
        }

        //-------------------------------------
        //формируем возвращяемую строку
        std::string sApplication = std::string(pszApplication, ulApplicationLen);
        std::string sLabel       = std::string(pszLabel,       ulLabelLen);
        std::string sValue       = std::string(pszValue,       ulValueLen);

        sRes =  "CKA_APPLICATION|" + sApplication + "\r\n" +
                "CKA_LABEL|"       + sLabel       + "\r\n" +
                "CKA_VALUE|"       + sValue       + "\r\n";

        delete[] pszApplication;
        delete[] pszLabel;
        delete[] pszValue;

        goto lDone;
	}

lDone:
    //-------------------------------------
    //Clean up the search.
    ulRes = _m_pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjectsFinal ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //делогинимся
    ulRes = _m_pFunctionList->C_Logout(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //закрываем сессию
    ulRes = _m_pFunctionList->C_CloseSession(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: bCreateDataObject
BOOL CXeToken::bCreateDataObject (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszLabel, char *pszValue) {
    ULONG  ulRes = CKR_OK;

	//-------------------------------------
	//открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

	ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }

	//-------------------------------------
	//логинимся
	ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }

    //-------------------------------------
    //создаём объект
    CK_OBJECT_HANDLE  hObject    = NULL;
    ULONG ulClass    = CKO_DATA;
    BOOL              bTrue      = CK_TRUE;
    BOOL              bPrivate   = CK_TRUE;
    
    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)      },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)        },
        {CKA_PRIVATE,	  &bPrivate,      sizeof(CK_BBOOL)     },
        {CKA_LABEL,       pszLabel,       strlen(pszLabel)     },
        {CKA_APPLICATION, pszObjectName,  strlen(pszObjectName)},
        {CKA_VALUE,       pszValue,       strlen(pszValue)     }
    };

    ulRes = _m_pFunctionList->C_CreateObject(hSession, pDataTamplate, sizeof (pDataTamplate) / sizeof (pDataTamplate[0]), &hObject);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_CreateObject ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }

    //-------------------------------------
    //делогинимся
    ulRes = _m_pFunctionList->C_Logout(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //закрываем сессию
    ulRes = _m_pFunctionList->C_CloseSession(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
    }

	return TRUE;
}
//--------------------------------------------------------------------------
//DONE: bDeleteDataObject
BOOL CXeToken::bDeleteDataObject(unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/) {
    ULONG  ulRes = CKR_OK;
    BOOL               bRes = FALSE;

    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        return bRes;
    }

    //-------------------------------------
    //логинимся
    ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        return bRes;
    }

	//-------------------------------------
    //ищем объект
    ULONG ulFoundObj = 0;

    CK_OBJECT_HANDLE  hObject    = NULL;
    ULONG ulClass    = CKO_DATA;
    BOOL              bTrue      = CK_TRUE;

    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)      },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)        },
        {CKA_APPLICATION, pszObjectName,  strlen(pszObjectName)}
    };

    //-------------------------------------
    //инициализируем поиск объектов
	ulRes = _m_pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjectsInit ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        return bRes;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRes = _m_pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjects ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        return bRes;
	}
    //Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (ulFoundObj < 1) {
        bRes = FALSE;
		goto lDone;
	}

    //-------------------------------------
	//найден объект с нужным шаблоном - удаляем его
	ulRes = _m_pFunctionList->C_DestroyObject(hSession, hObject);
	if (ulRes != CKR_OK) {
		MSG_WARNING("C_DestroyObject ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        goto lDone;
	}

    bRes = TRUE;
    goto lDone;

lDone:
    //-------------------------------------
    //Clean up the search.
    ulRes = _m_pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjectsFinal ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //делогинимся
    ulRes = _m_pFunctionList->C_Logout(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //закрываем сессию
    ulRes = _m_pFunctionList->C_CloseSession(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    return bRes;
}
//---------------------------------------------------------------------------
//DONE: bChangeDataObject
BOOL CXeToken::bChangeDataObject(unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszNewLabel, char *pszNewValue) {
    ULONG ulRes = !CKR_OK;
    BOOL              bRes = FALSE;
 
    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        return bRes;
    }

    //-------------------------------------
    //логинимся
    ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        return bRes;
    }

	//-------------------------------------
    //ищем объект
    ULONG ulFoundObj = 0;

    CK_OBJECT_HANDLE  hObject    = NULL;
    ULONG ulClass    = CKO_DATA;
    BOOL              bTrue      = CK_TRUE;

    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)      },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)        },
        {CKA_APPLICATION, pszObjectName,  strlen(pszObjectName)}
    };

    //-------------------------------------
    //инициализируем поиск объектов
	ulRes = _m_pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjectsInit ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        return bRes;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRes = _m_pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjects ошибка ---> " + _sEtokenErrorString(ulRes));
        bRes = FALSE;
        return bRes;
	}
    //Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (ulFoundObj < 1) {
        bRes = FALSE;
		goto lDone;
	}

    //-------------------------------------
    //найден объект с нужным шаблоном - меняем атрибуты
    {
        CK_ATTRIBUTE pNewDataTemplate[] = {
            {CKA_APPLICATION, pszObjectName, strlen(pszObjectName)},	//???? ID - не меняем
            {CKA_LABEL,       pszNewLabel,   strlen(pszNewLabel)  },
            {CKA_VALUE,       pszNewValue,   strlen(pszNewValue)  }
        };

        ulRes = _m_pFunctionList->C_SetAttributeValue(hSession, hObject, pNewDataTemplate, sizeof(pNewDataTemplate) / sizeof(pNewDataTemplate[0]));
        if (ulRes != CKR_OK) {
            MSG_WARNING("C_SetAttributeValue ошибка ---> " + _sEtokenErrorString(ulRes));
            bRes = FALSE;
            goto lDone;
        }

        bRes = TRUE;
        goto lDone;
    }        

lDone:
    //-------------------------------------
    //Clean up the search.
    ulRes = _m_pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_FindObjectsFinal ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //делогинимся
    ulRes = _m_pFunctionList->C_Logout(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    //-------------------------------------
    //закрываем сессию
    ulRes = _m_pFunctionList->C_CloseSession(hSession);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
    }

    return bRes;
}
//---------------------------------------------------------------------------
//DONE: bClearDataObject
BOOL CXeToken::bClearDataObject(unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/) {
    return bChangeDataObject(ulSlotId, pszUserPIN, pszObjectName/*ID*/, "", "");
}
//--------------------------------------------------------------------------

////---------------------------------------------------------------------------
//////TODO: bInitializeToken
/////*
////	Usage:   InitToken <reader-name> <format-password> <user-password>  
////	Example: InitToken "AKS ifdh 0" 1234567890 password
////*/
////BOOL CXeToken::bInitializeToken(const AnsiString& asFormatPass, const AnsiString& asUserPass) {
////    ULONG      ulRes     = CKR_OK;
////	CK_SESSION_HANDLE      hSession = NULL;
////
////    //--char *readerName     = argv[1];
////////	char *formatPassword = {"2222"};
////////	char *userPassword   = {"1111"};
////
//////--    AnsiString asFormatPass = "1111";
//////--    AnsiString asNewPass    = "2222";
////	
////	//--printf("Command line params: \n");
////	//--printf(" reader name(%s)\n", readerName);
////	//--printf(" format password(%s)\n", formatPassword);
////	//--printf(" user password(%s)\n",   userPassword);
////	//Load and initialize the PKCS#11 library.
////	//--bLoadPKCS11();	//--init();
////
////	//Insert command line argument for reader name ("AKS ifdh n").
////	/*is never used: int slot_index = 0*/;	//--selectSlot(readerName);
////    
////	//инициализируем токен (Initialize token with format password);
////	CK_CHAR token_label[] = {
////		"eToken"
////	};
////
////	ulRes = _m_pFunctionList->C_InitToken(0/*slots[slot_index]*/, asFormatPass.c_str()/*CK_CHAR_PTR(formatPassword)*/, asFormatPass.Length()/*strlen(formatPassword)*/, token_label);
////	if (ulRes != CKR_OK) {
////        MessageBox(0, "C_InitToken ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////		return FALSE;
////	}
////
////    //открываем сессию для чтения/записи на eToken 
////	ulRes = _m_pFunctionList->C_OpenSession(0/*slots[slot_index]*/, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
////	if (ulRes != CKR_OK) {
////        MessageBox(0, "C_OpenSession ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return FALSE;
////    }
////
////    //логинимся как SO с паролем formatPassword
////    /* Security Officer     #define CKU_SO    0 */
////    /* Normal user          #define CKU_USER  1 */
////	ulRes = _m_pFunctionList->C_Login(hSession, CKU_SO, asFormatPass.c_str()/*CK_CHAR_PTR(formatPassword)*/, asFormatPass.Length()/*strlen(formatPassword)*/);
////	if (ulRes != CKR_OK) {
////        MessageBox(0, "C_Login ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return FALSE;
////    }
////
////    //инициализируем USER PIN паролем userPassword
////	ulRes = _m_pFunctionList->C_InitPIN (hSession, asUserPass.c_str()/*CK_CHAR_PTR(userPassword)*/, asUserPass.Length()/*strlen(userPassword)*/);
////    if (ulRes != CKR_OK) {
////        MessageBox(0, "C_InitPIN ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return FALSE;
////    }
////
////    //делогинимся
////    ulRes = _m_pFunctionList->C_Logout(hSession);
////	if (ulRes != CKR_OK) {
////        MessageBox(0, "C_Logout ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return FALSE;
////    }
////
//////    //проверяем новый USER PIN.
//////    printf ("Logging in to eToken as USER with - %s \n", userPassword);
//////    if (CKR_OK != _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(userPassword), strlen(userPassword))) {
//////        MSG_WARNING("C_Login ошибка.\n");
//////        return FALSE;
//////    }
//////  
//////    //Show how to generate RSA key pair.
//////    //--genKeyPair();
//////
//////    //делогинимся
//////    if (CKR_OK != _m_pFunctionList->C_Logout (hSession)) {
//////        MSG_WARNING("C_Logout ошибка.\n");
//////        return FALSE;
//////    }
////
////    //закрываем сессию
////    ulRes = _m_pFunctionList->C_CloseSession(hSession);
////	if (ulRes != CKR_OK) {
////        MessageBox(0, "C_CloseSession ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return FALSE;
////    }                       
////
////    return TRUE;
////}
//---------------------------------------------------------------------------
//TODO: dwLocateToken
////DWORD CXeToken::dwLocateToken() {
////	DWORD dwSlots  = 1;
////	DWORD dwSlotID = 0;
////	if (CKR_OK != pFunc->C_GetSlotList(TRUE, &dwSlotID, &dwSlots)) {
////		MSG_WARNING("C_GetSlotList failed");
////		return TOKEN_NON_PRESENT;
////	}
////	if (dwSlots < 1) {
////		MSG_WARNING("No eToken inserted");
////		return TOKEN_NON_PRESENT;
////	}
////	return dwSlotID;
////}
//---------------------------------------------------------------------------
//TODO: bCheckPinPolicy
////BOOL CXeToken::bCheckPinPolicy(CK_SESSION_HANDLE	hSession, CK_OBJECT_HANDLE hObject) {
////	ULONG ulRes = !CKR_OK;
////	
////	CK_ULONG minPinAge   = 0;
////	CK_ULONG maxPinAge   = 0;
////	CK_ULONG warnPeriod  = 0;
////	CK_ULONG pinLen      = 0;
////	CK_ULONG historySize = 0;
////	CK_BBOOL mixChars    = CK_FALSE;
////
////	CK_ATTRIBUTE pTamplate[] = {
////		{ETCKA_PIN_MIN_AGE,           &minPinAge,   sizeof(minPinAge)  },
////		{ETCKA_PIN_MAX_AGE,          &maxPinAge,   sizeof(maxPinAge)},
////		{ETCKA_PIN_WARN_PERIOD, &warnPeriod,  sizeof(warnPeriod)   },
////		{ETCKA_PIN_MIN_LEN,            &pinLen,      sizeof(pinLen)           },
////		{ETCKA_PIN_HISTORY_SIZE,   &historySize, sizeof(historySize)   },
////		{ETCKA_PIN_MIX_CHARS,       &mixChars,    sizeof(mixChars)     }
////	};
////
////	if (ulRes = pFunc->C_GetAttributeValue(hSession, hObject, pTamplate, 6)) {
////		MSG_WARNING("Failed to get PIN policy information.");
////		return FALSE;
////	}
////
////	AnsiString asPinPolicyData = "";
////	asPinPolicyData.sprintf("\nNew PIN policy settings:\n");
////	asPinPolicyData.sprintf("PIN maximum age(%i)\n",maxPinAge);
////	asPinPolicyData.sprintf("PIN minimum age(%i)\n",minPinAge);
////	asPinPolicyData.sprintf("PIN warning period(%i)\n",warnPeriod);
////	asPinPolicyData.sprintf("Minimum PIN length(%i)\n",pinLen);
////	asPinPolicyData.sprintf("Maximum PIN history size(%i)\n",historySize);
////	asPinPolicyData.sprintf("PIN mixed characters(%i)\n",mixChars);
////	ShowMessage(asPinPolicyData);
////
////	if (minPinAge == m_minPinAge && maxPinAge == m_maxPinAge && warnPeriod == m_warnPeriod && pinLen == m_pinLen && historySize == m_historySize && mixChars == m_mixChars) {
////		return TRUE;
////	}	
////	
////	return FALSE;
/////}
//---------------------------------------------------------------------------
//DONE:  sGetTokenInfo

/**********************************************************************
*   sGetTokenInfo() - получить всю инфу о токене
*
*   Возвращаемое значение (формат):  
*	    имя_параметр1=значение
*       имя_параметр2=значение
*       ...
*       имя_параметрN=значение
*
***********************************************************************/
//TODO: sGetTokenInfo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

BOOL CXeToken::bGetTokenInfo(ULONG ulSlotId, TStringMap &smInfo) {
    //-------------------------------------
	//если токен был вынят - выход
    if (_m_bIsInit == FALSE) {
		return FALSE;
	}

    ULONG ulRes = !CKR_OK;
    
	CK_SLOT_INFO siSI;	ZERO_DATA(siSI);
	ulRes = _m_pFunctionList->C_GetSlotInfo(ulSlotId, &siSI);
	if (ulRes != CKR_OK) {
		MessageBox(0, "C_GetSlotInfo ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
		return FALSE;
	}
	//Если токен существует в слоте - показать его информацию
	if (!(siSI.flags & CKF_TOKEN_PRESENT)) {
		//MessageBox(0, "eToken извлечён", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
		return FALSE;
	}
	if (!(siSI.flags & CKF_REMOVABLE_DEVICE)) {
		MessageBox(0, "CKF_REMOVABLE_DEVICE", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
		return FALSE;
	}
	if (!(siSI.flags & CKF_HW_SLOT)) {
		MessageBox(0, "CKF_HW_SLOT", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);;
		return FALSE;
	}

	//-------------------------------------
	//eTSAPI.h

	//-------------------------------------
    //CKA_SAPI_PRODUCT_NAME [eToken PRO] (0)  //OutString
    {
		const ULONG ulProductNameLen = 256;
		char                    szProductName[ulProductNameLen];	ZERO_DATA(szProductName);	

        CK_ATTRIBUTE pTamplate[] = {
			{CKA_SAPI_PRODUCT_NAME, szProductName, ulProductNameLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) { 
			smInfo["CKA_SAPI_PRODUCT_NAME"] = EMPTY_MSG_; 
        } else {
			smInfo["CKA_SAPI_PRODUCT_NAME"] = std::string(szProductName, strlen(szProductName)); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_PRODUCT_NAME"] + "<<").c_str(), "", MB_OK);
    }    

    //-------------------------------------
    //CKA_SAPI_MODEL [Token P0514 F4.2.5.4] (1)     //OutString
    {
        const ULONG ulModelLen = 256;
        char                    szModel[ulModelLen];	ZERO_DATA(szModel);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_MODEL, szModel, ulModelLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_MODEL"] = EMPTY_MSG_; 
        } else {
            smInfo["CKA_SAPI_MODEL"] = std::string(szModel, strlen(szModel)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_MODEL"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_FW_VERSION [0.4] (2)         //OutVersion
    {
        const ULONG  ulFwVersionLen = sizeof(CK_VERSION) + 2;   //+1 символ на "." + 1 '\0'
        char                     szFwVersion[ulFwVersionLen];	ZERO_DATA(szFwVersion);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FW_VERSION, szFwVersion, ulFwVersionLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_FW_VERSION"] = EMPTY_MSG_; 
        } else {
            //--CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
            //--printf("%d.%d\n", pV->major, pV->minor);
            CK_VERSION *pV = (CK_VERSION *)pTamplate->pValue;
            sprintf(szFwVersion, "%d.%d", pV->major, pV->minor);
            smInfo["CKA_SAPI_FW_VERSION"] = std::string(szFwVersion, ulFwVersionLen); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_FW_VERSION"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_FW_REVISION [0] (3)      //OutDecimal
    {
        const ULONG  ulFwRevisionLen = sizeof(ULONG);         ///////////???
        char                     szFwRevision[ulFwRevisionLen];	ZERO_DATA(szFwRevision);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FW_REVISION, szFwRevision, ulFwRevisionLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_FW_REVISION"] = EMPTY_MSG_; 
        } else {
            //--printf("%d\n", *((int*)pAttr->pValue));
            sprintf(szFwRevision, "%d", *((int*)pTamplate->pValue));
            smInfo["CKA_SAPI_FW_REVISION"] = std::string(szFwRevision, ulFwRevisionLen);
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_FW_REVISION"] + "<<").c_str(), "", MB_OK);	////??????????
    }

    //-------------------------------------
    //CKA_SAPI_HW_VERSION [1.2] (4)   //OutVersion
    {
        const ULONG  ulHwVersionLen = sizeof(CK_VERSION) + 2;   //+1 символ на "."         ///???
        char                     szHwVersion[ulHwVersionLen];	ZERO_DATA(szHwVersion);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HW_VERSION, szHwVersion, ulHwVersionLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_HW_VERSION"] = EMPTY_MSG_; 
        } else {
            //--CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
            //--printf("%d.%d\n", pV->major, pV->minor);
            CK_VERSION *pV = (CK_VERSION *)pTamplate->pValue;
            sprintf(szHwVersion, "%d.%d", pV->major, pV->minor);
            smInfo["CKA_SAPI_HW_VERSION"] = std::string(szHwVersion, ulHwVersionLen); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_HW_VERSION"] + "<<").c_str(), "", MB_OK);	////??????????
    }

    //-------------------------------------
    //CKA_SAPI_HW_INTERNAL [01 04  ... 01 04 ff] (5)  //OutArray
    {
        const ULONG ulHwInternalLen = 256;
        char                    szHwInternal[ulHwInternalLen];	ZERO_DATA(szHwInternal);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HW_INTERNAL, szHwInternal, ulHwInternalLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_HW_INTERNAL"] = EMPTY_MSG_; 
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            char szTmp[3] = "";
            for (ULONG i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                smInfo["CKA_SAPI_HW_INTERNAL"] += std::string(szHwInternal, 3);		//+3 = 2 байта + 1 пробел
            }
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_HW_INTERNAL"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_PRODUCTION_DATE [27.08.2006] (6) //OutDate
    {
        const ULONG ulProductionDateLen = sizeof(CK_DATE) + 2 + 1;   //+2 символ на "." + 1 yна '\0'
        char                    szProductionDate[ulProductionDateLen];	ZERO_DATA(szProductionDate);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_PRODUCTION_DATE, szProductionDate, ulProductionDateLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_PRODUCTION_DATE"] = EMPTY_MSG_; 
        } else {
            //--CK_DATE* d = (CK_DATE*)pTemplate->pValue;
            //--printf("%c%c.%c%c.%c%c%c%c\n", d->day[0], d->day[1], d->month[0], d->month[1], d->year[0], d->year[1], d->year[2], d->year[3]);
            CK_DATE* d = (CK_DATE*)pTamplate->pValue;
            sprintf(szProductionDate, "%c%c.%c%c.%c%c%c%c", d->day[0], d->day[1], d->month[0], d->month[1], d->year[0], d->year[1], d->year[2], d->year[3]);

            if (strcmp(szProductionDate, "") != 0) {       /////////////////////////////////////////////////////////////////////???
                smInfo["CKA_SAPI_PRODUCTION_DATE"] = std::string(szProductionDate, ulProductionDateLen); 
            } else {
                smInfo["CKA_SAPI_PRODUCTION_DATE"] = EMPTY_MSG_;
            }
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_PRODUCTION_DATE"] + "<<").c_str(), "", MB_OK);
    }        

    //-------------------------------------
    //CKA_SAPI_CASE_MODEL [1] (7)   //OutDecimal
    {
        const ULONG  ulCaseModelLen = sizeof(ULONG);          //////////???
        char                     szCaseModel[ulCaseModelLen];	ZERO_DATA(szCaseModel);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CASE_MODEL, szCaseModel, ulCaseModelLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
			smInfo["CKA_SAPI_CASE_MODEL"] = EMPTY_MSG_; 
        } else {
            //--printf("%d\n", *((int*)pTemplate->pValue));
            sprintf(szCaseModel, "%d", *((int*)pTamplate->pValue));
			smInfo["CKA_SAPI_CASE_MODEL"] = std::string(szCaseModel, ulCaseModelLen); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_CASE_MODEL"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_TOKEN_ID [0x4706a314] (8)    //OutHex
    {
        const ULONG  ulTokenIdLen = 20;
        char                     szTokenId[ulTokenIdLen];	ZERO_DATA(szTokenId);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_TOKEN_ID, szTokenId, ulTokenIdLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_TOKEN_ID"] = EMPTY_MSG_; 
        } else {
            //--printf("0x%08x\n", *((unsigned int*)pAttr->pValue));
            sprintf(szTokenId, "0x%08x", *((unsigned int*)pTamplate->pValue));
            smInfo["CKA_SAPI_TOKEN_ID"] = std::string(szTokenId, strlen(szTokenId)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_TOKEN_ID"] + "<<").c_str(), "", MB_OK);
    }
	
    
	//-------------------------------------
	//CKA_SAPI_CARD_ID [24 9c 9f 10 39 1d] (9)           //OutArray
    {
        const ULONG ulCardIdLen = 256;
        char                    szCardId[ulCardIdLen];	ZERO_DATA(szCardId);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_ID, szCardId, ulCardIdLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_CARD_ID"] = EMPTY_MSG_; 
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            char szTmp[4] = "";	//+ 1 на '\0'
            for (ULONG i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                smInfo["CKA_SAPI_CARD_ID"] += std::string(szTmp, 3);	//+3 = 2 байта + 1 пробел
            }
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_CARD_ID"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_CARD_TYPE [1] (10)	//OutDecimal
    {
        const ULONG  ulpCardTypeLen = sizeof(ULONG);
        char                     pCardType[ulpCardTypeLen];	ZERO_DATA(pCardType);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_TYPE, pCardType, ulpCardTypeLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_CARD_TYPE"] = EMPTY_MSG_; 
        } else {
            //--printf("%d\n", *((int*)pAttr->pValue));
            sprintf(pCardType, "%d", *((int*)pTamplate->pValue));
            smInfo["CKA_SAPI_CARD_TYPE"] = std::string(pCardType, strlen(pCardType)); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_CARD_TYPE"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_CARD_VERSION [4.1] (11)	//OutVersion
    {
        const ULONG  ulCardVersionLen = sizeof(CK_VERSION) + 2;   //+1 символ на "." + 1 на '\0'
        char                     szCardVersion[ulCardVersionLen];	ZERO_DATA(szCardVersion);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_VERSION, szCardVersion, ulCardVersionLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_CARD_VERSION"] = EMPTY_MSG_; 
        } else {
            //--CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
            //--printf("%d.%d\n", pV->major, pV->minor);
            CK_VERSION* pV = (CK_VERSION*)pTamplate->pValue;
            sprintf(szCardVersion, "%d.%d", pV->major, pV->minor);
            smInfo["CKA_SAPI_CARD_VERSION"] = std::string(szCardVersion, ulCardVersionLen); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_CARD_VERSION"] + "<<").c_str(), "", MB_OK);
    }


    //-------------------------------------
    //CKA_SAPI_SERIAL [34 37 ... 20 20 20] (12)	//OutArray
    {
        const ULONG  ulSerialLen = 256;
        char                     szSerial[ulSerialLen];	ZERO_DATA(szSerial);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_SERIAL, szSerial, ulSerialLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_SERIAL"] = EMPTY_MSG_; 
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            char szTmp[4];		//+1 на '\0'
            for (ULONG i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                smInfo["CKA_SAPI_SERIAL"] += std::string(szTmp, 3);	//+3 = 2 байта + 1 пробел
             }
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_SERIAL"] + "<<").c_str(), "", MB_OK);
    }
	

    //-------------------------------------
    //CKA_SAPI_COLOR [0] (13)	//OutDecimal
    {
        const ULONG  ulColorLen = sizeof(ULONG);
        char                     szColor[ulColorLen];	ZERO_DATA(szColor);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_COLOR, szColor, ulColorLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_COLOR"] = EMPTY_MSG_;
        } else {
            //--printf("%d\n", *((int*)pAttr->pValue));
            sprintf(szColor, "%d", *((int*)pTamplate->pValue));
            smInfo["CKA_SAPI_COLOR"] = std::string(szColor, ulColorLen); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_COLOR"] + "<<").c_str(), "", MB_OK);
    }
                                                                       

    //-------------------------------------
    //CKA_SAPI_HAS_BATTERY [да | нет] (14)	//OutBoolean
    {
        const ULONG  ulHasBatteryLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHasBattery[ulHasBatteryLen];	ZERO_DATA(szHasBattery);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_BATTERY, szHasBattery, ulHasBatteryLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_HAS_BATTERY"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szHasBattery, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_HAS_BATTERY"] = std::string(szHasBattery, strlen(szHasBattery)); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_HAS_BATTERY"] + "<<").c_str(), "", MB_OK);
    }        


    //-------------------------------------
    //CKA_SAPI_HAS_LCD [да | нет] (15)	//OutBoolean
    {
        const ULONG  ulHasLCDLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHasLCD[ulHasLCDLen];	ZERO_DATA(szHasLCD);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_LCD, szHasLCD, ulHasLCDLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
           smInfo["CKA_SAPI_HAS_LCD"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szHasLCD, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_HAS_LCD"] = std::string(szHasLCD, strlen(szHasLCD)); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_HAS_LCD"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_HAS_USER [да | нет] (16)	//OutBoolean
    {
        const ULONG  ulHasUserLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHasUser[ulHasUserLen];	ZERO_DATA(szHasUser);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_USER, szHasUser, ulHasUserLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_HAS_USER"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szHasUser, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_HAS_USER"] = std::string(szHasUser, strlen(szHasUser)); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_HAS_USER"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_HAS_SO [да | нет] (17)	//OutBoolean
    {
        const ULONG  ulHasSOLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHasSO[ulHasSOLen];	ZERO_DATA(szHasSO);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_SO, szHasSO, ulHasSOLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_HAS_SO"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szHasSO, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_HAS_SO"] = std::string(szHasSO, strlen(szHasSO)); 
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_HAS_SO"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_FIPS [да | нет] (18)	//OutBoolean
    {
        const ULONG  ulFipsLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szFips[ulFipsLen];	ZERO_DATA(szFips);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FIPS, szFips, ulFipsLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_FIPS"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szFips, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_FIPS"] = std::string(szFips, strlen(szFips)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_FIPS"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_FIPS_SUPPORTED [да | нет] (19)	//OutBoolean
    {
        const ULONG  ulFipsSupportedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szFipsSupported[ulFipsSupportedLen];    ZERO_DATA(szFipsSupported);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FIPS_SUPPORTED, szFipsSupported, ulFipsSupportedLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_FIPS_SUPPORTED"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szFipsSupported, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_FIPS_SUPPORTED"] = std::string(szFipsSupported, strlen(szFipsSupported)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_FIPS_SUPPORTED"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_INIT_PIN_REQ [да | нет] (20)	//OutBoolean
    {
        const ULONG  ulInitPinReqLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szInitPinReq[ulInitPinReqLen];	ZERO_DATA(szInitPinReq);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_INIT_PIN_REQ, szInitPinReq, ulInitPinReqLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_INIT_PIN_REQ"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szInitPinReq, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_INIT_PIN_REQ"] = std::string(szInitPinReq, strlen(szInitPinReq)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_INIT_PIN_REQ"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_RSA_2048 [да | нет] (21)	//OutBoolean
    {
        const ULONG  ulRSA2048Len = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szRSA2048[ulRSA2048Len];		ZERO_DATA(szRSA2048);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_RSA_2048, szRSA2048, ulRSA2048Len}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_RSA_2048"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szRSA2048, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_RSA_2048"] = std::string(szRSA2048, strlen(szRSA2048));
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_RSA_2048"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_RSA_2048_SUPPORTED [да | нет] (22)	//OutBoolean
    {
        const ULONG  ulRSA2048SupportedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szRSA2048Supported[ulRSA2048SupportedLen];	ZERO_DATA(szRSA2048Supported);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_RSA_2048_SUPPORTED, szRSA2048Supported, ulRSA2048SupportedLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_RSA_2048_SUPPORTED"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szRSA2048Supported, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_RSA_2048_SUPPORTED"] = std::string(szRSA2048Supported, strlen(szRSA2048Supported)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_RSA_2048_SUPPORTED"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_HMAC_SHA1 [да | нет] (23)	//OutBoolean
    {
        const ULONG  ulHMACSHA1Len = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHMACSHA1[ulHMACSHA1Len];	ZERO_DATA(szHMACSHA1);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HMAC_SHA1, szHMACSHA1, ulHMACSHA1Len}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_HMAC_SHA1"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szHMACSHA1, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_HMAC_SHA1"] = std::string(szHMACSHA1, strlen(szHMACSHA1)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_HMAC_SHA1"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_HMAC_SHA1_SUPPORTED [да | нет] (24)	//OutBoolean
    {
        const ULONG  ulHMACSHA1SuppotedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHMACSHA1Suppoted[ulHMACSHA1SuppotedLen];	ZERO_DATA(szHMACSHA1Suppoted);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HMAC_SHA1_SUPPORTED, szHMACSHA1Suppoted, ulHMACSHA1SuppotedLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_HMAC_SHA1_SUPPORTED"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szHMACSHA1Suppoted, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_HMAC_SHA1_SUPPORTED"] = std::string(szHMACSHA1Suppoted, strlen(szHMACSHA1Suppoted)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_HMAC_SHA1_SUPPORTED"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_REAL_COLOR [да | нет] (25)	//OutBoolean
    {
        const ULONG  ulRealColorLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szRealColor[ulRealColorLen];	ZERO_DATA(szRealColor);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_REAL_COLOR, szRealColor, ulRealColorLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_REAL_COLOR"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szRealColor, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
            smInfo["CKA_SAPI_REAL_COLOR"] = std::string(szRealColor, strlen(szRealColor)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_REAL_COLOR"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_MAY_INIT [да | нет] (26)	//OutBoolean
    {
        const ULONG  ulMayInitLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szMayInit[ulMayInitLen];	ZERO_DATA(szMayInit);

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_MAY_INIT, szMayInit, ulMayInitLen}
        };

        ulRes = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRes != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
            return FALSE;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_MAY_INIT"] = EMPTY_MSG_;
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(szMayInit, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);
			smInfo["CKA_SAPI_MAY_INIT"] = std::string(szMayInit, strlen(szMayInit)); 
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_MAY_INIT"] + "<<").c_str(), "", MB_OK);
    }


                               
    //-------------------------------------
    //pkcs11			////CK_UTF8CharToStdStr
    CK_TOKEN_INFO tiTI;

    ulRes = _m_pFunctionList->C_GetTokenInfo(ulSlotId, &tiTI);
    if (ulRes != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + _sEtokenErrorString(ulRes));
        return FALSE;
    }
   
    //-------------------------------------
    //LABEL [eToken]     unsigned char[32] (27)		//CK_UTF8CHAR [32]
    {
        //printf ("Label: %.32s\n", tiTI.label);
        char szTemp[32 + 1];	ZERO_DATA(szTemp);
        sprintf(szTemp, "%.32s", tiTI.label);
        
        smInfo["LABEL"] = sTrimSpace(std::string(szTemp));
        //MessageBox(0, (">>" + smInfo["LABEL"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MANUFACTURER_ID [Aladdin Ltd.]   unsigned char[32] (28)
    {
        //printf ("Manufacturer: %.32s\n",          tiTI.manufacturerID);
        char szTemp[32 + 1];	ZERO_DATA(szTemp);
        sprintf(szTemp, "%.32s", tiTI.manufacturerID);
        smInfo["MANUFACTURER_ID"] = sTrimSpace(std::string(szTemp));
        //MessageBox(0, (">>" + smInfo["MANUFACTURER_ID"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MODEL_2 [eToken] unsigned char[16]    (29)????--------------------
    {
        //printf ("Model: %.16s\n",                 tiTI.model);
        char szTemp[16 + 1];	ZERO_DATA(szTemp);
        sprintf(szTemp, "%.16s", tiTI.model);
        smInfo["MODEL_2"] = sTrimSpace(std::string(szTemp)); 
        //MessageBox(0, (">>" + smInfo["MODEL_2"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //SERIAL_NUMBER [4706a314] unsigned char[16]   (30)---------------
    {
        //printf ("Serial number: %.16s\n",         tiTI.serialNumber);
        char szTemp[16 + 1];	ZERO_DATA(szTemp);
        sprintf(szTemp, "%.16s", tiTI.serialNumber);
        smInfo["SERIAL_NUMBER"] = sTrimSpace(std::string(szTemp));
        //MessageBox(0, (">>" + smInfo["SERIAL_NUMBER"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //HARDWARE_VERSION_MAJOR [1] (31)
    {
        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        char szTemp[1 + 1];	ZERO_DATA(szTemp);		//+1 на '\0' 
        sprintf(szTemp, "%d", tiTI.hardwareVersion.major);
        smInfo["HARDWARE_VERSION_MAJOR"] = std::string(szTemp); 
        //MessageBox(0, (">>" + smInfo["HARDWARE_VERSION_MAJOR"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //HARDWARE_VERSION_MINOR [2] (32)
    {
        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        char szTemp[1 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.hardwareVersion.minor);
        smInfo["HARDWARE_VERSION_MINOR"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["HARDWARE_VERSION_MINOR"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //FIRMWARE_VERSION_MAJOR [0] (33)
    {
        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        char szTemp[1 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.firmwareVersion.major);
        smInfo["FIRMWARE_VERSION_MAJOR"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["FIRMWARE_VERSION_MAJOR"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //FIRMWARE_VERSION_MINOR [4] (34)
    {
        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        char szTemp[1 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.firmwareVersion.minor);
        smInfo["FIRMWARE_VERSION_MINOR"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["FIRMWARE_VERSION_MINOR"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //SESSION_COUNT [0] unsigned long (35)
    {
        //printf ("Current session count: %d\n",    tiTI.ulSessionCount);
        char szTemp[1 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulSessionCount);
        smInfo["SESSION_COUNT"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["SESSION_COUNT"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MAX_SESSION_COUNT [0]  unsigned lon (36)
    {
        //printf ("Maximum session count: %d\n",    tiTI.ulMaxSessionCount);
        char szTemp[1 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulMaxSessionCount);
        smInfo["MAX_SESSION_COUNT"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["MAX_SESSION_COUNT"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MAX_RW_SESSION_COUNT [0] (37)
    {
        //printf ("Maximum RW session count: %d\n", tiTI.ulMaxRwSessionCount);
        char szTemp[1 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulMaxRwSessionCount);
        smInfo["MAX_RW_SESSION_COUNT"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["MAX_RW_SESSION_COUNT"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MIN_PIN_LEN [6...255] (38)
    {
        //printf ("PIN length: [%d..%d]\n",         tiTI.ulMinPinLen,  tiTI.ulMaxPinLen);
        char szTemp[1 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulMinPinLen);
        smInfo["MIN_PIN_LEN"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["MIN_PIN_LEN"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MAX_PIN_LEN [6...255] (39)
    {
        //printf ("PIN length: [%d..%d]\n",         tiTI.ulMinPinLen,  tiTI.ulMaxPinLen);
        char szTemp[3 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulMaxPinLen);
        smInfo["MAX_PIN_LEN"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["MAX_PIN_LEN"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //FREE_PUBLIC_MEMORY [27721 bytes] (40)
    {
        //printf ("Public memory: %d/%d bytes\n",   tiTI.ulFreePublicMemory,  tiTI.ulTotalPublicMemory);
        char szTemp[5 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulFreePublicMemory);
        smInfo["FREE_PUBLIC_MEMORY"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["FREE_PUBLIC_MEMORY"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //TOTAL_PUBLIC_MEMORY [32768 bytes] (41)
    {
        //printf ("Public memory: %d/%d bytes\n",   tiTI.ulFreePublicMemory,  tiTI.ulTotalPublicMemory);
        char szTemp[5 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulTotalPublicMemory);
        smInfo["TOTAL_PUBLIC_MEMORY"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["TOTAL_PUBLIC_MEMORY"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //FREE_PRIVATE_MEMORY [27721 bytes] (42)
    {
        //printf ("Private memory: %d/%d bytes\n",  tiTI.ulFreePrivateMemory, tiTI.ulTotalPrivateMemory);
        char szTemp[5 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulFreePrivateMemory);
        smInfo["FREE_PRIVATE_MEMORY"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["TOTAL_PUBLIC_MEMORY"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //TOTAL_PRIVATE_MEMORY [32768 bytes] (43)
    {
        //printf ("Private memory: %d/%d bytes\n",  tiTI.ulFreePrivateMemory, tiTI.ulTotalPrivateMemory);
        char szTemp[5 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulTotalPrivateMemory);
        smInfo["TOTAL_PRIVATE_MEMORY"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["TOTAL_PRIVATE_MEMORY"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //RANDOM_NUMBER_GENERATOR [да | нет] (44)
    {
        if (tiTI.flags & CKF_RNG) {
            smInfo["RANDOM_NUMBER_GENERATOR"] = TRUE_MSG;	//printf ("Yes\n");
        } else {
			smInfo["RANDOM_NUMBER_GENERATOR"] = FALSE_MSG;	//printf ("No\n");
        }
        //MessageBox(0, (">>" + smInfo["RANDOM_NUMBER_GENERATOR"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //IS_WRITE_PROTECTED [да | нет] (45)
    {
        if (tiTI.flags & CKF_WRITE_PROTECTED) {
            smInfo["IS_WRITE_PROTECTED"] = TRUE_MSG;	//printf ("Yes\n");
        } else {
			smInfo["IS_WRITE_PROTECTED"] = FALSE_MSG;	//printf ("No\n");
        }
        //MessageBox(0, (">>" + smInfo["IS_WRITE_PROTECTED"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //LOGIN_REQUIRED [да | нет] (46)
    {
        if (tiTI.flags & CKF_LOGIN_REQUIRED) {
            smInfo["LOGIN_REQUIRED"] = TRUE_MSG;	//printf ("Yes\n");
        } else {
			smInfo["LOGIN_REQUIRED"] = FALSE_MSG;	//printf ("No\n");
        }
        //MessageBox(0, (">>" + smInfo["LOGIN_REQUIRED"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //USERS_PIN_IS_SET [да | нет] (47)
    {
        if (tiTI.flags & CKF_USER_PIN_INITIALIZED) {
            smInfo["USERS_PIN_IS_SET"] = TRUE_MSG;	//printf ("Yes\n");
        } else {
			smInfo["USERS_PIN_IS_SET"] = FALSE_MSG;	//printf ("No\n");
        }
        //MessageBox(0, (">>" + smInfo["USERS_PIN_IS_SET"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //RESTORE_KEY_NOT_NEEDED [да | нет] (48)
    {
        if (tiTI.flags & CKF_RESTORE_KEY_NOT_NEEDED) {
            smInfo["RESTORE_KEY_NOT_NEEDED"] = TRUE_MSG;	//printf ("Yes\n");
        } else {
			smInfo["RESTORE_KEY_NOT_NEEDED"] = FALSE_MSG;	//printf ("No\n");
        }
        //MessageBox(0, (">>" + smInfo["RESTORE_KEY_NOT_NEEDED"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CLOCK_ON_TOKEN [да | нет] (49)
    {
        if (tiTI.flags & CKF_CLOCK_ON_TOKEN) {
            smInfo["CLOCK_ON_TOKEN"] = TRUE_MSG;	//printf ("Yes\n");
        } else {
			smInfo["CLOCK_ON_TOKEN"] = FALSE_MSG;	//printf ("No\n");
        }
        //MessageBox(0, (">>" + smInfo["CLOCK_ON_TOKEN"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //HAS_PROTECTED_AUTHENTICATION_PATH [да | нет] (50)
    {
        if (tiTI.flags & CKF_PROTECTED_AUTHENTICATION_PATH) {
            smInfo["HAS_PROTECTED_AUTHENTICATION_PATH"] = TRUE_MSG;	//printf ("Yes\n");
        } else {
			smInfo["HAS_PROTECTED_AUTHENTICATION_PATH"] = FALSE_MSG;	//printf ("No\n");
        }
        //MessageBox(0, (">>" + smInfo["HAS_PROTECTED_AUTHENTICATION_PATH"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //DUAL_CRYPTO_OPERATIONS [да | нет] (51)
    {
        if (tiTI.flags & CKF_DUAL_CRYPTO_OPERATIONS) {
            smInfo["DUAL_CRYPTO_OPERATIONS"] = TRUE_MSG;	//printf ("Yes\n");
        } else {
			smInfo["DUAL_CRYPTO_OPERATIONS"] = FALSE_MSG;	//printf ("No\n");
        }
        //MessageBox(0, (">>" + smInfo["DUAL_CRYPTO_OPERATIONS"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //RSA_MECHANISM_MAX_KEY_SIZE [1024] (52)
    {
        CK_MECHANISM_INFO mecInfo;	ZERO_DATA(mecInfo);
	
        ulRes = _m_pFunctionList->C_GetMechanismInfo(ulSlotId, CKM_RSA_PKCS, &mecInfo);
        if (ulRes != CKR_OK) {
            smInfo["RSA_MECHANISM_MAX_KEY_SIZE"] = EMPTY_MSG_;
        } else {
            //printf ("RSA Mechanism MaxKeySize: %d\n", mecInfo.ulMaxKeySize);
			char szTemp[4 + 1];	ZERO_DATA(szTemp);		//+ 1 на '\0' 
			sprintf(szTemp, "%d", mecInfo.ulMaxKeySize);
			smInfo["RSA_MECHANISM_MAX_KEY_SIZE"] = std::string(szTemp);
			//MessageBox(0, (">>" + smInfo["RSA_MECHANISM_MAX_KEY_SIZE"] + "<<").c_str(), "", MB_OK);
        }
    }

	return TRUE;
}
//---------------------------------------------------------------------------



/**********************************************************************
*	Шифрование
*
***********************************************************************/

//--------------------------------------------------------------------------
//TODO: bEncryptDES
BOOL CXeToken::bEncryptDES(unsigned long  ulSlotId,
                           char          *pszUserPIN,
                           unsigned char *pucKey,        ULONG  ulKeyLen,
                           unsigned char *pucIv,         ULONG  ulIvLen,
                           unsigned char *pucPlainText,  ULONG  ulPlainTextLen,
                           unsigned char *pucCipherText, ULONG &ulCipherTextLen)
{

    ULONG ulRes     = !CKR_OK;
    ULONG ulPadSize = 8;  //для DES 64 бита
    ULONG ulOffset  = 0;

    //-------------------------------------
    //открываем сессию
    CK_SESSION_HANDLE hSession = 0;          
    ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0, &hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	///*LOG*/_m_tlLog.bWrite("C_OpenSession ошибка" + _sEtokenErrorString(ulRes)).c_str());
	//    return FALSE;
	//}
                                                        
    //-------------------------------------
    //логинимся
    ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)strlen(pszUserPIN));
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
    //if (ulRes != CKR_OK) {
    //    /*LOG*/_m_tlLog.bWrite("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
    //    return FALSE;
    //}

    //-------------------------------------
    //создаём ключ
    CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
    CK_KEY_TYPE     ulKeyType   = CKK_DES;
    CK_BBOOL        bTrueValue  = TRUE;
    CK_BBOOL        bFalseValue = FALSE;

    CK_ATTRIBUTE pTemplate[] = {
        {CKA_CLASS,    &ulClass,     sizeof(ulClass)    },
        {CKA_KEY_TYPE, &ulKeyType,   sizeof(ulKeyType)  },
        {CKA_ENCRYPT,  &bTrueValue,  sizeof(bTrueValue) },
        {CKA_TOKEN,    &bFalseValue, sizeof(bFalseValue)},
        {CKA_VALUE,    pucKey,       ulKeyLen           }
    };

    CK_OBJECT_HANDLE hKey = 0;
    ulRes = _m_pFunctionList->C_CreateObject(hSession, pTemplate, sizeof(pTemplate) / sizeof(CK_ATTRIBUTE), &hKey);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//       /*LOG*/_m_tlLog.bWrite("C_CreateObject ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}              
 
	//-------------------------------------
	//шифруем
    CK_MECHANISM Mech;	ZERO_DATA(Mech);
    Mech.mechanism      = CKM_DES_CBC_PAD;
    Mech.pParameter     = pucIv;
    Mech.ulParameterLen = ulIvLen;
 
    ulRes = _m_pFunctionList->C_EncryptInit(hSession, &Mech, hKey);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
    //if (ulRes != CKR_OK ) {
    //    /*LOG*/_m_tlLog.bWrite("C_EncryptInit ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
    //}

    ////////if (ulPlainTextLen + ulPadSize - ulPlainTextLen % ulPadSize > ulCipherTextLen) {	//?????????????
    ////////    return FALSE;
    ////////}

    //продолжаем  многоступенчатое шифрование
    for (ulOffset = 0; ulOffset < ulPlainTextLen; ulOffset += ulPadSize) {
        ulRes = _m_pFunctionList->C_EncryptUpdate(hSession, pucPlainText + ulOffset, ulPadSize, pucCipherText + ulOffset, &ulCipherTextLen);
		/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
		//if (ulRes != CKR_OK) {
        //    /*LOG*/_m_tlLog.bWrite("C_EncryptUpdate ошибка ---> " + _sEtokenErrorString(ulRes));
		//	return FALSE;
        //}
    }

    //заканчиваем многоступенчатое шифрование
    ulRes = _m_pFunctionList->C_EncryptFinal(hSession, pucCipherText + ulOffset, &ulCipherTextLen);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
    //if (ulRes != CKR_OK) {
    //    /*LOG*/_m_tlLog.bWrite("C_EncryptFinal ошибка ---> " + _sEtokenErrorString(ulRes));
    //}
    /***/ulCipherTextLen = ulOffset;	/***/


    //-------------------------------------
    //удаляем ключ
    //--	if (key != (CK_OBJECT_HANDLE) 0) {}
    ulRes = _m_pFunctionList->C_DestroyObject(hSession, hKey);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
    //if (ulRes != CKR_OK) {
    //    /*LOG*/_m_tlLog.bWrite("C_DestroyObject ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
    //}

    //-------------------------------------
    //делогинимся
    ulRes = _m_pFunctionList->C_Logout(hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
    //if (ulRes != CKR_OK) {
    //    /*LOG*/_m_tlLog.bWrite("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
    //}

    //-------------------------------------
    //закрываем сессию
    ulRes = _m_pFunctionList->C_CloseSession(hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
    //if (ulRes != CKR_OK) {
    //    /*LOG*/_m_tlLog.bWrite("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
    //}

    //Log.vOpen();

    return TRUE;	
}
//--------------------------------------------------------------------------
//TODO: bDecryptDES
BOOL CXeToken::bDecryptDES(unsigned long  ulSlotId,
						   char          *pszUserPIN,    
						   unsigned char *pucKey,        ULONG  ulKeyLen,
						   unsigned char *pucIv,         ULONG  ulIvLen,
						   unsigned char *pucCipherText, ULONG  ulCipherTextLen,
						   unsigned char *pucPlainText,  ULONG &ulPlainTextLen) 
{
	ULONG ulRes     = !CKR_OK;
	ULONG ulPadSize = 8;  //для DES 64 бита
	ULONG ulOffset  = 0;

	//-------------------------------------
	//открываем сессию
	CK_SESSION_HANDLE hSession;
	ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0, &hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_OpenSession ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE; 
	//}

	//-------------------------------------
	//логинимся
	ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)strlen(pszUserPIN));
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//создаём ключ
	CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
	CK_KEY_TYPE     ulKeyType   = CKK_DES;
	CK_BBOOL        bTrue       = TRUE;
	CK_BBOOL        bFalse      = FALSE;
	CK_ATTRIBUTE    pTemplate[] = {
		{CKA_CLASS,    &ulClass,   sizeof(ulClass)  },
		{CKA_KEY_TYPE, &ulKeyType, sizeof(ulKeyType)},
		{CKA_DECRYPT,  &bTrue,     sizeof(bTrue)    },
		{CKA_TOKEN,    &bFalse,    sizeof(bFalse)   },
		{CKA_VALUE,    pucKey,     ulKeyLen         }
	};

	CK_OBJECT_HANDLE hKey = 0;
	ulRes = _m_pFunctionList->C_CreateObject(hSession, pTemplate, sizeof(pTemplate) / sizeof(CK_ATTRIBUTE), &hKey);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_CreateObject ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//дешифруем
	CK_MECHANISM Mech;
	Mech.mechanism      = CKM_DES_CBC_PAD;
	Mech.pParameter     = pucIv;
	Mech.ulParameterLen = ulIvLen;

	ulRes = _m_pFunctionList->C_DecryptInit(hSession, &Mech, hKey);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_DecryptInit ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//continue a multiple-part decryption operation
	ULONG ulFirstPieceLen = 5104;
	ulRes = _m_pFunctionList->C_DecryptUpdate(hSession, pucCipherText, ulCipherTextLen+1, pucPlainText, &ulFirstPieceLen);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (CKR_OK != ulRes) {
	//	/*LOG*/_m_tlLog.bWrite("C_DecryptUpdate ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}
	
	//ULONG ulEndPieceLen = ulPlainTextLen - ulFirstPieceLen;
	//ulRes = _m_pFunctionList->C_DecryptFinal(hSession, pucPlainText + ulPlainTextLen, &ulEndPieceLen);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_DecryptFinal ошибка ---> " + _sEtokenErrorString(ulRes));
	//}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
	////*if (ulPlainTextLen + ulPadSize - ulPlainTextLen % ulPadSize > ulCipherTextLen) {	//?????????????
	//	return FALSE;
	//}

	////продолжаем  многоступенчатое шифрование
	//for (ulOffset = 0; ulOffset < ulPlainTextLen; ulOffset += ulPadSize) {
	//	ulRes = _m_pFunctionList->C_EncryptUpdate(hSession, pucPlainText + ulOffset, ulPadSize, pucCipherText + ulOffset, &ulCipherTextLen);
	//	if (ulRes != CKR_OK) {
	//		_m_tlLog.bWrite("C_EncryptUpdate ошибка ---> " + _sEtokenErrorString(ulRes));
	//		return FALSE;
	//	}
	//}*/
	//if (ulCipherTextLen + ulPadSize - ulCipherTextLen % ulPadSize > ulPlainTextLen) {	
	//	return FALSE;
	//}

	////продолжаем  многоступенчатое шифрование
	//unsigned char     ucCipherTextX[]    = {0xc1, 0xfe, 0x3c, 0x32, 0x06, 0x09, 0x82, 0x57, 0xf3, 0xc3, 0x38, 0x69, 0x97, 0x1d, 0x6e, 0xcd};  //{0xc1, 0xfe, 0x3c, 0x32, 0x06, 0x09, 0x82, 0x57, 0x16, 0xc1, 0xe4, 0xf8, 0x2b, 0xec, 0xf3, 0xa7};
	//ULONG ulCipherTextLXenX   = sizeof(ucCipherTextX);

	//for (ulOffset = 0; ulOffset < /*ulCipherTextLen*/ulCipherTextLXenX; ulOffset += ulPadSize) {
	//	ulPlainTextLen = 8;
	//	ulRes = _m_pFunctionList->C_DecryptUpdate(hSession, /*pucCipherText*/ucCipherTextX + ulOffset, ulPadSize, pucPlainText + ulOffset, &ulPlainTextLen);
	//	if (ulRes != CKR_OK) {
	//		/*LOG*/_m_tlLog.bWrite("C_DecryptUpdate ошибка ---> " + _sEtokenErrorString(ulRes));
	//		return FALSE;
	//	}
	//}

	////заканчиваем многоступенчатое шифрование
	//ulRes = _m_pFunctionList->C_DecryptFinal(hSession, pucPlainText + ulOffset, &ulPlainTextLen);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_DecryptFinal ошибка ---> " + _sEtokenErrorString(ulRes));
	//}
	////***/ulPlainTextLen = ulOffset;	/***/

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	//удаляем ключ
	//--	if (key != (CK_OBJECT_HANDLE) 0) {}
	ulRes = _m_pFunctionList->C_DestroyObject(hSession, hKey);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_DestroyObject ошибка ---> " + _sEtokenErrorString(ulRes));
	//}

	//-------------------------------------
	//делогинимся
	ulRes = _m_pFunctionList->C_Logout(hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
	//}

	//-------------------------------------
	//закрываем сессию
	ulRes = _m_pFunctionList->C_CloseSession(hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
	//}

	return TRUE;
}
//--------------------------------------------------------------------------
//TODO: sEncryptFileDES
BOOL CXeToken::bEncryptFileDES(const std::string &csFilePathIn, 
							   const std::string &csFilePathOut,
							   char              *pszUserPIN,    
							   unsigned char     *pucKey,        ULONG  ulKeyLen,
							   unsigned char     *pucIv,         ULONG  ulIvLen) 
{
									  
	//-------------------------------------
	//CHECK

	//-------------------------------------
	//JOB							  
	ULONG ulRes     = !CKR_OK;

	//-------------------------------------
	//создаём вх, вых файлы 
	FILE *pFileIn = fopen(csFilePathIn.c_str(), "rb+");
	/*DEBUG*/XASSERT_RET(NULL != pFileIn, FALSE);

	//if (NULL == pFileIn) {
	//	/*LOG*/_m_tlLog.bWrite("Не могу открыть входной файл: ",  + csFilePathIn);
	//	return FALSE;
	//}

	FILE *pFileOut = fopen(csFilePathOut.c_str(), "wb+");
	/*DEBUG*/XASSERT_RET(NULL != pFileOut, FALSE);
	//if (NULL == pFileOut) {
	//	/*LOG*/_m_tlLog.bWrite("Не могу открыть выходной файл: " + csFilePathOut);
	//	return FALSE;
	//}

	//-------------------------------------
	//получаем размер файла
	fseek(pFileIn , 0 , SEEK_END);
	ULONG ulSize = ftell (pFileIn);
	rewind(pFileIn);

	//-------------------------------------
	//выделяем память для буфера вх. файла
	ULONG  ulInBuffSize = ulSize; //in
	unsigned char     *pucInBuff = new unsigned char[ulInBuffSize];
	/*DEBUG*/XASSERT_RET(NULL != pucInBuff, FALSE);
	//if (NULL == pucInBuff) {
	//	return FALSE;
	//}
	
	//-------------------------------------
	//выделяем память для буфера вых. файла
	ULONG  ulOutBuffSize = ulSize;  //out
	unsigned char     *pucOutBuff = new unsigned char[ulOutBuffSize + 16/*pad*/];
	/*DEBUG*/XASSERT_RET(NULL != pucOutBuff, FALSE);
	//if (NULL == pucOutBuff) {
	//	return FALSE;
	//}
	memset(pucOutBuff, 0, ulOutBuffSize + 16/*pad*/);

	//-------------------------------------
	//читаем файл в вх. буфер
	ULONG ulReadedLen = fread(pucInBuff, 1, ulInBuffSize, pFileIn);
	if (ulReadedLen != ulInBuffSize) {
		/*LOG*/_m_tlLog.bWrite("uiReadedLen != ulBuffInSize");
		return FALSE;
	}

	//-------------------------------------
	//шифруем буфер
	BOOL bIsEncrypted = bEncryptDES(0, pszUserPIN, pucKey, ulKeyLen, pucIv, ulIvLen, pucInBuff, ulInBuffSize, pucOutBuff, ulOutBuffSize);
	if (FALSE == bIsEncrypted) {
		/*LOG*/_m_tlLog.bWrite("FALSE == bIsEncrypted");
		return FALSE;
	}
	///*LOG*/Log.vLogUCharAsHex("pucOutBuff ---> ", pucOutBuff, ulOutBuffSize);

	//-------------------------------------
	//пишем буфер в файл
	//получился буфер кратный 8, пишем буфер такого же размера как и размер вх. файла
	ULONG ulWrited = fwrite(pucOutBuff, 1, ulOutBuffSize, pFileOut); 
	if (ulWrited != ulOutBuffSize) {
		/*LOG*/_m_tlLog.bWrite("uiWrited != ulBuffOutSize");
		return FALSE;
	}

	//-------------------------------------
	//закрываем вх, вых файлы
	delete [] pucOutBuff;	pucOutBuff = NULL;	
	fflush(pFileOut);	
	fclose(pFileOut);
	
	delete [] pucInBuff;	pucInBuff = NULL;	
	fflush(pFileIn);	
	fclose(pFileIn);

	return TRUE;
}
//--------------------------------------------------------------------------
//TODO: sDecryptFileDES
BOOL CXeToken::bDecryptFileDES(const std::string &csFilePathIn, 
							   const std::string &csFilePathOut,
							   char              *pszUserPIN,    
							   unsigned char     *pucKey,        ULONG  ulKeyLen,
							   unsigned char     *pucIv,         ULONG  ulIvLen) 
{
	//-------------------------------------
	//CHECK

	//-------------------------------------
	//JOB							  
	ULONG ulRes     = !CKR_OK;

	//-------------------------------------
	//создаём вх, вых файлы 
	FILE *pFileIn = fopen(csFilePathIn.c_str(), "rb+");
	/*DEBUG*/XASSERT_RET(NULL != pFileIn, FALSE);
	//if (NULL == pFileIn) {
	//	/*LOG*/_m_tlLog.bWrite("Не могу открыть входной файл: " + csFilePathIn);
	//	return FALSE;
	//}

	FILE *pFileOut = fopen(csFilePathOut.c_str(), "wb+");
	/*DEBUG*/XASSERT_RET(NULL != pFileOut, FALSE);
	//if (NULL == pFileOut) {
	//	/*LOG*/_m_tlLog.bWrite("Не могу открыть выходной файл: " + csFilePathOut);
	//	return FALSE;
	//}

	//-------------------------------------
	//получаем размер файла
	fseek(pFileIn , 0 , SEEK_END);
	ULONG ulSize = ftell(pFileIn);
	if (0 == ulSize) {
		return FALSE;
	}
	rewind(pFileIn);

	//-------------------------------------
	//выделяем память для буфера вх. файла
	ULONG  ulInBuffSize = ulSize/*+'\0'*/; 
	unsigned char     *pucInBuff = new unsigned char[ulInBuffSize/*+'\0'*/];
	if (NULL == pucInBuff) {
		return FALSE;
	}

	//-------------------------------------
	//выделяем память для буфера вых. файла
	ULONG  ulOutBuffSize = ulSize;	//out
	unsigned char     *pucOutBuff = new unsigned char[ulOutBuffSize];
	if (NULL == pucOutBuff) {
		return FALSE;
	}
	memset(pucOutBuff, 0, sizeof(unsigned char) * ulOutBuffSize);

	//-------------------------------------
	//читаем файл в вх. буфер
	size_t uiReadedLen = fread(pucInBuff, 1, ulSize/*ulInBuffSize*/, pFileIn);
	if (uiReadedLen != ulSize/*ulInBuffSize*/) {
		/*LOG*/_m_tlLog.bWrite("uiReadedLen != ulBuffInSize");
		return FALSE;
	}

	//-------------------------------------
	//шифруем буфер
	BOOL bIsDecrypted = bDecryptDES(0, pszUserPIN, pucKey, ulKeyLen, pucIv, ulIvLen, pucInBuff, ulInBuffSize, pucOutBuff, ulOutBuffSize);
	if (FALSE == bIsDecrypted) {
		/*LOG*/_m_tlLog.bWrite("FALSE == bIsEncrypted");
		return FALSE;
	}
	///*LOG*/Log.vLogUCharAsHex("pucOutBuff ---> ", pucOutBuff, ulOutBuffSize);

	//-------------------------------------
	//пишем буфер в файл
	size_t uiWrited = fwrite(pucOutBuff, 1, ulOutBuffSize, pFileOut); 
	if (uiWrited != ulOutBuffSize) {
		/*LOG*/_m_tlLog.bWrite("uiWrited != ulBuffOutSize");
		return FALSE;
	}

	//-------------------------------------
	//закрываем вх, вых файлы
	delete [] pucOutBuff;	pucOutBuff = NULL;	
	fflush(pFileOut);	
	fclose(pFileOut);

	delete [] pucInBuff;	pucInBuff = NULL;	
	fflush(pFileIn);	
	fclose(pFileIn);

	return TRUE;
}
//--------------------------------------------------------------------------
//DONE: bEncryptDES
BOOL CXeToken::bEncryptDES3(unsigned long  ulSlotId,
							char          *pszUserPIN,    
							unsigned char *pucKey,        ULONG  ulKeyLen,
							unsigned char *pucIv,         ULONG  ulIvLen,
							unsigned char *pucPlainText,  ULONG  ulPlainTextLen,
							unsigned char *pucCipherText, ULONG &ulCipherTextLen)
{
	ULONG ulRes     = !CKR_OK;
	ULONG ulPadSize =  8;  //для DES 64 бита
	ULONG ulOffset  = 0;

	//-------------------------------------
	//открываем сессию
	CK_SESSION_HANDLE hSession = 0;          
	ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_OpenSession ошибка" + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//логинимся
	ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)strlen(pszUserPIN));
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//создаём ключ
	////CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
	////CK_KEY_TYPE     ulKeyType   = CKK_DES3;
	////CK_BBOOL        bTrueValue  = TRUE;
	////CK_BBOOL        bFalseValue = FALSE;

	////CK_ATTRIBUTE pTemplate[] = {
	////	{CKA_CLASS,    &ulClass,     sizeof(ulClass)    },
	////	{CKA_KEY_TYPE, &ulKeyType,   sizeof(ulKeyType)  },
	////	{CKA_ENCRYPT,  &bTrueValue,  sizeof(bTrueValue) },
	////	{CKA_TOKEN,    &bFalseValue, sizeof(bFalseValue)},
	////	{CKA_VALUE,    pucKey,       ulKeyLen           }
	////};
	CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
	CK_KEY_TYPE     ulKeyType   = CKK_DES3;
	CK_BBOOL        bTrueValue  = TRUE;
	CK_BBOOL        bFalseValue = FALSE;

	CK_ATTRIBUTE pTemplate[] = {
		{CKA_CLASS,    &ulClass,     sizeof(ulClass)    },
		{CKA_KEY_TYPE, &ulKeyType,   sizeof(ulKeyType)  },
		{CKA_ENCRYPT,  &bTrueValue,  sizeof(bTrueValue) },
		{CKA_TOKEN,    &bTrueValue,  sizeof(bTrueValue)},
		{CKA_VALUE,    pucKey,       ulKeyLen           }
	};


	CK_OBJECT_HANDLE hKey = (CK_OBJECT_HANDLE)0;
	ulRes = _m_pFunctionList->C_CreateObject(hSession, pTemplate, sizeof(pTemplate) / sizeof(CK_ATTRIBUTE), &hKey);
	/*DEBUG*/XASSERT_MSG_RET(CKR_OK == ulRes, _sEtokenErrorString(ulRes).c_str(), FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_CreateObject ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}              

	//-------------------------------------
	//шифруем
	CK_MECHANISM Mech;	ZERO_DATA(Mech);
	Mech.mechanism      = CKM_DES3_CBC_PAD;  
	Mech.pParameter     = pucIv;
	Mech.ulParameterLen = ulIvLen;

	ulRes = _m_pFunctionList->C_EncryptInit(hSession, &Mech, hKey);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK ) {
	//	/*LOG*/_m_tlLog.bWrite("C_EncryptInit ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	if (ulPlainTextLen + ulPadSize - ulPlainTextLen % ulPadSize > /***/ulCipherTextLen) {	//?????????????
		return FALSE;
	}

	//продолжаем  многоступенчатое шифрование
	for (ulOffset = 0; ulOffset < ulPlainTextLen; ulOffset += ulPadSize) {
		ulRes = _m_pFunctionList->C_EncryptUpdate(hSession, pucPlainText + ulOffset, ulPadSize, pucCipherText + ulOffset, &ulCipherTextLen);
		/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
		//if (ulRes != CKR_OK) {
		//	/*LOG*/_m_tlLog.bWrite("C_EncryptUpdate ошибка ---> " + _sEtokenErrorString(ulRes));
		//	return FALSE;
		//}
	}

	//заканчиваем многоступенчатое шифрование
	ulRes = _m_pFunctionList->C_EncryptFinal(hSession, pucCipherText + ulOffset, &ulCipherTextLen);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_EncryptFinal ошибка ---> " + _sEtokenErrorString(ulRes));
	//}
	/***/ulCipherTextLen = ulOffset;	/***/

	//-------------------------------------
	//удаляем ключ
	//--	if (key != (CK_OBJECT_HANDLE) 0) {}
	ulRes = _m_pFunctionList->C_DestroyObject(hSession, hKey);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_DestroyObject ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//делогинимся
	ulRes = _m_pFunctionList->C_Logout(hSession);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//закрываем сессию
	ulRes = _m_pFunctionList->C_CloseSession(hSession);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//Log.vOpen();

	return TRUE;	
}
//--------------------------------------------------------------------------
//DONE: sDecryptTextDES
BOOL CXeToken::bDecryptDES3(unsigned long  ulSlotId,
							   char *pszUserPIN,    
							   unsigned char *pucKey,        ULONG  ulKeyLen,
							   unsigned char *pucIv,         ULONG  ulIvLen,
							   unsigned char *pucCipherText, ULONG  ulCipherTextLen,							   
							   unsigned char *pucPlainText,  ULONG &ulPlainTextLen) 
{
	ULONG ulRes = !CKR_OK;

	//-------------------------------------
	//открываем сессию
	CK_SESSION_HANDLE hSession;
	ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_OpenSession ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE; 
	//}

	//-------------------------------------
	//логинимся
	ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)strlen(pszUserPIN));
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_Login ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//создаём ключ
	CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
	CK_KEY_TYPE     ulKeyType   = CKK_DES3;
	CK_BBOOL        bTrue       = TRUE;
	CK_BBOOL        bFalse      = FALSE;
	CK_ATTRIBUTE    pTemplate[] = {
		{CKA_CLASS,    &ulClass,   sizeof(ulClass)  },
		{CKA_KEY_TYPE, &ulKeyType, sizeof(ulKeyType)},
		{CKA_DECRYPT,  &bTrue,     sizeof(bTrue)    },
		{CKA_TOKEN,    &bFalse,    sizeof(bFalse)   },
		{CKA_VALUE,    pucKey,     ulKeyLen         }
	};

	CK_OBJECT_HANDLE  hKey = (CK_OBJECT_HANDLE)0;
	ulRes = _m_pFunctionList->C_CreateObject(hSession, pTemplate, (sizeof(pTemplate) / sizeof(CK_ATTRIBUTE)), &hKey);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_CreateObject ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//дешифруем
	CK_MECHANISM Mech;
	Mech.mechanism      = CKM_DES3_CBC_PAD;
	Mech.pParameter     = pucIv;
	Mech.ulParameterLen = ulIvLen;

	ulRes = _m_pFunctionList->C_DecryptInit(hSession, &Mech, hKey);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_DecryptInit ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//дешифруем полностью всю шифрстроку
	ulRes = _m_pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)pucCipherText, (CK_ULONG)ulCipherTextLen, (CK_BYTE_PTR)pucPlainText, &ulPlainTextLen);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_Decrypt ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE;
	//}

	//-------------------------------------
	//удаляем ключ
	//--	if (key != (CK_OBJECT_HANDLE) 0) {}
	ulRes = _m_pFunctionList->C_DestroyObject(hSession, hKey);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_DestroyObject ошибка ---> " + _sEtokenErrorString(ulRes));
	//}

	//-------------------------------------
	//делогинимся
	ulRes = _m_pFunctionList->C_Logout(hSession);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_Logout ошибка ---> " + _sEtokenErrorString(ulRes));
	//}

	//-------------------------------------
	//закрываем сессию
	ulRes = _m_pFunctionList->C_CloseSession(hSession);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
	//}
	
	return TRUE;
}
//--------------------------------------------------------------------------
//TODO: sEncryptFileDES3
////std::string sEncryptFileDES3() {}
//--------------------------------------------------------------------------
//TODO: sDecryptFileDES3
////std::string sDecryptFileDES3() {}
//--------------------------------------------------------------------------
//TODO: bGenerateRSAKeyPair
BOOL CXeToken::bGenerateRSAKeyPair(unsigned long  ulSlotId,
						          char          *pszUserPIN/*CK_SESSION_HANDLE hSession*/, 
								  /*CK_UTF8CHAR*/char *pszPublicKeyLabel, 
								  char *pszPrivateKeyLabel, 
								  CK_ULONG ulModulus,
								  UCHAR         *pucPlainText,  ULONG ulPlainTextLen,
								  UCHAR         *pucCipherText, ULONG &ulCipherTextLen) 
{
	////if (LabelExists(ses,label))
	////{
	////	fprintf (stderr, "Key with label '%s' exists.\n",(char*)label);
	////	exit (1);
	////}


	ULONG ulRes     = !CKR_OK;
    ULONG ulPadSize = 8;  //для DES 64 бита
    ULONG ulOffset  = 0;

    //-------------------------------------
    //открываем сессию
    CK_SESSION_HANDLE hSession = 0;          
    ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0, &hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);
                                                       
    //-------------------------------------
    //логинимся
    ulRes = _m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)strlen(pszUserPIN));
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);



	CK_MECHANISM mechMechanism = 
	{
		CKM_RSA_PKCS_KEY_PAIR_GEN, NULL_PTR, 0 
	};

	/* Template for Public Key */
	CK_BYTE     ucPublicExp[] = {1, 0, 1};
	CK_KEY_TYPE ulKeyType     = CKK_RSA;
	CK_BBOOL    bTrueValue    = TRUE;
	CK_BBOOL    bFalseValue   = FALSE;

	/* A template to generate a private key */
	CK_ATTRIBUTE atrPrivateKeyTemplate[] =
	{
		{CKA_LABEL,         "My private key", sizeof("My private key")},
		{CKA_KEY_TYPE,     &ulKeyType,          sizeof(ulKeyType)         },
		{CKA_SIGN,         &bTrueValue,         sizeof(bTrueValue)        },
		{CKA_DECRYPT,      &bTrueValue,         sizeof(bTrueValue)        },
		{CKA_TOKEN,        &bTrueValue,         sizeof(bTrueValue)        },
		{CKA_PRIVATE,      &bTrueValue,         sizeof(bTrueValue)        },
		{CKA_SENSITIVE,    &bFalseValue,        sizeof(bFalseValue)       },
		{CKA_UNWRAP,       &bTrueValue,         sizeof(bTrueValue)        },
		{CKA_EXTRACTABLE,  &bTrueValue,         sizeof(bTrueValue)        }
	};

	CK_ATTRIBUTE atrPublicKeyTemplate[] =
	{
		{CKA_LABEL,            "My public key", sizeof("My public key")},
		{CKA_KEY_TYPE,        &ulKeyType,         sizeof(ulKeyType)        },
		{CKA_VERIFY,          &bTrueValue,        sizeof(bTrueValue)       },
		{CKA_ENCRYPT,         &bTrueValue,        sizeof(bTrueValue)       },
		{CKA_WRAP,            &bTrueValue,        sizeof(bTrueValue)       },
		{CKA_TOKEN,           &bTrueValue,        sizeof(bTrueValue)       },
		{CKA_MODULUS_BITS,    &ulModulus,         sizeof(ulModulus)        },
		{CKA_PUBLIC_EXPONENT, &ucPublicExp,       sizeof(ucPublicExp)      }
	};




	CK_OBJECT_HANDLE hPrivateKey = 0;
	CK_OBJECT_HANDLE hPublicKey  = 0;

	ulRes = _m_pFunctionList->C_GenerateKeyPair(hSession, &mechMechanism, atrPublicKeyTemplate, 8, atrPrivateKeyTemplate, 9, &hPublicKey, &hPrivateKey);
	/*DEBUG*/XASSERT_MSG_RET(CKR_OK == ulRes, _sEtokenErrorString(ulRes).c_str(), FALSE);




























    //-------------------------------------
    //делогинимся
    ulRes = _m_pFunctionList->C_Logout(hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);

	//-------------------------------------
    //закрываем сессию
    ulRes = _m_pFunctionList->C_CloseSession(hSession);
	/*DEBUG*/XASSERT_MSG_RET(ulRes == CKR_OK, _sEtokenErrorString(ulRes).c_str(), FALSE);

	return TRUE;	
}
//---------------------------------------------------------------------------


/**********************************************************************
*   Остальные
*
***********************************************************************/

//---------------------------------------------------------------------------
//DONE: _sEtokenErrorString (SDK 4.53)
std::string CXeToken::_sEtokenErrorString(DWORD ulRes) {
	switch (ulRes) {
		case CKR_OK: 	                           return "CKR_OK";
		case CKR_CANCEL:                           return "CKR_CANCEL";
		case CKR_HOST_MEMORY:                      return "CKR_HOST_MEMORY";
		case CKR_SLOT_ID_INVALID:                  return "CKR_SLOT_ID_INVALID";
		case CKR_GENERAL_ERROR:                    return "CKR_GENERAL_ERROR";
		case CKR_FUNCTION_FAILED:                  return "CKR_FUNCTION_FAILED";
		case CKR_ARGUMENTS_BAD:                    return "CKR_ARGUMENTS_BAD";
		case CKR_NO_EVENT:                         return "CKR_NO_EVENT";
		case CKR_NEED_TO_CREATE_THREADS:           return "CKR_NEED_TO_CREATE_THREADS";
		case CKR_CANT_LOCK:                        return "CKR_CANT_LOCK";
		case CKR_ATTRIBUTE_READ_ONLY:              return "CKR_ATTRIBUTE_READ_ONLY";
		case CKR_ATTRIBUTE_SENSITIVE:              return "CKR_ATTRIBUTE_SENSITIVE";
		case CKR_ATTRIBUTE_TYPE_INVALID:           return "CKR_ATTRIBUTE_TYPE_INVALID";
		case CKR_ATTRIBUTE_VALUE_INVALID:          return "CKR_ATTRIBUTE_VALUE_INVALID";
		case CKR_DATA_INVALID:                     return "CKR_DATA_INVALID";
		case CKR_DATA_LEN_RANGE:                   return "CKR_DATA_LEN_RANGE";						
		case CKR_DEVICE_ERROR:                     return "CKR_DEVICE_ERROR";						
		case CKR_DEVICE_MEMORY:                    return "CKR_DEVICE_MEMORY";						
		case CKR_DEVICE_REMOVED:                   return "CKR_DEVICE_REMOVED";						
		case CKR_ENCRYPTED_DATA_INVALID:           return "CKR_ENCRYPTED_DATA_INVALID";				
		case CKR_ENCRYPTED_DATA_LEN_RANGE:         return "CKR_ENCRYPTED_DATA_LEN_RANGE";			
		case CKR_FUNCTION_CANCELED:                return "CKR_FUNCTION_CANCELED";					
		case CKR_FUNCTION_NOT_PARALLEL:            return "CKR_FUNCTION_NOT_PARALLEL";				
		case CKR_FUNCTION_NOT_SUPPORTED:           return "CKR_FUNCTION_NOT_SUPPORTED";				
		case CKR_KEY_HANDLE_INVALID:               return "CKR_KEY_HANDLE_INVALID";					
		case CKR_KEY_SIZE_RANGE:                   return "CKR_KEY_SIZE_RANGE";						
		case CKR_KEY_TYPE_INCONSISTENT:            return "CKR_KEY_TYPE_INCONSISTENT";				
		case CKR_KEY_NOT_NEEDED:                   return "CKR_KEY_NOT_NEEDED";						
		case CKR_KEY_CHANGED:                      return "CKR_KEY_CHANGED";						
		case CKR_KEY_NEEDED:                       return "CKR_KEY_NEEDED";							
		case CKR_KEY_INDIGESTIBLE:                 return "CKR_KEY_INDIGESTIBLE";
		case CKR_KEY_FUNCTION_NOT_PERMITTED:       return "CKR_KEY_FUNCTION_NOT_PERMITTED";			
		case CKR_KEY_NOT_WRAPPABLE:                return "CKR_KEY_NOT_WRAPPABLE";					
		case CKR_KEY_UNEXTRACTABLE:                return "CKR_KEY_UNEXTRACTABLE";					
		case CKR_MECHANISM_INVALID:                return "CKR_MECHANISM_INVALID";					
		case CKR_MECHANISM_PARAM_INVALID:          return "CKR_MECHANISM_PARAM_INVALID";			
		case CKR_OBJECT_HANDLE_INVALID:            return "CKR_OBJECT_HANDLE_INVALID";				
		case CKR_OPERATION_ACTIVE:                 return "CKR_OPERATION_ACTIVE";					
		case CKR_OPERATION_NOT_INITIALIZED:        return "CKR_OPERATION_NOT_INITIALIZED";			
		case CKR_PIN_INCORRECT:                    return "CKR_PIN_INCORRECT";						
		case CKR_PIN_INVALID:                      return "CKR_PIN_INVALID";						
		case CKR_PIN_LEN_RANGE:                    return "CKR_PIN_LEN_RANGE";						
		case CKR_PIN_EXPIRED:                      return "CKR_PIN_EXPIRED";						
		case CKR_PIN_LOCKED:                       return "CKR_PIN_LOCKED";							
		case CKR_SESSION_CLOSED:                   return "CKR_SESSION_CLOSED";						
		case CKR_SESSION_COUNT:                    return "CKR_SESSION_COUNT";						
		case CKR_SESSION_HANDLE_INVALID:           return "CKR_SESSION_HANDLE_INVALID";
		case CKR_SESSION_PARALLEL_NOT_SUPPORTED:   return "CKR_SESSION_PARALLEL_NOT_SUPPORTED";		
		case CKR_SESSION_READ_ONLY:                return "CKR_SESSION_READ_ONLY";					
		case CKR_SESSION_EXISTS:                   return "CKR_SESSION_EXISTS";						
		case CKR_SESSION_READ_ONLY_EXISTS:         return "CKR_SESSION_READ_ONLY_EXISTS";			
		case CKR_SESSION_READ_WRITE_SO_EXISTS:     return "CKR_SESSION_READ_WRITE_SO_EXISTS";		
		case CKR_SIGNATURE_INVALID:                return "CKR_SIGNATURE_INVALID";					
		case CKR_SIGNATURE_LEN_RANGE:              return "CKR_SIGNATURE_LEN_RANGE";				
		case CKR_TEMPLATE_INCOMPLETE:              return "CKR_TEMPLATE_INCOMPLETE";				
		case CKR_TEMPLATE_INCONSISTENT:            return "CKR_TEMPLATE_INCONSISTENT";				
		case CKR_TOKEN_NOT_PRESENT:                return "CKR_TOKEN_NOT_PRESENT";					
		case CKR_TOKEN_NOT_RECOGNIZED:             return "CKR_TOKEN_NOT_RECOGNIZED";				
		case CKR_TOKEN_WRITE_PROTECTED:            return "CKR_TOKEN_WRITE_PROTECTED";				
		case CKR_UNWRAPPING_KEY_HANDLE_INVALID:    return "CKR_UNWRAPPING_KEY_HANDLE_INVALID";		
		case CKR_UNWRAPPING_KEY_SIZE_RANGE:        return "CKR_UNWRAPPING_KEY_SIZE_RANGE";			
		case CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT: return "CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT";	
		case CKR_USER_ALREADY_LOGGED_IN:           return "CKR_USER_ALREADY_LOGGED_IN";	        	
		case CKR_USER_NOT_LOGGED_IN:               return "CKR_USER_NOT_LOGGED_IN";	            	
		case CKR_USER_PIN_NOT_INITIALIZED:         return "CKR_USER_PIN_NOT_INITIALIZED";	        
		case CKR_USER_TYPE_INVALID:                return "CKR_USER_TYPE_INVALID";                 	
		case CKR_USER_ANOTHER_ALREADY_LOGGED_IN:   return "CKR_USER_ANOTHER_ALREADY_LOGGED_IN";    	
		case CKR_USER_TOO_MANY_TYPES:              return "CKR_USER_TOO_MANY_TYPES";			    
		case CKR_WRAPPED_KEY_INVALID:              return "CKR_WRAPPED_KEY_INVALID";				
		case CKR_WRAPPED_KEY_LEN_RANGE:            return "CKR_WRAPPED_KEY_LEN_RANGE";				
		case CKR_WRAPPING_KEY_HANDLE_INVALID:      return "CKR_WRAPPING_KEY_HANDLE_INVALID";		
		case CKR_WRAPPING_KEY_SIZE_RANGE:          return "CKR_WRAPPING_KEY_SIZE_RANGE";			
		case CKR_WRAPPING_KEY_TYPE_INCONSISTENT:   return "CKR_WRAPPING_KEY_TYPE_INCONSISTENT";		
		case CKR_RANDOM_SEED_NOT_SUPPORTED:        return "CKR_RANDOM_SEED_NOT_SUPPORTED";			
		case CKR_RANDOM_NO_RNG:                    return "CKR_RANDOM_NO_RNG";						
		case CKR_DOMAIN_PARAMS_INVALID:            return "CKR_DOMAIN_PARAMS_INVALID";					/*new SDK 4.53*/
		case CKR_BUFFER_TOO_SMALL:                 return "CKR_BUFFER_TOO_SMALL";					
		case CKR_SAVED_STATE_INVALID:              return "CKR_SAVED_STATE_INVALID";				
		case CKR_INFORMATION_SENSITIVE:            return "CKR_INFORMATION_SENSITIVE";				
		case CKR_STATE_UNSAVEABLE:                 return "CKR_STATE_UNSAVEABLE";					
		case CKR_CRYPTOKI_NOT_INITIALIZED:         return "CKR_CRYPTOKI_NOT_INITIALIZED";			
		case CKR_CRYPTOKI_ALREADY_INITIALIZED:     return "CKR_CRYPTOKI_ALREADY_INITIALIZED";		
		case CKR_MUTEX_BAD:                        return "CKR_MUTEX_BAD";							
		case CKR_MUTEX_NOT_LOCKED:                 return "CKR_MUTEX_NOT_LOCKED";					
		case CKR_FUNCTION_REJECTED:                return "CKR_FUNCTION_REJECTED";						/*new SDK 4.53*/
		case CKR_VENDOR_DEFINED:                   return "CKR_VENDOR_DEFINED";						
		case CKR_SAPI_OBJECT_DOES_NOT_EXIST:       return "CKR_SAPI_OBJECT_DOES_NOT_EXIST";				/*new SDK 4.53*/
		case CKR_SAPI_OBJECT_ALREADY_EXISTS:       return "CKR_SAPI_OBJECT_ALREADY_EXISTS";				/*new SDK 4.53*/
		case CKR_SAPI_NOT_SUPPORTED_BY_TOKEN:      return "CKR_SAPI_NOT_SUPPORTED_BY_TOKEN";			/*new SDK 4.53*/
		case CKR_SAPI_PIN_QUALITY:                 return "CKR_SAPI_PIN_QUALITY";						/*new SDK 4.53*/
		case CKR_SAPI_PIN_DEFAULT:                 return "CKR_SAPI_PIN_DEFAULT";						/*new SDK 4.53*/
		case CKR_SAPI_PIN_EXPIRATION:              return "CKR_SAPI_PIN_EXPIRATION";					/*new SDK 4.53*/
		case CKR_SAPI_PIN_CHANGE_NOT_ALLOWED:      return "CKR_SAPI_PIN_CHANGE_NOT_ALLOWED";			/*new SDK 4.53*/
		case CKR_SAPI_CANCELLED: 				   return "CKR_SAPI_CANCELLED";							/*new SDK 4.53*/
		case CKR_NEW_PIN_MODE:      			   return "CKR_NEW_PIN_MODE";							/*new SDK 4.53*/
		case CKR_NEXT_OTP:          	           return "CKR_NEXT_OTP";								/*new SDK 4.53*/

		default:								   return "UNKNOWN_ERROR";						    
	}
}
//--------------------------------------------------------------------------


/**********************************************************************
*	Генерация случайных чисел
*
***********************************************************************/

//--------------------------------------------------------------------------
//TODO: bGenRandomBytes
BOOL CXeToken::bGenRandomBytes(unsigned long  ulSlotId, unsigned char *pucBuff, ULONG ulBuffSize) {
	//-------------------------------------
	//CHECK

	//-------------------------------------
	//JOB	
	ULONG ulRes = !CKR_OK;

	//-------------------------------------
	//открываем сессию
	CK_SESSION_HANDLE hSession;
	ulRes = _m_pFunctionList->C_OpenSession(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0, &hSession);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_OpenSession ошибка ---> " + _sEtokenErrorString(ulRes));
	//	return FALSE; 
	//}

	//-------------------------------------
	//генерим рэндомные байты
	ulRes = _m_pFunctionList->C_GenerateRandom(hSession, pucBuff, ulBuffSize);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (CKR_OK != ulRes) {
	//	return FALSE;
	//}

	//-------------------------------------
	//закрываем сессию
	ulRes = _m_pFunctionList->C_CloseSession(hSession);
	/*DEBUG*/XASSERT_RET(CKR_OK == ulRes, FALSE);
	//if (ulRes != CKR_OK) {
	//	/*LOG*/_m_tlLog.bWrite("C_CloseSession ошибка ---> " + _sEtokenErrorString(ulRes));
	//}

	return TRUE;
}
//--------------------------------------------------------------------------
//generate random data
/*
11.15	Random number generation functions
Cryptoki provides the following functions for generating random numbers:
•	C_SeedRandom
CK_DEFINE_FUNCTION(CK_RV, C_SeedRandom)(
CK_SESSION_HANDLE hSession,
CK_BYTE_PTR pSeed,
CK_ULONG ulSeedLen
);
C_SeedRandom mixes additional seed material into the token’s random number generator. hSession is the session’s handle; pSeed points to the seed material; and ulSeedLen is the length in bytes of the seed material.
Return values: CKR_ARGUMENTS_BAD, CKR_CRYPTOKI_NOT_INITIALIZED, CKR_DEVICE_ERROR, CKR_DEVICE_MEMORY, CKR_DEVICE_REMOVED, CKR_FUNCTION_CANCELED, CKR_FUNCTION_FAILED, CKR_GENERAL_ERROR, CKR_HOST_MEMORY, CKR_OK, CKR_OPERATION_ACTIVE, CKR_RANDOM_SEED_NOT_SUPPORTED, CKR_RANDOM_NO_RNG, CKR_SESSION_CLOSED, CKR_SESSION_HANDLE_INVALID, CKR_USER_NOT_LOGGED_IN.
Example: see C_GenerateRandom.
•	C_GenerateRandom
CK_DEFINE_FUNCTION(CK_RV, C_GenerateRandom)(
CK_SESSION_HANDLE hSession,
CK_BYTE_PTR pRandomData,
CK_ULONG ulRandomLen
);
C_GenerateRandom generates random or pseudo-random data. hSession is the session’s handle; pRandomData points to the location that receives the random data; and ulRandomLen is the length in bytes of the random or pseudo-random data to be generated.
Return values: CKR_ARGUMENTS_BAD, CKR_CRYPTOKI_NOT_INITIALIZED, CKR_DEVICE_ERROR, CKR_DEVICE_MEMORY, CKR_DEVICE_REMOVED, CKR_FUNCTION_CANCELED, CKR_FUNCTION_FAILED, CKR_GENERAL_ERROR, CKR_HOST_MEMORY, CKR_OK, CKR_OPERATION_ACTIVE, CKR_RANDOM_NO_RNG, CKR_SESSION_CLOSED, CKR_SESSION_HANDLE_INVALID, CKR_USER_NOT_LOGGED_IN.
Example:
CK_SESSION_HANDLE hSession;
CK_BYTE seed[] = {...};
CK_BYTE randomData[] = {...};
CK_RV rv;

.
.
.
rv = C_SeedRandom(hSession, seed, sizeof(seed));
if (rv != CKR_OK) {
.
.
.
}
rv = C_GenerateRandom(hSession, randomData, sizeof(randomData));
if (rv == CKR_OK) {
.
.
.
}

*/
//--------------------------------------------------------------------------