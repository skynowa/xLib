/**
 * \file  CxSession.h
 * \brief Pkcs11 session
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;

class CxSession :
    private CxNonCopyable
    /// Pkcs11 session
{
public:
    explicit             CxSession(const CxPkcs11 &cPkcs11);
        ///< constructor
    virtual             ~CxSession();
        ///< destructor

    CK_SESSION_HANDLE    handle() const;
        ///< get handle
    void_t               open(CK_SLOT_ID slotID, CK_FLAGS flags, CK_VOID_PTR pApplication,
                             CK_NOTIFY Notify);
        ///< opens a session between an application and a token
    void_t               info(CK_SESSION_INFO_PTR pInfo);
        ///< obtains information about the session
    void_t               setOperationState(CK_BYTE_PTR pOperationState,
                             CK_ULONG ulOperationStateLen, CK_OBJECT_HANDLE hEncryptionKey,
                             CK_OBJECT_HANDLE hAuthenticationKey);
        ///< restores the state of the cryptographic operation in a session
    void_t               operationState(CK_BYTE_PTR pOperationState,
                             CK_ULONG_PTR pulOperationStateLen);
        ///< obtains the state of the cryptographic operation in a session
    void_t               close();
        ///< closes a session between an application and a token
    void_t               closeAll(CK_SLOT_ID slotID);
        ///< closes all sessions with a token

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif
