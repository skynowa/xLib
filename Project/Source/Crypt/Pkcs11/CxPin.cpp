/**
 * \file  CxPin.cpp
 * \brief Pkcs11 pin
 */


#include <xLib/Crypt/Pkcs11/CxPin.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>


#if   xOS_ENV_WIN

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
    _m_pFunc   (a_cPkcs11.funcList()),
    _m_hSession(a_cSession.handle())
{
}
//---------------------------------------------------------------------------
/* virtual */
CxPin::~CxPin() {

}
//---------------------------------------------------------------------------
void
CxPin::initToken(
    CK_SLOT_ID      a_slotID,    ///< ID of the token's slot
    CK_UTF8CHAR_PTR a_pPin,      ///< the SO's initial PIN
    CK_ULONG        a_ulPinLen,  ///< length in bytes of the PIN
    CK_UTF8CHAR_PTR a_pLabel     ///< 32-byte token label (blank padded)
)
{
    CK_RV ulRv = _m_pFunc->C_InitToken(a_slotID, a_pPin, a_ulPinLen, a_pLabel);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxPin::initPIN(
    CK_UTF8CHAR_PTR a_pPin,      ///< the normal user's PIN
    CK_ULONG        a_ulPinLen   ///< length in bytes of the PIN
)
{
    CK_RV ulRv = _m_pFunc->C_InitPIN(_m_hSession, a_pPin, a_ulPinLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxPin::setPIN(
    CK_UTF8CHAR_PTR a_pOldPin,   ///< the old PIN
    CK_ULONG        a_ulOldLen,  ///< length of the old PIN
    CK_UTF8CHAR_PTR a_pNewPin,   ///< the new PIN
    CK_ULONG        a_ulNewLen   ///< length of the new PIN
)
{
    CK_RV ulRv = _m_pFunc->C_SetPIN(_m_hSession, a_pOldPin, a_ulOldLen, a_pNewPin, a_ulNewLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
