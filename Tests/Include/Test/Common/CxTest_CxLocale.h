/**
 * \file   CxTest_CxLocale.h
 * \brief
 */


#ifndef CxTest_CxLocaleH
#define CxTest_CxLocaleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxLocale.h>
//---------------------------------------------------------------------------
class CxTest_CxLocale :
    public CxTest
{
    public:
                     CxTest_CxLocale();
        virtual     ~CxTest_CxLocale();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxLocaleH
