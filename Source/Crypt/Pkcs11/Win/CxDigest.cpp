/**
 * \file  CxDigest.cpp
 * \brief Pkcs11 digest
 */


#include <xLib/Crypt/Pkcs11/Win/CxDigest.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if defined(xOS_ENV_WIN)

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDigest::CxDigest(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxDigest::~CxDigest() {

}
//---------------------------------------------------------------------------
BOOL
CxDigest::bMake(
    CK_BYTE_PTR  pData,        ///< data to be digested
    CK_ULONG     ulDataLen,    ///< bytes of data to digest
    CK_BYTE_PTR  pDigest,      ///< gets the message digest
    CK_ULONG_PTR pulDigestLen  ///< gets digest length
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_Digest(_m_hSession, pData, ulDataLen, pDigest, pulDigestLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDigest::bEncryptUpdate(
    CK_BYTE_PTR  pPart,               ///< the plaintext data
    CK_ULONG     ulPartLen,           ///< plaintext length
    CK_BYTE_PTR  pEncryptedPart,      ///< gets ciphertext
    CK_ULONG_PTR pulEncryptedPartLen  ///< gets c-text length)
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DigestEncryptUpdate(_m_hSession, pPart, ulPartLen, pEncryptedPart, pulEncryptedPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDigest::bFinal(
    CK_BYTE_PTR  pDigest,      ///< gets the message digest
    CK_ULONG_PTR pulDigestLen  ///< gets byte count of digest
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DigestFinal(_m_hSession, pDigest, pulDigestLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDigest::bInit(
    CK_MECHANISM_PTR pMechanism  ///< the digesting mechanism
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DigestInit(_m_hSession,    pMechanism);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDigest::bKey(
    CK_OBJECT_HANDLE hKey       ///< secret key to digest
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DigestKey(_m_hSession, hKey );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDigest::bUpdate(
    CK_BYTE_PTR pPart,     ///< data to be digested
    CK_ULONG    ulPartLen  ///< bytes of data to be digested
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DigestUpdate(_m_hSession, pPart, ulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
