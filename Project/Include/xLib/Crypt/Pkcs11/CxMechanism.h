/**
 * \file  CxMechanism.h
 * \brief Pkcs11 mechanism
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;

class CxMechanism :
    private CxNonCopyable
    /// Pkcs11 mechanism
{
public:
                         CxMechanism(const CxPkcs11 &cPkcs11);
        ///< constructor
    virtual             ~CxMechanism();
        ///< destructor

    void_t               info(CK_SLOT_ID slotID, CK_MECHANISM_TYPE type,
                             CK_MECHANISM_INFO_PTR pInfo);
        ///< obtains information about a particular mechanism possibly supported by a token
    void_t               list(CK_SLOT_ID slotID, CK_MECHANISM_TYPE_PTR pMechanismList,
                             CK_ULONG_PTR pulCount);
        ///< obtains a list of mechanism types supported by a token

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;  ///< pointer to dll functions list
};

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
