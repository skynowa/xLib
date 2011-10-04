/**
 * \file  CxDigest.h
 * \brief Pkcs11 digest
 */


#ifndef xLib_Pkcs11_CxDigestH
#define xLib_Pkcs11_CxDigestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxDigest :
    public CxNonCopyable
    /// Pkcs11 digest
{
    public:
                             CxDigest      (const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxDigest      ();
            ///< destructor

        BOOL                 bMake         (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);
            ///< digests data in a single part
        BOOL                 bEncryptUpdate(CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
            ///< continues a multiple-part digesting and encryption operation
        BOOL                 bFinal        (CK_BYTE_PTR pDigest, CK_ULONG_PTR pulDigestLen);
            ///< finishes a multiple-part message-digesting operation
        BOOL                 bInit         (CK_MECHANISM_PTR pMechanism);
            ///< initializes a message-digesting operation
        BOOL                 bKey          (CK_OBJECT_HANDLE hKey);
            ///< continues a multi-part message-digesting operation, by digesting the value of a secret key as part of the data already digested
        BOOL                 bUpdate       (CK_BYTE_PTR pPart, CK_ULONG ulPartLen);
            ///< continues a multiple-part message-digesting operation

    private:
        BOOL                 _m_bRes;		///< for private use
        CK_RV                _m_ulRes;		///< for private use
        CK_FUNCTION_LIST_PTR _m_pFunc;		///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;	///< session handle
};
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxDigestH
