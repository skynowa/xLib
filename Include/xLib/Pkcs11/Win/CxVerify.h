/****************************************************************************
* Class name:  CxVerify
* Description: Pkcs11 verify
* File name:   CxVerify.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:14:22
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxVerifyH
#define xLib_Pkcs11_CxVerifyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Pkcs11/Win/CxSession.h>
//---------------------------------------------------------------------------
class CxVerify :
    public CxNonCopyable
{
    public:
                             CxVerify    (const CxPkcs11 &cPkcs11, const CxSession &cSession);
            ///< constructor
        virtual             ~CxVerify    ();
            ///< destructor

        BOOL                 bInit       (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        	///< initializes a verification operation, where the signature is an appendix to the data, and plaintext cannot cannot be recovered from the signature (e.g. DSA)
        BOOL                 bMake       (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen);
        	///< verifies a signature in a single-part operation,  where the signature is an appendix to the data, and plaintext cannot be recovered from the signature
        BOOL                 bFinal      (CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen);
        	///< finishes a multiple-part verification operation, checking the signature
        BOOL                 bRecoverInit(CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        	///< initializes a signature verification operation, where the data is recovered from the signature
        BOOL                 bRecover    (CK_BYTE_PTR pSignature, CK_ULONG ulSignatureLen, CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen);
        	///< verifies a signature in a single-part operation, where the data is recovered from the signature
        BOOL                 bUpdate     (CK_BYTE_PTR pPart, CK_ULONG ulPartLen);
        	///< continues a multiple-part verification operation, where the signature is an appendix to the data, and plaintext cannot be recovered from the signature

    private:
        BOOL                 _m_bRes;
        	///< for private use
        CK_RV                _m_ulRes;
        	///< for private use

        CK_FUNCTION_LIST_PTR _m_pFunc;
        	///< pointer to dll's functions list
        CK_SESSION_HANDLE    _m_hSession;
        	///< session handle
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxVerifyH
