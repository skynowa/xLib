/**
 * \file  CxLogin.cpp
 * \brief Pkcs11 login
 */


#include <xLib/Pkcs11/Win/CxLogin.h>

#include <xLib/Pkcs11/Win/CxUtils.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxLogin::CxLogin(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
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
BOOL
CxLogin::bLogin(
    CK_USER_TYPE    userType,  ///< user type
    CK_UTF8CHAR_PTR pPin,      ///< user's PIN
    CK_ULONG        ulPinLen   ///< length of the PIN
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    _m_ulRes = _m_pFunc->C_Login(_m_hSession, userType, pPin, ulPinLen);
    xCHECK_DO(
        CKR_PIN_INCORRECT == _m_ulRes,
        CxMsgBoxT::iShow(xT("Pin is incorrect"), xT("Pkcs11"), MB_OK + MB_ICONSTOP);
        return FALSE
    );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxLogin::bLogout() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    _m_ulRes = _m_pFunc->C_Logout(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#elif defined(xOS_ENV_UNIX)

#endif
