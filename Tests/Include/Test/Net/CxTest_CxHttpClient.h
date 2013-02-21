/**
 * \file   CxTest_CxHttpClient.h
 * \brief
 */


#ifndef CxTest_CxHttpClientH
#define CxTest_CxHttpClientH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxHttpClient.h>
//------------------------------------------------------------------------------
class CxTest_CxHttpClient :
    public CxTest
{
public:
                 CxTest_CxHttpClient();
    virtual     ~CxTest_CxHttpClient();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxHttpClientH
