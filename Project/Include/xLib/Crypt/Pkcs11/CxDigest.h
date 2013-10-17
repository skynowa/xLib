/**
 * \file  CxDigest.h
 * \brief Pkcs11 digest
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxDigest :
    private CxNonCopyable
    /// Pkcs11 digest
{
public:
                         CxDigest(const CxPkcs11 &cPkcs11, const CxSession &cSession);
        ///< constructor
    virtual             ~CxDigest();
        ///< destructor

    void_t               make(CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pDigest,
                             CK_ULONG_PTR pulDigestLen);
        ///< digests data in a single part
    void_t               encryptUpdate(CK_BYTE_PTR pPart, CK_ULONG ulPartLen,
                             CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
        ///< continues a multiple-part digesting and encryption operation
    void_t               final(CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);
        ///< finishes a multiple-part message-digesting operation
    void_t               init(CK_MECHANISM_PTR pMechanism);
        ///< initializes a message-digesting operation
    void_t               key(CK_OBJECT_HANDLE hKey);
        ///< continues a multi-part message-digesting operation, by digesting the value of a secret
        ///< key as part of the data already digested
    void_t               update(CK_BYTE_PTR pPart, CK_ULONG ulPartLen);
        ///< continues a multiple-part message-digesting operation

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif
