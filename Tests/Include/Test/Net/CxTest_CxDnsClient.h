/**
 * \file   CxTest_CxDnsClient.h
 * \brief
 */


#ifndef CxTest_CxDnsClientH
#define CxTest_CxDnsClientH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxDnsClient.h>
//------------------------------------------------------------------------------
class CxTest_CxDnsClient :
    public CxTest
{
public:
                 CxTest_CxDnsClient();
    virtual     ~CxTest_CxDnsClient();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxDnsClientH
