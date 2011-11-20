/**
 * \file  CxInfo.h
 * \brief Pkcs11 info
 */


#ifndef xLib_Pkcs11_CxInfoH
#define xLib_Pkcs11_CxInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Win/Common.h>
#include <xLib/Crypt/Pkcs11/Win/CxPkcs11.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxInfo :
    public CxNonCopyable
    /// Pkcs11 info
{
    public:
                             CxInfo   (const CxPkcs11 &cPkcs11);
            ///< constructor
        virtual             ~CxInfo   ();
            ///< destructor

        bool                 bGet     (CK_INFO_PTR pInfo);
            ///< returns general information about Cryptoki
        bool                 bGetToken(CK_SLOT_ID slotID, CK_TOKEN_INFO_PTR pInfo);
            ///< obtains information about a particular token in the system

    private:
        CK_FUNCTION_LIST_PTR _m_pFunc;    ///< pointer to dll's function list
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxInfoH
