/**
 * \file  CxSign.cpp
 * \brief Pkcs11 sign
 */


#include <xLib/Crypt/Pkcs11/CxSign.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>
#include <xLib/Crypt/Pkcs11/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSign::CxSign(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.pGetFuncList()),
    _m_hSession(a_cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/* virtual */
CxSign::~CxSign() {

}
//---------------------------------------------------------------------------
bool
CxSign::bInit(
    CK_MECHANISM_PTR a_pMechanism,  ///< the signature mechanism
    CK_OBJECT_HANDLE a_hKey         ///< handle of signature key
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_SignInit(_m_hSession, a_pMechanism, a_hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bMake(
    CK_BYTE_PTR  a_pData,           ///< the data to sign
    CK_ULONG     a_ulDataLen,       ///< count of bytes to sign
    CK_BYTE_PTR  a_pSignature,      ///< gets the signature
    CK_ULONG_PTR a_pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_Sign(_m_hSession, a_pData, a_ulDataLen, a_pSignature, a_pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

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

    CK_RV ulRv = _m_pFunc->C_SignUpdate(_m_hSession, pPart, ulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bEncryptUpdate(
    CK_BYTE_PTR  a_pPart,               ///< the plaintext data
    CK_ULONG     a_ulPartLen,           ///< plaintext length
    CK_BYTE_PTR  a_pEncryptedPart,      ///< gets ciphertext
    CK_ULONG_PTR a_pulEncryptedPartLen  ///< gets c-text length
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_SignEncryptUpdate(_m_hSession, a_pPart, a_ulPartLen, a_pEncryptedPart, a_pulEncryptedPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bFinal(
    CK_BYTE_PTR  a_pSignature,      ///< gets the signature
    CK_ULONG_PTR a_pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_SignFinal(_m_hSession, a_pSignature, a_pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bRecoverInit(
    CK_MECHANISM_PTR a_pMechanism, ///< the signature mechanism
    CK_OBJECT_HANDLE a_hKey        ///< handle of the signature key
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_SignRecoverInit(_m_hSession, a_pMechanism, a_hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSign::bRecover(
    CK_BYTE_PTR  a_pData,           ///< the data to sign
    CK_ULONG     a_ulDataLen,       ///< count of bytes to sign
    CK_BYTE_PTR  a_pSignature,      ///< gets the signature
    CK_ULONG_PTR a_pulSignatureLen  ///< gets signature length
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_SignRecover(_m_hSession, a_pData, a_ulDataLen, a_pSignature, a_pulSignatureLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
