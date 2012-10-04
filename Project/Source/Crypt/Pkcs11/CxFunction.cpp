/**
 * \file  CxFunction.cpp
 * \brief Pkcs11 function
 */


#include <xLib/Crypt/Pkcs11/CxFunction.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>


#if   xOS_ENV_WIN

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
void
CxFunction::vGetList(
    CK_FUNCTION_LIST_PTR_PTR a_ppFunctionList  ///< receives pointer to function list
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetFunctionList(a_ppFunctionList);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxFunction::vGetStatus() {
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetFunctionStatus(_m_hSession);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxFunction::vCancel() {
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_CancelFunction(_m_hSession);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxFunction::vGetListEx() {
    /*DEBUG*/

    #if xTODO
        CK_RV ulRv = _m_pFunc->ETC_GetFunctionListEx();
        /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
    #endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
