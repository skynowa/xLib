/**
 * \file  CxPin.cpp
 * \brief Pkcs11 pin
 */


#include <xLib/Crypt/Pkcs11/CxPin.h>

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
CxPin::CxPin(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.pGetFuncList()),
    _m_hSession(a_cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxPin::~CxPin() {

}
//---------------------------------------------------------------------------
bool
CxPin::bInitToken(
    CK_SLOT_ID      a_slotID,    ///< ID of the token's slot
    CK_UTF8CHAR_PTR a_pPin,      ///< the SO's initial PIN
    CK_ULONG        a_ulPinLen,  ///< length in bytes of the PIN
    CK_UTF8CHAR_PTR a_pLabel     ///< 32-byte token label (blank padded)
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_InitToken(a_slotID, a_pPin, a_ulPinLen, a_pLabel);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxPin::bInitPIN(
    CK_UTF8CHAR_PTR a_pPin,      ///< the normal user's PIN
    CK_ULONG        a_ulPinLen   ///< length in bytes of the PIN
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_InitPIN(_m_hSession, a_pPin, a_ulPinLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxPin::bSetPIN(
    CK_UTF8CHAR_PTR a_pOldPin,   ///< the old PIN
    CK_ULONG        a_ulOldLen,  ///< length of the old PIN
    CK_UTF8CHAR_PTR a_pNewPin,   ///< the new PIN
    CK_ULONG        a_ulNewLen   ///< length of the new PIN
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_SetPIN(_m_hSession, a_pOldPin, a_ulOldLen, a_pNewPin, a_ulNewLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
