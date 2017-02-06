/**
 * \file   Test_HttpClient.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_HttpClient)
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
