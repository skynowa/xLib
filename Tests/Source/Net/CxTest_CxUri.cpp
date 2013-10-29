/**
 * \file   CxTest_CxUri.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxUri.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxUri::unit(
    culonglong_t &a_cullCaseLoops
)
{
    std::tstring_t m_sRv;

    xTEST_CASE(xT("CxUri::getters"), a_cullCaseLoops)
    {
        CxUri objUri(xT("foo://userinfo@example.com:8042/over/there?name=ferret#nose"));

        m_sRv  = objUri.uri();
        xTEST_EQ(std::tstring_t(xT("foo://userinfo@example.com:8042/over/there?name=ferret#nose")), m_sRv);

        m_sRv  = objUri.scheme();
        xTEST_EQ(std::tstring_t(xT("foo")), m_sRv);

        m_sRv  = objUri.authority();
        xTEST_EQ(std::tstring_t(xT("//userinfo@example.com:8042")), m_sRv);

        m_sRv  = objUri.userInfo();
        xTEST_EQ(std::tstring_t(xT("userinfo")), m_sRv);

        m_sRv  = objUri.host();
        xTEST_EQ(std::tstring_t(xT("example.com")), m_sRv);

        m_usiRv = objUri.port();
        xTEST_EQ((ushort_t)8042u, m_usiRv);

        m_sRv  = objUri.path();
        xTEST_EQ(std::tstring_t(xT("/over/there")), m_sRv);

        m_sRv  = objUri.query();
        xTEST_EQ(std::tstring_t(xT("name=ferret")), m_sRv);

        m_sRv  = objUri.fragment();
        xTEST_EQ(std::tstring_t(xT("nose")), m_sRv);
    }

    xTEST_CASE("CxUri::getters", a_cullCaseLoops)
    {
        CxUri objUri(xT("foo://userinfo@example.com:8042/over/there?name=ferret"));

        m_sRv  = objUri.uri();
        xTEST_EQ(std::tstring_t(xT("foo://userinfo@example.com:8042/over/there?name=ferret")), m_sRv);

        m_sRv  = objUri.scheme();
        xTEST_EQ(std::tstring_t(xT("foo")), m_sRv);

        m_sRv  = objUri.authority();
        xTEST_EQ(std::tstring_t(xT("//userinfo@example.com:8042")), m_sRv);

        m_sRv  = objUri.userInfo();
        xTEST_EQ(std::tstring_t(xT("userinfo")), m_sRv);

        m_sRv  = objUri.host();
        xTEST_EQ(std::tstring_t(xT("example.com")), m_sRv);

        m_usiRv = objUri.port();
        xTEST_EQ((ushort_t)8042u, m_usiRv);

        m_sRv  = objUri.path();
        xTEST_EQ(std::tstring_t(xT("/over/there")), m_sRv);

        m_sRv  = objUri.query();
        xTEST_EQ(std::tstring_t(xT("name=ferret")), m_sRv);

        m_sRv  = objUri.fragment();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    xTEST_CASE("CxUri::getters", a_cullCaseLoops)
    {
        CxUri objUri(xT("foo://userinfo@example.com:8042/over/there"));

        m_sRv  = objUri.uri();
        xTEST_EQ(std::tstring_t(xT("foo://userinfo@example.com:8042/over/there")), m_sRv);

        m_sRv  = objUri.scheme();
        xTEST_EQ(std::tstring_t(xT("foo")), m_sRv);

        m_sRv  = objUri.authority();
        xTEST_EQ(std::tstring_t(xT("//userinfo@example.com:8042")), m_sRv);

        m_sRv  = objUri.userInfo();
        xTEST_EQ(std::tstring_t(xT("userinfo")), m_sRv);

        m_sRv  = objUri.host();
        xTEST_EQ(std::tstring_t(xT("example.com")), m_sRv);

        m_usiRv = objUri.port();
        xTEST_EQ((ushort_t)8042u, m_usiRv);

        m_sRv  = objUri.path();
        xTEST_EQ(std::tstring_t(xT("/over/there")), m_sRv);

        m_sRv  = objUri.query();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv  = objUri.fragment();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    xTEST_CASE("CxUri::getters", a_cullCaseLoops)
    {
        CxUri objUri(xT("foo://userinfo@example.com:8042"));

        m_sRv  = objUri.uri();
        xTEST_EQ(std::tstring_t(xT("foo://userinfo@example.com:8042")), m_sRv);

        m_sRv  = objUri.scheme();
        xTEST_EQ(std::tstring_t(xT("foo")), m_sRv);

        m_sRv  = objUri.authority();
        xTEST_EQ(std::tstring_t(xT("//userinfo@example.com:8042")), m_sRv);

        m_sRv  = objUri.userInfo();
        xTEST_EQ(std::tstring_t(xT("userinfo")), m_sRv);

        m_sRv  = objUri.host();
        xTEST_EQ(std::tstring_t(xT("example.com")), m_sRv);

        m_usiRv = objUri.port();
        xTEST_EQ((ushort_t)8042u, m_usiRv);

        m_sRv  = objUri.path();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv  = objUri.query();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv  = objUri.fragment();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    xTEST_CASE("CxUri::getters", a_cullCaseLoops)
    {
        CxUri objUri(xT("foo://userinfo@example.com"));

        m_sRv  = objUri.uri();
        xTEST_EQ(std::tstring_t(xT("foo://userinfo@example.com")), m_sRv);

        m_sRv  = objUri.scheme();
        xTEST_EQ(std::tstring_t(xT("foo")), m_sRv);

        m_sRv  = objUri.authority();
        xTEST_EQ(std::tstring_t(xT("//userinfo@example.com")), m_sRv);

        m_sRv  = objUri.userInfo();
        xTEST_EQ(std::tstring_t(xT("userinfo")), m_sRv);

        m_sRv  = objUri.host();
        xTEST_EQ(std::tstring_t(xT("example.com")), m_sRv);

        m_usiRv = objUri.port();
        xTEST_EQ((ushort_t)0, m_usiRv);

        m_sRv  = objUri.path();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv  = objUri.query();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv  = objUri.fragment();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    xTEST_CASE("CxUri::getters", a_cullCaseLoops)
    {
        CxUri objUri(xT("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c"));

        m_sRv  = objUri.uri();
        xTEST_EQ(std::tstring_t(xT("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c")), m_sRv);

        m_sRv  = objUri.scheme();
        xTEST_EQ(std::tstring_t(xT("http")), m_sRv);

        m_sRv  = objUri.authority();
        xTEST_EQ(std::tstring_t(xT("//weather.yahoo.com")), m_sRv);

        m_sRv  = objUri.userInfo();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv  = objUri.host();
        xTEST_EQ(std::tstring_t(xT("weather.yahoo.com")), m_sRv);

        m_usiRv = objUri.port();
        xTEST_EQ((ushort_t)80u, m_usiRv);

        m_sRv  = objUri.path();
        xTEST_EQ(std::tstring_t(xT("/ukraine/kiev-city-municipality/kiev-924938/")), m_sRv);

        m_sRv  = objUri.query();
        xTEST_EQ(std::tstring_t(xT("unit=c")), m_sRv);

        m_sRv  = objUri.fragment();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    xTEST_CASE("CxUri::getters", a_cullCaseLoops)
    {
        CxUri objUri(xT("http://dn1.berloga.net/83841/zombie_baseball_2.swf"));

        m_sRv  = objUri.uri();
        xTEST_EQ(std::tstring_t(xT("http://dn1.berloga.net/83841/zombie_baseball_2.swf")), m_sRv);

        m_sRv  = objUri.scheme();
        xTEST_EQ(std::tstring_t(xT("http")), m_sRv);

        m_sRv  = objUri.authority();
        xTEST_EQ(std::tstring_t(xT("//dn1.berloga.net")), m_sRv);

        m_sRv  = objUri.userInfo();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv  = objUri.host();
        xTEST_EQ(std::tstring_t(xT("dn1.berloga.net")), m_sRv);

        m_usiRv = objUri.port();
        xTEST_EQ((ushort_t)80u, m_usiRv);

        m_sRv  = objUri.path();
        xTEST_EQ(std::tstring_t(xT("/83841/zombie_baseball_2.swf")), m_sRv);

        m_sRv  = objUri.query();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);

        m_sRv  = objUri.fragment();
        xTEST_EQ(std::tstring_t(xT("")), m_sRv);
    }

    xTEST_CASE("CxUri::sEncodeComponent CxUri::sDecodeComponent", a_cullCaseLoops)
    {
        std::ctstring_t uri[] = {
            xT("http://dn1.berloga.net/83841/xxxxx.swf"),
            xT("http://dn1.berloga.net/83841/yyyyyy.swf"),
            xT("foo://userinfo@example.com:8042/over/there?name=ferret#nose"),
            xT("http://dn1.berloga.net/83841/zombie_baseball_2.swf")
        };

        for (size_t i = 0; i < xARRAY_SIZE(uri); i ++) {
            m_sRv = CxUri::encodeComponent(uri[i]);
            m_sRv = CxUri::decodeComponent(m_sRv);

            xTEST_EQ(uri[i], m_sRv);
        }
    }
}
//------------------------------------------------------------------------------
