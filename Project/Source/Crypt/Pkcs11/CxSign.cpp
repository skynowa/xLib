/**
 * \file  CxSign.cpp
 * \brief Pkcs11 sign
 */


#include <xLib/Crypt/Pkcs11/CxSign.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxSign::CxSign(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.funcList()),
    _m_hSession(a_cSession.handle())
{
}
//------------------------------------------------------------------------------
/* virtual */
CxSign::~CxSign() {

}
//------------------------------------------------------------------------------
void_t
CxSign::init(
    CK_MECHANISM_PTR a_pMechanism,  ///< the signature mechanism
    CK_OBJECT_HANDLE a_hKey         ///< handle of signature key
)
{
    CK_RV ulRv = _m_pFunc->C_SignInit(_m_hSession, a_pMechanism, a_hKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxSign::make(
    CK_BYTE_PTR  a_pData,           ///< the data to sign
    CK_ULONG     a_ulDataLen,       ///< count of bytes to sign
    CK_BYTE_PTR  a_pSignature,      ///< gets the signature
    CK_ULONG_PTR a_pulSignatureLen  ///< gets signature length
)
{
    CK_RV ulRv = _m_pFunc->C_Sign(_m_hSession, a_pData, a_ulDataLen, a_pSignature, a_pulSignatureLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxSign::update(
    CK_BYTE_PTR pPart,     ///< the data to sign
    CK_ULONG    ulPartLen  ///< count of bytes to sign
)
{
    CK_RV ulRv = _m_pFunc->C_SignUpdate(_m_hSession, pPart, ulPartLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxSign::encryptUpdate(
    CK_BYTE_PTR  a_pPart,               ///< the plaintext data
    CK_ULONG     a_ulPartLen,           ///< plaintext length
    CK_BYTE_PTR  a_pEncryptedPart,      ///< gets ciphertext
    CK_ULONG_PTR a_pulEncryptedPartLen  ///< gets c-text length
)
{
    CK_RV ulRv = _m_pFunc->C_SignEncryptUpdate(_m_hSession, a_pPart, a_ulPartLen, a_pEncryptedPart, a_pulEncryptedPartLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxSign::final(
    CK_BYTE_PTR  a_pSignature,      ///< gets the signature
    CK_ULONG_PTR a_pulSignatureLen  ///< gets signature length
)
{
    CK_RV ulRv = _m_pFunc->C_SignFinal(_m_hSession, a_pSignature, a_pulSignatureLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxSign::recoverInit(
    CK_MECHANISM_PTR a_pMechanism, ///< the signature mechanism
    CK_OBJECT_HANDLE a_hKey        ///< handle of the signature key
)
{
    CK_RV ulRv = _m_pFunc->C_SignRecoverInit(_m_hSession, a_pMechanism, a_hKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxSign::recover(
    CK_BYTE_PTR  a_pData,           ///< the data to sign
    CK_ULONG     a_ulDataLen,       ///< count of bytes to sign
    CK_BYTE_PTR  a_pSignature,      ///< gets the signature
    CK_ULONG_PTR a_pulSignatureLen  ///< gets signature length
)
{
    CK_RV ulRv = _m_pFunc->C_SignRecover(_m_hSession, a_pData, a_ulDataLen, a_pSignature, a_pulSignatureLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
