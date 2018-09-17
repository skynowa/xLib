/**
 * \file   Test_CurlClient.cpp
 * \brief  test Client
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
	Client curl;

	CURL *curlHandle = curl.get().get();

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
		std::tstring_t url = xT("http://www.cplusplus.com/reference/");

		curl.setOption(CURLOPT_URL, url.c_str());

		// header
		Buffer headerBuff;
		::curl_easy_setopt(curlHandle, CURLOPT_WRITEHEADER, &headerBuff);
		::curl_easy_setopt(curlHandle, CURLOPT_HEADERFUNCTION, Client::onWriteHeader);

		// data
		Buffer writeBuff;
		::curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &writeBuff);
		::curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, Client::onWriteData);

		::curl_easy_setopt(curlHandle, CURLOPT_POST,0);
		::curl_easy_setopt(curlHandle, CURLOPT_NOBODY, 0);

		curl.perform();
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
