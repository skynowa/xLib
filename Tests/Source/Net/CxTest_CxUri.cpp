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
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxUri
CxTest_CxUri::~CxTest_CxUri() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxUri::bUnit() {
#if defined(xOS_WIN)
    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret#nose");

        m_sRes  = objUri.sGetUri();
        xASSERT("foo://userinfo@example.com:8042/over/there?name=ferret#nose" == m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT("foo" == m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT("//userinfo@example.com:8042" == m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT("userinfo" == m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT("example.com" == m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT(8042 == m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT("/over/there" == m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT("name=ferret" == m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT("nose" == m_sRes);
    }

    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret");

        m_sRes  = objUri.sGetUri();
        xASSERT("foo://userinfo@example.com:8042/over/there?name=ferret" == m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT("foo" == m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT("//userinfo@example.com:8042" == m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT("userinfo" == m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT("example.com" == m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT(8042 == m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT("/over/there" == m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT("name=ferret" == m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT("" == m_sRes);
    }

    {
        CxUri objUri("foo://userinfo@example.com:8042/over/there");

        m_sRes  = objUri.sGetUri();
        xASSERT("foo://userinfo@example.com:8042/over/there" == m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT("foo" == m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT("//userinfo@example.com:8042" == m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT("userinfo" == m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT("example.com" == m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT(8042 == m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT("/over/there" == m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT("" == m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT("" == m_sRes);
    }

    {
        CxUri objUri("foo://userinfo@example.com:8042");

        m_sRes  = objUri.sGetUri();
        xASSERT("foo://userinfo@example.com:8042" == m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT("foo" == m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT("//userinfo@example.com:8042" == m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT("userinfo" == m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT("example.com" == m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT(8042 == m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT("" == m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT("" == m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT("" == m_sRes);
    }

    {
        CxUri objUri("foo://userinfo@example.com");

        m_sRes  = objUri.sGetUri();
        xASSERT("foo://userinfo@example.com" == m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT("foo" == m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT("//userinfo@example.com" == m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT("userinfo" == m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT("example.com" == m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT(0 == m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT("" == m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT("" == m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT("" == m_sRes);
    }

    {
        CxUri objUri("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c");

        m_sRes  = objUri.sGetUri();
        xASSERT("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c" == m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT("http" == m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT("//weather.yahoo.com" == m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT("" == m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT("weather.yahoo.com" == m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT(80 == m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT("/ukraine/kiev-city-municipality/kiev-924938/" == m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT("unit=c" == m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT("" == m_sRes);
    }

    {
        CxUri objUri("http://dn1.berloga.net/83841/zombie_baseball_2.swf");

        m_sRes  = objUri.sGetUri();
        xASSERT("http://dn1.berloga.net/83841/zombie_baseball_2.swf" == m_sRes);

        m_sRes  = objUri.sGetScheme();
        xASSERT("http" == m_sRes);

        m_sRes  = objUri.sGetAuthority();
        xASSERT("//dn1.berloga.net" == m_sRes);

        m_sRes  = objUri.sGetUserInfo();
        xASSERT("" == m_sRes);

        m_sRes  = objUri.sGetHost();
        xASSERT("dn1.berloga.net" == m_sRes);

        m_usiRes = objUri.usGetPort();
        xASSERT(80 == m_usiRes);

        m_sRes  = objUri.sGetPath();
        xASSERT("/83841/zombie_baseball_2.swf" == m_sRes);

        m_sRes  = objUri.sGetQuery();
        xASSERT("" == m_sRes);

        m_sRes  = objUri.sGetFragment();
        xASSERT("" == m_sRes);
    }


    //-------------------------------------
    //sEncode, sDecode
    {
        const std::string sUri[] = {
            "http://dn1.berloga.net/83841/Ч�ЧњпїЅ_Ч¤ЧђЧ™Ч›Чђ.swf",
            "http://dn1.berloga.net/83841/Ч�ЧњпїЅ Ч¤ЧђЧ™Ч›Чђ.swf",
            "foo://userinfo@example.com:8042/over/there?name=ferret#nose",
            "http://dn1.berloga.net/83841/zombie_baseball_2.swf"
        };

        for (int i = 0; i < xARRAY_SIZE(sUri); i ++) {
            m_sRes = CxUri::sEncodeComponent(sUri[i]);
            m_sRes = CxUri::sDecodeComponent(m_sRes);

            xASSERT(sUri[i] == m_sRes);
        }
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
