/**
 * \file  CxVerify.h
 * \brief Pkcs11 verify
 */


#ifndef xLib_Pkcs11_CxVerifyH
#define xLib_Pkcs11_CxVerifyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxVerify :
    private CxNonCopyable
    /// Pkcs11 verify
{
    public:
                             CxVerify    (const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxVerify    ();
            ///< destructor

        bool                 bInit       (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
            ///< initializes a verification operation, where the signature is an appendix to the data, and plaintext cannot cannot be recovered from the signature (e.g. DSA)
        bool                 bMake       (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen);
            ///< verifies a signature in a single-part operation,  where the signature is an appendix to the data, and plaintext cannot be recovered from the signature
        bool                 bFinal      (CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen);
            ///< finishes a multiple-part verification operation, checking the signature
        bool                 bRecoverInit(CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
            ///< initializes a signature verification operation, where the data is recovered from the signature
        bool                 bRecover    (CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen, CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen);
            ///< verifies a signature in a single-part operation, where the data is recovered from the signature
        bool                 bUpdate     (CK_BYTE_PTR pPart, CK_ULONG ulPartLen);
            ///< continues a multiple-part verification operation, where the signature is an appendix to the data, and plaintext cannot be recovered from the signature

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;         ///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;    ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxVerifyH
