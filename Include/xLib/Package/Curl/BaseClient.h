/**
 * \file  BaseClient.h
 * \brief CURL client
 *
 * https://curl.haxx.se/libcurl/c/example.html
 */


#pragma once


#include <xLib/Package/Curl/Client.h>
#include <xLib/Interface/IData.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xl, package, curl)

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
	std::tstring_t user_agent;
		///<

	bool_t         isFollowLocation {true};
	int_t          maxRedirects {50};
	bool_t         isCacheControl {false}; // Impl for GET requests
		///< false - no cache, force to reset cache

	bool_t         isDebugHeader {true};

	std::tstring_t request;

	struct DebugData :
		public interface::IDataPrint
		/// debug data
	{
		std::tstring_t text;
		std::tstring_t headerIn;
		std::tstring_t headerOut;
		std::tstring_t dataIn;
		std::tstring_t dataOut;
		std::tstring_t sslDataIn;
		std::tstring_t sslDataOut;

	protected:
		void_t print(core::OStream &os) const override;
	};

	DebugData      debugData;

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
class BaseClient :
	public Client
    /// Base client (proxy)
{
protected:
             BaseClient() = default;
    virtual ~BaseClient() = 0;

    void_t   setProtocols(clong_t bitMask);
		///< set allowed protocols
    void_t   setOptionsDefault(DataIn *dataIn, curl_slist *headers, std::tstring_t *buffHeader,
				std::tstring_t *buffData);
        ///< set options in
    void_t   getInfos(DataOut *dataOut);
        ///< get options out

private:
    xNO_COPY_ASSIGN(BaseClient)
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
