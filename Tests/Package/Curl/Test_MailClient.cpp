/**
 * \file  Test_MailClient.cpp
 * \brief test MailClient
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl::curl;

xTEST_UNIT(Test_MailClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MailClient::unit()
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

		MailClient mail;
		m_bRv = mail.request(dataIn, &dataOut);
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
		std::ctstring_t caPath   = "/home/skynowa/.config/kdeconnect/certificate.pem";

		std::ctstring_t userName = "<skynowa@gmail.com>";
		std::ctstring_t password = "";	// TODO: set password for test

		std::ctstring_t from     = "<skynowa@gmail.com>";
		std::ctstring_t to       = "<skynowa@fabrica.net.ua>";
		std::ctstring_t cc       = "<skynowa@gmail.com>";
		std::ctstring_t subject  = "SMTP example message";
		std::ctstring_t body     =
			"The body of the message starts here.\r\n"
			"\r\n"
			"It could be a lot of lines, could be MIME encoded, whatever.\r\n"
			"Check RFC5322.";

		MailClient mail(url, caPath, userName, password, from, to, cc, subject, body);
		mail.send();
	#endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
