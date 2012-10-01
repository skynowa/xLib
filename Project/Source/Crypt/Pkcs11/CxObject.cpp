/**
 * \file  CxObject.cpp
 * \brief Pkcs11 object
 */


#include <xLib/Crypt/Pkcs11/CxObject.h>

#include <xLib/Crypt/Pkcs11/All.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxObject::CxObject(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.pGetFuncList()),
    _m_hSession(a_cSession.hGetHandle()),
    _m_hObject (NULL)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/xTEST_PTR(_m_hObject);

}
//---------------------------------------------------------------------------
/* virtual */
CxObject::~CxObject() {

}
//---------------------------------------------------------------------------
CK_OBJECT_HANDLE
CxObject::hGetHandle() const {
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/xTEST_PTR(_m_hObject);

    return _m_hObject;
}
//---------------------------------------------------------------------------
bool
CxObject::bSetHandle(
    CK_OBJECT_HANDLE a_hHandle
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/// _m_hObject - n/a

    _m_hObject = a_hHandle;

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bCreate(
    CK_ATTRIBUTE_PTR a_pTemplate,   ///< the object's template
    CK_ULONG         a_ulCount      ///< attributes in template
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/xTEST_PTR_FAIL(_m_hObject);

    CK_RV ulRv = _m_pFunc->C_CreateObject(_m_hSession, a_pTemplate, a_ulCount, &_m_hObject);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bGetSize(
    CK_ULONG_PTR a_pulSize    ///< receives size of object
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/xTEST_PTR(_m_hObject);

    CK_RV ulRv = _m_pFunc->C_GetObjectSize(_m_hSession, _m_hObject, a_pulSize);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bCopy(
    CK_ATTRIBUTE_PTR     a_pTemplate,   ///< template for new object
    CK_ULONG             a_ulCount,     ///< attributes in template
    CK_OBJECT_HANDLE_PTR a_phNewObject  ///< receives handle of copy
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/xTEST_PTR(_m_hObject);

    CK_RV ulRv = _m_pFunc->C_CopyObject(_m_hSession, _m_hObject, a_pTemplate, a_ulCount, a_phNewObject);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//--------------------------------------------------------------------------
bool
CxObject::bFind(
    CK_ATTRIBUTE_PTR               a_pTemplate,           ///< attribute values to match
    CK_ULONG                       a_ulCount,             ///< attrs in search template
    std::vector<CK_OBJECT_HANDLE> *a_pvecObjectHandles    ///< [out] handles to objects
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/// _m_hObject - n/a
    /*DEBUG*/xTEST_PTR(a_pTemplate);
    /*DEBUG*/// ulCount    - n/a
    /*DEBUG*/xTEST_PTR(a_pvecObjectHandles);

    (*a_pvecObjectHandles).clear();

    CK_RV ulRv = _m_pFunc->C_FindObjectsInit(_m_hSession, a_pTemplate, a_ulCount);    // To find all attributes, set ulCount to 0.
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    const CK_ULONG   culMaxFindedObjects        = 512;
    CK_OBJECT_HANDLE hList[culMaxFindedObjects] = {0};
    CK_ULONG         ulFound                    = 0;

    ulRv = _m_pFunc->C_FindObjects(_m_hSession, &hList[0], xARRAY_SIZE(hList), &ulFound);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
    /*DEBUG*/xTEST_GR_EQ(static_cast<ulong_t>( xARRAY_SIZE(hList) ), ulFound);

    ulRv = _m_pFunc->C_FindObjectsFinal(_m_hSession);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    xCHECK_RET(0 == ulFound, false);

    //-------------------------------------
    //���������� std::vector
    for (CK_ULONG i = 0; i < ulFound; ++ i) {
        (*a_pvecObjectHandles).push_back(hList[i]);
    }

    return true;
}
//---------------------------------------------------------------------------
bool CxObject::bGetAttributeValue(
    CK_ATTRIBUTE_PTR a_pTemplate,  ///< specifies attrs; gets vals
    CK_ULONG         a_ulCount     ///< attributes in template
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/xTEST_PTR(_m_hObject);

    CK_RV ulRv = _m_pFunc->C_GetAttributeValue(_m_hSession, _m_hObject, a_pTemplate, a_ulCount);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bSetAttributeValue(
    CK_ATTRIBUTE_PTR a_pTemplate,  ///< specifies attrs and values
    CK_ULONG         a_ulCount     ///< attributes in template
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/xTEST_PTR(_m_hObject);

    CK_RV ulRv = _m_pFunc->C_SetAttributeValue(_m_hSession, _m_hObject, a_pTemplate, a_ulCount);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bDestroy() {
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/xTEST_PTR(_m_hObject);

    CK_RV ulRv = _m_pFunc->C_DestroyObject(_m_hSession, _m_hObject);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    _m_hObject = NULL;

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bGetData(
    CK_SLOT_ID            a_ulSlotId,
    const std::ustring_t &a_cusUserPin,
    const std::ustring_t &a_cusDataLabel,
    std::ustring_t       *a_pusData
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

    bRv = objSession.bOpen(a_ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0);
    /*DEBUG*/xTEST_EQ(true, bRv);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRv = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&a_cusUserPin.at(0), a_cusUserPin.size());
    /*DEBUG*/xTEST_EQ(true, bRv);

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_ATTRIBUTE atDataTemplate [] = {
            {CKA_LABEL, (CK_VOID_PTR)&a_cusDataLabel.at(0), a_cusDataLabel.size()}
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
    /*DEBUG*/xTEST_EQ(true, bRv);

    ulong_t  ulValueLen = atrTamplate[0].ulValueLen;
    uchar_t *pucValue      = new uchar_t[ulValueLen];
    {
        memset(pucValue, '\0', ulValueLen);

        atrTamplate[0].pValue = pucValue;

        bRv = objData.bGetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xTEST_EQ(true, bRv);

        std::ustring_t usValue = std::ustring_t(pucValue, ulValueLen);

        (*a_pusData) = usValue;

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
    CK_SLOT_ID            a_ulSlotId,
    const std::ustring_t &a_cusUserPin,
    std::vec_ustring_t   *a_pusDataLabel,
    std::vec_ustring_t   *a_pusDataValue
)
{
    /*DEBUG*/// ulSlotId - n/a
    /*DEBUG*/xTEST_EQ(false, a_cusUserPin.empty());
    /*DEBUG*/xTEST_PTR(a_pusDataLabel);
    /*DEBUG*/xTEST_PTR(a_pusDataValue);

    bool bRv = false;

    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    bRv = objSession.bOpen(a_ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0);
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRv = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&a_cusUserPin.at(0), a_cusUserPin.size());
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
    (*a_pusDataLabel).clear();
    (*a_pusDataValue).clear();

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
        /*DEBUG*/xTEST_EQ(true, bRv);

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
        xTEST_EQ(true, bRv);

        //���������
        a_pusDataLabel->push_back(usLabel);
        a_pusDataValue->push_back(usValue);
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
    CK_SLOT_ID            a_ulSlotId,
    const std::ustring_t &a_cusUserPin,
    const std::ustring_t &a_cusDataLabel,
    const std::ustring_t &a_cusData
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

    bRv = objSession.bOpen(a_ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL_PTR, 0);
    /*DEBUG*/xTEST_EQ(true, bRv);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    bRv = objLogin.bLogin(CKU_USER, (CK_UTF8CHAR_PTR)&a_cusUserPin.at(0), a_cusUserPin.size());
    /*DEBUG*/xTEST_EQ(true, bRv);

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_ATTRIBUTE atDataTemplate [] = {
            {CKA_LABEL, (CK_VOID_PTR)&a_cusDataLabel.at(0), a_cusDataLabel.size()}
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
            {CKA_VALUE, (CK_VOID_PTR)&a_cusData.at(0), a_cusData.size()}
        };

        bRv = objData.bSetAttributeValue(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xTEST_EQ(true, bRv);
    }
    else {
        //-------------------------------------
        //������ �� ���������� - ��������
        CK_OBJECT_CLASS ocData    = CKO_DATA;
        CK_BBOOL        bFalse    = false;
        CK_BBOOL        bTrue     = true;
        std::ustring_t         usApplication;

        CK_ATTRIBUTE atrTamplate [] = {
            {CKA_CLASS,       &ocData,                             sizeof(ocData)         },
            {CKA_TOKEN,       &bTrue,                              sizeof(bTrue)          },
            {CKA_PRIVATE,     &bTrue,                              sizeof(bTrue)          },
            {CKA_LABEL,        (CK_VOID_PTR)&a_cusDataLabel.at(0), a_cusDataLabel.size()  },
          /*{CKA_APPLICATION,  (CK_VOID_PTR)&a_usApplication.at(0),a_usApplication.size() },*/
            {CKA_VALUE,        (CK_VOID_PTR)&a_cusData.at(0),      a_cusData.size()       },
            {CKA_MODIFIABLE,  &bTrue,                              sizeof(bTrue)          }
        };

        bRv = objData.bCreate(atrTamplate, xARRAY_SIZE(atrTamplate));
        /*DEBUG*/xTEST_EQ(true, bRv);
    }

    //-------------------------------------
    //
    bRv = objLogin.bLogout();
    /*DEBUG*/xTEST_EQ(true, bRv);

    //-------------------------------------
    //
    bRv = objSession.bClose();
    /*DEBUG*/xTEST_EQ(true, bRv);

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
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/// _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjectsInit(_m_hSession, pTemplate, ulCount);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

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
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/// _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjects(_m_hSession, phObject, ulMaxObjectCount, pulObjectCount);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
    /*DEBUG*/xTEST_GR_EQ(ulMaxObjectCount, *pulObjectCount);

    return true;
}
//---------------------------------------------------------------------------
bool 
CxObject::bFindFinal() {
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR(_m_hSession);
    /*DEBUG*/// _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjectsFinal(_m_hSession);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
#endif

xNAMESPACE_END(NxLib)

#endif
