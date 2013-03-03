/**
 * \file  CxMechanism.cpp
 * \brief Pkcs11 mechanism
 */


#include <xLib/Crypt/Pkcs11/CxMechanism.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    Public methods
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxMechanism::CxMechanism(
    const CxPkcs11 &a_cPkcs11
) :
    _m_pFunc(a_cPkcs11.funcList())
{
}
//------------------------------------------------------------------------------
/* virtual */
CxMechanism::~CxMechanism() {

}
//------------------------------------------------------------------------------
void_t
CxMechanism::info(
    CK_SLOT_ID            a_slotID,  ///< ID of the token's slot
    CK_MECHANISM_TYPE     a_type,    ///< type of mechanism
    CK_MECHANISM_INFO_PTR a_pInfo    ///< receives mechanism info
)
{
    CK_RV ulRv = _m_pFunc->C_GetMechanismInfo(a_slotID, a_type, a_pInfo);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void_t
CxMechanism::list(
    CK_SLOT_ID            a_slotID,          ///< ID of token's slot
    CK_MECHANISM_TYPE_PTR a_pMechanismList,  ///< gets mech. array
    CK_ULONG_PTR          a_pulCount         ///< gets # of mechs.
)
{
    CK_RV ulRv = _m_pFunc->C_GetMechanismList(a_slotID, a_pMechanismList, a_pulCount);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
