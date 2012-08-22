/**
 * \file  CxLogin.cpp
 * \brief Pkcs11 login
 */


#include <xLib/Crypt/Pkcs11/CxLogin.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>
#include <xLib/Crypt/Pkcs11/CxUtils.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxLogin::CxLogin(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{
    /*DEBUG*/xASSERT_DO(NULL != _m_pFunc,    return);
    /*DEBUG*/xASSERT_DO(NULL != _m_hSession, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxLogin::~CxLogin() {

}
//---------------------------------------------------------------------------
bool
CxLogin::bLogin(
    CK_USER_TYPE    userType,  ///< user type
    CK_UTF8CHAR_PTR pPin,      ///< user's PIN
    CK_ULONG        ulPinLen   ///< length of the PIN
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);

    CK_RV ulRv = _m_pFunc->C_Login(_m_hSession, userType, pPin, ulPinLen);
    xCHECK_DO(
        CKR_PIN_INCORRECT == ulRv,
        CxMsgBoxT::iShow(xT("Pin is incorrect"), xT("Pkcs11"), MB_OK + MB_ICONSTOP);
        return false
    );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxLogin::bLogout() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, false);

    CK_RV ulRv = _m_pFunc->C_Logout(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
