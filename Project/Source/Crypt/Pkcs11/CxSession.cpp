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
    _m_pFunc   (a_cPkcs11.pGetFuncList()),
    _m_hSession(0UL)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_DIFF(0UL, _m_hSession);
}
//---------------------------------------------------------------------------
/* virtual */
CxSession::~CxSession() {

}
//---------------------------------------------------------------------------
CK_SESSION_HANDLE
CxSession::hGetHandle() const {
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_DIFF(0UL, _m_hSession);

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
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_PTR_FAIL(_m_hSession);

    CK_RV ulRv = _m_pFunc->C_OpenSession(a_slotID, a_flags, a_pApplication, a_Notify, &_m_hSession);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxSession::vGetInfo(
    CK_SESSION_INFO_PTR a_pInfo      ///< receives session info
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_DIFF(0UL, _m_hSession);

    CK_RV ulRv = _m_pFunc->C_GetSessionInfo(_m_hSession, a_pInfo);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
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
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_DIFF(0UL, _m_hSession);

    CK_RV ulRv = _m_pFunc->C_SetOperationState(_m_hSession, a_pOperationState, a_ulOperationStateLen, a_hEncryptionKey, a_hAuthenticationKey);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxSession::vGetOperationState(
    CK_BYTE_PTR  a_pOperationState,      ///< gets state
    CK_ULONG_PTR a_pulOperationStateLen  ///< gets state length
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_DIFF(0UL, _m_hSession);

    CK_RV ulRv = _m_pFunc->C_GetOperationState(_m_hSession, a_pOperationState, a_pulOperationStateLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));
}
//---------------------------------------------------------------------------
void
CxSession::vClose() {
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/xTEST_DIFF(0UL, _m_hSession);


    CK_RV ulRv = _m_pFunc->C_CloseSession(_m_hSession);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    _m_hSession = NULL;
}
//---------------------------------------------------------------------------
void
CxSession::vCloseAll(
    CK_SLOT_ID slotID  ///< the token's slot
)
{
    /*DEBUG*/xTEST_PTR(_m_pFunc);
    /*DEBUG*/// _m_hSession - n/a

    CK_RV ulRv = _m_pFunc->C_CloseAllSessions(slotID);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    _m_hSession = NULL;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
