/**
 * \file  CxSign.h
 * \brief Pkcs11 sign
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxSign :
    private CxNonCopyable
    /// Pkcs11 sign
{
public:
                         CxSign(const CxPkcs11 &cPkcs11, const CxSession &cSession);
        ///< constructor
    virtual             ~CxSign();
        ///< destructor

    void_t               init(CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        ///< initializes a signature (private key encryption) operation, where the signature
        ///< is (will be) an appendix to the data, and plaintext cannot be recovered
        ///< from the signature
    void_t               make(CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature,
                             CK_ULONG_PTR pulSignatureLen);
        ///< signs (encrypts with private key) data in a single part, where the signature
        ///< is (will be) an appendix to the data, and plaintext cannot be recovered
        ///< from the signature
    void_t               update(CK_BYTE_PTR pPart, CK_ULONG ulPartLen);
        ///< continues a multiple-part signature operation,where the signature is (will be)
        ///< an appendix to the data, and plaintext cannot be recovered from the signature
    void_t               encryptUpdate(CK_BYTE_PTR pPart, CK_ULONG ulPartLen,
                             CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
        ///< continues a multiple-part signing and encryption operation
    void_t               final(CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen);
        ///< finishes a multiple-part signature operation, returning the signature
    void_t               recoverInit(CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        ///< initializes a signature operation, where the data can be recovered from the signature
    void_t               recover(CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature,
                             CK_ULONG_PTR pulSignatureLen);
        ///< signs data in a single operation, where the data can be recovered from the signature

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
