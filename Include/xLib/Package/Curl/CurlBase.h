/**
 * \file  CurlBase.h
 * \brief CURL client
 */


#pragma once

#include <xLib/Package/Curl/CurlClient.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

struct CurlBaseData
    /// base data
{
	long int    use_header {};

	long int    ssl_verify_peer {};
	long int    ssl_verify_host {};
	long int    ssl_version {};
	std::string ssl_cert;
	std::string ssl_cert_pass;

	HttpVersion http_version {HttpVersion::Default};

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
	std::string debug_data_all;
	DebugData   debug_data;

	// out
	std::string content_type;
	std::string efective_url;
	int         state {};
	double      total_time_sec {};
};
xTYPEDEF_CONST(CurlBaseData);

class CurlBase :
	public CurlClient
    ///< CURL base
{
protected:
	CurlBaseData &data;

    explicit CurlBase(CurlBaseData &data);
        ///< constructor
    virtual ~CurlBase();
        ///< destructor

    void     setOptionsDefault();
        ///< set options in
    void     getInfos();
        ///< get options out
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
