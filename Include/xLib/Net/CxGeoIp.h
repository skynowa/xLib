/**
 * \file  CxGeoIp.h
 * \brief GeoIP (http://geolite.maxmind.com/download/geoip/api/c/)
 */


#ifndef xLib_Net_CxGeoIpH
#define xLib_Net_CxGeoIpH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <GeoIP.h>
//---------------------------------------------------------------------------
class CxGeoIp :
    public CxNonCopyable
    /// GeoIP
{
    public:
        enum EOption {
            opStandard    = GEOIP_STANDARD,
            opMemoryCache = GEOIP_MEMORY_CACHE,
            opCheckCache  = GEOIP_CHECK_CACHE,
            opIndexCache  = GEOIP_INDEX_CACHE,
            opMmapCache   = GEOIP_MMAP_CACHE
        };

                      CxGeoIp                  ();
        virtual      ~CxGeoIp                  ();

        BOOL          bOpen                    (const std::tstring &csFilePath, const EOption copOption);
        BOOL          bIsValid                 () const;
        std::tstring       sGetCountryCodeByAddress (const std::tstring &csAddress) const;
        std::tstring       sGetCountryCode3ByAddress(const std::tstring &csAddress) const;
        BOOL          bClose                   ();

    private:
        mutable BOOL  _m_bRes;

        GeoIP        *_m_pgiGeoIp;

};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxGeoIpH
