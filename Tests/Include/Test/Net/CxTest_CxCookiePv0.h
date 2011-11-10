/****************************************************************************
* Class name:  CxTest_CxCookiePv0
* Description: test CxCookiePv0
* File name:   CxTest_CxCookiePv0.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCookiePv0H
#define CxTest_CxCookiePv0H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxCookiePv0.h>
//---------------------------------------------------------------------------
class CxTest_CxCookiePv0 :
    public CxTest
{
    public:
                     CxTest_CxCookiePv0();
        virtual     ~CxTest_CxCookiePv0();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCookiePv0H
