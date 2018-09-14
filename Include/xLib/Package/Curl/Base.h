/**
 * \file  CurlBase.h
 * \brief CURL client
 */


#pragma once


#include <xLib/Package/Curl/Client.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xl, package, curl)

struct BaseData
    /// base data
{
	std::string url;
	bool        isUseHeader {true};

		bool        isSslVerifyPeer {true};
	bool        isSslVerifyHost {true};
	long int    sslVersion {CURL_SSLVERSION_DEFAULT};
	std::string sslCert;
	std::string sslCertPass;

	HttpVersion httpVersion {HttpVersion::Default};

	bool        isVerbose {true};

	std::string cookieFile;
	std::string addCookie;

	std::string encodingParam;
	std::string ciphers;

	char        errorStr[1024 + 1] {};

	int         timeoutSec {};
	int         timeoutMs {};
	int         continueTimeoutMs {};

	ProxyType   proxyType {ProxyType::Http};
	std::string proxy;
	std::string proxyUserPass;
	std::string userPass;

	std::map_tstring_t addHeader;

	std::string referer;
	std::string acceptEncoding;
	std::string agent;

	bool        isFollowLocation {true};
	int         maxRedirects {100};

	bool        isDebugHeader {true};

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

		void clear();
	};

	DebugData   debugData;

	// out
	std::string contentType;
	std::string effectiveUrl;
	int         responseCode {};
	double      totalTimeSec {};
};
xTYPEDEF_CONST(BaseData);

class CurlBase :
	public Client
    ///< CURL base
{
protected:
	BaseData &data;

    explicit CurlBase(BaseData &data);
        ///< constructor
    virtual ~CurlBase();
        ///< destructor

    void     setProtocols(clong_t bitMask);
		///< set allowed protocols
    void     setOptionsDefault(curl_slist *headers, Buffer *buffHeader, Buffer *buffData);
        ///< set options in
    void     getInfos();
        ///< get options out

private:
	xNO_DEFAULT_CONSTRUCT(CurlBase)
    xNO_COPY_ASSIGN(CurlBase)
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
