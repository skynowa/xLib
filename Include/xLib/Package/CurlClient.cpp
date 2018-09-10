/**
 * \file   CurlClient.cpp
 * \brief  CURL client
 */


#include "CurlClient.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Test/Test.h>


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
CurlClient::CurlClient() :
    _handle()
{
	CURLcode iRv = ::curl_global_init(CURL_GLOBAL_ALL);
	xTEST_EQ(iRv, CURLE_OK);

    _handle = ::curl_easy_init();
    xTEST_EQ(_handle.isValid(), true);
}
//-------------------------------------------------------------------------------------------------
CurlClient::~CurlClient()
{
	(void_t)::curl_global_cleanup();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::version()
{
    return ::curl_version();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::versionInfo(
    const CURLversion a_version
)
{
    std::tstring_t sRv;

    curl_version_info_data *infoData = ::curl_version_info(a_version);
    xTEST_PTR(infoData);

    sRv = Format::str(
        "age: {}\n"
        "version: {}\n"
        "version_num: {}\n"
        "host: {}\n"
        "features: {}\n"
        "ssl_version: {}\n"
        "ssl_version_num: {}\n"
        "libz_version: {}\n"
        "protocols: {}\n"
        "ares: {}\n"
        "ares_num: {}\n"
        "libidn: {}\n"
        "iconv_ver_num: {}\n"
        "libssh_version: {}",
        infoData->age,
        infoData->version,
        infoData->version_num,
        infoData->host,
        infoData->features,
        infoData->ssl_version,
        infoData->ssl_version_num,
        infoData->libz_version,
        infoData->protocols,
        infoData->ares,
        infoData->ares_num,
        infoData->libidn,
        infoData->iconv_ver_num,
        infoData->libssh_version);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
HandleCurl &
CurlClient::get()
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::reset()
{
    (void_t)::curl_easy_reset( _handle.get() );
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::setOption(
    const CURLoption a_option, ...
)
{
    va_list args;
    xVA_START(args, a_option);
    CURLcode iRv = ::curl_easy_setopt(_handle.get(), a_option, args);
    xVA_END(args);

    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::setOptions()
{
#if 1
	long int    _use_header {};

	long int    _ssl_verify_peer {};
	long int    _ssl_verify_host {};
	long int    _ssl_version {};
	std::string _ssl_cert;
	std::string _ssl_cert_pass;

	long int    _http_version {20};

	bool        _verbose {true};

	std::string _cookie_file;
	std::string _add_cookie;

	std::string _encoding_param;
	std::string _ciphers;

	char        _error_str[255] {};

	int         _timeout {};
	int         _timeout_ms {};
	int         _continue_timeout_ms {};

	ProxyType   _proxy_type {};
	std::string _proxy;
	std::string _proxy_userpass;
	std::string _userpass;

	curl_slist *_slist {};
	std::map<std::string, std::string> _add_header;

	std::string _referer;
	std::string _accept_encoding;
	std::string _agent;

	bool        _follow_location {true};
	int         _max_redirects {100};

	bool        _debug_header {true};
	std::string _debug_header_in;
	std::string _debug_header_out;
	std::string _debug_all_data;
	DebugData   _debug_data;
#endif

	CURL *curl = get().get();

	setOption(CURLOPT_HEADER, _use_header);

	//  CURLOPT_SSL...
	{
		setOption(CURLOPT_SSL_VERIFYPEER, _ssl_verify_peer);
		setOption(CURLOPT_SSL_VERIFYHOST, _ssl_verify_host);
		setOption(CURLOPT_SSLVERSION,     _ssl_version);

		if ( !_ssl_cert.empty() ) {
			setOption(CURLOPT_SSLCERT,       _ssl_cert.c_str());
			setOption(CURLOPT_SSLCERTPASSWD, _ssl_cert_pass.c_str());
		}
	}

	// CURLOPT_HTTP_VERSION
	{
		switch (_http_version) {
		case 10:
			setOption(CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
			break;
		case 11:
			setOption(CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
			break;
		case 20:
			setOption(CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
			break;
		default:
			xTEST(false);
			break;
		}
	}

	if (_verbose) {
		setOption(CURLOPT_VERBOSE, 1L);
	}

	// CURLOPT_COOKIE...
	{
		if ( !_cookie_file.empty() ) {
			setOption(CURLOPT_COOKIESESSION, 0L);
			setOption(CURLOPT_COOKIEFILE,    _cookie_file.c_str());
			setOption(CURLOPT_COOKIEJAR,     _cookie_file.c_str());
		}

		if ( !_add_cookie.empty() ) {
			setOption(CURLOPT_COOKIE, _add_cookie.c_str());
		}
	}

	if ( !_encoding_param.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, _encoding_param.c_str());
	}

	if ( !_ciphers.empty() ) {
		setOption(CURLOPT_SSL_CIPHER_LIST, _ciphers.c_str());
	}


	setOption(CURLOPT_ERRORBUFFER, _error_str);

	// FTP
	{
		curl_slist *quotes {};
		setOption(CURLOPT_QUOTE, quotes);

		curl_slist *postQuotes {};
		setOption(CURLOPT_POSTQUOTE, postQuotes);
	}

	// CURLOPT_TIMEOUT...
	{
		if (_timeout_ms > 0) {
			if (_timeout_ms >= 1000) {
				setOption(CURLOPT_TIMEOUT_MS,        0L);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
				setOption(CURLOPT_TIMEOUT,           _timeout_ms / 1000);
				setOption(CURLOPT_CONNECTTIMEOUT ,   _timeout_ms / 1000);
			} else {
				setOption(CURLOPT_TIMEOUT,           0L);
				setOption(CURLOPT_CONNECTTIMEOUT,    0L);
				setOption(CURLOPT_TIMEOUT_MS,        _timeout_ms);
				setOption(CURLOPT_CONNECTTIMEOUT_MS, _timeout_ms);
			}
		}
		else if (_timeout > 0) {
			setOption(CURLOPT_TIMEOUT_MS,        0L);
			setOption(CURLOPT_CONNECTTIMEOUT_MS, 0L);
			setOption(CURLOPT_TIMEOUT,           _timeout);
			setOption(CURLOPT_CONNECTTIMEOUT,    _timeout);
		}

		if (_continue_timeout_ms > 0) {
			setOption(CURLOPT_EXPECT_100_TIMEOUT_MS, _continue_timeout_ms);
		}
	}

	// CURLOPT_PROXY
	if ( !_proxy.empty() ) {
		setOption(CURLOPT_PROXY,     _proxy.c_str());
		setOption(CURLOPT_PROXYTYPE, _proxy_type);

		if ( !_proxy_userpass.empty() ) {
			setOption(CURLOPT_PROXYUSERPWD, _proxy_userpass.c_str());
		}
	}

	if ( !_userpass.empty() ) {
		setOption(CURLOPT_USERPWD, _userpass.c_str());
	}

	// CURLOPT_HTTPHEADER
	{
		_slist = nullptr;

		for (auto &it_header : _add_header) {
			const std::string value = it_header.first + ": " + it_header.second;

			_slist = ::curl_slist_append(_slist, value.c_str());
		}

		setOption(CURLOPT_HTTPHEADER, _slist);
	}

	if ( !_referer.empty() ) {
		setOption(CURLOPT_REFERER, _referer.c_str());
	}

	if ( !_accept_encoding.empty() ) {
		setOption(CURLOPT_ACCEPT_ENCODING, _accept_encoding.c_str());
	}

	if ( !_agent.empty() ) {
		setOption(CURLOPT_USERAGENT, _agent.c_str());
	}

	// curl_easy_setopt(curl, CURLOPT_AUTOREFERER , 1);
	setOption(CURLOPT_FOLLOWLOCATION, _follow_location);
	setOption(CURLOPT_MAXREDIRS,      _max_redirects);

	// CURLOPT_DEBUG...
	{
		_debug_header_in.clear();
		_debug_header_out.clear();
		_debug_all_data.clear();

		if (_debug_header) {
			setOption(CURLOPT_VERBOSE,       1L);
			setOption(CURLOPT_DEBUGFUNCTION, onDebug);

			_debug_data.header_in.free();
			_debug_data.header_out.free();
			_debug_data.all_data.free();

			setOption(CURLOPT_DEBUGDATA, &_debug_data);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::perform()
{
    CURLcode iRv = ::curl_easy_perform( _handle.get() );
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::pause(
    cint_t a_bitMask
)
{
    CURLcode iRv = ::curl_easy_pause(_handle.get(), a_bitMask);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::info(
    const CURLINFO a_info, ...
)
{
    va_list args;
    xVA_START(args, a_info);
    CURLcode iRv = ::curl_easy_getinfo(_handle.get(), a_info, args);
    xVA_END(args);

    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::receive(
    void         *a_buff,
    const size_t  a_buffSize,
    size_t       *a_n
)
{
    CURLcode iRv = ::curl_easy_recv(_handle.get(), a_buff, a_buffSize, a_n);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::send(
    const void   *a_buff,
    const size_t  a_buffSize,
    size_t       *a_n
)
{
    CURLcode iRv = ::curl_easy_send(_handle.get(), a_buff, a_buffSize, a_n);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::escape(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *pszRv = ::curl_easy_escape(_handle.get(), a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    if (pszRv != xPTR_NULL) {
        ::curl_free(pszRv);
        pszRv = xPTR_NULL;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::unescape(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    int size_out = 0;
    char *pszRv = ::curl_easy_unescape(_handle.get(), a_str.c_str(),
        static_cast<int>( a_str.size() ), &size_out);
    xTEST_PTR(pszRv);

    sRv.assign(pszRv, static_cast<std::size_t>(size_out));

    if (pszRv != xPTR_NULL) {
        ::curl_free(pszRv);
        pszRv = xPTR_NULL;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
CurlClient::escapeUrl(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *pszRv = ::curl_escape(a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    if (pszRv != xPTR_NULL) {
        ::curl_free(pszRv);
        pszRv = xPTR_NULL;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
CurlClient::unescapeUrl(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *pszRv = ::curl_unescape(a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    if (pszRv != xPTR_NULL) {
        ::curl_free(pszRv);
        pszRv = xPTR_NULL;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::strError(
   const CURLcode a_code
)
{
    const char *pszRv = ::curl_easy_strerror(a_code);
    if (pszRv == xPTR_NULL) {
        return Const::strUnknown();
    }

    return pszRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
size_t
CurlClient::onWriteHeader(
	void_t *a_buff,
	size_t  a_size,
	size_t  a_items,
	void_t *a_userData
)
{
	const size_t buffSize = a_items * a_size;

	auto *buff = static_cast<CurlBuffer *>(a_userData);
	buff->add(static_cast<char *>(a_buff), buffSize);

	return buffSize;
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
CurlClient::onWriteData(
	void_t *a_buff,
	size_t  a_size,
	size_t  a_items,
	void_t *a_userData
)
{
	const size_t buffSize = a_items * a_size;

	auto *buff = static_cast<CurlBuffer *>(a_userData);
	buff->add(static_cast<char *>(a_buff), buffSize);

	return buffSize;
}
//-------------------------------------------------------------------------------------------------
/* static */
size_t
CurlClient::onReadData(
	void_t *a_buff,			///< [out]
	size_t  a_size,
	size_t  a_items,
	void_t *a_userData
)
{
	const size_t buffSize = a_items * a_size;

	auto *buff = static_cast<CurlBuffer *>(a_userData);

	return buff->get(static_cast<char *>(a_buff), buffSize);
}
//-------------------------------------------------------------------------------------------------
/* static */
int
CurlClient::onDebug(
	CURL          *a_curl,
	curl_infotype  a_type,
	char          *a_buf,
	size_t         a_len,
	void          *a_useData
)
{
	if (a_useData == nullptr) {
		return CURLE_OK;
	}

	auto *data = static_cast<DebugData *>(a_useData);
	if (data == nullptr) {
		return CURLE_OK;
	}

	switch (a_type) {
	case CURLINFO_HEADER_IN:
		data->header_in.add(a_buf, a_len);
		break;
	case CURLINFO_HEADER_OUT:
		data->header_out.add(a_buf, a_len);
		break;
	case CURLINFO_TEXT:
	case CURLINFO_DATA_IN:
	case CURLINFO_DATA_OUT:
	case CURLINFO_END:
		break;
	case CURLINFO_SSL_DATA_IN:
	case CURLINFO_SSL_DATA_OUT:
		return CURLE_OK;
		break;
	default:
		xTEST(false);
		return CURLE_OK;
		break;
	}

	data->all_data.add(a_buf, a_len);

	return CURLE_OK;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
