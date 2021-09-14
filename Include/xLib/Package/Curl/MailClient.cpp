/**
 * \file  MailClient.cpp
 * \brief Mail client
 */


#include "MailClient.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#define FROM_MAIL    "<skynowa@gmail.com>"
#define TO_MAIL      "<skynowa@fabrica.net.ua>"
#define CC_MAIL      "<skynowa@gmail.com>"
#define MAIL_SUBJECT "SMTP example message"
//-------------------------------------------------------------------------------------------------
bool_t
MailClient::request(
	DataIn   &a_dataIn,		///< [in,out]
	DataOut  *out_dataOut	///< [out]
)
{
	xTEST_PTR(out_dataOut);

	out_dataOut->headers.clear();
	out_dataOut->body.clear();

    /* This is the URL for your mailserver. Note the use of port 587 here,
     * instead of the normal SMTP port (25). Port 587 is commonly used for
     * secure mail submission (see RFC4403), but you should use whatever
     * matches your server configuration. */
	if (0) {
		setOption(CURLOPT_URL, "smtp://smtp.gmail.com:587");
	}

    /* In this example, we'll start with a plain text connection, and upgrade
     * to Transport Layer Security (TLS) using the STARTTLS command. Be careful
     * of using CURLUSESSL_TRY here, because if TLS upgrade fails, the transfer
     * will continue anyway - see the security discussion in the libcurl
     * tutorial for more details. */
    setOption(CURLOPT_USE_SSL, static_cast<long_t>(CURLUSESSL_ALL));

    /* If your server doesn't have a valid certificate, then you can disable
     * part of the Transport Layer Security protection by setting the
     * CURLOPT_SSL_VERIFYPEER and CURLOPT_SSL_VERIFYHOST options to 0 (false).
     *   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
     *   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
     * That is, in general, a bad idea. It is still better than sending your
     * authentication details in plain text though.  Instead, you should get
     * the issuer certificate (or the host certificate if the certificate is
     * self-signed) and add it to the set of certificates that are known to
     * libcurl using CURLOPT_CAINFO and/or CURLOPT_CAPATH. See docs/SSLCERTS
     * for more information. */
	if (0) {
		setOption(CURLOPT_CAINFO, "/home/skynowa/.config/kdeconnect/certificate.pem");
	}

    /* Set username and password */
    setOption(CURLOPT_USERNAME, "skynowa@gmail.com");
    setOption(CURLOPT_PASSWORD, "");	// TODO: set password for test

    /* Note that this option isn't strictly required, omitting it will result
     * in libcurl sending the MAIL FROM command with empty sender data. All
     * autoresponses should have an empty reverse-path, and should be directed
     * to the address in the reverse-path which triggered them. Otherwise,
     * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
     * details.
     */
    setOption(CURLOPT_MAIL_FROM, FROM_MAIL);

    // _recipients
	{
	   /**
		* Add two recipients, in this particular case they correspond to the
		* To: and Cc: addressees in the header, but they could be any kind of recipient
		*/

		struct curl_slist *recipients {};

		recipients = ::curl_slist_append(recipients, TO_MAIL);
		recipients = ::curl_slist_append(recipients, CC_MAIL);

		// [out]
		_recipients.reset(recipients);
	}

	setOption(CURLOPT_MAIL_RCPT, _recipients.get());
	setOption(CURLOPT_UPLOAD, 1L);

	std::tstring_t mimeMsg;
	{
		std::ctstring_t headers =
			"To: "      TO_MAIL   + Const::crNl() +
			"From: "    FROM_MAIL + Const::crNl() +
			"Subject: " MAIL_SUBJECT;

		std::ctstring_t &body = a_dataIn.request;

		mimeMsg = headers + Const::crNl() + body + Const::crNl();
	}

	std::tstring_t buffRead(mimeMsg);
	std::tstring_t buffHeaderOut;
	std::tstring_t buffDataOut;
	BaseClient::setOptionsDefault(&a_dataIn, buffRead, &buffHeaderOut, &buffDataOut);

	perform();

	BaseClient::getInfos(out_dataOut);

	// [out]
	out_dataOut->headers = {{"", buffHeaderOut}};
	out_dataOut->body    = buffDataOut;

	return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
