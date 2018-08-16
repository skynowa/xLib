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

    /// struct curl_slist *curl_slist_append(struct curl_slist *,  const char *);
    /// void               curl_slist_free_all(struct curl_slist *);

    std::tstring_t strError(const CURLcode code);

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
