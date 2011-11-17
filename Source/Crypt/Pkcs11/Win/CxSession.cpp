/**
 * \file  CxSession.cpp
 * \brief Pkcs11 session
 */


#include <xLib/Crypt/Pkcs11/Win/CxSession.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSession::CxSession(
    const CxPkcs11 &cPkcs11
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(NULL)
{
    /*DEBUG*/xASSERT_DO(NULL != _m_pFunc,    return);
    /*DEBUG*/xASSERT_DO(NULL == _m_hSession, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxSession::~CxSession() {

}
//---------------------------------------------------------------------------
CK_SESSION_HANDLE
CxSession::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, NULL);

    return _m_hSession;
}
//---------------------------------------------------------------------------
BOOL
CxSession::bOpen(
    CK_SLOT_ID  slotID,        ///< the slot's ID
    CK_FLAGS    flags,         ///< from CK_SESSION_INFO
    CK_VOID_PTR pApplication,  ///< passed to callback
    CK_NOTIFY   Notify         ///< callback function
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL == _m_hSession, FALSE);

    CK_RV ulRes = _m_pFunc->C_OpenSession(slotID, flags, pApplication, Notify, &_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSession::bGetInfo(
    CK_SESSION_INFO_PTR pInfo      ///< receives session info
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    CK_RV ulRes = _m_pFunc->C_GetSessionInfo(_m_hSession, pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSession::bSetOperationState(
    CK_BYTE_PTR      pOperationState,      ///< holds state
    CK_ULONG         ulOperationStateLen,  ///< holds state length
    CK_OBJECT_HANDLE hEncryptionKey,       ///< en/decryption key
    CK_OBJECT_HANDLE hAuthenticationKey    ///< sign/verify key
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    CK_RV ulRes = _m_pFunc->C_SetOperationState(_m_hSession, pOperationState, ulOperationStateLen, hEncryptionKey, hAuthenticationKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSession::bGetOperationState(
    CK_BYTE_PTR  pOperationState,      ///< gets state
    CK_ULONG_PTR pulOperationStateLen  ///< gets state length
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,   FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    CK_RV ulRes = _m_pFunc->C_GetOperationState(_m_hSession, pOperationState, pulOperationStateLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSession::bClose() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);


    CK_RV ulRes = _m_pFunc->C_CloseSession(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    _m_hSession = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxSession::bCloseAll(
    CK_SLOT_ID slotID  ///< the token's slot
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc, FALSE);
    /*DEBUG*/// _m_hSession - n/a

    CK_RV ulRes = _m_pFunc->C_CloseAllSessions(slotID);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    _m_hSession = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
