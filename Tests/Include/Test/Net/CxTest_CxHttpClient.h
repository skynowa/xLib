/**
 * \file   CxTest_CxHttpClient.h
 * \brief
 */


#ifndef CxTest_CxHttpClientH
#define CxTest_CxHttpClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxHttpClient.h>
//---------------------------------------------------------------------------
class CxTest_CxHttpClient :
    public CxTest
{
    public:
                     CxTest_CxHttpClient();
        virtual     ~CxTest_CxHttpClient();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxHttpClientH
