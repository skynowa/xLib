/****************************************************************************
* Class name:  CxTest_CxUri
* Description: test CxUri
* File name:   CxTest_CxUri.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxUri.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxUri
CxTest_CxUri::CxTest_CxUri() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxUri
CxTest_CxUri::~CxTest_CxUri() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxUri::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
    xTEST_BLOCK(cullBlockLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret#nose");

        m_sRes  = objUri.sGetUri();
        xASSERT_EQ(std::string("foo://userinfo@example.com:8042/over/there?name=ferret#nose"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT_EQ(std::string("//userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT_EQ((USHORT)8042u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT_EQ(std::string("/over/there"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT_EQ(std::string("name=ferret"), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT_EQ(std::string("nose"), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret");

        m_sRes  = objUri.sGetUri();
        xASSERT_EQ(std::string("foo://userinfo@example.com:8042/over/there?name=ferret"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT_EQ(std::string("//userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT_EQ((USHORT)8042u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT_EQ(std::string("/over/there"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT_EQ(std::string("name=ferret"), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT_EQ(std::string(), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there");

        m_sRes  = objUri.sGetUri();
        xASSERT_EQ(std::string("foo://userinfo@example.com:8042/over/there"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT_EQ(std::string("//userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT_EQ((USHORT)8042u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT_EQ(std::string("/over/there"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT_EQ(std::string(), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT_EQ(std::string(), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        CxUri objUri("foo://userinfo@example.com:8042");

        m_sRes  = objUri.sGetUri();
        xASSERT_EQ(std::string("foo://userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT_EQ(std::string("//userinfo@example.com:8042"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT_EQ((USHORT)8042u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT_EQ(std::string(), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT_EQ(std::string(), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT_EQ(std::string(), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        CxUri objUri("foo://userinfo@example.com");

        m_sRes  = objUri.sGetUri();
        xASSERT_EQ(std::string("foo://userinfo@example.com"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT_EQ(std::string("foo"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT_EQ(std::string("//userinfo@example.com"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT_EQ(std::string("userinfo"), m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT_EQ(std::string("example.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT_EQ((USHORT)0, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT_EQ(std::string(), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT_EQ(std::string(), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT_EQ(std::string(), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        CxUri objUri("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c");

        m_sRes  = objUri.sGetUri();
        xASSERT_EQ(std::string("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT_EQ(std::string("http"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT_EQ(std::string("//weather.yahoo.com"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT_EQ(std::string(), m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT_EQ(std::string("weather.yahoo.com"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT_EQ((USHORT)80u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT_EQ(std::string("/ukraine/kiev-city-municipality/kiev-924938/"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT_EQ(std::string("unit=c"), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT_EQ(std::string(), m_sRes);
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        CxUri objUri("http://dn1.berloga.net/83841/zombie_baseball_2.swf");

        m_sRes  = objUri.sGetUri();
        xASSERT_EQ(std::string("http://dn1.berloga.net/83841/zombie_baseball_2.swf"), m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT_EQ(std::string("http"), m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT_EQ(std::string("//dn1.berloga.net"), m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT_EQ(std::string(), m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT_EQ(std::string("dn1.berloga.net"), m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT_EQ((USHORT)80u, m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT_EQ(std::string("/83841/zombie_baseball_2.swf"), m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT_EQ(std::string(), m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT_EQ(std::string(), m_sRes);
    }

    //-------------------------------------
    //sEncode, sDecode
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::string sUri[] = {
            "http://dn1.berloga.net/83841/Ч�ЧњпїЅ_Ч¤ЧђЧ™Ч›Чђ.swf",
            "http://dn1.berloga.net/83841/Ч�ЧњпїЅ Ч¤ЧђЧ™Ч›Чђ.swf",
            "foo://userinfo@example.com:8042/over/there?name=ferret#nose",
            "http://dn1.berloga.net/83841/zombie_baseball_2.swf"
        };

        for (size_t i = 0; i < xARRAY_SIZE(sUri); i ++) {
            m_sRes = CxUri::sEncodeComponent(sUri[i]);
            m_sRes = CxUri::sDecodeComponent(m_sRes);

            xASSERT_EQ(sUri[i], m_sRes);
        }
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
