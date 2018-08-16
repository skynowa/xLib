/**
 * \file   CurlClient.cpp
 * \brief  CURL client
 */


#include "CurlClient.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Test/Test.h>


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
CurlClient::CurlClient() :
    _handle()
{
	CURLcode iRv = ::curl_global_init(CURL_GLOBAL_ALL);
	xTEST_EQ(iRv, CURLE_OK);

    _handle = ::curl_easy_init();
    xTEST_EQ(_handle.isValid(), true);
}
//-------------------------------------------------------------------------------------------------
CurlClient::~CurlClient()
{
	(void_t)::curl_global_cleanup();
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

    sRv = Format::str(
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
HandleCurl &
CurlClient::get()
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::reset()
{
    (void_t)::curl_easy_reset( _handle.get() );
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::setOption(
    const CURLoption a_option, ...
)
{
    va_list args;
    xVA_START(args, a_option);
    CURLcode iRv = ::curl_easy_setopt(_handle.get(), a_option, args);
    xVA_END(args);

    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::perform()
{
    CURLcode iRv = ::curl_easy_perform( _handle.get() );
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::pause(
    cint_t a_bitMask
)
{
    CURLcode iRv = ::curl_easy_pause(_handle.get(), a_bitMask);
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
    CURLcode iRv = ::curl_easy_getinfo(_handle.get(), a_info, args);
    xVA_END(args);

    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::receive(
    void         *a_buff,
    const size_t  a_buffSize,
    size_t       *a_n
)
{
    CURLcode iRv = ::curl_easy_recv(_handle.get(), a_buff, a_buffSize, a_n);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
void
CurlClient::send(
    const void   *a_buff,
    const size_t  a_buffSize,
    size_t       *a_n
)
{
    CURLcode iRv = ::curl_easy_send(_handle.get(), a_buff, a_buffSize, a_n);
    xTEST_EQ(iRv, CURLE_OK);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
CurlClient::escape(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *pszRv = ::curl_easy_escape(_handle.get(), a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    if (pszRv != xPTR_NULL) {
        ::curl_free(pszRv);
        pszRv = xPTR_NULL;
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
    char *pszRv = ::curl_easy_unescape(_handle.get(), a_str.c_str(),
        static_cast<int>( a_str.size() ), &size_out);
    xTEST_PTR(pszRv);

    sRv.assign(pszRv, static_cast<std::size_t>(size_out));

    if (pszRv != xPTR_NULL) {
        ::curl_free(pszRv);
        pszRv = xPTR_NULL;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
CurlClient::escapeUrl(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *pszRv = ::curl_escape(a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    if (pszRv != xPTR_NULL) {
        ::curl_free(pszRv);
        pszRv = xPTR_NULL;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
CurlClient::unescapeUrl(
    std::ctstring_t &a_str
)
{
    std::tstring_t sRv;

    char *pszRv = ::curl_unescape(a_str.c_str(), static_cast<int>( a_str.size() ));
    xTEST_PTR(pszRv);

    sRv.assign(pszRv);

    if (pszRv != xPTR_NULL) {
        ::curl_free(pszRv);
        pszRv = xPTR_NULL;
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


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
size_t
CurlClient::onWriteHeader(
	void_t *a_buff,
	size_t  a_size,
	size_t  a_items,
	void_t *a_userData
)
{
	const size_t buffSize = a_items * a_size;

	auto *buff = static_cast<CurlBuffer *>(a_userData);
	buff->add(static_cast<char *>(a_buff), buffSize);

	return buffSize;
}
//-------------------------------------------------------------------------------------------------
size_t
CurlClient::onWriteData(
	void_t *a_buff,
	size_t  a_size,
	size_t  a_items,
	void_t *a_userData
)
{
	const size_t buffSize = a_items * a_size;

	auto *buff = static_cast<CurlBuffer *>(a_userData);
	buff->add(static_cast<char *>(a_buff), buffSize);

	return buffSize;
}
//-------------------------------------------------------------------------------------------------
size_t
CurlClient::onReadData(
	void_t *a_buff,
	size_t  a_size,
	size_t  a_items,
	void_t *a_userData
)
{
	const size_t buffSize = a_items * a_size;

	auto *buff = static_cast<CurlBuffer *>(a_userData);

	return buff->get(static_cast<char *>(a_buff), buffSize);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
