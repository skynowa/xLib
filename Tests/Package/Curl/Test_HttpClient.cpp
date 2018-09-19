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
		BaseData baseData;
		baseData.url     = xT("https://example.com/");
		baseData.request = xT("");

		BaseDataOut baseDataOut;

		HttpClient http;
		m_bRv = http.request(HttpClient::RequestType::Get, baseData, &baseDataOut);
		xTEST(m_bRv);
		xTEST_EQ(baseDataOut.headers.empty(), false);
		xTEST_EQ(baseDataOut.body.empty(), false);

		std::cout
			<< xTRACE_VAR(baseDataOut.contentType)  << "\n"
			<< xTRACE_VAR(baseDataOut.effectiveUrl) << "\n"
			<< xTRACE_VAR(baseDataOut.responseCode) << "\n"
			<< xTRACE_VAR(baseDataOut.totalTimeSec) << "\n"
			<< "\n"
			<< xTRACE_VAR(baseDataOut.headers)      << "\n"
			<< xTRACE_VAR(baseDataOut.body.size())  << "\n";
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
