/**
 * \file   CxTest_CxTcpClient.h
 * \brief
 */


#ifndef CxTest_CxTcpClientH
#define CxTest_CxTcpClientH
//------------------------------------------------------------------------------
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
//------------------------------------------------------------------------------
class CxTest_CxTcpClient :
    public CxTest
{
public:
                 CxTest_CxTcpClient();
    virtual     ~CxTest_CxTcpClient();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxTcpClientH
