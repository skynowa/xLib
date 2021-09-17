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
*   DataOut public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
DataIn::print(
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
*   DataOut public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
DataOut::print(
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

	setOption(CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);

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
			setOption(CURLOPT_POSTFIELDS,    a_dataIn.request.data());
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
		xTEST(false);
		return false;
		break;
	}

	std::tstring_t buffRead;
	std::tstring_t buffHeaderOut;
	std::tstring_t buffDataOut;
	setOptionsDefault(&a_dataIn, buffRead, &buffHeaderOut, &buffDataOut);

	perform();

	getInfos(out_dataOut);

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
	static const std::map<std::pair<int, int>, HttpCode> httpCodes
	{
		{{100, 199}, HttpCode::Info       },
		{{200, 299}, HttpCode::Success    },
		{{300, 399}, HttpCode::Redirection},
		{{400, 499}, HttpCode::ClientError},
		{{500, 599}, HttpCode::ServerError}
	};

	for (const auto &[it_range, it_code] : httpCodes) {
		if ( Algos::isInBounds(a_dataOut.responseCode, it_range.first, it_range.second) ) {
			return it_code;
		}
	}

	return HttpCode::Unknown;
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


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
HttpClient::setOptionsDefault(
	DataIn          *a_dataIn,			///< [in,out]
	std::ctstring_t &a_buffRead,		///<
	std::tstring_t  *out_buffHeader,	///< [out]
	std::tstring_t  *out_buffData		///< [out]
)
{
	xTEST(_handle.isValid());
	xTEST_PTR(a_dataIn);
	xTEST_NA(a_buffRead);
	xTEST_PTR(out_buffHeader);
	xTEST_PTR(out_buffData);

	out_buffHeader->clear();
	out_buffData->clear();

	setOption(CURLOPT_URL, a_dataIn->url.c_str());

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

	setOption(CURLOPT_HEADER, static_cast<long_t>(a_dataIn->isUseHeader));

	//  CURLOPT_SSL...
	{
		setOption(CURLOPT_SSL_VERIFYPEER, static_cast<long_t>(a_dataIn->isSslVerifyPeer));
		setOption(CURLOPT_SSL_VERIFYHOST, a_dataIn->isSslVerifyHost ? 2L : 0L);
		setOption(CURLOPT_SSLVERSION,     a_dataIn->sslVersion);

		if ( !a_dataIn->sslCert.empty() ) {
			setOption(CURLOPT_SSLCERT,       a_dataIn->sslCert.c_str());
			setOption(CURLOPT_SSLCERTPASSWD, a_dataIn->sslCertPass.c_str());
		}
	}

	setOption(CURLOPT_HTTP_VERSION, a_dataIn->httpVersion);

	// CURLOPT_COOKIE...
	{
		if ( !a_dataIn->cookieFile.empty() ) {
			setOption(CURLOPT_COOKIESESSION, 0L);
			setOption(CURLOPT_COOKIEFILE,    a_dataIn->cookieFile.c_str());
			setOption(CURLOPT_COOKIEJAR,     a_dataIn->cookieFile.c_str());
		}

		if ( !a_dataIn->addCookie.empty() ) {
			setOption(CURLOPT_COOKIE, a_dataIn->addCookie.c_str());
		}
	}

	if ( !a_dataIn->encodingParam.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, a_dataIn->encodingParam.c_str());
	}

	if ( !a_dataIn->ciphers.empty() ) {
		setOption(CURLOPT_SSL_CIPHER_LIST, a_dataIn->ciphers.c_str());
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
		if (a_dataIn->timeoutMs > 0) {
			if (a_dataIn->timeoutMs >= 1000) {
				setOption(CURLOPT_TIMEOUT_MS,        0L);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
				setOption(CURLOPT_TIMEOUT,           a_dataIn->timeoutMs / 1000);
				setOption(CURLOPT_CONNECTTIMEOUT ,   a_dataIn->timeoutMs / 1000);
			} else {
				setOption(CURLOPT_TIMEOUT,           0L);
				setOption(CURLOPT_CONNECTTIMEOUT,    0L);
				setOption(CURLOPT_TIMEOUT_MS,        a_dataIn->timeoutMs);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, a_dataIn->timeoutMs);
			}
		}
		else if (a_dataIn->timeoutSec > 0) {
			setOption(CURLOPT_TIMEOUT_MS,        0L);
			setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
			setOption(CURLOPT_TIMEOUT,           a_dataIn->timeoutSec);
			setOption(CURLOPT_CONNECTTIMEOUT,    a_dataIn->timeoutSec);
		}

		if (a_dataIn->continueTimeoutMs > 0) {
			setOption(CURLOPT_EXPECT_100_TIMEOUT_MS, a_dataIn->continueTimeoutMs);
		}
	}

	// CURLOPT_PROXY
	if ( !a_dataIn->proxy.empty() ) {
		setOption(CURLOPT_PROXY,     a_dataIn->proxy.c_str());
		setOption(CURLOPT_PROXYTYPE, a_dataIn->proxyType);

		if ( !a_dataIn->proxyUserPass.empty() ) {
			setOption(CURLOPT_PROXYUSERPWD, a_dataIn->proxyUserPass.c_str());
		}
	}

	if ( !a_dataIn->userPass.empty() ) {
		setOption(CURLOPT_USERPWD, a_dataIn->userPass.c_str());
	}

	// CURLOPT_HTTPHEADER
	{
		// _headers
		{
			curl_slist *headers {};

			if ( !a_dataIn->accept.empty() ) {
				std::ctstring_t &value = xT("Accept: ") + a_dataIn->accept;

				headers = ::curl_slist_append(headers, value.c_str());
			}

			if ( !a_dataIn->acceptLanguage.empty() ) {
				std::ctstring_t &value = xT("Accept-Language: ") + a_dataIn->acceptLanguage;

				headers = ::curl_slist_append(headers, value.c_str());
			}

			if ( !a_dataIn->acceptCharset.empty() ) {
				std::ctstring_t &value = xT("Accept-Charset: ") + a_dataIn->acceptCharset;

				headers = ::curl_slist_append(headers, value.c_str());
			}

			if (a_dataIn->isCacheControl) {
				// use cache
			} else {
				// no cache
				headers = ::curl_slist_append(headers, xT("Cache-Control: no-cache"));

				// SEE: also set in HttpClient::request()
			}

			for (const auto &[param, value] : a_dataIn->addHeaders) {
				std::ctstring_t &value_ = param + xT(": ") + value;

				headers = ::curl_slist_append(headers, value_.c_str());
			}

			// [out]
			_headers.reset(headers);
		}

		// set list
		setOption(CURLOPT_HTTPHEADER, _headers.get());
	}

	if ( !a_dataIn->referer.empty() ) {
		setOption(CURLOPT_REFERER, a_dataIn->referer.c_str());
	}

	if ( !a_dataIn->acceptEncoding.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, a_dataIn->acceptEncoding.c_str());
	}

	if ( !a_dataIn->userAgent.empty() ) {
		setOption(CURLOPT_USERAGENT, a_dataIn->userAgent.c_str());
	}

	// curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1);
	setOption(CURLOPT_FOLLOWLOCATION, static_cast<long_t>(a_dataIn->isFollowLocation));
	setOption(CURLOPT_MAXREDIRS,      a_dataIn->maxRedirects);
}
//-------------------------------------------------------------------------------------------------
void_t
HttpClient::getInfos(
	DataOut *out_dataOut	///< [out]
)
{
	xTEST(_handle.isValid());

	{
		tchar_t *contentType {};
		info(CURLINFO_CONTENT_TYPE, &contentType);

		out_dataOut->contentType = (contentType == nullptr ? xT("") : contentType);
	}

	{
		tchar_t *effectiveUrl {};
		info(CURLINFO_EFFECTIVE_URL, &effectiveUrl);

		out_dataOut->effectiveUrl = (effectiveUrl == nullptr ? xT("") : effectiveUrl);
	}

	{
		int_t responseCode {};
		info(CURLINFO_RESPONSE_CODE, &responseCode);

		out_dataOut->responseCode = responseCode;
	}

	{
		double_t totalTimeSec {};
		info(CURLINFO_TOTAL_TIME, &totalTimeSec);

		out_dataOut->totalTimeSec = totalTimeSec;
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
