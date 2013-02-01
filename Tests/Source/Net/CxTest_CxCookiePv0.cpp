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
CxTest_CxCookiePv0::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csName      = xT("Name0");
    const std::tstring_t csValue     = xT("Value0");
    const std::tstring_t csDomain    = xT(".domain.com0");
    const std::tstring_t csPath      = xT("/0");
    const std::tstring_t csExpires   = xT("Wed, 13-Jan-2021 22:23:01 GMT");  //Thu, 22 Mar 2012 18:16:13 GMT
    const bool           cbSecure    = true;
    const bool           cbHttpOnly  = true;
    const std::tstring_t csRawCookie = CxString::format(
                                            xT("%s=%s; Domain=%s; Path=%s; Expires=%s; Secure; HttpOnly"),
                                            csName.c_str(), csValue.c_str(), csDomain.c_str(), 
                                            csPath.c_str(), csExpires.c_str() /*cbSecure = true, cbHttpOnly = true*/);

    xTEST_CASE("CxCookiePv0::CxCookiePv0", cullCaseLoops)
    {
        CxCookiePv0 ckCookiePv0;

        ckCookiePv0.setName(csName);

        m_sRv = ckCookiePv0.name();
        xTEST_EQ(csName, m_sRv);

        ckCookiePv0.setValue(csValue);

        m_sRv = ckCookiePv0.value();
        xTEST_EQ(csValue, m_sRv);

        ckCookiePv0.setDomain(csDomain);

        m_sRv = ckCookiePv0.domain();
        xTEST_EQ(csDomain, m_sRv);

        ckCookiePv0.setPath(csPath);

        m_sRv = ckCookiePv0.path();
        xTEST_EQ(csPath, m_sRv);

        ckCookiePv0.setExpires(csExpires);
  
        m_sRv = ckCookiePv0.expires();
        xTEST_EQ(csExpires, m_sRv);

        ckCookiePv0.setSecure(cbSecure);

        m_bRv = ckCookiePv0.secure();
        xTEST_EQ(cbSecure, m_bRv);

        ckCookiePv0.setHttpOnly(cbHttpOnly);

        m_bRv = ckCookiePv0.httpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv0.toString();
        xTEST_EQ(csRawCookie, m_sRv);

        {
            CxCookiePv0 _ckCookiePv0(ckCookiePv0.toString());
            xTEST_EQ(_ckCookiePv0.toString(), csRawCookie);
            xTEST_EQ(ckCookiePv0.toString() , _ckCookiePv0.toString());
        }

        ckCookiePv0.clear();
    }

    xTEST_CASE("CxCookiePv1::CxCookiePv0(const std::tstring_t &)", cullCaseLoops)
    {
        CxCookiePv0 ckCookiePv0(csRawCookie);

        m_sRv = ckCookiePv0.name();
        xTEST_EQ(csName, m_sRv);

        m_sRv = ckCookiePv0.value();
        xTEST_EQ(csValue, m_sRv);

        m_sRv = ckCookiePv0.domain();
        xTEST_EQ(csDomain, m_sRv);

        m_sRv = ckCookiePv0.path();
        xTEST_EQ(csPath, m_sRv);

        m_sRv = ckCookiePv0.expires();
        xTEST_EQ(csExpires, m_sRv);

        m_bRv = ckCookiePv0.secure();
        xTEST_EQ(cbSecure, m_bRv);

        m_bRv = ckCookiePv0.httpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv0.toString();
        xTEST_EQ(csRawCookie, m_sRv);

        ckCookiePv0.clear();
    }
}
//---------------------------------------------------------------------------
