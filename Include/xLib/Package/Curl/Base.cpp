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
BaseData::DebugData::clear()
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
	BaseData   *a_data,			///< [in,out]
	curl_slist *out_headers,	///< [out]
	Buffer     *out_buffHeader,	///< [out]
	Buffer     *out_buffData	///< [out]
)
{
	xTEST(_handle.isValid());
	xTEST_PTR(out_buffHeader);
	xTEST_PTR(out_buffData);

	out_headers = nullptr;
	out_buffHeader->clear();
	out_buffData->clear();

	setOption(CURLOPT_URL, a_data->url.c_str());

	{
		setOption(CURLOPT_HEADERFUNCTION, onWriteHeader);
		setOption(CURLOPT_WRITEHEADER, out_buffHeader);

		setOption(CURLOPT_WRITEFUNCTION, onWriteData);
		setOption(CURLOPT_WRITEDATA, out_buffData);
	}

	setOption(CURLOPT_HEADER, static_cast<long_t>(a_data->isUseHeader));

	//  CURLOPT_SSL...
	{
		setOption(CURLOPT_SSL_VERIFYPEER, static_cast<long_t>(a_data->isSslVerifyPeer));
		setOption(CURLOPT_SSL_VERIFYHOST, a_data->isSslVerifyHost ? 2L : 0L);
		setOption(CURLOPT_SSLVERSION,     a_data->sslVersion);

		if ( !a_data->sslCert.empty() ) {
			setOption(CURLOPT_SSLCERT,       a_data->sslCert.c_str());
			setOption(CURLOPT_SSLCERTPASSWD, a_data->sslCertPass.c_str());
		}
	}

	setOption(CURLOPT_HTTP_VERSION, a_data->httpVersion);

	setOption(CURLOPT_VERBOSE, static_cast<long_t>(a_data->isVerbose));

	// CURLOPT_COOKIE...
	{
		if ( !a_data->cookieFile.empty() ) {
			setOption(CURLOPT_COOKIESESSION, 0L);
			setOption(CURLOPT_COOKIEFILE,    a_data->cookieFile.c_str());
			setOption(CURLOPT_COOKIEJAR,     a_data->cookieFile.c_str());
		}

		if ( !a_data->addCookie.empty() ) {
			setOption(CURLOPT_COOKIE, a_data->addCookie.c_str());
		}
	}

	if ( !a_data->encodingParam.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, a_data->encodingParam.c_str());
	}

	if ( !a_data->ciphers.empty() ) {
		setOption(CURLOPT_SSL_CIPHER_LIST, a_data->ciphers.c_str());
	}

	setOption(CURLOPT_ERRORBUFFER, a_data->errorStr);

	// FTP
	{
		curl_slist *quotes {};
		setOption(CURLOPT_QUOTE, quotes);

		curl_slist *postQuotes {};
		setOption(CURLOPT_POSTQUOTE, postQuotes);
	}

	// CURLOPT_TIMEOUT...
	{
		if (a_data->timeoutMs > 0) {
			if (a_data->timeoutMs >= 1000) {
				setOption(CURLOPT_TIMEOUT_MS,        0L);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
				setOption(CURLOPT_TIMEOUT,           a_data->timeoutMs / 1000);
				setOption(CURLOPT_CONNECTTIMEOUT ,   a_data->timeoutMs / 1000);
			} else {
				setOption(CURLOPT_TIMEOUT,           0L);
				setOption(CURLOPT_CONNECTTIMEOUT,    0L);
				setOption(CURLOPT_TIMEOUT_MS,        a_data->timeoutMs);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, a_data->timeoutMs);
			}
		}
		else if (a_data->timeoutSec > 0) {
			setOption(CURLOPT_TIMEOUT_MS,        0L);
			setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
			setOption(CURLOPT_TIMEOUT,           a_data->timeoutSec);
			setOption(CURLOPT_CONNECTTIMEOUT,    a_data->timeoutSec);
		}

		if (a_data->continueTimeoutMs > 0) {
			setOption(CURLOPT_EXPECT_100_TIMEOUT_MS, a_data->continueTimeoutMs);
		}
	}

	// CURLOPT_PROXY
	if ( !a_data->proxy.empty() ) {
		setOption(CURLOPT_PROXY,     a_data->proxy.c_str());
		setOption(CURLOPT_PROXYTYPE, a_data->proxyType);

		if ( !a_data->proxyUserPass.empty() ) {
			setOption(CURLOPT_PROXYUSERPWD, a_data->proxyUserPass.c_str());
		}
	}

	if ( !a_data->userPass.empty() ) {
		setOption(CURLOPT_USERPWD, a_data->userPass.c_str());
	}

	// CURLOPT_HTTPHEADER
	{
		for (auto &it_header : a_data->addHeader) {
			std::ctstring_t value = it_header.first + xT(": ") + it_header.second;

			out_headers = ::curl_slist_append(out_headers, value.c_str());
		}

		setOption(CURLOPT_HTTPHEADER, out_headers);
	}

	if ( !a_data->referer.empty() ) {
		setOption(CURLOPT_REFERER, a_data->referer.c_str());
	}

	if ( !a_data->acceptEncoding.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, a_data->acceptEncoding.c_str());
	}

	if ( !a_data->agent.empty() ) {
		setOption(CURLOPT_USERAGENT, a_data->agent.c_str());
	}

	// curl_easy_setopt(curl, CURLOPT_AUTOREFERER , 1);
	setOption(CURLOPT_FOLLOWLOCATION, static_cast<long_t>(a_data->isFollowLocation));
	setOption(CURLOPT_MAXREDIRS,      a_data->maxRedirects);

	// CURLOPT_DEBUG...
	if (a_data->isDebugHeader) {
		setOption(CURLOPT_VERBOSE,       1L);
		setOption(CURLOPT_DEBUGFUNCTION, onDebug);

		a_data->debugData.clear();
		setOption(CURLOPT_DEBUGDATA, &a_data->debugData);
	}
}
//-------------------------------------------------------------------------------------------------
void_t
CurlBase::getInfos(
	BaseDataOut *out_dataOut	///< [out]
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
