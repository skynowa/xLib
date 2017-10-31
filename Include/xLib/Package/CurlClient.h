/**
 * \file   CurlClient.h
 * \brief  CURL client
 */


#pragma once

#include <xLib/Core/Core.h>
#include <curl/curl.h>
#include <curl/easy.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, Package)

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
    bool_t         isValid() const;
    CURL *         get();
    CURL *         dup();
    void           reset();

    void           setOption(const CURLoption option, ...);
    void           perform();
    void           pause(cint_t bitmask);
    void           info(const CURLINFO info, ...);

    void           recv(void *buffer, const size_t buflen, size_t *n);
    void           send(const void *buffer, const size_t buflen, size_t *n);


    std::tstring_t escape(std::ctstring_t &str);
    std::tstring_t unescape(std::ctstring_t &str);

    /// struct curl_slist *curl_slist_append(struct curl_slist *,  const char *);
    /// void               curl_slist_free_all(struct curl_slist *);

    std::tstring_t strError(const CURLcode code);

private:
    xNO_COPY_ASSIGN(CurlClient)

    CURL    *_handle;
};

xNAMESPACE_END2(xl, Package)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "CurlClient.cpp"
#endif
