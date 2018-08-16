/**
 * \file   CurlClient.h
 * \brief  CURL client
 *
 * https://curl.haxx.se/libcurl/c/allfuncs.html
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
		buf = NULL;
		size = 0;
		read_pos = 0;
	}

	void add(char* buffer, size_t buflen)
	{
		buf=(char*)realloc(buf, size + buflen + 1);
		if (buf)
		{
			memcpy(buf + size, buffer, buflen);
			size += buflen;
			buf[size] = 0;
		}
	}

	size_t get(char* buffer, size_t buflen)
	{
		if ( read_pos < size )
		{
			size_t len = ( size - read_pos < buflen ) ? (size - read_pos) : buflen;
			memcpy(buffer, buf + read_pos, len);
			read_pos += len;
			return len;
		}
		else
		{
			return 0;
		}
	}

	int Free()
	{
		if (buf&&size)
		{
			free(buf);
			buf = NULL;
			size = 0;
			return 1;
		}
		return 0;
	}

	char* buf;
	size_t size;
	size_t read_pos;
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
