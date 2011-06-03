/****************************************************************************
* Class name:  CxMechanism
* Description: Pkcs11 mechanism
* File name:   CxMechanism.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:09:28
*
*****************************************************************************/


#include <xLib/Pkcs11/CxMechanism.h>

#include <xLib/Pkcs11/CxUtils.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxMechanism ()
CxMechanism::CxMechanism(const CxPkcs11 &cPkcs11) :
    _m_bRes (FALSE),
    _m_ulRes(!CKR_OK),
    _m_pFunc(cPkcs11.pGetFuncList())
{
    //code
}
//---------------------------------------------------------------------------
//TODO: ~CxMechanism ()
CxMechanism::~CxMechanism() {
    //code
}
//---------------------------------------------------------------------------
//TODO: bGetInfo (obtains information about a particular mechanism possibly supported by a token)
BOOL
CxMechanism::bGetInfo(
    CK_SLOT_ID            slotID,  /* ID of the token's slot */
    CK_MECHANISM_TYPE     type,    /* type of mechanism */
    CK_MECHANISM_INFO_PTR pInfo    /* receives mechanism info */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GetMechanismInfo(slotID, type, pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bGetList (obtains a list of mechanism types supported by a token)
BOOL
CxMechanism::bGetList(
    CK_SLOT_ID            slotID,          /* ID of token's slot */
    CK_MECHANISM_TYPE_PTR pMechanismList,  /* gets mech. array */
    CK_ULONG_PTR          pulCount         /* gets # of mechs. */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_GetMechanismList(slotID, pMechanismList, pulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
