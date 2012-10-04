/**
 * \file  CxDigest.h
 * \brief Pkcs11 digest
 */


#ifndef xLib_Pkcs11_CxDigestH
#define xLib_Pkcs11_CxDigestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxDigest :
    private CxNonCopyable
    /// Pkcs11 digest
{
    public:
                             CxDigest      (const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxDigest      ();
            ///< destructor

        void                 vMake         (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);
            ///< digests data in a single part
        void                 vEncryptUpdate(CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
            ///< continues a multiple-part digesting and encryption operation
        void                 vFinal        (CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);
            ///< finishes a multiple-part message-digesting operation
        void                 vInit         (CK_MECHANISM_PTR pMechanism);
            ///< initializes a message-digesting operation
        void                 vKey          (CK_OBJECT_HANDLE hKey);
            ///< continues a multi-part message-digesting operation, by digesting the value of a secret key as part of the data already digested
        void                 vUpdate       (CK_BYTE_PTR pPart, CK_ULONG ulPartLen);
            ///< continues a multiple-part message-digesting operation

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;        ///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;    ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxDigestH
