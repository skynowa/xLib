/**
 * \file  CxLogin.h
 * \brief Pkcs11 login
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxLogin :
    private CxNonCopyable
    /// Pkcs11 login
{
public:
                         CxLogin(const CxPkcs11 &cPkcs11, const CxSession &cSession);
        ///< constructor
    virtual             ~CxLogin();
        ///< constructor

    void_t               login(CK_USER_TYPE userType, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);
        ///< login user into a token
    void_t               logout();
        ///< logout user from a token

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
