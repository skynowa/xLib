/**
 * \file   Test_CurlClient.cpp
 * \brief  test Client
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;
using namespace curl;

xTEST_CLASS(Test_CurlClient)
xTEST_UNIT(Test_CurlClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_CurlClient::unit()
{
	Client curl;

	CURL *curlHandle = curl.get().get();

    xTEST_CASE("setOption")
	{
		std::ctstring_t url = xT("http://www.cplusplus.com/reference/");

		// options
		curl.setOption(CURLOPT_URL, url.c_str());

		// header
		Buffer headerBuff;
		::curl_easy_setopt(curlHandle, CURLOPT_WRITEHEADER, &headerBuff);
		::curl_easy_setopt(curlHandle, CURLOPT_HEADERFUNCTION, Client::onWriteHeader);

		// body
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
