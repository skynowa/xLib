/**
 * \file   HttpClient.cpp
 * \brief  HTTP client
 */


#include "HttpClient.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{


/**************************************************************************************************
*   OptionOut public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
OptionIn::print(
	core::OStream &a_os
) const
{
	a_os
		<< xTRACE_VAR(url)               << xT("\n")
		<< xTRACE_VAR(isUseHeader)       << xT("\n")
		<< xTRACE_VAR(isSslVerifyPeer)   << xT("\n")
		<< xTRACE_VAR(isSslVerifyHost)   << xT("\n")
		<< xTRACE_VAR(sslVersion)        << xT("\n")
		<< xTRACE_VAR(sslCert)           << xT("\n")
		<< xTRACE_VAR(sslCertPass)       << xT("\n")
		<< xTRACE_VAR((int)httpVersion)  << xT("\n")
		<< xTRACE_VAR(cookieFile)        << xT("\n")
		<< xTRACE_VAR(addCookie)         << xT("\n")
		<< xTRACE_VAR(encodingParam)     << xT("\n")
		<< xTRACE_VAR(ciphers)           << xT("\n")
		<< xTRACE_VAR(timeoutSec)        << xT("\n")
		<< xTRACE_VAR(timeoutMs)         << xT("\n")
		<< xTRACE_VAR(continueTimeoutMs) << xT("\n")
		<< xTRACE_VAR((int)proxyType)    << xT("\n")
		<< xTRACE_VAR(proxy)             << xT("\n")
		<< xTRACE_VAR(proxyUserPass)     << xT("\n")
		<< xTRACE_VAR(userPass)          << xT("\n")
		<< xTRACE_VAR(addHeaders)        << xT("\n")
		<< xTRACE_VAR(referer)           << xT("\n")
		<< xTRACE_VAR(accept)            << xT("\n")
		<< xTRACE_VAR(acceptEncoding)    << xT("\n")
		<< xTRACE_VAR(acceptLanguage)    << xT("\n")
		<< xTRACE_VAR(acceptCharset)     << xT("\n")
		<< xTRACE_VAR(userAgent)         << xT("\n")
		<< xTRACE_VAR(isFollowLocation)  << xT("\n")
		<< xTRACE_VAR(maxRedirects)      << xT("\n")
		<< xTRACE_VAR(isCacheControl)    << xT("\n")
		<< xTRACE_VAR(request);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   OptionOut public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
OptionOut::print(
	core::OStream &a_os
) const
{
	a_os
		<< xTRACE_VAR(contentType)  << xT("\n")
		<< xTRACE_VAR(effectiveUrl) << xT("\n")
		<< xTRACE_VAR(responseCode) << xT("\n")
		<< xTRACE_VAR(totalTimeSec) << xT("\n")
		// << xTRACE_VAR(headers)      << xT("\n")
		<< xTRACE_VAR(body);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
HttpClient::HttpClient(
	cbool_t a_isDebug
) :
	Client(a_isDebug)
{
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::get(
	OptionIn  &a_optionIn,		///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	return _request(Request::Get, a_optionIn, out_optionOut);
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::head(
	OptionIn  &a_optionIn,		///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	return _request(Request::Head, a_optionIn, out_optionOut);
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::post(
	OptionIn  &a_optionIn,		///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	return _request(Request::Post, a_optionIn, out_optionOut);
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::put(
	OptionIn  &a_optionIn,		///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	return _request(Request::Put, a_optionIn, out_optionOut);
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::del(
	OptionIn  &a_optionIn,		///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	return _request(Request::Delete, a_optionIn, out_optionOut);
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::connect(
	OptionIn  &a_optionIn,		///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	return _request(Request::Connect, a_optionIn, out_optionOut);
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::options(
	OptionIn  &a_optionIn,		///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	return _request(Request::Options, a_optionIn, out_optionOut);
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::trace(
	OptionIn  &a_optionIn,		///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	return _request(Request::Trace, a_optionIn, out_optionOut);
}
//-------------------------------------------------------------------------------------------------
/**
 * https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
 * https://restfulapi.net/http-status-codes/
 */
HttpClient::HttpCode
HttpClient::httpCode(
	cOptionOut &a_optionOut
) const
{
	static const std::map<std::pair<int, int>, HttpCode> httpCodes
	{
		{{100, 199}, HttpCode::Info       },
		{{200, 299}, HttpCode::Success    },
		{{300, 399}, HttpCode::Redirection},
		{{400, 499}, HttpCode::ClientError},
		{{500, 599}, HttpCode::ServerError}
	};

	for (const auto &[it_range, it_code] : httpCodes) {
		const auto &[it_low, it_high] = it_range;

		if ( Algos::isInBounds(a_optionOut.responseCode, it_low, it_high) ) {
			return it_code;
		}
	}

	return HttpCode::Unknown;
}
//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::isSuccess(
	cOptionOut &a_optionOut
) const
{
	return (httpCode(a_optionOut) == HttpCode::Success);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
HttpClient::setOptionsDefault(
	OptionIn          *a_optionIn,			///< [in,out]
	std::ctstring_t &a_buffRead,		///<
	std::tstring_t  *out_buffHeader,	///< [out]
	std::tstring_t  *out_buffData		///< [out]
)
{
	xTEST(_handle.isValid());
	xTEST_PTR(a_optionIn);
	xTEST_NA(a_buffRead);
	xTEST_PTR(out_buffHeader);
	xTEST_PTR(out_buffData);

	out_buffHeader->clear();
	out_buffData->clear();

	setOption(CURLOPT_URL, a_optionIn->url.c_str());

	// Download data
	{
		setOption(CURLOPT_WRITEHEADER,    out_buffHeader);
		setOption(CURLOPT_HEADERFUNCTION, onWriteHeader);

		setOption(CURLOPT_WRITEDATA,      out_buffData);
		setOption(CURLOPT_WRITEFUNCTION,  onWriteData);
	}

	// Upload data
	{
		_readData.buff = a_buffRead;

		setOption(CURLOPT_READDATA,     &_readData);
		setOption(CURLOPT_READFUNCTION,  onReadData);
	}

	setOption(CURLOPT_HEADER, static_cast<long_t>(a_optionIn->isUseHeader));

	//  CURLOPT_SSL...
	{
		setOption(CURLOPT_SSL_VERIFYPEER, static_cast<long_t>(a_optionIn->isSslVerifyPeer));
		setOption(CURLOPT_SSL_VERIFYHOST, a_optionIn->isSslVerifyHost ? 2L : 0L);
		setOption(CURLOPT_SSLVERSION,     a_optionIn->sslVersion);

		if ( !a_optionIn->sslCert.empty() ) {
			setOption(CURLOPT_SSLCERT,       a_optionIn->sslCert.c_str());
			setOption(CURLOPT_SSLCERTPASSWD, a_optionIn->sslCertPass.c_str());
		}
	}

	setOption(CURLOPT_HTTP_VERSION, a_optionIn->httpVersion);

	// CURLOPT_COOKIE...
	{
		if ( !a_optionIn->cookieFile.empty() ) {
			setOption(CURLOPT_COOKIESESSION, 0L);
			setOption(CURLOPT_COOKIEFILE,    a_optionIn->cookieFile.c_str());
			setOption(CURLOPT_COOKIEJAR,     a_optionIn->cookieFile.c_str());
		}

		if ( !a_optionIn->addCookie.empty() ) {
			setOption(CURLOPT_COOKIE, a_optionIn->addCookie.c_str());
		}
	}

	if ( !a_optionIn->encodingParam.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, a_optionIn->encodingParam.c_str());
	}

	if ( !a_optionIn->ciphers.empty() ) {
		setOption(CURLOPT_SSL_CIPHER_LIST, a_optionIn->ciphers.c_str());
	}

	// FTP
	{
		curl_slist *quotes {};
		setOption(CURLOPT_QUOTE, quotes);

		curl_slist *postQuotes {};
		setOption(CURLOPT_POSTQUOTE, postQuotes);
	}

	// CURLOPT_TIMEOUT...
	{
		if (a_optionIn->timeoutMs > 0) {
			if (a_optionIn->timeoutMs >= 1000) {
				setOption(CURLOPT_TIMEOUT_MS,        0L);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
				setOption(CURLOPT_TIMEOUT,           a_optionIn->timeoutMs / 1000);
				setOption(CURLOPT_CONNECTTIMEOUT ,   a_optionIn->timeoutMs / 1000);
			} else {
				setOption(CURLOPT_TIMEOUT,           0L);
				setOption(CURLOPT_CONNECTTIMEOUT,    0L);
				setOption(CURLOPT_TIMEOUT_MS,        a_optionIn->timeoutMs);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, a_optionIn->timeoutMs);
			}
		}
		else if (a_optionIn->timeoutSec > 0) {
			setOption(CURLOPT_TIMEOUT_MS,        0L);
			setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
			setOption(CURLOPT_TIMEOUT,           a_optionIn->timeoutSec);
			setOption(CURLOPT_CONNECTTIMEOUT,    a_optionIn->timeoutSec);
		}

		if (a_optionIn->continueTimeoutMs > 0) {
			setOption(CURLOPT_EXPECT_100_TIMEOUT_MS, a_optionIn->continueTimeoutMs);
		}
	}

	// CURLOPT_PROXY
	if ( !a_optionIn->proxy.empty() ) {
		setOption(CURLOPT_PROXY,     a_optionIn->proxy.c_str());
		setOption(CURLOPT_PROXYTYPE, a_optionIn->proxyType);

		if ( !a_optionIn->proxyUserPass.empty() ) {
			setOption(CURLOPT_PROXYUSERPWD, a_optionIn->proxyUserPass.c_str());
		}
	}

	if ( !a_optionIn->userPass.empty() ) {
		setOption(CURLOPT_USERPWD, a_optionIn->userPass.c_str());
	}

	// CURLOPT_HTTPHEADER
	{
		// _headers
		{
			curl_slist *headers {};

			if ( !a_optionIn->accept.empty() ) {
				std::ctstring_t &value = xT("Accept: ") + a_optionIn->accept;

				headers = ::curl_slist_append(headers, value.c_str());
			}

			if ( !a_optionIn->acceptLanguage.empty() ) {
				std::ctstring_t &value = xT("Accept-Language: ") + a_optionIn->acceptLanguage;

				headers = ::curl_slist_append(headers, value.c_str());
			}

			if ( !a_optionIn->acceptCharset.empty() ) {
				std::ctstring_t &value = xT("Accept-Charset: ") + a_optionIn->acceptCharset;

				headers = ::curl_slist_append(headers, value.c_str());
			}

			if (a_optionIn->isCacheControl) {
				// use cache
			} else {
				// no cache
				headers = ::curl_slist_append(headers, xT("Cache-Control: no-cache"));

				// SEE: also set in HttpClient::request()
			}

			for (const auto &[param, value] : a_optionIn->addHeaders) {
				std::ctstring_t &value_ = param + xT(": ") + value;

				headers = ::curl_slist_append(headers, value_.c_str());
			}

			// [out]
			_headers.reset(headers);
		}

		// set list
		setOption(CURLOPT_HTTPHEADER, _headers.get());
	}

	if ( !a_optionIn->referer.empty() ) {
		setOption(CURLOPT_REFERER, a_optionIn->referer.c_str());
	}

	if ( !a_optionIn->acceptEncoding.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, a_optionIn->acceptEncoding.c_str());
	}

	if ( !a_optionIn->userAgent.empty() ) {
		setOption(CURLOPT_USERAGENT, a_optionIn->userAgent.c_str());
	}

	// curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1);
	setOption(CURLOPT_FOLLOWLOCATION, static_cast<long_t>(a_optionIn->isFollowLocation));
	setOption(CURLOPT_MAXREDIRS,      a_optionIn->maxRedirects);
}
//-------------------------------------------------------------------------------------------------
void_t
HttpClient::getInfos(
	OptionOut *out_optionOut	///< [out]
)
{
	xTEST(_handle.isValid());

	{
		tchar_t *contentType {};
		info(CURLINFO_CONTENT_TYPE, &contentType);

		out_optionOut->contentType = (contentType == nullptr ? xT("") : contentType);
	}

	{
		tchar_t *effectiveUrl {};
		info(CURLINFO_EFFECTIVE_URL, &effectiveUrl);

		out_optionOut->effectiveUrl = (effectiveUrl == nullptr ? xT("") : effectiveUrl);
	}

	{
		int_t responseCode {};
		info(CURLINFO_RESPONSE_CODE, &responseCode);

		out_optionOut->responseCode = responseCode;
	}

	{
		double_t totalTimeSec {};
		info(CURLINFO_TOTAL_TIME, &totalTimeSec);

		out_optionOut->totalTimeSec = totalTimeSec;
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
HttpClient::_request(
	cRequest   a_type,		///<
	OptionIn  &a_optionIn,	///< [in,out]
	OptionOut *out_optionOut	///< [out]
)
{
	xTEST_DIFF((int)a_type, (int)Request::Unknown);
	xTEST_PTR(out_optionOut);

	out_optionOut->headers.clear();
	out_optionOut->body.clear();

	setOption(CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);

	switch (a_type) {
	case Request::Get:
		{
		   /**
			* Retrieve information from the given server using a given URI.
			* Requests using GET should only retrieve data and should have no other effect
			* on the data
			*/

			a_optionIn.url += xT("?") + a_optionIn.request;

			if (!a_optionIn.isCacheControl) {
				std::ctstring_t sessId = std::to_string( DateTime().current().toMsec() );

				a_optionIn.url += "&SessId=" + escape(sessId);
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
			setOption(CURLOPT_POSTFIELDS,    a_optionIn.request.data());
			setOption(CURLOPT_POSTFIELDSIZE, a_optionIn.request.size());
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
		xTEST(false);
		return false;
		break;
	}

	std::tstring_t buffRead;
	std::tstring_t buffHeaderOut;
	std::tstring_t buffOptionOut;
	setOptionsDefault(&a_optionIn, buffRead, &buffHeaderOut, &buffOptionOut);

	perform();

	getInfos(out_optionOut);

	// [out]
	String::split(buffHeaderOut, Const::crNl(), xT(": "), &out_optionOut->headers);
	out_optionOut->body = buffOptionOut;

	return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
