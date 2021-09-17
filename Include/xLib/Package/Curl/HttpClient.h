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

struct DataIn :
	public interface::IDataPrint
	/// Incoming data
{
	std::tstring_t url;
	bool_t         isUseHeader {false};	///< headers in body

	bool_t         isSslVerifyPeer {true};
	bool_t         isSslVerifyHost {true};
	long_t         sslVersion {CURL_SSLVERSION_DEFAULT};
	std::tstring_t sslCert;
	std::tstring_t sslCertPass;

	HttpVersion    httpVersion {HttpVersion::Default};

	bool_t         isVerbose {true};

	std::tstring_t cookieFile;
	std::tstring_t addCookie;

	std::tstring_t encodingParam;
	std::tstring_t ciphers;

	tchar_t        errorStr[1024 + 1] {};

	int_t          timeoutSec {};
	int_t          timeoutMs {};
	int_t          continueTimeoutMs {};

	ProxyType      proxyType {ProxyType::Http};
	std::tstring_t proxy;
	std::tstring_t proxyUserPass;
	std::tstring_t userPass;

	std::map_tstring_t addHeaders;

	std::tstring_t referer;
		///<
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

	bool_t         isDebugHeader {true};

	std::tstring_t request;

protected:
	void_t print(core::OStream &os) const override;
};
xUSING_CONST(DataIn);
//-------------------------------------------------------------------------------------------------
struct DataOut :
	public interface::IDataPrint
	/// Outcoming data
{
	std::tstring_t      contentType;
	std::tstring_t      effectiveUrl;
	int_t               responseCode {};
	double_t            totalTimeSec {};

	std::mmap_tstring_t headers;
	std::tstring_t      body;

protected:
	void_t print(core::OStream &os) const override;
};
xUSING_CONST(DataOut);
//-------------------------------------------------------------------------------------------------

class HttpClient :
	public Client
    /// HTTP client
{
public:
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

///@name ctors, dtor
///@{
			 HttpClient() = default;
	virtual ~HttpClient() = default;

	xNO_COPY_ASSIGN(HttpClient)
///@}

    bool_t   request(cRequest type, DataIn &dataIn, DataOut *dataOut);
		///< send request
	HttpCode httpCode(cDataOut &dataOut) const;
		///< get HTTP state code
    bool_t   isSuccess(cDataOut &dataOut) const;
		///< is HTTP state code OK

protected:
    void_t   setOptionsDefault(DataIn *dataIn, std::ctstring_t &buffRead,
				std::tstring_t *buffHeader, std::tstring_t *buffData);
        ///< set options in
    void_t   getInfos(DataOut *dataOut);
        ///< get options out
};

} // namespace
//-------------------------------------------------------------------------------------------------
