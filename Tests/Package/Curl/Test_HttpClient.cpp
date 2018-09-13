/**
 * \file   Test_HttpClient.cpp
 * \brief  test HttpClient
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
    xTEST_CASE("HttpClient::request (Get)")
    {
		std::ctstring_t url     = "https://example.com/";
		std::ctstring_t request = "";
		std::tstring_t  responseHeader;
		std::tstring_t  responseBody;

		HttpClient http;
		http.request(HttpClient::RequestType::Get, url, request, &responseHeader, &responseBody);
		xTEST_EQ(responseHeader.empty(), false);
		xTEST_EQ(responseBody.empty(), false);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
