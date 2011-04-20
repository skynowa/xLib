/**********************************************************************
*   CYug_eToken.cpp  (RTE 4.53)
*
***********************************************************************/


#define WIN32_LEAN_AND_MEAN		//Exclude rarely-used content from Windows headers.

#include "CYug_eToken.h"
#include "CXLog.h"
#include "CXString.h"

CXLog Log("___CYug_eToken.log", 10);
//---------------------------------------------------------------------------
//DONE: объявление SAPI's функции
typedef CK_RV (*t_SAPI_GetTokenInfo)(CK_SLOT_ID, CK_ATTRIBUTE_PTR, CK_ULONG);
////t_SAPI_GetTokenInfo f_SAPI_GetTokenInfo = NULL; /*DIF: SDK 3.60*/
t_SAPI_GetTokenInfo _SAPI_GetTokenInfo = NULL;		/*DIF: SDK 4.53*/
//---------------------------------------------------------------------------
//DONE: CYug_eToken
CYug_eToken::CYug_eToken() {
    m_pFunctionList = NULL;
	m_bWasInit      = false;
}
//---------------------------------------------------------------------------
//DONE: ~CYug_eToken
CYug_eToken::~CYug_eToken() {

}
//---------------------------------------------------------------------------
//DONE: bInitialize (Инициализируем DLL-ки (eTPKCS11.dll, eTSAPI.dll))
bool CYug_eToken::bInitialize() {
    if (!bLoadPKCS11() || !bLoadETSAPI()) {
        m_bWasInit = false;
		return false;
    } else {
        m_bWasInit = true;  
		return true;
    }
}
//---------------------------------------------------------------------------
//DONE: bFinalize (Финализируем DLL-ки (eTPKCS11.dll, eTSAPI.dll))
bool CYug_eToken::bFinalize() {  //закрыть PKCS #11 библиотеку
    unsigned long int ulRV = CKR_OK;
	
	if (!m_bWasInit) {return false;}     

	ulRV = m_pFunctionList->C_Finalize(0);
    if (ulRV == CKR_OK) {
        m_bWasInit = false;
        return true;
    } else {
        MessageBox(0, "C_Finalize ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return false;
    }
}
//---------------------------------------------------------------------------
//DONE: bLoadPKCS11 (Подгружаем eTPKCS11.dll и инициализируем PKCS#11)
bool CYug_eToken::bLoadPKCS11() {
    unsigned long int ulRV = CKR_OK;
	
	HINSTANCE hLib = LoadLibrary(ETPKCS11_PATH);
    if (!hLib) {
        MessageBox(0, "Невозможно подгрузить etpkcs11.dll", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return false;
    }

    CK_C_GetFunctionList f_C_GetFunctionList = NULL;
    (FARPROC&)f_C_GetFunctionList = GetProcAddress(hLib, "C_GetFunctionList");
    if (!f_C_GetFunctionList) {
        MessageBox(0, "C_GetFunctionList не найдена", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return false;
    }

    ulRV = f_C_GetFunctionList(&m_pFunctionList);
	if (ulRV != CKR_OK) {
		MSG_WARNING_("C_GetFunctionList ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }
	
    ulRV = m_pFunctionList->C_Initialize(0);
	if (ulRV != CKR_OK) {
		MSG_WARNING_("C_Initialize ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
//DONE: bLoadETSAPI (Подгружаем eTSAPI.dll и приобретаем его необходимые методы)
bool CYug_eToken::bLoadETSAPI() {
    HINSTANCE hLib = LoadLibrary(ETSAPI_PATH);
    if (!hLib) {
        MessageBox(0, "Невозможно подгрузить etsapi.dll", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return false;
    }

    (FARPROC&)/*f*/_SAPI_GetTokenInfo = GetProcAddress(hLib, "SAPI_GetTokenInfo");
    if (!/*f*/_SAPI_GetTokenInfo) {
        MessageBox(0, "SAPI_GetTokenInfo не найдена", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------


/**********************************************************************
*   SLOT AND TOKEN MANAGEMENT FUNCTIONS
*
***********************************************************************/

//---------------------------------------------------------------------------
//TODO: ulGetSlotList()
unsigned long int *CYug_eToken::ulGetSlotList(/*unsigned long int &ulSlotCount*/) {
    unsigned long int ciSLOTS_NOT_PRESENT = - 1;

    ///std::string sSlots = "";
	if (!m_bWasInit) {return NULL/*(unsigned long int *)ciSLOTS_NOT_PRESENT*/;}	//????????????

	unsigned long int ulRV    = CKR_OK;
    ////////////unsigned long int uiAllSlots;  // = (unsigned int *)ciSLOTS_NOT_PRESENT;	//?????????????

    //получаем список слотов
    CK_SLOT_ID_PTR    pSlots      = NULL;
    unsigned long int ulSlotCount = 0;

    ulRV = m_pFunctionList->C_GetSlotList(TRUE, NULL, &ulSlotCount);
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_GetSlotList ошибка --->" + sEtokenErrorString(ulRV));
        return NULL/*(unsigned long int *)ciSLOTS_NOT_PRESENT*/;
    }
    if (ulSlotCount < 1) {
        MessageBox(0, "Нет вставленного eToken", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
        return NULL/*(unsigned long int *)ciSLOTS_NOT_PRESENT*/;
    }
    pSlots = new CK_SLOT_ID[ulSlotCount];
    ulRV = m_pFunctionList->C_GetSlotList(TRUE, pSlots, &ulSlotCount);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_GetSlotList ошибка ---> " + sEtokenErrorString(ulRV));
        return NULL/*(unsigned long int *)ciSLOTS_NOT_PRESENT*/;
    }

    ////ulSlotCount = nSlotCount;
    return pSlots;

//--    delete []pSlots;    pSlots = NULL;
//--    return uiAllSlots;
}
//---------------------------------------------------------------------------
//TODO: iInsertedTokens (Получаем количество вставленных токенов)
unsigned long int CYug_eToken::ulInsertedTokens() {
    if (!m_bWasInit) {return 0;}

    unsigned long int ulRV        = CKR_OK;
    unsigned long int ulSlotCount = 0;

    ulRV = m_pFunctionList->C_GetSlotList(true, NULL, &ulSlotCount);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_GetSlotList ошибка ---> " + sEtokenErrorString(ulRV));
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
////CK_FUNCTION_LIST_PTR   m_pFunctionList;
////CK_C_GetFunctionList   pGFL  = 0;
////CK_SESSION_HANDLE      session;
////CK_SLOT_ID*            slots;
////unsigned long          slot_count;
////
////unsigned long CYug_eToken::dwSelectSlot(char* readerName) {
////    unsigned long int ulRV = CKR_OK;
////
////	//Get all the occupied slots.
////	unsigned long slot_index = 0;
////
////    //Get all the occupied slots
////	ulRV = m_pFunctionList->C_GetSlotList(true, NULL, &slot_count);
////	if (ulRV == CKR_OK) {
////		if (slot_count < 1)	{
////			//--leave ("No eToken is available.\n");
////		}
////
////		slots = new CK_SLOT_ID [slot_count];
////		ulRV = m_pFunctionList->C_GetSlotList (true, slots, &slot_count);
////		if (ulRV != CKR_OK) {
////			//--leave ("C_GetSlotList failed...\n");
////		}
////	} else {
////		//--leave ("C_GetSlotList failed...\n");
////	}
////  
////	//Get the selected slot information.
////	bool bFound = false;
////	std::transform(readerName, readerName + strlen(readerName), readerName, tolower);
////	for (slot_index; slot_index < slot_count; slot_index++)	{
////		CK_SLOT_INFO slot_info;
////		
////		ulRV = m_pFunctionList->C_GetSlotInfo (slots[slot_index], &slot_info);
////		if (ulRV != CKR_OK)	{
////			//--leave ("C_GetSlotInfo failed.\n");
////		}
////	   	std::transform(slot_info.slotDescription,slot_info.slotDescription + sizeof(slot_info.slotDescription),slot_info.slotDescription,tolower);
////	    if (memcmp((void*)slot_info.slotDescription, readerName, min(strlen(readerName), sizeof(slot_info.slotDescription))) == 0) {    
////			bFound = true;
////			break;  
////	    }
////	}
////	return bFound? slot_index : 0; //If not found, work with slot 0.
////}
//---------------------------------------------------------------------------
//TODO: ulGetSlotInfo
unsigned long CYug_eToken::ulGetSlotType(unsigned long int ulSlotId) {
    unsigned long int   ulRV               = CKR_OK;
    
    const unsigned long int culKnownInfo       = 0;
    const unsigned long int culTokenNotPresent = 1;
    const unsigned long int culTokenPresent    = 3;
    const unsigned long int culRemovableDevice = 2;
    const unsigned long int culHardwareSlot    = 4;
	
	//-------------------------------------
	//если токен был вынят - выход
    if (!m_bWasInit) {return culKnownInfo;}

	CK_SLOT_INFO siSI;
	ulRV = m_pFunctionList->C_GetSlotInfo(ulSlotId, &siSI);                 //////////////////////???????
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_GetSlotInfo ошибка ---> " + sEtokenErrorString(ulRV));
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
unsigned long int CYug_eToken::ulWaitForSlotEvent() {
    if (!m_bWasInit) {return TOKEN_NON_PRESENT;}

    unsigned long int ulRV     = CKR_OK;
	unsigned long int ulSlotId = TOKEN_NON_PRESENT;

    ulRV = m_pFunctionList->C_WaitForSlotEvent(0, &ulSlotId, 0);
	if (ulRV != CKR_OK) {
        return TOKEN_NON_PRESENT;
    } else {
        return ulSlotId;
    }
}
//---------------------------------------------------------------------------
//DONE: sGetLibraryInfo (Информация о PKCS#11 библиотеке)
bool CYug_eToken::bGetLibraryInfo(TStringMap &smLibraryInfo) {
    if (m_bWasInit == false) {
		return false;
	}

    unsigned long int   ulRV         = CKR_OK;
	std::string         sLibraryInfo = "";
    
	CK_INFO info;	memset(&info, 0, sizeof(info));	
	ulRV = m_pFunctionList->C_GetInfo(&info);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_GetInfo ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

	smLibraryInfo["CRYPTOKI_VERSION_MAJOR"] = sTypeToStr((unsigned int)info.cryptokiVersion.major);                            //unsigned char ???
	smLibraryInfo["CRYPTOKI_VERSION_MINOR"] = sTypeToStr((unsigned int)info.cryptokiVersion.minor);                            //unsigned char ???
	smLibraryInfo["MANUFACTURER_ID"]        = sTrimSpace(sTypeToStr((unsigned char *)info.manufacturerID).substr(0, 32));      //%.32s
	smLibraryInfo["LIBRARY_DESCRIPTION"]    = sTrimSpace(sTypeToStr((unsigned char *)info.libraryDescription).substr(0, 32));  //%.32s
	smLibraryInfo["LIBRARY_VERSION_MAJOR"]  = sTypeToStr((unsigned int)info.libraryVersion.major);                             //unsigned char ???
	smLibraryInfo["LIBRARY_VERSION_MINOR"]  = sTypeToStr((unsigned int)info.libraryVersion.minor);                             //unsigned char ???

	return true;
}
//---------------------------------------------------------------------------


/**********************************************************************
*	Объекты
*
***********************************************************************/

//--------------------------------------------------------------------------
//DONE: bIsDataObjectExists
bool CYug_eToken::bIsDataObjectExists(unsigned long ulSlotId, char *pszUserPIN, char *pszApplication/*ID*/, char *pszLabel, char *pszValue) {
   	unsigned long int ulRV         = CKR_OK;

    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_OpenSession ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

    //-------------------------------------
    //логинимся
    ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

	//-------------------------------------
    //ищем объект
    CK_OBJECT_HANDLE  hObject    = NULL;
    unsigned long int ulFoundObj = 0;
    
    unsigned long int ulClass    = CKO_DATA;
    bool              bTrue      = CK_TRUE;

    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)       },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)         },
        {CKA_APPLICATION, pszApplication, strlen(pszApplication)}
    };

	////ULONG	//unsigned long int
	////size_t	//unsigned int

    //-------------------------------------
    //инициализируем поиск объектов
	ulRV = m_pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjectsInit ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
	}

    //-------------------------------------
	//Find matching objects. There should be only a single match as there is only one on the eToken.
	ulRV = m_pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjects ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
	}

    //-------------------------------------
    //Clean up the search.
    ulRV = m_pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjectsFinal ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = m_pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = m_pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (ulFoundObj < 1) {
		return false;
	}

    return true;
}
//--------------------------------------------------------------------------
//DONE: sGetDataObject
std::string CYug_eToken::sGetDataObject(unsigned long int ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/) {
    unsigned long int  ulRV = CKR_OK;
    std::string        sRes = "";
 
    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_OpenSession ошибка ---> " + sEtokenErrorString(ulRV));
        return NULL;
    }

    //-------------------------------------
    //логинимся
    ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
        return NULL;
    }

	//-------------------------------------
    //ищем объект
    unsigned long int ulFoundObj = 0;

    CK_OBJECT_HANDLE  hObject    = NULL;
    unsigned long int ulClass    = CKO_DATA;
    bool              bTrue      = CK_TRUE;

    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)      },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)        },
        {CKA_APPLICATION, pszObjectName,  strlen(pszObjectName)}
    };

    //-------------------------------------
    //инициализируем поиск объектов
	ulRV = m_pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjectsInit ошибка ---> " + sEtokenErrorString(ulRV));
        return NULL;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRV = m_pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjects ошибка ---> " + sEtokenErrorString(ulRV));
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
        ulRV = m_pFunctionList->C_GetAttributeValue(hSession, hObject, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
        if (ulRV != CKR_OK) {
            MSG_WARNING_("C_GetAttributeValue ошибка ---> " + sEtokenErrorString(ulRV));
            goto lDone;
        }

        unsigned long int ulApplicationLen = pDataTamplate[0].ulValueLen;
        char             *pszApplication   = new char[ulApplicationLen];
        pDataTamplate[0].pValue = pszApplication;

        unsigned long int  ulLabelLen	   = pDataTamplate[1].ulValueLen;
        char              *pszLabel        = new char[ulLabelLen];
        pDataTamplate[1].pValue = pszLabel;

        unsigned long int  ulValueLen      = pDataTamplate[2].ulValueLen;
        char              *pszValue	       = new char[ulValueLen];
        pDataTamplate[2].pValue = pszValue;


        //-------------------------------------
        //получаем данные   //если CKA_LABEL == 3_Test_Login (выводит лишний символ)
        ulRV = m_pFunctionList->C_GetAttributeValue(hSession, hObject, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
        if (ulRV != CKR_OK) {
            MSG_WARNING_("C_GetAttributeValue ошибка ---> " + sEtokenErrorString(ulRV));

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
    ulRV = m_pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjectsFinal ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = m_pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = m_pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
    }

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: bCreateDataObject
bool CYug_eToken::bCreateDataObject (unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszLabel, char *pszValue) {
    unsigned long int  ulRV = CKR_OK;

	//-------------------------------------
	//открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

	ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_OpenSession ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

	//-------------------------------------
	//логинимся
	ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

    //-------------------------------------
    //создаём объект
    CK_OBJECT_HANDLE  hObject    = NULL;
    unsigned long int ulClass    = CKO_DATA;
    bool              bTrue      = CK_TRUE;
    bool              bPrivate   = CK_TRUE;
    
    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)      },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)        },
        {CKA_PRIVATE,	  &bPrivate,      sizeof(CK_BBOOL)     },
        {CKA_LABEL,       pszLabel,       strlen(pszLabel)     },
        {CKA_APPLICATION, pszObjectName,  strlen(pszObjectName)},
        {CKA_VALUE,       pszValue,       strlen(pszValue)     }
    };

    ulRV = m_pFunctionList->C_CreateObject(hSession, pDataTamplate, sizeof (pDataTamplate) / sizeof (pDataTamplate[0]), &hObject);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_CreateObject ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

    //-------------------------------------
    //делогинимся
    ulRV = m_pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = m_pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
    }

	return true;
}
//--------------------------------------------------------------------------
//DONE: bDeleteDataObject
bool CYug_eToken::bDeleteDataObject(unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/) {
    unsigned long int  ulRV = CKR_OK;
    bool               bRes = false;

    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_OpenSession ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
    }

    //-------------------------------------
    //логинимся
    ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
    }

	//-------------------------------------
    //ищем объект
    unsigned long int ulFoundObj = 0;

    CK_OBJECT_HANDLE  hObject    = NULL;
    unsigned long int ulClass    = CKO_DATA;
    bool              bTrue      = CK_TRUE;

    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)      },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)        },
        {CKA_APPLICATION, pszObjectName,  strlen(pszObjectName)}
    };

    //-------------------------------------
    //инициализируем поиск объектов
	ulRV = m_pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjectsInit ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRV = m_pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjects ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
	}
    //Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (ulFoundObj < 1) {
        bRes = false;
		goto lDone;
	}

    //-------------------------------------
	//найден объект с нужным шаблоном - удаляем его
	ulRV = m_pFunctionList->C_DestroyObject(hSession, hObject);
	if (ulRV != CKR_OK) {
		MSG_WARNING_("C_DestroyObject ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        goto lDone;
	}

    bRes = true;
    goto lDone;

lDone:
    //-------------------------------------
    //Clean up the search.
    ulRV = m_pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjectsFinal ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = m_pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = m_pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
    }

    return bRes;
}
//---------------------------------------------------------------------------
//DONE: bChangeDataObject
bool CYug_eToken::bChangeDataObject(unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/, char *pszNewLabel, char *pszNewValue) {
    unsigned long int ulRV = CKR_OK;
    bool              bRes = false;
 
    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_OpenSession ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
    }

    //-------------------------------------
    //логинимся
    ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
    }

	//-------------------------------------
    //ищем объект
    unsigned long int ulFoundObj = 0;

    CK_OBJECT_HANDLE  hObject    = NULL;
    unsigned long int ulClass    = CKO_DATA;
    bool              bTrue      = CK_TRUE;

    CK_ATTRIBUTE pDataTamplate[] = {
        {CKA_CLASS,       &ulClass,       sizeof(ulClass)      },
        {CKA_TOKEN,       &bTrue,         sizeof(bTrue)        },
        {CKA_APPLICATION, pszObjectName,  strlen(pszObjectName)}
    };

    //-------------------------------------
    //инициализируем поиск объектов
	ulRV = m_pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjectsInit ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRV = m_pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjects ошибка ---> " + sEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
	}
    //Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (ulFoundObj < 1) {
        bRes = false;
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

        ulRV = m_pFunctionList->C_SetAttributeValue(hSession, hObject, pNewDataTemplate, sizeof(pNewDataTemplate) / sizeof(pNewDataTemplate[0]));
        if (ulRV != CKR_OK) {
            MSG_WARNING_("C_SetAttributeValue ошибка ---> " + sEtokenErrorString(ulRV));
            bRes = false;
            goto lDone;
        }

        bRes = true;
        goto lDone;
    }        

lDone:
    //-------------------------------------
    //Clean up the search.
    ulRV = m_pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_FindObjectsFinal ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = m_pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = m_pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
    }

    return bRes;
}
//---------------------------------------------------------------------------
//DONE: bClearDataObject
bool CYug_eToken::bClearDataObject(unsigned long ulSlotId, char *pszUserPIN, char *pszObjectName/*ID*/) {
    return bChangeDataObject(ulSlotId, pszUserPIN, pszObjectName/*ID*/, "", "");
}
//--------------------------------------------------------------------------

////---------------------------------------------------------------------------
//////TODO: bInitializeToken
/////*
////	Usage:   InitToken <reader-name> <format-password> <user-password>  
////	Example: InitToken "AKS ifdh 0" 1234567890 password
////*/
////bool CYug_eToken::bInitializeToken(const AnsiString& asFormatPass, const AnsiString& asUserPass) {
////    unsigned long int      ulRV     = CKR_OK;
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
////	ulRV = m_pFunctionList->C_InitToken(0/*slots[slot_index]*/, asFormatPass.c_str()/*CK_CHAR_PTR(formatPassword)*/, asFormatPass.Length()/*strlen(formatPassword)*/, token_label);
////	if (ulRV != CKR_OK) {
////        MessageBox(0, "C_InitToken ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////		return false;
////	}
////
////    //открываем сессию для чтения/записи на eToken 
////	ulRV = m_pFunctionList->C_OpenSession(0/*slots[slot_index]*/, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
////	if (ulRV != CKR_OK) {
////        MessageBox(0, "C_OpenSession ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return false;
////    }
////
////    //логинимся как SO с паролем formatPassword
////    /* Security Officer     #define CKU_SO    0 */
////    /* Normal user          #define CKU_USER  1 */
////	ulRV = m_pFunctionList->C_Login(hSession, CKU_SO, asFormatPass.c_str()/*CK_CHAR_PTR(formatPassword)*/, asFormatPass.Length()/*strlen(formatPassword)*/);
////	if (ulRV != CKR_OK) {
////        MessageBox(0, "C_Login ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return false;
////    }
////
////    //инициализируем USER PIN паролем userPassword
////	ulRV = m_pFunctionList->C_InitPIN (hSession, asUserPass.c_str()/*CK_CHAR_PTR(userPassword)*/, asUserPass.Length()/*strlen(userPassword)*/);
////    if (ulRV != CKR_OK) {
////        MessageBox(0, "C_InitPIN ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return false;
////    }
////
////    //делогинимся
////    ulRV = m_pFunctionList->C_Logout(hSession);
////	if (ulRV != CKR_OK) {
////        MessageBox(0, "C_Logout ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return false;
////    }
////
//////    //проверяем новый USER PIN.
//////    printf ("Logging in to eToken as USER with - %s \n", userPassword);
//////    if (CKR_OK != m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(userPassword), strlen(userPassword))) {
//////        MSG_WARNING_("C_Login ошибка.\n");
//////        return false;
//////    }
//////  
//////    //Show how to generate RSA key pair.
//////    //--genKeyPair();
//////
//////    //делогинимся
//////    if (CKR_OK != m_pFunctionList->C_Logout (hSession)) {
//////        MSG_WARNING_("C_Logout ошибка.\n");
//////        return false;
//////    }
////
////    //закрываем сессию
////    ulRV = m_pFunctionList->C_CloseSession(hSession);
////	if (ulRV != CKR_OK) {
////        MessageBox(0, "C_CloseSession ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
////        return false;
////    }                       
////
////    return true;
////}
//---------------------------------------------------------------------------
//TODO: dwLocateToken
////DWORD CYug_eToken::dwLocateToken() {
////	DWORD dwSlots  = 1;
////	DWORD dwSlotID = 0;
////	if (CKR_OK != pFunc->C_GetSlotList(true, &dwSlotID, &dwSlots)) {
////		MSG_WARNING_("C_GetSlotList failed");
////		return TOKEN_NON_PRESENT;
////	}
////	if (dwSlots < 1) {
////		MSG_WARNING_("No eToken inserted");
////		return TOKEN_NON_PRESENT;
////	}
////	return dwSlotID;
////}
//---------------------------------------------------------------------------
//TODO: bCheckPinPolicy
////bool CYug_eToken::bCheckPinPolicy(CK_SESSION_HANDLE	hSession, CK_OBJECT_HANDLE hObject) {
////	unsigned long int ulRV = CKR_OK;
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
////	if (ulRV = pFunc->C_GetAttributeValue(hSession, hObject, pTamplate, 6)) {
////		MSG_WARNING_("Failed to get PIN policy information.");
////		return false;
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
////		return true;
////	}	
////	
////	return false;
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

bool CYug_eToken::bGetTokenInfo(unsigned long int ulSlotId, TStringMap &smInfo) {
    //-------------------------------------
	//если токен был вынят - выход
    if (m_bWasInit == false) {
		return false;
	}

    unsigned long int ulRV = CKR_OK;
    
	CK_SLOT_INFO siSI;	memset(&siSI, 0, sizeof(siSI));
	ulRV = m_pFunctionList->C_GetSlotInfo(ulSlotId, &siSI);
	if (ulRV != CKR_OK) {
		MessageBox(0, "C_GetSlotInfo ошибка", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
		return false;
	}
	//Если токен существует в слоте - показать его информацию
	if (!(siSI.flags & CKF_TOKEN_PRESENT)) {
		//MessageBox(0, "eToken извлечён", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
		return false;
	}
	if (!(siSI.flags & CKF_REMOVABLE_DEVICE)) {
		MessageBox(0, "CKF_REMOVABLE_DEVICE", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);
		return false;
	}
	if (!(siSI.flags & CKF_HW_SLOT)) {
		MessageBox(0, "CKF_HW_SLOT", "Внимание", MB_OK + MB_ICONSTOP + MB_TOPMOST);;
		return false;
	}

	//-------------------------------------
	//eTSAPI.h

	//-------------------------------------
    //CKA_SAPI_PRODUCT_NAME [eToken PRO] (0)  //OutString
    {
		const unsigned long int ulProductNameLen = 256;
		char                    szProductName[ulProductNameLen];	memset(szProductName, 0, sizeof(szProductName));	

        CK_ATTRIBUTE pTamplate[] = {
			{CKA_SAPI_PRODUCT_NAME, szProductName, ulProductNameLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int ulModelLen = 256;
        char                    szModel[ulModelLen];	memset(szModel, 0, sizeof(szModel));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_MODEL, szModel, ulModelLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulFwVersionLen = sizeof(CK_VERSION) + 2;   //+1 символ на "." + 1 '\0'
        char                     szFwVersion[ulFwVersionLen];	memset(szFwVersion, 0, sizeof(szFwVersion));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FW_VERSION, szFwVersion, ulFwVersionLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulFwRevisionLen = sizeof(unsigned long int);         ///////////???
        char                     szFwRevision[ulFwRevisionLen];	memset(szFwRevision, 0, sizeof(szFwRevision));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FW_REVISION, szFwRevision, ulFwRevisionLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulHwVersionLen = sizeof(CK_VERSION) + 2;   //+1 символ на "."         ///???
        char                     szHwVersion[ulHwVersionLen];	memset(szHwVersion, 0, sizeof(szHwVersion));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HW_VERSION, szHwVersion, ulHwVersionLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int ulHwInternalLen = 256;
        char                    szHwInternal[ulHwInternalLen];	memset(szHwInternal, 0, sizeof(szHwInternal));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HW_INTERNAL, szHwInternal, ulHwInternalLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_HW_INTERNAL"] = EMPTY_MSG_; 
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            char szTmp[3] = "";
            for (unsigned long int i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                smInfo["CKA_SAPI_HW_INTERNAL"] += std::string(szHwInternal, 3);		//+3 = 2 байта + 1 пробел
            }
        }
		//MessageBox(0, (">>" + smInfo["CKA_SAPI_HW_INTERNAL"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_PRODUCTION_DATE [27.08.2006] (6) //OutDate
    {
        const unsigned long int ulProductionDateLen = sizeof(CK_DATE) + 2 + 1;   //+2 символ на "." + 1 yна '\0'
        char                    szProductionDate[ulProductionDateLen];	memset(szProductionDate, 0, sizeof(szProductionDate));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_PRODUCTION_DATE, szProductionDate, ulProductionDateLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulCaseModelLen = sizeof(unsigned long int);          //////////???
        char                     szCaseModel[ulCaseModelLen];	memset(szCaseModel, 0, sizeof(szCaseModel));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CASE_MODEL, szCaseModel, ulCaseModelLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulTokenIdLen = 20;
        char                     szTokenId[ulTokenIdLen];	memset(szTokenId, 0, sizeof(szTokenId));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_TOKEN_ID, szTokenId, ulTokenIdLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int ulCardIdLen = 256;
        char                    szCardId[ulCardIdLen];	memset(szCardId, 0, sizeof(szCardId));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_ID, szCardId, ulCardIdLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_CARD_ID"] = EMPTY_MSG_; 
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            char szTmp[4] = "";	//+ 1 на '\0'
            for (unsigned long int i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                smInfo["CKA_SAPI_CARD_ID"] += std::string(szTmp, 3);	//+3 = 2 байта + 1 пробел
            }
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_CARD_ID"] + "<<").c_str(), "", MB_OK);
    }

    //-------------------------------------
    //CKA_SAPI_CARD_TYPE [1] (10)	//OutDecimal
    {
        const unsigned long int  ulpCardTypeLen = sizeof(unsigned long int);
        char                     pCardType[ulpCardTypeLen];	memset(pCardType, 0, sizeof(pCardType));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_TYPE, pCardType, ulpCardTypeLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulCardVersionLen = sizeof(CK_VERSION) + 2;   //+1 символ на "." + 1 на '\0'
        char                     szCardVersion[ulCardVersionLen];	memset(szCardVersion, 0, sizeof(szCardVersion));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_VERSION, szCardVersion, ulCardVersionLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulSerialLen = 256;
        char                     szSerial[ulSerialLen];	memset(szSerial, 0, sizeof(szSerial));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_SERIAL, szSerial, ulSerialLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
        }

        if (pTamplate->ulValueLen == 0) {
            smInfo["CKA_SAPI_SERIAL"] = EMPTY_MSG_; 
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            char szTmp[4];		//+1 на '\0'
            for (unsigned long int i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                smInfo["CKA_SAPI_SERIAL"] += std::string(szTmp, 3);	//+3 = 2 байта + 1 пробел
             }
        }
        //MessageBox(0, (">>" + smInfo["CKA_SAPI_SERIAL"] + "<<").c_str(), "", MB_OK);
    }
	

    //-------------------------------------
    //CKA_SAPI_COLOR [0] (13)	//OutDecimal
    {
        const unsigned long int  ulColorLen = sizeof(unsigned long int);
        char                     szColor[ulColorLen];	memset(szColor, 0, sizeof(szColor));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_COLOR, szColor, ulColorLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulHasBatteryLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHasBattery[ulHasBatteryLen];	memset(szHasBattery, 0, sizeof(szHasBattery));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_BATTERY, szHasBattery, ulHasBatteryLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulHasLCDLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHasLCD[ulHasLCDLen];	memset(szHasLCD, 0, sizeof(szHasLCD));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_LCD, szHasLCD, ulHasLCDLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulHasUserLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHasUser[ulHasUserLen];	memset(szHasUser, 0, sizeof(szHasUser));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_USER, szHasUser, ulHasUserLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulHasSOLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHasSO[ulHasSOLen];	memset(szHasSO, 0, sizeof(szHasSO));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_SO, szHasSO, ulHasSOLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulFipsLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szFips[ulFipsLen];	memset(szFips, 0, sizeof(szFips));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FIPS, szFips, ulFipsLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulFipsSupportedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szFipsSupported[ulFipsSupportedLen];    memset(szFipsSupported, 0, sizeof(szFipsSupported));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FIPS_SUPPORTED, szFipsSupported, ulFipsSupportedLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulInitPinReqLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szInitPinReq[ulInitPinReqLen];	memset(szInitPinReq, 0, sizeof(szInitPinReq));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_INIT_PIN_REQ, szInitPinReq, ulInitPinReqLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulRSA2048Len = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szRSA2048[ulRSA2048Len];		memset(szRSA2048, 0, sizeof(szRSA2048));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_RSA_2048, szRSA2048, ulRSA2048Len}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulRSA2048SupportedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szRSA2048Supported[ulRSA2048SupportedLen];	memset(szRSA2048Supported, 0, sizeof(szRSA2048Supported));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_RSA_2048_SUPPORTED, szRSA2048Supported, ulRSA2048SupportedLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulHMACSHA1Len = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHMACSHA1[ulHMACSHA1Len];	memset(szHMACSHA1, 0, sizeof(szHMACSHA1));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HMAC_SHA1, szHMACSHA1, ulHMACSHA1Len}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulHMACSHA1SuppotedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szHMACSHA1Suppoted[ulHMACSHA1SuppotedLen];	memset(szHMACSHA1Suppoted, 0, sizeof(szHMACSHA1Suppoted));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HMAC_SHA1_SUPPORTED, szHMACSHA1Suppoted, ulHMACSHA1SuppotedLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulRealColorLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szRealColor[ulRealColorLen];	memset(szRealColor, 0, sizeof(szRealColor));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_REAL_COLOR, szRealColor, ulRealColorLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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
        const unsigned long int  ulMayInitLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        char                     szMayInit[ulMayInitLen];	memset(szMayInit, 0, sizeof(szMayInit));

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_MAY_INIT, szMayInit, ulMayInitLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING_("SAPI_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
            return false;
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

    ulRV = m_pFunctionList->C_GetTokenInfo(ulSlotId, &tiTI);
    if (ulRV != CKR_OK) {
        MSG_WARNING_("C_GetTokenInfo ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }
   
    //-------------------------------------
    //LABEL [eToken]     unsigned char[32] (27)		//CK_UTF8CHAR [32]
    {
        //printf ("Label: %.32s\n", tiTI.label);
        char szTemp[32 + 1];	memset(szTemp, 0, sizeof(szTemp));
        sprintf(szTemp, "%.32s", tiTI.label);
        
        smInfo["LABEL"] = sTrimSpace(std::string(szTemp));
        //MessageBox(0, (">>" + smInfo["LABEL"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MANUFACTURER_ID [Aladdin Ltd.]   unsigned char[32] (28)
    {
        //printf ("Manufacturer: %.32s\n",          tiTI.manufacturerID);
        char szTemp[32 + 1];	memset(szTemp, 0, sizeof(szTemp));
        sprintf(szTemp, "%.32s", tiTI.manufacturerID);
        smInfo["MANUFACTURER_ID"] = sTrimSpace(std::string(szTemp));
        //MessageBox(0, (">>" + smInfo["MANUFACTURER_ID"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MODEL_2 [eToken] unsigned char[16]    (29)????--------------------
    {
        //printf ("Model: %.16s\n",                 tiTI.model);
        char szTemp[16 + 1];	memset(szTemp, 0, sizeof(szTemp));
        sprintf(szTemp, "%.16s", tiTI.model);
        smInfo["MODEL_2"] = sTrimSpace(std::string(szTemp)); 
        //MessageBox(0, (">>" + smInfo["MODEL_2"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //SERIAL_NUMBER [4706a314] unsigned char[16]   (30)---------------
    {
        //printf ("Serial number: %.16s\n",         tiTI.serialNumber);
        char szTemp[16 + 1];	memset(szTemp, 0, sizeof(szTemp));
        sprintf(szTemp, "%.16s", tiTI.serialNumber);
        smInfo["SERIAL_NUMBER"] = sTrimSpace(std::string(szTemp));
        //MessageBox(0, (">>" + smInfo["SERIAL_NUMBER"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //HARDWARE_VERSION_MAJOR [1] (31)
    {
        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        char szTemp[1 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+1 на '\0' 
        sprintf(szTemp, "%d", tiTI.hardwareVersion.major);
        smInfo["HARDWARE_VERSION_MAJOR"] = std::string(szTemp); 
        //MessageBox(0, (">>" + smInfo["HARDWARE_VERSION_MAJOR"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //HARDWARE_VERSION_MINOR [2] (32)
    {
        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        char szTemp[1 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.hardwareVersion.minor);
        smInfo["HARDWARE_VERSION_MINOR"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["HARDWARE_VERSION_MINOR"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //FIRMWARE_VERSION_MAJOR [0] (33)
    {
        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        char szTemp[1 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.firmwareVersion.major);
        smInfo["FIRMWARE_VERSION_MAJOR"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["FIRMWARE_VERSION_MAJOR"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //FIRMWARE_VERSION_MINOR [4] (34)
    {
        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        char szTemp[1 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.firmwareVersion.minor);
        smInfo["FIRMWARE_VERSION_MINOR"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["FIRMWARE_VERSION_MINOR"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //SESSION_COUNT [0] unsigned long (35)
    {
        //printf ("Current session count: %d\n",    tiTI.ulSessionCount);
        char szTemp[1 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulSessionCount);
        smInfo["SESSION_COUNT"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["SESSION_COUNT"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MAX_SESSION_COUNT [0]  unsigned lon (36)
    {
        //printf ("Maximum session count: %d\n",    tiTI.ulMaxSessionCount);
        char szTemp[1 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulMaxSessionCount);
        smInfo["MAX_SESSION_COUNT"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["MAX_SESSION_COUNT"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MAX_RW_SESSION_COUNT [0] (37)
    {
        //printf ("Maximum RW session count: %d\n", tiTI.ulMaxRwSessionCount);
        char szTemp[1 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulMaxRwSessionCount);
        smInfo["MAX_RW_SESSION_COUNT"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["MAX_RW_SESSION_COUNT"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MIN_PIN_LEN [6...255] (38)
    {
        //printf ("PIN length: [%d..%d]\n",         tiTI.ulMinPinLen,  tiTI.ulMaxPinLen);
        char szTemp[1 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulMinPinLen);
        smInfo["MIN_PIN_LEN"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["MIN_PIN_LEN"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //MAX_PIN_LEN [6...255] (39)
    {
        //printf ("PIN length: [%d..%d]\n",         tiTI.ulMinPinLen,  tiTI.ulMaxPinLen);
        char szTemp[3 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulMaxPinLen);
        smInfo["MAX_PIN_LEN"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["MAX_PIN_LEN"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //FREE_PUBLIC_MEMORY [27721 bytes] (40)
    {
        //printf ("Public memory: %d/%d bytes\n",   tiTI.ulFreePublicMemory,  tiTI.ulTotalPublicMemory);
        char szTemp[5 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulFreePublicMemory);
        smInfo["FREE_PUBLIC_MEMORY"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["FREE_PUBLIC_MEMORY"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //TOTAL_PUBLIC_MEMORY [32768 bytes] (41)
    {
        //printf ("Public memory: %d/%d bytes\n",   tiTI.ulFreePublicMemory,  tiTI.ulTotalPublicMemory);
        char szTemp[5 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulTotalPublicMemory);
        smInfo["TOTAL_PUBLIC_MEMORY"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["TOTAL_PUBLIC_MEMORY"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //FREE_PRIVATE_MEMORY [27721 bytes] (42)
    {
        //printf ("Private memory: %d/%d bytes\n",  tiTI.ulFreePrivateMemory, tiTI.ulTotalPrivateMemory);
        char szTemp[5 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
        sprintf(szTemp, "%d", tiTI.ulFreePrivateMemory);
        smInfo["FREE_PRIVATE_MEMORY"] = std::string(szTemp); 
		//MessageBox(0, (">>" + smInfo["TOTAL_PUBLIC_MEMORY"] + "<<").c_str(), "", MB_OK); 
    }

    //-------------------------------------
    //TOTAL_PRIVATE_MEMORY [32768 bytes] (43)
    {
        //printf ("Private memory: %d/%d bytes\n",  tiTI.ulFreePrivateMemory, tiTI.ulTotalPrivateMemory);
        char szTemp[5 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
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
        CK_MECHANISM_INFO mecInfo;	memset(&mecInfo, 0, sizeof(mecInfo));
	
        ulRV = m_pFunctionList->C_GetMechanismInfo(ulSlotId, CKM_RSA_PKCS, &mecInfo);
        if (ulRV != CKR_OK) {
            smInfo["RSA_MECHANISM_MAX_KEY_SIZE"] = EMPTY_MSG_;
        } else {
            //printf ("RSA Mechanism MaxKeySize: %d\n", mecInfo.ulMaxKeySize);
			char szTemp[4 + 1];	memset(szTemp, 0, sizeof(szTemp));		//+ 1 на '\0' 
			sprintf(szTemp, "%d", mecInfo.ulMaxKeySize);
			smInfo["RSA_MECHANISM_MAX_KEY_SIZE"] = std::string(szTemp);
			//MessageBox(0, (">>" + smInfo["RSA_MECHANISM_MAX_KEY_SIZE"] + "<<").c_str(), "", MB_OK);
        }
    }

	return true;
}
//---------------------------------------------------------------------------



/**********************************************************************
*	Шифрование
*
***********************************************************************/

//--------------------------------------------------------------------------
//DONE: sEncryptTextDES
bool CYug_eToken::bEncryptDES(unsigned long  ulSlotId,
                                       char *pszUserPIN,    unsigned long int  ulUserPINLen,
                              unsigned char *pucKey,        unsigned long int  uiKeyLen,
                              unsigned char *pucIv,         unsigned long int  uiIvLen,
                              unsigned char *pucPlainText,  unsigned long int  uiPlainTextLen,
                              unsigned char *pucCipherText, unsigned long int &ulCipherTextLen)
{
    #define BYTESIZE(bitsize) ((bitsize + 7) >> 3)

    unsigned long int ulRV      = CKR_OK;
    unsigned long int uiPadSize = BYTESIZE(64/*SNMP_TRANS_PRIVLEN_1DES*/);  //for DES
    unsigned long int uiOffset  = 0;

    //-------------------------------------
    //открываем сессию
    CK_SESSION_HANDLE hSession = 0;          
    ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_OpenSession ошибка" + sEtokenErrorString(ulRV));
        return false;
    }
                                                        
    //-------------------------------------
    //логинимся
    ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

    //-------------------------------------
    //создаём ключ
    CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
    CK_KEY_TYPE     ulKeyType   = CKK_DES;
    CK_BBOOL        bTrueValue  = true;
    CK_BBOOL        bFalseValue = false;

    CK_ATTRIBUTE pTemplate[] = {
        {CKA_CLASS,    &ulClass,     sizeof(ulClass)    },
        {CKA_KEY_TYPE, &ulKeyType,   sizeof(ulKeyType)  },
        {CKA_ENCRYPT,  &bTrueValue,  sizeof(bTrueValue) },
        {CKA_TOKEN,    &bFalseValue, sizeof(bFalseValue)},
        {CKA_VALUE,    pucKey,       uiKeyLen           }
    };

    CK_OBJECT_HANDLE hKey = 0;
    ulRV = m_pFunctionList->C_CreateObject(hSession, pTemplate, sizeof(pTemplate) / sizeof(CK_ATTRIBUTE), &hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CreateObject ошибка ---> " + sEtokenErrorString(ulRV));
		return false;
    }              
 
	//-------------------------------------
	//шифруем
    CK_MECHANISM Mech;	memset(&Mech, 0, sizeof(Mech));
    Mech.mechanism      = CKM_DES_CBC_PAD;
    Mech.pParameter     = pucIv;
    Mech.ulParameterLen = uiIvLen;
 
    ulRV = m_pFunctionList->C_EncryptInit(hSession, &Mech, hKey);
    if (ulRV != CKR_OK ) {
        /*LOG*/Log.vLog("C_EncryptInit ошибка ---> " + sEtokenErrorString(ulRV));
		return false;
    }

    if (uiPlainTextLen + uiPadSize - uiPlainTextLen % uiPadSize > /***/ulCipherTextLen) {
        return false;
    }

    //продолжаем  многоступенчатое шифрование
    for (uiOffset = 0; uiOffset < uiPlainTextLen; uiOffset += uiPadSize) {
        ulRV = m_pFunctionList->C_EncryptUpdate(hSession, pucPlainText + uiOffset, uiPadSize, /*(unsigned char *)*/pucCipherText + uiOffset, &ulCipherTextLen);
        if (ulRV != CKR_OK) {
            /*LOG*/Log.vLog("C_EncryptUpdate ошибка ---> " + sEtokenErrorString(ulRV));
			return false;
        }
    }

    //заканчиваем многоступенчатое шифрование
    ulRV = m_pFunctionList->C_EncryptFinal(hSession, pucCipherText + uiOffset, &ulCipherTextLen);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_EncryptFinal ошибка ---> " + sEtokenErrorString(ulRV));
    }
    /***/ulCipherTextLen = uiOffset;

    /*LOG*///Log.vLogCharAsHex("Результат шифрования:", pucCipherText, ulCipherTextLen);
    /*LOG*///Log.vLogCharAsStr("Результат шифрования:", pucCipherText, ulCipherTextLen);

    //-------------------------------------
    //удаляем ключ
    //--	if (key != (CK_OBJECT_HANDLE) 0) {}
    ulRV = m_pFunctionList->C_DestroyObject(hSession, hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_DestroyObject ошибка ---> " + sEtokenErrorString(ulRV));
		return false;
    }

    //-------------------------------------
    //делогинимся
    ulRV = m_pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
		return false;
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = m_pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
		return false;
    }

    //Log.vOpen();

    return true;	
}
//--------------------------------------------------------------------------
//DONE: sDecryptTextDES
bool CYug_eToken::bDecryptDES(unsigned long  ulSlotId,
                                       char *pszUserPIN,    unsigned long int  ulUserPINLen,
                              unsigned char *pucKey,        unsigned long int  ulKeyLen,
                              unsigned char *pucIv,         unsigned long int  ulIvLen,
                              unsigned char *pucPlainText,  unsigned long int &ulPlainTextLen,
                              unsigned char *pucCipherText, unsigned long int  ulCipherTextLen) {

	#define BYTESIZE_B(bitsize) ((bitsize + 7) >> 3)

	unsigned long int ulRV      = CKR_OK;
	unsigned long int uiPadSize = BYTESIZE_B(64/*SNMP_TRANS_PRIVLEN_1DES*/);  //for DES
	unsigned long int uiOffset  = 0;

    //-------------------------------------
    //открываем сессию
    CK_SESSION_HANDLE hSession = 0;
    ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_OpenSession ошибка ---> " + sEtokenErrorString(ulRV));
        return false; 
    }

    //-------------------------------------
    //логинимся
    ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

	//-------------------------------------
    //создаём ключ
	CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
	CK_KEY_TYPE     ulKeyType   = CKK_DES;
	CK_BBOOL        bTrueValue  = TRUE;
	CK_BBOOL        bFalseValue = FALSE;
	
	CK_ATTRIBUTE pTemplate[] = {
		{CKA_CLASS,    &ulClass,     sizeof(ulClass)    },
		{CKA_KEY_TYPE, &ulKeyType,   sizeof(ulKeyType)  },
		{CKA_DECRYPT,  &bTrueValue,  sizeof(bTrueValue) },
		{CKA_TOKEN,    &bFalseValue, sizeof(bFalseValue)},
		{CKA_VALUE,     pucKey,      ulKeyLen           }
	};

    CK_OBJECT_HANDLE hKey = 0;
	ulRV = m_pFunctionList->C_CreateObject(hSession, pTemplate, sizeof(pTemplate) / sizeof(CK_ATTRIBUTE), &hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CreateObject ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }

    //-------------------------------------
   	//дешифруем
    CK_MECHANISM Mech;  memset(&Mech, 0, sizeof(Mech));
    Mech.mechanism      = CKM_DES_CBC_PAD;
    Mech.pParameter     = pucIv; 
    Mech.ulParameterLen = ulIvLen;

	ulRV = m_pFunctionList->C_DecryptInit(hSession, &Mech, hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_DecryptInit ошибка ---> " + sEtokenErrorString(ulRV));
        return false;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////if (ulCipherTextLen + uiPadSize - ulCipherTextLen % uiPadSize > /***/ulCipherTextLen) {
	////	return false;
	////}

	//продолжаем  многоступенчатое шифрование
	for (uiOffset = 0; uiOffset < ulCipherTextLen; uiOffset += uiPadSize) {
		ulRV = m_pFunctionList->C_DecryptUpdate(hSession, pucPlainText + uiOffset, uiPadSize, /*(unsigned char *)*/pucCipherText + uiOffset, &ulCipherTextLen);
		if (ulRV != CKR_OK) {
			/*LOG*/Log.vLog("C_DecryptUpdate ошибка ---> " + sEtokenErrorString(ulRV));
			return false;
		}
	}

	//заканчиваем многоступенчатое шифрование
	ulRV = m_pFunctionList->C_DecryptFinal(hSession, pucCipherText + uiOffset, &ulCipherTextLen);
	if (ulRV != CKR_OK) {
		/*LOG*/Log.vLog("C_DecryptFinal ошибка ---> " + sEtokenErrorString(ulRV));
	}
	/***/ulCipherTextLen = uiOffset;








	////////   //дешифруем полностью всю шифрстроку
	////////ulRV = m_pFunctionList->C_Decrypt(hSession, /*(CK_BYTE_PTR)*/pucCipherText, /*(CK_ULONG)*/ulCipherTextLen, /*(CK_BYTE_PTR)*/pucPlainText, &ulPlainTextLen);
	////////if (ulRV != CKR_OK) {
	////////       /*LOG*/Log.vLog("C_Decrypt ошибка ---> " + sEtokenErrorString(ulRV));
	////////       return false;
	////////}

    /*LOG*///Log.vLogCharAsHex("Результат дешифрования:", pucPlainText, ulPlainTextLen);
    /*LOG*///Log.vLogCharAsStr("Результат дешифрования:", pucPlainText, ulPlainTextLen);
/////////////////////////////////////////////////////////////////////////////////////////////////
    //-------------------------------------
    //удаляем ключ
	//--	if (key != (CK_OBJECT_HANDLE) 0) {}
    ulRV = m_pFunctionList->C_DestroyObject(hSession, hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_DestroyObject ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = m_pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = m_pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
    }

    /*LOG*/Log.vOpen();

    return true;	
}
//--------------------------------------------------------------------------
//DONE: sDecryptTextDES
std::string CYug_eToken::sDecryptTextDES(unsigned long ulSlotId,
										 char *pszUserPIN,    unsigned long int  ulUserPINLen,
										 char *pszKey,        unsigned long int  uiKeyLen,
										 char *pszIv,         unsigned long int  uiIvLen,
										 char *pszPlainText,  unsigned long int &uiPlainTextLen,
										 char *pszCipherText, unsigned long int  ulCipherTextLen) {
	 unsigned long int ulRV = CKR_OK;

	 //-------------------------------------
	 //открываем сессию
	 CK_SESSION_HANDLE hSession;
	 ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
	 if (ulRV != CKR_OK) {
		 /*LOG*/Log.vLog("C_OpenSession ошибка ---> " + sEtokenErrorString(ulRV));
		 return ""; //leave ("C_OpenSession failed.\n");
	 }

	 //-------------------------------------
	 //логинимся
	 ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
	 if (ulRV != CKR_OK) {
		 /*LOG*/Log.vLog("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
		 MSG_WARNING_("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
		 return "";
	 }

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
		 {CKA_VALUE,    pszKey,     uiKeyLen         }
	 };

	 CK_OBJECT_HANDLE  hKey = (CK_OBJECT_HANDLE)0;
	 ulRV = m_pFunctionList->C_CreateObject(hSession, pTemplate, (sizeof(pTemplate) / sizeof(CK_ATTRIBUTE)), &hKey);
	 if (ulRV != CKR_OK) {
		 /*LOG*/Log.vLog("C_CreateObject ошибка ---> " + sEtokenErrorString(ulRV));
		 return "";
	 }

	 //-------------------------------------
	 //дешифруем
	 CK_MECHANISM Mech;
	 Mech.mechanism      = CKM_DES_CBC_PAD;
	 Mech.pParameter     = pszIv;
	 Mech.ulParameterLen = uiIvLen;

	 ulRV = m_pFunctionList->C_DecryptInit(hSession, &Mech, hKey);
	 if (ulRV != CKR_OK) {
		 /*LOG*/Log.vLog("C_DecryptInit ошибка ---> " + sEtokenErrorString(ulRV));
		 return "";
	 }

	 //дешифруем полностью всю шифрстроку
	 ulRV = m_pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)pszCipherText, (CK_ULONG)ulCipherTextLen, (CK_BYTE_PTR)pszPlainText, &uiPlainTextLen);
	 if (ulRV != CKR_OK) {
		 /*LOG*/Log.vLog("C_Decrypt ошибка ---> " + sEtokenErrorString(ulRV));
		 return "";
	 }

	 /*LOG*///Log.vLogCharAsHex("Результат дешифрования:", pszPlainText, uiPlainTextLen);
	 /*LOG*///Log.vLogCharAsStr("Результат дешифрования:", pszPlainText, uiPlainTextLen);

	 //-------------------------------------
	 //удаляем ключ
	 //--	if (key != (CK_OBJECT_HANDLE) 0) {}
	 ulRV = m_pFunctionList->C_DestroyObject(hSession, hKey);
	 if (ulRV != CKR_OK) {
		 /*LOG*/Log.vLog("C_DestroyObject ошибка ---> " + sEtokenErrorString(ulRV));
	 }

	 //-------------------------------------
	 //делогинимся
	 ulRV = m_pFunctionList->C_Logout(hSession);
	 if (ulRV != CKR_OK) {
		 /*LOG*/Log.vLog("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
		 MSG_WARNING_("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
	 }

	 //-------------------------------------
	 //закрываем сессию
	 ulRV = m_pFunctionList->C_CloseSession(hSession);
	 if (ulRV != CKR_OK) {
		 /*LOG*/Log.vLog("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
		 MSG_WARNING_("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
	 }

	 Log.vOpen();

	 return std::string(pszPlainText);
}
//--------------------------------------------------------------------------
//TODO: sEncryptFileDES
////std::string sEncryptFileDES() {}
//--------------------------------------------------------------------------
//TODO: sDecryptFileDES
////std::string sDecryptFileDES() {}
//--------------------------------------------------------------------------
//TODO: sEncryptTextDES3
//////////////std::string CYug_eToken::sEncryptTextDES3(unsigned long ulSlotId,
//////////////                                         unsigned char *pszUserPIN,    unsigned long int  ulUserPINLen,
//////////////                                         unsigned char *pszKey,        unsigned long int  ulKeyLen,
//////////////                                         unsigned char *pszIv,         unsigned long int  ulIvLen,
//////////////                                         unsigned char *pszPlainText,  unsigned long int  ulPlainTextLen,
//////////////                                         unsigned char *pszCipherText, unsigned long int &ulCipherTextLen) {
//////////////    #define BYTESIZE(bitsize) ((bitsize + 7) >> 3)
//////////////
//////////////    ///std::string sRes = "";
//////////////
//////////////    unsigned long int ulRV      = CKR_OK;
//////////////    unsigned long int ulPadSize = BYTESIZE(64/*SNMP_TRANS_PRIVLEN_1DES*/);  //for DES
//////////////    unsigned long int ulOffset  = 0;
//////////////
//////////////    //-------------------------------------
//////////////    //открываем сессию
//////////////    CK_SESSION_HANDLE hSession = 0;          
//////////////    ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
//////////////    if (ulRV != CKR_OK) {
//////////////        /*LOG*///Log.vLog("C_OpenSession ошибка" + sEtokenErrorString(ulRV));
//////////////        return "";
//////////////    }
//////////////                                                        
//////////////    //-------------------------------------
//////////////    //логинимся
//////////////    ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
//////////////    if (ulRV != CKR_OK) {
//////////////        /*LOG*///Log.vLog("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
//////////////        MSG_WARNING_("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
//////////////        return "";
//////////////    }
//////////////
//////////////    //-------------------------------------
//////////////    //создаём ключ
//////////////    //DES
//////////////    /*CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
//////////////    CK_KEY_TYPE     ulKeyType   = CKK_DES3;		//--CKK_DES;
//////////////    CK_BBOOL        bTrueValue  = true;
//////////////    CK_BBOOL        bFalseValue = false;
//////////////
//////////////
//////////////	CK_ATTRIBUTE pTemplate[] = {
//////////////        {CKA_CLASS,    &ulClass,     sizeof(ulClass)    },
//////////////        {CKA_KEY_TYPE, &ulKeyType,   sizeof(ulKeyType)  },
//////////////		{CKA_TOKEN,    &bFalseValue, sizeof(bFalseValue)},
//////////////        {CKA_ENCRYPT,  &bTrueValue,  sizeof(bTrueValue) },
//////////////        {CKA_VALUE,    pszKey,       uiKeyLen           }
//////////////    };*/
//////////////	
//////////////	CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
//////////////	CK_KEY_TYPE     ulKeyType   = CKK_DES3;
//////////////	CK_BBOOL        bTrueValue  = true;
//////////////	CK_BBOOL        bFalseValue = false;
//////////////	
//////////////	CK_ATTRIBUTE pTemplate[] = {
//////////////	   {CKA_CLASS,    &ulClass,     sizeof(ulClass)    },
//////////////	   {CKA_KEY_TYPE, &ulKeyType,   sizeof(ulKeyType)  },
//////////////	   {CKA_TOKEN,    &bFalseValue, sizeof(bFalseValue)},
//////////////	   {CKA_ENCRYPT,  &bTrueValue,  sizeof(bTrueValue) },
//////////////	   {CKA_VALUE,     pszKey,      sizeof(ulKeyLen)   }			//CK_BYTE         value[24]  = {...};
//////////////	};
//////////////
//////////////    /*
//////////////      CK_ATTRIBUTE SessionKeyTemplate[] = 
//////////////	{
//////////////		{ CKA_CLASS,      &cko_SecretKey, sizeof(cko_SecretKey)},
//////////////		{ CKA_KEY_TYPE,   &ckk_DES3,      sizeof(ckk_DES3)},
//////////////		{ CKA_TOKEN,      &ck_False,      sizeof(ck_False)},
//////////////	};
//////////////    */
//////////////
//////////////    CK_OBJECT_HANDLE  hKey     = (CK_OBJECT_HANDLE)0;
//////////////    ulRV = m_pFunctionList->C_CreateObject(hSession, pTemplate, (sizeof(pTemplate) / sizeof(CK_ATTRIBUTE)), &hKey);
//////////////    if (ulRV != CKR_OK) {
//////////////        /*LOG*///Log.vLog("C_CreateObject ошибка ---> " + sEtokenErrorString(ulRV));
//////////////    }              
////////////// 
//////////////	//-------------------------------------
//////////////	//шифруем
//////////////    CK_MECHANISM Mech;
//////////////    Mech.mechanism      = CKM_DES3_CBC_PAD;	//--CKM_DES_CBC_PAD;   
//////////////    Mech.pParameter     = pszIv;
//////////////    Mech.ulParameterLen = ulIvLen;
////////////// 
//////////////    ulRV = m_pFunctionList->C_EncryptInit(hSession, &Mech, hKey);
//////////////    if (ulRV != CKR_OK ) {
//////////////        /*LOG*///Log.vLog("C_EncryptInit ошибка ---> " + sEtokenErrorString(ulRV));
//////////////    }
//////////////
//////////////    if (ulPlainTextLen + ulPadSize - ulPlainTextLen % ulPadSize > /***/ulCipherTextLen) {
//////////////        return "";
//////////////    }
//////////////
//////////////    //продолжаем  многоступенчатое шифрование
//////////////    for (ulOffset = 0; ulOffset < ulPlainTextLen; ulOffset += ulPadSize) {
//////////////        ulRV = m_pFunctionList->C_EncryptUpdate(hSession, pszPlainText + ulOffset, ulPadSize, pszCipherText + ulOffset, &ulCipherTextLen);
//////////////        if (ulRV != CKR_OK) {
//////////////            /*LOG*///Log.vLog("C_EncryptUpdate ошибка ---> " + sEtokenErrorString(ulRV));
//////////////        }
//////////////    }
//////////////
//////////////    //заканчиваем многоступенчатое шифрование
//////////////    ulRV = m_pFunctionList->C_EncryptFinal(hSession, pszCipherText + ulOffset, &ulCipherTextLen);
//////////////    if (ulRV != CKR_OK) {
//////////////        /*LOG*///Log.vLog("C_EncryptFinal ошибка ---> " + sEtokenErrorString(ulRV));
//////////////    }
//////////////    /***/ulCipherTextLen = ulOffset;
//////////////
//////////////    /*LOG*///Log.vLogCharAsHex("Результат шифрования:", pszCipherText, ulCipherTextLen);
//////////////    /*LOG*///Log.vLogCharAsStr("Результат шифрования:", pszCipherText, ulCipherTextLen);
//////////////
//////////////    //-------------------------------------
//////////////    //удаляем ключ
//////////////    //--	if (key != (CK_OBJECT_HANDLE) 0) {}
//////////////    ulRV = m_pFunctionList->C_DestroyObject(hSession, hKey);
//////////////    if (ulRV != CKR_OK) {
//////////////        /*LOG*///Log.vLog("C_DestroyObject ошибка ---> " + sEtokenErrorString(ulRV));
//////////////    }
//////////////
//////////////    //-------------------------------------
//////////////    //делогинимся
//////////////    ulRV = m_pFunctionList->C_Logout(hSession);
//////////////    if (ulRV != CKR_OK) {
//////////////        /*LOG*///Log.vLog("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
//////////////        MSG_WARNING_("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
//////////////    }
//////////////
//////////////    //-------------------------------------
//////////////    //закрываем сессию
//////////////    ulRV = m_pFunctionList->C_CloseSession(hSession);
//////////////    if (ulRV != CKR_OK) {
//////////////        /*LOG*///Log.vLog("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
//////////////        MSG_WARNING_("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
//////////////    }
//////////////
//////////////    //Log.vOpen();
//////////////
//////////////    return "std::string(pszCipherText)";	//------------------
//////////////}
////////////////--------------------------------------------------------------------------
////////////////TODO: sDecryptTextDES3
//////////////std::string CYug_eToken::sDecryptTextDES3(unsigned long ulSlotId,
//////////////                                         unsigned char *pszUserPIN,    unsigned long int  ulUserPINLen,
//////////////                                         unsigned char *pszKey,        unsigned long int  uiKeyLen,
//////////////                                         unsigned char *pszIv,         unsigned long int  uiIvLen,
//////////////                                         unsigned char *pszPlainText,  unsigned long int &uiPlainTextLen,
//////////////                                         unsigned char *pszCipherText, unsigned long int  ulCipherTextLen) {
//    unsigned long int ulRV = CKR_OK;           
//
//    //-------------------------------------
//    //открываем сессию
//    CK_SESSION_HANDLE hSession;
//    ulRV = m_pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
//    if (ulRV != CKR_OK) {
//        /*LOG*///Log.vLog("C_OpenSession ошибка ---> " + sEtokenErrorString(ulRV));
//        return ""; //leave ("C_OpenSession failed.\n");
//    }
//
//    //-------------------------------------
//    //логинимся
//    ulRV = m_pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
//    if (ulRV != CKR_OK) {
//        /*LOG*///Log.vLog("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
//        MSG_WARNING_("C_Login ошибка ---> " + sEtokenErrorString(ulRV));
//        return "";
//    }
//
//	//-------------------------------------
//    //создаём ключ
//    //DES
//	/*CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
//	CK_KEY_TYPE     ulKeyType   = CKK_DES;
//	CK_BBOOL        bTrue       = TRUE;
//	CK_BBOOL        bFalse      = FALSE;
//	
//	CK_ATTRIBUTE    pTemplate[] = {
//		{CKA_CLASS,    &ulClass,   sizeof(ulClass)  },
//		{CKA_KEY_TYPE, &ulKeyType, sizeof(ulKeyType)},
//		{CKA_DECRYPT,  &bTrue,     sizeof(bTrue)    },
//		{CKA_TOKEN,    &bFalse,    sizeof(bFalse)   },
//		{CKA_VALUE,    pszKey,     uiKeyLen         }
//	};*/
//	
//	CK_OBJECT_CLASS ulClass     = CKO_SECRET_KEY;
//	CK_KEY_TYPE     ulKeyType   = CKK_DES3;
//	CK_BBOOL        bTrueValue  = true;
//	CK_BBOOL        bFalseValue = false;
//	
//	CK_ATTRIBUTE pTemplate[] = {
//	   {CKA_CLASS,    &ulClass,     sizeof(ulClass)   },
//	   {CKA_KEY_TYPE, &ulKeyType,   sizeof(ulKeyType) },
//	   {CKA_TOKEN,    &bFalseValue, sizeof(bTrueValue)},
//	   {CKA_DECRYPT,  &bTrueValue,  sizeof(bTrueValue)},
//	   {CKA_VALUE,     pszKey,      sizeof(uiKeyLen)  }			//CK_BYTE         value[24]  = {...};
//	};		
//
//    CK_OBJECT_HANDLE  hKey = (CK_OBJECT_HANDLE)0;
//	ulRV = m_pFunctionList->C_CreateObject(hSession, pTemplate, (sizeof(pTemplate) / sizeof(CK_ATTRIBUTE)), &hKey);
//    if (ulRV != CKR_OK) {
//        /*LOG*///Log.vLog("C_CreateObject ошибка ---> " + sEtokenErrorString(ulRV));
//        return "";
//    }
//
//    //-------------------------------------
//   	//дешифруем
//    CK_MECHANISM Mech;
//    Mech.mechanism      = CKM_DES3_CBC_PAD;	//--CKM_DES_CBC_PAD; 
//    Mech.pParameter     = pszIv;
//    Mech.ulParameterLen = uiIvLen;
//
//	ulRV = m_pFunctionList->C_DecryptInit(hSession, &Mech, hKey);
//    if (ulRV != CKR_OK) {
//        /*LOG*///Log.vLog("C_DecryptInit ошибка ---> " + sEtokenErrorString(ulRV));
//        return "";
//    }
//
//    //дешифруем полностью всю шифрстроку
//	ulRV = m_pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)pszCipherText, (CK_ULONG)ulCipherTextLen, pszPlainText, &uiPlainTextLen);
//	if (ulRV != CKR_OK) {
//        /*LOG*///Log.vLog("C_Decrypt ошибка ---> " + sEtokenErrorString(ulRV));
//        return "";
//	}
//
//    /*LOG*///Log.vLogCharAsHex("Результат дешифрования:", pszPlainText, uiPlainTextLen);
//    /*LOG*///Log.vLogCharAsStr("Результат дешифрования:", pszPlainText, uiPlainTextLen);
//
//    //-------------------------------------
//    //удаляем ключ
//	//--	if (key != (CK_OBJECT_HANDLE) 0) {}
//    ulRV = m_pFunctionList->C_DestroyObject(hSession, hKey);
//    if (ulRV != CKR_OK) {
//        /*LOG*///Log.vLog("C_DestroyObject ошибка ---> " + sEtokenErrorString(ulRV));
//    }
//
//    //-------------------------------------
//    //делогинимся
//    ulRV = m_pFunctionList->C_Logout(hSession);
//    if (ulRV != CKR_OK) {
//        /*LOG*///Log.vLog("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
//        MSG_WARNING_("C_Logout ошибка ---> " + sEtokenErrorString(ulRV));
//    }
//
//    //-------------------------------------
//    //закрываем сессию
//    ulRV = m_pFunctionList->C_CloseSession(hSession);
//    if (ulRV != CKR_OK) {
//        /*LOG*///Log.vLog("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
//        MSG_WARNING_("C_CloseSession ошибка ---> " + sEtokenErrorString(ulRV));
//    }
//
//    //Log.vOpen();
//
//    return "std::string(pszPlainText)";	//??????????????
//}
//--------------------------------------------------------------------------
//TODO: sEncryptFileDES3
////std::string sEncryptFileDES3() {}
//--------------------------------------------------------------------------
//TODO: sDecryptFileDES3
////std::string sDecryptFileDES3() {}
//--------------------------------------------------------------------------


/**********************************************************************
*   Остальные
*
***********************************************************************/

//---------------------------------------------------------------------------
//DONE: sEtokenErrorString (SDK 4.53)
std::string CYug_eToken::sEtokenErrorString(DWORD ulRV) {
	switch (ulRV) {
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