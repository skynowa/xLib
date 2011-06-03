/****************************************************************************
* Class name:  CxKey
* Description: Pkcs11 key
* File name:   CxKey.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:10:29
*
*****************************************************************************/


#include <xLib/Pkcs11/Win/CxKey.h>

#include <xLib/Pkcs11/Win/CxUtils.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxKey ()
CxKey::CxKey(
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
//TODO: ~CxKey ()
/*virtual*/
CxKey::~CxKey() {

}
//---------------------------------------------------------------------------
//TODO: bGenerate (generates a secret key, creating a new key object)
BOOL
CxKey::bGenerate(
    CK_MECHANISM_PTR     pMechanism,  /* key generation mech. */
    CK_ATTRIBUTE_PTR     pTemplate,   /* template for new key */
    CK_ULONG             ulCount,     /* # of attrs in template */
    CK_OBJECT_HANDLE_PTR phKey        /* gets handle of new key */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GenerateKey(_m_hSession, pMechanism, pTemplate, ulCount, phKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bGeneratePair (generates a public-key/private-key pair, creating new key objects)
BOOL
CxKey::bGeneratePair(
    CK_MECHANISM_PTR     pMechanism,                  /* key-gen mech. */
    CK_ATTRIBUTE_PTR     pPublicKeyTemplate,          /* template for pub key */
    CK_ULONG             ulPublicKeyAttributeCount,   /* # pub. attrs. */
    CK_ATTRIBUTE_PTR     pPrivateKeyTemplate,         /* template for priv. key */
    CK_ULONG             ulPrivateKeyAttributeCount,  /* # priv. attrs. */
    CK_OBJECT_HANDLE_PTR phPublicKey,                 /* gets pub. key handle */
    CK_OBJECT_HANDLE_PTR phPrivateKey
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GenerateKeyPair(_m_hSession, pMechanism, pPublicKeyTemplate, ulPublicKeyAttributeCount, pPrivateKeyTemplate, ulPrivateKeyAttributeCount, phPublicKey, phPrivateKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bDerive (derives a key from a base key, creating a new key object)
BOOL
CxKey::bDerive(
    CK_MECHANISM_PTR     pMechanism,        /* key deriv. mech. */
    CK_OBJECT_HANDLE     hBaseKey,          /* base key */
    CK_ATTRIBUTE_PTR     pTemplate,         /* new key template */
    CK_ULONG             ulAttributeCount,  /* template length */
    CK_OBJECT_HANDLE_PTR phKey
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_DeriveKey(_m_hSession, pMechanism, hBaseKey, pTemplate, ulAttributeCount, phKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWrap (wraps (i.e., encrypts) a key)
BOOL
CxKey::bWrap(
    CK_MECHANISM_PTR pMechanism,      /* the wrapping mechanism */
    CK_OBJECT_HANDLE hWrappingKey,    /* wrapping key */
    CK_OBJECT_HANDLE hKey,            /* key to be wrapped */
    CK_BYTE_PTR      pWrappedKey,     /* gets wrapped key */
    CK_ULONG_PTR     pulWrappedKeyLen /* gets wrapped key size */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_WrapKey(_m_hSession, pMechanism, hWrappingKey, hKey, pWrappedKey, pulWrappedKeyLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bUnwrap (unwraps (decrypts) a wrapped key, creating a new key object)
BOOL
CxKey::bUnwrap(
    CK_MECHANISM_PTR     pMechanism,        /* unwrapping mech. */
    CK_OBJECT_HANDLE     hUnwrappingKey,    /* unwrapping key */
    CK_BYTE_PTR          pWrappedKey,       /* the wrapped key */
    CK_ULONG             ulWrappedKeyLen,   /* wrapped key len */
    CK_ATTRIBUTE_PTR     pTemplate,         /* new key template */
    CK_ULONG             ulAttributeCount,  /* template length */
    CK_OBJECT_HANDLE_PTR phKey
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_UnwrapKey(_m_hSession, pMechanism, hUnwrappingKey, pWrappedKey, ulWrappedKeyLen, pTemplate, ulAttributeCount, phKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSeedRandom (mixes additional seed material into the token's random number generator)
BOOL
CxKey::bSeedRandom(
    CK_BYTE_PTR pSeed,     /* the seed material */
    CK_ULONG    ulSeedLen  /* length of seed material */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SeedRandom(_m_hSession, pSeed, ulSeedLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bGenerateRandom (generates random data)
BOOL
CxKey::bGenerateRandom(
    CK_BYTE_PTR pRandomData,  /* receives the random data */
    CK_ULONG    ulRandomLen   /* # of bytes to generate */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GenerateRandom(_m_hSession, pRandomData, ulRandomLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
