/****************************************************************************
* Class name:  CxPin
* Description: Pkcs11 pin
* File name:   CxPin.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:09:04
*
*****************************************************************************/


#include <xLib/Pkcs11/Win/CxPin.h>

#include <xLib/Pkcs11/Win/CxUtils.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxPin ()
CxPin::CxPin(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
//TODO: ~CxPin ()
/*virtual*/
CxPin::~CxPin() {

}
//---------------------------------------------------------------------------
//TODO: bInitToken (initializes a token)
BOOL
CxPin::bInitToken(
    CK_SLOT_ID      slotID,    /* ID of the token's slot */
    CK_UTF8CHAR_PTR pPin,      /* the SO's initial PIN */
    CK_ULONG        ulPinLen,  /* length in bytes of the PIN */
    CK_UTF8CHAR_PTR pLabel     /* 32-byte token label (blank padded) */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_InitToken(slotID, pPin, ulPinLen, pLabel);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bInitPIN (initializes the normal user's PIN)
BOOL
CxPin::bInitPIN(
    CK_UTF8CHAR_PTR pPin,      /* the normal user's PIN */
    CK_ULONG        ulPinLen   /* length in bytes of the PIN */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_InitPIN(_m_hSession, pPin, ulPinLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetPIN (modifies the PIN of the user who is logged in)
BOOL
CxPin::bSetPIN(
    CK_UTF8CHAR_PTR pOldPin,   /* the old PIN */
    CK_ULONG        ulOldLen,  /* length of the old PIN */
    CK_UTF8CHAR_PTR pNewPin,   /* the new PIN */
    CK_ULONG        ulNewLen   /* length of the new PIN */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SetPIN(_m_hSession, pOldPin, ulOldLen, pNewPin, ulNewLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
