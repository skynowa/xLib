/**
 * \file  CxSlot.cpp
 * \brief Pkcs11 slot
 */


#include <xLib/Crypt/Pkcs11/Win/CxSlot.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSlot::CxSlot(
    const CxPkcs11 &cPkcs11
) :
    _m_pFunc(cPkcs11.pGetFuncList())
{
    /*DEBUG*/xASSERT_DO(NULL != _m_pFunc, return);
}
//---------------------------------------------------------------------------
/*virtual*/
CxSlot::~CxSlot() {

}
//---------------------------------------------------------------------------
#if xTEMP_DISABLED
    bool CxSlot::bGetList(
        CK_BBOOL       bTokenPresent,  ///< only slots with tokens?
        CK_SLOT_ID_PTR pSlotList,      ///< receives array of slot IDs
        CK_ULONG_PTR   pulCount        ///< receives number of slots
    )
#endif

bool
CxSlot::bGetList(
    CK_BBOOL                 bTokenPresent,     ///< only slots with tokens?
    std::vector<CK_SLOT_ID> *pvecSlotList       ///< receives array of slot IDs
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc,     false);
    /*DEBUG*/// bTokenPresent - n/a
    /*DEBUG*/xASSERT_RET(NULL != pvecSlotList, false);

    CK_ULONG ulCount = 0;

    (*pvecSlotList).clear();

    CK_RV ulRes = _m_pFunc->C_GetSlotList(bTokenPresent, NULL_PTR, &ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);
    xCHECK_RET(0 == ulCount, true);

    (*pvecSlotList).resize(ulCount);

    ulRes = _m_pFunc->C_GetSlotList(bTokenPresent, &(*pvecSlotList).at(0), &ulCount);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK                 == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);
    /*DEBUG*/xASSERT_RET    ((*pvecSlotList).size() == ulCount,                                        false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxSlot::bGetInfo(
    CK_SLOT_ID       slotID,  ///< the ID of the slot
    CK_SLOT_INFO_PTR pInfo    ///< receives the slot information
)
{
    /*DEBUG*/xASSERT_RET(NULL != _m_pFunc, false);
    /*DEBUG*/// slotID - n/a
    /*DEBUG*/xASSERT_RET(NULL != pInfo,    false);

    CK_RV ulRes = _m_pFunc->C_GetSlotInfo(slotID, pInfo);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
CxSlot::ENotification
CxSlot::nfWaitForEvent(
    CK_FLAGS       flags,     ///< blocking/nonblocking flag
    CK_SLOT_ID_PTR pSlot,     ///< location that receives the slot ID
    CK_VOID_PTR    pRserved   ///< reserved.  Should be NULL_PTR
)
{
    /*DEBUG*/xASSERT_RET(NULL     != _m_pFunc, nfError);
    /*DEBUG*/// flags    - n/a
    /*DEBUG*/xASSERT_RET(NULL     != pSlot,    nfError);
    /*DEBUG*/// pRserved - n/a

    CK_RV ulRes = _m_pFunc->C_WaitForSlotEvent(flags, pSlot, pRserved);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), nfError);

    //-------------------------------------
    //�������� ������� ������ � �����
    CK_SLOT_INFO siInfo = {{0}};

    bool bRes = bGetInfo(*pSlot, &siInfo);
    /*DEBUG*/xASSERT_RET(true == bRes, nfError);

    xCHECK_RET(siInfo.flags & CKF_TOKEN_PRESENT, nfInsertion);

    return nfRemoval;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
