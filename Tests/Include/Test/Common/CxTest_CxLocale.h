/**
 * \file   CxTest_CxLocale.h
 * \brief
 */


#ifndef CxTest_CxLocaleH
#define CxTest_CxLocaleH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxLocale.h>
//------------------------------------------------------------------------------
class CxTest_CxLocale :
    public CxTest
{
public:
                 CxTest_CxLocale();
    virtual     ~CxTest_CxLocale();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxLocaleH
