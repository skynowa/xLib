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
    _m_pFunc   (a_cPkcs11.funcList()),
    _m_hSession(a_cSession.handle()),
    _m_hObject (0UL)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    xTEST_DIFF(0UL, _m_hObject);
}
//---------------------------------------------------------------------------
/* virtual */
CxObject::~CxObject() {

}
//---------------------------------------------------------------------------
CK_OBJECT_HANDLE
CxObject::handle() const {
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    xTEST_DIFF(0UL, _m_hObject);

    return _m_hObject;
}
//---------------------------------------------------------------------------
void
CxObject::setHandle(
    CK_OBJECT_HANDLE a_hHandle
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    // _m_hObject - n/a

    _m_hObject = a_hHandle;
}
//---------------------------------------------------------------------------
void
CxObject::create(
    CK_ATTRIBUTE_PTR a_pTemplate,   ///< the object's template
    CK_ULONG         a_ulCount      ///< attributes in template
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    xTEST_EQ(0UL, _m_hObject);

    CK_RV ulRv = _m_pFunc->C_CreateObject(_m_hSession, a_pTemplate, a_ulCount, &_m_hObject);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxObject::size(
    CK_ULONG_PTR a_pulSize    ///< receives size of object
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    xTEST_DIFF(0UL, _m_hObject);

    CK_RV ulRv = _m_pFunc->C_GetObjectSize(_m_hSession, _m_hObject, a_pulSize);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxObject::copy(
    CK_ATTRIBUTE_PTR     a_pTemplate,   ///< template for new object
    CK_ULONG             a_ulCount,     ///< attributes in template
    CK_OBJECT_HANDLE_PTR a_phNewObject  ///< receives handle of copy
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    xTEST_DIFF(0UL, _m_hObject);

    CK_RV ulRv = _m_pFunc->C_CopyObject(_m_hSession, _m_hObject, a_pTemplate, a_ulCount, a_phNewObject);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//--------------------------------------------------------------------------
void
CxObject::find(
    CK_ATTRIBUTE_PTR               a_pTemplate,           ///< attribute values to match
    CK_ULONG                       a_ulCount,             ///< attrs in search template
    std::vector<CK_OBJECT_HANDLE> *a_pvecObjectHandles    ///< [out] handles to objects
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    // _m_hObject - n/a
    xTEST_PTR(a_pTemplate);
    // ulCount    - n/a
    xTEST_PTR(a_pvecObjectHandles);

    (*a_pvecObjectHandles).clear();

    CK_RV ulRv = _m_pFunc->C_FindObjectsInit(_m_hSession, a_pTemplate, a_ulCount);    // To find all attributes, set ulCount to 0.
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));

    const CK_ULONG   culMaxFindedObjects        = 512;
    CK_OBJECT_HANDLE hList[culMaxFindedObjects] = {0};
    CK_ULONG         ulFound                    = 0;

    ulRv = _m_pFunc->C_FindObjects(_m_hSession, &hList[0], static_cast<CK_ULONG>( xARRAY_SIZE(hList) ), &ulFound);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
    xTEST_GR_EQ(static_cast<ulong_t>( xARRAY_SIZE(hList) ), ulFound);

    ulRv = _m_pFunc->C_FindObjectsFinal(_m_hSession);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));

    xTEST_DIFF(0UL, ulFound);

    //-------------------------------------
    //���������� std::vector
    for (CK_ULONG i = 0; i < ulFound; ++ i) {
        (*a_pvecObjectHandles).push_back(hList[i]);
    }
}
//---------------------------------------------------------------------------
void
CxObject::attributeValue(
    CK_ATTRIBUTE_PTR a_pTemplate,  ///< specifies attrs; gets vals
    CK_ULONG         a_ulCount     ///< attributes in template
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    xTEST_DIFF(0UL, _m_hObject);

    CK_RV ulRv = _m_pFunc->C_GetAttributeValue(_m_hSession, _m_hObject, a_pTemplate, a_ulCount);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxObject::setAttributeValue(
    CK_ATTRIBUTE_PTR a_pTemplate,  ///< specifies attrs and values
    CK_ULONG         a_ulCount     ///< attributes in template
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    xTEST_DIFF(0UL, _m_hObject);

    CK_RV ulRv = _m_pFunc->C_SetAttributeValue(_m_hSession, _m_hObject, a_pTemplate, a_ulCount);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxObject::destroy() {
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    xTEST_DIFF(0UL, _m_hObject);

    CK_RV ulRv = _m_pFunc->C_DestroyObject(_m_hSession, _m_hObject);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));

    _m_hObject = 0UL;
}
//---------------------------------------------------------------------------
void
CxObject::data(
    CK_SLOT_ID            a_ulSlotId,
    const std::ustring_t &a_cusUserPin,
    const std::ustring_t &a_cusDataLabel,
    std::ustring_t       *a_pusData
)
{
    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    objSession.open(a_ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    objLogin.login(CKU_USER, (CK_UTF8CHAR_PTR)&a_cusUserPin.at(0), static_cast<CK_ULONG>( a_cusUserPin.size() ));

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_ATTRIBUTE atDataTemplate [] = {
            {CKA_LABEL, (CK_VOID_PTR)&a_cusDataLabel.at(0), static_cast<CK_ULONG>( a_cusDataLabel.size() )}
        };

        CxObject objObject(objPkcs11, objSession);

        objObject.find(atDataTemplate, static_cast<CK_ULONG>( xARRAY_SIZE(atDataTemplate) ), &vechData);
        xTEST_EQ(false, vechData.empty());
    }

    //-------------------------------------
    //CxObject
    CxObject objData(objPkcs11, objSession);

    objData.setHandle(vechData.at(0));

    //-------------------------------------
    //������ ������ � ������ ��������
    CK_ATTRIBUTE atrTamplate[] = {
        {CKA_VALUE, NULL_PTR, 0}
    };

    //Get data issuer, subject, and value attributes
    objData.attributeValue(atrTamplate, static_cast<CK_ULONG>( xARRAY_SIZE(atrTamplate) ));

    ulong_t  ulValueLen = atrTamplate[0].ulValueLen;
    uchar_t *pucValue      = new uchar_t[ulValueLen];
    {
        memset(pucValue, '\0', ulValueLen);

        atrTamplate[0].pValue = pucValue;

        objData.attributeValue(atrTamplate, static_cast<CK_ULONG>( xARRAY_SIZE(atrTamplate) ));

        std::ustring_t usValue = std::ustring_t(pucValue, ulValueLen);

        (*a_pusData) = usValue;

    }
    delete [] pucValue;

    //-------------------------------------
    //
    objLogin.logout();
    objSession.close();
}
//--------------------------------------------------------------------------
void
CxObject::data(
    CK_SLOT_ID            a_ulSlotId,
    const std::ustring_t &a_cusUserPin,
    std::vec_ustring_t   *a_pusDataLabel,
    std::vec_ustring_t   *a_pusDataValue
)
{
    // ulSlotId - n/a
    xTEST_EQ(false, a_cusUserPin.empty());
    xTEST_PTR(a_pusDataLabel);
    xTEST_PTR(a_pusDataValue);

    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    objSession.open(a_ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, 0, 0);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    objLogin.login(CKU_USER, (CK_UTF8CHAR_PTR)&a_cusUserPin.at(0), static_cast<CK_ULONG>( a_cusUserPin.size() ));

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_OBJECT_CLASS    ocData = CKO_DATA;

        CK_ATTRIBUTE atDataTemplate[] = {
            {CKA_CLASS, &ocData, sizeof(ocData)}
        };

        CxObject objObject(objPkcs11, objSession);

        objObject.find(atDataTemplate, static_cast<CK_ULONG>( xARRAY_SIZE(atDataTemplate) ), &vechData);
        xTEST_EQ(false, vechData.empty());

        ////CK_OBJECT_HANDLE hData = vechData.at(0);
    }

    //-------------------------------------
    //CxObject
    (*a_pusDataLabel).clear();
    (*a_pusDataValue).clear();

    for (size_t i = 0; i < vechData.size(); ++ i) {
        CxObject objData(objPkcs11, objSession);

        objData.setHandle(vechData.at(i));

        //-------------------------------------
        //������ ������ � ������ ��������
        CK_ATTRIBUTE atrTamplate[] = {
            {CKA_LABEL, NULL_PTR, 0},
            {CKA_VALUE, NULL_PTR, 0}
        };

        //Get data issuer, subject, and value attributes
        objData.attributeValue(atrTamplate, static_cast<CK_ULONG>( xARRAY_SIZE(atrTamplate) ));

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

        objData.attributeValue(atrTamplate, static_cast<CK_ULONG>( xARRAY_SIZE(atrTamplate) ));

        //���������
        a_pusDataLabel->push_back(usLabel);
        a_pusDataValue->push_back(usValue);
    }

    //-------------------------------------
    //
    objLogin.logout();
    objSession.close();
}
//--------------------------------------------------------------------------
void
CxObject::setData(
    CK_SLOT_ID            a_ulSlotId,
    const std::ustring_t &a_cusUserPin,
    const std::ustring_t &a_cusDataLabel,
    const std::ustring_t &a_cusData
)
{


    //-------------------------------------
    //CxPkcs11
    CxPkcs11 objPkcs11;

    //-------------------------------------
    //CxSession
    CxSession objSession(objPkcs11);

    objSession.open(a_ulSlotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL_PTR, 0);

    //-------------------------------------
    //CxLogin
    CxLogin objLogin(objPkcs11, objSession);

    objLogin.login(CKU_USER, (CK_UTF8CHAR_PTR)&a_cusUserPin.at(0), static_cast<CK_ULONG>( a_cusUserPin.size() ));

    //-------------------------------------
    //CxObject
    std::vector<CK_OBJECT_HANDLE> vechData;
    {
        CK_ATTRIBUTE atDataTemplate [] = {
            {CKA_LABEL, (CK_VOID_PTR)&a_cusDataLabel.at(0), static_cast<CK_ULONG>( a_cusDataLabel.size() )}
        };

        CxObject objObject(objPkcs11, objSession);

        objObject.find(atDataTemplate, static_cast<CK_ULONG>( xARRAY_SIZE(atDataTemplate) ), &vechData);
    }

    //-------------------------------------
    //CxObject
    CxObject objData(objPkcs11, objSession);

    if (false == vechData.empty()) {
        //-------------------------------------
        //������ ���������� - ����������
        objData.setHandle(vechData.at(0));

        //-------------------------------------
        //������ ������ � ������ ��������
        CK_ATTRIBUTE atrTamplate[] = {
            {CKA_VALUE, (CK_VOID_PTR)&a_cusData.at(0), static_cast<CK_ULONG>( a_cusData.size() )}
        };

        objData.setAttributeValue(atrTamplate, static_cast<CK_ULONG>( xARRAY_SIZE(atrTamplate) ));
    }
    else {
        //-------------------------------------
        //������ �� ���������� - ��������
        CK_OBJECT_CLASS ocData    = CKO_DATA;
        CK_BBOOL        bFalse    = false;  xUNUSED(bFalse);
        CK_BBOOL        bTrue     = true;
        std::ustring_t         usApplication;

        CK_ATTRIBUTE atrTamplate [] = {
            {CKA_CLASS,       &ocData,                             sizeof(ocData)         },
            {CKA_TOKEN,       &bTrue,                              sizeof(bTrue)          },
            {CKA_PRIVATE,     &bTrue,                              sizeof(bTrue)          },
            {CKA_LABEL,        (CK_VOID_PTR)&a_cusDataLabel.at(0), static_cast<CK_ULONG>( a_cusDataLabel.size() )  },
          /*{CKA_APPLICATION,  (CK_VOID_PTR)&a_usApplication.at(0),a_usApplication.size() },*/
            {CKA_VALUE,        (CK_VOID_PTR)&a_cusData.at(0),      static_cast<CK_ULONG>( a_cusData.size() )       },
            {CKA_MODIFIABLE,  &bTrue,                              sizeof(bTrue)          }
        };

        objData.create(atrTamplate, static_cast<CK_ULONG>( xARRAY_SIZE(atrTamplate) ));
    }

    //-------------------------------------
    //
    objLogin.logout();
    objSession.close();
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
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    // _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjectsInit(_m_hSession, pTemplate, ulCount);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));

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
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    // _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjects(_m_hSession, phObject, ulMaxObjectCount, pulObjectCount);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
    xTEST_GR_EQ(ulMaxObjectCount, *pulObjectCount);

    return true;
}
//---------------------------------------------------------------------------
bool
CxObject::bFindFinal() {
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
    // _m_hObject - n/a

    CK_RV ulRv = _m_pFunc->C_FindObjectsFinal(_m_hSession);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
#endif

xNAMESPACE_END(NxLib)

#endif
