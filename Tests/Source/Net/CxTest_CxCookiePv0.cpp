/**
 * \file   CxTest_CxCookiePv0.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxCookiePv0.h>


//---------------------------------------------------------------------------
CxTest_CxCookiePv0::CxTest_CxCookiePv0() {

}
//---------------------------------------------------------------------------
CxTest_CxCookiePv0::~CxTest_CxCookiePv0() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxCookiePv0::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::tstring csName      = xT("Name0");
    const std::tstring csValue     = xT("Value0");
    const std::tstring csDomain    = xT(".domain.com0");
    const std::tstring csPath      = xT("/0");
    const std::tstring csExpires   = xT("Wed, 13-Jan-2021 22:23:01 GMT");  //Thu, 22 Mar 2012 18:16:13 GMT
    const bool    cbSecure    = true;
    const bool    cbHttpOnly  = true;
    const std::tstring csRawCookie = CxString::sFormat(
                                    xT("%s=%s; Domain=%s; Path=%s; Expires=%s; Secure; HttpOnly"),
                                    csName.c_str(), csValue.c_str(), csDomain.c_str(), csPath.c_str(), csExpires.c_str() /*cbSecure = true, cbHttpOnly = true*/
                                );

    //--------------------------------------------------
    //CxCookiePv0()
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCookiePv0 ckCookiePv0;

        m_bRes = ckCookiePv0.bSetName(csName);
        xTEST_DIFF(false, m_bRes);
        m_sRes = ckCookiePv0.sGetName();
        xTEST_EQ(csName, m_sRes);

        m_bRes = ckCookiePv0.bSetValue(csValue);
        xTEST_DIFF(false, m_bRes);
        m_sRes = ckCookiePv0.sGetValue();
        xTEST_EQ(csValue, m_sRes);

        m_bRes = ckCookiePv0.bSetDomain(csDomain);
        xTEST_DIFF(false, m_bRes);
        m_sRes = ckCookiePv0.sGetDomain();
        xTEST_EQ(csDomain, m_sRes);

        m_bRes = ckCookiePv0.bSetPath(csPath);
        xTEST_DIFF(false, m_bRes);
        m_sRes = ckCookiePv0.sGetPath();
        xTEST_EQ(csPath, m_sRes);

        m_bRes = ckCookiePv0.bSetExpires(csExpires);
        xTEST_DIFF(false, m_bRes);
        m_sRes = ckCookiePv0.sGetExpires();
        xTEST_EQ(csExpires, m_sRes);

        m_bRes = ckCookiePv0.bSetSecure(cbSecure);
        xTEST_DIFF(false, m_bRes);
        m_bRes = ckCookiePv0.bGetSecure();
        xTEST_EQ(cbSecure, m_bRes);

        m_bRes = ckCookiePv0.bSetHttpOnly(cbHttpOnly);
        xTEST_DIFF(false, m_bRes);
        m_bRes = ckCookiePv0.bGetHttpOnly();
        xTEST_EQ(cbHttpOnly, m_bRes);

        m_sRes = ckCookiePv0.sToString();
        xTEST_EQ(csRawCookie, m_sRes);

        {
            CxCookiePv0 _ckCookiePv0(ckCookiePv0.sToString());
            xTEST_EQ(_ckCookiePv0.sToString(), csRawCookie);
            xTEST_EQ(ckCookiePv0.sToString() , _ckCookiePv0.sToString());
        }

        m_bRes = ckCookiePv0.bClear();
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //CxCookiePv0(const std::tstring &)
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCookiePv0 ckCookiePv0(csRawCookie);

        m_sRes = ckCookiePv0.sGetName();
        xTEST_EQ(csName, m_sRes);

        m_sRes = ckCookiePv0.sGetValue();
        xTEST_EQ(csValue, m_sRes);

        m_sRes = ckCookiePv0.sGetDomain();
        xTEST_EQ(csDomain, m_sRes);

        m_sRes = ckCookiePv0.sGetPath();
        xTEST_EQ(csPath, m_sRes);

        m_sRes = ckCookiePv0.sGetExpires();
        xTEST_EQ(csExpires, m_sRes);

        m_bRes = ckCookiePv0.bGetSecure();
        xTEST_EQ(cbSecure, m_bRes);

        m_bRes = ckCookiePv0.bGetHttpOnly();
        xTEST_EQ(cbHttpOnly, m_bRes);

        m_sRes = ckCookiePv0.sToString();
        xTEST_EQ(csRawCookie, m_sRes);

        m_bRes = ckCookiePv0.bClear();
        xTEST_DIFF(false, m_bRes);
    }

    return true;
}
//---------------------------------------------------------------------------
