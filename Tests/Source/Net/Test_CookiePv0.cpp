/**
 * \file   Test_CookiePv0.cpp
 * \brief
 */


#include <Test/Net/Test_CookiePv0.h>

#include <xLib/Core/String.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_CookiePv0)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_CookiePv0::unit()
{
    std::ctstring_t csName      = xT("Name0");
    std::ctstring_t csValue     = xT("Value0");
    std::ctstring_t csDomain    = xT(".domain.com0");
    std::ctstring_t csPath      = xT("/0");
    std::ctstring_t csExpires   = xT("Wed, 13-Jan-2021 22:23:01 GMT");  //Thu, 22 Mar 2012 18:16:13 GMT
    cbool_t         cbSecure    = true;
    cbool_t         cbHttpOnly  = true;
    std::ctstring_t csRawCookie = String::format(
                                            xT("%s=%s; Domain=%s; Path=%s; Expires=%s; Secure; HttpOnly"),
                                            csName.c_str(), csValue.c_str(), csDomain.c_str(),
                                            csPath.c_str(), csExpires.c_str() /*cbSecure = true, cbHttpOnly = true*/);

    xTEST_CASE("CookiePv0")
    {
        CookiePv0 ckCookiePv0;

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
            CookiePv0 _ckCookiePv0(ckCookiePv0.toString());
            xTEST_EQ(_ckCookiePv0.toString(), csRawCookie);
            xTEST_EQ(ckCookiePv0.toString() , _ckCookiePv0.toString());
        }

        ckCookiePv0.clear();
    }

    xTEST_CASE("CookiePv0(std::ctstring_t &)")
    {
        CookiePv0 ckCookiePv0(csRawCookie);

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
//-------------------------------------------------------------------------------------------------
