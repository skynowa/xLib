/**
 * \file  CxUtils.h
 * \brief Pkcs11 utils
 */


#ifndef xLib_Pkcs11_CxUtilsH
#define xLib_Pkcs11_CxUtilsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Crypt/Pkcs11/Win/Common.h>
#include <xLib/Crypt/Pkcs11/Win/CxPkcs11.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxUtils :
    public CxNonCopyable
    /// Pkcs11 utils
{
    public:
        static std::tstring sErrorStr(const CK_RV culCode);
            ///< get error string by code, SDK 4.53

    private:
                            CxUtils  ();
            ///< constructor
        virtual            ~CxUtils  ();
            ///< destructor
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxUtilsH
