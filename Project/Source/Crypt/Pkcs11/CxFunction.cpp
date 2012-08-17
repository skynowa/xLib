/**
 * \file  CxFunction.cpp
 * \brief Pkcs11 function
 */


#include <xLib/Crypt/Pkcs11/CxFunction.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>
#include <xLib/Crypt/Pkcs11/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

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
bool
CxFunction::bGetList(
    CK_FUNCTION_LIST_PTR_PTR ppFunctionList  ///< receives pointer to function list
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GetFunctionList(ppFunctionList);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFunction::bGetStatus() {
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GetFunctionStatus(_m_hSession );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFunction::bCancel() {
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_CancelFunction(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFunction::bGetListEx() {
    /*DEBUG*/

    #if xTODO
        CK_RV ulRes = _m_pFunc->ETC_GetFunctionListEx();
        /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);
    #endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
