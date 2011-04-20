/****************************************************************************
* Class name:  CxSession
* Description: Pkcs11 session
* File name:   CxSession.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:04:46
*
*****************************************************************************/


#include <xLib/Pkcs11/CxSession.h>

#include <xLib/Pkcs11/CxUtils.h>



/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxSession ()
CxSession::CxSession(const CxPkcs11 &cPkcs11) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(NULL)
{
    /*DEBUG*/xASSERT_DO(NULL != _m_pFunc,    return);
    /*DEBUG*/xASSERT_DO(NULL == _m_hSession, return);
}
//---------------------------------------------------------------------------
//TODO: - ~CxSession ()
CxSession::~CxSession() {

}
//---------------------------------------------------------------------------
//TODO: - CxSession (gets a handle)
CK_SESSION_HANDLE
CxSession::hGetHandle() const {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    NULL);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, NULL);

    return _m_hSession;
}
//---------------------------------------------------------------------------
//TODO: - bOpen (opens a session between an application and a token)
BOOL
CxSession::bOpen(
        CK_SLOT_ID  slotID,        /* the slot's ID */
        CK_FLAGS    flags,         /* from CK_SESSION_INFO */
        CK_VOID_PTR pApplication,  /* passed to callback */
        CK_NOTIFY   Notify         /* callback function */
) 
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL == _m_hSession, FALSE);

    _m_ulRes = _m_pFunc->C_OpenSession(slotID, flags, pApplication, Notify, &_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetInfo (obtains information about the session)
BOOL
CxSession::bGetInfo(
      CK_SESSION_INFO_PTR pInfo      /* receives session info */
) 
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    _m_ulRes = _m_pFunc->C_GetSessionInfo(_m_hSession, pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSetOperationState (restores the state of the cryptographic operation in a session)
BOOL
CxSession::bSetOperationState(
    CK_BYTE_PTR      pOperationState,      /* holds state */
    CK_ULONG         ulOperationStateLen,  /* holds state length */
    CK_OBJECT_HANDLE hEncryptionKey,       /* en/decryption key */
    CK_OBJECT_HANDLE hAuthenticationKey    /* sign/verify key */
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    _m_ulRes = _m_pFunc->C_SetOperationState(_m_hSession, pOperationState, ulOperationStateLen, hEncryptionKey, hAuthenticationKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bGetOperationState (obtains the state of the cryptographic operation in a session)
BOOL
CxSession::bGetOperationState(
    CK_BYTE_PTR  pOperationState,      /* gets state */
    CK_ULONG_PTR pulOperationStateLen  /* gets state length */
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,   FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);

    _m_ulRes = _m_pFunc->C_GetOperationState(_m_hSession, pOperationState, pulOperationStateLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bClose (closes a session between an application and a token)
BOOL
CxSession::bClose() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,    FALSE);
    /*DEBUG*/xASSERT_RET(NULL != _m_hSession, FALSE);


    _m_ulRes = _m_pFunc->C_CloseSession(_m_hSession);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    _m_hSession = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bCloseAll (closes all sessions with a token)
BOOL
CxSession::bCloseAll(
      CK_SLOT_ID slotID  /* the token's slot */
) 
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc, FALSE);
    /*DEBUG*/// _m_hSession - n/a

    _m_ulRes =     _m_pFunc->C_CloseAllSessions(slotID);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    _m_hSession = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------





/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
