/**
 * \file   CxTest_CxCookiePv0.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxCookiePv0.h>

#include <xLib/Common/CxString.h>


//---------------------------------------------------------------------------
CxTest_CxCookiePv0::CxTest_CxCookiePv0() {

}
//---------------------------------------------------------------------------
CxTest_CxCookiePv0::~CxTest_CxCookiePv0() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxCookiePv0::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csName      = xT("Name0");
    const std::tstring_t csValue     = xT("Value0");
    const std::tstring_t csDomain    = xT(".domain.com0");
    const std::tstring_t csPath      = xT("/0");
    const std::tstring_t csExpires   = xT("Wed, 13-Jan-2021 22:23:01 GMT");  //Thu, 22 Mar 2012 18:16:13 GMT
    const bool    cbSecure    = true;
    const bool    cbHttpOnly  = true;
    const std::tstring_t csRawCookie = CxString::sFormat(
                                    xT("%s=%s; Domain=%s; Path=%s; Expires=%s; Secure; HttpOnly"),
                                    csName.c_str(), csValue.c_str(), csDomain.c_str(), csPath.c_str(), csExpires.c_str() /*cbSecure = true, cbHttpOnly = true*/
                                );

    xTEST_CASE("CxCookiePv0::CxCookiePv0", cullCaseLoops)
    {
        CxCookiePv0 ckCookiePv0;

        ckCookiePv0.vSetName(csName);

        m_sRv = ckCookiePv0.sName();
        xTEST_EQ(csName, m_sRv);

        ckCookiePv0.vSetValue(csValue);

        m_sRv = ckCookiePv0.sValue();
        xTEST_EQ(csValue, m_sRv);

        ckCookiePv0.vSetDomain(csDomain);

        m_sRv = ckCookiePv0.sDomain();
        xTEST_EQ(csDomain, m_sRv);

        ckCookiePv0.vSetPath(csPath);

        m_sRv = ckCookiePv0.sPath();
        xTEST_EQ(csPath, m_sRv);

        ckCookiePv0.vSetExpires(csExpires);
  
        m_sRv = ckCookiePv0.sExpires();
        xTEST_EQ(csExpires, m_sRv);

        ckCookiePv0.vSetSecure(cbSecure);

        m_bRv = ckCookiePv0.bGetSecure();
        xTEST_EQ(cbSecure, m_bRv);

        ckCookiePv0.vSetHttpOnly(cbHttpOnly);

        m_bRv = ckCookiePv0.bGetHttpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv0.sToString();
        xTEST_EQ(csRawCookie, m_sRv);

        {
            CxCookiePv0 _ckCookiePv0(ckCookiePv0.sToString());
            xTEST_EQ(_ckCookiePv0.sToString(), csRawCookie);
            xTEST_EQ(ckCookiePv0.sToString() , _ckCookiePv0.sToString());
        }

        ckCookiePv0.vClear();
    }

    xTEST_CASE("CxCookiePv1::CxCookiePv0(const std::tstring_t &)", cullCaseLoops)
    {
        CxCookiePv0 ckCookiePv0(csRawCookie);

        m_sRv = ckCookiePv0.sName();
        xTEST_EQ(csName, m_sRv);

        m_sRv = ckCookiePv0.sValue();
        xTEST_EQ(csValue, m_sRv);

        m_sRv = ckCookiePv0.sDomain();
        xTEST_EQ(csDomain, m_sRv);

        m_sRv = ckCookiePv0.sPath();
        xTEST_EQ(csPath, m_sRv);

        m_sRv = ckCookiePv0.sExpires();
        xTEST_EQ(csExpires, m_sRv);

        m_bRv = ckCookiePv0.bGetSecure();
        xTEST_EQ(cbSecure, m_bRv);

        m_bRv = ckCookiePv0.bGetHttpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv0.sToString();
        xTEST_EQ(csRawCookie, m_sRv);

        ckCookiePv0.vClear();
    }
}
//---------------------------------------------------------------------------
