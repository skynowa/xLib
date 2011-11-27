/**
 * \file   CxTest_CxTcpServer.h
 * \brief
 */


#ifndef CxTest_CxTcpServerH
#define CxTest_CxTcpServerH
//---------------------------------------------------------------------------
#include <xLib/Net/CxTcpServer.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxTcpServer :
    public CxTest
{
    public:
                     CxTest_CxTcpServer();
        virtual     ~CxTest_CxTcpServer();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTcpServerH
