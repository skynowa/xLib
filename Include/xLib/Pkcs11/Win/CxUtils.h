/****************************************************************************
* Class name:  CxUtils
* Description: Pkcs11 utils
* File name:   CxUtils.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:15:59
*
*****************************************************************************/


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
        static tString sErrorStr(const CK_RV culCode);
        	///< get error string by code, SDK 4.53

    private:
                       CxUtils  ();
            ///< constructor
        virtual       ~CxUtils  ();
        	///< destructor
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxUtilsH
