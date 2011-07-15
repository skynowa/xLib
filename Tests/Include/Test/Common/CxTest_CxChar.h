/****************************************************************************
* Class name:  CxTest_CxChar
* Description: test CxChar
* File name:   CxTest_CxChar.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCharH
#define CxTest_CxCharH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxChar.h>
//---------------------------------------------------------------------------
class CxTest_CxChar :
    public CxTest
{
    public:
                     CxTest_CxChar();
        virtual     ~CxTest_CxChar();

        virtual BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCharH
