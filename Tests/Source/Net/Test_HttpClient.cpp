/**
 * \file   Test_HttpClient.cpp
 * \brief
 */


#include <Test/Net/Test_HttpClient.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_HttpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_HttpClient::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("HttpClient", a_caseLoops)
    {
        HttpClient hcHttpClient;
    }
}
//-------------------------------------------------------------------------------------------------
