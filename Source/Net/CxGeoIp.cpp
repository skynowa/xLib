/**
 * \file  CxGeoIp.cpp
 * \brief GeoIP (http://geolite.maxmind.com/download/geoip/api/c/)
 */


#include <xLib/Net/CxGeoIp.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if defined(xOS_WIN)
    #pragma comment(lib, "GeoIP.lib")
#elif defined(xOS_LINUX)
    //-lGeoIP
#endif


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxGeoIp
CxGeoIp::CxGeoIp() :
    _m_bRes    (FALSE),
    _m_pgiGeoIp(NULL)
{

}
//---------------------------------------------------------------------------
//DONE: ~CxGeoIp
/*virtual*/
CxGeoIp::~CxGeoIp() {
    _m_bRes = bClose();
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bOpen ()
BOOL
CxGeoIp::bOpen(
    const std::tstring &csFilePath,
    const EOption  copOption
)
{
    /*DEBUG*/xASSERT_RET(FALSE == bIsValid(),                       FALSE);
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != CxPath::bIsNameValid(csFilePath), FALSE);
    /*DEBUG*/// copOption - n/a

    GeoIP *pgiGeoIP = GeoIP_open(csFilePath.c_str(), copOption);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pgiGeoIP, csFilePath, FALSE);

    _m_pgiGeoIp = pgiGeoIP;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsValid (validating handle)
BOOL
CxGeoIp::bIsValid() const {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( NULL != _m_pgiGeoIp );
}
//---------------------------------------------------------------------------
//DONE: sGetCountryCodeByAddress (get country code by address)
std::tstring
CxGeoIp::sGetCountryCodeByAddress(
    const std::tstring &csAddress
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),        std::tstring());
    /*DEBUG*/xASSERT_RET(false == csAddress.empty(), std::tstring());

    std::tstring sRes;

    sRes = CxMacros::sAsTString( GeoIP_country_code_by_addr(_m_pgiGeoIp, csAddress.c_str()) );
    /*DEBUG*/xASSERT_RET(2 == sRes.size(), std::tstring());

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sGetCountryCodeBy3Address (get country code by address)
std::tstring
CxGeoIp::sGetCountryCode3ByAddress(
    const std::tstring &csAddress
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),        std::tstring());
    /*DEBUG*/xASSERT_RET(false == csAddress.empty(), std::tstring());

    std::tstring sRes;

    sRes = CxMacros::sAsTString( GeoIP_country_code3_by_addr(_m_pgiGeoIp, csAddress.c_str()) );
    /*DEBUG*/xASSERT_RET(3 == sRes.size(), std::tstring());

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bClose (close)
BOOL
CxGeoIp::bClose() {
    /*DEBUG*/// _m_pgiGeoIp - n/a

    if (FALSE != bIsValid()) {
        GeoIP_delete(_m_pgiGeoIp);
        /*DEBUG*/// n/a
    }

    _m_pgiGeoIp = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
