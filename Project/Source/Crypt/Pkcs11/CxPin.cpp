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
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxPin::~CxPin() {

}
//---------------------------------------------------------------------------
bool
CxPin::bInitToken(
    CK_SLOT_ID      slotID,    ///< ID of the token's slot
    CK_UTF8CHAR_PTR pPin,      ///< the SO's initial PIN
    CK_ULONG        ulPinLen,  ///< length in bytes of the PIN
    CK_UTF8CHAR_PTR pLabel     ///< 32-byte token label (blank padded)
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_InitToken(slotID, pPin, ulPinLen, pLabel);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxPin::bInitPIN(
    CK_UTF8CHAR_PTR pPin,      ///< the normal user's PIN
    CK_ULONG        ulPinLen   ///< length in bytes of the PIN
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_InitPIN(_m_hSession, pPin, ulPinLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxPin::bSetPIN(
    CK_UTF8CHAR_PTR pOldPin,   ///< the old PIN
    CK_ULONG        ulOldLen,  ///< length of the old PIN
    CK_UTF8CHAR_PTR pNewPin,   ///< the new PIN
    CK_ULONG        ulNewLen   ///< length of the new PIN
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_SetPIN(_m_hSession, pOldPin, ulOldLen, pNewPin, ulNewLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
