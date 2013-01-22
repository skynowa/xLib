/**
 * \file   CxTest_CxUri.h
 * \brief
 */


#ifndef CxTest_CxUriH
#define CxTest_CxUriH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxUri.h>
//---------------------------------------------------------------------------
class CxTest_CxUri :
    public CxTest
{
public:
                 CxTest_CxUri();
    virtual     ~CxTest_CxUri();

    virtual void vUnit(const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxUriH
