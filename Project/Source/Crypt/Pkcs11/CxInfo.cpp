/**
 * \file  CxInfo.cpp
 * \brief Pkcs11 info
 */


#include <xLib/Crypt/Pkcs11/CxInfo.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxInfo::CxInfo(
    const CxPkcs11 &a_cPkcs11
) :
    _m_pFunc(a_cPkcs11.pGetFuncList())
{

}
//---------------------------------------------------------------------------
CxInfo::~CxInfo() {

}
//---------------------------------------------------------------------------
bool
CxInfo::bGet(
    CK_INFO_PTR a_pInfo  ///< location that receives information
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetInfo(a_pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxPkcs11::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxInfo::bGetToken(
    CK_SLOT_ID        a_slotID,  ///< ID of the token's slot
    CK_TOKEN_INFO_PTR a_pInfo    ///< receives the token information
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetTokenInfo(a_slotID, a_pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxPkcs11::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
