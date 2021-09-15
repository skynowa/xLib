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
	#if 0
		DataIn dataIn;
		dataIn.url     = xT("smtp://smtp.gmail.com:587");
		dataIn.request =
			"The body of the message starts here.\r\n"
			"\r\n"
			"It could be a lot of lines, could be MIME encoded, whatever.\r\n"
			"Check RFC5322.";

		DataOut dataOut;

		SmtpClient smtp;
		m_bRv = smtp.request(dataIn, &dataOut);
		xTEST(m_bRv);
		xTEST(!dataOut.headers.empty());
		xTEST(dataOut.body.empty());

		if (0) {
			Cout()
				<< xTRACE_VAR(dataIn.request)       << std::endl
				<< xT("\n")
				<< xTRACE_VAR(dataOut.contentType)  << std::endl
				<< xTRACE_VAR(dataOut.effectiveUrl) << std::endl
				<< xTRACE_VAR(dataOut.responseCode) << std::endl
				<< xTRACE_VAR(dataOut.totalTimeSec) << std::endl
				<< xT("\n")
				<< xTRACE_VAR(dataOut.headers)      << std::endl
				<< xTRACE_VAR(dataOut.body.size())  << std::endl
				<< xTRACE_VAR(dataOut.body)         << std::endl;
		}
	#else
		std::ctstring_t url      = "smtp://smtp.gmail.com:587";
		std::ctstring_t caPath   = "/etc/ssl/certs/ca-certificates.crt";
		std::ctstring_t userName = "skynowa@gmail.com";
		std::ctstring_t password = "";	// TODO: set password for test
		std::ctstring_t from     = "skynowa@gmail.com";
		std::ctstring_t to       = "skynowa@fabrica.net.ua";
		std::ctstring_t cc       = "skynowa@gmail.com";
		std::ctstring_t subject  = "xlib::curl::SmtpClient";
		std::ctstring_t body     = "Test";

		SmtpClient smpt(url, caPath, userName, password, from, to, cc, subject, body);
		smpt.request();
	#endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
