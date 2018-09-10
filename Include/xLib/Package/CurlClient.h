/**
 * \file   CurlClient.h
 * \brief  CURL client
 *
 * https://curl.haxx.se/libcurl/c/allfuncs.html
 * https://curl.haxx.se/libcurl/c/example.html
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <curl/curl.h>
#include <curl/easy.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class CurlBuffer
{
public:
	CurlBuffer()
	{
	}

	void add(const char *a_buffer, const size_t a_buflen)
	{
		_buff = (char *)::realloc(_buff, _size + a_buflen + 1);
		if (_buff) {
			::memcpy(_buff + _size, a_buffer, a_buflen);
			_size       += a_buflen;
			_buff[_size] = 0;
		}
	}

	size_t get(char *a_buffer, const size_t a_buflen) const
	{
		if (_read_pos < _size) {
			size_t len = ( _size - _read_pos < a_buflen ) ? (_size - _read_pos) : a_buflen;
			::memcpy(a_buffer, _buff + _read_pos, len);
			_read_pos += len;

			return len;
		}

		return 0;
	}

	int free()
	{
		if (_buff && _size) {
			::free(_buff);
			_buff = nullptr;
			_size = 0;

			return 1;
		}

		return 0;
	}

private:
	char          *_buff {};
	size_t         _size {};
	mutable size_t _read_pos {};

	xNO_COPY_ASSIGN(CurlBuffer);
};
//-------------------------------------------------------------------------------------------------
enum class ProxyType
{
	Http           = CURLPROXY_HTTP,
	Http10         = CURLPROXY_HTTP_1_0,
	Https          = CURLPROXY_HTTPS,
	Socks4         = CURLPROXY_SOCKS4,
	Socks4A        = CURLPROXY_SOCKS4A,
	Socks5         = CURLPROXY_SOCKS5,
	Socks5Hostname = CURLPROXY_SOCKS5_HOSTNAME
};

struct DebugData
{
	CurlBuffer header_in;
	CurlBuffer header_out;
	CurlBuffer all_data;
};
//-------------------------------------------------------------------------------------------------
struct CurlClientData
    /// CURL client data
{
	long int    use_header {};

	long int    ssl_verify_peer {};
	long int    ssl_verify_host {};
	long int    ssl_version {};
	std::string ssl_cert;
	std::string ssl_cert_pass;

	long int    http_version {20};

	bool        verbose {true};

	std::string cookie_file;
	std::string add_cookie;

	std::string encoding_param;
	std::string ciphers;

	char        error_str[255] {};

	int         timeout {};
	int         timeout_ms {};
	int         continue_timeout_ms {};

	ProxyType   proxy_type {};
	std::string proxy;
	std::string proxy_userpass;
	std::string userpass;

	curl_slist *slist {};
	std::map<std::string, std::string> add_header;

	std::string referer;
	std::string accept_encoding;
	std::string agent;

	bool        follow_location {true};
	int         max_redirects {100};

	bool        debug_header {true};
	std::string debug_header_in;
	std::string debug_header_out;
	std::string debug_all_data;
	DebugData   debug_data;
};
xTYPEDEF_CONST(CurlClientData);
//-------------------------------------------------------------------------------------------------
class CurlClient
    ///< CURL client
{
public:
    explicit       CurlClient(CurlClientData &data);
        ///< constructor
    virtual       ~CurlClient();
        ///< destructor

    std::tstring_t version();
    std::tstring_t versionInfo(const CURLversion version);

    // handle
    HandleCurl &   get();
    void           reset();

    void           setOption(const CURLoption option, ...);
    void           setOptionsDefault();
    void           perform();
    void           pause(cint_t bitMask);
    void           info(const CURLINFO info, ...);

    void           receive(void *buff, const size_t buffSize, size_t *n);
    void           send(const void *buff, const size_t buffSize, size_t *n);


    std::tstring_t escape(std::ctstring_t &str);
    std::tstring_t unescape(std::ctstring_t &str);

    static
    std::tstring_t escapeUrl(std::ctstring_t &str);
    static
    std::tstring_t unescapeUrl(std::ctstring_t &str);

    /// struct curl_slist *curl_slist_append(struct curl_slist *,  const char *);
    /// void               curl_slist_free_all(struct curl_slist *);

    std::tstring_t strError(const CURLcode code);

public:
	static
	size_t onWriteHeader(void_t *buff, size_t size, size_t items, void_t *userData);
	static
	size_t onWriteData(void_t *buff, size_t size, size_t items, void_t *userData);
	static
	size_t onReadData(void_t *buff, size_t size, size_t items, void_t *userData);
	static
	int    onDebug(CURL *curl, curl_infotype type, char *buf, size_t len, void *useData);

protected:
	CurlClientData &_data;

private:
    xNO_COPY_ASSIGN(CurlClient)

    HandleCurl _handle;
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------

/**
 * TODO: curl_easy
 *
 * url_easy_cleanup
 * curl_easy_duphandle
 * curl_easy_escape
 * curl_easy_getinfo
 * curl_easy_init
 * curl_easy_pause
 * curl_easy_perform
 * curl_easy_recv
 * curl_easy_reset
 * curl_easy_send
 * curl_easy_setopt
 * curl_easy_strerror
 * curl_easy_unescape
 */
