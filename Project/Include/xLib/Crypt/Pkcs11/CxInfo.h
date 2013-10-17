/**
 * \file  CxInfo.h
 * \brief Pkcs11 info
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;

class CxInfo :
    private CxNonCopyable
    /// Pkcs11 info
{
public:
    explicit             CxInfo(const CxPkcs11 &cPkcs11);
        ///< constructor
    virtual             ~CxInfo();
        ///< destructor

    void_t               get(CK_INFO_PTR pInfo);
        ///< returns general information about Cryptoki
    void_t               token(CK_SLOT_ID slotID, CK_TOKEN_INFO_PTR pInfo);
        ///< obtains information about a particular token in the system

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;  ///< pointer to dll function list
};

xNAMESPACE_END(NxLib)

#if xXLIB_HEADER_ONLY

#endif

#endif
//------------------------------------------------------------------------------
