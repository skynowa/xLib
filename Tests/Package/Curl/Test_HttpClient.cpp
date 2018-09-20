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

		Cout()
			<< xTRACE_VAR(baseDataOut.contentType)  << std::endl
			<< xTRACE_VAR(baseDataOut.effectiveUrl) << std::endl
			<< xTRACE_VAR(baseDataOut.responseCode) << std::endl
			<< xTRACE_VAR(baseDataOut.totalTimeSec) << std::endl
			<< xT("\n")
			<< xTRACE_VAR(baseDataOut.headers)      << std::endl
			<< xTRACE_VAR(baseDataOut.body.size())  << std::endl;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
