/**
 * \file   Test_CurlClient.cpp
 * \brief  test CurlClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_CurlClient)
xTEST_UNIT(Test_CurlClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_CurlClient::unit()
{
	CurlClient curl;

    xTEST_CASE("version, versionInfo")
    {
		{
			std::tstring_t version = curl.version();
			// Trace() << xTRACE_VAR(version);
			xTEST(!version.empty());
		}

		for (CURLversion version = CURLVERSION_FIRST; version < CURLVERSION_LAST; ++ version) {
			std::tstring_t info = curl.versionInfo(version);
			// Trace() << xTRACE_VAR(version) << ":\n" << xTRACE_VAR(info) << "\n";
			xTEST(!info.empty());
		}
    }

    xTEST_CASE("setOption")
	{
		const CURLoption option = CURLOPT_URL;

		curl.setOption(option);
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
