/****************************************************************************
* Class name:  CxTest_CxGeoIp
* Description: test CxGeoIp
* File name:   CxGeoIp.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#include <Test/Net/CxTest_CxGeoIp.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxGeoIp
CxTest_CxGeoIp::CxTest_CxGeoIp() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxGeoIp
CxTest_CxGeoIp::~CxTest_CxGeoIp() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxGeoIp::bUnit() {
    const tString csFilePath = xT("./Tests/Source/_TestData/GeoIP.dat");

    const CxGeoIp::EOption copOption[] = {
        CxGeoIp::opStandard,
        CxGeoIp::opMemoryCache,
        CxGeoIp::opCheckCache,
    #if xTODO
        CxGeoIp::opIndexCache,
        CxGeoIp::opMmapCache
    #endif
    };

    //--------------------------------------------------
    //bOpen
    {
        for (size_t i = 0; i < xARRAY_SIZE(copOption); ++ i) {
            CxGeoIp giGeoIp;

            m_bRes = giGeoIp.bOpen(csFilePath, copOption[i]);
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //bIsValid
    {
        for (size_t i = 0; i < xARRAY_SIZE(copOption); ++ i) {
            CxGeoIp giGeoIp;

            m_bRes = giGeoIp.bIsValid();
            xASSERT_EQUAL(FALSE, m_bRes);

            m_bRes = giGeoIp.bOpen(csFilePath, copOption[i]);
            xASSERT_NOT_EQUAL(FALSE, m_bRes);

            m_bRes = giGeoIp.bIsValid();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //sGetCountryCodeByAddress, sGetCountryCode3ByAddress
    {
        for (size_t i = 0; i < xARRAY_SIZE(copOption); ++ i) {
            const tString sTestData[][3] = {
                {xT("216.236.135.152"), xT("US"), xT("USA") },
                {xT("192.106.51.100"),  xT("IT"), xT("ITA") },
                {xT("147.251.48.1"),    xT("CZ"), xT("CZE") },
                {xT("203.174.65.12"),   xT("JP"), xT("JPN") },
                {xT("212.208.74.140"),  xT("FR"), xT("FRA") },
                {xT("200.219.192.106"), xT("BR"), xT("BRA") },
                {xT("134.102.101.18"),  xT("DE"), xT("DEU") },
                {xT("193.75.148.28"),   xT("BE"), xT("BEL") },
                {xT("194.244.83.2"),    xT("IT"), xT("ITA") },
                {xT("203.15.106.23"),   xT("AU"), xT("AUS") }
            };

            for (size_t a = 0; a < xARRAY_SIZE(sTestData); ++ a) {
                const tString csAddress   = sTestData[a][0];
                const tString csMustCode2 = sTestData[a][1];
                const tString csMustCode3 = sTestData[a][2];

                CxGeoIp giGeoIp;

                m_bRes = giGeoIp.bOpen(csFilePath, copOption[i]);
                xASSERT_NOT_EQUAL(FALSE, m_bRes);

                m_sRes = giGeoIp.sGetCountryCodeByAddress(csAddress);
                xASSERT(csMustCode2 == m_sRes);

                m_sRes = giGeoIp.sGetCountryCode3ByAddress(csAddress);
                xASSERT(csMustCode3 == m_sRes);
            }
        }
    }

    //--------------------------------------------------
    //bClose
    {
        for (size_t i = 0; i < xARRAY_SIZE(copOption); ++ i) {
            CxGeoIp giGeoIp;

            m_bRes = giGeoIp.bOpen(csFilePath, copOption[i]);
            xASSERT_NOT_EQUAL(FALSE, m_bRes);

            m_bRes = giGeoIp.bClose();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
