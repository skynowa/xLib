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

        BOOL          bOpen                    (const std::tstring &csFilePath, const EOption copOption);
        	///< open
        BOOL          bIsValid                 () const;
        	///< validating handle
        std::tstring  sGetCountryCodeByAddress (const std::tstring &csAddress) const;
        	///< get country code by address
        std::tstring  sGetCountryCode3ByAddress(const std::tstring &csAddress) const;
        	///< get country code by address
        BOOL          bClose                   ();
        	///< close

    private:
        mutable BOOL  _m_bRes;		///< constructor
        GeoIP        *_m_pgiGeoIp;	///< pointer to GeoIP

};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxGeoIpH
