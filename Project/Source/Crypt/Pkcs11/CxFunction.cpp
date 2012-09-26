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
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.pGetFuncList()),
    _m_hSession(a_cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/* virtual */
CxFunction::~CxFunction() {

}
//---------------------------------------------------------------------------
bool
CxFunction::bGetList(
    CK_FUNCTION_LIST_PTR_PTR a_ppFunctionList  ///< receives pointer to function list
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetFunctionList(a_ppFunctionList);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFunction::bGetStatus() {
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetFunctionStatus(_m_hSession );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFunction::bCancel() {
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_CancelFunction(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxFunction::bGetListEx() {
    /*DEBUG*/

    #if xTODO
        CK_RV ulRv = _m_pFunc->ETC_GetFunctionListEx();
        /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);
    #endif

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
