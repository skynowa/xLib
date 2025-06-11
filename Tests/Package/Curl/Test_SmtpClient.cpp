/**
 * \file  Test_SmtpClient.cpp
 * \brief test SmtpClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl::package::curl;

xTEST_UNIT(Test_SmtpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SmtpClient::unit()
{
	// Local + Github env
	if (true || isGithubCI()) {
		LogCout() << "GithubCI - skip";
		return true;
	}

	xTEST_CASE("request")
	{
		std::map_tstring_t creds;
		cfg(&creds);

		cbool_t         isDebug  = true;
		std::ctstring_t url      = "smtp://smtp.gmail.com:587";
		std::ctstring_t caPath   = "";
		std::ctstring_t userName = creds[xT("EmailUser")];
		std::ctstring_t password = creds[xT("EmailPassword")];
		std::ctstring_t from     = "skynowa@gmail.com";
		std::ctstring_t to       = "skynowa@fabrica.net.ua";
		std::ctstring_t cc       = "skynowa@gmail.com";
		std::ctstring_t subject  = "xlib::curl::SmtpClient";
		std::ctstring_t body     = "Test";

		SmtpClient smpt(isDebug, url, caPath, userName, password, from, to, cc, subject, body);
		smpt.request();
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
