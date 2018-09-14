/**
 * \file   HttpClient.cpp
 * \brief  HTTP client
 */


#include "HttpClient.h"


xNAMESPACE_BEGIN3(xl, package, curl)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

BaseData baseData;

//-------------------------------------------------------------------------------------------------
HttpClient::HttpClient() :
	CurlBase(baseData)
{
}
//-------------------------------------------------------------------------------------------------
HttpClient::~HttpClient()
{
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::request(
	cRequestType     a_type,				///<
	std::ctstring_t &a_url,					///<
	std::ctstring_t &a_request,				///<
	std::tstring_t  *out_responseHeader,	///< [out]
	std::tstring_t  *out_responseBody		///< [out]
)
{
	xTEST_DIFF((int)a_type, (int)RequestType::Unknown);
	xTEST_EQ(a_url.empty(), false);
	xTEST_NA(a_request);
	xTEST_PTR(out_responseHeader);
	xTEST_PTR(out_responseBody);

	out_responseHeader->clear();
	out_responseBody->clear();

	// CurlBase - overrides
	data.url = a_url;

	setProtocols(CURLPROTO_HTTP | CURLPROTO_HTTPS);

	switch (a_type) {
	case RequestType::Get:
		{
			setOption(CURLOPT_POST, 0L);
			setOption(CURLOPT_NOBODY, 0L);
		}
		break;
	case RequestType::Head:
		{
			setOption(CURLOPT_NOBODY, 1L);
		}
		break;
	case RequestType::Post:
		{
			setOption(CURLOPT_POST, 1L);
		}
		break;
	case RequestType::Put:
		{
			// TODO: RequestType::Put
			setOption(CURLOPT_UPLOAD, 1L);
		}
		break;
	case RequestType::Delete:
		{
			setOption(CURLOPT_CUSTOMREQUEST, xT("DELETE"));
		}
		break;
	case RequestType::Connect:
		{
			// TODO: RequestType::Connect
		}
		break;
	case RequestType::Options:
		{
			// TODO: RequestType::Options
		}
		break;
	case RequestType::Trace:
		{
			// TODO: RequestType::Trace
		}
		break;
	case RequestType::Unknown:
	default:
		xTEST(false);
		return false;
		break;
	}

	curl_slist *headers {};
	Buffer      buffHeader;
	Buffer      buffData;
	CurlBase::setOptionsDefault(headers, &buffHeader, &buffData);

	/*CURLcode st = */ perform();

	getInfos();

	if (headers) {
		::curl_slist_free_all(headers);
		headers = nullptr;
	}

	/// _error = st;

	// [out]
	*out_responseHeader = buffHeader.buffer();
	*out_responseBody   = buffData.buffer();

	return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, package, curl)
