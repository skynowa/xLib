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



//-------------------------------------------------------------------------------------------------
HttpClient::HttpClient()
{
}
//-------------------------------------------------------------------------------------------------
HttpClient::~HttpClient()
{
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::request(
	cRequestType     a_type,			///<
	BaseData        &a_baseData,		///< [in,out]
	BaseDataOut     *out_baseDataOut	///< [out]
)
{
	xTEST_DIFF((int)a_type, (int)RequestType::Unknown);
	xTEST_PTR(out_baseDataOut);

	out_baseDataOut->headers.clear();
	out_baseDataOut->body.clear();

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
	CurlBase::setOptionsDefault(&a_baseData, headers, &buffHeader, &buffData);

	/*CURLcode st = */ perform();

	CurlBase::getInfos(out_baseDataOut);

	Utils::freeT(headers, ::curl_slist_free_all, nullptr);

	/// _error = st;

	// [out]
	out_baseDataOut->headers = buffHeader.buffer();
	out_baseDataOut->body    = buffData.buffer();

	return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, package, curl)
