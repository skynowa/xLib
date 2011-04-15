/****************************************************************************
* Class name:  CxInfo
* Description: Pkcs11 ����������
* File name:   CxInfo.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.03.2010 13:08:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Pkcs11/CxInfo.h>

#include <xLib/Pkcs11/CxUtils.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxInfo ()
CxInfo::CxInfo(const CxPkcs11 &cPkcs11) :
	_m_bRes (FALSE),
	_m_ulRes(!CKR_OK),
	_m_pFunc(cPkcs11.pGetFuncList())
{
	//code
}
//---------------------------------------------------------------------------
//TODO: - ~CxInfo ()
CxInfo::~CxInfo() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - bGet (returns general information about Cryptoki)
BOOL
CxInfo::bGet(
	CK_INFO_PTR pInfo  /* location that receives information */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetInfo(pInfo); 
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetToken (obtains information about a particular token in the system)
BOOL
CxInfo::bGetToken(
	CK_SLOT_ID        slotID,  /* ID of the token's slot */
	CK_TOKEN_INFO_PTR pInfo    /* receives the token information */
)
{
	/*DEBUG*/

	_m_ulRes = _m_pFunc->C_GetTokenInfo(slotID, pInfo); 
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
