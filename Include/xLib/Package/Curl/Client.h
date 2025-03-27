/**
 * \file   Client.h
 * \brief  CURL client
 *
 * https://curl.se/libcurl/c/CURLOPT_PROTOCOLS.html
 *
 * https://curl.haxx.se/libcurl/c/allfuncs.html
 * https://curl.haxx.se/libcurl/c/example.html
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Interface/IData.h>
#include "Common.h"
#include "Types.h"
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

struct DebugOption :
	public interface_::IDataPrint
	/// debug option
{
	std::tstring_t text;
	std::tstring_t headerIn;
	std::tstring_t headerOut;
	std::tstring_t dataIn;
	std::tstring_t dataOut;
	std::tstring_t sslOptionIn;
	std::tstring_t sslOptionOut;

protected:
	void_t print(core::OStream &os) const final;
};
//-------------------------------------------------------------------------------------------------
class Client
    /// Client
{
public:
///\name Ctors, dtor
///\{
	explicit  Client(cbool_t isDebug);
	virtual  ~Client();

	xNO_DEFAULT_CONSTRUCT(Client);
	xNO_COPY_ASSIGN(Client);
///\}

    // handle
    HandleCurl &   get();
    void_t         reset();

	template<typename T>
	void_t         setOption(cCURLoption option, const T &value);
    void_t         perform();
    void_t         pause(cint_t bitMask);
    template<typename T>
    void_t         info(cCURLINFO info, const T &value);

    void_t         receive(void_t *buff, std::csize_t buffSize, std::size_t *items);
    void_t         send(cvoid_t *buff, std::csize_t buffSize, std::size_t *items);

    std::tstring_t escape(std::ctstring_t &str) const;
    std::tstring_t unescape(std::ctstring_t &str) const;

xPUBLIC_STATIC:
    static std::tstring_t escapeUrl(std::ctstring_t &str);
    static std::tstring_t unescapeUrl(std::ctstring_t &str);

///\name Callbacks
///\{
	static std::size_t onWriteHeader(void_t *buff, std::csize_t size, std::csize_t items,
							void_t *userData);
	static std::size_t onWriteData(void_t *buff, std::csize_t size, std::csize_t items,
							void_t *userData);
	static std::size_t onReadData(void_t *buff, std::csize_t size, std::csize_t items,
							void_t *userData);
///\}

protected:
///\name Types
///\{
	struct ReadData
	{
		std::tstring_t buff;
		std::size_t    bytes;
	};

	struct SlistDeleter
	{
		void_t operator() (curl_slist *out_list) const
		{
			Utils::freeT(out_list, ::curl_slist_free_all, nullptr);
		}
	};
	using slist_unique_ptr_t = std::unique_ptr<curl_slist, SlistDeleter>;
///\}
///
	cbool_t            _isDebug {};
	HandleCurl         _handle;
	ReadData           _readData {};
	slist_unique_ptr_t _headers;

private:
    static std::csize_t _errorBuffSize {CURL_ERROR_SIZE};
    tchar_t             _errorBuff[_errorBuffSize + 1] {};

///\name Callbacks
///\{
	DebugOption _debugData {};

	static CURLcode _onDebugOption(CURL *curl, const curl_infotype type, char *buff,
						std::csize_t size, void_t *userData);
		///< debug option
///\}
};

} // namespace
//-------------------------------------------------------------------------------------------------

#include "Client.inl"

/**
 * \file   Client.h
 * \todo
 *
 * curl_easy
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
 *
 * struct curl_slist *curl_slist_append(struct curl_slist *,  const char *);
 * void_t             curl_slist_free_all(struct curl_slist *);
 */
