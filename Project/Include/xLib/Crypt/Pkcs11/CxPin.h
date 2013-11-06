/**
 * \file  CxPin.h
 * \brief Pkcs11 pin
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;
class CxSession;

class CxPin :
    private CxNonCopyable
    /// Pkcs11 pin
{
public:
                         CxPin(const CxPkcs11 &cPkcs11, const CxSession &cSession);
         ///< constructor
    virtual             ~CxPin();
         ///< destructor

    void_t               initToken(CK_SLOT_ID slotID, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen,
                             CK_UTF8CHAR_PTR pLabel);
        ///< initializes a token
    void_t               initPIN(CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen);
        ///< initializes the normal user's PIN
    void_t               setPIN(CK_UTF8CHAR_PTR pOldPin, CK_ULONG ulOldLen, CK_UTF8CHAR_PTR pNewPin,
                             CK_ULONG ulNewLen);
        ///< modifies the PIN of the user who is logged in

    // TODO: CxPin utils
#if xTODO
    std::tstring_t       changeUserPin(std::ctstring_t &csOldUserPin,
                             std::ctstring_t &csNewUserPin);
    std::tstring_t       changeSOPin(std::ctstring_t &csOldSOPin, std::ctstring_t &csNewSOPin);
#endif

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;      ///< pointer to dll functions list
    CK_SESSION_HANDLE    _m_hSession;   ///< session handle
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Crypt/Pkcs11/CxPin.cpp>
#endif
