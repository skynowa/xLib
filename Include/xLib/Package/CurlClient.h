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

struct CurlBuffer
{
	CurlBuffer()
	{
	}

	void add(char *buffer, const size_t buflen)
	{
		_buff = (char *)::realloc(_buff, _size + buflen + 1);
		if (_buff) {
			::memcpy(_buff + _size, buffer, buflen);
			_size += buflen;
			_buff[_size] = 0;
		}
	}

	size_t get(char *buffer, const size_t buflen)
	{
		if (_read_pos < _size) {
			size_t len = ( _size - _read_pos < buflen ) ? (_size - _read_pos) : buflen;
			::memcpy(buffer, _buff + _read_pos, len);
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

	char   *_buff {};
	size_t  _size {};
	size_t  _read_pos {};
};

class CurlClient
    ///< CURL client
{
public:
                   CurlClient();
        ///< constructor
    virtual       ~CurlClient();
        ///< destructor

    std::tstring_t version();
    std::tstring_t versionInfo(const CURLversion version);

    // handle
    HandleCurl &   get();
    void           reset();

    void           setOption(const CURLoption option, ...);
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

private:
    xNO_COPY_ASSIGN(CurlClient)

    HandleCurl     _handle;
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
