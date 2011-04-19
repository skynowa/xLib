/****************************************************************************
* Class name:  CxPkcs11
* Description: Aladdin eToken, PKCS #11
* File name:   CxPkcs11.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.02.2010 13:31:54
*
*****************************************************************************/


#include <xLib/Pkcs11/CxPkcs11.h>

#include <xLib/Pkcs11/CxUtils.h>


/****************************************************************************
*    public                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxPkcs11 ()
CxPkcs11::CxPkcs11() :
	_m_bRes       (FALSE),
	_m_ulRes      (!CKR_OK),
	_m_pFunc      (NULL),
	_m_dllETPkcs11()
{
	/*DEBUG*/xASSERT_DO(NULL == _m_pFunc, return);
	/*DEBUG*/// _m_dllETPkcs11 - n/a

	_m_bRes = _bLoadETPkcs11();
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);

	_m_bRes = bInitialize();
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//TODO: - ~CxPkcs11 ()
/*virtual*/
CxPkcs11::~CxPkcs11() {
	/*DEBUG*/

	_m_bRes = bFinalize();
	/*DEBUG*/xCHECK_DO(FALSE == _m_bRes, return);
}
//---------------------------------------------------------------------------
//TODO: - pGetFuncList (get pointer to functions list)
CK_FUNCTION_LIST_PTR
CxPkcs11::pGetFuncList() const {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFunc, NULL);

	return _m_pFunc;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + _bLoadETPkcs11 (load eTPkcs11.dll, init PKCS#11)
BOOL
CxPkcs11::_bLoadETPkcs11() {
	/*DEBUG*/

	_m_bRes = _m_dllETPkcs11.bLoad(xT("eTPkcs11.dll"));
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	CK_C_GetFunctionList pFunctionList = NULL;

	(FARPROC &)pFunctionList = (FARPROC)_m_dllETPkcs11.fpGetProcAddress(xT("C_GetFunctionList"));
	/*DEBUG*/xASSERT_RET(NULL != pFunctionList, FALSE);

	_m_ulRes = pFunctionList(&_m_pFunc);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
	/*DEBUG*/xASSERT_RET    (NULL   != _m_pFunc,                                       FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bInitialize ()
BOOL
CxPkcs11::bInitialize() {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFunc, FALSE);

	_m_ulRes = _m_pFunc->C_Initialize(NULL_PTR);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bFinalize ()
BOOL
CxPkcs11::bFinalize() {
	/*DEBUG*/xASSERT_RET(NULL != _m_pFunc, FALSE);

	_m_ulRes = _m_pFunc->C_Finalize(NULL_PTR);
	/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------






















/*

//---------------------------------------------------------------------------
//TODO: - FFFFFFFFFFFFF (CCCCCCCCCCCCCCCCCCCCCCCccc)
BOOL
CxPkcs11::FFFFFFFFFFFFF(

)
{
	/DEBUG/

	_m_ulRes = _m_pFunc->XXXXXXXXXXXXX(XXXXXXXXXXXXXXXXXXXXXXX);
	/DEBUG/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

	return TRUE;
}


*/
