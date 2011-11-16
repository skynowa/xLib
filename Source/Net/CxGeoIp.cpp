/**
 * \file  CxGeoIp.cpp
 * \brief GeoIP (http://geolite.maxmind.com/download/geoip/api/c/)
 */


#include <xLib/Net/CxGeoIp.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if defined(xOS_ENV_WIN)
    #pragma comment(lib, "GeoIP.lib")
#elif defined(xOS_ENV_UNIX)
    //-lGeoIP
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxGeoIp::CxGeoIp() :
    _m_pgiGeoIp(NULL)
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxGeoIp::~CxGeoIp() {
    (void)bClose();
}
//---------------------------------------------------------------------------
BOOL
CxGeoIp::bOpen(
    const std::string_t &csFilePath,
    const EOption       copOption
)
{
    /*DEBUG*/xASSERT_RET(FALSE == bIsValid(),                       FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsNameValid(csFilePath), FALSE);
    /*DEBUG*/// copOption - n/a

    GeoIP *pgiGeoIP = ::GeoIP_open(csFilePath.c_str(), copOption);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pgiGeoIP, csFilePath, FALSE);

    _m_pgiGeoIp = pgiGeoIP;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxGeoIp::bIsValid() const {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( NULL != _m_pgiGeoIp );
}
//---------------------------------------------------------------------------
std::string_t
CxGeoIp::sGetCountryCodeByAddress(
    const std::string_t &csAddress
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),        std::string_t());
    /*DEBUG*/xASSERT_RET(false == csAddress.empty(), std::string_t());

    std::string_t sRes;

    sRes = CxMacros::sAsTString( ::GeoIP_country_code_by_addr(_m_pgiGeoIp, csAddress.c_str()) );
    /*DEBUG*/xASSERT_RET(2 == sRes.size(), std::string_t());

    return sRes;
}
//---------------------------------------------------------------------------
std::string_t
CxGeoIp::sGetCountryCode3ByAddress(
    const std::string_t &csAddress
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),        std::string_t());
    /*DEBUG*/xASSERT_RET(false == csAddress.empty(), std::string_t());

    std::string_t sRes;

    sRes = CxMacros::sAsTString( ::GeoIP_country_code3_by_addr(_m_pgiGeoIp, csAddress.c_str()) );
    /*DEBUG*/xASSERT_RET(3 == sRes.size(), std::string_t());

    return sRes;
}
//---------------------------------------------------------------------------
BOOL
CxGeoIp::bClose() {
    /*DEBUG*/// _m_pgiGeoIp - n/a

    if (FALSE != bIsValid()) {
        (void)::GeoIP_delete(_m_pgiGeoIp);
    }

    _m_pgiGeoIp = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
