/**
 * \file  CxInfo.cpp
 * \brief Pkcs11 info
 */


#include <xLib/Crypt/Pkcs11/Win/CxInfo.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if defined(xOS_ENV_WIN)
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
BOOL
CxInfo::bGet(
    CK_INFO_PTR pInfo  ///< location that receives information
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GetInfo(pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxInfo::bGetToken(
    CK_SLOT_ID        slotID,  ///< ID of the token's slot
    CK_TOKEN_INFO_PTR pInfo    ///< receives the token information
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_GetTokenInfo(slotID, pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
