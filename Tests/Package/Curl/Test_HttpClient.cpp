/**
 * \file   Test_HttpClient.cpp
 * \brief  test HttpClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl::package::curl;

xTEST_UNIT(Test_HttpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_HttpClient::unit()
{
    xTEST_CASE("request (Get)")
    {
		cbool_t isDebug {false};

		DataIn dataIn;
		dataIn.url     = xT("https://example.com/");
		dataIn.request = xT("");

		DataOut dataOut;

		HttpClient http(isDebug);
		m_bRv = http.get(dataIn, &dataOut);
		xTEST(m_bRv);
		xTEST(!dataOut.headers.empty());
		xTEST(!dataOut.body.empty());

		if (0) {
			Cout()
				<< xSTD_TRACE_VAR(dataIn.request)       << std::endl
				<< xT("\n")
				<< xSTD_TRACE_VAR(dataOut.contentType)  << std::endl
				<< xSTD_TRACE_VAR(dataOut.effectiveUrl) << std::endl
				<< xSTD_TRACE_VAR(dataOut.responseCode) << std::endl
				<< xSTD_TRACE_VAR(dataOut.totalTimeSec) << std::endl
				<< xT("\n")
				<< xSTD_TRACE_VAR(dataOut.headers)      << std::endl
				<< xSTD_TRACE_VAR(dataOut.body.size())  << std::endl
				<< xSTD_TRACE_VAR(dataOut.body)         << std::endl;
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
