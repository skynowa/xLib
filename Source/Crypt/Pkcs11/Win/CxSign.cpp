/**
 * \file  CxSign.cpp
 * \brief Pkcs11 sign
 */


#include <xLib/Crypt/Pkcs11/Win/CxSign.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSign::CxSign(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxSign::~CxSign() {

}
//---------------------------------------------------------------------------
bool
CxSign::bInit(
    CK_MECHANISM_PTR pMechanism,  ///< the signature mechanism
    CK_OBJECT_HANDLE hKey         ///< handle of signature key
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_SignInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bMake(
    CK_BYTE_PTR  pData,           ///< the data to sign
    CK_ULONG     ulDataLen,       ///< count of bytes to sign
    CK_BYTE_PTR  pSignature,      ///< gets the signature
    CK_ULONG_PTR pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_Sign(_m_hSession, pData, ulDataLen, pSignature, pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bUpdate(
    CK_BYTE_PTR pPart,     ///< the data to sign
    CK_ULONG    ulPartLen  ///< count of bytes to sign
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_SignUpdate(_m_hSession, pPart, ulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bEncryptUpdate(
    CK_BYTE_PTR  pPart,               ///< the plaintext data
    CK_ULONG     ulPartLen,           ///< plaintext length
    CK_BYTE_PTR  pEncryptedPart,      ///< gets ciphertext
    CK_ULONG_PTR pulEncryptedPartLen  ///< gets c-text length
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_SignEncryptUpdate(_m_hSession, pPart, ulPartLen, pEncryptedPart, pulEncryptedPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bFinal(
    CK_BYTE_PTR  pSignature,      ///< gets the signature
    CK_ULONG_PTR pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_SignFinal(_m_hSession, pSignature, pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bRecoverInit(
    CK_MECHANISM_PTR pMechanism, ///< the signature mechanism
    CK_OBJECT_HANDLE hKey        ///< handle of the signature key
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_SignRecoverInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bRecover(
    CK_BYTE_PTR  pData,           ///< the data to sign
    CK_ULONG     ulDataLen,       ///< count of bytes to sign
    CK_BYTE_PTR  pSignature,      ///< gets the signature
    CK_ULONG_PTR pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_SignRecover(_m_hSession, pData, ulDataLen, pSignature, pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
