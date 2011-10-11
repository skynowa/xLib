/**
 * \file  CxFunction.cpp
 * \brief Pkcs11 function
 */


#include <xLib/Crypt/Pkcs11/Win/CxFunction.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFunction::CxFunction(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxFunction::~CxFunction() {

}
//---------------------------------------------------------------------------
BOOL
CxFunction::bGetList(
    CK_FUNCTION_LIST_PTR_PTR ppFunctionList  ///< receives pointer to function list
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GetFunctionList(ppFunctionList);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFunction::bGetStatus() {
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GetFunctionStatus(_m_hSession );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFunction::bCancel() {
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_CancelFunction(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFunction::bGetListEx() {
    /*DEBUG*/

    #if xTODO
        CK_RV ulRes = _m_pFunc->ETC_GetFunctionListEx();
        /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);
    #endif

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
