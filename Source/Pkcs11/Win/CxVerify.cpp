/****************************************************************************
* Class name:  CxVerify
* Description: Pkcs11 verify
* File name:   CxVerify.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:14:22
*
*****************************************************************************/


#include <xLib/Pkcs11/Win/CxVerify.h>

#include <xLib/Pkcs11/Win/CxUtils.h>


/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxVerify::CxVerify(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxVerify::~CxVerify() {

}
//---------------------------------------------------------------------------
BOOL
CxVerify::bInit(
    CK_MECHANISM_PTR pMechanism,  ///< the verification mechanism
    CK_OBJECT_HANDLE hKey         ///< verification key
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_VerifyInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxVerify::bMake(
    CK_BYTE_PTR pData,          ///< signed data
    CK_ULONG    ulDataLen,      ///< length of signed data
    CK_BYTE_PTR pSignature,     ///< signature
    CK_ULONG    ulSignatureLen  ///< signature length*/
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_Verify(_m_hSession, pData, ulDataLen, pSignature, ulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxVerify::bFinal(
    CK_BYTE_PTR pSignature,     ///< signature to verify
    CK_ULONG    ulSignatureLen  ///< signature length
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_VerifyFinal(_m_hSession, pSignature, ulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxVerify::bRecoverInit(
    CK_MECHANISM_PTR pMechanism,  ///< the verification mechanism
    CK_OBJECT_HANDLE hKey         ///< verification key
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_VerifyRecoverInit(_m_hSession, pMechanism, hKey );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxVerify::bRecover(
    CK_BYTE_PTR  pSignature,      ///< signature to verify
    CK_ULONG     ulSignatureLen,  ///< signature length
    CK_BYTE_PTR  pData,           ///< gets signed data
    CK_ULONG_PTR pulDataLen       ///< gets signed data len
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_VerifyRecover(_m_hSession, pSignature,ulSignatureLen, pData, pulDataLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxVerify::bUpdate(
    CK_BYTE_PTR pPart,     ///< signed data
    CK_ULONG    ulPartLen  ///< length of signed data
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_VerifyUpdate(_m_hSession, pPart, ulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
