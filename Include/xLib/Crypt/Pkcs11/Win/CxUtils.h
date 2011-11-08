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
#if defined(xOS_ENV_WIN)

class CxUtils :
    public CxNonCopyable
    /// Pkcs11 utils
{
    public:
        static std::string_t sErrorStr(const CK_RV culCode);
            ///< get error string by code, SDK 4.53

    private:
                            CxUtils  ();
            ///< constructor
        virtual            ~CxUtils  ();
            ///< destructor
};

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxUtilsH
