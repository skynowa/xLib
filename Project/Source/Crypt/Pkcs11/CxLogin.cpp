/**
 * \file  CxLogin.cpp
 * \brief Pkcs11 login
 */


#include <xLib/Crypt/Pkcs11/CxLogin.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxLogin::CxLogin(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.pFuncList()),
    _m_hSession(a_cSession.hHandle())
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
}
//---------------------------------------------------------------------------
/* virtual */
CxLogin::~CxLogin() {

}
//---------------------------------------------------------------------------
void
CxLogin::vLogin(
    CK_USER_TYPE    a_userType,  ///< user type
    CK_UTF8CHAR_PTR a_pPin,      ///< user's PIN
    CK_ULONG        a_ulPinLen   ///< length of the PIN
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);

    CK_RV ulRv = _m_pFunc->C_Login(_m_hSession, a_userType, a_pPin, a_ulPinLen);
    xCHECK_DO(
        CKR_PIN_INCORRECT == ulRv,
        CxMsgBoxT::iShow(xT("Pin is incorrect"), xT("Pkcs11"), MB_OK + MB_ICONSTOP);
        return
    );
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxLogin::vLogout() {
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);

    CK_RV ulRv = _m_pFunc->C_Logout(_m_hSession);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
