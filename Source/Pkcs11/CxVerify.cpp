/****************************************************************************
* Class name:  CxVerify
* Description: Pkcs11 verify
* File name:   CxVerify.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:14:22
*
*****************************************************************************/


#include <xLib/Pkcs11/CxVerify.h>

#include <xLib/Pkcs11/CxUtils.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxVerify ()
CxVerify::CxVerify(const CxPkcs11 &cPkcs11, const CxSession &cSession) :
	_m_bRes    (FALSE),
	_m_ulRes   (!CKR_OK),
	_m_pFunc   (cPkcs11.pGetFuncList()),
	_m_hSession(cSession.hGetHandle())
{
	//code
}
//---------------------------------------------------------------------------
//TODO: - ~CxVerify ()
CxVerify::~CxVerify() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - bInit (initializes a verification operation, where the signature is an appendix to the data, and plaintext cannot cannot be recovered from the signature (e.g. DSA))
BOOL
CxVerify::bInit(
	CK_MECHANISM_PTR  pMechanism,  /* the verification mechanism */
	CK_OBJECT_HANDLE  hKey         /* verification key */ 
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyInit(_m_hSession, pMechanism, hKey);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}	
//---------------------------------------------------------------------------
//TODO: - bMake (verifies a signature in a single-part operation,  where the signature is an appendix to the data, and plaintext cannot be recovered from the signature)
BOOL
CxVerify::bMake(
	CK_BYTE_PTR       pData,          /* signed data */
	CK_ULONG          ulDataLen,      /* length of signed data */
	CK_BYTE_PTR       pSignature,     /* signature */
	CK_ULONG          ulSignatureLen  /* signature length*/
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_Verify(_m_hSession, pData, ulDataLen, pSignature, ulSignatureLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bFinal (finishes a multiple-part verification operation, checking the signature)
BOOL
CxVerify::bFinal(
	CK_BYTE_PTR       pSignature,     /* signature to verify */
	CK_ULONG          ulSignatureLen  /* signature length */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyFinal(_m_hSession, pSignature, ulSignatureLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bRecoverInit (initializes a signature verification operation, where the data is recovered from the signature)
BOOL
CxVerify::bRecoverInit(
	CK_MECHANISM_PTR  pMechanism,  /* the verification mechanism */
	CK_OBJECT_HANDLE  hKey         /* verification key */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyRecoverInit(_m_hSession, pMechanism, hKey );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bVerifyRecover (verifies a signature in a single-part operation, where the data is recovered from the signature)
BOOL
CxVerify::bRecover(
	CK_BYTE_PTR       pSignature,      /* signature to verify */
	CK_ULONG          ulSignatureLen,  /* signature length */
	CK_BYTE_PTR       pData,           /* gets signed data */
	CK_ULONG_PTR      pulDataLen       /* gets signed data len */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyRecover(_m_hSession, pSignature,ulSignatureLen, pData, pulDataLen );
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bVerifyUpdate (continues a multiple-part verification operation, where the signature is an appendix to the data, and plaintext cannot be recovered from the signature)
BOOL
CxVerify::bUpdate(
	CK_BYTE_PTR       pPart,     /* signed data */
	CK_ULONG          ulPartLen  /* length of signed data */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_VerifyUpdate(_m_hSession, pPart, ulPartLen);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
