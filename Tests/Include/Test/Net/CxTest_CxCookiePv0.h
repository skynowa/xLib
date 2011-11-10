/**
 * \file   CxTest_CxCookiePv0.h
 * \brief
 */


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
