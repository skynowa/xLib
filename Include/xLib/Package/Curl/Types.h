/**
 * \file  CurlTypes.h
 * \brief CURL client
 */


#pragma once

#include <curl/curl.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

xUSING_CONST(CURLversion);
xUSING_CONST(CURLcode);
xUSING_CONST(CURLoption);
xUSING_CONST(CURLINFO);

enum class HttpVersion
	/// HTTP version
{
	Default = CURL_HTTP_VERSION_NONE,
	v1      = CURL_HTTP_VERSION_1_0,
	v2      = CURL_HTTP_VERSION_2_0,
	v2Tls   = CURL_HTTP_VERSION_2TLS,
	v2Prior = CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE
};
xUSING_CONST(HttpVersion);

enum class ProxyType
	/// Proxy type
{
	Http           = CURLPROXY_HTTP,
	Http10         = CURLPROXY_HTTP_1_0,
	Https          = CURLPROXY_HTTPS,
	Socks4         = CURLPROXY_SOCKS4,
	Socks4A        = CURLPROXY_SOCKS4A,
	Socks5         = CURLPROXY_SOCKS5,
	Socks5Hostname = CURLPROXY_SOCKS5_HOSTNAME
};
xUSING_CONST(ProxyType);

} // namespace
//-------------------------------------------------------------------------------------------------
