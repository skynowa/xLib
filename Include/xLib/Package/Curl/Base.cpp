/**
 * \file  CurlBase.cpp
 * \brief CURL client
 */


#include "Base.h"


xNAMESPACE_BEGIN3(xl, package, curl)

/**************************************************************************************************
*   DebugData public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
DataIn::DebugData::clear()
{
	text.clear();
	headerIn.clear();
	headerOut.clear();
	dataIn.clear();
	dataOut.clear();
	sslDataIn.clear();
	sslDataOut.clear();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
CurlBase::setProtocols(
	clong_t a_bitMask	///< bitmask of CURLPROTO_* defines (CURLPROTO_HTTP, ..., CURLPROTO_ALL)
)
{
	setOption(CURLOPT_PROTOCOLS, a_bitMask);
}
//-------------------------------------------------------------------------------------------------
void_t
CurlBase::setOptionsDefault(
	DataIn      *a_dataIn,			///< [in,out]
	curl_slist  *out_headers,		///< [out]
	Buffer      *out_buffHeader,	///< [out]
	Buffer      *out_buffData		///< [out]
)
{
	xTEST(_handle.isValid());
	xTEST_PTR(out_buffHeader);
	xTEST_PTR(out_buffData);

	out_headers = nullptr;
	out_buffHeader->clear();
	out_buffData->clear();

	setOption(CURLOPT_URL, a_dataIn->url.c_str());

	{
		setOption(CURLOPT_WRITEHEADER,    out_buffHeader);
		setOption(CURLOPT_HEADERFUNCTION, onWriteHeader);

		setOption(CURLOPT_WRITEDATA,      out_buffData);
		setOption(CURLOPT_WRITEFUNCTION,  onWriteData);
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

	setOption(CURLOPT_VERBOSE, static_cast<long_t>(a_dataIn->isVerbose));

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

	setOption(CURLOPT_ERRORBUFFER, a_dataIn->errorStr);

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
		if ( !a_dataIn->accept.empty() ) {
			std::ctstring_t &value = xT("Accept: ") + a_dataIn->accept;

			out_headers = ::curl_slist_append(out_headers, value.c_str());
		}

		if ( !a_dataIn->acceptLanguage.empty() ) {
			std::ctstring_t &value = xT("Accept-Language: ") + a_dataIn->acceptLanguage;

			out_headers = ::curl_slist_append(out_headers, value.c_str());
		}

		if ( !a_dataIn->acceptCharset.empty() ) {
			std::ctstring_t &value = xT("Accept-Charset: ") + a_dataIn->acceptCharset;

			out_headers = ::curl_slist_append(out_headers, value.c_str());
		}

		for (auto &it_header : a_dataIn->addHeader) {
			std::ctstring_t &value = it_header.first + xT(": ") + it_header.second;

			out_headers = ::curl_slist_append(out_headers, value.c_str());
		}

		setOption(CURLOPT_HTTPHEADER, out_headers);
	}

	if ( !a_dataIn->referer.empty() ) {
		setOption(CURLOPT_REFERER, a_dataIn->referer.c_str());
	}

	if ( !a_dataIn->acceptEncoding.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, a_dataIn->acceptEncoding.c_str());
	}

	if ( !a_dataIn->user_agent.empty() ) {
		setOption(CURLOPT_USERAGENT, a_dataIn->user_agent.c_str());
	}

	// curl_easy_setopt(curl, CURLOPT_AUTOREFERER , 1);
	setOption(CURLOPT_FOLLOWLOCATION, static_cast<long_t>(a_dataIn->isFollowLocation));
	setOption(CURLOPT_MAXREDIRS,      a_dataIn->maxRedirects);

	// CURLOPT_DEBUG...
	if (a_dataIn->isDebugHeader) {
		setOption(CURLOPT_VERBOSE,       1L);
		setOption(CURLOPT_DEBUGFUNCTION, onDebug);

		a_dataIn->debugData.clear();
		setOption(CURLOPT_DEBUGDATA, &a_dataIn->debugData);
	}
}
//-------------------------------------------------------------------------------------------------
void_t
CurlBase::getInfos(
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

	/// if (data.isDebugHeader) {
	/// 	// data.debugData - with data
	/// }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, package, curl)
