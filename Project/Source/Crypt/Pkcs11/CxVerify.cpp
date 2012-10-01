/**
 * \file  CxVerify.cpp
 * \brief Pkcs11 verify
 */


#include <xLib/Crypt/Pkcs11/CxVerify.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxVerify::CxVerify(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.pGetFuncList()),
    _m_hSession(a_cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/* virtual */
CxVerify::~CxVerify() {

}
//---------------------------------------------------------------------------
bool
CxVerify::bInit(
    CK_MECHANISM_PTR a_pMechanism,  ///< the verification mechanism
    CK_OBJECT_HANDLE a_hKey         ///< verification key
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_VerifyInit(_m_hSession, a_pMechanism, a_hKey);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bMake(
    CK_BYTE_PTR a_pData,          ///< signed data
    CK_ULONG    a_ulDataLen,      ///< length of signed data
    CK_BYTE_PTR a_pSignature,     ///< signature
    CK_ULONG    a_ulSignatureLen  ///< signature length*/
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_Verify(_m_hSession, a_pData, a_ulDataLen, a_pSignature, a_ulSignatureLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bFinal(
    CK_BYTE_PTR a_pSignature,     ///< signature to verify
    CK_ULONG    a_ulSignatureLen  ///< signature length
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_VerifyFinal(_m_hSession, a_pSignature, a_ulSignatureLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bRecoverInit(
    CK_MECHANISM_PTR a_pMechanism,  ///< the verification mechanism
    CK_OBJECT_HANDLE a_hKey         ///< verification key
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_VerifyRecoverInit(_m_hSession, a_pMechanism, a_hKey);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bRecover(
    CK_BYTE_PTR  a_pSignature,      ///< signature to verify
    CK_ULONG     a_ulSignatureLen,  ///< signature length
    CK_BYTE_PTR  a_pData,           ///< gets signed data
    CK_ULONG_PTR a_pulDataLen       ///< gets signed data len
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_VerifyRecover(_m_hSession, a_pSignature, a_ulSignatureLen, a_pData, a_pulDataLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxVerify::bUpdate(
    CK_BYTE_PTR a_pPart,     ///< signed data
    CK_ULONG    a_ulPartLen  ///< length of signed data
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_VerifyUpdate(_m_hSession, a_pPart, a_ulPartLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
