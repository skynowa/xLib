/**
 * \file   HttpClient.cpp
 * \brief  HTTP client
 */


#include "HttpClient.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>


//-------------------------------------------------------------------------------------------------
namespace
{

struct SlistDeleter
{
	void operator() (struct curl_slist *&a_list) const
	{
		if (a_list == nullptr) {
			return;
		}

		::curl_slist_free_all(a_list); a_list = nullptr;
	}
};
using slist_unique_ptr_t = std::unique_ptr<struct curl_slist, SlistDeleter>;

} // namespace
//-------------------------------------------------------------------------------------------------

xNAMESPACE_BEGIN3(xl, package, curl)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::request(
	cRequest  a_type,		///<
	DataIn   &a_dataIn,		///< [in,out]
	DataOut  *out_dataOut	///< [out]
)
{
	xTEST_DIFF((int)a_type, (int)Request::Unknown);
	xTEST_PTR(out_dataOut);

	out_dataOut->headers.clear();
	out_dataOut->body.clear();

	setProtocols(CURLPROTO_HTTP | CURLPROTO_HTTPS);

	switch (a_type) {
	case Request::Get:
		{
		   /**
			* Retrieve information from the given server using a given URI.
			* Requests using GET should only retrieve data and should have no other effect
			* on the data
			*/

			a_dataIn.url += xT("?") + a_dataIn.request;

			if (!a_dataIn.isCacheControl) {
				std::ctstring_t sessId = std::to_string( DateTime().current().toMsec() );

				a_dataIn.url += "&SessId=" + escape(sessId);
			}

			setOption(CURLOPT_POST,   0L);
			setOption(CURLOPT_NOBODY, 0L);
		}
		break;
	case Request::Head:
		{
		   /**
			* Same as GET, but transfers the status line and header section only
			*/

			setOption(CURLOPT_NOBODY, 1L);
		}
		break;
	case Request::Post:
		{
		   /**
			* Send data to the server, for example, customer information, file upload, etc.
			* using HTML forms
			*/

			setOption(CURLOPT_POST,          1L);
			setOption(CURLOPT_POSTFIELDS,    a_dataIn.request.c_str());
			setOption(CURLOPT_POSTFIELDSIZE, a_dataIn.request.size());
		}
		break;
	case Request::Put:
		{
		   /**
			* Replaces all current representations of the target resource with uploaded content
			*/

			// TODO: Request::Put
			setOption(CURLOPT_UPLOAD, 1L);
		}
		break;
	case Request::Delete:
		{
		   /**
			* Removes all current representations of the target resource given by a URI
			*/

			setOption(CURLOPT_CUSTOMREQUEST, xT("DELETE"));
		}
		break;
	case Request::Connect:
		{
		   /**
			* Establishes a tunnel to the server identified by a given URI
			*/

			// TODO: Request::Connect
		}
		break;
	case Request::Options:
		{
		   /**
			* Describes the communication options for the target resource
			*/

			// TODO: Request::Options
		}
		break;
	case Request::Trace:
		{
		   /**
			* Performs a message loop-back test along the path to the target resource
			*/

			// TODO: Request::Trace
		}
		break;
	case Request::Unknown:
	default:
		xTEST(false);
		return false;
		break;
	}

	slist_unique_ptr_t headersIn;
	std::tstring_t     buffHeaderOut;
	std::tstring_t     buffDataOut;
	BaseClient::setOptionsDefault(&a_dataIn, headersIn.get(), &buffHeaderOut, &buffDataOut);

	/* CURLcode st = */ perform();
#if 0
	Cout()
		<< "buffHeaderOut: [" << buffHeaderOut << "]\n"
		<< "buffDataOut: ["   << buffDataOut <<   "]";
#endif

	BaseClient::getInfos(out_dataOut);

	/// _error = st;

	// [out]
	String::split(buffHeaderOut, Const::crNl(), xT(": "), &out_dataOut->headers);
	out_dataOut->body = buffDataOut;

	return true;
}
//-------------------------------------------------------------------------------------------------
/**
 * https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
 * https://restfulapi.net/http-status-codes/
 */
HttpClient::HttpCode
HttpClient::httpCode(
	cDataOut &a_dataOut
) const
{
	HttpCode hcRv {};

	if      (a_dataOut.responseCode >= 100 && a_dataOut.responseCode <= 199) {
		hcRv = HttpCode::Info;
	}
	else if (a_dataOut.responseCode >= 200 && a_dataOut.responseCode <= 299) {
		hcRv = HttpCode::Success;
	}
	else if (a_dataOut.responseCode >= 300 && a_dataOut.responseCode <= 399) {
		hcRv = HttpCode::Redirection;
	}
	else if (a_dataOut.responseCode >= 400 && a_dataOut.responseCode <= 499) {
		hcRv = HttpCode::ClientError;
	}
	else if (a_dataOut.responseCode >= 500 && a_dataOut.responseCode <= 599) {
		hcRv = HttpCode::ServerError;
	}
	else {
		hcRv = HttpCode::Unknown;
	}

	return hcRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::isSuccess(
	cDataOut &a_dataOut
) const
{
	return (httpCode(a_dataOut) == HttpCode::Success);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, package, curl)
