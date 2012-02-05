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
/*virtual*/
bool
CxTest_CxUri::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    std::string m_sRes;

    xTEST_CASE(cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret#nose");

        m_sRes  = objUri.sGetUri();
        xTEST_EQ(std::string("foo://userinfo@example.com:8042/over/there?name=ferret#nose"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xTEST_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xTEST_EQ(std::string("//userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xTEST_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xTEST_EQ((ushort_t)8042u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xTEST_EQ(std::string("/over/there"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xTEST_EQ(std::string("name=ferret"), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xTEST_EQ(std::string("nose"), m_sRes);
    }

    xTEST_CASE(cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret");

        m_sRes  = objUri.sGetUri();
        xTEST_EQ(std::string("foo://userinfo@example.com:8042/over/there?name=ferret"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xTEST_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xTEST_EQ(std::string("//userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xTEST_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xTEST_EQ((ushort_t)8042u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xTEST_EQ(std::string("/over/there"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xTEST_EQ(std::string("name=ferret"), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);
    }

    xTEST_CASE(cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there");

        m_sRes  = objUri.sGetUri();
        xTEST_EQ(std::string("foo://userinfo@example.com:8042/over/there"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xTEST_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xTEST_EQ(std::string("//userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xTEST_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xTEST_EQ((ushort_t)8042u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xTEST_EQ(std::string("/over/there"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);

        m_sRes  = objUri.sGetFragment();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);
    }

    xTEST_CASE(cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042");

        m_sRes  = objUri.sGetUri();
        xTEST_EQ(std::string("foo://userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xTEST_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xTEST_EQ(std::string("//userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xTEST_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xTEST_EQ((ushort_t)8042u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);

        m_sRes  = objUri.sGetQuery();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);

        m_sRes  = objUri.sGetFragment();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);
    }

    xTEST_CASE(cullCaseLoops)
    {
        CxUri objUri("foo://userinfo@example.com");

        m_sRes  = objUri.sGetUri();
        xTEST_EQ(std::string("foo://userinfo@example.com"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xTEST_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xTEST_EQ(std::string("//userinfo@example.com"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xTEST_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xTEST_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xTEST_EQ((ushort_t)0, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);

        m_sRes  = objUri.sGetQuery();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);

        m_sRes  = objUri.sGetFragment();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);
    }

    xTEST_CASE(cullCaseLoops)
    {
        CxUri objUri("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c");

        m_sRes  = objUri.sGetUri();
        xTEST_EQ(std::string("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xTEST_EQ(std::string("http"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xTEST_EQ(std::string("//weather.yahoo.com"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);

        m_sRes  = objUri.sGetHost();
        xTEST_EQ(std::string("weather.yahoo.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xTEST_EQ((ushort_t)80u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xTEST_EQ(std::string("/ukraine/kiev-city-municipality/kiev-924938/"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xTEST_EQ(std::string("unit=c"), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);
    }

    xTEST_CASE(cullCaseLoops)
    {
        CxUri objUri("http://dn1.berloga.net/83841/zombie_baseball_2.swf");

        m_sRes  = objUri.sGetUri();
        xTEST_EQ(std::string("http://dn1.berloga.net/83841/zombie_baseball_2.swf"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xTEST_EQ(std::string("http"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xTEST_EQ(std::string("//dn1.berloga.net"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);

        m_sRes  = objUri.sGetHost();
        xTEST_EQ(std::string("dn1.berloga.net"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xTEST_EQ((ushort_t)80u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xTEST_EQ(std::string("/83841/zombie_baseball_2.swf"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);

        m_sRes  = objUri.sGetFragment();
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);
    }

    //-------------------------------------
    //sEncode, sDecode
    xTEST_CASE(cullCaseLoops)
    {
        const std::string sUri[] = {
			"http://dn1.berloga.net/83841/xxxxx.swf",
            "http://dn1.berloga.net/83841/yyyyyy.swf",
            "foo://userinfo@example.com:8042/over/there?name=ferret#nose",
            "http://dn1.berloga.net/83841/zombie_baseball_2.swf"
        };

        for (size_t i = 0; i < xARRAY_SIZE(sUri); i ++) {
            m_sRes = CxUri::sEncodeComponent(sUri[i]);
            m_sRes = CxUri::sDecodeComponent(m_sRes);

            xTEST_EQ(sUri[i], m_sRes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
