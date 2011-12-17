/**
 * \file  CxDecrypt.h
 * \brief Pkcs11 decrypt
 */


#ifndef xLib_Pkcs11_CxDecryptH
#define xLib_Pkcs11_CxDecryptH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Win/Common.h>
#include <xLib/Crypt/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxDecrypt :
    private CxNonCopyable
    /// Pkcs11 decrypt
{
    public:
                             CxDecrypt    (const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxDecrypt    ();
            ///< destructor

        bool                 bInit        (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
            ///< initializes a decryption operation
        bool                 bMake        (CK_BYTE_PTR pEncryptedData, CK_ULONG ulEncryptedDataLen, CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen);
            ///< decrypts encrypted data in a single part
        bool                 bUpdate      (CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen);
            ///< continues a multiple-part decryption operation
        bool                 bFinal       (CK_BYTE_PTR pLastPart, CK_ULONG_PTR pulLastPartLen);
            ///< finishes a multiple-part decryption operation

        bool                 bDigestUpdate(CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen );
            ///< continues a multiple-part decryption and digesting operation
        bool                 bVerifyUpdate(CK_BYTE_PTR pEncryptedPart, CK_ULONG ulEncryptedPartLen, CK_BYTE_PTR pPart, CK_ULONG_PTR pulPartLen );
            ///< continues a multiple-part decryption and verify operation

        //Utils
        bool                 bMakeFile    (const std::tstring_t &csInFilePath, const std::tstring_t &csOutFilePath, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
            ///< make file

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;        ///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;    ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxDecryptH
