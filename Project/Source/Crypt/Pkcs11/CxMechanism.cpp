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
    const CxPkcs11 &a_cPkcs11
) :
    _m_pFunc(a_cPkcs11.pGetFuncList())
{

}
//---------------------------------------------------------------------------
/* virtual */
CxMechanism::~CxMechanism() {

}
//---------------------------------------------------------------------------
bool
CxMechanism::bGetInfo(
    CK_SLOT_ID            a_slotID,  ///< ID of the token's slot
    CK_MECHANISM_TYPE     a_type,    ///< type of mechanism
    CK_MECHANISM_INFO_PTR a_pInfo    ///< receives mechanism info
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetMechanismInfo(a_slotID, a_type, a_pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMechanism::bGetList(
    CK_SLOT_ID            a_slotID,          ///< ID of token's slot
    CK_MECHANISM_TYPE_PTR a_pMechanismList,  ///< gets mech. array
    CK_ULONG_PTR          a_pulCount         ///< gets # of mechs.
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetMechanismList(a_slotID, a_pMechanismList, a_pulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
