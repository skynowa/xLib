/**
 * \file  CxSession.cpp
 * \brief Pkcs11 session
 */


#include <xLib/Crypt/Pkcs11/CxSession.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSession::CxSession(
    const CxPkcs11 &a_cPkcs11
) :
    _m_pFunc   (a_cPkcs11.pFuncList()),
    _m_hSession(0UL)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);
}
//---------------------------------------------------------------------------
/* virtual */
CxSession::~CxSession() {

}
//---------------------------------------------------------------------------
CK_SESSION_HANDLE
CxSession::hHandle() const {
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);

    return _m_hSession;
}
//---------------------------------------------------------------------------
void
CxSession::vOpen(
    CK_SLOT_ID  a_slotID,        ///< the slot's ID
    CK_FLAGS    a_flags,         ///< from CK_SESSION_INFO
    CK_VOID_PTR a_pApplication,  ///< passed to callback
    CK_NOTIFY   a_Notify         ///< callback function
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_PTR_FAIL(_m_hSession);

    CK_RV ulRv = _m_pFunc->C_OpenSession(a_slotID, a_flags, a_pApplication, a_Notify, &_m_hSession);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxSession::vInfo(
    CK_SESSION_INFO_PTR a_pInfo      ///< receives session info
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);

    CK_RV ulRv = _m_pFunc->C_GetSessionInfo(_m_hSession, a_pInfo);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxSession::vSetOperationState(
    CK_BYTE_PTR      a_pOperationState,      ///< holds state
    CK_ULONG         a_ulOperationStateLen,  ///< holds state length
    CK_OBJECT_HANDLE a_hEncryptionKey,       ///< en/decryption key
    CK_OBJECT_HANDLE a_hAuthenticationKey    ///< sign/verify key
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);

    CK_RV ulRv = _m_pFunc->C_SetOperationState(_m_hSession, a_pOperationState, a_ulOperationStateLen, a_hEncryptionKey, a_hAuthenticationKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxSession::vOperationState(
    CK_BYTE_PTR  a_pOperationState,      ///< gets state
    CK_ULONG_PTR a_pulOperationStateLen  ///< gets state length
)
{
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);

    CK_RV ulRv = _m_pFunc->C_GetOperationState(_m_hSession, a_pOperationState, a_pulOperationStateLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxSession::vClose() {
    xTEST_PTR(_m_pFunc);
    xTEST_DIFF(0UL, _m_hSession);


    CK_RV ulRv = _m_pFunc->C_CloseSession(_m_hSession);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    _m_hSession = NULL;
}
//---------------------------------------------------------------------------
void
CxSession::vCloseAll(
    CK_SLOT_ID slotID  ///< the token's slot
)
{
    xTEST_PTR(_m_pFunc);
    // _m_hSession - n/a

    CK_RV ulRv = _m_pFunc->C_CloseAllSessions(slotID);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    _m_hSession = NULL;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
