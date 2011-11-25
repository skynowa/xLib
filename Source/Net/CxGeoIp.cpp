/**
 * \file  CxGeoIp.cpp
 * \brief GeoIP (http://geolite.maxmind.com/download/geoip/api/c/)
 */


#include <xLib/Net/CxGeoIp.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if xOS_ENV_WIN
    #pragma comment(lib, "GeoIP.lib")
#elif xOS_ENV_UNIX
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
bool
CxGeoIp::bOpen(
    const std::tstring_t &csFilePath,
    const EOption       copOption
)
{
    /*DEBUG*/xASSERT_RET(false == bIsValid(),                       false);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               false);
    /*DEBUG*/xASSERT_RET(false != CxPath::bIsNameValid(csFilePath), false);
    /*DEBUG*/// copOption - n/a

    GeoIP *pgiGeoIP = ::GeoIP_open(csFilePath.c_str(), copOption);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pgiGeoIP, csFilePath, false);

    _m_pgiGeoIp = pgiGeoIP;

    return true;
}
//---------------------------------------------------------------------------
bool
CxGeoIp::bIsValid() const {
    /*DEBUG*/// n/a

    return (NULL != _m_pgiGeoIp);
}
//---------------------------------------------------------------------------
std::tstring_t
CxGeoIp::sGetCountryCodeByAddress(
    const std::tstring_t &csAddress
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        std::tstring_t());
    /*DEBUG*/xASSERT_RET(false == csAddress.empty(), std::tstring_t());

    std::tstring_t sRes;

    sRes = CxMacros::sAsTString( ::GeoIP_country_code_by_addr(_m_pgiGeoIp, csAddress.c_str()) );
    /*DEBUG*/xASSERT_RET(2 == sRes.size(), std::tstring_t());

    return sRes;
}
//---------------------------------------------------------------------------
std::tstring_t
CxGeoIp::sGetCountryCode3ByAddress(
    const std::tstring_t &csAddress
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        std::tstring_t());
    /*DEBUG*/xASSERT_RET(false == csAddress.empty(), std::tstring_t());

    std::tstring_t sRes;

    sRes = CxMacros::sAsTString( ::GeoIP_country_code3_by_addr(_m_pgiGeoIp, csAddress.c_str()) );
    /*DEBUG*/xASSERT_RET(3 == sRes.size(), std::tstring_t());

    return sRes;
}
//---------------------------------------------------------------------------
bool
CxGeoIp::bClose() {
    /*DEBUG*/// _m_pgiGeoIp - n/a

    if (false != bIsValid()) {
        (void)::GeoIP_delete(_m_pgiGeoIp);
    }

    _m_pgiGeoIp = NULL;

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
