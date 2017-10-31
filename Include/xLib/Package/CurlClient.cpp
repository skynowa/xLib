/**
 * \file   CurlClient.cpp
 * \brief  CURL client
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "CurlClient.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Test/Test.h>


xNAMESPACE_BEGIN2(xl, Package)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
CurlClient::CurlClient() :
    _handle(xPTR_NULL)
{
    _handle = ::curl_easy_init();
    xTEST_PTR(_handle);
}
//-------------------------------------------------------------------------------------------------
xINLINE
CurlClient::~CurlClient()
{
    (void_t)::curl_easy_cleanup( get() );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::version()
{
    return ::curl_version();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::versionInfo(
    const CURLversion a_version
)
{
    std::tstring_t sRv;

    curl_version_info_data *infoData = ::curl_version_info(a_version);
    xTEST_PTR(infoData);

    Format::str(
        "age: {}\n"
        "version: {}\n"
        "version_num: {}\n"
        "host: {}\n"
        "features: {}\n"
        "ssl_version: {}\n"
        "ssl_version_num: {}\n"
        "libz_version: {}\n"
        "protocols: {}\n"
        "ares: {}\n"
        "ares_num: {}\n"
        "libidn: {}\n"
        "iconv_ver_num: {}\n"
        "libssh_version: {}",
        infoData->age,
        infoData->version,
        infoData->version_num,
        infoData->host,
        infoData->features,
        infoData->ssl_version,
        infoData->ssl_version_num,
        infoData->libz_version,
        infoData->protocols,
        infoData->ares,
        infoData->ares_num,
        infoData->libidn,
        infoData->iconv_ver_num,
        infoData->libssh_version);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
CurlClient::isValid() const
{
    return (_handle != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
CURL *
CurlClient::get()
{
    xTEST_PTR(_handle);

    return _handle;
}
//-------------------------------------------------------------------------------------------------
CURL *
CurlClient::dup()
{
    return ::curl_easy_duphandle( get() );
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::reset()
{
    ::curl_easy_reset( get() );
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::setOption(
    const CURLoption a_option, ...
)
{
    va_list args;
    xVA_START(args, a_option);
    CURLcode iRv = ::curl_easy_setopt(get(), a_option, args);
    xVA_END(args);

    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::perform()
{
    CURLcode iRv = ::curl_easy_perform( get() );
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::pause(
    cint_t a_bitmask
)
{
    CURLcode iRv = ::curl_easy_pause(get(), a_bitmask);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::info(
    const CURLINFO a_info, ...
)
{
    va_list args;
    xVA_START(args, a_info);
    CURLcode iRv = ::curl_easy_getinfo(get(), a_info, args);
    xVA_END(args);

    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::recv(
    void         *a_buffer,
    const size_t  a_buflen,
    size_t       *a_n
)
{
    CURLcode iRv = ::curl_easy_recv(get(), a_buffer, a_buflen, a_n);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::send(
    const void   *a_buffer,
    const size_t  a_buflen,
    size_t       *a_n
)
{
    CURLcode iRv = ::curl_easy_send(get(), a_buffer, a_buflen, a_n);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::escape(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *szRv = ::curl_easy_escape(get(), a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(szRv);

    sRv.assign(szRv);

    if (szRv != xPTR_NULL) {
        ::curl_free(szRv);
        szRv = xPTR_NULL;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::unescape(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    int size_out = 0;
    char *szRv = ::curl_easy_unescape(get(), a_str.c_str(), static_cast<int>( a_str.size() ),
        &size_out);
    xTEST_PTR(szRv);

    sRv.assign(szRv, static_cast<std::size_t>(size_out));

    if (szRv != xPTR_NULL) {
        ::curl_free(szRv);
        szRv = xPTR_NULL;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::strError(
   const CURLcode a_code
)
{
    const char *pszRv = ::curl_easy_strerror(a_code);
    if (pszRv == xPTR_NULL) {
        return Const::strUnknown();
    }

    return pszRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, Package)
