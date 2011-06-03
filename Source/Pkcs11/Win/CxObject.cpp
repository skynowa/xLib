/****************************************************************************
* Class name:  CxObject
* Description: Pkcs11 object
* File name:   CxObject.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:09:54
*
*****************************************************************************/


#include <xLib/Pkcs11/Win/CxObject.h>

#include <xLib/Pkcs11/Win/All.h>
#include <xLib/Pkcs11/Win/CxUtils.h>


/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxObject ()
CxObject::CxObject(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle()),
    _m_hObject (NULL)
{
    /*DEBUG*/xASSERT_DO(NULL != _m_pFunc,    return);
    /*DEBUG*/xASSERT_DO(NULL != _m_hSession, return);
    /*DEBUG*/xASSERT_DO(NULL == _m_hObject,  return);

}
//---------------------------------------------------------------------------
//TODO: ~CxObject ()
/*virtual*/
CxObject::~CxObject() {

}
//---------------------------------------------------------------------------
//TODO: CxObject (gets a handle)
CK_OBJECT_HANDLE
CxObject::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  NULL);

    return _m_hObject;
}
//---------------------------------------------------------------------------
//TODO: bSetHandle (assign object as a handle)
BOOL
CxObject::bSetHandle(
    CK_OBJECT_HANDLE hHandle
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
    /*DEBUG*/// _m_hObject - n/a

    _m_hObject = hHandle;

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bCreate (creates a new object)
BOOL
CxObject::bCreate(
    CK_ATTRIBUTE_PTR pTemplate,   /* the object's template */
    CK_ULONG         ulCount     /* attributes in template */
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
    /*DEBUG*/xASSERT_RET(NULL == _m_hObject,  FALSE);

    _m_ulRes = _m_pFunc->C_CreateObject(_m_hSession, pTemplate, ulCount, &_m_hObject);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bGetSize (gets the size of an object in bytes)
BOOL
CxObject::bGetSize(
    CK_ULONG_PTR pulSize    /* receives size of object */
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  FALSE);

    _m_ulRes = _m_pFunc->C_GetObjectSize(_m_hSession, _m_hObject, pulSize);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bCopy (copies an object, creating a new object for the copy)
BOOL
CxObject::bCopy(
    CK_ATTRIBUTE_PTR     pTemplate,   /* template for new object */
    CK_ULONG             ulCount,     /* attributes in template */
    CK_OBJECT_HANDLE_PTR phNewObject  /* receives handle of copy */
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  FALSE);

    _m_ulRes = _m_pFunc->C_CopyObject(_m_hSession, _m_hObject, pTemplate, ulCount, phNewObject);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: bFind (search for token and session objects that match a template, obtaining additional object handles)
BOOL
CxObject::bFind(
    CK_ATTRIBUTE_PTR               pTemplate,              /* attribute values to match */
    CK_ULONG                       ulCount,                /* attrs in search template */
    std::vector<CK_OBJECT_HANDLE> *pvecObjectHandles    /* [out] handles to objects */
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession,        FALSE);
    /*DEBUG*/// _m_hObject - n/a
    /*DEBUG*/xASSERT_RET(NULL != pTemplate,         FALSE);
    /*DEBUG*/// ulCount    - n/a
    /*DEBUG*/xASSERT_RET(NULL != pvecObjectHandles, FALSE);

    (*pvecObjectHandles).clear();

    _m_ulRes = _m_pFunc->C_FindObjectsInit(_m_hSession, pTemplate, ulCount);    // To find all attributes, set ulCount to 0.
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    const CK_ULONG   culMaxFindedObjects        = 512;
    CK_OBJECT_HANDLE hList[culMaxFindedObjects] = {0};
    CK_ULONG         ulFound                    = 0;

    _m_ulRes = _m_pFunc->C_FindObjects(_m_hSession, &hList[0], xARRAY_SIZE(hList), &ulFound);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
    /*DEBUG*/xASSERT_RET    (xARRAY_SIZE(hList) >= ulFound,                            FALSE);

    _m_ulRes = _m_pFunc->C_FindObjectsFinal(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    xCHECK_RET(0 == ulFound, FALSE);

    //-------------------------------------
    //���������� std::vector
    for (CK_ULONG i = 0; i < ulFound; ++ i) {
        (*pvecObjectHandles).push_back(hList[i]);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bGetAttributeValue (obtains the value of one or more object attributes)
BOOL CxObject::bGetAttributeValue(
    CK_ATTRIBUTE_PTR  pTemplate,  /* specifies attrs; gets vals */
    CK_ULONG          ulCount     /* attributes in template */
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  FALSE);

    _m_ulRes = _m_pFunc->C_GetAttributeValue(_m_hSession, _m_hObject, pTemplate, ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetAttributeValue (modifies the value of one or more object attributes)
BOOL
CxObject::bSetAttributeValue(
    CK_ATTRIBUTE_PTR  pTemplate,  /* specifies attrs and values */
    CK_ULONG          ulCount     /* attributes in template */
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  FALSE);

    _m_ulRes = _m_pFunc->C_SetAttributeValue(_m_hSession, _m_hObject, pTemplate, ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bDestroy (destroys an object)
BOOL
CxObject::bDestroy() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  FALSE);

    _m_ulRes = _m_pFunc->C_DestroyObject(_m_hSession, _m_hObject);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    _m_hObject = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bGetData
BOOL
CxObject::bGetData(
    CK_SLOT_ID     ulSlotId,
    const uString &cusUserPin,
    const uString &cusDataLabel,
    uString       *pusData
)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    bRes = objSession.bOpen(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRes = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&cusUserPin.at(0), cusUserPin.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_ATTRIBUTE atDataTemplate [] = {
            {CKA_LABEL, (CK_VOID_PTR)&cusDataLabel.at(0), cusDataLabel.size()}
        };

        CxObject objObject(objPkcs11, objSession);

        bRes = objObject.bFind(atDataTemplate, xARRAY_SIZE(atDataTemplate), &vechData);
        xCHECK_RET(0 >= vechData.size(), FALSE);
    }

    //-------------------------------------
    //CxObject
    CxObject objData(objPkcs11, objSession);

    objData.bSetHandle(vechData.at(0));

    //-------------------------------------
    //������ ������ � ������ ��������
    CK_ATTRIBUTE atrTamplate[] = {
        {CKA_VALUE, NULL_PTR, 0}
    };

    //Get data issuer, subject, and value attributes
    bRes = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    ULONG  ulValueLen = atrTamplate[0].ulValueLen;
    UCHAR *pucValue      = new UCHAR[ulValueLen];
    {
        memset(pucValue, '\0', ulValueLen);

        atrTamplate[0].pValue = pucValue;

        bRes = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        uString usValue = uString(pucValue, ulValueLen);

        (*pusData) = usValue;

    }
    delete [] pucValue;

    //-------------------------------------
    //
    bRes = objLogin.bLogout();
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //
    bRes = objSession.bClose();
    xCHECK_RET(FALSE == bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: bGetData
BOOL
CxObject::bGetData(
    CK_SLOT_ID            ulSlotId,
    const uString        &cusUserPin,
    std::vector<uString> *pusDataLabel,
    std::vector<uString> *pusDataValue
)
{
    /*DEBUG*/// ulSlotId - n/a
    /*DEBUG*/xASSERT_RET(false == cusUserPin.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pusDataLabel,       FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pusDataValue,       FALSE);

    BOOL bRes = FALSE;

    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    bRes = objSession.bOpen(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0);
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRes = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&cusUserPin.at(0), cusUserPin.size());
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_OBJECT_CLASS    ocData = CKO_DATA;

        CK_ATTRIBUTE atDataTemplate[] = {
            {CKA_CLASS, &ocData, sizeof(ocData)}
        };

        CxObject objObject(objPkcs11, objSession);

        bRes = objObject.bFind(atDataTemplate, xARRAY_SIZE(atDataTemplate), &vechData);
        xCHECK_RET(0 >= vechData.size(), FALSE);

        ////CK_OBJECT_HANDLE hData = vechData.at(0);
    }

    //-------------------------------------
    //CxObject
    (*pusDataLabel).clear();
    (*pusDataValue).clear();

    for (size_t i = 0; i < vechData.size(); ++ i) {
        CxObject objData(objPkcs11, objSession);

        objData.bSetHandle(vechData.at(i));

        //-------------------------------------
        //������ ������ � ������ ��������
        CK_ATTRIBUTE atrTamplate[] = {
            {CKA_LABEL, NULL_PTR, 0},
            {CKA_VALUE, NULL_PTR, 0}
        };

        //Get data issuer, subject, and value attributes
        bRes = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        /////
        ULONG  ulLabelLen      = atrTamplate[0].ulValueLen;
        UCHAR *pucLabel       = new UCHAR[ulLabelLen];
        atrTamplate[0].pValue = pucLabel;

        ULONG  ulValueLen     = atrTamplate[1].ulValueLen;
        UCHAR *pucValue          = new UCHAR[ulValueLen];
        atrTamplate[1].pValue = pucValue;

        ////
        bRes = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        xASSERT_RET(FALSE != bRes, FALSE);

        //���������
        uString usLabel = uString(pucLabel, ulLabelLen);
        pusDataLabel->push_back(usLabel);

        uString usValue = uString(pucValue, ulValueLen);
        pusDataValue->push_back(usValue);

        delete [] pucLabel;
        delete [] pucValue;
    }

    //-------------------------------------
    //
    bRes = objLogin.bLogout();
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //
    bRes = objSession.bClose();
    xCHECK_RET(FALSE == bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO:
BOOL
CxObject::bSetData(
    CK_SLOT_ID     ulSlotId,
    const uString &cusUserPin,
    const uString &cusDataLabel,
    const uString &cusData
)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    bRes = objSession.bOpen(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL_PTR, 0);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRes = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&cusUserPin.at(0), cusUserPin.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_ATTRIBUTE atDataTemplate [] = {
            {CKA_LABEL, (CK_VOID_PTR)&cusDataLabel.at(0), cusDataLabel.size()}
        };

        CxObject objObject(objPkcs11, objSession);

        bRes = objObject.bFind(atDataTemplate, xARRAY_SIZE(atDataTemplate), &vechData);
    }

    //-------------------------------------
    //CxObject
    CxObject objData(objPkcs11, objSession);

    if (false == vechData.empty()) {
        //-------------------------------------
        //������ ���������� - ����������
        objData.bSetHandle(vechData.at(0));

        //-------------------------------------
        //������ ������ � ������ ��������
        CK_ATTRIBUTE atrTamplate[] = {
            {CKA_VALUE, (CK_VOID_PTR)&cusData.at(0), cusData.size()}
        };

        bRes = objData.bSetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }
    else {
        //-------------------------------------
        //������ �� ���������� - ��������
        CK_OBJECT_CLASS ocData    = CKO_DATA;
        CK_BBOOL        bFalse    = FALSE;
        CK_BBOOL        bTrue     = TRUE;
        uString         usApplication;

        CK_ATTRIBUTE atrTamplate [] = {
            {CKA_CLASS,       &ocData,                            sizeof(ocData)      },
            {CKA_TOKEN,       &bTrue,                             sizeof(bTrue)       },
            {CKA_PRIVATE,     &bTrue,                             sizeof(bTrue)       },
            {CKA_LABEL,        (CK_VOID_PTR)&cusDataLabel.at(0),  cusDataLabel.size() },
          /*{CKA_APPLICATION,  (CK_VOID_PTR)&usApplication.at(0), usApplication.size()},*/
            {CKA_VALUE,        (CK_VOID_PTR)&cusData.at(0),       cusData.size()      },
            {CKA_MODIFIABLE,  &bTrue,                             sizeof(bTrue)       }
        };

        bRes = objData.bCreate(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //-------------------------------------
    //
    bRes = objLogin.bLogout();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //
    bRes = objSession.bClose();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

#if xTODO
    //---------------------------------------------------------------------------
    //TODO: bFindInit (initializes a search for token and session objects that match a template)
    BOOL CxObject::bFindInit(
        CK_ATTRIBUTE_PTR  pTemplate,  /* attribute values to match */
        CK_ULONG          ulCount     /* attrs in search template */
    )
    {
        /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
        /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
        /*DEBUG*/// _m_hObject - n/a

        _m_ulRes = _m_pFunc->C_FindObjectsInit(_m_hSession, pTemplate, ulCount);
        /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

        return TRUE;
    }
    //---------------------------------------------------------------------------
    //TODO: bFind (continues a search for token and session objects that match a template, obtaining additional object handles)
    BOOL CxObject::bFind(
        CK_OBJECT_HANDLE_PTR phObject,          /* gets obj. handles */
        CK_ULONG             ulMaxObjectCount,  /* max handles to get */
        CK_ULONG_PTR         pulObjectCount     /* actual # returned */
    )
    {
        /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
        /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
        /*DEBUG*/// _m_hObject - n/a

        _m_ulRes = _m_pFunc->C_FindObjects(_m_hSession, phObject, ulMaxObjectCount, pulObjectCount);
        /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
        /*DEBUG*/xASSERT_RET    (ulMaxObjectCount >= *pulObjectCount,                      FALSE);

        return TRUE;
    }
    //---------------------------------------------------------------------------
    //TODO: bFindFinal (finishes a search for token and session objects)
    BOOL CxObject::bFindFinal() {
        /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
        /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);
        /*DEBUG*/// _m_hObject - n/a

        _m_ulRes = _m_pFunc->C_FindObjectsFinal(_m_hSession);
        /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

        return TRUE;
    }
    //---------------------------------------------------------------------------
#endif
