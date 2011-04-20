/****************************************************************************
* Class name:  CxFunction
* Description: Pkcs11 function
* File name:   CxFunction.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:14:45
*
*****************************************************************************/


#include <xLib/Pkcs11/CxFunction.h>

#include <xLib/Pkcs11/CxUtils.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxFunction ()
CxFunction::CxFunction(const CxPkcs11 &cPkcs11, const CxSession &cSession) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{
    //code
}
//---------------------------------------------------------------------------
//TODO: - ~CxFunction ()
CxFunction::~CxFunction() {
    //code
}
//---------------------------------------------------------------------------
//TODO: - bGetList (returns the function list)
BOOL
CxFunction::bGetList(
    CK_FUNCTION_LIST_PTR_PTR ppFunctionList  /* receives pointer to function list */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GetFunctionList(ppFunctionList);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetStatus (is a legacy function; it obtains an updated status of a function running in parallel with an application)
BOOL
CxFunction::bGetStatus() {
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GetFunctionStatus(_m_hSession );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bCancel (is a legacy function; it cancels a function running in parallel)
BOOL
CxFunction::bCancel() {
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_CancelFunction(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetListEx (� SDK 4.53 ���� ������� ���)
BOOL
CxFunction::bGetListEx() {
    /*DEBUG*/

    ////_m_ulRes = _m_pFunc->ETC_GetFunctionListEx();
    /////*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------





/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
