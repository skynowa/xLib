/**
 * \file  CurlBase.cpp
 * \brief CURL client
 */


#include "CurlBase.h"


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
CurlBase::CurlBase(
	CurlBaseData &a_data
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
CurlBase::setOptionsDefault()
{
	xTEST(_handle.isValid());

	setOption(CURLOPT_HEADER, static_cast<long int>(data.isUseHeader));

	//  CURLOPT_SSL...
	{
		setOption(CURLOPT_SSL_VERIFYPEER, data.ssl_verify_peer);
		setOption(CURLOPT_SSL_VERIFYHOST, data.ssl_verify_host);
		setOption(CURLOPT_SSLVERSION,     data.ssl_version);

		if ( !data.ssl_cert.empty() ) {
			setOption(CURLOPT_SSLCERT,       data.ssl_cert.c_str());
			setOption(CURLOPT_SSLCERTPASSWD, data.ssl_cert_pass.c_str());
		}
	}

	setOption(CURLOPT_HTTP_VERSION, data.http_version);

	setOption(CURLOPT_VERBOSE, static_cast<long int>(data.isVerbose));

	// CURLOPT_COOKIE...
	{
		if ( !data.cookie_file.empty() ) {
			setOption(CURLOPT_COOKIESESSION, 0L);
			setOption(CURLOPT_COOKIEFILE,    data.cookie_file.c_str());
			setOption(CURLOPT_COOKIEJAR,     data.cookie_file.c_str());
		}

		if ( !data.add_cookie.empty() ) {
			setOption(CURLOPT_COOKIE, data.add_cookie.c_str());
		}
	}

	if ( !data.encoding_param.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, data.encoding_param.c_str());
	}

	if ( !data.ciphers.empty() ) {
		setOption(CURLOPT_SSL_CIPHER_LIST, data.ciphers.c_str());
	}

	setOption(CURLOPT_ERRORBUFFER, data.error_str);

	// FTP
	{
		curl_slist *quotes {};
		setOption(CURLOPT_QUOTE, quotes);

		curl_slist *postQuotes {};
		setOption(CURLOPT_POSTQUOTE, postQuotes);
	}

	// CURLOPT_TIMEOUT...
	{
		if (data.timeout_ms > 0) {
			if (data.timeout_ms >= 1000) {
				setOption(CURLOPT_TIMEOUT_MS,        0L);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
				setOption(CURLOPT_TIMEOUT,           data.timeout_ms / 1000);
				setOption(CURLOPT_CONNECTTIMEOUT ,   data.timeout_ms / 1000);
			} else {
				setOption(CURLOPT_TIMEOUT,           0L);
				setOption(CURLOPT_CONNECTTIMEOUT,    0L);
				setOption(CURLOPT_TIMEOUT_MS,        data.timeout_ms);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, data.timeout_ms);
			}
		}
		else if (data.timeout_sec > 0) {
			setOption(CURLOPT_TIMEOUT_MS,        0L);
			setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
			setOption(CURLOPT_TIMEOUT,           data.timeout_sec);
			setOption(CURLOPT_CONNECTTIMEOUT,    data.timeout_sec);
		}

		if (data.continue_timeout_ms > 0) {
			setOption(CURLOPT_EXPECT_100_TIMEOUT_MS, data.continue_timeout_ms);
		}
	}

	// CURLOPT_PROXY
	if ( !data.proxy.empty() ) {
		setOption(CURLOPT_PROXY,     data.proxy.c_str());
		setOption(CURLOPT_PROXYTYPE, data.proxy_type);

		if ( !data.proxy_userpass.empty() ) {
			setOption(CURLOPT_PROXYUSERPWD, data.proxy_userpass.c_str());
		}
	}

	if ( !data.userpass.empty() ) {
		setOption(CURLOPT_USERPWD, data.userpass.c_str());
	}

	// CURLOPT_HTTPHEADER
	{
		data.slist = nullptr;

		for (auto &it_header : data.add_header) {
			const std::string value = it_header.first + ": " + it_header.second;

			data.slist = ::curl_slist_append(data.slist, value.c_str());
		}

		setOption(CURLOPT_HTTPHEADER, data.slist);
	}

	if ( !data.referer.empty() ) {
		setOption(CURLOPT_REFERER, data.referer.c_str());
	}

	if ( !data.accept_encoding.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, data.accept_encoding.c_str());
	}

	if ( !data.agent.empty() ) {
		setOption(CURLOPT_USERAGENT, data.agent.c_str());
	}

	// curl_easy_setopt(curl, CURLOPT_AUTOREFERER , 1);
	setOption(CURLOPT_FOLLOWLOCATION, static_cast<long int>(data.isFollowLocation));
	setOption(CURLOPT_MAXREDIRS,      data.max_redirects);

	// CURLOPT_DEBUG...
	{
		data.debug_text.clear();
		data.debug_header_in.clear();
		data.debug_header_in.clear();
		data.debug_header_out.clear();
		data.debug_data_in.clear();
		data.debug_data_out.clear();
		data.debug_ssl_data_in.clear();
		data.debug_ssl_data_out.clear();

		if (data.isDebugHeader) {
			setOption(CURLOPT_VERBOSE,       1L);
			setOption(CURLOPT_DEBUGFUNCTION, onDebug);

			data.debug_data.text.clear();
			data.debug_data.header_in.clear();
			data.debug_data.header_out.clear();
			data.debug_data.data_in.clear();
			data.debug_data.data_out.clear();
			data.debug_data.ssl_data_in.clear();
			data.debug_data.ssl_data_out.clear();

			setOption(CURLOPT_DEBUGDATA, &data.debug_data);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void
CurlBase::getInfos()
{
	xTEST(_handle.isValid());

	{
		char *content_type {};
		info(CURLINFO_CONTENT_TYPE, &content_type);

		data.content_type = (content_type == nullptr ? "" : content_type);
	}

	{
		char *effective_url {};
		info(CURLINFO_EFFECTIVE_URL, &effective_url);

		data.effective_url = (effective_url == nullptr ? "" : effective_url);
	}

	{
		int response_code {};
		info(CURLINFO_RESPONSE_CODE, &response_code);

		data.response_code = response_code;
	}

	{
		double total_time_sec {};
		info(CURLINFO_TOTAL_TIME, &total_time_sec);

		data.total_time_sec = total_time_sec;
	}

	if (data.isDebugHeader) {
		if ( !data.debug_data.text.isEmpty() ) {
			data.debug_text = data.debug_data.text.buffer();
		}
		if ( !data.debug_data.header_in.isEmpty() ) {
			data.debug_header_in = data.debug_data.header_in.buffer();
		}
		if ( !data.debug_data.header_out.isEmpty() ) {
			data.debug_header_out = data.debug_data.header_out.buffer();
		}
		if ( !data.debug_data.data_in.isEmpty() ) {
			data.debug_data_in = data.debug_data.data_in.buffer();
		}
		if ( !data.debug_data.data_out.isEmpty() ) {
			data.debug_data_out = data.debug_data.data_out.buffer();
		}
		if ( !data.debug_data.ssl_data_in.isEmpty() ) {
			data.debug_ssl_data_in = data.debug_data.ssl_data_in.buffer();
		}
		if ( !data.debug_data.ssl_data_out.isEmpty() ) {
			data.debug_ssl_data_out = data.debug_data.ssl_data_out.buffer();
		}

		data.debug_data.text.clear();
		data.debug_data.header_in.clear();
		data.debug_data.header_out.clear();
		data.debug_data.data_in.clear();
		data.debug_data.data_out.clear();
		data.debug_data.ssl_data_in.clear();
		data.debug_data.ssl_data_out.clear();
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
