/**
 * \file   CxTest_CxDnsClient.h
 * \brief
 */


#ifndef CxTest_CxDnsClientH
#define CxTest_CxDnsClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxDnsClient :
    public CxTest
{
    public:
                     CxTest_CxDnsClient();
        virtual     ~CxTest_CxDnsClient();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDnsClientH
