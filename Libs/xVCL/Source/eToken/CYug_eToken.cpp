/**********************************************************************
*	Класс  CEToken (CYug_eToken.cpp)  (RTE 3.60)
*	образец - имя_параметра=значение п_параметра\n
***********************************************************************/


#define WIN32_LEAN_AND_MEAN		//Exclude rarely-used content from Windows headers.

#include "CYug_eToken.h"
#include "Classes\CLog.h"
#include "uEToken.h"            //frmMain
//---------------------------------------------------------------------------
extern CLog Log;
//---------------------------------------------------------------------------
//DONE: объявление SAPI's функции
typedef CK_RV       (*t_SAPI_GetTokenInfo)(CK_SLOT_ID, CK_ATTRIBUTE_PTR, CK_ULONG);
////t_SAPI_GetTokenInfo f_SAPI_GetTokenInfo = NULL; /*DIF: SDK 3.60*/
t_SAPI_GetTokenInfo _SAPI_GetTokenInfo = NULL;		/*DIF: SDK 4.53*/
//---------------------------------------------------------------------------
//DONE: CEToken
CEToken::CEToken() {	//DEBUG_("Конструктор CEToken");
    pFunctionList = NULL;
	bWasInit      = false;
}
//---------------------------------------------------------------------------
//DONE: ~CEToken
CEToken::~CEToken() {	//DEBUG_("Деструктор CEToken");

}
//---------------------------------------------------------------------------
//DONE: bInitialize (Инициализируем DLL-ки (eTPKCS11.dll, eTSAPI.dll))
bool CEToken::bInitialize() {
    if (!bLoadPKCS11() || !bLoadETSAPI()) {
        bWasInit = false;
		return false;
    } else {
        bWasInit = true;  
		return true;
    }
}
//---------------------------------------------------------------------------
//DONE: bFinalize (Финализируем DLL-ки (eTPKCS11.dll, eTSAPI.dll))
bool CEToken::bFinalize() {  //закрыть PKCS #11 библиотеку
    unsigned long int ulRV = CKR_OK;
	
	if (!bWasInit) {return false;}     

	ulRV = pFunctionList->C_Finalize(0);
    if (ulRV == CKR_OK) {
        bWasInit = false;
        return true;
    } else {
        MSG_WARNING("C_Finalize ошибка");
        return false;
    }
}
//---------------------------------------------------------------------------
//DONE: bLoadPKCS11 (Подгружаем eTPKCS11.dll и инициализируем PKCS#11)
bool CEToken::bLoadPKCS11() {
    unsigned long int ulRV = CKR_OK;
	
	HINSTANCE hLib = LoadLibrary(ETPKCS11_PATH);
    if (!hLib) {
		MSG_WARNING("Невозможно подгрузить etpkcs11.dll");
        return false;
    }

    CK_C_GetFunctionList f_C_GetFunctionList = NULL;
    (FARPROC&)f_C_GetFunctionList = GetProcAddress(hLib, "C_GetFunctionList");
    if (!f_C_GetFunctionList) {
		MSG_WARNING("C_GetFunctionList не найдена");
        return false;
    }

    ulRV = f_C_GetFunctionList(&pFunctionList);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetFunctionList ошибка ---> " + asEtokenErrorString(ulRV));
        return false;
    }
	
    ulRV = pFunctionList->C_Initialize(0);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_Initialize ошибка ---> " + asEtokenErrorString(ulRV));
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
//DONE: bLoadETSAPI (Подгружаем eTSAPI.dll и приобретаем его необходимые методы)
bool CEToken::bLoadETSAPI() {
    HINSTANCE hLib = LoadLibrary(ETSAPI_PATH);
    if (!hLib) {
		MSG_WARNING("Невозможно подгрузить etsapi.dll");
        return false;
    }

    (FARPROC&)/*f*/_SAPI_GetTokenInfo = GetProcAddress(hLib, "SAPI_GetTokenInfo");
    if (!/*f*/_SAPI_GetTokenInfo) {
		MSG_WARNING("SAPI_GetTokenInfo не найдена");
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
//TODO: asReadTokenInfo (Прочитать информацию с токенов (для  ListView))
AnsiString CEToken::asReadTokenInfo() {
	if (!bWasInit) {return "";}

	unsigned long int      ulRV = CKR_OK;
    AnsiString asAllReadInfo = "";

    //получаем список слотов
    CK_SLOT_ID_PTR    pSlots     = NULL;
    unsigned long int ulSlotCount = 0;

    ulRV = pFunctionList->C_GetSlotList(TRUE, NULL, &ulSlotCount);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetSlotList ошибка --->" + asEtokenErrorString(ulRV));
        return "";
    }
    if (ulSlotCount < 1) {
        MSG_WARNING("Нет вставленного eToken");
        return "";
    }
    pSlots = new CK_SLOT_ID[ulSlotCount];
    ulRV = pFunctionList->C_GetSlotList(TRUE, pSlots, &ulSlotCount);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetSlotList ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
    
    //цикл по всем eToken - выводим инфу
    TStringList* pList = new TStringList();
    for (CK_ULONG i = 0; i < ulSlotCount; i ++) {
        CK_ULONG SlotID = pSlots[i];
        pList->Add(asGetTokenInfo(SlotID) + "`");    //MessageBox(0, pList->Text.c_str(), "", MB_OK);=
    }
    asAllReadInfo = pList->Text;
    
    delete pList;       pList  = NULL;
    delete []pSlots;    pSlots = NULL;

    return asAllReadInfo;   
}
//---------------------------------------------------------------------------
//TODO: uiGetSlotList()
unsigned long int *CEToken::uiGetSlotList(/*unsigned long int &ulSlotCount*/) {
    const int ciSLOTS_NOT_PRESENT = - 1;
    
	if (!bWasInit) {return (unsigned long int *)ciSLOTS_NOT_PRESENT;}	//????????????

	unsigned long int ulRV                   = CKR_OK;
    unsigned long int uiAllSlots;  // = (unsigned int *)ciSLOTS_NOT_PRESENT;	//?????????????

    //получаем список слотов
    CK_SLOT_ID_PTR pSlots     = NULL;
    CK_ULONG       nSlotCount = 0;

    ulRV = pFunctionList->C_GetSlotList(TRUE, NULL, &nSlotCount);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetSlotList ошибка --->" + asEtokenErrorString(ulRV));
        return (unsigned long int *)ciSLOTS_NOT_PRESENT;
    }
    if (nSlotCount < 1) {
        MSG_WARNING("Нет вставленного eToken");
        return (unsigned long int *)ciSLOTS_NOT_PRESENT;
    }
    pSlots = new CK_SLOT_ID[nSlotCount];
    ulRV = pFunctionList->C_GetSlotList(TRUE, pSlots, &nSlotCount);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetSlotList ошибка ---> " + asEtokenErrorString(ulRV));
        return (unsigned long int *)ciSLOTS_NOT_PRESENT;
    }

    ////ulSlotCount = nSlotCount;

    return pSlots;

//--    //цикл по всем eToken - выводим инфу
//--    for (CK_ULONG i = 0; i < nSlotCount; i ++) {
//--        CK_ULONG SlotID = pSlots[i];
//--        //ShowMessage(SlotID);
//--        //uiAllSlots = ;
//--    }


//--    delete []pSlots;    pSlots = NULL;

//--    return uiAllSlots;
}
//---------------------------------------------------------------------------
//TODO: iInsertedTokens (Получаем количество вставленных токенов)
int CEToken::iInsertedTokens() {
    if (!bWasInit) {return 0;}

    unsigned long int             ulRV        = CKR_OK;
    unsigned long int ulSlotCount = 0;

    ulRV = pFunctionList->C_GetSlotList(TRUE, NULL, &ulSlotCount);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetSlotList ошибка ---> " + asEtokenErrorString(ulRV));
        return 0;
    }

    return ulSlotCount;
}
//---------------------------------------------------------------------------
//DONE: dwWaitForSlotEvent (Ждём вставки/извлечения токена)
unsigned long int CEToken::dwWaitForSlotEvent() {
    if (!bWasInit) {return TOKEN_NON_PRESENT;}

    unsigned long int ulRV     = CKR_OK;
	DWORD dwSlotId = TOKEN_NON_PRESENT;

    ulRV = pFunctionList->C_WaitForSlotEvent(0, &dwSlotId, 0);
	if (ulRV != CKR_OK) {
        return TOKEN_NON_PRESENT;
    } else {
        return dwSlotId;
    }
}
//---------------------------------------------------------------------------
//TODO: asGetLibraryInfo (Информация о PKCS#11 библиотеке)
AnsiString CEToken::asGetLibraryInfo() {
    if (!bWasInit) {return "";}

    unsigned long int   ulRV = CKR_OK;
	AnsiString asLibraryInfo = "";
    
	CK_INFO info;
	ulRV = pFunctionList->C_GetInfo(&info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }

	asLibraryInfo += ("CRYPTOKI_VERSION_MAJOR=" + IntToStr(info.cryptokiVersion.major) + '\n').c_str();
	asLibraryInfo += ("CRYPTOKI_VERSION_MINOR=" + IntToStr(info.cryptokiVersion.minor) + '\n').c_str();
	asLibraryInfo += AnsiString().sprintf("%s=%.32s\n", "MANUFACTURER_ID",     info.manufacturerID).c_str();
	asLibraryInfo += AnsiString().sprintf("%s=%.32s\n", "LIBRARY_DESCRIPTION", info.libraryDescription).c_str();
	asLibraryInfo += ("LIBRARY_VERSION_MAJOR="  + IntToStr(info.libraryVersion.major)  + '\n').c_str();
	asLibraryInfo += ("LIBRARY_VERSION_MINOR="  + IntToStr(info.libraryVersion.minor)  + '\n').c_str();
	
	return asLibraryInfo;
}
//---------------------------------------------------------------------------

/**********************************************************************
*	Объекты
*
***********************************************************************/


//--------------------------------------------------------------------------
//DONE: hFindObject (Small utility function to search for a particular object containing the attribute 't')
CK_OBJECT_HANDLE CEToken::hFindObject(CK_SESSION_HANDLE hSess, CK_ATTRIBUTE * t, CK_ULONG size) {
    unsigned long int ulRV = CKR_OK;

	//Initialize the search for any object with attribute 't'
	ulRV = pFunctionList->C_FindObjectsInit(hSess, t, size);
	if (ulRV != CKR_OK) {
		//--leave ("C_FindObjectsInit failed.\n");
	}

	CK_OBJECT_HANDLE list[1];
	CK_ULONG         found = 0;

	//Find matching objects. There should be only a single match as there is only one on the eToken.
	ulRV = pFunctionList->C_FindObjects(hSess, list, 1, &found);
	if (ulRV != CKR_OK) {
		//--leave ("C_FindObjects failed.\n");
	}

	//Clean up the search.
	ulRV = pFunctionList->C_FindObjectsFinal(hSess);
	if (ulRV != CKR_OK) {
		//--leave ("C_FindObjectsFinal failed.\n");
	}

	//Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (found < 1) {
		return (NULL);
	}

	return (list[0]);
}
//--------------------------------------------------------------------------
//TODO: bIsDataObjectExists
bool CEToken::bIsDataObjectExists(unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszApplication/*ID*/, unsigned char *pszLabel, unsigned char *pszValue) {
   	unsigned long int ulRV         = CKR_OK;

    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRV = pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + asEtokenErrorString(ulRV));
        return false;
    }

    //-------------------------------------
    //логинимся
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
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

    //-------------------------------------
    //инициализируем поиск объектов
	ulRV = pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjectsInit ошибка ---> " + asEtokenErrorString(ulRV));
        return false;
	}

    //-------------------------------------
	//Find matching objects. There should be only a single match as there is only one on the eToken.
	ulRV = pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjects ошибка ---> " + asEtokenErrorString(ulRV));
        return false;
	}

    //-------------------------------------
    //Clean up the search.
    ulRV = pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjectsFinal ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //Return NULL if no match is found, otherwise return the object handles of the matching object.
	if (ulFoundObj < 1) {
		return false;
	}

    return true;
}
//--------------------------------------------------------------------------
//TODO: asGetDataObject
char *CEToken::asGetDataObject(unsigned long int ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/) {
    //const std::auto_ptr<unsigned char> pAutoBuff(unsigned char(0));
    //const std::auto_ptr<unsigned char> pAutoBuff(new unsigned char[10]);

    unsigned long int  ulRV = CKR_OK;
    unsigned char     *pRes = NULL;
 
    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRV = pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + asEtokenErrorString(ulRV));
        return NULL;
    }

    //-------------------------------------
    //логинимся
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
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
	ulRV = pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjectsInit ошибка ---> " + asEtokenErrorString(ulRV));
        return NULL;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRV = pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjects ошибка ---> " + asEtokenErrorString(ulRV));
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
        ulRV = pFunctionList->C_GetAttributeValue(hSession, hObject, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
        if (ulRV != CKR_OK) {
            MSG_WARNING("C_GetAttributeValue ошибка ---> " + asEtokenErrorString(ulRV));
            goto lDone;
        }

        unsigned long int ulApplicationLen = pDataTamplate[0].ulValueLen;
        unsigned char    *pszApplication   = new unsigned char[ulApplicationLen];
        pDataTamplate[0].pValue = pszApplication;

        unsigned long int ulLabelLen	   = pDataTamplate[1].ulValueLen;
        unsigned char    *pszLabel         = new unsigned char[ulLabelLen];
        pDataTamplate[1].pValue = pszLabel;

        unsigned long int ulValueLen       = pDataTamplate[2].ulValueLen;
        unsigned char    *pszValue	       = new unsigned char[ulValueLen];
        pDataTamplate[2].pValue = pszValue;


        //-------------------------------------
        //получаем данные   //если CKA_LABEL == 3_Test_Login (выводит лишний символ)
        ulRV = pFunctionList->C_GetAttributeValue(hSession, hObject, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
        if (ulRV != CKR_OK) {
            MSG_WARNING("C_GetAttributeValue ошибка ---> " + asEtokenErrorString(ulRV));

            delete[] pszApplication;
            delete[] pszLabel;
            delete[] pszValue;

            goto lDone;
        }

        //-------------------------------------
        //формируем возвращяемую строку
        unsigned long int ulResLen = strlen("CKA_APPLICATION|") + strlen(pszApplication) + 2 +
                                     strlen("CKA_LABEL|")       + strlen(pszLabel)       + 2 +
                                     strlen("CKA_VALUE|")       + strlen(pszValue)       + 3;

        pRes = new unsigned char[ulResLen];
                                                 
        _mbsncpy(pRes, "CKA_APPLICATION|", sizeof("CKA_APPLICATION|"));
        _mbsncat(pRes, pszApplication,     ulApplicationLen          );
        _mbsncat(pRes, "\r\n",             sizeof("\r\n")            );

        _mbsncat(pRes, "CKA_LABEL|",       sizeof("CKA_LABEL|")      );
        _mbsncat(pRes, pszLabel,           ulLabelLen                );
        _mbsncat(pRes, "\r\n",             sizeof("\r\n")            );

        _mbsncat(pRes, "CKA_VALUE|",       sizeof("CKA_VALUE|")      );
        _mbsncat(pRes, pszValue,           ulValueLen                );
        _mbsncat(pRes, "\r\n",             sizeof("\r\n")            );

        delete[] pszApplication;
        delete[] pszLabel;
        delete[] pszValue;

        goto lDone;
	}

lDone:
    //-------------------------------------
    //Clean up the search.
    ulRV = pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjectsFinal ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

    if (pRes != NULL) {
        return pRes;
    } else {
        return NULL;
    }
}
//--------------------------------------------------------------------------
//TODO: bCreateDataObject
bool CEToken::bCreateDataObject (unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/, unsigned char *pszLabel, unsigned char *pszValue) {
    unsigned long int  ulRV = CKR_OK;

	//-------------------------------------
	//открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

	ulRV = pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + asEtokenErrorString(ulRV));
        return false;
    }

	//-------------------------------------
	//логинимся
	ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
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

    ulRV = pFunctionList->C_CreateObject(hSession, pDataTamplate, sizeof (pDataTamplate) / sizeof (pDataTamplate[0]), &hObject);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_CreateObject ошибка ---> " + asEtokenErrorString(ulRV));
        return false;
    }

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

	return true;
}
//--------------------------------------------------------------------------
//TODO: bDeleteDataObject
bool CEToken::bDeleteDataObject(unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/) {
    unsigned long int  ulRV = CKR_OK;
    bool               bRes = false;

    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRV = pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + asEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
    }

    //-------------------------------------
    //логинимся
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
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
	ulRV = pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjectsInit ошибка ---> " + asEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRV = pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjects ошибка ---> " + asEtokenErrorString(ulRV));
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
	ulRV = pFunctionList->C_DestroyObject(hSession, hObject);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_DestroyObject ошибка ---> " + asEtokenErrorString(ulRV));
        bRes = false;
        goto lDone;
	}

    bRes = true;
    goto lDone;

lDone:
    //-------------------------------------
    //Clean up the search.
    ulRV = pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjectsFinal ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: bChangeDataObject
bool CEToken::bChangeDataObject(unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/, unsigned char *pszNewLabel, unsigned char *pszNewValue) {
    unsigned long int  ulRV = CKR_OK;
    bool               bRes = false;
    unsigned char     *pRes = NULL;
 
    //-------------------------------------
    //открываем сессию
	CK_SESSION_HANDLE hSession     = NULL;
    size_t            ulUserPINLen = strlen(pszUserPIN);

    ulRV = pFunctionList->C_OpenSession(ulSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка ---> " + asEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
    }

    //-------------------------------------
    //логинимся
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pszUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
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
	ulRV = pFunctionList->C_FindObjectsInit(hSession, pDataTamplate, sizeof(pDataTamplate) / sizeof(pDataTamplate[0]));
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjectsInit ошибка ---> " + asEtokenErrorString(ulRV));
        bRes = false;
        return bRes;
	}

    //-------------------------------------
	//ищем объект с нужным шаблоном (There should be only a single match as there is only one on the eToken)
	ulRV = pFunctionList->C_FindObjects(hSession, &hObject, 1, &ulFoundObj);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjects ошибка ---> " + asEtokenErrorString(ulRV));
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

        ulRV = pFunctionList->C_SetAttributeValue(hSession, hObject, pNewDataTemplate, sizeof(pNewDataTemplate) / sizeof(pNewDataTemplate[0]));
        if (ulRV != CKR_OK) {
            MSG_WARNING("C_SetAttributeValue ошибка ---> " + asEtokenErrorString(ulRV));
            bRes = false;
            goto lDone;
        }

        bRes = true;
        goto lDone;
    }        

lDone:
    //-------------------------------------
    //Clean up the search.
    ulRV = pFunctionList->C_FindObjectsFinal(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_FindObjectsFinal ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: bClearDataObject
bool CEToken::bClearDataObject(unsigned long ulSlotId, unsigned char *pszUserPIN, unsigned char *pszObjectName/*ID*/) {
    return bChangeDataObject(ulSlotId, pszUserPIN, pszObjectName/*ID*/, "", "");
}
//--------------------------------------------------------------------------













/**********************************************************************
*	Сертификаты
*
***********************************************************************/

//---------------------------------------------------------------------------
//TODO: asGetCertificate (Сертификат)
AnsiString CEToken::asGetCertificate(DWORD dwSlotId) {
	if (!bWasInit) {return "";}
		
	unsigned long int      ulRV          = CKR_OK;
	AnsiString asCertificate = "";
	
	//Открыть сессию и получить сертификат с токена
	CK_SESSION_HANDLE session;
	ulRV = pFunctionList->C_OpenSession (dwSlotId, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &session);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_OpenSession ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}                       

	//Найти хэндлы сертификата
	//--CK_BBOOL bFalse    = 0;
	CK_BBOOL bTrue     = 1;
	CK_ULONG classType = CKO_CERTIFICATE;
	CK_ULONG certType  = CKC_X_509;

	CK_ATTRIBUTE cert_template[]  = { 
		{CKA_CLASS,            &classType , sizeof(classType)},
		{CKA_CERTIFICATE_TYPE, &certType,   sizeof(certType) },
		{CKA_TOKEN,            &bTrue,      sizeof (bTrue)   },
	};

	CK_OBJECT_HANDLE hObject;
	CK_ULONG         foundObjects = 0;
	
	ulRV = pFunctionList->C_FindObjectsInit(session, cert_template,sizeof(cert_template)/sizeof(cert_template[0]));
	if (ulRV == CKR_OK) {
		bool firstTime = true;	
	    while ((pFunctionList->C_FindObjects(session, &hObject, 1, &foundObjects) == CKR_OK) && foundObjects > 0) {
			if (firstTime) {
		        //--printf ("<List of certificate information>\n");
		        firstTime = false;
	        }

			//Получить сертификат запрашивающей стороны, subject, значение атрибутов 
			CK_ATTRIBUTE cert_template[] = {
				{CKA_LABEL, NULL, 0},
				{CKA_VALUE, NULL, 0},
			};

			ulRV = pFunctionList->C_GetAttributeValue(session, hObject, cert_template, sizeof(cert_template) / sizeof(cert_template[0]));
			if (ulRV == CKR_OK) {
				int certLabelLen = cert_template[0].ulValueLen;
				BYTE* labelValue = new BYTE [certLabelLen];
				cert_template[0].pValue = labelValue;

				int certValueLen = cert_template[1].ulValueLen;
				BYTE* certValue = new BYTE [certValueLen];
				cert_template[1].pValue = certValue;

				ulRV = pFunctionList->C_GetAttributeValue(session, hObject, cert_template, sizeof(cert_template) / sizeof(cert_template[0]));
				if (ulRV == CKR_OK) {
					//--printf ("Label: %.*s\n", certLabelLen,labelValue);

					//Сертификат написан в ASN-1 формате, используем Windows Crypt32 API, чтобы показать его
					//-----void displaysCertificate(BYTE* certValue, int certValueLen)
					//----displaysCertificate(certValue,certValueLen);					
						
					char pszNameString[256]; 
					PCCERT_CONTEXT pCertContext = NULL; 

				    //Создать контекст сертификата
					if ((pCertContext = CertCreateCertificateContext(PKCS_7_ASN_ENCODING | X509_ASN_ENCODING, certValue, certValueLen)) != NULL) {	/*было =*/
						//Получить дружественное имя сертификата
						if (CertGetNameString(pCertContext, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0, NULL, pszNameString, sizeof(pszNameString)) != 0) {
							//--printf ("Subject Name: %s\n", pszNameString);
/*----------------------*/							DEBUG_(pszNameString);
						}
						//Когда закончили освобождаем контекст сертификата
						CertFreeCertificateContext(pCertContext);
					}				
					
					
					
					
					

				} 
				
		        delete []labelValue; 
		        delete []certValue;
			}
	    }
	    pFunctionList->C_FindObjectsFinal(session);
		//Закрыть сессию
		pFunctionList->C_CloseSession (session);
	}
	
	return asCertificate;
}
//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
//TODO: bCreateSelfCertificate

// STL
#include <string>
#include <iostream>
using namespace std;

#define ET_PROVIDER "eToken Base Cryptographic Provider"
#define CONTAINER_NAME " (Self Sign Certificate Container)"

bool CEToken::bCreateSelfCertificate(char *pszReaderName, char *pucUserPIN, char *pszSubject, char *pszOrganization, char *pszCountry) {
	//--("Usage: CreateSelfCertificate <reader name> <password>"); 
//--	char *readerName = pszReaderName;
//--	char *password   = pucUserPIN;
//--
//--	//Start to create Self Sign Certificate
//--    //Certifcate Subject
//--    char Subject[MAX_PATH];
//--
//--    //Certifcate Organization
//--    char Organization[MAX_PATH];
//--
//--    //Certifcate Country
//--    char Country[MAX_PATH];

    char X500Name[1024];
    sprintf(X500Name, "CN=\"%s\",O=\"%s\",C=\"%s\"", pszSubject, pszOrganization, pszCountry);	//DEBUG_(X500Name);
    
    //Pass user password, reader name and KC name to prevent select token and login dialog box.
    //Format: [reader-name{{password}}]=MyKeyContainer
    string certKCname;
    certKCname += pszSubject;
    certKCname += CONTAINER_NAME;
    
    string kcname = "[";
    kcname += pszReaderName;
    kcname += "{{"; 
    kcname += pucUserPIN; 
    kcname += "}}]="; 
    kcname += certKCname; 	//DEBUG_(X500Name);
    
    char szProvider[260] = {ET_PROVIDER};
DEBUG_("xxxxxxxxxx");
    //Get handle to eToken CSP 
    HCRYPTPROV hProv = NULL; 
    if (! ::CryptAcquireContext(&hProv, kcname.c_str(), szProvider, PROV_RSA_FULL, 0)) {
		if ((unsigned int)GetLastError() != NTE_EXISTS) {
			if (!::CryptAcquireContext(&hProv, kcname.c_str(), szProvider, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
                MSG_WARNING("CryptAcquireContext failed to create new key set...");
				return false;
			}
		} else {
            MSG_WARNING("CryptAcquireContext failed and key container exists...");
            return false;
		}
    }
DEBUG_("xxxxxxxxxx");
	//--return false;

    
    //Handle to RSA Gen key pair
    HCRYPTKEY hKeyExchange = NULL; 
    //Generate RSA exchange key pair 
    if (! ::CryptGenKey(hProv, AT_KEYEXCHANGE, 0, &hKeyExchange)) {
		MSG_WARNING("CryptGenKey failed to create AT_KEYEXCHANGE key...");
        return false;
    }
    
    CERT_NAME_BLOB certName = {0};
    certName.cbData = 0;
    certName.pbData = NULL;
    //\\char* dn = "CN=\"John Smite\",O=\"Aladdin Company\"";
    
    //Prepair certificate name in X509 format 
    if (! ::CertStrToName(
					X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
					X500Name, //dn
					CERT_OID_NAME_STR,
					NULL,
					NULL, &certName.cbData,
					NULL))
    {
		MSG_WARNING("CertStrToName with NULL failed...");
        return false;
    }
    certName.pbData = (PBYTE) malloc(certName.cbData);
    if (! ::CertStrToName(
					X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 
					X500Name, //dn
					CERT_OID_NAME_STR,
					NULL,
					certName.pbData, &certName.cbData,
					NULL))
    {
        free(certName.pbData);
		MSG_WARNING("CertStrToName failed...");
        return false;
    }

    WCHAR szwContainer[260];
    WCHAR szwProvider[260];
    
    //Convert container name and provider name to unicode.
    int i = MultiByteToWideChar(0, 0, certKCname.c_str(), - 1, szwContainer, 260);
    if (i == 0)	{
		MSG_WARNING("MultiByteToWideChar (container name) failed ...");
		return false;
    }
      
    i = MultiByteToWideChar(0, 0, szProvider, - 1, szwProvider, 260);
    if (i == 0) {
		MSG_WARNING("MultiByteToWideChar (provider name) failed ...");
		return false;
    }
    
    CRYPT_KEY_PROV_INFO keyinfo;
    memset(&keyinfo, 0x00, sizeof(CRYPT_KEY_PROV_INFO));
    keyinfo.pwszContainerName = szwContainer;
    keyinfo.pwszProvName      = szwProvider;
    keyinfo.dwProvType        = PROV_RSA_FULL;
    keyinfo.dwKeySpec         = AT_KEYEXCHANGE;
    
    SYSTEMTIME cs;
    GetSystemTime(&cs);
    cs.wYear += 1;
      
	CRYPT_ALGORITHM_IDENTIFIER  signatureAlgorithm;
	memset(&signatureAlgorithm, 0, sizeof(CRYPT_ALGORITHM_IDENTIFIER));
	signatureAlgorithm.pszObjId = szOID_RSA_SHA1RSA; 
    
	//Handle to certificate context.
	PCCERT_CONTEXT pCertCtx = NULL; 
    
	//Create Self Sign Certificate 
	pCertCtx = CertCreateSelfSignCertificate(hProv, &certName, 0, &keyinfo, &signatureAlgorithm, NULL, &cs, NULL);
	free(certName.pbData);
	if (!pCertCtx) {
		MSG_WARNING("CertCreateSelfSignCertificate failed...");
		return false;
	}
    
    //Set Certificate context to key handle; 
	if (! ::CryptSetKeyParam(hKeyExchange, KP_CERTIFICATE, pCertCtx->pbCertEncoded, 0)) {
		MSG_WARNING("CryptSetKeyParam  failed...");
		return false;
	}
    
	//Free Certificate, Key and CSP handles 
	if (pCertCtx) {
		CertFreeCertificateContext(pCertCtx);
	}
	if (hKeyExchange) {
		CryptDestroyKey(hKeyExchange);
	}
	if (hProv) {
		CryptReleaseContext(hProv, 0);
	}
    
    //Creation of Self Sign Certificate successful
    return true;
}
//---------------------------------------------------------------------------
//TODO: dwSelectSlot
#include <memory.h>
#include <string.h>

#include <algorithm>
using namespace std;

//Global variables. 
CK_FUNCTION_LIST_PTR   pFunctionList;
CK_C_GetFunctionList   pGFL  = 0;
CK_SESSION_HANDLE      session;
CK_SLOT_ID*            slots;
unsigned long          slot_count;

unsigned long CEToken::dwSelectSlot(char* readerName) {
    unsigned long int ulRV = CKR_OK;

	//Get all the occupied slots.
	unsigned long slot_index = 0;

    //Get all the occupied slots
	ulRV = pFunctionList->C_GetSlotList(true, NULL, &slot_count);
	if (ulRV == CKR_OK) {
		if (slot_count < 1)	{
			//--leave ("No eToken is available.\n");
		}

		slots = new CK_SLOT_ID [slot_count];
		ulRV = pFunctionList->C_GetSlotList (true, slots, &slot_count);
		if (ulRV != CKR_OK) {
			//--leave ("C_GetSlotList failed...\n");
		}
	} else {
		//--leave ("C_GetSlotList failed...\n");
	}
  
	//Get the selected slot information.
	bool bFound = false;
	std::transform(readerName, readerName + strlen(readerName), readerName, tolower);
	for (slot_index; slot_index < slot_count; slot_index++)	{
		CK_SLOT_INFO slot_info;
		
		ulRV = pFunctionList->C_GetSlotInfo (slots[slot_index], &slot_info);
		if (ulRV != CKR_OK)	{
			//--leave ("C_GetSlotInfo failed.\n");
		}
	   	std::transform(slot_info.slotDescription,slot_info.slotDescription + sizeof(slot_info.slotDescription),slot_info.slotDescription,tolower);
	    if (memcmp((void*)slot_info.slotDescription, readerName, min(strlen(readerName), sizeof(slot_info.slotDescription))) == 0) {    
			bFound = true;
			break;  
	    }
	}
	return bFound? slot_index : 0; //If not found, work with slot 0.
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//TODO: vGenKeyPair
void CEToken::vGenKeyPair() {
////////    unsigned long int ulRV = CKR_OK;
////////    
////////    CK_BBOOL         bFalse   = 0;
////////    CK_BBOOL         bTrue    = 1;
////////    CK_KEY_TYPE      key_type = CKK_RSA;
////////
////////    CK_CHAR label_public[]  = {"My public key"};  //Label of public key.
////////    CK_CHAR label_private[] = {"My private key"}; //Label of private key.
////////
////////    //Setup public key attributes.
////////    CK_OBJECT_CLASS  class_public_key  = CKO_PUBLIC_KEY;
////////    CK_ULONG         vecModulusBits[]  = {1024};
////////    CK_BYTE          public_exponent[] = { 0x01, 0x00, 0x01 };
////////
////////    CK_ATTRIBUTE public_key_template[] = {
////////        {CKA_CLASS,           &class_public_key,  sizeof (class_public_key) },
////////        {CKA_LABEL,           label_public,       sizeof (label_public)     },
////////        {CKA_KEY_TYPE,        &key_type,          sizeof (key_type)         },
////////        {CKA_TOKEN,           &bTrue,             sizeof (bTrue)            },
////////        {CKA_PRIVATE,         &bFalse,            sizeof (bFalse)           },
////////        {CKA_MODULUS_BITS,    &vecModulusBits[0], sizeof (vecModulusBits[0])},
////////        {CKA_PUBLIC_EXPONENT, &public_exponent,   sizeof (public_exponent)  },
////////    };
////////
////////    //Setup private key attributes.
////////    CK_OBJECT_CLASS  class_private_key = CKO_PRIVATE_KEY;
////////    CK_ATTRIBUTE private_key_template[] = {
////////        {CKA_CLASS,    &class_private_key, sizeof (class_private_key)},
////////        {CKA_LABEL,    label_private,      sizeof (label_private)    },
////////        {CKA_KEY_TYPE, &key_type,          sizeof (key_type)         },
////////        {CKA_TOKEN,    &bTrue,             sizeof (bTrue)            },
////////        {CKA_PRIVATE,  &bTrue,             sizeof (bTrue)            },
////////    };
////////
////////    //Setup mechanism to generate RSA key pair.
////////    CK_MECHANISM mechanism;
////////    memset (&mechanism, 0, sizeof (mechanism));
////////    mechanism.mechanism = CKM_RSA_PKCS_KEY_PAIR_GEN;
////////
////////    CK_OBJECT_HANDLE public_key;
////////    CK_OBJECT_HANDLE private_key;
////////
////////	//Setup a PKCS#11 attribute list for constructing the public user information that will be put on the eToken
////////	CK_OBJECT_CLASS  class_data    = CKO_DATA;
////////	CK_CHAR          app_name[]    = {"eToken"};
////////	static CK_CHAR   user_object[] = {"ISP User Information"};
////////	CK_CHAR          user_name[]   = {"John_Smith"};
////////
////////	CK_ATTRIBUTE pUser[] = {
////////        {CKA_CLASS,        &class_data,    sizeof (class_data) },
////////        {CKA_TOKEN,        &bTrue,         sizeof (bTrue)      },
////////        {CKA_APPLICATION,  app_name,       sizeof (app_name)   },
////////        {CKA_LABEL,        user_object,    sizeof (user_object)},
////////        {CKA_VALUE,        user_name,      sizeof (user_name)  },
////////	};
////////  
////////    //Try to find the two keys using the find_object utility function if it exists, or generate a new key pair.
////////    private_key = hFindObject(session, private_key_template, 1);
////////    public_key  = hFindObject(session, public_key_template,  1);
////////
////////    if (!(public_key && private_key))  {
////////        //--printf ("Wait for RSA PKCS#11 key pair generation ... \n");
////////
////////        ulRV = pFunctionList->C_GenerateKeyPair(session, &mechanism, public_key_template, 7, private_key_template, 5, &public_key, &private_key);
////////		if (ulRV != CKR_OK) {
////////            pFunctionList->C_Logout(session);
////////            pFunctionList->C_CloseSession(session);
////////            //--leave ("C_GenerateKeyPair failed.  Please run InitToken first.");
////////        }
////////    }
}
//---------------------------------------------------------------------------











//---------------------------------------------------------------------------
//TODO: bInitializeToken
/*
	Usage:   InitToken <reader-name> <format-password> <user-password>  
	Example: InitToken "AKS ifdh 0" 1234567890 password
*/
bool CEToken::bInitializeToken(const AnsiString& asFormatPass, const AnsiString& asUserPass) {
    unsigned long int                  ulRV     = CKR_OK;
	CK_SESSION_HANDLE      hSession = NULL;

    //--char *readerName     = argv[1];
////	char *formatPassword = {"2222"};
////	char *userPassword   = {"1111"};

//--    AnsiString asFormatPass = "1111";
//--    AnsiString asNewPass    = "2222";
	
	//--printf("Command line params: \n");
	//--printf(" reader name(%s)\n", readerName);
	//--printf(" format password(%s)\n", formatPassword);
	//--printf(" user password(%s)\n",   userPassword);
	//Load and initialize the PKCS#11 library.
	//--bLoadPKCS11();	//--init();

	//Insert command line argument for reader name ("AKS ifdh n").
	/*is never used: int slot_index = 0*/;	//--selectSlot(readerName);
    
	//инициализируем токен (Initialize token with format password);
	CK_CHAR token_label[] = {
		"eToken"
	};

	ulRV = pFunctionList->C_InitToken(0/*slots[slot_index]*/, asFormatPass.c_str()/*CK_CHAR_PTR(formatPassword)*/, asFormatPass.Length()/*strlen(formatPassword)*/, token_label);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_InitToken ошибка.\n");
		return false;
	}

    //открываем сессию для чтения/записи на eToken 
	ulRV = pFunctionList->C_OpenSession(0/*slots[slot_index]*/, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_OpenSession ошибка.\n");
        return false;
    }

    //логинимся как SO с паролем formatPassword
    /* Security Officer     #define CKU_SO    0 */
    /* Normal user          #define CKU_USER  1 */
	ulRV = pFunctionList->C_Login(hSession, CKU_SO, asFormatPass.c_str()/*CK_CHAR_PTR(formatPassword)*/, asFormatPass.Length()/*strlen(formatPassword)*/);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_Login ошибка.\n");
        return false;
    }

    //инициализируем USER PIN паролем userPassword
	ulRV = pFunctionList->C_InitPIN (hSession, asUserPass.c_str()/*CK_CHAR_PTR(userPassword)*/, asUserPass.Length()/*strlen(userPassword)*/);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_InitPIN ошибка.\n");
        return false;
    }

    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_Logout ошибка.\n");
        return false;
    }

//    //проверяем новый USER PIN.
//    printf ("Logging in to eToken as USER with - %s \n", userPassword);
//    if (CKR_OK != pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(userPassword), strlen(userPassword))) {
//        MSG_WARNING("C_Login ошибка.\n");
//        return false;
//    }
//  
//    //Show how to generate RSA key pair.
//    //--genKeyPair();
//
//    //делогинимся
//    if (CKR_OK != pFunctionList->C_Logout (hSession)) {
//        MSG_WARNING("C_Logout ошибка.\n");
//        return false;
//    }

    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
	if (ulRV != CKR_OK) {
        MSG_WARNING("C_CloseSession ошибка.\n");
        return false;
    }                       

    return true;
}
//---------------------------------------------------------------------------
//TODO: dwLocateToken
DWORD CEToken::dwLocateToken() {
/*	DWORD dwSlots  = 1;
	DWORD dwSlotID = 0;
	if (CKR_OK != pFunc->C_GetSlotList(true, &dwSlotID, &dwSlots)) {
		MSG_WARNING("C_GetSlotList failed");
		return TOKEN_NON_PRESENT;
	}
	if (dwSlots < 1) {
		MSG_WARNING("No eToken inserted");
		return TOKEN_NON_PRESENT;
	}
	return dwSlotID;*/
    return false;
}
//---------------------------------------------------------------------------
//TODO: bCheckPinPolicy
bool CEToken::bCheckPinPolicy(CK_SESSION_HANDLE	hSession, CK_OBJECT_HANDLE hObject) {
/*	unsigned long int ulRV = CKR_OK;
	
	CK_ULONG minPinAge   = 0;
	CK_ULONG maxPinAge   = 0;
	CK_ULONG warnPeriod  = 0;
	CK_ULONG pinLen      = 0;
	CK_ULONG historySize = 0;
	CK_BBOOL mixChars    = CK_FALSE;

	CK_ATTRIBUTE pTamplate[] = {
		{ETCKA_PIN_MIN_AGE,           &minPinAge,   sizeof(minPinAge)  },
		{ETCKA_PIN_MAX_AGE,          &maxPinAge,   sizeof(maxPinAge)},
		{ETCKA_PIN_WARN_PERIOD, &warnPeriod,  sizeof(warnPeriod)   },
		{ETCKA_PIN_MIN_LEN,            &pinLen,      sizeof(pinLen)           },
		{ETCKA_PIN_HISTORY_SIZE,   &historySize, sizeof(historySize)   },
		{ETCKA_PIN_MIX_CHARS,       &mixChars,    sizeof(mixChars)     }
	};

	if (ulRV = pFunc->C_GetAttributeValue(hSession, hObject, pTamplate, 6)) {
		MSG_WARNING("Failed to get PIN policy information.");
		return false;
	}

	AnsiString asPinPolicyData = "";
	asPinPolicyData.sprintf("\nNew PIN policy settings:\n");
	asPinPolicyData.sprintf("PIN maximum age(%i)\n",maxPinAge);
	asPinPolicyData.sprintf("PIN minimum age(%i)\n",minPinAge);
	asPinPolicyData.sprintf("PIN warning period(%i)\n",warnPeriod);
	asPinPolicyData.sprintf("Minimum PIN length(%i)\n",pinLen);
	asPinPolicyData.sprintf("Maximum PIN history size(%i)\n",historySize);
	asPinPolicyData.sprintf("PIN mixed characters(%i)\n",mixChars);
	ShowMessage(asPinPolicyData);

	if (minPinAge == m_minPinAge && maxPinAge == m_maxPinAge && warnPeriod == m_warnPeriod && pinLen == m_pinLen && historySize == m_historySize && mixChars == m_mixChars) {
		return true;
	}	
	
	return false;*/
    return false;
}
//---------------------------------------------------------------------------
//TODO: ulGetSlotInfo
unsigned long CEToken::ulGetSlotInfo(DWORD dwSlotId) {
	     unsigned long int          ulRV               = CKR_OK;
    const unsigned long culKnownInfo       = 0;
    const unsigned long culTokenNotPresent = 1;
    const unsigned long culTokenPresent    = 3;
    const unsigned long culRemovableDevice = 2;
    const unsigned long culHardwareSlot    = 4;
	
	//-------------------------------------
	//если токен был вынят - выход
    if (!bWasInit) {return culKnownInfo;}

	CK_SLOT_INFO slot_info;
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return culKnownInfo;
	}

	//-------------------------------------
	//Токен извлечен (CKF_TOKEN_PRESENT     0x00000001)
	if (!(slot_info.flags & CKF_TOKEN_PRESENT)) {
		return culTokenNotPresent;
	}

	//-------------------------------------
	//Токен - съёмное устройство (CKF_REMOVABLE_DEVICE  0x00000002)
	if (!(slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		return culRemovableDevice;
	}

    //-------------------------------------
	//Токен вставлен (CKF_TOKEN_PRESENT     0x00000001)
    if ((slot_info.flags & CKF_TOKEN_PRESENT)) {
        return culTokenPresent;
	}

	//-------------------------------------
	//Токен - хадверный слот (CKF_HW_SLOT   0x00000004)
	if (!(slot_info.flags & CKF_HW_SLOT)) {
		return culHardwareSlot;
	}

    return culKnownInfo;
}
//---------------------------------------------------------------------------









//---------------------------------------------------------------------------
//DONE:  asGetTokenInfo

/**********************************************************************
*   asGetTokenInfo() - получить всю инфу о токене
*
*   Возвращаемое значение (формат):  
*	имя_параметр1=значение\n
*       имя_параметр2=значение\n
*       ...
*       имя_параметрN=значение\n
*
***********************************************************************/

AnsiString CEToken::asGetTokenInfo(DWORD dwSlotId) {
	unsigned long int ulRV = CKR_OK;
	
	//-------------------------------------
	//если токен был вынят - выход
    if (!bWasInit) {return "";}

	CK_SLOT_INFO slot_info;
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}
	
	//-------------------------------------
	//получаем информацию
	AnsiString asAllInfo = "";

	asAllInfo += asGetPRODUCT_NAME                      (dwSlotId);
	asAllInfo += asGetMODEL                             (dwSlotId);
	asAllInfo += asGetFW_VERSION                        (dwSlotId);
	asAllInfo += asGetFW_REVISION                       (dwSlotId);
	asAllInfo += asGetHW_VERSION                        (dwSlotId);
	asAllInfo += asGetHW_INTERNAL                       (dwSlotId);
	asAllInfo += asGetPRODUCTION_DATE                   (dwSlotId);
	asAllInfo += asGetCASE_MODEL                        (dwSlotId);
	asAllInfo += asGetTOKEN_ID                          (dwSlotId);
	asAllInfo += asGetCARD_ID                           (dwSlotId);
	asAllInfo += asGetCARD_TYPE                         (dwSlotId);
	asAllInfo += asGetCARD_VERSION                      (dwSlotId);
	asAllInfo += asGetSERIAL                            (dwSlotId);
	asAllInfo += asGetCOLOR                             (dwSlotId);
	asAllInfo += asGetHAS_BATTERY                       (dwSlotId);
	asAllInfo += asGetHAS_LCD                           (dwSlotId);
	asAllInfo += asGetHAS_USER                          (dwSlotId);
	asAllInfo += asGetHAS_SO                            (dwSlotId);
	asAllInfo += asGetFIPS                              (dwSlotId);
	asAllInfo += asGetFIPS_SUPPORTED                    (dwSlotId);
	asAllInfo += asGetINIT_PIN_REQ                      (dwSlotId);
	asAllInfo += asGetRSA_2048                          (dwSlotId);
	asAllInfo += asGetRSA_2048_SUPPORTED                (dwSlotId);
	asAllInfo += asGetHMAC_SHA1                         (dwSlotId);
	asAllInfo += asGetHMAC_SHA1_SUPPORTED               (dwSlotId);
	asAllInfo += asGetREAL_COLOR                        (dwSlotId);
	asAllInfo += asGetMAY_INIT                          (dwSlotId);
	asAllInfo += asGetLABEL                             (dwSlotId);
	asAllInfo += asGetMANUFACTURER_ID                   (dwSlotId);
	asAllInfo += asGetMODEL_2                           (dwSlotId);
	asAllInfo += asGetSERIAL_NUMBER                     (dwSlotId);
	asAllInfo += asGetHARDWARE_VERSION_MAJOR            (dwSlotId);
	asAllInfo += asGetHARDWARE_VERSION_MINOR            (dwSlotId);
	asAllInfo += asGetFIRMWARE_VERSION_MAJOR            (dwSlotId);
	asAllInfo += asGetFIRMWARE_VERSION_MINOR            (dwSlotId);
	asAllInfo += asGetSESSION_COUNT                     (dwSlotId);
	asAllInfo += asGetMAX_SESSION_COUNT                 (dwSlotId);
	asAllInfo += asGetMAX_RW_SESSION_COUNT              (dwSlotId);
	asAllInfo += asGetMIN_PIN_LEN                       (dwSlotId);
	asAllInfo += asGetMAX_PIN_LEN                       (dwSlotId);
	asAllInfo += asGetFREE_PUBLIC_MEMORY                (dwSlotId);
	asAllInfo += asGetTOTAL_PUBLIC_MEMORY               (dwSlotId);
	asAllInfo += asGetFREE_PRIVATE_MEMORY               (dwSlotId);
	asAllInfo += asGetTOTAL_PRIVATE_MEMORY              (dwSlotId);
	asAllInfo += asGetRANDOM_NUMBER_GENERATOR           (dwSlotId);
	asAllInfo += asGetIS_WRITE_PROTECTED                (dwSlotId);
	asAllInfo += asGetLOGIN_REQUIRED                    (dwSlotId);
	asAllInfo += asGetUSERS_PIN_IS_SET                  (dwSlotId);
	asAllInfo += asGetRESTORE_KEY_NOT_NEEDED            (dwSlotId);
	asAllInfo += asGetCLOCK_ON_TOKEN                    (dwSlotId);
	asAllInfo += asGetHAS_PROTECTED_AUTHENTICATION_PATH (dwSlotId);
	asAllInfo += asGetDUAL_CRYPTO_OPERATIONS            (dwSlotId);
	asAllInfo += asGetRSA_MECHANISM_MAX_KEY_SIZE        (dwSlotId);

    return asAllInfo;
}
//---------------------------------------------------------------------------
//TODO: asGetTokenInfoFast
char *CEToken::pszGetTokenInfoFast(unsigned long int ulSlotId) {
    unsigned long int    ulRV = CKR_OK;
    static unsigned char szRes[1024] = ""; strcpy(szRes, "");  //?????????

    //-------------------------------------
	//если токен был вынят - выход
    if (!bWasInit) {return "";}

	CK_SLOT_INFO siSI;
	ulRV = pFunctionList->C_GetSlotInfo(ulSlotId, &siSI);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	//Если токен существует в слоте - показать его информацию
	if (!(siSI.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (!(siSI.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (!(siSI.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//eTSAPI.h

	//-------------------------------------
    //CKA_SAPI_PRODUCT_NAME [eToken PRO] (1)  //OutString
    {
        const unsigned long int ulProductNameLen                = 256;
        unsigned char           szProductName[ulProductNameLen] = "";

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_PRODUCT_NAME, szProductName, ulProductNameLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG,     strlen(EMPTY_MSG));
        } else {
            _mbsncat(szRes, szProductName, strlen(szProductName));
            _mbsncat(szRes, "\n", 2);
        }
    }        

    //-------------------------------------
    //CKA_SAPI_MODEL [Token P0514 F4.2.5.4] (2)     //OutString
    {
        const unsigned long int ulModelLen          = 256;
        unsigned char           szModel[ulModelLen] = "";

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_MODEL, szModel, ulModelLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            _mbsncat(szRes, szModel,   strlen(szModel));
            _mbsncat(szRes, "\n", 2);
        }
    }

    //-------------------------------------
    //CKA_SAPI_FW_VERSION [0.4] (3)         //OutVersion
    {
        unsigned long int  ulFwVersionLen = sizeof(CK_VERSION) + 1;   //+1 символ на "."
        unsigned char     *pszFwVersion   = new unsigned char[ulFwVersionLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FW_VERSION, pszFwVersion, ulFwVersionLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG,    strlen(EMPTY_MSG));
        } else {
            //--CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
            //--printf("%d.%d\n", pV->major, pV->minor);
            CK_VERSION* pV = (CK_VERSION*)pTamplate->pValue;
            sprintf(pszFwVersion, "%d.%d", pV->major, pV->minor);

            _mbsncat(szRes, pszFwVersion, ulFwVersionLen);
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszFwVersion;
    }

    //-------------------------------------
    //CKA_SAPI_FW_REVISION [0] (4)      //OutDecimal
    {
        unsigned long int  ulFwRevisionLen = sizeof(unsigned long int);
        unsigned char     *pszFwRevision   = new unsigned char[ulFwRevisionLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FW_REVISION, pszFwRevision, ulFwRevisionLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG,     strlen(EMPTY_MSG));
        } else {
            //--printf("%d\n", *((int*)pAttr->pValue));
            sprintf(pszFwRevision, "%d", *((int*)pTamplate->pValue));

            _mbsncat(szRes, pszFwRevision, ulFwRevisionLen);
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszFwRevision;
    }

    //-------------------------------------
    //CKA_SAPI_HW_VERSION [1.2] (5)   //OutVersion
    {
        unsigned long int  ulHwVersionLen = sizeof(CK_VERSION) + 1;   //+1 символ на "."
        unsigned char     *pszHwVersion   = new unsigned char[ulHwVersionLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HW_VERSION, pszHwVersion, ulHwVersionLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG,    strlen(EMPTY_MSG));
        } else {
            //--CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
            //--printf("%d.%d\n", pV->major, pV->minor);
            CK_VERSION* pV = (CK_VERSION*)pTamplate->pValue;
            sprintf(pszHwVersion, "%d.%d", pV->major, pV->minor);

            _mbsncat(szRes, pszHwVersion, ulHwVersionLen);
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszHwVersion;
    }

    //-------------------------------------
    //CKA_SAPI_HW_INTERNAL [01 04  ... 01 04 ff] (6)  //OutArray
    {
        const unsigned long int ulHwInternalLen               = 256;
        unsigned char           szHwInternal[ulHwInternalLen] = "";

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HW_INTERNAL, szHwInternal, ulHwInternalLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG,    strlen(EMPTY_MSG));
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            unsigned char szTmp[3] = "";
            for (unsigned long int i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                _mbsncat(szRes, szTmp, 3);       //+3 = 2 байта + 1 пробел
             }

            _mbsncat(szRes, "\n", 2);
        }
    }

    //-------------------------------------
    //CKA_SAPI_PRODUCTION_DATE [27.08.2006] (7) //OutDate
    {
        unsigned long int  ulProductionDateLen = sizeof(CK_DATE) + 2;   //+2 символ на "."
        unsigned char     *pszProductionDate   = new unsigned char[ulProductionDateLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_PRODUCTION_DATE, pszProductionDate, ulProductionDateLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG,         strlen(EMPTY_MSG));
        } else {
            //--CK_DATE* d = (CK_DATE*)pTemplate->pValue;
            //--printf("%c%c.%c%c.%c%c%c%c\n", d->day[0], d->day[1], d->month[0], d->month[1], d->year[0], d->year[1], d->year[2], d->year[3]);
            CK_DATE* d = (CK_DATE*)pTamplate->pValue;
            sprintf(pszProductionDate, "%c%c.%c%c.%c%c%c%c", d->day[0], d->day[1], d->month[0], d->month[1], d->year[0], d->year[1], d->year[2], d->year[3]);

            _mbsncat(szRes, pszProductionDate, ulProductionDateLen);
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszProductionDate;
    }        

    //-------------------------------------
    //CKA_SAPI_CASE_MODEL [1] (8)   //OutDecimal
    {
        unsigned long int  ulCaseModelLen = sizeof(unsigned long int);
        unsigned char     *pszCaseModel   = new unsigned char[ulCaseModelLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CASE_MODEL, pszCaseModel, ulCaseModelLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%d\n", *((int*)pTemplate->pValue));
            sprintf(pszCaseModel, "%d", *((int*)pTamplate->pValue));

            _mbsncat(szRes, pszCaseModel, ulCaseModelLen);
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszCaseModel;
    }

    //-------------------------------------
    //CKA_SAPI_TOKEN_ID [0x4706a314] (9)    //OutHex
    {
        const unsigned long int  ulTokenIdLen            = 20;
        unsigned char            szTokenId[ulTokenIdLen] = "";

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_TOKEN_ID, szTokenId, ulTokenIdLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG,  strlen(EMPTY_MSG));
        } else {
            //--printf("0x%08x\n", *((unsigned int*)pAttr->pValue));
            sprintf(szTokenId, "0x%08x", *((unsigned int*)pTamplate->pValue));

            _mbsncat(szRes, szTokenId, strlen(szTokenId));
            _mbsncat(szRes, "\n", 2);
        }
    }
	
    
	//-------------------------------------
	//CKA_SAPI_CARD_ID [24 9c 9f 10 39 1d] (10)           //OutArray
    {
        const unsigned long int ulCardIdLen           = 256;
        unsigned char           szCardId[ulCardIdLen] = "";

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_ID, szCardId, ulCardIdLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            unsigned char szTmp[3] = "";
            for (unsigned long int i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                _mbsncat(szRes, szTmp, 3);       //+3 = 2 байта + 1 пробел
             }

            _mbsncat(szRes, "\n", 2);
        }
    }

    //-------------------------------------
    //CKA_SAPI_CARD_TYPE [1] (11)	//OutDecimal
    {
        unsigned long int  ulpCardTypeLen = sizeof(unsigned long int);
        unsigned char      *pCardType     = new unsigned char[ulpCardTypeLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_TYPE, pCardType, ulpCardTypeLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%d\n", *((int*)pAttr->pValue));
            sprintf(pCardType, "%d", *((int*)pTamplate->pValue));

            _mbsncat(szRes, pCardType,  strlen(pCardType));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pCardType;
    }

    //-------------------------------------
    //CKA_SAPI_CARD_VERSION [4.1] (12)	//OutVersion
    {
        unsigned long int  ulCardVersionLen = sizeof(CK_VERSION) + 1;   //+1 символ на "."
        unsigned char     *pszCardVersion   = new unsigned char[ulCardVersionLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_CARD_VERSION, pszCardVersion, ulCardVersionLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
            //--printf("%d.%d\n", pV->major, pV->minor);
            CK_VERSION* pV = (CK_VERSION*)pTamplate->pValue;
            sprintf(pszCardVersion, "%d.%d", pV->major, pV->minor);

            _mbsncat(szRes, pszCardVersion,  ulCardVersionLen);
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszCardVersion;
    }


    //-------------------------------------
    //CKA_SAPI_SERIAL [34 37 ... 20 20 20] (13)	//OutArray
    {
        const unsigned long int  ulSerialLen           = 256;
        unsigned char            szSerial[ulSerialLen] = "";

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_SERIAL, szSerial, ulSerialLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--for (CK_ULONG i=0; i<attr->ulValueLen; i++)
            //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
            unsigned char szTmp[3] = "";
            for (unsigned long int i = 0; i < pTamplate->ulValueLen; i ++) {
                sprintf(szTmp, "%02x ", ((BYTE*)(pTamplate->pValue))[i]);
                _mbsncat(szRes, szTmp, 3);       //+3 = 2 байта + 1 пробел
             }

            _mbsncat(szRes, "\n", 2);
        }
    }
	

    //-------------------------------------
    //CKA_SAPI_COLOR [0] (14)	//OutDecimal
    {
        unsigned long int  ulColorLen = sizeof(unsigned long int);
        unsigned char     *pszColor   = new unsigned char[ulColorLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_COLOR, pszColor, ulColorLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%d\n", *((int*)pAttr->pValue));
            sprintf(pszColor, "%d", *((int*)pTamplate->pValue));
        
            _mbsncat(szRes, pszColor,  ulColorLen);
            _mbsncat(szRes, "\n", 2);
        }
	
        delete[] pszColor;
    }
                                                                       

    //-------------------------------------
    //CKA_SAPI_HAS_BATTERY [да | нет] (15)	//OutBoolean
    {
        unsigned long int  ulHasBatteryLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszHasBattery   = new unsigned char[ulHasBatteryLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_BATTERY, pszHasBattery, ulHasBatteryLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszHasBattery, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszHasBattery,  strlen(pszHasBattery));
            _mbsncat(szRes, "\n", 2);
        }
	
        delete[] pszHasBattery;
    }        


    //-------------------------------------
    //CKA_SAPI_HAS_LCD [да | нет] (16)	//OutBoolean
    {
        unsigned long int  ulHasLCDLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszHasLCD   = new unsigned char[ulHasLCDLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_LCD, pszHasLCD, ulHasLCDLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszHasLCD, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszHasLCD,  strlen(pszHasLCD));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszHasLCD;
    }

    //-------------------------------------
    //CKA_SAPI_HAS_USER [да | нет] (17)	//OutBoolean
    {
        unsigned long int  ulHasUserLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszHasUser   = new unsigned char[ulHasUserLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_USER, pszHasUser, ulHasUserLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszHasUser, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszHasUser,  strlen(pszHasUser));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszHasUser;
    }

    //-------------------------------------
    //CKA_SAPI_HAS_SO [да | нет] (18)	//OutBoolean
    {
        unsigned long int  ulHasSOLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszHasSO   = new unsigned char[ulHasSOLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HAS_SO, pszHasSO, ulHasSOLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszHasSO, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszHasSO,  strlen(pszHasSO));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszHasSO;
    }

    //-------------------------------------
    //CKA_SAPI_FIPS [да | нет] (19)	//OutBoolean
    {
        unsigned long int  ulFipsLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszFips   = new unsigned char[ulFipsLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FIPS, pszFips, ulFipsLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszFips, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszFips,  strlen(pszFips));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszFips;
    }

    //-------------------------------------
    //CKA_SAPI_FIPS_SUPPORTED [да | нет] (20)	//OutBoolean
    {
        unsigned long int  ulFipsSupportedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszFipsSupported   = new unsigned char[ulFipsSupportedLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_FIPS_SUPPORTED, pszFipsSupported, ulFipsSupportedLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszFipsSupported, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszFipsSupported,  strlen(pszFipsSupported));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszFipsSupported;
    }

    //-------------------------------------
    //CKA_SAPI_INIT_PIN_REQ [да | нет] (21)	//OutBoolean
    {
        unsigned long int  ulInitPinReqLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszInitPinReq   = new unsigned char[ulInitPinReqLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_INIT_PIN_REQ, pszInitPinReq, ulInitPinReqLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszInitPinReq, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszInitPinReq,  strlen(pszInitPinReq));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszInitPinReq;
    }

    //-------------------------------------
    //CKA_SAPI_RSA_2048 [да | нет] (22)	//OutBoolean
    {
        unsigned long int  ulRSA2048Len = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszRSA2048   = new unsigned char[ulRSA2048Len];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_RSA_2048, pszRSA2048, ulRSA2048Len}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszRSA2048, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszRSA2048,  strlen(pszRSA2048));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszRSA2048;
    }

    //-------------------------------------
    //CKA_SAPI_RSA_2048_SUPPORTED [да | нет] (23)	//OutBoolean
    {
        unsigned long int  ulRSA2048SupportedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszRSA2048Supported   = new unsigned char[ulRSA2048SupportedLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_RSA_2048_SUPPORTED, pszRSA2048Supported, ulRSA2048SupportedLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszRSA2048Supported, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszRSA2048Supported,  strlen(pszRSA2048Supported));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszRSA2048Supported;
    }

    //-------------------------------------
    //CKA_SAPI_HMAC_SHA1 [да | нет] (24)	//OutBoolean
    {
        unsigned long int  ulHMACSHA1Len = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszHMACSHA1   = new unsigned char[ulHMACSHA1Len];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HMAC_SHA1, pszHMACSHA1, ulHMACSHA1Len}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszHMACSHA1, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszHMACSHA1,  strlen(pszHMACSHA1));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszHMACSHA1;
    }

    //-------------------------------------
    //CKA_SAPI_HMAC_SHA1_SUPPORTED [да | нет] (25)	//OutBoolean
    {
        unsigned long int  ulHMACSHA1SuppotedLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszHMACSHA1Suppoted   = new unsigned char[ulHMACSHA1SuppotedLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_HMAC_SHA1_SUPPORTED, pszHMACSHA1Suppoted, ulHMACSHA1SuppotedLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszHMACSHA1Suppoted, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszHMACSHA1Suppoted,  strlen(pszHMACSHA1Suppoted));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszHMACSHA1Suppoted;
    }

    //-------------------------------------
    //CKA_SAPI_REAL_COLOR [да | нет] (26)	//OutBoolean
    {
        unsigned long int  ulRealColorLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszRealColor   = new unsigned char[ulRealColorLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_REAL_COLOR, pszRealColor, ulRealColorLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszRealColor, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszRealColor,  strlen(pszRealColor));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszRealColor;
    }

    //-------------------------------------
    //CKA_SAPI_MAY_INIT [да | нет] (27)	//OutBoolean
    {
        unsigned long int  ulMayInitLen = sizeof(FALSE_MSG);  //FALSE_MSG >= TRUE_MSG
        unsigned char     *pszMayInit   = new unsigned char[ulMayInitLen];

        CK_ATTRIBUTE pTamplate[] = {
            {CKA_SAPI_MAY_INIT, pszMayInit, ulMayInitLen}
        };

        ulRV = /*f*/_SAPI_GetTokenInfo(ulSlotId, pTamplate, 1);
        if (ulRV != CKR_OK) {
            MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
            return "";
        }

        if (pTamplate->ulValueLen == 0) {
            _mbsncat(szRes, EMPTY_MSG, strlen(EMPTY_MSG));
        } else {
            //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
            sprintf(pszMayInit, "%s", *((CK_BBOOL*)pTamplate->pValue) ? TRUE_MSG : FALSE_MSG);

            _mbsncat(szRes, pszMayInit,  strlen(pszMayInit));
            _mbsncat(szRes, "\n", 2);
        }

        delete[] pszMayInit;
    }



    //-------------------------------------
    //pkcs11
    CK_TOKEN_INFO tiTI;

    ulRV = pFunctionList->C_GetTokenInfo(ulSlotId, &tiTI);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }

    //-------------------------------------
    //LABEL [eToken]     unsigned char[32]
    {
        //printf ("Label: %.32s\n",                 tiTI.label);
        _mbsncat(szRes, tiTI.label, sizeof(tiTI.label));
        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //MANUFACTURER_ID [Aladdin Ltd.]   unsigned char[32]
    {
        //printf ("Manufacturer: %.32s\n",          tiTI.manufacturerID);
        _mbsncat(szRes, tiTI.manufacturerID, sizeof(tiTI.manufacturerID));
        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //MODEL_2 [eToken] unsigned char[16]   ????--------------------
    {
        //printf ("Model: %.16s\n",                 tiTI.model);
        _mbsncat(szRes, tiTI.model, sizeof(tiTI.model));
        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //SERIAL_NUMBER [4706a314] unsigned char[16]  ---------------
    {
        //printf ("Serial number: %.16s\n",         tiTI.serialNumber);
        _mbsncat(szRes, tiTI.serialNumber, sizeof(tiTI.serialNumber));
        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //HARDWARE_VERSION_MAJOR [1]
    {
        unsigned char *pszHardwareVersionMajor = new unsigned char[lIntLen(tiTI.hardwareVersion.major)];

        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        sprintf(pszHardwareVersionMajor, "%d", tiTI.hardwareVersion.major);

        _mbsncat(szRes, pszHardwareVersionMajor,  strlen(pszHardwareVersionMajor));
        _mbsncat(szRes, "\n", 2);

        delete[] pszHardwareVersionMajor;
    }

    //-------------------------------------
    //HARDWARE_VERSION_MINOR [2]
    {
        unsigned char *pszHardwareVersionMinor = new unsigned char[lIntLen(tiTI.hardwareVersion.minor)];

        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        sprintf(pszHardwareVersionMinor, "%d", tiTI.hardwareVersion.minor);

        _mbsncat(szRes, pszHardwareVersionMinor,  strlen(pszHardwareVersionMinor));
        _mbsncat(szRes, "\n", 2);

        delete[] pszHardwareVersionMinor;
    }

    //-------------------------------------
    //FIRMWARE_VERSION_MAJOR [0]
    {
        unsigned char *pszFirmwareVersionMajor = new unsigned char[lIntLen(tiTI.firmwareVersion.major)];

        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        sprintf(pszFirmwareVersionMajor, "%d", tiTI.firmwareVersion.major);

        _mbsncat(szRes, pszFirmwareVersionMajor,  strlen(pszFirmwareVersionMajor));
        _mbsncat(szRes, "\n", 2);

        delete[] pszFirmwareVersionMajor;
    }

    //-------------------------------------
    //FIRMWARE_VERSION_MINOR [4]
    {
        unsigned char *pszFirmwareVersionMinor = new unsigned char[lIntLen(tiTI.firmwareVersion.minor)];

        //printf ("Version hardware/firmware: %d.%d, %d.%d\n", tiTI.hardwareVersion.major, tiTI.hardwareVersion.minor,  tiTI.firmwareVersion.major, tiTI.firmwareVersion.minor);
        sprintf(pszFirmwareVersionMinor, "%d", tiTI.firmwareVersion.minor);

        _mbsncat(szRes, pszFirmwareVersionMinor,  strlen(pszFirmwareVersionMinor));
        _mbsncat(szRes, "\n", 2);

        delete[] pszFirmwareVersionMinor;
    }

    //-------------------------------------
    //SESSION_COUNT [0] unsigned long
    {
        //printf ("Current session count: %d\n",    tiTI.ulSessionCount);
        unsigned char *pszSessionCount = new unsigned char[lIntLen(tiTI.ulSessionCount)];

        sprintf(pszSessionCount, "%d", tiTI.ulSessionCount);
        _mbsncat(szRes, pszSessionCount, strlen(pszSessionCount));
        _mbsncat(szRes, "\n", 2);

        delete[] pszSessionCount;

    }

    //-------------------------------------
    //MAX_SESSION_COUNT [0]  unsigned lon
    {
        //printf ("Maximum session count: %d\n",    tiTI.ulMaxSessionCount);
        unsigned char *pszMaxSessionCount = new unsigned char[lIntLen(tiTI.ulMaxSessionCount)];

        sprintf(pszMaxSessionCount, "%d", tiTI.ulMaxSessionCount);
        _mbsncat(szRes, pszMaxSessionCount, strlen(pszMaxSessionCount));
        _mbsncat(szRes, "\n", 2);

        delete[] pszMaxSessionCount;
    }

    //-------------------------------------
    //MAX_RW_SESSION_COUNT [0]
    {
        //printf ("Maximum RW session count: %d\n", tiTI.ulMaxRwSessionCount);
        unsigned char *pszMaxRwSessionCount = new unsigned char[lIntLen(tiTI.ulMaxRwSessionCount)];

        sprintf(pszMaxRwSessionCount, "%d", tiTI.ulMaxRwSessionCount);
        _mbsncat(szRes, pszMaxRwSessionCount, strlen(pszMaxRwSessionCount));
        _mbsncat(szRes, "\n", 2);

        delete[] pszMaxRwSessionCount;
    }

    //-------------------------------------
    //MIN_PIN_LEN [6...255]
    {
        //printf ("PIN length: [%d..%d]\n",         tiTI.ulMinPinLen,  tiTI.ulMaxPinLen);
        unsigned char *pszMinPinLen = new unsigned char[lIntLen(tiTI.ulMinPinLen)];

        sprintf(pszMinPinLen, "%d", tiTI.ulMinPinLen);
        _mbsncat(szRes, pszMinPinLen, strlen(pszMinPinLen));
        _mbsncat(szRes, "\n", 2);

        delete[] pszMinPinLen;
    }

    //-------------------------------------
    //MAX_PIN_LEN [6...255]
    {
        //printf ("PIN length: [%d..%d]\n",         tiTI.ulMinPinLen,  tiTI.ulMaxPinLen);
        unsigned char *pszMaxPinLen = new unsigned char[lIntLen(tiTI.ulMaxPinLen)];

        sprintf(pszMaxPinLen, "%d", tiTI.ulMaxPinLen);
        _mbsncat(szRes, pszMaxPinLen, strlen(pszMaxPinLen));
        _mbsncat(szRes, "\n", 2);

        delete[] pszMaxPinLen;
    }

    //-------------------------------------
    //FREE_PUBLIC_MEMORY [27721 bytes]
    {
        //printf ("Public memory: %d/%d bytes\n",   tiTI.ulFreePublicMemory,  tiTI.ulTotalPublicMemory);
        unsigned char *pszFreePublicMemory = new unsigned char[lIntLen(tiTI.ulFreePublicMemory)];

        sprintf(pszFreePublicMemory, "%d", tiTI.ulFreePublicMemory);
        _mbsncat(szRes, pszFreePublicMemory, strlen(pszFreePublicMemory));
        _mbsncat(szRes, "\n", 2);

        delete[] pszFreePublicMemory;
    }

    //-------------------------------------
    //TOTAL_PUBLIC_MEMORY [32768 bytes]
    {
        //printf ("Public memory: %d/%d bytes\n",   tiTI.ulFreePublicMemory,  tiTI.ulTotalPublicMemory);
        unsigned char *pszTotalPublicMemory = new unsigned char[lIntLen(tiTI.ulTotalPublicMemory)];

        sprintf(pszTotalPublicMemory, "%d", tiTI.ulTotalPublicMemory);
        _mbsncat(szRes, pszTotalPublicMemory, strlen(pszTotalPublicMemory));
        _mbsncat(szRes, "\n", 2);

        delete[] pszTotalPublicMemory;
    }

    //-------------------------------------
    //FREE_PRIVATE_MEMORY [27721 bytes]
    {
        //printf ("Private memory: %d/%d bytes\n",  tiTI.ulFreePrivateMemory, tiTI.ulTotalPrivateMemory);
        unsigned char *pszFreePrivateMemory = new unsigned char[lIntLen(tiTI.ulFreePrivateMemory)];

        sprintf(pszFreePrivateMemory, "%d", tiTI.ulFreePrivateMemory);
        _mbsncat(szRes, pszFreePrivateMemory, strlen(pszFreePrivateMemory));
        _mbsncat(szRes, "\n", 2);

        delete[] pszFreePrivateMemory;
    }

    //-------------------------------------
    //TOTAL_PRIVATE_MEMORY [32768 bytes]
    {
        //printf ("Private memory: %d/%d bytes\n",  tiTI.ulFreePrivateMemory, tiTI.ulTotalPrivateMemory);
        unsigned char *pszTotalPrivateMemory = new unsigned char[lIntLen(tiTI.ulTotalPrivateMemory)];

        sprintf(pszTotalPrivateMemory, "%d", tiTI.ulTotalPrivateMemory);
        _mbsncat(szRes, pszTotalPrivateMemory, strlen(pszTotalPrivateMemory));
        _mbsncat(szRes, "\n", 2);

        delete[] pszTotalPrivateMemory;
    }

    //-------------------------------------
    //RANDOM_NUMBER_GENERATOR [да | нет]
    {
        if (tiTI.flags & CKF_RNG) {
            _mbsncat(szRes, TRUE_MSG,  strlen(TRUE_MSG));   //printf ("Yes\n");
        } else {
            _mbsncat(szRes, FALSE_MSG, strlen(FALSE_MSG));  //printf ("No\n");
        }

        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //IS_WRITE_PROTECTED [да | нет]
    {
        if (tiTI.flags & CKF_WRITE_PROTECTED) {
            _mbsncat(szRes, TRUE_MSG,  strlen(TRUE_MSG));   //printf ("Yes\n");
        } else {
            _mbsncat(szRes, FALSE_MSG, strlen(FALSE_MSG));  //printf ("No\n");
        }

        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //LOGIN_REQUIRED [да | нет]
    {
        if (tiTI.flags & CKF_LOGIN_REQUIRED) {
            _mbsncat(szRes, TRUE_MSG,  strlen(TRUE_MSG));   //printf ("Yes\n");
        } else {
            _mbsncat(szRes, FALSE_MSG, strlen(FALSE_MSG));  //printf ("No\n");
        }

        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //USERS_PIN_IS_SET [да | нет]
    {
        if (tiTI.flags & CKF_USER_PIN_INITIALIZED) {
            _mbsncat(szRes, TRUE_MSG,  strlen(TRUE_MSG));   //printf ("Yes\n");
        } else {
            _mbsncat(szRes, FALSE_MSG, strlen(FALSE_MSG));  //printf ("No\n");
        }

        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //RESTORE_KEY_NOT_NEEDED [да | нет]
    {
        if (tiTI.flags & CKF_RESTORE_KEY_NOT_NEEDED) {
            _mbsncat(szRes, TRUE_MSG,  strlen(TRUE_MSG));   //printf ("Yes\n");
        } else {
            _mbsncat(szRes, FALSE_MSG, strlen(FALSE_MSG));  //printf ("No\n");
        }

        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //CLOCK_ON_TOKEN [да | нет]
    {
        if (tiTI.flags & CKF_CLOCK_ON_TOKEN) {
            _mbsncat(szRes, TRUE_MSG,  strlen(TRUE_MSG));   //printf ("Yes\n");
        } else {
            _mbsncat(szRes, FALSE_MSG, strlen(FALSE_MSG));  //printf ("No\n");
        }

        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //HAS_PROTECTED_AUTHENTICATION_PATH [да | нет]
    {
        if (tiTI.flags & CKF_PROTECTED_AUTHENTICATION_PATH) {
            _mbsncat(szRes, TRUE_MSG,  strlen(TRUE_MSG));   //printf ("Yes\n");
        } else {
            _mbsncat(szRes, FALSE_MSG, strlen(FALSE_MSG));  //printf ("No\n");
        }

        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //DUAL_CRYPTO_OPERATIONS [да | нет]
    {
        if (tiTI.flags & CKF_DUAL_CRYPTO_OPERATIONS) {
            _mbsncat(szRes, TRUE_MSG,  strlen(TRUE_MSG));   //printf ("Yes\n");
        } else {
            _mbsncat(szRes, FALSE_MSG, strlen(FALSE_MSG));  //printf ("No\n");
        }

        _mbsncat(szRes, "\n", 2);
    }

    //-------------------------------------
    //RSA_MECHANISM_MAX_KEY_SIZE [1024]
    {
        CK_MECHANISM_INFO mecInfo;
	
        ulRV = pFunctionList->C_GetMechanismInfo(ulSlotId, CKM_RSA_PKCS, &mecInfo);
        if (ulRV != CKR_OK) {
            _mbsncat(szRes, EMPTY_MSG,  strlen(EMPTY_MSG));
        } else {
            //printf ("RSA Mechanism MaxKeySize: %d\n", mecInfo.ulMaxKeySize);
            unsigned char *pszMaxKeySize = new unsigned char[lIntLen(mecInfo.ulMaxKeySize)];

            sprintf(pszMaxKeySize, "%d", mecInfo.ulMaxKeySize);
            _mbsncat(szRes, pszMaxKeySize, strlen(pszMaxKeySize));

            delete[] pszMaxKeySize;
        }

        _mbsncat(szRes, "\n", 2);
    }

	return szRes;
}
//---------------------------------------------------------------------------
//TODO: lIntLen
long int CEToken::lIntLen(long int lDigit) {
	lDigit = abs(lDigit);

    long int lCountChars = 0;

    do {
        lDigit /= 10;
        lCountChars ++;
    }
    while (lDigit);

    return lCountChars;
}
//---------------------------------------------------------------------------

/**********************************************************************
*   Информация по каждому атрибуту отдельно
*
***********************************************************************/

//---------------------------------------------------------------------------
//DONE: asGetPRODUCT_NAME
AnsiString CEToken::asGetPRODUCT_NAME(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_PRODUCT_NAME;
	const AnsiString casAttrCaption = "PRODUCT_NAME";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
    ulRV = /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1);
	if (ulRV != CKR_OK) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), (const char*)pTemplate->pValue);
    
	if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}

	return asData;
}
//---------------------------------------------------------------------------






















//---------------------------------------------------------------------------
//DONE: asGetMODEL
AnsiString CEToken::asGetMODEL(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_MODEL;
	const AnsiString casAttrCaption = "MODEL";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}
	
    //--printf("%s\n", (const char*)pAttr->pValue);
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), (const char*)pTemplate->pValue);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetFW_VERSION
AnsiString CEToken::asGetFW_VERSION(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_FW_VERSION;
	const AnsiString casAttrCaption = "FW_VERSION";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
    //--printf("%d.%d\n", pV->major, pV->minor);
    asData.sprintf("%s=%d.%d\n", casAttrCaption.c_str(), pV->major, pV->minor);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetFW_REVISION
AnsiString CEToken::asGetFW_REVISION(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_FW_REVISION;
	const AnsiString casAttrCaption = "FW_REVISION";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%d\n", *((int*)pAttr->pValue));
    asData.sprintf("%s=%d\n", casAttrCaption.c_str(), *((int*)pTemplate->pValue));
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetHW_VERSION
AnsiString CEToken::asGetHW_VERSION(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_HW_VERSION;
	const AnsiString casAttrCaption = "HW_VERSION";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
    //--printf("%d.%d\n", pV->major, pV->minor);
    asData.sprintf("%s=%d.%d\n", casAttrCaption.c_str(), pV->major, pV->minor);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetHW_INTERNAL (проверить - <empty>)
AnsiString CEToken::asGetHW_INTERNAL(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_HW_INTERNAL;
	const AnsiString casAttrCaption = "HW_INTERNAL";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
    AnsiString asTmp2 = "";
    for (CK_ULONG i = 0; i < pTemplate->ulValueLen; i ++) {
        asTmp2.sprintf("%02x ", ((BYTE*)(pTemplate->pValue))[i]);  
        asData = asData + asTmp2;
    }
    asData = casAttrCaption + "=" + asData + "\n";
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetPRODUCTION_DATE (проверить - <empty>)
AnsiString CEToken::asGetPRODUCTION_DATE(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_PRODUCTION_DATE;
	const AnsiString casAttrCaption = "PRODUCTION_DATE";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

//    if (pAttr->ulValueLen > 0) {
//        ShowMessage("pTemplate->ulValueLen > 0");
//    }
//    if (!pAttr->pValue) {
//        ShowMessage("!pTemplate->pValue");
//    }

    CK_DATE* d = (CK_DATE*)pTemplate->pValue;
    //--printf("%c%c.%c%c.%c%c%c%c\n",
    //--    d->day[0],   d->day[1],
    //--    d->month[0], d->month[1],
    //--    d->year[0],  d->year[1], d->year[2], d->year[3]);
    asData.sprintf("%s=%c%c.%c%c.%c%c%c%c\n", casAttrCaption.c_str(), d->day[0], d->day[1], d->month[0], d->month[1], d->year[0], d->year[1], d->year[2], d->year[3]);

    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetCASE_MODEL
AnsiString CEToken::asGetCASE_MODEL(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_CASE_MODEL;
	const AnsiString casAttrCaption = "CASE_MODEL";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%d\n", *((int*)pTemplate->pValue));
    asData.sprintf("%s=%d\n", casAttrCaption.c_str(), *((int*)pTemplate->pValue));
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetTOKEN_ID
AnsiString CEToken::asGetTOKEN_ID(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_TOKEN_ID;
	const AnsiString casAttrCaption = "TOKEN_ID";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("0x%08x\n", *((unsigned int*)pAttr->pValue));
    asData.sprintf("%s=0x%08x\n", casAttrCaption.c_str(), *((unsigned int*)pTemplate->pValue));
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetCARD_ID
AnsiString CEToken::asGetCARD_ID(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_CARD_ID;
	const AnsiString casAttrCaption = "CARD_ID";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
    AnsiString asTmp2 = "";
    for (CK_ULONG i = 0; i < pTemplate->ulValueLen; i ++) {
        asTmp2.sprintf("%02x ", ((BYTE*)(pTemplate->pValue))[i]);  //--printf("%02x ", ((BYTE*)(attr->pValue))[i]);
        asData = asData + asTmp2;
    }
    asData = casAttrCaption + "=" + asData + "\n";
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetCARD_TYPE
AnsiString CEToken::asGetCARD_TYPE(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_CARD_TYPE;
	const AnsiString casAttrCaption = "CARD_TYPE";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%d\n", *((int*)pAttr->pValue));
    asData.sprintf("%s=%d\n", casAttrCaption.c_str(), *((int*)pTemplate->pValue));
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetCARD_VERSION
AnsiString CEToken::asGetCARD_VERSION(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_CARD_VERSION;
	const AnsiString casAttrCaption = "CARD_VERSION";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    CK_VERSION* pV = (CK_VERSION*)pTemplate->pValue;
    //--printf("%d.%d\n", pV->major, pV->minor);
    asData.sprintf("%s=%d.%d\n", casAttrCaption.c_str(), pV->major, pV->minor);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetSERIAL
AnsiString CEToken::asGetSERIAL(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_SERIAL;
	const AnsiString casAttrCaption = "SERIAL";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%02x ",((BYTE*)(attr->pValue))[i]);
    AnsiString asTmp2 = "";
    for (CK_ULONG i = 0; i < pTemplate->ulValueLen; i ++) {
        asTmp2.sprintf("%02x ", ((BYTE*)(pTemplate->pValue))[i]);  //--printf("%02x ", ((BYTE*)(attr->pValue))[i]);
        asData = asData + asTmp2;
    }
    asData = casAttrCaption + "=" + asData + "\n";
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetCOLOR
AnsiString CEToken::asGetCOLOR(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_COLOR;
	const AnsiString casAttrCaption = "COLOR";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%d\n", *((int*)pAttr->pValue));
    asData.sprintf("%s=%d\n", casAttrCaption.c_str(), *((int*)pTemplate->pValue));
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetHAS_BATTERY
AnsiString CEToken::asGetHAS_BATTERY(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_HAS_BATTERY;
	const AnsiString casAttrCaption = "HAS_BATTERY";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetHAS_LCD
AnsiString CEToken::asGetHAS_LCD(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_HAS_LCD;
	const AnsiString casAttrCaption = "HAS_LCD";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetHAS_USER
AnsiString CEToken::asGetHAS_USER(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_HAS_USER;
	const AnsiString casAttrCaption = "HAS_USER";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetHAS_SO
AnsiString CEToken::asGetHAS_SO(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_HAS_SO;
	const AnsiString casAttrCaption = "HAS_SO";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetFIPS(
AnsiString CEToken::asGetFIPS(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_FIPS;
	const AnsiString casAttrCaption = "FIPS";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetFIPS_SUPPORTED
AnsiString CEToken::asGetFIPS_SUPPORTED(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_FIPS_SUPPORTED;
	const AnsiString casAttrCaption = "FIPS_SUPPORTED";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetINIT_PIN_REQ
AnsiString CEToken::asGetINIT_PIN_REQ(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_INIT_PIN_REQ;
	const AnsiString casAttrCaption = "INIT_PIN_REQ";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetRSA_2048
AnsiString CEToken::asGetRSA_2048(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_RSA_2048;
	const AnsiString casAttrCaption = "RSA_2048";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetRSA_2048_SUPPORTED
AnsiString CEToken::asGetRSA_2048_SUPPORTED(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_RSA_2048_SUPPORTED;
	const AnsiString casAttrCaption = "RSA_2048_SUPPORTED";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetHMAC_SHA1
AnsiString CEToken::asGetHMAC_SHA1(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
		
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_HMAC_SHA1;
	const AnsiString casAttrCaption = "HMAC_SHA1";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetHMAC_SHA1_SUPPORTED
AnsiString CEToken::asGetHMAC_SHA1_SUPPORTED(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_HMAC_SHA1_SUPPORTED;
	const AnsiString casAttrCaption = "HMAC_SHA1_SUPPORTED";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetREAL_COLOR
AnsiString CEToken::asGetREAL_COLOR(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_REAL_COLOR;
	const AnsiString casAttrCaption = "REAL_COLOR";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//---------------------------------------------------------------------------
//DONE: asGetMAY_INIT
AnsiString CEToken::asGetMAY_INIT(DWORD dwSlotId) {
    if (!bWasInit) {return "";}

    unsigned long int        ulRV = CKR_OK;
	CK_SLOT_INFO slot_info;
	
	ulRV = pFunctionList->C_GetSlotInfo(dwSlotId, &slot_info);
	if (ulRV != CKR_OK) {
		MSG_WARNING("C_GetSlotInfo ошибка...");
		return "";
	}
	
	//Если токен существует в слоте - показать его информацию
	if (! (slot_info.flags & CKF_TOKEN_PRESENT)) {
		//MSG_WARNING("eToken извлечён");
		return "";
	}
	if (! (slot_info.flags & CKF_REMOVABLE_DEVICE)) {
		MSG_WARNING("CKF_REMOVABLE_DEVICE");
		return "";
	}
	if (! (slot_info.flags & CKF_HW_SLOT)) {
		MSG_WARNING("CKF_HW_SLOT");
		return "";
	}

	//-------------------------------------
	//читаем значение атрибута
	const unsigned   ciAttrName     = CKA_SAPI_MAY_INIT;
	const AnsiString casAttrCaption = "MAY_INIT";
    AnsiString       asData         = "";
	char             szBuff[256]    = {""};	
	CK_ATTRIBUTE     pTemplate[]    = {ciAttrName, szBuff, sizeof(szBuff)};

	//получить все атрибуты
	if (CKR_OK != /*f*/_SAPI_GetTokenInfo(dwSlotId, pTemplate, 1)) {
		MSG_WARNING("SAPI_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

	if (pTemplate->ulValueLen == 0) {
		return casAttrCaption + EMPTY_MSG;
	}

    //--printf("%s\n", *((CK_BBOOL*)pAttr->pValue) ? "TRUE" : "FALSE");
    asData.sprintf("%s=%s\n", casAttrCaption.c_str(), *((CK_BBOOL*)pTemplate->pValue) ? TRUE_MSG : FALSE_MSG);
    if (AnsiString(asData.c_str()).SubString(AnsiString(asData.c_str()).Length(), 1) == "=") {
		return casAttrCaption + EMPTY_MSG;
	}
    return asData;
}
//--------------------------------------------------------------------------
//DONE: asGetLABEL
AnsiString CEToken::asGetLABEL(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Label: %.32s\n",                 token_info.label);
    return AnsiString().sprintf("%s=%.32s\n", "LABEL", token_info.label).c_str();
}
//--------------------------------------------------------------------------
//DONE: asGetMANUFACTURER_ID
AnsiString CEToken::asGetMANUFACTURER_ID(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Manufacturer: %.32s\n",          token_info.manufacturerID);
    return  AnsiString().sprintf("%s=%.32s\n", "MANUFACTURER_ID", token_info.manufacturerID).c_str();
}
//--------------------------------------------------------------------------
//DONE: asGetMODEL_2
AnsiString CEToken::asGetMODEL_2(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Model: %.16s\n",                 token_info.model);
    return AnsiString().sprintf("%s=%.16s\n", "MODEL_2", token_info.model).c_str();
}
//--------------------------------------------------------------------------
//DONE: asGetSERIAL_NUMBER
AnsiString CEToken::asGetSERIAL_NUMBER(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Serial number: %.16s\n",         token_info.serialNumber);
    return AnsiString().sprintf("%s=%.16s\n", "SERIAL_NUMBER", token_info.serialNumber).c_str();
}
//--------------------------------------------------------------------------
//DONE: asGetHARDWARE_VERSION_MAJOR
AnsiString CEToken::asGetHARDWARE_VERSION_MAJOR(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Version hardware/firmware: %d.%d, %d.%d\n", token_info.hardwareVersion.major, token_info.hardwareVersion.minor,  token_info.firmwareVersion.major, token_info.firmwareVersion.minor);
    return "HARDWARE_VERSION_MAJOR="  + IntToStr(token_info.hardwareVersion.major) + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetHARDWARE_VERSION_MINOR
AnsiString CEToken::asGetHARDWARE_VERSION_MINOR(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Version hardware/firmware: %d.%d, %d.%d\n", token_info.hardwareVersion.major, token_info.hardwareVersion.minor,  token_info.firmwareVersion.major, token_info.firmwareVersion.minor);
	return "HARDWARE_VERSION_MINOR="  + IntToStr(token_info.hardwareVersion.minor) + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetFIRMWARE_VERSION_MAJOR
AnsiString CEToken::asGetFIRMWARE_VERSION_MAJOR(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Version hardware/firmware: %d.%d, %d.%d\n", token_info.hardwareVersion.major, token_info.hardwareVersion.minor,  token_info.firmwareVersion.major, token_info.firmwareVersion.minor);
	return "FIRMWARE_VERSION_MAJOR="  + IntToStr(token_info.firmwareVersion.major) + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetFIRMWARE_VERSION_MINOR
AnsiString CEToken::asGetFIRMWARE_VERSION_MINOR(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Version hardware/firmware: %d.%d, %d.%d\n", token_info.hardwareVersion.major, token_info.hardwareVersion.minor,  token_info.firmwareVersion.major, token_info.firmwareVersion.minor);
	return "FIRMWARE_VERSION_MINOR="  + IntToStr(token_info.firmwareVersion.minor) + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetSESSION_COUNT
AnsiString CEToken::asGetSESSION_COUNT(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Current session count: %d\n",    token_info.ulSessionCount);
    return "SESSION_COUNT="           + IntToStr(token_info.ulSessionCount)        + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetMAX_SESSION_COUNT
AnsiString CEToken::asGetMAX_SESSION_COUNT(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Maximum session count: %d\n",    token_info.ulMaxSessionCount);
    return "MAX_SESSION_COUNT="       + IntToStr(token_info.ulMaxSessionCount)     + "\n";	
}
//--------------------------------------------------------------------------
//DONE: asGetMAX_RW_SESSION_COUNT
AnsiString CEToken::asGetMAX_RW_SESSION_COUNT(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Maximum RW session count: %d\n", token_info.ulMaxRwSessionCount);
    return "MAX_RW_SESSION_COUNT="    + IntToStr(token_info.ulMaxRwSessionCount)   + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetMIN_PIN_LEN
AnsiString CEToken::asGetMIN_PIN_LEN(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("PIN length: [%d..%d]\n",         token_info.ulMinPinLen,  token_info.ulMaxPinLen);
    return "MIN_PIN_LEN="             + IntToStr(token_info.ulMinPinLen)           + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetMAX_PIN_LEN
AnsiString CEToken::asGetMAX_PIN_LEN(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("PIN length: [%d..%d]\n",         token_info.ulMinPinLen,  token_info.ulMaxPinLen);
	return "MAX_PIN_LEN="             + IntToStr(token_info.ulMaxPinLen)           + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetFREE_PUBLIC_MEMORY
AnsiString CEToken::asGetFREE_PUBLIC_MEMORY(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Public memory: %d/%d bytes\n",   token_info.ulFreePublicMemory,  token_info.ulTotalPublicMemory);
    return "FREE_PUBLIC_MEMORY="      + IntToStr(token_info.ulFreePublicMemory)    + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetTOTAL_PUBLIC_MEMORY
AnsiString CEToken::asGetTOTAL_PUBLIC_MEMORY(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
   //printf ("Public memory: %d/%d bytes\n",   token_info.ulFreePublicMemory,  token_info.ulTotalPublicMemory);
	return "TOTAL_PUBLIC_MEMORY="     + IntToStr(token_info.ulTotalPublicMemory)   + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetFREE_PRIVATE_MEMORY
AnsiString CEToken::asGetFREE_PRIVATE_MEMORY(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Private memory: %d/%d bytes\n",  token_info.ulFreePrivateMemory, token_info.ulTotalPrivateMemory);
    return "FREE_PRIVATE_MEMORY="     + IntToStr(token_info.ulFreePrivateMemory)   + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetTOTAL_PRIVATE_MEMORY
AnsiString CEToken::asGetTOTAL_PRIVATE_MEMORY(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
    //printf ("Private memory: %d/%d bytes\n",  token_info.ulFreePrivateMemory, token_info.ulTotalPrivateMemory);
	return "TOTAL_PRIVATE_MEMORY="    + IntToStr(token_info.ulTotalPrivateMemory)  + "\n";
}
//--------------------------------------------------------------------------
//DONE: asGetRANDOM_NUMBER_GENERATOR
AnsiString CEToken::asGetRANDOM_NUMBER_GENERATOR(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Random number generator: ");
	if (token_info.flags & CKF_RNG) {
		return "RANDOM_NUMBER_GENERATOR="TRUE_MSG"\n"; //printf ("Yes\n");
	} else {
		return "RANDOM_NUMBER_GENERATOR="FALSE_MSG"\n"; //printf ("No\n");
    }
}
//--------------------------------------------------------------------------
//DONE: asGetIS_WRITE_PROTECTED
AnsiString CEToken::asGetIS_WRITE_PROTECTED(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Is write protected: ");
	if (token_info.flags & CKF_WRITE_PROTECTED) {
        return "IS_WRITE_PROTECTED="TRUE_MSG"\n";   //printf ("Yes\n");
	} else {
		return "IS_WRITE_PROTECTED="FALSE_MSG"\n";  //printf ("No\n");
    }
}
//--------------------------------------------------------------------------
//DONE: asGetLOGIN_REQUIRED
AnsiString CEToken::asGetLOGIN_REQUIRED(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Login required: ");
	if (token_info.flags & CKF_LOGIN_REQUIRED) {
        return "LOGIN_REQUIRED="TRUE_MSG"\n";     //printf ("Yes\n");
	} else {
		return "LOGIN_REQUIRED="FALSE_MSG"\n";    //printf ("No\n");
    }
}
//--------------------------------------------------------------------------
//DONE: asGetUSERS_PIN_IS_SET
AnsiString CEToken::asGetUSERS_PIN_IS_SET(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("User's PIN is set: ");
	if (token_info.flags & CKF_USER_PIN_INITIALIZED) {
        return "USERS_PIN_IS_SET="TRUE_MSG"\n";     //printf ("Yes\n");
	} else {
		return "USERS_PIN_IS_SET="FALSE_MSG"\n";    //printf ("No\n");
    }
}
//--------------------------------------------------------------------------
//DONE: asGetRESTORE_KEY_NOT_NEEDED
AnsiString CEToken::asGetRESTORE_KEY_NOT_NEEDED(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Restore key not needed: ");
	if (token_info.flags & CKF_RESTORE_KEY_NOT_NEEDED) {
        return "RESTORE_KEY_NOT_NEEDED="TRUE_MSG"\n";  //printf ("Yes\n");
	} else {
		return "RESTORE_KEY_NOT_NEEDED="FALSE_MSG"\n"; //printf ("No\n");
    }
}
//--------------------------------------------------------------------------
//DONE: asGetCLOCK_ON_TOKEN
AnsiString CEToken::asGetCLOCK_ON_TOKEN(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Clock on token: ");
	if (token_info.flags & CKF_CLOCK_ON_TOKEN) {
        return "CLOCK_ON_TOKEN="TRUE_MSG"\n";   //printf ("Yes\n");
	} else {
		return "CLOCK_ON_TOKEN="FALSE_MSG"\n";  //printf ("No\n");
    }
}
//--------------------------------------------------------------------------
//DONE: asGetHAS_PROTECTED_AUTHENTICATION_PATH
AnsiString CEToken::asGetHAS_PROTECTED_AUTHENTICATION_PATH(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Has protected authentication path: ");
	if (token_info.flags & CKF_PROTECTED_AUTHENTICATION_PATH) {
        return "HAS_PROTECTED_AUTHENTICATION_PATH="TRUE_MSG"\n";    //printf ("Yes\n");
	} else {
		return "HAS_PROTECTED_AUTHENTICATION_PATH="FALSE_MSG"\n";   //printf ("No\n");
    }
}
//--------------------------------------------------------------------------
//DONE: asGetDUAL_CRYPTO_OPERATIONS
AnsiString CEToken::asGetDUAL_CRYPTO_OPERATIONS(DWORD dwSlotId) {
    unsigned long int         ulRV       = CKR_OK;
    CK_TOKEN_INFO token_info;
	
	ulRV = pFunctionList->C_GetTokenInfo(dwSlotId, &token_info);
    if (ulRV != CKR_OK) {
        MSG_WARNING("C_GetTokenInfo ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }
	
	//printf ("Dual crypto operations: ");
	if (token_info.flags & CKF_DUAL_CRYPTO_OPERATIONS) {
        return "DUAL_CRYPTO_OPERATIONS="TRUE_MSG"\n";   //printf ("Yes\n");
	} else {
		return "DUAL_CRYPTO_OPERATIONS="FALSE_MSG"\n";  //printf ("No\n");
    }
}
//--------------------------------------------------------------------------
//DONE: asGetRSA_MECHANISM_MAX_KEY_SIZE
AnsiString CEToken::asGetRSA_MECHANISM_MAX_KEY_SIZE(DWORD dwSlotId) {
    unsigned long int             ulRV    = CKR_OK;
	CK_MECHANISM_INFO mecInfo;
	
	ulRV = pFunctionList->C_GetMechanismInfo(dwSlotId, CKM_RSA_PKCS, &mecInfo);
	if (ulRV != CKR_OK) {
		return "RSA_MECHANISM_MAX_KEY_SIZE"EMPTY_MSG"\n";
	} else {
		//printf ("RSA Mechanism MaxKeySize: %d\n", mecInfo.ulMaxKeySize);
        return "RSA_MECHANISM_MAX_KEY_SIZE=" + IntToStr(mecInfo.ulMaxKeySize) + "\n";
    }
}
//--------------------------------------------------------------------------



/**********************************************************************
*	Шифрование
*
***********************************************************************/

//--------------------------------------------------------------------------
//TODO: asEncryptDES
AnsiString CEToken::asEncryptFileDES() {	//DWORD dwSlotId, const AnsiString& casPlainText, const AnsiString& casPin
	#define BUFFERSIZE    8192

	unsigned long int             ulRV             = CKR_OK;
	CK_MECHANISM      mechanism;
	CK_OBJECT_HANDLE  hKey;
	CK_SESSION_HANDLE hSession;
	CK_ULONG          ciphertext_len   = 64, lastpart_len = 64;
	long              ciphertext_space = BUFFERSIZE;
	CK_ULONG          decrypttext_len;
	CK_ULONG          total_encrypted  = 0;
	CK_ULONG          ulDatalen        = BUFFERSIZE;

	unsigned int      i, bytes_read    = 0;
	char              inbuf[BUFFERSIZE];
	FILE*             pFS;
	unsigned char     ciphertext[BUFFERSIZE], *pciphertext, decrypttext[BUFFERSIZE];
	
	//-------------------------------------
	//Set the DES key object
	unsigned char   des_key[]    = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};	//Declare values for the key materials.  -->
	unsigned char   des_cbc_iv[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};	//--> DO NOT declare initialization vectors statically like this in real life!!
	CK_BBOOL        truevalue    = true;
	CK_BBOOL        falsevalue   = false;
	CK_OBJECT_CLASS ocClass      = CKO_SECRET_KEY;
	CK_KEY_TYPE     keyType      = CKK_DES;
	
	CK_ATTRIBUTE pTemplate[] = {
		{CKA_CLASS,    &ocClass,    sizeof (ocClass)   },
		{CKA_KEY_TYPE, &keyType,    sizeof (keyType)   },
		{CKA_TOKEN,    &falsevalue, sizeof (falsevalue)},
		{CKA_ENCRYPT,  &truevalue,  sizeof (truevalue) },
		{CKA_VALUE,    &des_key,    sizeof (des_key)   }
	};

	//-------------------------------------
	//Set the encryption mechanism to CKM_DES_CBC_PAD
	mechanism.mechanism      = CKM_DES_CBC_PAD;
	mechanism.pParameter     = des_cbc_iv;
	mechanism.ulParameterLen = 8;

    //-------------------------------------
	//открываем сессию
	ulRV = pFunctionList->C_OpenSession (0/*slotId*/, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_OpenSession failed.");
		return ""; //leave ("C_OpenSession failed.\n");
	}

    //-------------------------------------
	//логинимся
    char*  pucUserPIN = {"2222"};
    size_t PasswordLen = strlen((const char *)pucUserPIN);
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pucUserPIN), (CK_ULONG)PasswordLen);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Login ошибка.");
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }

    //-------------------------------------
	//Open the input file
	if ((pFS = fopen("Key.key"/*argv[1]*/, "r")) == NULL) {
        /*LOG*/Log.vLog("fopen ошибка.");
		MSG_WARNING("fopen ошибка ---> " + asEtokenErrorString(ulRV));
		(void) pFunctionList->C_CloseSession(hSession);
		return ""; 
	}

    //-------------------------------------
	//Create an object handle for the key
	ulRV = pFunctionList->C_CreateObject(hSession, pTemplate, sizeof (pTemplate) / sizeof (CK_ATTRIBUTE), &hKey);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CreateObject ошибка.");
		MSG_WARNING("C_CreateObject ошибка ---> " + asEtokenErrorString(ulRV));
		(void) pFunctionList->C_CloseSession(hSession);
		return ""; 
	}

    //-------------------------------------
    //шифруем

	//инициализируем шифрование
	ulRV = pFunctionList->C_EncryptInit(hSession, &mechanism, hKey);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_EncryptInit ошибка.");
		MSG_WARNING("C_EncryptInit ошибка ---> " + asEtokenErrorString(ulRV));
		(void)pFunctionList->C_CloseSession(hSession);
		return ""; 
	}

    //-------------------------------------
	//Read in the data and encrypt this portion
	pciphertext = &ciphertext[0];
	while (!feof(pFS) && (ciphertext_space > 0) && (ulDatalen = fread(inbuf/*8192*/, 1, ciphertext_space, pFS)) > 0) {
		ciphertext_len = ciphertext_space;

		/* C_EncryptUpdate is only being sent one byte at a time, so we are not checking for CKR_BUFFER_TOO_SMALL.
		 * Also, we are checking to make sure we do not go over the alloted buffer size.  
		 * A more robust program could incorporate realloc to enlarge the buffer dynamically.*/
		ulRV = pFunctionList->C_EncryptUpdate(hSession, (CK_BYTE_PTR)inbuf, ulDatalen, pciphertext, &ciphertext_len);
		if (ulRV != CKR_OK) {
            /*LOG*/Log.vLog("C_EncryptUpdate ошибка.");
			MSG_WARNING("C_EncryptUpdate ошибка ---> " + asEtokenErrorString(ulRV));
			fclose(pFS);
			return ""; 
		}
		pciphertext      += ciphertext_len;
		total_encrypted  += ciphertext_len;
		ciphertext_space -= ciphertext_len;
		bytes_read       += ulDatalen;
	}

	if (!feof(pFS) || (ciphertext_space < 0)) {
        /*LOG*/Log.vLog("Недостаточно места для шифрования файла");
		MSG_WARNING("Недостаточно места для шифрования файла");
		fclose(pFS);
		return ""; 
	}

    //-------------------------------------
	//Get the last portion of the encrypted data
	lastpart_len = ciphertext_space;
	ulRV = pFunctionList->C_EncryptFinal(hSession, pciphertext, &lastpart_len);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_EncryptFinal ошибка ---> " + asEtokenErrorString(ulRV));
		MSG_WARNING("C_EncryptFinal ошибка ---> " + asEtokenErrorString(ulRV));
		fclose(pFS);
		return ""; 
	}
	total_encrypted += lastpart_len;

	//--fprintf(stdout, "%d bytes read and encrypted. Size of the ciphertext: %d!\n\n", bytes_read, total_encrypted);

    //-------------------------------------
	//Результат шифрования
    AnsiString asCipherText = "";   //шифртекст
	for (i = 0; i < ciphertext_len; i++) {
		if (ciphertext[i] < 16) {
            asCipherText += AnsiString().sprintf("0%x", ciphertext[i]);
		} else {
            asCipherText += AnsiString().sprintf("%2x", ciphertext[i]);
        }
	}
    /*LOG*/Log.vLog("Результат шифрования:\n" + asCipherText);

    //-------------------------------------
    //дешифруем
	//Initialize the decryption operation in the session
	ulRV = pFunctionList->C_DecryptInit(hSession, &mechanism, hKey);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_DecryptInit ошибка ---> " + asEtokenErrorString(ulRV));
		MSG_WARNING("C_DecryptInit ошибка ---> " + asEtokenErrorString(ulRV));
		fclose(pFS);
		return "";
	}

	//-------------------------------------
	//Decrypt the entire ciphertext string
	decrypttext_len = sizeof(decrypttext);
	ulRV = pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)ciphertext/*шифртекст*/, total_encrypted, decrypttext, &decrypttext_len);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Decrypt ошибка ---> " + asEtokenErrorString(ulRV));
		MSG_WARNING("C_Decrypt ошибка ---> " + asEtokenErrorString(ulRV));
		fclose(pFS);
		return ""; 
	}

	//-------------------------------------
	//--fprintf(stdout, "\n\n%d bytes decrypted!!!\n\n", decrypttext_len);

	//-------------------------------------
	//Результат дешифрования
    /*LOG*/Log.vLog("Результат дешифрования:\n" + AnsiString().sprintf("%s", decrypttext));

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

    return "";
}
//--------------------------------------------------------------------------























//--------------------------------------------------------------------------
//TODO: asEncryptDES3
AnsiString CEToken::asEncryptDES3(/*char **argv*/) {
    unsigned long int ulRV;

	//------------------------------------------------------
	CK_SESSION_HANDLE hSession;

    //-------------------------------------
	//открываем сессию
    if (CKR_OK != pFunctionList->C_OpenSession (0/*slotId*/, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession)) {
        /*LOG*/Log.vLog("C_OpenSession failed.");
		return ""; //leave ("C_OpenSession failed.\n");
	}

    //-------------------------------------
    //логинимся
    char *pucUserPIN = {"2222"};
    size_t PasswordLen = strlen((const char *)pucUserPIN);
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pucUserPIN), (CK_ULONG)PasswordLen);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Login ошибка.");
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }


    /*------------------------------------------------*/
    /*------------------------------------------------*/
    /*------------------------------------------------*/
    unsigned long int rc2;
	
    CK_OBJECT_CLASS oClass    = CKO_SECRET_KEY;
    CK_KEY_TYPE     keyType   = CKK_DES3;
    CK_CHAR         label[]   = "A DES3 ECB secret key object";
    CK_BYTE         value[24] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11, 0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD, 0xBE, 0xEF};
    CK_BBOOL        bTrue     = TRUE;

    CK_ATTRIBUTE pTemplate[] = {
        {CKA_CLASS,    &oClass,  sizeof(oClass)},
        {CKA_KEY_TYPE, &keyType, sizeof(keyType)},
        {CKA_TOKEN,    &bTrue,   sizeof(bTrue)},
        {CKA_LABEL,    label,    sizeof(label)},
        {CKA_ENCRYPT,  &bTrue,   sizeof(bTrue)},
        {CKA_VALUE,    value,    sizeof(value)}
    };

    CK_OBJECT_HANDLE hKey;
    CK_CHAR          data[16] = {0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD, 0xBE, 0xEF, 0xC0, 0xC0, 0xCA, 0xFE, 0x11, 0x22, 0x33, 0x44};
    Log.vLog("Data1:\t\t" + AnsiString().sprintf("%s", data));
	AnsiString asVar = "";
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); i ++) {
        asVar += (char)data[i];
	}
	Log.vLog("Data:\t\t" + asVar);
	/*---------- LOG ----------*/

    //ожидаемый результат
    CK_CHAR cipher[16] = {0x5E, 0x69, 0x7E, 0x64, 0xE6, 0x16, 0xF5, 0x79, 0x7A, 0xD6, 0x0E, 0xDC, 0xED, 0x4A, 0xE9, 0x24};
	/*---------- LOG ----------*/
	/*LOG*/asVar = "";
	/*LOG*/for (int i = 0; i < sizeof(cipher) / sizeof(cipher[0]); i ++) {
    /*LOG*/    asVar += (char)cipher[i];
	/*LOG*/}
	/*LOG*/Log.vLog("Cipher:\t\t" + asVar);
	/*---------- LOG ----------*/
	
    //-------------------------------------
	//устанавливаем механизм шифрования
    CK_MECHANISM mechanism = {
        CKM_DES3_ECB, NULL, 0
    };

    //создаём DES3 ключ
    ulRV = pFunctionList->C_CreateObject(hSession, pTemplate, sizeof(pTemplate) / sizeof (CK_ATTRIBUTE), &hKey);
    if (ulRV != CKR_OK) {
        //--fprintf(stderr, "ERROR call to C_CreateObject failed, rc = %p\n", (void *)rc);
        /*LOG*/Log.vLog("C_CreateObject ошибка ---> " + asEtokenErrorString(ulRV));
        return ulRV;
    }

    //-------------------------------------
	CK_CHAR*     encryptedData    = NULL;
    CK_ULONG     encryptedDataLen = 0;
	
    ulRV = symmetric_encryption(hSession, hKey, mechanism, data, sizeof(data), &encryptedData, &encryptedDataLen);
	Log.vLog("encryptedDataLen:\t\t" + IntToStr((int)encryptedDataLen));

	/*---------- LOG ----------*/
	/*LOG*/asVar = "";
	/*LOG*/for (unsigned int i = 0; i < encryptedDataLen; i ++) {
    /*LOG*/    asVar += (char)encryptedData[i];
	/*LOG*/}
	/*LOG*/Log.vLog("encryptedData:\t\t" + asVar);
	/*---------- LOG ----------*/
	
	if (ulRV != CKR_OK) {
        //--fprintf(stderr, "ERROR call to symmetric_encryption failed, rc =%p\n", (void *)rc);
        /*LOG*/Log.vLog("symmetric_encryption ошибка ---> " + asEtokenErrorString(ulRV));
        ulRV = CKR_GENERAL_ERROR;
        return 0; /*goto done;*/
    }

    //-------------------------------------
    //known answer test
    ulRV = memcmp(cipher, encryptedData, sizeof(cipher));   //cipher - expected result
	/*---------- LOG ----------*/
	/*LOG*/asVar = "";
	/*LOG*/for (unsigned int i = 0; i < encryptedDataLen; i ++) {
    /*LOG*/    asVar += (char)encryptedData[i];
	/*LOG*/}
	/*LOG*/Log.vLog("encryptedData:\t\t" + asVar);
	/*---------- LOG ----------*/
	
    if (ulRV != 0) {
        //--fprintf(stderr, "ERROR test vector failed.\n");
        /*LOG*/Log.vLog("memcmp ошибка ---> " + asEtokenErrorString(ulRV));
        ulRV = CKR_GENERAL_ERROR;
        ////return 0; /*goto done;*/
    }

    
	
	
	
	
	
	
	//-------------------------------------
    //расшифровуем
    CK_CHAR  *TempData    = NULL;
    CK_ULONG  TempDataLen = 8192/*0*/;

    //--ulRV = symmetric_decryption(hSession, hKey, mechanism, data, sizeof(data), &encryptedData, &encryptedDataLen);
    ulRV = symmetric_decryption(hSession, hKey, mechanism, encryptedData, sizeof(encryptedData), &TempData, &TempDataLen);
    if (ulRV != 0) {
        //--fprintf(stderr, "ERROR call to symmetric_encryption failed, rc =%p\n", (void *)rc);
        /*LOG*/Log.vLog("symmetric_encryption ошибка ---> " + asEtokenErrorString(ulRV));
        ulRV = CKR_GENERAL_ERROR;
        return 0; /*goto done;*/
    }

//////   //-------------------------------------
//////   //known answer test 2
//////   ulRV = memcmp(data/*cipher*/, TempData/*encryptedData*/, sizeof(data/*cipher*/));   //cipher - expected result
//////   if (ulRV != 0) {
//////      //--fprintf(stderr, "ERROR test vector failed.\n");
//////      /*LOG*/Log.vLog("memcmp ошибка ---> " + asEtokenErrorString(ulRV));
//////      ulRV = CKR_GENERAL_ERROR;
//////      ////return 0; /*goto done;*/
//////   }
//////   /*LOG*///Log.vLog((char *)encryptedData);

   ulRV = CKR_OK;

done:
    if (encryptedData) {
        free(encryptedData);
    }
    rc2 = pFunctionList->C_DestroyObject(hSession, hKey);
    if (rc2 != CKR_OK) {
        //--fprintf(stderr, "Error deleting 3DES key...\n");
        /*LOG*/Log.vLog("C_DestroyObject ошибка ---> " + asEtokenErrorString(ulRV));
        if (ulRV == CKR_OK)
         ulRV = rc2;
    }

    return ulRV;

    /*------------------------------------------------*/
    /*------------------------------------------------*/
    /*------------------------------------------------*/


////	//Initialize the decryption operation in the session
////	ulRV = pFunctionList->C_DecryptInit(hSession, &mechanism, hKey);
////
////	//Decrypt the entire ciphertext string
////	decrypttext_len = sizeof (decrypttext);
////	ulRV = pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)ciphertext, total_encrypted, decrypttext, &decrypttext_len);
////
////	if (ulRV != CKR_OK) {
////        /*LOG*/Log.vLog("C_Decrypt ошибка ---> " + asEtokenErrorString(ulRV));
////		//--fprintf(stderr, "C_Decrypt: ulRV = 0x%.8X\n", ulRV);
////
////		return ""; //--goto exit_encrypt;
////	}
////
////    /*LOG*/Log.vLog("he value of the decryption");
////    /*LOG*/Log.vLog(AnsiString().sprintf("%s", decrypttext));
////
////	//--fprintf(stdout, "\nDone!!!\n");
////
////    //-------------------------------------
////    //делогинимся
////    ulRV = pFunctionList->C_Logout(hSession);
////    if (ulRV != CKR_OK) {
////        /*LOG*/Log.vLog("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
////        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
////    }
////
////    //-------------------------------------
////    //закрываем сессию
////    ulRV = pFunctionList->C_CloseSession(hSession);
////    if (ulRV != CKR_OK) {
////        /*LOG*/Log.vLog("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
////        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
////    }
////
////    exit_encrypt:
////        fclose(fs);

////    return "";
}
//--------------------------------------------------------------------------
/* General symmetric encryption, given a handle to a key object and a mechanism */
/* Caller needs to free memory for encryptedData */
//DONE: symmetric_encryption
CK_RV CEToken::symmetric_encryption(
									CK_SESSION_HANDLE hSession, 
									CK_OBJECT_HANDLE  hKey, 
									CK_MECHANISM      mechanism, 
									CK_CHAR*          data, 
									CK_ULONG          data_sz, 
									CK_CHAR**         encryptedData, 
									CK_ULONG*         encryptedData_sz) 
{
    unsigned long int    ulRV;
    CK_CHAR* this_encryptedData;

    /* init */
    ulRV = pFunctionList->C_EncryptInit(hSession, &mechanism, hKey);
    if (ulRV != CKR_OK) {
        //--fprintf(stderr, "ERROR call to C_EncryptInit failed, rc = %p\n", (void *)rc);
        /*LOG*/Log.vLog("C_EncryptInit ошибка ---> " + asEtokenErrorString(ulRV));
        return ulRV;
    }

    ulRV = pFunctionList->C_Encrypt(hSession, data, data_sz, NULL, encryptedData_sz);
    if (ulRV != CKR_OK) {
        //--fprintf(stderr, "ERROR failed to get size of encrypted data calling C_Encrypt, rc = %p\n", (void *)rc);
        /*LOG*/Log.vLog("C_Encrypt ошибка ---> " + asEtokenErrorString(ulRV));
        return ulRV;
    }

    this_encryptedData = (CK_CHAR *)malloc((*encryptedData_sz)*sizeof(CK_CHAR));

	//-------------------------------------
    //шифруем
    ulRV = pFunctionList->C_Encrypt(hSession, data, data_sz, this_encryptedData, encryptedData_sz);
    if (ulRV != CKR_OK) {
        //--fprintf(stderr, "ERROR call to C_EncryptUpdate failed, rc = %p\n", (void *)rc);
        /*LOG*/Log.vLog("C_Encrypt ошибка ---> " + asEtokenErrorString(ulRV));
        return ulRV;
    }

    *encryptedData = this_encryptedData;
    /*LOG*///--Log.vLog(encryptedData);

    ulRV = CKR_OK;
    return ulRV;
}
//--------------------------------------------------------------------------
//DONE: symmetric_decryption
CK_RV CEToken::symmetric_decryption(CK_SESSION_HANDLE hSession,
                                    CK_OBJECT_HANDLE  hKey,
                                    CK_MECHANISM      mechanism,
                                    CK_CHAR          *data,
                                    CK_ULONG          data_sz,
                                    CK_CHAR          **decryptedData,
                                    CK_ULONG         *decryptedData_sz)
{
    unsigned long int    ulRV;
    CK_CHAR* this_decryptedData;

    /* init */
    ulRV = pFunctionList->C_DecryptInit(hSession, &mechanism, hKey);
    if (ulRV != CKR_OK) {
        //--fprintf(stderr, "ERROR call to C_EncryptInit failed, rc = %p\n", (void *)rc);
        /*LOG*/Log.vLog("C_DecryptInit ошибка ---> " + asEtokenErrorString(ulRV));
        return ulRV;
    }

    ulRV = pFunctionList->C_Decrypt(hSession, data, data_sz, NULL, decryptedData_sz);
    if (ulRV != CKR_OK) {
        //--fprintf(stderr, "ERROR failed to get size of encrypted data calling C_Encrypt, rc = %p\n", (void *)rc);
        /*LOG*/Log.vLog("C_Decrypt ошибка ---> " + asEtokenErrorString(ulRV));
        return ulRV;
    }

    this_decryptedData = (CK_CHAR *)malloc((*decryptedData_sz)*sizeof(CK_CHAR));

	//-------------------------------------
    //шифруем
    ulRV = pFunctionList->C_Decrypt(hSession, data, data_sz, this_decryptedData, decryptedData_sz);
    if (ulRV != CKR_OK) {
        //--fprintf(stderr, "ERROR call to C_EncryptUpdate failed, rc = %p\n", (void *)rc);
        /*LOG*/Log.vLog("C_Decrypt ошибка ---> " + asEtokenErrorString(ulRV));
        return ulRV;
    }

    *decryptedData = this_decryptedData;
    /*LOG*///--Log.vLog(encryptedData);

    ulRV = CKR_OK;
    return ulRV;


////    unsigned long int ulRV;
////    //--unsigned char     ciphertext[BUFFERSIZE], *pciphertext, decrypttext[BUFFERSIZE];
////    //--CK_CHAR *this_encryptedData;
////
////    //-------------------------------------
////    //дешифруем
////    ulRV = pFunctionList->C_DecryptInit(hSession, &mechanism, hKey);
////    if (ulRV != CKR_OK) {
////        /*LOG*/Log.vLog("C_DecryptInit ошибка ---> " + asEtokenErrorString(ulRV));
////        return 0;
////    }
////
////    //-------------------------------------
////    //Decrypt the entire ciphertext string
//////--    CK_CHAR  *TempData    = NULL;
//////--    CK_ULONG  TempDataLen = 0;
////
////    /////////////////////////decryptedData_sz = sizeof(decryptedData); //--decrypttext_len = sizeof (decrypttext);
////    //--CK_ULONG          decrypttext_len;
////    //--unsigned char     decrypttext[BUFFERSIZE];
////    //--ulRV = pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)ciphertext/*шифртекст*/, total_encrypted, decrypttext, &decrypttext_len);
////
////
////    //decryptedData_sz - function
////    CK_CHAR *this_decryptedData = NULL;
////    this_decryptedData = (CK_CHAR *)malloc((*decryptedData_sz)*sizeof(CK_CHAR));
////    //this_decryptedData - in function
////	/*LOG*/Log.vLog("decryptedData_sz: " + (AnsiString)(*decryptedData_sz));
////    CK_ULONG  decrypttext_len = 0/*8192*/;
////
////	
////    ulRV = pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)data/*шифр*/, data_sz, this_decryptedData/*decryptedData*/, &decrypttext_len);
////    if (ulRV != CKR_OK) {
////        /*LOG*/Log.vLog("C_Decrypt ошибка ---> " + asEtokenErrorString(ulRV));
////        return 0;
////    }
////    return ulRV;
}
//--------------------------------------------------------------------------











































/**********************************************************************
*	Дешифрование
*
***********************************************************************/

//---------------------------------------------------------------------------
//DONE: asEtokenErrorString (SDK 4.53)
AnsiString CEToken::asEtokenErrorString(DWORD ulRV) {
	AnsiString asResult = "";
	
	switch (ulRV) {
		case CKR_OK: 	                           asResult = "CKR_OK";									break;
		case CKR_CANCEL:                           asResult = "CKR_CANCEL";								break;
		case CKR_HOST_MEMORY:                      asResult = "CKR_HOST_MEMORY";						break;
		case CKR_SLOT_ID_INVALID:                  asResult = "CKR_SLOT_ID_INVALID";					break;
		case CKR_GENERAL_ERROR:                    asResult = "CKR_GENERAL_ERROR";						break;
		case CKR_FUNCTION_FAILED:                  asResult = "CKR_FUNCTION_FAILED";					break;
		case CKR_ARGUMENTS_BAD:                    asResult = "CKR_ARGUMENTS_BAD";						break;
		case CKR_NO_EVENT:                         asResult = "CKR_NO_EVENT";							break;
		case CKR_NEED_TO_CREATE_THREADS:           asResult = "CKR_NEED_TO_CREATE_THREADS";				break;
		case CKR_CANT_LOCK:                        asResult = "CKR_CANT_LOCK";							break;
		case CKR_ATTRIBUTE_READ_ONLY:              asResult = "CKR_ATTRIBUTE_READ_ONLY";				break;
		case CKR_ATTRIBUTE_SENSITIVE:              asResult = "CKR_ATTRIBUTE_SENSITIVE";				break;
		case CKR_ATTRIBUTE_TYPE_INVALID:           asResult = "CKR_ATTRIBUTE_TYPE_INVALID";				break;
		case CKR_ATTRIBUTE_VALUE_INVALID:          asResult = "CKR_ATTRIBUTE_VALUE_INVALID";			break;
		case CKR_DATA_INVALID:                     asResult = "CKR_DATA_INVALID";						break;
		case CKR_DATA_LEN_RANGE:                   asResult = "CKR_DATA_LEN_RANGE";						break;
		case CKR_DEVICE_ERROR:                     asResult = "CKR_DEVICE_ERROR";						break;
		case CKR_DEVICE_MEMORY:                    asResult = "CKR_DEVICE_MEMORY";						break;
		case CKR_DEVICE_REMOVED:                   asResult = "CKR_DEVICE_REMOVED";						break;
		case CKR_ENCRYPTED_DATA_INVALID:           asResult = "CKR_ENCRYPTED_DATA_INVALID";				break;
		case CKR_ENCRYPTED_DATA_LEN_RANGE:         asResult = "CKR_ENCRYPTED_DATA_LEN_RANGE";			break;
		case CKR_FUNCTION_CANCELED:                asResult = "CKR_FUNCTION_CANCELED";					break;
		case CKR_FUNCTION_NOT_PARALLEL:            asResult = "CKR_FUNCTION_NOT_PARALLEL";				break;
		case CKR_FUNCTION_NOT_SUPPORTED:           asResult = "CKR_FUNCTION_NOT_SUPPORTED";				break;
		case CKR_KEY_HANDLE_INVALID:               asResult = "CKR_KEY_HANDLE_INVALID";					break;
		case CKR_KEY_SIZE_RANGE:                   asResult = "CKR_KEY_SIZE_RANGE";						break;
		case CKR_KEY_TYPE_INCONSISTENT:            asResult = "CKR_KEY_TYPE_INCONSISTENT";				break;
		case CKR_KEY_NOT_NEEDED:                   asResult = "CKR_KEY_NOT_NEEDED";						break;
		case CKR_KEY_CHANGED:                      asResult = "CKR_KEY_CHANGED";						break;
		case CKR_KEY_NEEDED:                       asResult = "CKR_KEY_NEEDED";							break;
		case CKR_KEY_INDIGESTIBLE:                 asResult = "CKR_KEY_INDIGESTIBLE";					break;
		case CKR_KEY_FUNCTION_NOT_PERMITTED:       asResult = "CKR_KEY_FUNCTION_NOT_PERMITTED";			break;
		case CKR_KEY_NOT_WRAPPABLE:                asResult = "CKR_KEY_NOT_WRAPPABLE";					break;
		case CKR_KEY_UNEXTRACTABLE:                asResult = "CKR_KEY_UNEXTRACTABLE";					break;
		case CKR_MECHANISM_INVALID:                asResult = "CKR_MECHANISM_INVALID";					break;
		case CKR_MECHANISM_PARAM_INVALID:          asResult = "CKR_MECHANISM_PARAM_INVALID";			break;
		case CKR_OBJECT_HANDLE_INVALID:            asResult = "CKR_OBJECT_HANDLE_INVALID";				break;
		case CKR_OPERATION_ACTIVE:                 asResult = "CKR_OPERATION_ACTIVE";					break;
		case CKR_OPERATION_NOT_INITIALIZED:        asResult = "CKR_OPERATION_NOT_INITIALIZED";			break;
		case CKR_PIN_INCORRECT:                    asResult = "CKR_PIN_INCORRECT";						break;
		case CKR_PIN_INVALID:                      asResult = "CKR_PIN_INVALID";						break;
		case CKR_PIN_LEN_RANGE:                    asResult = "CKR_PIN_LEN_RANGE";						break;
		case CKR_PIN_EXPIRED:                      asResult = "CKR_PIN_EXPIRED";						break;
		case CKR_PIN_LOCKED:                       asResult = "CKR_PIN_LOCKED";							break;
		case CKR_SESSION_CLOSED:                   asResult = "CKR_SESSION_CLOSED";						break;
		case CKR_SESSION_COUNT:                    asResult = "CKR_SESSION_COUNT";						break;
		case CKR_SESSION_HANDLE_INVALID:           asResult = "CKR_SESSION_HANDLE_INVALID";				break;
		case CKR_SESSION_PARALLEL_NOT_SUPPORTED:   asResult = "CKR_SESSION_PARALLEL_NOT_SUPPORTED";		break;
		case CKR_SESSION_READ_ONLY:                asResult = "CKR_SESSION_READ_ONLY";					break;
		case CKR_SESSION_EXISTS:                   asResult = "CKR_SESSION_EXISTS";						break;
		case CKR_SESSION_READ_ONLY_EXISTS:         asResult = "CKR_SESSION_READ_ONLY_EXISTS";			break;
		case CKR_SESSION_READ_WRITE_SO_EXISTS:     asResult = "CKR_SESSION_READ_WRITE_SO_EXISTS";		break;
		case CKR_SIGNATURE_INVALID:                asResult = "CKR_SIGNATURE_INVALID";					break;
		case CKR_SIGNATURE_LEN_RANGE:              asResult = "CKR_SIGNATURE_LEN_RANGE";				break;
		case CKR_TEMPLATE_INCOMPLETE:              asResult = "CKR_TEMPLATE_INCOMPLETE";				break;
		case CKR_TEMPLATE_INCONSISTENT:            asResult = "CKR_TEMPLATE_INCONSISTENT";				break;
		case CKR_TOKEN_NOT_PRESENT:                asResult = "CKR_TOKEN_NOT_PRESENT";					break;
		case CKR_TOKEN_NOT_RECOGNIZED:             asResult = "CKR_TOKEN_NOT_RECOGNIZED";				break;
		case CKR_TOKEN_WRITE_PROTECTED:            asResult = "CKR_TOKEN_WRITE_PROTECTED";				break;
		case CKR_UNWRAPPING_KEY_HANDLE_INVALID:    asResult = "CKR_UNWRAPPING_KEY_HANDLE_INVALID";		break;
		case CKR_UNWRAPPING_KEY_SIZE_RANGE:        asResult = "CKR_UNWRAPPING_KEY_SIZE_RANGE";			break;
		case CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT: asResult = "CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT";	break;
		case CKR_USER_ALREADY_LOGGED_IN:           asResult = "CKR_USER_ALREADY_LOGGED_IN";	        	break;
		case CKR_USER_NOT_LOGGED_IN:               asResult = "CKR_USER_NOT_LOGGED_IN";	            	break;
		case CKR_USER_PIN_NOT_INITIALIZED:         asResult = "CKR_USER_PIN_NOT_INITIALIZED";	        break;
		case CKR_USER_TYPE_INVALID:                asResult = "CKR_USER_TYPE_INVALID";                 	break;
		case CKR_USER_ANOTHER_ALREADY_LOGGED_IN:   asResult = "CKR_USER_ANOTHER_ALREADY_LOGGED_IN";    	break;
		case CKR_USER_TOO_MANY_TYPES:              asResult = "CKR_USER_TOO_MANY_TYPES";			    break;
		case CKR_WRAPPED_KEY_INVALID:              asResult = "CKR_WRAPPED_KEY_INVALID";				break;
		case CKR_WRAPPED_KEY_LEN_RANGE:            asResult = "CKR_WRAPPED_KEY_LEN_RANGE";				break;
		case CKR_WRAPPING_KEY_HANDLE_INVALID:      asResult = "CKR_WRAPPING_KEY_HANDLE_INVALID";		break;
		case CKR_WRAPPING_KEY_SIZE_RANGE:          asResult = "CKR_WRAPPING_KEY_SIZE_RANGE";			break;
		case CKR_WRAPPING_KEY_TYPE_INCONSISTENT:   asResult = "CKR_WRAPPING_KEY_TYPE_INCONSISTENT";		break;
		case CKR_RANDOM_SEED_NOT_SUPPORTED:        asResult = "CKR_RANDOM_SEED_NOT_SUPPORTED";			break;
		case CKR_RANDOM_NO_RNG:                    asResult = "CKR_RANDOM_NO_RNG";						break;
		case CKR_DOMAIN_PARAMS_INVALID:            asResult = "CKR_DOMAIN_PARAMS_INVALID";				break;	/*new SDK 4.53*/
		case CKR_BUFFER_TOO_SMALL:                 asResult = "CKR_BUFFER_TOO_SMALL";					break;
		case CKR_SAVED_STATE_INVALID:              asResult = "CKR_SAVED_STATE_INVALID";				break;
		case CKR_INFORMATION_SENSITIVE:            asResult = "CKR_INFORMATION_SENSITIVE";				break;
		case CKR_STATE_UNSAVEABLE:                 asResult = "CKR_STATE_UNSAVEABLE";					break;
		case CKR_CRYPTOKI_NOT_INITIALIZED:         asResult = "CKR_CRYPTOKI_NOT_INITIALIZED";			break;
		case CKR_CRYPTOKI_ALREADY_INITIALIZED:     asResult = "CKR_CRYPTOKI_ALREADY_INITIALIZED";		break;
		case CKR_MUTEX_BAD:                        asResult = "CKR_MUTEX_BAD";							break;
		case CKR_MUTEX_NOT_LOCKED:                 asResult = "CKR_MUTEX_NOT_LOCKED";					break;
		case CKR_FUNCTION_REJECTED:                asResult = "CKR_FUNCTION_REJECTED";					break;	/*new SDK 4.53*/
		case CKR_VENDOR_DEFINED:                   asResult = "CKR_VENDOR_DEFINED";						break;
		case CKR_SAPI_OBJECT_DOES_NOT_EXIST:       asResult = "CKR_SAPI_OBJECT_DOES_NOT_EXIST";			break;	/*new SDK 4.53*/
		case CKR_SAPI_OBJECT_ALREADY_EXISTS:       asResult = "CKR_SAPI_OBJECT_ALREADY_EXISTS";			break;	/*new SDK 4.53*/
		case CKR_SAPI_NOT_SUPPORTED_BY_TOKEN:      asResult = "CKR_SAPI_NOT_SUPPORTED_BY_TOKEN";		break;	/*new SDK 4.53*/
		case CKR_SAPI_PIN_QUALITY:                 asResult = "CKR_SAPI_PIN_QUALITY";					break;	/*new SDK 4.53*/
		case CKR_SAPI_PIN_DEFAULT:                 asResult = "CKR_SAPI_PIN_DEFAULT";					break;	/*new SDK 4.53*/
		case CKR_SAPI_PIN_EXPIRATION:              asResult = "CKR_SAPI_PIN_EXPIRATION";				break;	/*new SDK 4.53*/
		case CKR_SAPI_PIN_CHANGE_NOT_ALLOWED:      asResult = "CKR_SAPI_PIN_CHANGE_NOT_ALLOWED";		break;	/*new SDK 4.53*/
		case CKR_SAPI_CANCELLED: 				   asResult = "CKR_SAPI_CANCELLED";						break;	/*new SDK 4.53*/
		case CKR_NEW_PIN_MODE:      			   asResult = "CKR_NEW_PIN_MODE";						break;	/*new SDK 4.53*/
		case CKR_NEXT_OTP:          	           asResult = "CKR_NEXT_OTP";							break;	/*new SDK 4.53*/

		default:								   asResult = "UNKNOWN_ERROR";						    break;
	}
	
	return asResult;
}
//---------------------------------------------------------------------------








//--------------------------------------------------------------------------
AnsiString CEToken::asEncryptDES3Text() {	//DWORD dwSlotId, const AnsiString& casPlainText, const AnsiString& casPin
	#define BUFFERSIZE    8192
	
	unsigned long int             ulRV             = CKR_OK;
	CK_MECHANISM      mechanism;
	CK_OBJECT_HANDLE  hKey;
	CK_SESSION_HANDLE hSession;
	CK_ULONG          ciphertext_len   = 64, lastpart_len = 64;
	long              ciphertext_space = BUFFERSIZE;
	CK_ULONG          decrypttext_len;
	CK_ULONG          total_encrypted  = 0;
	CK_ULONG          ulDatalen        = BUFFERSIZE;

	unsigned int      i, bytes_read    = 0;
	char              inbuf[BUFFERSIZE];
	FILE*             pFS;
	unsigned char     ciphertext[BUFFERSIZE], *pciphertext, decrypttext[BUFFERSIZE];
	
	//-------------------------------------
	//Set the DES key object
	unsigned char   des_key[]    = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11, 0xDE, 0xAD, 0xBE, 0xEF, 0xDE, 0xAD, 0xBE, 0xEF};    /*{0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};	//Declare values for the key materials.  -->*/
	unsigned char   des_cbc_iv[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};	//--> DO NOT declare initialization vectors statically like this in real life!!
	CK_BBOOL        truevalue    = true;
	CK_BBOOL        falsevalue   = false;
	CK_OBJECT_CLASS ocClass      = CKO_SECRET_KEY;
	CK_KEY_TYPE     keyType      = CKK_DES3/*CKK_DES*/;
	
 	CK_ATTRIBUTE pTemplate[] = {
		{CKA_CLASS,    &ocClass,    sizeof (ocClass)   },
		{CKA_KEY_TYPE, &keyType,    sizeof (keyType)   },
		{CKA_TOKEN,    &falsevalue, sizeof (falsevalue)},
		{CKA_ENCRYPT,  &truevalue,  sizeof (truevalue) },
		{CKA_VALUE,    &des_key,    sizeof (des_key)   }
	};
	

	//-------------------------------------
	//Set the encryption mechanism to CKM_DES_CBC_PAD
	mechanism.mechanism      = CKM_DES3_CBC/*CKM_DES3_ECB*//*CKM_DES_CBC_PAD*/;
	mechanism.pParameter     = /*NULL*/ des_cbc_iv;
	mechanism.ulParameterLen = /*0*/sizeof(des_cbc_iv);

    //-------------------------------------
	//открываем сессию
	ulRV = pFunctionList->C_OpenSession(0/*slotId*/, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_OpenSession failed." + asEtokenErrorString(ulRV));
		return ""; //leave ("C_OpenSession failed.\n");
	}

    //-------------------------------------
	//логинимся
    char*  pucUserPIN = {"2222"};
    size_t PasswordLen = strlen((const char *)pucUserPIN);
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pucUserPIN), (CK_ULONG)PasswordLen);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Login ошибка." + asEtokenErrorString(ulRV));
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }

    //-------------------------------------
	//Open the input file
	if ((pFS = fopen("Key.key"/*argv[1]*/, "r")) == NULL) {
        /*LOG*/Log.vLog("fopen ошибка.");
		MSG_WARNING("fopen ошибка ---> " + asEtokenErrorString(ulRV));
		(void) pFunctionList->C_CloseSession(hSession);
		return ""; 
	}

    //-------------------------------------
	//Create an object handle for the key
	ulRV = pFunctionList->C_CreateObject(hSession, pTemplate, sizeof(pTemplate) / sizeof(CK_ATTRIBUTE), &hKey);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CreateObject ошибка ---> " + asEtokenErrorString(ulRV));
		MSG_WARNING("C_CreateObject ошибка ---> " + asEtokenErrorString(ulRV));
		(void) pFunctionList->C_CloseSession(hSession);
		return ""; 
	}

    //-------------------------------------
    //шифруем

	//инициализируем шифрование
	ulRV = pFunctionList->C_EncryptInit(hSession, &mechanism, hKey);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_EncryptInit ошибка." + asEtokenErrorString(ulRV));
		MSG_WARNING("C_EncryptInit ошибка ---> " + asEtokenErrorString(ulRV));
		(void)pFunctionList->C_CloseSession(hSession);
		return ""; 
	}

    //-------------------------------------
	//Read in the data and encrypt this portion
	pciphertext = &ciphertext[0];
	while (!feof(pFS) && (ciphertext_space > 0) && (ulDatalen = fread(inbuf, 1, ciphertext_space, pFS)) > 0) {
		ciphertext_len = ciphertext_space;

		/* C_EncryptUpdate is only being sent one byte at a time, so we are not checking for CKR_BUFFER_TOO_SMALL.
		 * Also, we are checking to make sure we do not go over the alloted buffer size.  
		 * A more robust program could incorporate realloc to enlarge the buffer dynamically.*/
		ulRV = pFunctionList->C_EncryptUpdate(hSession, (CK_BYTE_PTR)inbuf, ulDatalen, pciphertext, &ciphertext_len);
		if (ulRV != CKR_OK) {
            /*LOG*/Log.vLog("C_EncryptUpdate ошибка." + asEtokenErrorString(ulRV));
			MSG_WARNING("C_EncryptUpdate ошибка ---> " + asEtokenErrorString(ulRV));
			fclose(pFS);
			return ""; 
		}
		pciphertext      += ciphertext_len;
		total_encrypted  += ciphertext_len;
		ciphertext_space -= ciphertext_len;
		bytes_read       += ulDatalen;
	}

	if (!feof(pFS) || (ciphertext_space < 0)) {
        /*LOG*/Log.vLog("Недостаточно места для шифрования файла");
		MSG_WARNING("Недостаточно места для шифрования файла");
		fclose(pFS);
		return ""; 
	}

    //-------------------------------------
	//Get the last portion of the encrypted data
	lastpart_len = ciphertext_space;
	ulRV = pFunctionList->C_EncryptFinal(hSession, pciphertext, &lastpart_len);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_EncryptFinal ошибка" + asEtokenErrorString(ulRV));
		MSG_WARNING("C_EncryptFinal ошибка ---> " + asEtokenErrorString(ulRV));
		fclose(pFS);
		return "";
	}
	total_encrypted += lastpart_len;

	//--fprintf(stdout, "%d bytes read and encrypted. Size of the ciphertext: %d!\n\n", bytes_read, total_encrypted);

    //-------------------------------------
	//Результат шифрования
    AnsiString asCipherText = "";   //шифртекст
	for (i = 0; i < ciphertext_len; i++) {
		if (ciphertext[i] < 16) {
            asCipherText += AnsiString().sprintf("0%x", ciphertext[i]);
		} else {
            asCipherText += AnsiString().sprintf("%2x", ciphertext[i]);
        }
	}
    /*LOG*/Log.vLog("Результат шифрования:\n" + asCipherText);

    //-------------------------------------
    //дешифруем
	//Initialize the decryption operation in the session
	ulRV = pFunctionList->C_DecryptInit(hSession, &mechanism, hKey);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_DecryptInit ошибка" + asEtokenErrorString(ulRV));
		MSG_WARNING("C_DecryptInit ошибка ---> " + asEtokenErrorString(ulRV));
		fclose(pFS);
		return ""; 
	}

	//-------------------------------------
	//Decrypt the entire ciphertext string
	decrypttext_len = sizeof(decrypttext);
	ulRV = pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)ciphertext/*шифртекст*/, total_encrypted, decrypttext, &decrypttext_len);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Decrypt ошибка" + asEtokenErrorString(ulRV));
		MSG_WARNING("C_Decrypt ошибка ---> " + asEtokenErrorString(ulRV));
		fclose(pFS);
		return ""; 
	}

	//-------------------------------------
	//--fprintf(stdout, "\n\n%d bytes decrypted!!!\n\n", decrypttext_len);

	//-------------------------------------
	//Результат дешифрования
    /*LOG*/Log.vLog("Результат дешифрования:\n" + AnsiString().sprintf("%s", decrypttext));

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Logout ошибка" + asEtokenErrorString(ulRV));
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CloseSession ошибка" + asEtokenErrorString(ulRV));
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

    return "";
}














//--------------------------------------------------------------------------
//DONE : asEncryptTextDES
unsigned char *CEToken::asEncryptTextDES(unsigned char *pucUserPIN,    unsigned long int  ulUserPINLen,
                                         unsigned char *pucKey,        unsigned long int  uiKeyLen,
                                         unsigned char *pucIv,         unsigned long int  uiIvLen,
                                         unsigned char *pucPlainText,  unsigned long int  uiPlainTextLen,
                                         unsigned char *pucCipherText, unsigned long int &ulCipherTextLen)
{
    #define BYTESIZE(bitsize) ((bitsize + 7) >> 3)

    unsigned long int             ulRV      = CKR_OK;
    unsigned long int uiPadSize = BYTESIZE(64/*SNMP_TRANS_PRIVLEN_1DES*/);  //for DES
    unsigned long int uiOffset  = 0;

    //-------------------------------------
    //открываем сессию
    CK_SESSION_HANDLE hSession = 0;          
    ulRV = pFunctionList->C_OpenSession(0/*slotId*/, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_OpenSession ошибка" + asEtokenErrorString(ulRV));
        return "";
    }
                                                        
    //-------------------------------------
    //логинимся
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pucUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
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
        {CKA_VALUE,    pucKey,        uiKeyLen           }
    };



    CK_OBJECT_HANDLE  hKey     = (CK_OBJECT_HANDLE)0;
    ulRV = pFunctionList->C_CreateObject(hSession, pTemplate, (sizeof(pTemplate) / sizeof(CK_ATTRIBUTE)), &hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CreateObject ошибка ---> " + asEtokenErrorString(ulRV));
    }              
 
	//-------------------------------------
	//шифруем
    CK_MECHANISM Mech;
    Mech.mechanism      = CKM_DES_CBC_PAD;
    Mech.pParameter     = pucIv;
    Mech.ulParameterLen = uiIvLen;
 
    ulRV = pFunctionList->C_EncryptInit(hSession, &Mech, hKey);
    if (ulRV != CKR_OK ) {
        /*LOG*/Log.vLog("C_EncryptInit ошибка ---> " + asEtokenErrorString(ulRV));
    }

    if (uiPlainTextLen + uiPadSize - uiPlainTextLen % uiPadSize > /***/ulCipherTextLen) {
        return "";
    }

    //продолжаем  многоступенчатое шифрование
    for (uiOffset = 0; uiOffset < uiPlainTextLen; uiOffset += uiPadSize) {
        ulRV = pFunctionList->C_EncryptUpdate(hSession, pucPlainText + uiOffset, uiPadSize, pucCipherText + uiOffset, &ulCipherTextLen);
        if (ulRV != CKR_OK) {
            /*LOG*/Log.vLog("C_EncryptUpdate ошибка ---> " + asEtokenErrorString(ulRV));
        }
    }

    //заканчиваем многоступенчатое шифрование
    ulRV = pFunctionList->C_EncryptFinal(hSession, pucCipherText + uiOffset, &ulCipherTextLen);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_EncryptFinal ошибка ---> " + asEtokenErrorString(ulRV));
    }
    /***/ulCipherTextLen = uiOffset;

    /*LOG*/Log.vLogCharAsHex("Результат шифрования:", pucCipherText, ulCipherTextLen);
    /*LOG*/Log.vLogCharAsStr("Результат шифрования:", pucCipherText, ulCipherTextLen);

    //-------------------------------------
    //удаляем ключ
    //--	if (key != (CK_OBJECT_HANDLE) 0) {}
    ulRV = pFunctionList->C_DestroyObject(hSession, hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_DestroyObject ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

    Log.vOpen();
    
    return &pucCipherText[0];
}
//--------------------------------------------------------------------------
//DONE: asDecryptTextDES
unsigned char *CEToken::asDecryptTextDES(unsigned char *pucUserPIN,    unsigned long int  ulUserPINLen,
                                         unsigned char *pucKey,        unsigned long int  uiKeyLen,
                                         unsigned char *pucIv,         unsigned long int  uiIvLen,
                                         unsigned char *pucPlainText,  unsigned long int  &uiPlainTextLen,
                                         unsigned char *pucCipherText, unsigned long int  ulCipherTextLen) {
    unsigned long int ulRV = CKR_OK;           

    //-------------------------------------
    //открываем сессию
    CK_SESSION_HANDLE hSession;
    ulRV = pFunctionList->C_OpenSession(0/*dwSlotId*/, (CKF_SERIAL_SESSION | CKF_RW_SESSION), 0, 0, &hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_OpenSession ошибка ---> " + asEtokenErrorString(ulRV));
        return ""; //leave ("C_OpenSession failed.\n");
    }

    //-------------------------------------
    //логинимся
    ulRV = pFunctionList->C_Login(hSession, CKU_USER, CK_CHAR_PTR(pucUserPIN), (CK_ULONG)ulUserPINLen);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
        MSG_WARNING("C_Login ошибка ---> " + asEtokenErrorString(ulRV));
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
		{CKA_VALUE,    pucKey,     uiKeyLen         }
	};

    CK_OBJECT_HANDLE  hKey = (CK_OBJECT_HANDLE)0;
	ulRV = pFunctionList->C_CreateObject(hSession, pTemplate, (sizeof(pTemplate) / sizeof(CK_ATTRIBUTE)), &hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CreateObject ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }

    //-------------------------------------
   	//дешифруем
    CK_MECHANISM Mech;
    Mech.mechanism      = CKM_DES_CBC_PAD;
    Mech.pParameter     = pucIv;
    Mech.ulParameterLen = uiIvLen;

	ulRV = pFunctionList->C_DecryptInit(hSession, &Mech, hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_DecryptInit ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
    }

    //дешифруем полностью всю шифрстроку
	ulRV = pFunctionList->C_Decrypt(hSession, (CK_BYTE_PTR)pucCipherText, (CK_ULONG)ulCipherTextLen,  pucPlainText, &uiPlainTextLen);
	if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Decrypt ошибка ---> " + asEtokenErrorString(ulRV));
        return "";
	}

    /*LOG*/Log.vLogCharAsHex("Результат дешифрования:", pucPlainText, uiPlainTextLen);
    /*LOG*/Log.vLogCharAsStr("Результат дешифрования:", pucPlainText, uiPlainTextLen);

    //-------------------------------------
    //удаляем ключ
	//--	if (key != (CK_OBJECT_HANDLE) 0) {}
    ulRV = pFunctionList->C_DestroyObject(hSession, hKey);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_DestroyObject ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //делогинимся
    ulRV = pFunctionList->C_Logout(hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
        MSG_WARNING("C_Logout ошибка ---> " + asEtokenErrorString(ulRV));
    }

    //-------------------------------------
    //закрываем сессию
    ulRV = pFunctionList->C_CloseSession(hSession);
    if (ulRV != CKR_OK) {
        /*LOG*/Log.vLog("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
        MSG_WARNING("C_CloseSession ошибка ---> " + asEtokenErrorString(ulRV));
    }

    Log.vOpen();

	return &pucPlainText[0];
}
//--------------------------------------------------------------------------
//TODO: vEnumReaderList
TStringList *CEToken::vEnumReaderList() {
    TStringList *pList = new TStringList();

	unsigned long int ulRV = 0;

	SCARDCONTEXT hContext;

    ulRV = SCardEstablishContext(SCARD_SCOPE_SYSTEM, 0, 0, &hContext);
	if (ulRV != 0) {
		//--leave("SCardEstablishContext ошибка...");
		return 0;
	}

	DWORD  dwLen	    = SCARD_AUTOALLOCATE;
	char  *pcReaderList = NULL;

    ulRV = SCardListReaders(hContext, 0, (LPTSTR)&pcReaderList, &dwLen);
	if (ulRV != 0) {
		//--leave("SCardListReaders ошибка...");
		return 0; 
	}

	char *pcReader = pcReaderList;
	for (int i = 0; *pcReader; pcReader += (strlen(pcReader) + 1), ++ i) {
		SCARD_READERSTATEA	srState;
		memset(&srState, 0, sizeof(srState));
		srState.szReader = pcReader;

        ulRV = SCardGetStatusChange(hContext, 0, &srState, 1);
        if (ulRV != 0) {
            continue;
		}
		if (srState.dwEventState & SCARD_STATE_PRESENT) {
			char *pCardNames = NULL;
			dwLen = SCARD_AUTOALLOCATE;

			ulRV  = SCardListCards(hContext, srState.rgbAtr, NULL, 0, (LPTSTR)&pCardNames, &dwLen);
			if (ulRV !=  SCARD_S_SUCCESS) {
                //--leave("SCardListCards failed...");
                return 0;
			}

			char *pProvider	= NULL;
			dwLen = SCARD_AUTOALLOCATE;
			ulRV = SCardGetCardTypeProviderName(hContext, pCardNames, SCARD_PROVIDER_CSP, (LPTSTR)&pProvider, &dwLen);
			if (ulRV == SCARD_S_SUCCESS) {
				if (!strcmp(pProvider, "eToken Base Cryptographic Provider")) {
					//--cout  <<  "Reader Name              : "  <<  reader  <<  endl;
					//--cout  <<  "Card/Token Name          : "  <<  pCardNames  <<  endl;

                    //MessageBox(0, pcReader, "Ioeaaea", MB_OK);
                    //MessageBox(0, pCardNames, "Ioeaaea", MB_OK);
                    pList->Add(AnsiString(pcReader) + '|' +  AnsiString(pCardNames));

					/*
					//MS format for passing reader name as container name. 
					//If more then one token is inserted, this is the way to select a specific token.
					string	szContainer	=  "\\\\.\\";
					szContainer  +=  reader;
					szContainer  +=  "\\"; 
					
					...
					*/
				}
				SCardFreeMemory(hContext, pProvider);
			}
			SCardFreeMemory(hContext, pCardNames);
		}
	}
	SCardFreeMemory(hContext, pcReaderList);
	SCardReleaseContext(hContext);

    return pList;
}
//--------------------------------------------------------------------------













