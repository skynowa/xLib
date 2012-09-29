/**
 * \file  CxSlot.cpp
 * \brief Pkcs11 slot
 */


#include <xLib/Crypt/Pkcs11/CxSlot.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSlot::CxSlot(
    const CxPkcs11 &a_cPkcs11
) :
    _m_pFunc(a_cPkcs11.pGetFuncList())
{
    /*DEBUG*/xASSERT_DO(NULL != _m_pFunc, return);
}
//---------------------------------------------------------------------------
/* virtual */
CxSlot::~CxSlot() {

}
//---------------------------------------------------------------------------
#if xTEMP_DISABLED
    bool CxSlot::bGetList(
        CK_BBOOL       a_bTokenPresent,  ///< only slots with tokens?
        CK_SLOT_ID_PTR a_pSlotList,      ///< receives array of slot IDs
        CK_ULONG_PTR   a_pulCount        ///< receives number of slots
    )
#endif

bool
CxSlot::bGetList(
    CK_BBOOL                 a_bTokenPresent,     ///< only slots with tokens?
    std::vector<CK_SLOT_ID> *a_pvecSlotList       ///< receives array of slot IDs
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,       false);
    /*DEBUG*/// bTokenPresent - n/a
    /*DEBUG*/xASSERT_RET(NULL != a_pvecSlotList, false);

    CK_ULONG ulCount = 0;

    (*a_pvecSlotList).clear();

    CK_RV ulRv = _m_pFunc->C_GetSlotList(a_bTokenPresent, NULL_PTR, &ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxPkcs11::sErrorStr(ulRv).c_str(), false);
    xCHECK_RET(0 == ulCount, true);

    (*a_pvecSlotList).resize(ulCount);

    ulRv = _m_pFunc->C_GetSlotList(a_bTokenPresent, &(*a_pvecSlotList).at(0), &ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK                 == ulRv, CxPkcs11::sErrorStr(ulRv).c_str(), false);
    /*DEBUG*/xASSERT_RET    ((*a_pvecSlotList).size() == ulCount,                              false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSlot::bGetInfo(
    CK_SLOT_ID       a_slotID,  ///< the ID of the slot
    CK_SLOT_INFO_PTR a_pInfo    ///< receives the slot information
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc, false);
    /*DEBUG*/// slotID - n/a
    /*DEBUG*/xASSERT_RET(NULL != a_pInfo,  false);

    CK_RV ulRv = _m_pFunc->C_GetSlotInfo(a_slotID, a_pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxPkcs11::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
CxSlot::ENotification
CxSlot::nfWaitForEvent(
    CK_FLAGS       a_flags,     ///< blocking/nonblocking flag
    CK_SLOT_ID_PTR a_pSlot,     ///< location that receives the slot ID
    CK_VOID_PTR    a_pRserved   ///< reserved.  Should be NULL_PTR
)
{
    /*DEBUG*/xASSERT_RET(NULL     != _m_pFunc, nfError);
    /*DEBUG*/// flags    - n/a
    /*DEBUG*/xASSERT_RET(NULL     != a_pSlot,  nfError);
    /*DEBUG*/// pRserved - n/a

    CK_RV ulRv = _m_pFunc->C_WaitForSlotEvent(a_flags, a_pSlot, a_pRserved);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxPkcs11::sErrorStr(ulRv).c_str(), nfError);

    //-------------------------------------
    //�������� ������� ������ � �����
    CK_SLOT_INFO siInfo = {{0}};

    bool bRv = bGetInfo(*a_pSlot, &siInfo);
    /*DEBUG*/xASSERT_RET(true == bRv, nfError);

    xCHECK_RET(siInfo.flags & CKF_TOKEN_PRESENT, nfInsertion);

    return nfRemoval;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
