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
	if ( isGithubCI() ) {
		Cout() << "GithubCI - skip";
		return true;
	}

    xTEST_CASE("translate.google.com (Get)")
    {
	   /**
		https://translate.google.com.vn/translate_tts?
		ie=UTF-8&
		q=%D0%B1%D0%BE%D0%BB%D0%B3%D0%B0%D1%80%D0%BA%D0%B0&
		tl=en&
		client=tw-ob
		*/

		cbool_t isDebug {false};

		HttpClient http(isDebug);

		DataIn dataIn;
		dataIn.url     = xT("https://translate.google.com.vn/translate_tts");
		dataIn.request = Format::str("ie={}&q={}&tl={}&client={}",
							"UTF-8",
							http.escape("comma-separated list of guest names"),
							"en",
							"tw-ob");

		DataOut dataOut;


		m_bRv = http.get(dataIn, &dataOut);
		xTEST(m_bRv);
		xTEST(!dataOut.headers.empty());
		xTEST(!dataOut.body.empty());

		std::custring_t body(dataOut.body.cbegin(), dataOut.body.cend());

		File file("./test.mp3");
		file.binWrite(body, xl::fs::FileIO::OpenMode::BinWrite);

		if (0) {
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
	}

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
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
