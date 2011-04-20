/****************************************************************************
* Class name:  CxMechanism
* Description: Pkcs11 mechanism
* File name:   CxMechanism.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:09:28
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxMechanismH
#define xLib_Pkcs11_CxMechanismH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxMechanism : public CxNonCopyable {
    public:
                             CxMechanism(const CxPkcs11 &cPkcs11);
                            ~CxMechanism();
       
           BOOL                 bGetInfo   (CK_SLOT_ID slotID, CK_MECHANISM_TYPE type, CK_MECHANISM_INFO_PTR pInfo);        
        BOOL                 bGetList   (CK_SLOT_ID slotID, CK_MECHANISM_TYPE_PTR pMechanismList, CK_ULONG_PTR pulCount);    
        
    private:
        BOOL                 _m_bRes;
        CK_RV                _m_ulRes;

        CK_FUNCTION_LIST_PTR _m_pFunc;
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxMechanismH
