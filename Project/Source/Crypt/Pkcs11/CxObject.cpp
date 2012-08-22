/**
 * \file  CxObject.cpp
 * \brief Pkcs11 object
 */


#include <xLib/Crypt/Pkcs11/CxObject.h>

#include <xLib/Crypt/Pkcs11/All.h>
#include <xLib/Crypt/Pkcs11/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxObject::CxObject(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle()),
    _m_hObject (NULL)
{
    /*DEBUG*/xASSERT_DO(NULL != _m_pFunc,    return);
    /*DEBUG*/xASSERT_DO(NULL != _m_hSession, return);
    /*DEBUG*/xASSERT_DO(NULL == _m_hObject,  return);

}
//---------------------------------------------------------------------------
/*virtual*/
CxObject::~CxObject() {

}
//---------------------------------------------------------------------------
CK_OBJECT_HANDLE
CxObject::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  NULL);

    return _m_hObject;
}
//---------------------------------------------------------------------------
bool
CxObject::bSetHandle(
    CK_OBJECT_HANDLE hHandle
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/// _m_hObject - n/a

    _m_hObject = hHandle;

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bCreate(
    CK_ATTRIBUTE_PTR pTemplate,    ///< the object's template
    CK_ULONG         ulCount    ///< attributes in template
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/xASSERT_RET(NULL == _m_hObject,  false);

    CK_RV ulRv = _m_pFunc->C_CreateObject(_m_hSession, pTemplate, ulCount, &_m_hObject);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bGetSize(
    CK_ULONG_PTR pulSize    ///< receives size of object
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  false);

    CK_RV ulRv = _m_pFunc->C_GetObjectSize(_m_hSession, _m_hObject, pulSize);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bCopy(
    CK_ATTRIBUTE_PTR     pTemplate,   ///< template for new object
    CK_ULONG             ulCount,     ///< attributes in template
    CK_OBJECT_HANDLE_PTR phNewObject  ///< receives handle of copy
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  false);

    CK_RV ulRv = _m_pFunc->C_CopyObject(_m_hSession, _m_hObject, pTemplate, ulCount, phNewObject);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//--------------------------------------------------------------------------
bool
CxObject::bFind(
    CK_ATTRIBUTE_PTR               pTemplate,           ///< attribute values to match
    CK_ULONG                       ulCount,             ///< attrs in search template
    std::vector<CK_OBJECT_HANDLE> *pvecObjectHandles    ///< [out] handles to objects
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,          false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession,       false);
    /*DEBUG*/// _m_hObject - n/a
    /*DEBUG*/xASSERT_RET(NULL != pTemplate,         false);
    /*DEBUG*/// ulCount    - n/a
    /*DEBUG*/xASSERT_RET(NULL != pvecObjectHandles, false);

    (*pvecObjectHandles).clear();

    CK_RV ulRv = _m_pFunc->C_FindObjectsInit(_m_hSession, pTemplate, ulCount);    // To find all attributes, set ulCount to 0.
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    const CK_ULONG   culMaxFindedObjects        = 512;
    CK_OBJECT_HANDLE hList[culMaxFindedObjects] = {0};
    CK_ULONG         ulFound                    = 0;

    ulRv = _m_pFunc->C_FindObjects(_m_hSession, &hList[0], xARRAY_SIZE(hList), &ulFound);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);
    /*DEBUG*/xASSERT_RET    (xARRAY_SIZE(hList) >= ulFound,                            false);

    ulRv = _m_pFunc->C_FindObjectsFinal(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    xCHECK_RET(0 == ulFound, false);

    //-------------------------------------
    //���������� std::vector
    for (CK_ULONG i = 0; i < ulFound; ++ i) {
        (*pvecObjectHandles).push_back(hList[i]);
    }

    return true;
}
//---------------------------------------------------------------------------
bool CxObject::bGetAttributeValue(
    CK_ATTRIBUTE_PTR pTemplate,  ///< specifies attrs; gets vals
    CK_ULONG         ulCount     ///< attributes in template
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  false);

    CK_RV ulRv = _m_pFunc->C_GetAttributeValue(_m_hSession, _m_hObject, pTemplate, ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bSetAttributeValue(
    CK_ATTRIBUTE_PTR pTemplate,  ///< specifies attrs and values
    CK_ULONG         ulCount     ///< attributes in template
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  false);

    CK_RV ulRv = _m_pFunc->C_SetAttributeValue(_m_hSession, _m_hObject, pTemplate, ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bDestroy() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hObject,  false);

    CK_RV ulRv = _m_pFunc->C_DestroyObject(_m_hSession, _m_hObject);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    _m_hObject = NULL;

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bGetData(
    CK_SLOT_ID          ulSlotId,
    const std::ustring_t &cusUserPin,
    const std::ustring_t &cusDataLabel,
    std::ustring_t       *pusData
)
{
    /*DEBUG*/

    bool bRv = false;

    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    bRv = objSession.bOpen(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRv = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&cusUserPin.at(0), cusUserPin.size());
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_ATTRIBUTE atDataTemplate [] = {
            {CKA_LABEL, (CK_VOID_PTR)&cusDataLabel.at(0), cusDataLabel.size()}
        };

        CxObject objObject(objPkcs11, objSession);

        bRv = objObject.bFind(atDataTemplate, xARRAY_SIZE(atDataTemplate), &vechData);
        xCHECK_RET(0 >= vechData.size(), false);
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
    bRv = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    ulong_t  ulValueLen = atrTamplate[0].ulValueLen;
    uchar_t *pucValue      = new uchar_t[ulValueLen];
    {
        memset(pucValue, '\0', ulValueLen);

        atrTamplate[0].pValue = pucValue;

        bRv = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        std::ustring_t usValue = std::ustring_t(pucValue, ulValueLen);

        (*pusData) = usValue;

    }
    delete [] pucValue;

    //-------------------------------------
    //
    bRv = objLogin.bLogout();
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //
    bRv = objSession.bClose();
    xCHECK_RET(false == bRv, false);

    return true;
}
//--------------------------------------------------------------------------
bool
CxObject::bGetData(
    CK_SLOT_ID                 ulSlotId,
    const std::ustring_t        &cusUserPin,
    std::vector<std::ustring_t> *pusDataLabel,
    std::vector<std::ustring_t> *pusDataValue
)
{
    /*DEBUG*/// ulSlotId - n/a
    /*DEBUG*/xASSERT_RET(false == cusUserPin.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pusDataLabel,       false);
    /*DEBUG*/xASSERT_RET(NULL  != pusDataValue,       false);

    bool bRv = false;

    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    bRv = objSession.bOpen(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0);
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRv = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&cusUserPin.at(0), cusUserPin.size());
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_OBJECT_CLASS    ocData = CKO_DATA;

        CK_ATTRIBUTE atDataTemplate[] = {
            {CKA_CLASS, &ocData, sizeof(ocData)}
        };

        CxObject objObject(objPkcs11, objSession);

        bRv = objObject.bFind(atDataTemplate, xARRAY_SIZE(atDataTemplate), &vechData);
        xCHECK_RET(0 >= vechData.size(), false);

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
        bRv = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        std::ustring_t usLabel;
        std::ustring_t usValue;

        {
            ulong_t ulLabelLen      = atrTamplate[0].ulValueLen;
            usLabel.resize(ulLabelLen);
            atrTamplate[0].pValue = &usLabel.at(0);

            ulong_t ulValueLen      = atrTamplate[1].ulValueLen;
            usValue.resize(ulValueLen);
            atrTamplate[1].pValue = &usValue.at(0);
        }

        bRv = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        xASSERT_RET(true == bRv, false);

        //���������
        pusDataLabel->push_back(usLabel);
        pusDataValue->push_back(usValue);
    }

    //-------------------------------------
    //
    bRv = objLogin.bLogout();
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //
    bRv = objSession.bClose();
    xCHECK_RET(false == bRv, false);

    return true;
}
//--------------------------------------------------------------------------
bool
CxObject::bSetData(
    CK_SLOT_ID          ulSlotId,
    const std::ustring_t &cusUserPin,
    const std::ustring_t &cusDataLabel,
    const std::ustring_t &cusData
)
{
    /*DEBUG*/

    bool bRv = false;

    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    bRv = objSession.bOpen(ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL_PTR, 0);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRv = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&cusUserPin.at(0), cusUserPin.size());
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_ATTRIBUTE atDataTemplate [] = {
            {CKA_LABEL, (CK_VOID_PTR)&cusDataLabel.at(0), cusDataLabel.size()}
        };

        CxObject objObject(objPkcs11, objSession);

        bRv = objObject.bFind(atDataTemplate, xARRAY_SIZE(atDataTemplate), &vechData);
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

        bRv = objData.bSetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xASSERT_RET(true == bRv, false);
    }
    else {
        //-------------------------------------
        //������ �� ���������� - ��������
        CK_OBJECT_CLASS ocData    = CKO_DATA;
        CK_BBOOL        bFalse    = false;
        CK_BBOOL        bTrue     = true;
        std::ustring_t         usApplication;

        CK_ATTRIBUTE atrTamplate [] = {
            {CKA_CLASS,       &ocData,                            sizeof(ocData)      },
            {CKA_TOKEN,       &bTrue,                             sizeof(bTrue)       },
            {CKA_PRIVATE,     &bTrue,                             sizeof(bTrue)       },
            {CKA_LABEL,        (CK_VOID_PTR)&cusDataLabel.at(0),  cusDataLabel.size() },
          /*{CKA_APPLICATION,  (CK_VOID_PTR)&usApplication.at(0), usApplication.size()},*/
            {CKA_VALUE,        (CK_VOID_PTR)&cusData.at(0),       cusData.size()      },
            {CKA_MODIFIABLE,  &bTrue,                             sizeof(bTrue)       }
        };

        bRv = objData.bCreate(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xASSERT_RET(true == bRv, false);
    }

    //-------------------------------------
    //
    bRv = objLogin.bLogout();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //
    bRv = objSession.bClose();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//--------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

#if xTODO
//---------------------------------------------------------------------------
bool 
CxObject::bFindInit(
    CK_ATTRIBUTE_PTR pTemplate,  ///< attribute values to match
    CK_ULONG         ulCount     ///< attrs in search template
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/// _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjectsInit(_m_hSession, pTemplate, ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool 
CxObject::bFind(
    CK_OBJECT_HANDLE_PTR phObject,          ///< gets obj. handles
    CK_ULONG             ulMaxObjectCount,  ///< max handles to get
    CK_ULONG_PTR         pulObjectCount     ///< actual # returned
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/// _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjects(_m_hSession, phObject, ulMaxObjectCount, pulObjectCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);
    /*DEBUG*/xASSERT_RET    (ulMaxObjectCount >= *pulObjectCount,                      false);

    return true;
}
//---------------------------------------------------------------------------
bool 
CxObject::bFindFinal() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);
    /*DEBUG*/// _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjectsFinal(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
#endif

xNAMESPACE_END(NxLib)

#endif
