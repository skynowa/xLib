/**
 * \file  CxUtils.h
 * \brief Pkcs11 utils
 */


#ifndef xLib_Pkcs11_CxUtilsH
#define xLib_Pkcs11_CxUtilsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Win/Common.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxUtils :
    public CxNonCopyable
{
    public:
        static std::tstring sErrorStr(const CK_RV culCode);
        	///< get error string by code, SDK 4.53

    private:
                       CxUtils  ();
            ///< constructor
        virtual       ~CxUtils  ();
        	///< destructor
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxUtilsH
