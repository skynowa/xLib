/****************************************************************************
* Class name:  CxTest_CxDateTime
* Description: testing CxDateTime
* File name:   CxTest_CxDateTime.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxDateTimeH
#define CxTest_CxDateTimeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxDateTime.h>
//---------------------------------------------------------------------------
class CxTest_CxDateTime :
    public CxTest
{
    public:
        CxTest_CxDateTime();
        virtual     ~CxTest_CxDateTime();

        virtual     BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDateTimeH
