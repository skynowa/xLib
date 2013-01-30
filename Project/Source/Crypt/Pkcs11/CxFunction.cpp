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
    _m_pFunc   (a_cPkcs11.funcList()),
    _m_hSession(a_cSession.handle())
{
}
//---------------------------------------------------------------------------
/* virtual */
CxFunction::~CxFunction() {

}
//---------------------------------------------------------------------------
void
CxFunction::list(
    CK_FUNCTION_LIST_PTR_PTR a_ppFunctionList  ///< receives pointer to function list
)
{
    CK_RV ulRv = _m_pFunc->C_GetFunctionList(a_ppFunctionList);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxFunction::status() {
    CK_RV ulRv = _m_pFunc->C_GetFunctionStatus(_m_hSession);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxFunction::cancel() {
    CK_RV ulRv = _m_pFunc->C_CancelFunction(_m_hSession);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxFunction::listEx() {
    // TODO: CxFunction::listEx
    #if xTODO
        CK_RV ulRv = _m_pFunc->ETC_GetFunctionListEx();
        xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
    #endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
