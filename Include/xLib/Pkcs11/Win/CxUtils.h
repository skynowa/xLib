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
        static tString sErrorStr(CK_RV ulCode);

    private:
                       CxUtils  ();
        virtual       ~CxUtils  ();
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CxUtilsH
