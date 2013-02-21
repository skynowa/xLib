/**
 * \file   CxTest_CxHttpClient.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxHttpClient.h>


//------------------------------------------------------------------------------
CxTest_CxHttpClient::CxTest_CxHttpClient() {

}
//------------------------------------------------------------------------------
CxTest_CxHttpClient::~CxTest_CxHttpClient() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxHttpClient::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxHttpClient::CxHttpClient", cullCaseLoops)
    {
        CxHttpClient hcHttpClient;
    }
}
//------------------------------------------------------------------------------
