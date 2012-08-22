/**
 * \file  CxMechanism.cpp
 * \brief Pkcs11 mechanism
 */


#include <xLib/Crypt/Pkcs11/CxMechanism.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxMechanism::CxMechanism(
    const CxPkcs11 &cPkcs11
) :
    _m_pFunc(cPkcs11.pGetFuncList())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxMechanism::~CxMechanism() {

}
//---------------------------------------------------------------------------
bool
CxMechanism::bGetInfo(
    CK_SLOT_ID            slotID,  ///< ID of the token's slot
    CK_MECHANISM_TYPE     type,    ///< type of mechanism
    CK_MECHANISM_INFO_PTR pInfo    ///< receives mechanism info
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetMechanismInfo(slotID, type, pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMechanism::bGetList(
    CK_SLOT_ID            slotID,          ///< ID of token's slot
    CK_MECHANISM_TYPE_PTR pMechanismList,  ///< gets mech. array
    CK_ULONG_PTR          pulCount         ///< gets # of mechs.
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetMechanismList(slotID, pMechanismList, pulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
