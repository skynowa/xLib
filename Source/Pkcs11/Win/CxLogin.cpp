/****************************************************************************
* Class name:  CxLogin
* Description: Pkcs11 login
* File name:   CxLogin.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:03:30
*
*****************************************************************************/


#include <xLib/Pkcs11/CxLogin.h>

#include <xLib/Pkcs11/CxUtils.h>
#include <xLib/Gui/Win/Dialogs/CxMsgBoxT.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxLogin (const CxPkcs11 &cPkcs11)
CxLogin::CxLogin(const CxPkcs11 &cPkcs11, const CxSession &cSession) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{
    /*DEBUG*/xASSERT_DO(NULL != _m_pFunc,    return);
    /*DEBUG*/xASSERT_DO(NULL != _m_hSession, return);
}
//---------------------------------------------------------------------------
//TODO: ~CxLogin ()
CxLogin::~CxLogin() {

}
//---------------------------------------------------------------------------
//TODO: bLogin (logs a user into a token)
BOOL
CxLogin::bLogin(
    CK_USER_TYPE      userType,  /* the user type */
    CK_UTF8CHAR_PTR   pPin,      /* the user's PIN */
    CK_ULONG          ulPinLen   /* the length of the PIN */
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
//TODO: bLogout (logs a user out from a token)
BOOL
CxLogin::bLogout() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    _m_ulRes = _m_pFunc->C_Logout(_m_hSession); 
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
