/**
 * \file  CxSlot.h
 * \brief Pkcs11 slot
 */


#ifndef xLib_Pkcs11_CxSlotH
#define xLib_Pkcs11_CxSlotH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

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

    explicit             CxSlot      (const CxPkcs11 &cPkcs11);
        ///< constructor
    virtual             ~CxSlot      ();
        ///< destructor

    void                 list        (CK_BBOOL bTokenPresent, std::vector<CK_SLOT_ID> *pvecSlotList);
        ///< obtains a list of slots in the system
    void                 info        (CK_SLOT_ID slotID, CK_SLOT_INFO_PTR pInfo);
        ///< obtains information about a particular slot in the system
    ENotification        waitForEvent(CK_FLAGS flags, CK_SLOT_ID_PTR pSlot, CK_VOID_PTR pRserved);
        ///< waits for a slot event (token insertion, removal, etc.) to occur

private:
    CK_FUNCTION_LIST_PTR _m_pFunc;  ///< pointer to dll functions list
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif // xLib_Pkcs11_CxSlotH
