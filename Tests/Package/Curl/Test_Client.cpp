/**
 * \file   Test_Client.cpp
 * \brief  test Client
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl::package::curl;

xTEST_UNIT(Test_Client)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Client::unit()
{
	if ( isGithubCI() ) {
		LogCout() << "GithubCI - skip";
		return true;
	}

	cbool_t isDebug {false};

	Client curl(isDebug);

    xTEST_CASE("setOption")
	{
		std::ctstring_t url = xT("http://www.cplusplus.com/reference/");

		// options
		curl.setOption(CURLOPT_URL, url.c_str());

		// header
		std::tstring_t buffHeader;
		curl.setOption(CURLOPT_WRITEHEADER,    &buffHeader);
		curl.setOption(CURLOPT_HEADERFUNCTION, Client::onWriteHeader);

		// body
		std::tstring_t dataBuff;
		curl.setOption(CURLOPT_WRITEDATA,     &dataBuff);
		curl.setOption(CURLOPT_WRITEFUNCTION, Client::onWriteData);

		curl.setOption(CURLOPT_POST,   0L);
		curl.setOption(CURLOPT_NOBODY, 0L);

		curl.perform();

		xTEST(!buffHeader.empty());
		xTEST(!dataBuff.empty());
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
