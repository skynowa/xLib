/**
 * \file  CxSign.cpp
 * \brief Pkcs11 sign
 */


#include <xLib/Pkcs11/Win/CxSign.h>

#include <xLib/Pkcs11/Win/CxUtils.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSign::CxSign(
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
CxSign::~CxSign() {

}
//---------------------------------------------------------------------------
BOOL
CxSign::bInit(
    CK_MECHANISM_PTR pMechanism,  ///< the signature mechanism
    CK_OBJECT_HANDLE hKey         ///< handle of signature key
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SignInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSign::bMake(
    CK_BYTE_PTR  pData,           ///< the data to sign
    CK_ULONG     ulDataLen,       ///< count of bytes to sign
    CK_BYTE_PTR  pSignature,      ///< gets the signature
    CK_ULONG_PTR pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_Sign(_m_hSession, pData, ulDataLen, pSignature, pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSign::bUpdate(
    CK_BYTE_PTR pPart,     ///< the data to sign
    CK_ULONG    ulPartLen  ///< count of bytes to sign
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SignUpdate(_m_hSession, pPart, ulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSign::bEncryptUpdate(
    CK_BYTE_PTR  pPart,               ///< the plaintext data
    CK_ULONG     ulPartLen,           ///< plaintext length
    CK_BYTE_PTR  pEncryptedPart,      ///< gets ciphertext
    CK_ULONG_PTR pulEncryptedPartLen  ///< gets c-text length
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SignEncryptUpdate(_m_hSession, pPart, ulPartLen, pEncryptedPart, pulEncryptedPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSign::bFinal(
    CK_BYTE_PTR  pSignature,      ///< gets the signature
    CK_ULONG_PTR pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SignFinal(_m_hSession, pSignature, pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSign::bRecoverInit(
    CK_MECHANISM_PTR pMechanism, ///< the signature mechanism
    CK_OBJECT_HANDLE hKey        ///< handle of the signature key
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SignRecoverInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSign::bRecover(
    CK_BYTE_PTR  pData,           ///< the data to sign
    CK_ULONG     ulDataLen,       ///< count of bytes to sign
    CK_BYTE_PTR  pSignature,      ///< gets the signature
    CK_ULONG_PTR pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_SignRecover(_m_hSession, pData, ulDataLen, pSignature, pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
