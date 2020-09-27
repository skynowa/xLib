/**
 * \file   Version.cpp
 * \brief  CURL client
 */


#include "Version.h"


namespace xl::package::curl
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Version::version() const
{
    return ::curl_version();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Version::info(
    cCURLversion a_version
) const
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
std::tstring_t
Version::infoCurrent() const
{
    return info(CURLVERSION_NOW);
}
//-------------------------------------------------------------------------------------------------
void_t
Version::protocols(
	std::vec_tstring_t *a_values	///< [out]
) const
{
	xTEST_PTR(a_values);

	a_values->clear();

    curl_version_info_data *infoData = ::curl_version_info(CURLVERSION_NOW);
    xTEST_PTR(infoData);

    const char *const *const prot = infoData->protocols;

    for (std::size_t i = 0; *(prot + i) != nullptr; ++ i) {
        a_values->push_back(*(prot + i));
    }
}
//-------------------------------------------------------------------------------------------------

} // namespace
