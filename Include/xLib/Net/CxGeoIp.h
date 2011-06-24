/****************************************************************************
* Class name:  CxGeoIp
* Description: GeoIP (http://geolite.maxmind.com/download/geoip/api/c/)
* File name:   CxGeoIp.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     24.06.2011
*
*****************************************************************************/


#ifndef xLib_Net_CxGeoIpH
#define xLib_Net_CxGeoIpH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <GeoIP.h>

#if defined(xOS_WIN)
    #pragma comment(lib, "GeoIP.Lib")
#elif defined(xOS_LINUX)
    //-lGeoIP
#endif
//---------------------------------------------------------------------------
class CxGeoIp :
    public CxNonCopyable
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

		BOOL          bOpen                    (const tString &csFilePath, const EOption copOption);
		BOOL          bIsValid                 () const;
		tString       sGetCountryCodeByAddress (const tString &csAddress) const;
		tString       sGetCountryCode3ByAddress(const tString &csAddress) const;
        BOOL          bClose                   ();

    private:
        mutable BOOL  _m_bRes;

		GeoIP        *_m_pgiGeoIp;

};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxGeoIpH
