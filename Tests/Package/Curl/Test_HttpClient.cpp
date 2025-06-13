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
		LogCout() << "GithubCI - skip";
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

		OptionIn optionIn;
		optionIn.url     = xT("https://translate.google.com.vn/translate_tts");
		optionIn.request = Format::str("ie={}&q={}&tl={}&client={}",
							"UTF-8",
							http.escape("comma-separated list of guest names"),
							"en",
							"tw-ob");

		OptionOut optionOut;


		m_bRv = http.get(optionIn, &optionOut);
		xTEST(m_bRv);
		xTEST(!optionOut.headers.empty());
		xTEST(!optionOut.body.empty());

		std::custring_t body(optionOut.body.cbegin(), optionOut.body.cend());

		FileBin file("./test.mp3");
		file.write(body, xl::fs::FileIO::OpenMode::BinWrite);

		if (0) {
			LogCout()
				<< xTRACE_VAR(optionIn.request)       << std::endl
				<< xT("\n")
				<< xTRACE_VAR(optionOut.contentType)  << std::endl
				<< xTRACE_VAR(optionOut.effectiveUrl) << std::endl
				<< xTRACE_VAR(optionOut.responseCode) << std::endl
				<< xTRACE_VAR(optionOut.totalTimeSec) << std::endl
				<< xT("\n")
				<< xTRACE_VAR(optionOut.headers)      << std::endl
				<< xTRACE_VAR(optionOut.body.size())  << std::endl
				<< xTRACE_VAR(optionOut.body)         << std::endl;
		}
	}

    xTEST_CASE("request (Get)")
    {
		cbool_t isDebug {false};

		OptionIn optionIn;
		optionIn.url     = xT("https://example.com/");
		optionIn.request = xT("");

		OptionOut optionOut;

		HttpClient http(isDebug);
		m_bRv = http.get(optionIn, &optionOut);
		xTEST(m_bRv);
		xTEST(!optionOut.headers.empty());
		xTEST(!optionOut.body.empty());

		if (0) {
			LogCout()
				<< xTRACE_VAR(optionIn.request)       << std::endl
				<< xT("\n")
				<< xTRACE_VAR(optionOut.contentType)  << std::endl
				<< xTRACE_VAR(optionOut.effectiveUrl) << std::endl
				<< xTRACE_VAR(optionOut.responseCode) << std::endl
				<< xTRACE_VAR(optionOut.totalTimeSec) << std::endl
				<< xT("\n")
				<< xTRACE_VAR(optionOut.headers)      << std::endl
				<< xTRACE_VAR(optionOut.body.size())  << std::endl
				<< xTRACE_VAR(optionOut.body)         << std::endl;
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
