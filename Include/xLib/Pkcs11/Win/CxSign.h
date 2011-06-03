/****************************************************************************
* Class name:  CxSign
* Description: Pkcs11 sign
* File name:   CxSign.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:12:48
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxSignH
#define xLib_Pkcs11_CxSignH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
#include <xLib/Pkcs11/CxSession.h>
//---------------------------------------------------------------------------
class CxSign :
    public CxNonCopyable
{
    public:
                             CxSign        (const CxPkcs11 &cPkcs11, const CxSession &cSession);
        virtual             ~CxSign        ();

        BOOL                 bInit         (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        BOOL                 bMake         (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen);
        BOOL                 bUpdate       (CK_BYTE_PTR pPart, CK_ULONG ulPartLen);
        BOOL                 bEncryptUpdate(CK_BYTE_PTR pPart, CK_ULONG ulPartLen, CK_BYTE_PTR pEncryptedPart, CK_ULONG_PTR pulEncryptedPartLen);
        BOOL                 bFinal        (CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen);
        BOOL                 bRecoverInit  (CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey);
        BOOL                 bRecover      (CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen);

    private:
        BOOL                 _m_bRes;
        CK_RV                _m_ulRes;

        CK_FUNCTION_LIST_PTR _m_pFunc;
        CK_SESSION_HANDLE    _m_hSession;
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxSignH
