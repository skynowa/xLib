/**
 * \file  CxSlot.h
 * \brief Pkcs11 slot
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Crypt/Pkcs11/Core.h>
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11;

class CxSlot :
    private CxNonCopyable
    /// Pkcs11 slot
{
public:
    enum ENotification
        /// notifications
    {
        nfError,
        nfInsertion,
        nfRemoval
    };

    explicit             CxSlot(const CxPkcs11 &cPkcs11);
        ///< constructor
    virtual             ~CxSlot();
        ///< destructor

    void_t               list(CK_BBOOL bTokenPresent, std::vector<CK_SLOT_ID> *pvecSlotList);
        ///< obtains a list of slots in the system
    void_t               info(CK_SLOT_ID slotID, CK_SLOT_INFO_PTR pInfo);
        ///< obtains information about a particular slot in the system
    ENotification        waitForEvent(CK_FLAGS flags, CK_SLOT_ID_PTR pSlot, CK_VOID_PTR pRserved)
                             xWARN_UNUSED_RV;
        ///< waits for a slot event (token insertion, removal, etc.) to occur

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;  ///< pointer to dll functions list
};

xNAMESPACE_END(NxLib)

#if xXLIB_HEADER_ONLY

#endif

#endif
//------------------------------------------------------------------------------
