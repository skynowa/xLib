/**
 * \file   Test_Client.cpp
 * \brief  test Client
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;
using namespace curl;

xTEST_CLASS(Test_Client)
xTEST_UNIT(Test_Client)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Client::unit()
{
	Client curl;

	CURL *curlHandle = curl.get().get();

    xTEST_CASE("setOption")
	{
		std::ctstring_t url = xT("http://www.cplusplus.com/reference/");

		// options
		curl.setOption(CURLOPT_URL, url.c_str());

		// header
		std::tstring_t buffHeader;
		::curl_easy_setopt(curlHandle, CURLOPT_WRITEHEADER, &buffHeader);
		::curl_easy_setopt(curlHandle, CURLOPT_HEADERFUNCTION, Client::onWriteHeader);

		// body
		std::tstring_t dataBuff;
		::curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &dataBuff);
		::curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, Client::onWriteData);

		::curl_easy_setopt(curlHandle, CURLOPT_POST, 0L);
		::curl_easy_setopt(curlHandle, CURLOPT_NOBODY, 0L);

		curl.perform();

		xTEST(!buffHeader.empty());
		xTEST(!dataBuff.empty());
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
