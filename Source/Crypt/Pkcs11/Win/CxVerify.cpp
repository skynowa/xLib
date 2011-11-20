/**
 * \file  CxVerify.cpp
 * \brief Pkcs11 verify
 */


#include <xLib/Crypt/Pkcs11/Win/CxVerify.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxVerify::CxVerify(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxVerify::~CxVerify() {

}
//---------------------------------------------------------------------------
bool
CxVerify::bInit(
    CK_MECHANISM_PTR pMechanism,  ///< the verification mechanism
    CK_OBJECT_HANDLE hKey         ///< verification key
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_VerifyInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bMake(
    CK_BYTE_PTR pData,          ///< signed data
    CK_ULONG    ulDataLen,      ///< length of signed data
    CK_BYTE_PTR pSignature,     ///< signature
    CK_ULONG    ulSignatureLen  ///< signature length*/
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_Verify(_m_hSession, pData, ulDataLen, pSignature, ulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bFinal(
    CK_BYTE_PTR pSignature,     ///< signature to verify
    CK_ULONG    ulSignatureLen  ///< signature length
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_VerifyFinal(_m_hSession, pSignature, ulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bRecoverInit(
    CK_MECHANISM_PTR pMechanism,  ///< the verification mechanism
    CK_OBJECT_HANDLE hKey         ///< verification key
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_VerifyRecoverInit(_m_hSession, pMechanism, hKey );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bRecover(
    CK_BYTE_PTR  pSignature,      ///< signature to verify
    CK_ULONG     ulSignatureLen,  ///< signature length
    CK_BYTE_PTR  pData,           ///< gets signed data
    CK_ULONG_PTR pulDataLen       ///< gets signed data len
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_VerifyRecover(_m_hSession, pSignature,ulSignatureLen, pData, pulDataLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bUpdate(
    CK_BYTE_PTR pPart,     ///< signed data
    CK_ULONG    ulPartLen  ///< length of signed data
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_VerifyUpdate(_m_hSession, pPart, ulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
