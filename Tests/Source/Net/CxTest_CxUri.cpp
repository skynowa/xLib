/****************************************************************************
* Class name:  CxTest_CxUri
* Description: test CxUri
* File name:   CxTest_CxUri.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxUri (constructor)
CxTest_CxUri::CxTest_CxUri() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxUri (destructor)
CxTest_CxUri::~CxTest_CxUri() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxUri::bUnit() {
	{
		CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret#nose");

		g_sRes  = objUri.sGetUri();
		xASSERT("foo://userinfo@example.com:8042/over/there?name=ferret#nose" == g_sRes);

		g_sRes  = objUri.sGetScheme();
		xASSERT("foo" == g_sRes);

		g_sRes  = objUri.sGetAuthority();
		xASSERT("//userinfo@example.com:8042" == g_sRes);

		g_sRes  = objUri.sGetUserInfo();
		xASSERT("userinfo" == g_sRes);

		g_sRes  = objUri.sGetHost();
		xASSERT("example.com" == g_sRes);

		g_usRes = objUri.usGetPort();
		xASSERT(8042 == g_usRes);

		g_sRes  = objUri.sGetPath();
		xASSERT("/over/there" == g_sRes);

		g_sRes  = objUri.sGetQuery();
		xASSERT("name=ferret" == g_sRes);

		g_sRes  = objUri.sGetFragment();
		xASSERT("nose" == g_sRes);
	}

	{
		CxUri objUri("foo://userinfo@example.com:8042/over/there?name=ferret");

		g_sRes  = objUri.sGetUri();
		xASSERT("foo://userinfo@example.com:8042/over/there?name=ferret" == g_sRes);

		g_sRes  = objUri.sGetScheme();
		xASSERT("foo" == g_sRes);

		g_sRes  = objUri.sGetAuthority();
		xASSERT("//userinfo@example.com:8042" == g_sRes);

		g_sRes  = objUri.sGetUserInfo();
		xASSERT("userinfo" == g_sRes);

		g_sRes  = objUri.sGetHost();
		xASSERT("example.com" == g_sRes);

		g_usRes = objUri.usGetPort();
		xASSERT(8042 == g_usRes);

		g_sRes  = objUri.sGetPath();
		xASSERT("/over/there" == g_sRes);

		g_sRes  = objUri.sGetQuery();
		xASSERT("name=ferret" == g_sRes);

		g_sRes  = objUri.sGetFragment();
		xASSERT("" == g_sRes);
	}

	{
		CxUri objUri("foo://userinfo@example.com:8042/over/there");

		g_sRes  = objUri.sGetUri();
		xASSERT("foo://userinfo@example.com:8042/over/there" == g_sRes);

		g_sRes  = objUri.sGetScheme();
		xASSERT("foo" == g_sRes);

		g_sRes  = objUri.sGetAuthority();
		xASSERT("//userinfo@example.com:8042" == g_sRes);

		g_sRes  = objUri.sGetUserInfo();
		xASSERT("userinfo" == g_sRes);

		g_sRes  = objUri.sGetHost();
		xASSERT("example.com" == g_sRes);

		g_usRes = objUri.usGetPort();
		xASSERT(8042 == g_usRes);

		g_sRes  = objUri.sGetPath();
		xASSERT("/over/there" == g_sRes);

		g_sRes  = objUri.sGetQuery();
		xASSERT("" == g_sRes);

		g_sRes  = objUri.sGetFragment();
		xASSERT("" == g_sRes);
	}

	{
		CxUri objUri("foo://userinfo@example.com:8042");

		g_sRes  = objUri.sGetUri();
		xASSERT("foo://userinfo@example.com:8042" == g_sRes);

		g_sRes  = objUri.sGetScheme();
		xASSERT("foo" == g_sRes);

		g_sRes  = objUri.sGetAuthority();
		xASSERT("//userinfo@example.com:8042" == g_sRes);

		g_sRes  = objUri.sGetUserInfo();
		xASSERT("userinfo" == g_sRes);

		g_sRes  = objUri.sGetHost();
		xASSERT("example.com" == g_sRes);

		g_usRes = objUri.usGetPort();
		xASSERT(8042 == g_usRes);

		g_sRes  = objUri.sGetPath();
		xASSERT("" == g_sRes);

		g_sRes  = objUri.sGetQuery();
		xASSERT("" == g_sRes);

		g_sRes  = objUri.sGetFragment();
		xASSERT("" == g_sRes);
	}

	{
		CxUri objUri("foo://userinfo@example.com");

		g_sRes  = objUri.sGetUri();
		xASSERT("foo://userinfo@example.com" == g_sRes);

		g_sRes  = objUri.sGetScheme();
		xASSERT("foo" == g_sRes);

		g_sRes  = objUri.sGetAuthority();
		xASSERT("//userinfo@example.com" == g_sRes);

		g_sRes  = objUri.sGetUserInfo();
		xASSERT("userinfo" == g_sRes);

		g_sRes  = objUri.sGetHost();
		xASSERT("example.com" == g_sRes);

		g_usRes = objUri.usGetPort();
		xASSERT(0 == g_usRes);

		g_sRes  = objUri.sGetPath();
		xASSERT("" == g_sRes);

		g_sRes  = objUri.sGetQuery();
		xASSERT("" == g_sRes);

		g_sRes  = objUri.sGetFragment();
		xASSERT("" == g_sRes);
	}

	{
		CxUri objUri("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c");

		g_sRes  = objUri.sGetUri();
		xASSERT("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c" == g_sRes);

		g_sRes  = objUri.sGetScheme();
		xASSERT("http" == g_sRes);

		g_sRes  = objUri.sGetAuthority();
		xASSERT("//weather.yahoo.com" == g_sRes);

		g_sRes  = objUri.sGetUserInfo();
		xASSERT("" == g_sRes);

		g_sRes  = objUri.sGetHost();
		xASSERT("weather.yahoo.com" == g_sRes);

		g_usRes = objUri.usGetPort();
		xASSERT(80 == g_usRes);

		g_sRes  = objUri.sGetPath();
		xASSERT("/ukraine/kiev-city-municipality/kiev-924938/" == g_sRes);

		g_sRes  = objUri.sGetQuery();
		xASSERT("unit=c" == g_sRes);

		g_sRes  = objUri.sGetFragment();
		xASSERT("" == g_sRes);
	}

	{
		CxUri objUri("http://dn1.berloga.net/83841/zombie_baseball_2.swf");

		g_sRes  = objUri.sGetUri();
		xASSERT("http://dn1.berloga.net/83841/zombie_baseball_2.swf" == g_sRes);

		g_sRes  = objUri.sGetScheme();
		xASSERT("http" == g_sRes);

		g_sRes  = objUri.sGetAuthority();
		xASSERT("//dn1.berloga.net" == g_sRes);

		g_sRes  = objUri.sGetUserInfo();
		xASSERT("" == g_sRes);

		g_sRes  = objUri.sGetHost();
		xASSERT("dn1.berloga.net" == g_sRes);

		g_usRes = objUri.usGetPort();
		xASSERT(80 == g_usRes);

		g_sRes  = objUri.sGetPath();
		xASSERT("/83841/zombie_baseball_2.swf" == g_sRes);

		g_sRes  = objUri.sGetQuery();
		xASSERT("" == g_sRes);

		g_sRes  = objUri.sGetFragment();
		xASSERT("" == g_sRes);
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
			g_sRes = CxUri::sEncodeComponent(sUri[i]);
			g_sRes = CxUri::sDecodeComponent(g_sRes);

			xASSERT(sUri[i] == g_sRes);
		}
	}

    return TRUE;
}
//---------------------------------------------------------------------------
