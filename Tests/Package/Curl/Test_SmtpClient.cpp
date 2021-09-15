/**
 * \file  Test_SmtpClient.cpp
 * \brief test SmtpClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl::curl;

xTEST_UNIT(Test_SmtpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SmtpClient::unit()
{
	if ( isGithubCI() ) {
		Cout() << "Skip";
		return true;
	}

	xTEST_CASE("request")
	{
		std::ctstring_t url      = "smtp://smtp.gmail.com:587";
		std::ctstring_t caPath   = "";
		std::ctstring_t userName = "skynowa@gmail.com";
		std::ctstring_t password = "";	// TODO: set password for test
		std::ctstring_t from     = "skynowa@gmail.com";
		std::ctstring_t to       = "skynowa@fabrica.net.ua";
		std::ctstring_t cc       = "skynowa@gmail.com";
		std::ctstring_t subject  = "xlib::curl::SmtpClient";
		std::ctstring_t body     = "Test";

		SmtpClient smpt(url, caPath, userName, password, from, to, cc, subject, body);
		smpt.request();
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
