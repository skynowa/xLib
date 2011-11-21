/**
 * \file   CxTest_CxTcpClient.h
 * \brief
 */


#ifndef CxTest_CxTcpClientH
#define CxTest_CxTcpClientH
//---------------------------------------------------------------------------
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxTcpClient :
    public CxTest
{
    public:
                     CxTest_CxTcpClient();
        virtual     ~CxTest_CxTcpClient();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTcpClientH
