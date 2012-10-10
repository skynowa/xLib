/**
 * \file   CxTest_CxUri.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxUri.h>


//---------------------------------------------------------------------------
CxTest_CxUri::CxTest_CxUri() {

}
//---------------------------------------------------------------------------
CxTest_CxUri::~CxTest_CxUri() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxUri::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    std::string m_sRv;

    xTEST_CASE(CxUri::getters, cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret#nose");

        m_sRv  = objUri.sUri();
        xTEST_EQ(std::string("foo://userinfo@example.com:8042/over/there?name=ferret#nose"), m_sRv);

        m_sRv  = objUri.sScheme();
        xTEST_EQ(std::string("foo"), m_sRv);

        m_sRv  = objUri.sAuthority();
        xTEST_EQ(std::string("//userinfo@example.com:8042"), m_sRv);

        m_sRv  = objUri.sUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRv);

        m_sRv  = objUri.sHost();
        xTEST_EQ(std::string("example.com"), m_sRv);

        m_usiRv = objUri.usPort();
        xTEST_EQ((ushort_t)8042u, m_usiRv);

        m_sRv  = objUri.sPath();
        xTEST_EQ(std::string("/over/there"), m_sRv);

        m_sRv  = objUri.sQuery();
        xTEST_EQ(std::string("name=ferret"), m_sRv);

        m_sRv  = objUri.sFragment();
        xTEST_EQ(std::string("nose"), m_sRv);
    }

    xTEST_CASE(CxUri::getters, cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret");

        m_sRv  = objUri.sUri();
        xTEST_EQ(std::string("foo://userinfo@example.com:8042/over/there?name=ferret"), m_sRv);

        m_sRv  = objUri.sScheme();
        xTEST_EQ(std::string("foo"), m_sRv);

        m_sRv  = objUri.sAuthority();
        xTEST_EQ(std::string("//userinfo@example.com:8042"), m_sRv);

        m_sRv  = objUri.sUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRv);

        m_sRv  = objUri.sHost();
        xTEST_EQ(std::string("example.com"), m_sRv);

        m_usiRv = objUri.usPort();
        xTEST_EQ((ushort_t)8042u, m_usiRv);

        m_sRv  = objUri.sPath();
        xTEST_EQ(std::string("/over/there"), m_sRv);

        m_sRv  = objUri.sQuery();
        xTEST_EQ(std::string("name=ferret"), m_sRv);

        m_sRv  = objUri.sFragment();
        xTEST_EQ(std::string(""), m_sRv);
    }

    xTEST_CASE(CxUri::getters, cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there");

        m_sRv  = objUri.sUri();
        xTEST_EQ(std::string("foo://userinfo@example.com:8042/over/there"), m_sRv);

        m_sRv  = objUri.sScheme();
        xTEST_EQ(std::string("foo"), m_sRv);

        m_sRv  = objUri.sAuthority();
        xTEST_EQ(std::string("//userinfo@example.com:8042"), m_sRv);

        m_sRv  = objUri.sUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRv);

        m_sRv  = objUri.sHost();
        xTEST_EQ(std::string("example.com"), m_sRv);

        m_usiRv = objUri.usPort();
        xTEST_EQ((ushort_t)8042u, m_usiRv);

        m_sRv  = objUri.sPath();
        xTEST_EQ(std::string("/over/there"), m_sRv);

        m_sRv  = objUri.sQuery();
        xTEST_EQ(std::string(""), m_sRv);

        m_sRv  = objUri.sFragment();
        xTEST_EQ(std::string(""), m_sRv);
    }

    xTEST_CASE(CxUri::getters, cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042");

        m_sRv  = objUri.sUri();
        xTEST_EQ(std::string("foo://userinfo@example.com:8042"), m_sRv);

        m_sRv  = objUri.sScheme();
        xTEST_EQ(std::string("foo"), m_sRv);

        m_sRv  = objUri.sAuthority();
        xTEST_EQ(std::string("//userinfo@example.com:8042"), m_sRv);

        m_sRv  = objUri.sUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRv);

        m_sRv  = objUri.sHost();
        xTEST_EQ(std::string("example.com"), m_sRv);

        m_usiRv = objUri.usPort();
        xTEST_EQ((ushort_t)8042u, m_usiRv);

        m_sRv  = objUri.sPath();
        xTEST_EQ(std::string(""), m_sRv);

        m_sRv  = objUri.sQuery();
        xTEST_EQ(std::string(""), m_sRv);

        m_sRv  = objUri.sFragment();
        xTEST_EQ(std::string(""), m_sRv);
    }

    xTEST_CASE(CxUri::getters, cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com");

        m_sRv  = objUri.sUri();
        xTEST_EQ(std::string("foo://userinfo@example.com"), m_sRv);

        m_sRv  = objUri.sScheme();
        xTEST_EQ(std::string("foo"), m_sRv);

        m_sRv  = objUri.sAuthority();
        xTEST_EQ(std::string("//userinfo@example.com"), m_sRv);

        m_sRv  = objUri.sUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRv);

        m_sRv  = objUri.sHost();
        xTEST_EQ(std::string("example.com"), m_sRv);

        m_usiRv = objUri.usPort();
        xTEST_EQ((ushort_t)0, m_usiRv);

        m_sRv  = objUri.sPath();
        xTEST_EQ(std::string(""), m_sRv);

        m_sRv  = objUri.sQuery();
        xTEST_EQ(std::string(""), m_sRv);

        m_sRv  = objUri.sFragment();
        xTEST_EQ(std::string(""), m_sRv);
    }
     
    xTEST_CASE(CxUri::getters, cullCaseLoops)
    {
        CxUri objUri("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c");

        m_sRv  = objUri.sUri();
        xTEST_EQ(std::string("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c"), m_sRv);

        m_sRv  = objUri.sScheme();
        xTEST_EQ(std::string("http"), m_sRv);

        m_sRv  = objUri.sAuthority();
        xTEST_EQ(std::string("//weather.yahoo.com"), m_sRv);

        m_sRv  = objUri.sUserInfo();
        xTEST_EQ(std::string(""), m_sRv);

        m_sRv  = objUri.sHost();
        xTEST_EQ(std::string("weather.yahoo.com"), m_sRv);

        m_usiRv = objUri.usPort();
        xTEST_EQ((ushort_t)80u, m_usiRv);

        m_sRv  = objUri.sPath();
        xTEST_EQ(std::string("/ukraine/kiev-city-municipality/kiev-924938/"), m_sRv);

        m_sRv  = objUri.sQuery();
        xTEST_EQ(std::string("unit=c"), m_sRv);

        m_sRv  = objUri.sFragment();
        xTEST_EQ(std::string(""), m_sRv);
    }

    xTEST_CASE(CxUri::getters, cullCaseLoops)
    {
        CxUri objUri("http://dn1.berloga.net/83841/zombie_baseball_2.swf");

        m_sRv  = objUri.sUri();
        xTEST_EQ(std::string("http://dn1.berloga.net/83841/zombie_baseball_2.swf"), m_sRv);

        m_sRv  = objUri.sScheme();
        xTEST_EQ(std::string("http"), m_sRv);

        m_sRv  = objUri.sAuthority();
        xTEST_EQ(std::string("//dn1.berloga.net"), m_sRv);

        m_sRv  = objUri.sUserInfo();
        xTEST_EQ(std::string(""), m_sRv);

        m_sRv  = objUri.sHost();
        xTEST_EQ(std::string("dn1.berloga.net"), m_sRv);

        m_usiRv = objUri.usPort();
        xTEST_EQ((ushort_t)80u, m_usiRv);

        m_sRv  = objUri.sPath();
        xTEST_EQ(std::string("/83841/zombie_baseball_2.swf"), m_sRv);

        m_sRv  = objUri.sQuery();
        xTEST_EQ(std::string(""), m_sRv);

        m_sRv  = objUri.sFragment();
        xTEST_EQ(std::string(""), m_sRv);
    }

    xTEST_CASE(CxUri::sEncodeComponent CxUri::sDecodeComponent, cullCaseLoops)
    {
        const std::string sUri[] = {
            "http://dn1.berloga.net/83841/xxxxx.swf",
            "http://dn1.berloga.net/83841/yyyyyy.swf",
            "foo://userinfo@example.com:8042/over/there?name=ferret#nose",
            "http://dn1.berloga.net/83841/zombie_baseball_2.swf"
        };

        for (size_t i = 0; i < xARRAY_SIZE(sUri); i ++) {
            m_sRv = CxUri::sEncodeComponent(sUri[i]);
            m_sRv = CxUri::sDecodeComponent(m_sRv);

            xTEST_EQ(sUri[i], m_sRv);
        }
    }
}
//---------------------------------------------------------------------------
