/**
 * \file  CxInfo.cpp
 * \brief Pkcs11 info
 */


#include <xLib/Crypt/Pkcs11/CxInfo.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxInfo::CxInfo(
    const CxPkcs11 &cPkcs11
) :
    _m_pFunc(cPkcs11.pGetFuncList())
{

}
//---------------------------------------------------------------------------
CxInfo::~CxInfo() {

}
//---------------------------------------------------------------------------
bool
CxInfo::bGet(
    CK_INFO_PTR pInfo  ///< location that receives information
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetInfo(pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxInfo::bGetToken(
    CK_SLOT_ID        slotID,  ///< ID of the token's slot
    CK_TOKEN_INFO_PTR pInfo    ///< receives the token information
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_GetTokenInfo(slotID, pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
