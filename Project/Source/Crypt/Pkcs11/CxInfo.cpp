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
    _m_pFunc(a_cPkcs11.funcList())
{
}
//---------------------------------------------------------------------------
CxInfo::~CxInfo() {

}
//---------------------------------------------------------------------------
void
CxInfo::get(
    CK_INFO_PTR a_pInfo  ///< location that receives information
)
{
    CK_RV ulRv = _m_pFunc->C_GetInfo(a_pInfo);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxInfo::token(
    CK_SLOT_ID        a_slotID,  ///< ID of the token's slot
    CK_TOKEN_INFO_PTR a_pInfo    ///< receives the token information
)
{
    CK_RV ulRv = _m_pFunc->C_GetTokenInfo(a_slotID, a_pInfo);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
