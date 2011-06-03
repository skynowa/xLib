/****************************************************************************
* Class name:  CxUtils
* Description: Pkcs11 utils
* File name:   CxUtils.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:15:59
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CXUtilsH
#define xLib_Pkcs11_CXUtilsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxUtils :
    public CxNonCopyable
{
    public:
        static tString sErrorStr(CK_RV ulCode);

    private:
        virtual        CxUtils  ();
                      ~CxUtils  ();
};
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_CXUtilsH
