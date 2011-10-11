/**
 * \file  CxKey.cpp
 * \brief Pkcs11 key
 */


#include <xLib/Crypt/Pkcs11/Win/CxKey.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxKey::CxKey(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxKey::~CxKey() {

}
//---------------------------------------------------------------------------
BOOL
CxKey::bGenerate(
    CK_MECHANISM_PTR     pMechanism,  ///< key generation mech.
    CK_ATTRIBUTE_PTR     pTemplate,   ///< template for new key
    CK_ULONG             ulCount,     ///< # of attrs in template
    CK_OBJECT_HANDLE_PTR phKey        ///< gets handle of new key
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GenerateKey(_m_hSession, pMechanism, pTemplate, ulCount, phKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxKey::bGeneratePair(
    CK_MECHANISM_PTR     pMechanism,                  ///< key-gen mech.
    CK_ATTRIBUTE_PTR     pPublicKeyTemplate,          ///< template for pub key
    CK_ULONG             ulPublicKeyAttributeCount,   ///< # pub. attrs.
    CK_ATTRIBUTE_PTR     pPrivateKeyTemplate,         ///< template for priv. key
    CK_ULONG             ulPrivateKeyAttributeCount,  ///< # priv. attrs.
    CK_OBJECT_HANDLE_PTR phPublicKey,                 ///< gets pub. key handle
    CK_OBJECT_HANDLE_PTR phPrivateKey
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GenerateKeyPair(_m_hSession, pMechanism, pPublicKeyTemplate, ulPublicKeyAttributeCount, pPrivateKeyTemplate, ulPrivateKeyAttributeCount, phPublicKey, phPrivateKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxKey::bDerive(
    CK_MECHANISM_PTR     pMechanism,        ///< key deriv. mech.
    CK_OBJECT_HANDLE     hBaseKey,          ///< base key
    CK_ATTRIBUTE_PTR     pTemplate,         ///< new key template
    CK_ULONG             ulAttributeCount,  ///< template length
    CK_OBJECT_HANDLE_PTR phKey
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DeriveKey(_m_hSession, pMechanism, hBaseKey, pTemplate, ulAttributeCount, phKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxKey::bWrap(
    CK_MECHANISM_PTR pMechanism,      ///< the wrapping mechanism
    CK_OBJECT_HANDLE hWrappingKey,    ///< wrapping key
    CK_OBJECT_HANDLE hKey,            ///< key to be wrapped
    CK_BYTE_PTR      pWrappedKey,     ///< gets wrapped key
    CK_ULONG_PTR     pulWrappedKeyLen ///< gets wrapped key size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_WrapKey(_m_hSession, pMechanism, hWrappingKey, hKey, pWrappedKey, pulWrappedKeyLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxKey::bUnwrap(
    CK_MECHANISM_PTR     pMechanism,        ///< unwrapping mech.
    CK_OBJECT_HANDLE     hUnwrappingKey,    ///< unwrapping key
    CK_BYTE_PTR          pWrappedKey,       ///< the wrapped key
    CK_ULONG             ulWrappedKeyLen,   ///< wrapped key len
    CK_ATTRIBUTE_PTR     pTemplate,         ///< new key template
    CK_ULONG             ulAttributeCount,  ///< template length
    CK_OBJECT_HANDLE_PTR phKey
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_UnwrapKey(_m_hSession, pMechanism, hUnwrappingKey, pWrappedKey, ulWrappedKeyLen, pTemplate, ulAttributeCount, phKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxKey::bSeedRandom(
    CK_BYTE_PTR pSeed,     ///< the seed material
    CK_ULONG    ulSeedLen  ///< length of seed material
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_SeedRandom(_m_hSession, pSeed, ulSeedLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxKey::bGenerateRandom(
    CK_BYTE_PTR pRandomData,  ///< receives the random data
    CK_ULONG    ulRandomLen   ///< # of bytes to generate
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GenerateRandom(_m_hSession, pRandomData, ulRandomLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
