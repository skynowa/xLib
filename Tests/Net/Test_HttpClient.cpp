/**
 * \file   Test_HttpClient.cpp
 * \brief
 */


#include "Test_HttpClient.h"

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_HttpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_HttpClient::unit()
{
    xTEST_CASE("HttpClient")
    {
        HttpClient hcHttpClient;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
