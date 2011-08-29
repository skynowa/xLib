/**
 * \file  CxMechanism.h
 * \brief Pkcs11 mechanism
 */


#ifndef xLib_Pkcs11_CxMechanismH
#define xLib_Pkcs11_CxMechanismH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxMechanism :
    public CxNonCopyable
    /// Pkcs11 mechanism
{
    public:
                             CxMechanism(const CxPkcs11 &cPkcs11);
            ///< constructor
        virtual             ~CxMechanism();
        	///< destructor

        BOOL                 bGetInfo   (CK_SLOT_ID slotID, CK_MECHANISM_TYPE type, CK_MECHANISM_INFO_PTR pInfo);
        	///< obtains information about a particular mechanism possibly supported by a token
        BOOL                 bGetList   (CK_SLOT_ID slotID, CK_MECHANISM_TYPE_PTR pMechanismList, CK_ULONG_PTR pulCount);
        	///< obtains a list of mechanism types supported by a token

    private:
        BOOL                 _m_bRes;	///< for private use
        CK_RV                _m_ulRes; 	///< for private use
        CK_FUNCTION_LIST_PTR _m_pFunc; 	///< pointer to dll's functions list
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxMechanismH
