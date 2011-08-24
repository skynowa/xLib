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
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
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
        	///< notifications

                             CxSlot        (const CxPkcs11 &cPkcs11);
            ///< constructor
        virtual             ~CxSlot        ();
        	///< destructor

        BOOL                 bGetList      (CK_BBOOL bTokenPresent, std::vector<CK_SLOT_ID> *pvecSlotList);
    		///< obtains a list of slots in the system
        BOOL                 bGetInfo      (CK_SLOT_ID slotID, CK_SLOT_INFO_PTR pInfo);
    		///< obtains information about a particular slot in the system
        ENotification        nfWaitForEvent(CK_FLAGS flags, CK_SLOT_ID_PTR pSlot, CK_VOID_PTR pRserved);
    		///< waits for a slot event (token insertion, removal, etc.) to occur

    private:
        BOOL                 _m_bRes;
    		///< for private use
        CK_RV                _m_ulRes;
    		///< for private use
        CK_FUNCTION_LIST_PTR _m_pFunc;
    		///< pointer to dll's functions list
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxSlotH
