/**
 * \file  CxInfo.h
 * \brief Pkcs11 info
 */


#ifndef xLib_Pkcs11_CxInfoH
#define xLib_Pkcs11_CxInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxInfo :
    public CxNonCopyable
    /// Pkcs11 info
{
    public:
                             CxInfo   (const CxPkcs11 &cPkcs11);
            ///< constructor
        virtual             ~CxInfo   ();
            ///< destructor

        BOOL                 bGet     (CK_INFO_PTR pInfo);
            ///< returns general information about Cryptoki
        BOOL                 bGetToken(CK_SLOT_ID slotID, CK_TOKEN_INFO_PTR pInfo);
            ///< obtains information about a particular token in the system

    private:
        BOOL                 _m_bRes;	///< for private use
        CK_RV                _m_ulRes;	///< for private use
        CK_FUNCTION_LIST_PTR _m_pFunc;	///< pointer to dll's function list
};
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxInfoH
