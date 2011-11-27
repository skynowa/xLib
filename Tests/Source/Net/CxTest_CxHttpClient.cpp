/**
 * \file   CxTest_CxHttpClient.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxHttpClient.h>


//---------------------------------------------------------------------------
CxTest_CxHttpClient::CxTest_CxHttpClient() {

}
//---------------------------------------------------------------------------
CxTest_CxHttpClient::~CxTest_CxHttpClient() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxHttpClient::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    xTEST_CASE(cullCaseLoops)
    {
        CxHttpClient hcHttpClient;
    }

    return true;
}
//---------------------------------------------------------------------------
