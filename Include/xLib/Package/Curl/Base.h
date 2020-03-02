/**
 * \file  CurlBase.h
 * \brief CURL client
 *
 * https://curl.haxx.se/libcurl/c/example.html
 */


#pragma once


#include <xLib/Package/Curl/Client.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xl, package, curl)

struct DataIn
    /// base data (in)
{
	std::tstring_t url;
	bool_t         isUseHeader {true};

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

	std::map_tstring_t addHeader;

	std::tstring_t referer;
	std::tstring_t acceptEncoding;
	std::tstring_t acceptLanguage;
	std::tstring_t acceptCharset;
	std::tstring_t agent;

	bool_t         isFollowLocation {true};
	int_t          maxRedirects {100};

	bool_t         isDebugHeader {true};

	std::tstring_t request;

	struct DebugData
		/// debug data
	{
		Buffer text;
		Buffer headerIn;
		Buffer headerOut;
		Buffer dataIn;
		Buffer dataOut;
		Buffer sslDataIn;
		Buffer sslDataOut;

		void_t clear();
	};

	DebugData      debugData;
};
xUSING_CONST(DataIn);
//-------------------------------------------------------------------------------------------------
struct DataOut
    /// base data (out)
{
	std::tstring_t      contentType;
	std::tstring_t      effectiveUrl;
	int_t               responseCode {};
	double_t            totalTimeSec {};

	std::mmap_tstring_t headers;
	std::tstring_t      body;
};
xUSING_CONST(DataOut);
//-------------------------------------------------------------------------------------------------
class CurlBase :
	public Client
    ///< CURL base
{
protected:
             CurlBase() = default;
        ///< constructor
    virtual ~CurlBase() = default;
        ///< destructor

    void_t   setProtocols(clong_t bitMask);
		///< set allowed protocols
    void_t   setOptionsDefault(DataIn *dataIn, curl_slist *headers, Buffer *buffHeader,
				Buffer *buffData);
        ///< set options in
    void_t   getInfos(DataOut *dataOut);
        ///< get options out

private:
    xNO_COPY_ASSIGN(CurlBase)
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
