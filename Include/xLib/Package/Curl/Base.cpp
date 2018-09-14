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
void
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
CurlBase::CurlBase(
	BaseData &a_data
) :
	data(a_data)
{
}
//-------------------------------------------------------------------------------------------------
CurlBase::~CurlBase()
{
}
//-------------------------------------------------------------------------------------------------
void
CurlBase::setProtocols(
	clong_t a_bitMask	///< bitmask of CURLPROTO_* defines (CURLPROTO_HTTP, ..., CURLPROTO_ALL)
)
{
	setOption(CURLOPT_PROTOCOLS, a_bitMask);
}
//-------------------------------------------------------------------------------------------------
void
CurlBase::setOptionsDefault(
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

	setOption(CURLOPT_URL, data.url.c_str());

	{
		setOption(CURLOPT_HEADERFUNCTION, onWriteHeader);
		setOption(CURLOPT_WRITEHEADER, out_buffHeader);

		setOption(CURLOPT_WRITEFUNCTION, onWriteData);
		setOption(CURLOPT_WRITEDATA, out_buffData);
	}

	setOption(CURLOPT_HEADER, static_cast<long_t>(data.isUseHeader));

	//  CURLOPT_SSL...
	{
		setOption(CURLOPT_SSL_VERIFYPEER, static_cast<long_t>(data.isSslVerifyPeer));
		setOption(CURLOPT_SSL_VERIFYHOST, data.isSslVerifyHost ? 2L : 0L);
		setOption(CURLOPT_SSLVERSION,     data.sslVersion);

		if ( !data.sslCert.empty() ) {
			setOption(CURLOPT_SSLCERT,       data.sslCert.c_str());
			setOption(CURLOPT_SSLCERTPASSWD, data.sslCertPass.c_str());
		}
	}

	setOption(CURLOPT_HTTP_VERSION, data.httpVersion);

	setOption(CURLOPT_VERBOSE, static_cast<long_t>(data.isVerbose));

	// CURLOPT_COOKIE...
	{
		if ( !data.cookieFile.empty() ) {
			setOption(CURLOPT_COOKIESESSION, 0L);
			setOption(CURLOPT_COOKIEFILE,    data.cookieFile.c_str());
			setOption(CURLOPT_COOKIEJAR,     data.cookieFile.c_str());
		}

		if ( !data.addCookie.empty() ) {
			setOption(CURLOPT_COOKIE, data.addCookie.c_str());
		}
	}

	if ( !data.encodingParam.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, data.encodingParam.c_str());
	}

	if ( !data.ciphers.empty() ) {
		setOption(CURLOPT_SSL_CIPHER_LIST, data.ciphers.c_str());
	}

	setOption(CURLOPT_ERRORBUFFER, data.errorStr);

	// FTP
	{
		curl_slist *quotes {};
		setOption(CURLOPT_QUOTE, quotes);

		curl_slist *postQuotes {};
		setOption(CURLOPT_POSTQUOTE, postQuotes);
	}

	// CURLOPT_TIMEOUT...
	{
		if (data.timeoutMs > 0) {
			if (data.timeoutMs >= 1000) {
				setOption(CURLOPT_TIMEOUT_MS,        0L);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
				setOption(CURLOPT_TIMEOUT,           data.timeoutMs / 1000);
				setOption(CURLOPT_CONNECTTIMEOUT ,   data.timeoutMs / 1000);
			} else {
				setOption(CURLOPT_TIMEOUT,           0L);
				setOption(CURLOPT_CONNECTTIMEOUT,    0L);
				setOption(CURLOPT_TIMEOUT_MS,        data.timeoutMs);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, data.timeoutMs);
			}
		}
		else if (data.timeoutSec > 0) {
			setOption(CURLOPT_TIMEOUT_MS,        0L);
			setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
			setOption(CURLOPT_TIMEOUT,           data.timeoutSec);
			setOption(CURLOPT_CONNECTTIMEOUT,    data.timeoutSec);
		}

		if (data.continueTimeoutMs > 0) {
			setOption(CURLOPT_EXPECT_100_TIMEOUT_MS, data.continueTimeoutMs);
		}
	}

	// CURLOPT_PROXY
	if ( !data.proxy.empty() ) {
		setOption(CURLOPT_PROXY,     data.proxy.c_str());
		setOption(CURLOPT_PROXYTYPE, data.proxyType);

		if ( !data.proxyUserPass.empty() ) {
			setOption(CURLOPT_PROXYUSERPWD, data.proxyUserPass.c_str());
		}
	}

	if ( !data.userPass.empty() ) {
		setOption(CURLOPT_USERPWD, data.userPass.c_str());
	}

	// CURLOPT_HTTPHEADER
	{
		for (auto &it_header : data.addHeader) {
			std::ctstring_t value = it_header.first + xT(": ") + it_header.second;

			out_headers = ::curl_slist_append(out_headers, value.c_str());
		}

		setOption(CURLOPT_HTTPHEADER, out_headers);
	}

	if ( !data.referer.empty() ) {
		setOption(CURLOPT_REFERER, data.referer.c_str());
	}

	if ( !data.acceptEncoding.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, data.acceptEncoding.c_str());
	}

	if ( !data.agent.empty() ) {
		setOption(CURLOPT_USERAGENT, data.agent.c_str());
	}

	// curl_easy_setopt(curl, CURLOPT_AUTOREFERER , 1);
	setOption(CURLOPT_FOLLOWLOCATION, static_cast<long_t>(data.isFollowLocation));
	setOption(CURLOPT_MAXREDIRS,      data.maxRedirects);

	// CURLOPT_DEBUG...
	if (data.isDebugHeader) {
		setOption(CURLOPT_VERBOSE,       1L);
		setOption(CURLOPT_DEBUGFUNCTION, onDebug);

		data.debugData.clear();
		setOption(CURLOPT_DEBUGDATA, &data.debugData);
	}
}
//-------------------------------------------------------------------------------------------------
void
CurlBase::getInfos()
{
	xTEST(_handle.isValid());

	{
		char *contentType {};
		info(CURLINFO_CONTENT_TYPE, &contentType);

		data.contentType = (contentType == nullptr ? xT("") : contentType);
	}

	{
		char *effectiveUrl {};
		info(CURLINFO_EFFECTIVE_URL, &effectiveUrl);

		data.effectiveUrl = (effectiveUrl == nullptr ? xT("") : effectiveUrl);
	}

	{
		int responseCode {};
		info(CURLINFO_RESPONSE_CODE, &responseCode);

		data.responseCode = responseCode;
	}

	{
		double totalTimeSec {};
		info(CURLINFO_TOTAL_TIME, &totalTimeSec);

		data.totalTimeSec = totalTimeSec;
	}

	if (data.isDebugHeader) {
		// data.debugData - with data
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, package, curl)
