/**
 * \file  CxFunction.cpp
 * \brief Pkcs11 function
 */


#include <xLib/Pkcs11/Win/CxFunction.h>

#include <xLib/Pkcs11/Win/CxUtils.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFunction::CxFunction(
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
CxFunction::~CxFunction() {

}
//---------------------------------------------------------------------------
BOOL
CxFunction::bGetList(
    CK_FUNCTION_LIST_PTR_PTR ppFunctionList  ///< receives pointer to function list
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GetFunctionList(ppFunctionList);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFunction::bGetStatus() {
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GetFunctionStatus(_m_hSession );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFunction::bCancel() {
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_CancelFunction(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxFunction::bGetListEx() {
    /*DEBUG*/

	#if xTODO
		_m_ulRes = _m_pFunc->ETC_GetFunctionListEx();
		/*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);
	#endif

    return TRUE;
}
//---------------------------------------------------------------------------
