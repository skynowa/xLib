/**
 * \file  CxPkcs11.cpp
 * \brief Aladdin eToken, PKCS #11
 */


#include <xLib/Crypt/Pkcs11/Win/CxPkcs11.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxPkcs11::CxPkcs11() :
    _m_pFunc      (NULL),
    _m_dllETPkcs11()
{
    /*DEBUG*/xASSERT_DO(NULL == _m_pFunc, return);
    /*DEBUG*/// _m_dllETPkcs11 - n/a

    (void)_bLoadETPkcs11();
    (void)bInitialize();
}
//---------------------------------------------------------------------------
/*virtual*/
CxPkcs11::~CxPkcs11() {
    /*DEBUG*/

    (void)bFinalize();
}
//---------------------------------------------------------------------------
CK_FUNCTION_LIST_PTR
CxPkcs11::pGetFuncList() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc, NULL);

    return _m_pFunc;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxPkcs11::_bLoadETPkcs11() {
    /*DEBUG*/

    BOOL bRes = _m_dllETPkcs11.bLoad(xT("eTPkcs11.dll"));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    CK_C_GetFunctionList pFunctionList = NULL;

    (FARPROC &)pFunctionList = (FARPROC)_m_dllETPkcs11.fpGetProcAddress(xT("C_GetFunctionList"));
    /*DEBUG*/xASSERT_RET(NULL != pFunctionList, FALSE);

    CK_RV ulRes = pFunctionList(&_m_pFunc);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);
    /*DEBUG*/xASSERT_RET    (NULL   != _m_pFunc,                                       FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxPkcs11::bInitialize() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc, FALSE);

    CK_RV ulRes = _m_pFunc->C_Initialize(NULL_PTR);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxPkcs11::bFinalize() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc, FALSE);

    CK_RV ulRes = _m_pFunc->C_Finalize(NULL_PTR);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
