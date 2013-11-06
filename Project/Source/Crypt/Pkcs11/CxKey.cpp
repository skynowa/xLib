/**
 * \file  CxKey.cpp
 * \brief Pkcs11 key
 */


#include <xLib/Crypt/Pkcs11/CxKey.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxKey::CxKey(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.funcList()),
    _m_hSession(a_cSession.handle())
{
}
//------------------------------------------------------------------------------
/* virtual */
CxKey::~CxKey() {

}
//------------------------------------------------------------------------------
void_t
CxKey::generate(
    CK_MECHANISM_PTR     a_pMechanism,  ///< key generation mech.
    CK_ATTRIBUTE_PTR     a_pTemplate,   ///< template for new key
    CK_ULONG             a_ulCount,     ///< # of attrs in template
    CK_OBJECT_HANDLE_PTR a_phKey        ///< gets handle of new key
)
{
    CK_RV ulRv = _m_pFunc->C_GenerateKey(_m_hSession, a_pMechanism, a_pTemplate, a_ulCount,
        a_phKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxKey::generatePair(
    CK_MECHANISM_PTR     a_pMechanism,                  ///< key-gen mech.
    CK_ATTRIBUTE_PTR     a_pPublicKeyTemplate,          ///< template for pub key
    CK_ULONG             a_ulPublicKeyAttributeCount,   ///< # pub. attrs.
    CK_ATTRIBUTE_PTR     a_pPrivateKeyTemplate,         ///< template for priv. key
    CK_ULONG             a_ulPrivateKeyAttributeCount,  ///< # priv. attrs.
    CK_OBJECT_HANDLE_PTR a_phPublicKey,                 ///< gets pub. key handle
    CK_OBJECT_HANDLE_PTR a_phPrivateKey
)
{
    CK_RV ulRv = _m_pFunc->C_GenerateKeyPair(_m_hSession, a_pMechanism,
        a_pPublicKeyTemplate, a_ulPublicKeyAttributeCount, a_pPrivateKeyTemplate,
        a_ulPrivateKeyAttributeCount, a_phPublicKey, a_phPrivateKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxKey::derive(
    CK_MECHANISM_PTR     a_pMechanism,        ///< key deriv. mech.
    CK_OBJECT_HANDLE     a_hBaseKey,          ///< base key
    CK_ATTRIBUTE_PTR     a_pTemplate,         ///< new key template
    CK_ULONG             a_ulAttributeCount,  ///< template length
    CK_OBJECT_HANDLE_PTR a_phKey
)
{
    CK_RV ulRv = _m_pFunc->C_DeriveKey(_m_hSession, a_pMechanism, a_hBaseKey, a_pTemplate,
        a_ulAttributeCount, a_phKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxKey::wrap(
    CK_MECHANISM_PTR a_pMechanism,      ///< the wrapping mechanism
    CK_OBJECT_HANDLE a_hWrappingKey,    ///< wrapping key
    CK_OBJECT_HANDLE a_hKey,            ///< key to be wrapped
    CK_BYTE_PTR      a_pWrappedKey,     ///< gets wrapped key
    CK_ULONG_PTR     a_pulWrappedKeyLen ///< gets wrapped key size
)
{
    CK_RV ulRv = _m_pFunc->C_WrapKey(_m_hSession, a_pMechanism, a_hWrappingKey, a_hKey,
        a_pWrappedKey, a_pulWrappedKeyLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxKey::unwrap(
    CK_MECHANISM_PTR     a_pMechanism,        ///< unwrapping mech.
    CK_OBJECT_HANDLE     a_hUnwrappingKey,    ///< unwrapping key
    CK_BYTE_PTR          a_pWrappedKey,       ///< the wrapped key
    CK_ULONG             a_ulWrappedKeyLen,   ///< wrapped key len
    CK_ATTRIBUTE_PTR     a_pTemplate,         ///< new key template
    CK_ULONG             a_ulAttributeCount,  ///< template length
    CK_OBJECT_HANDLE_PTR a_phKey
)
{
    CK_RV ulRv = _m_pFunc->C_UnwrapKey(_m_hSession, a_pMechanism, a_hUnwrappingKey, a_pWrappedKey,
        a_ulWrappedKeyLen, a_pTemplate, a_ulAttributeCount, a_phKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxKey::seedRandom(
    CK_BYTE_PTR pSeed,     ///< the seed material
    CK_ULONG    ulSeedLen  ///< length of seed material
)
{
    CK_RV ulRv = _m_pFunc->C_SeedRandom(_m_hSession, pSeed, ulSeedLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxKey::generateRandom(
    CK_BYTE_PTR a_pRandomData,  ///< receives the random data
    CK_ULONG    a_ulRandomLen   ///< # of bytes to generate
)
{
    CK_RV ulRv = _m_pFunc->C_GenerateRandom(_m_hSession, a_pRandomData, a_ulRandomLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
