/**
 * \file  CxKey.h
 * \brief Pkcs11 key
 */


#ifndef xLib_Pkcs11_CxKeyH
#define xLib_Pkcs11_CxKeyH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
//------------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxKey :
    private CxNonCopyable
    /// Pkcs11 key
{
public:
                         CxKey         (const CxPkcs11 &cPkcs11, const CxSession &cSession);
        ///< constructor
    virtual             ~CxKey         ();
        ///< destructor

    void                 generate      (CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pTemplate,          CK_ULONG         ulCount,                   CK_OBJECT_HANDLE_PTR phKey);
        ///< generates a secret key, creating a new key object
    void                 generatePair  (CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pPublicKeyTemplate, CK_ULONG         ulPublicKeyAttributeCount, CK_ATTRIBUTE_PTR     pPrivateKeyTemplate, CK_ULONG             ulPrivateKeyAttributeCount, CK_OBJECT_HANDLE_PTR phPublicKey,      CK_OBJECT_HANDLE_PTR phPrivateKey);
        ///< generates a public-key/private-key pair, creating new key objects
    void                 derive        (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hBaseKey,           CK_ATTRIBUTE_PTR pTemplate,                 CK_ULONG             ulAttributeCount,    CK_OBJECT_HANDLE_PTR phKey);
        ///< derives a key from a base key, creating a new key object
    void                 wrap          (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hWrappingKey,       CK_OBJECT_HANDLE hKey,                      CK_BYTE_PTR          pWrappedKey,         CK_ULONG_PTR         pulWrappedKeyLen);
        ///< wraps (i.e., encrypts) a key
    void                 unwrap        (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hUnwrappingKey,     CK_BYTE_PTR      pWrappedKey,               CK_ULONG             ulWrappedKeyLen,     CK_ATTRIBUTE_PTR     pTemplate,                  CK_ULONG             ulAttributeCount, CK_OBJECT_HANDLE_PTR phKey);
        ///< unwraps (decrypts) a wrapped key, creating a new key object

    void                 seedRandom    (CK_BYTE_PTR pSeed,       CK_ULONG ulSeedLen);
        ///< mixes additional seed material into the token's random number generator
    void                 generateRandom(CK_BYTE_PTR pRandomData, CK_ULONG ulRandomLen);
        ///< generates random data

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#endif // xLib_Pkcs11_CxKeyH
