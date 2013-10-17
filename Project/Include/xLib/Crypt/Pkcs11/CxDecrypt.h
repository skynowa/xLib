/**
 * \file  CxDecrypt.h
 * \brief Pkcs11 decrypt
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxDecrypt :
    private CxNonCopyable
    /// Pkcs11 decrypt
{
public:
                         CxDecrypt(const CxPkcs11 &cPkcs11, const CxSession &cSession);
        ///< constructor
    virtual             ~CxDecrypt();
        ///< destructor

    void_t               init(CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        ///< initializes a decryption operation
    void_t               make(CK_BYTE_PTR pEncryptedData, CK_ULONG ulEncryptedDataLen,
                             CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen);
        ///< decrypts encrypted data in a single part
    void_t               update(CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen,
                             CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen);
        ///< continues a multiple-part decryption operation
    void_t               final(CK_BYTE_PTR pLastPart, CK_ULONG_PTR pulLastPartLen);
        ///< finishes a multiple-part decryption operation

    void_t               digestUpdate(CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen,
                             CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen );
        ///< continues a multiple-part decryption and digesting operation
    void_t               verifyUpdate(CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen,
                             CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen );
        ///< continues a multiple-part decryption and verify operation

    // Utils
    void_t               makeFile(std::ctstring_t &csInFilePath, std::ctstring_t &csOutFilePath,
                             CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        ///< make file

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Crypt/Pkcs11/CxDecrypt.cpp>
#endif
