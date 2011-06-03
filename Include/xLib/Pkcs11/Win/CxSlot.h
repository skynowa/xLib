/****************************************************************************
* Class name:  CxSlot
* Description: Pkcs11 slot
* File name:   CxSlot.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:07:29
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxSlotH
#define xLib_Pkcs11_CxSlotH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxSlot :
    public CxNonCopyable
{
    public:
        enum ENotification {
            nfError,
            nfInsertion,
            nfRemoval
        };

                             CxSlot        (const CxPkcs11 &cPkcs11);
        virtual             ~CxSlot        ();

        BOOL                 bGetList      (CK_BBOOL bTokenPresent, std::vector<CK_SLOT_ID> *pvecSlotList);
        BOOL                 bGetInfo      (CK_SLOT_ID slotID, CK_SLOT_INFO_PTR pInfo);
        ENotification        nfWaitForEvent(CK_FLAGS flags, CK_SLOT_ID_PTR pSlot, CK_VOID_PTR pRserved);

    private:
        BOOL                 _m_bRes;
        CK_RV                _m_ulRes;
        CK_FUNCTION_LIST_PTR _m_pFunc;
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxSlotH
