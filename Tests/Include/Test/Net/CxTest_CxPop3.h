/**
 * \file   CxTest_CxPop3.h
 * \brief
 */


#ifndef CxTest_CxPop3H
#define CxTest_CxPop3H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxPop3.h>
//---------------------------------------------------------------------------
class CxTest_CxPop3 :
    public CxTest
{
public:
                 CxTest_CxPop3();
    virtual     ~CxTest_CxPop3();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxPop3H
