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
        enum EOption
            /// option
        {
            opStandard    = GEOIP_STANDARD,
            opMemoryCache = GEOIP_MEMORY_CACHE,
            opCheckCache  = GEOIP_CHECK_CACHE,
            opIndexCache  = GEOIP_INDEX_CACHE,
            opMmapCache   = GEOIP_MMAP_CACHE
        };

                      CxGeoIp                  ();
            ///< constructor
        virtual      ~CxGeoIp                  ();
            ///< destructor

        BOOL          bOpen                    (const std::string_t &csFilePath, const EOption copOption);
            ///< open
        BOOL          bIsValid                 () const;
            ///< validating handle
        std::string_t  sGetCountryCodeByAddress (const std::string_t &csAddress) const;
            ///< get country code by address
        std::string_t  sGetCountryCode3ByAddress(const std::string_t &csAddress) const;
            ///< get country code by address
        BOOL          bClose                   ();
            ///< close

    private:
        GeoIP        *_m_pgiGeoIp;    ///< pointer to GeoIP
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxGeoIpH
