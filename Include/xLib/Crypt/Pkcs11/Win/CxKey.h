/**
 * \file  CxKey.h
 * \brief Pkcs11 key
 */


#ifndef xLib_Pkcs11_CxKeyH
#define xLib_Pkcs11_CxKeyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Win/Common.h>
#include <xLib/Crypt/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

class CxKey :
    public CxNonCopyable
    /// Pkcs11 key
{
    public:
                             CxKey          (const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxKey          ();
            ///< destructor

        BOOL                 bGenerate      (CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pTemplate,          CK_ULONG         ulCount,                   CK_OBJECT_HANDLE_PTR phKey);
            ///< generates a secret key, creating a new key object
        BOOL                 bGeneratePair  (CK_MECHANISM_PTR pMechanism, CK_ATTRIBUTE_PTR pPublicKeyTemplate, CK_ULONG         ulPublicKeyAttributeCount, CK_ATTRIBUTE_PTR     pPrivateKeyTemplate, CK_ULONG             ulPrivateKeyAttributeCount, CK_OBJECT_HANDLE_PTR phPublicKey,      CK_OBJECT_HANDLE_PTR phPrivateKey);
            ///< generates a public-key/private-key pair, creating new key objects
        BOOL                 bDerive        (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hBaseKey,           CK_ATTRIBUTE_PTR pTemplate,                 CK_ULONG             ulAttributeCount,    CK_OBJECT_HANDLE_PTR phKey);
            ///< derives a key from a base key, creating a new key object
        BOOL                 bWrap          (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hWrappingKey,       CK_OBJECT_HANDLE hKey,                      CK_BYTE_PTR          pWrappedKey,         CK_ULONG_PTR         pulWrappedKeyLen);
            ///< wraps (i.e., encrypts) a key
        BOOL                 bUnwrap        (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hUnwrappingKey,     CK_BYTE_PTR      pWrappedKey,               CK_ULONG             ulWrappedKeyLen,     CK_ATTRIBUTE_PTR     pTemplate,                  CK_ULONG             ulAttributeCount, CK_OBJECT_HANDLE_PTR phKey);
            ///< unwraps (decrypts) a wrapped key, creating a new key object

        BOOL                 bSeedRandom    (CK_BYTE_PTR pSeed,       CK_ULONG ulSeedLen);
            ///< mixes additional seed material into the token's random number generator
        BOOL                 bGenerateRandom(CK_BYTE_PTR pRandomData, CK_ULONG ulRandomLen);
            ///< generates random data

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;		///< pointerto dll's functions list
        CK_SESSION_HANDLE    _m_hSession;	///< session handle
};

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxKeyH
