/**
 * \file  CxPin.cpp
 * \brief Pkcs11 pin
 */


#include <xLib/Crypt/Pkcs11/Win/CxPin.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
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
/*virtual*/
CxPin::~CxPin() {

}
//---------------------------------------------------------------------------
BOOL
CxPin::bInitToken(
    CK_SLOT_ID      slotID,    ///< ID of the token's slot
    CK_UTF8CHAR_PTR pPin,      ///< the SO's initial PIN
    CK_ULONG        ulPinLen,  ///< length in bytes of the PIN
    CK_UTF8CHAR_PTR pLabel     ///< 32-byte token label (blank padded)
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_InitToken(slotID, pPin, ulPinLen, pLabel);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxPin::bInitPIN(
    CK_UTF8CHAR_PTR pPin,      ///< the normal user's PIN
    CK_ULONG        ulPinLen   ///< length in bytes of the PIN
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_InitPIN(_m_hSession, pPin, ulPinLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxPin::bSetPIN(
    CK_UTF8CHAR_PTR pOldPin,   ///< the old PIN
    CK_ULONG        ulOldLen,  ///< length of the old PIN
    CK_UTF8CHAR_PTR pNewPin,   ///< the new PIN
    CK_ULONG        ulNewLen   ///< length of the new PIN
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SetPIN(_m_hSession, pOldPin, ulOldLen, pNewPin, ulNewLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#elif defined(xOS_ENV_UNIX)

#endif
