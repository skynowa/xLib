/**
 * \file   HttpClient.h
 * \brief  HTTP client
 *
 * https://www.tutorialspoint.com/http/http_methods.htm
 */


#pragma once

#include <xLib/Package/Curl/Client.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

struct OptionIn :
	public interface_::IDataPrint
	/// Incoming option
{
	std::tstring_t url;
	bool_t         isUseHeader {false};	///< headers in body

	bool_t         isSslVerifyPeer {true};
	bool_t         isSslVerifyHost {true};
	long_t         sslVersion {CURL_SSLVERSION_DEFAULT};
	std::tstring_t sslCert;
	std::tstring_t sslCertPass;

	HttpVersion    httpVersion {HttpVersion::Default};

	std::tstring_t cookieFile;
	std::tstring_t addCookie;

	std::tstring_t encodingParam;
	std::tstring_t ciphers;

	int_t          timeoutSec {};
	int_t          timeoutMs {};
	int_t          continueTimeoutMs {};

	ProxyType      proxyType {ProxyType::Http};
	std::tstring_t proxy;
	std::tstring_t proxyUserPass;
	std::tstring_t userPass;

	std::map_tstring_t addHeaders;

	std::tstring_t referer;
		///< referer
	std::tstring_t accept;
		///< specify certain media types which are acceptable
	std::tstring_t acceptEncoding;
		///< similar to Accept, but restricts the content-codings that are acceptable
	std::tstring_t acceptLanguage;
		///< similar to Accept, but restricts the set of natural languages that are preferred
	std::tstring_t acceptCharset;
		///< indicate what character sets are acceptable
	std::tstring_t userAgent;
		///<

	bool_t         isFollowLocation {true};
	int_t          maxRedirects {50};
	bool_t         isCacheControl {false}; // Impl for GET requests
		///< false - no cache, force to reset cache

	std::tstring_t request;

protected:
	void_t print(core::OStream &os) const final;
};
xUSING_CONST(OptionIn);
//-------------------------------------------------------------------------------------------------
struct OptionOut :
	public interface_::IDataPrint
	/// Outcoming option
{
	std::tstring_t      contentType;
	std::tstring_t      effectiveUrl;
	int_t               responseCode {};
	double_t            totalTimeSec {};

	std::mmap_tstring_t headers;
	std::tstring_t      body;

protected:
	void_t print(core::OStream &os) const final;
};
xUSING_CONST(OptionOut);
//-------------------------------------------------------------------------------------------------
class HttpClient :
	public Client
    /// HTTP client
{
public:
	enum class HttpCode
		/// HTTP response code
	{
		Unknown     = 0,	///< Unknown
		Info        = 1,	///< 1xx - Transient code, a new one follows
		Success     = 2,	///< 2xx - Things are OK
		Redirection = 3,	///< 3xx - The content is somewhere else
		ClientError = 4,	///< 4xx - Failed because of a client problem
		ServerError = 5		///< 5xx - Failed because of a server problem
	};
	xUSING_CONST(HttpCode);

///\name ctors, dtor
///\{
	explicit HttpClient(cbool_t isDebug);
	virtual ~HttpClient() = default;

	xNO_DEFAULT_CONSTRUCT(HttpClient)
	xNO_COPY_ASSIGN(HttpClient)
///\}

///\name Requests
///\{
    bool_t get(OptionIn &optionIn, OptionOut *optionOut);
    bool_t head(OptionIn &optionIn, OptionOut *optionOut);
    bool_t post(OptionIn &optionIn, OptionOut *optionOut);
    bool_t put(OptionIn &optionIn, OptionOut *optionOut);
    bool_t del(OptionIn &optionIn, OptionOut *optionOut);
    bool_t connect(OptionIn &optionIn, OptionOut *optionOut);
    bool_t options(OptionIn &optionIn, OptionOut *optionOut);
    bool_t trace(OptionIn &optionIn, OptionOut *optionOut);
///\}

///\name HTTP result
///\{
	HttpCode httpCode(cOptionOut &optionOut) const;
	bool_t   isSuccess(cOptionOut &optionOut) const;
///\}

protected:
    void_t setOptionsDefault(OptionIn *optionIn, std::ctstring_t &buffRead,
                std::tstring_t *buffHeader, std::tstring_t *buffData);
        ///< set options in
    void_t getInfos(OptionOut *optionOut);
        ///< get options out

private:
	enum class Request
	{
		Unknown = 0,
		Get     = 1,
		Head    = 2,
		Post    = 3,
		Put     = 4,
		Delete  = 5,
		Connect = 6,
		Options = 7,
		Trace   = 8
	};
	xUSING_CONST(Request);

    bool_t _request(cRequest type, OptionIn &optionIn, OptionOut *optionOut);
		///< send request
};

} // namespace
//-------------------------------------------------------------------------------------------------
