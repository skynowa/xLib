/**
 * \file   Test_HttpClient.cpp
 * \brief  test HttpClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;
using namespace curl;

xTEST_CLASS(Test_HttpClient)
xTEST_UNIT(Test_HttpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_HttpClient::unit()
{
    xTEST_CASE("request (Get)")
    {
		DataIn dataIn;
		dataIn.url     = xT("https://example.com/");
		dataIn.request = xT("");

		DataOut dataOut;

		HttpClient http;
		m_bRv = http.request(HttpClient::Request::Get, dataIn, &dataOut);
		xTEST(m_bRv);
		xTEST(!dataOut.headers.empty());
		xTEST(!dataOut.body.empty());

		Cout()
			<< xTRACE_VAR(dataIn.request)       << std::endl
			<< xT("\n")
			<< xTRACE_VAR(dataOut.contentType)  << std::endl
			<< xTRACE_VAR(dataOut.effectiveUrl) << std::endl
			<< xTRACE_VAR(dataOut.responseCode) << std::endl
			<< xTRACE_VAR(dataOut.totalTimeSec) << std::endl
			<< xT("\n")
			<< xTRACE_VAR(dataOut.headers)      << std::endl
			<< xTRACE_VAR(dataOut.body.size())  << std::endl
			<< xTRACE_VAR(dataOut.body)         << std::endl;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
