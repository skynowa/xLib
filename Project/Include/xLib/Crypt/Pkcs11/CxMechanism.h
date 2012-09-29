/**
 * \file  CxMechanism.h
 * \brief Pkcs11 mechanism
 */


#ifndef xLib_Pkcs11_CxMechanismH
#define xLib_Pkcs11_CxMechanismH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

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

        bool                 bGetInfo   (CK_SLOT_ID slotID, CK_MECHANISM_TYPE type, CK_MECHANISM_INFO_PTR pInfo);
            ///< obtains information about a particular mechanism possibly supported by a token
        bool                 bGetList   (CK_SLOT_ID slotID, CK_MECHANISM_TYPE_PTR pMechanismList, CK_ULONG_PTR pulCount);
            ///< obtains a list of mechanism types supported by a token

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;     ///< pointer to dll's functions list
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxMechanismH
