/**
 * \file  CxPkcs11.h
 * \brief Aladdin eToken, PKCS#11
 */


#ifndef xLib_Pkcs11_CxPkcs11H
#define xLib_Pkcs11_CxPkcs11H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Common.h>
#include <xLib/Filesystem/CxDll.h>
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxPkcs11 :
    private CxNonCopyable
    /// Aladdin eToken, PKCS#11
{
    public:
                              CxPkcs11      ();
            ///< constructor
        virtual              ~CxPkcs11      ();
            ///< destructor

        CK_FUNCTION_LIST_PTR  pGetFuncList  () const;
            ///< get pointer to dll's functions list
        static std::tstring_t sErrorStr     (const CK_RV culCode);
            ///< get error string by code, SDK 4.53

   private:
        CK_FUNCTION_LIST_PTR _m_pFunc;            ///< pointer to fumction
        CxDll                _m_dllETPkcs11;    ///< Pkcs11 CxDll object

        void                 _vLoadETPkcs11 ();
            ///< load eTPkcs11.dll
        void                 vInitialize    ();
            ///< initiate PKCS#11
        void                 vFinalize      ();
            ///< finalize PKCS#11
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxPkcs11H
