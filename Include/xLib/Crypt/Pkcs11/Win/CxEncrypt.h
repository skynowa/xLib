/**
 * \file  CxEncrypt.h
 * \brief Pkcs11 encrypt
 */


#ifndef xLib_Pkcs11_CxEncryptH
#define xLib_Pkcs11_CxEncryptH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Win/Common.h>
#include <xLib/Crypt/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxEncrypt :
    public CxNonCopyable
    /// Pkcs11 encrypt
{
    public:
                             CxEncrypt(const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxEncrypt();
            ///< destructor

        bool                 bInit    (CK_MECHANISM_PTR  pMechanism, CK_OBJECT_HANDLE hKey);
            ///< initializes an encryption operation
        bool                 bMake    (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pEncryptedData, CK_ULONG_PTR pulEncryptedDataLen);
            ///< encrypts single-part data
        bool                 bUpdate  (CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR  pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
            ///< continues a multiple-part encryption operation
        bool                 bFinal   (CK_BYTE_PTR pLastEncryptedPart, CK_ULONG_PTR pulLastEncryptedPartLen );
            ///< finishes a multiple-part encryption operation

        //Utils
        bool                 bMakeFile(const std::tstring_t &csInFilePath, const std::tstring_t &csOutFilePath, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
            ///< make file

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;        ///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;    ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxEncryptH
