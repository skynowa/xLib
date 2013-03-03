/**
 * \file   CxTest_CxCookiePv1.h
 * \brief
 */


#ifndef CxTest_CxCookiePv1H
#define CxTest_CxCookiePv1H
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxCookiePv1.h>
//------------------------------------------------------------------------------
class CxTest_CxCookiePv1 :
    public CxTest
{
public:
                 CxTest_CxCookiePv1();
    virtual     ~CxTest_CxCookiePv1();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxCookiePv1H
