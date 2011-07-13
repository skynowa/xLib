/****************************************************************************
* Class name:  CxTest_CxMacros
* Description: testing CxMacros
* File name:   CxTest_CxMacros.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxMacrosH
#define CxTest_CxMacrosH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxMacros.h>
//---------------------------------------------------------------------------
class CxTest_CxMacros :
    public CxTest
{
    public:
                       CxTest_CxMacros();
        virtual       ~CxTest_CxMacros();

        virtual  BOOL  bUnit          ();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxMacrosH
