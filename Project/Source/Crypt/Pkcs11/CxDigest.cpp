/**
 * \file  CxDigest.cpp
 * \brief Pkcs11 digest
 */


#include <xLib/Crypt/Pkcs11/CxDigest.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDigest::CxDigest(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.pFuncList()),
    _m_hSession(a_cSession.hHandle())
{

}
//---------------------------------------------------------------------------
/* virtual */
CxDigest::~CxDigest() {

}
//---------------------------------------------------------------------------
void
CxDigest::vMake(
    CK_BYTE_PTR  a_pData,        ///< data to be digested
    CK_ULONG     a_ulDataLen,    ///< bytes of data to digest
    CK_BYTE_PTR  a_pDigest,      ///< gets the message digest
    CK_ULONG_PTR a_pulDigestLen  ///< gets digest length
)
{
    

    CK_RV ulRv = _m_pFunc->C_Digest(_m_hSession, a_pData, a_ulDataLen, a_pDigest, a_pulDigestLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxDigest::vEncryptUpdate(
    CK_BYTE_PTR  a_pPart,               ///< the plaintext data
    CK_ULONG     a_ulPartLen,           ///< plaintext length
    CK_BYTE_PTR  a_pEncryptedPart,      ///< gets ciphertext
    CK_ULONG_PTR a_pulEncryptedPartLen  ///< gets c-text length)
)
{
    

    CK_RV ulRv = _m_pFunc->C_DigestEncryptUpdate(_m_hSession, a_pPart, a_ulPartLen, a_pEncryptedPart, a_pulEncryptedPartLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxDigest::vFinal(
    CK_BYTE_PTR  a_pDigest,      ///< gets the message digest
    CK_ULONG_PTR a_pulDigestLen  ///< gets byte count of digest
)
{
    

    CK_RV ulRv = _m_pFunc->C_DigestFinal(_m_hSession, a_pDigest, a_pulDigestLen );
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxDigest::vInit(
    CK_MECHANISM_PTR a_pMechanism  ///< the digesting mechanism
)
{
    

    CK_RV ulRv = _m_pFunc->C_DigestInit(_m_hSession, a_pMechanism);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxDigest::vKey(
    CK_OBJECT_HANDLE a_hKey       ///< secret key to digest
)
{
    

    CK_RV ulRv = _m_pFunc->C_DigestKey(_m_hSession, a_hKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxDigest::vUpdate(
    CK_BYTE_PTR a_pPart,     ///< data to be digested
    CK_ULONG    a_ulPartLen  ///< bytes of data to be digested
)
{
    

    CK_RV ulRv = _m_pFunc->C_DigestUpdate(_m_hSession, a_pPart, a_ulPartLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
