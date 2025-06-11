/**
 * \file  SmtpClient.cpp
 * \brief SMTP client
 */


#include <xLib/Package/Curl/SmtpClient.h>

#include <xLib/Log/LogStream.h>

//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
SmtpClient::SmtpClient(
	cbool_t          a_isDebug,
	std::ctstring_t &a_url,
	std::ctstring_t &a_caPath,
	std::ctstring_t &a_userName,
	std::ctstring_t &a_password,
	std::ctstring_t &a_from,
	std::ctstring_t &a_to,
	std::ctstring_t &a_cc,
	std::ctstring_t &a_subject,
	std::ctstring_t &a_body
) :
	Client   (a_isDebug),
	_url     {a_url},
	_caPath  {a_caPath},
	_userName{a_userName},
	_password{a_password},
	_from    {a_from},
	_to      {a_to},
	_cc      {a_cc},
	_subject {a_subject},
	_body    {a_body}
{
}
//-------------------------------------------------------------------------------------------------
void_t
SmtpClient::request()
{
#if 0
	LogCout()
		<< xTRACE_VAR(_url)      << "\n"
		<< xTRACE_VAR(_caPath)   << "\n"
		<< xTRACE_VAR(_userName) << "\n"
		<< xTRACE_VAR(_password) << "\n"
		<< xTRACE_VAR(_from)     << "\n"
		<< xTRACE_VAR(_to)       << "\n"
		<< xTRACE_VAR(_cc)       << "\n"
		<< xTRACE_VAR(_subject)  << "\n"
		<< xTRACE_VAR(_body);
#endif

	setOption(CURLOPT_PROTOCOLS, CURLPROTO_SMTP);

   /**
	* This is the URL for your mailserver. Note the use of port 587 here,
	* instead of the normal SMTP port (25). Port 587 is commonly used for
	* secure mail submission (see RFC4403), but you should use whatever
	* matches your server configuration.
	*/
	setOption(CURLOPT_URL, _url.c_str());

   /**
	* In this example, we'll start with a plain text connection, and upgrade
	* to Transport Layer Security (TLS) using the STARTTLS command. Be careful
	* of using CURLUSESSL_TRY here, because if TLS upgrade fails, the transfer
	* will continue anyway - see the security discussion in the libcurl
	* tutorial for more details.
	*/
	setOption(CURLOPT_USE_SSL, static_cast<long_t>(CURLUSESSL_ALL));

   /**
	* If your server doesn't have a valid certificate, then you can disable
	* part of the Transport Layer Security protection by setting the
	* CURLOPT_SSL_VERIFYPEER and CURLOPT_SSL_VERIFYHOST options to 0 (false).
	*   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	*   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	*
	* That is, in general, a bad idea. It is still better than sending your
	* authentication details in plain text though.  Instead, you should get
	* the issuer certificate (or the host certificate if the certificate is
	* self-signed) and add it to the set of certificates that are known to
	* libcurl using CURLOPT_CAINFO and/or CURLOPT_CAPATH. See docs/SSLCERTS
	* for more information.
	*/
	if ( !_caPath.empty() ) {
		setOption(CURLOPT_CAINFO, _caPath.c_str());
	}

   /**
	* Set username and password
	*/
	setOption(CURLOPT_USERNAME, _userName.c_str());
	setOption(CURLOPT_PASSWORD, _password.c_str());

   /**
	* Note that this option isn't strictly required, omitting it will result
	* in libcurl sending the MAIL FROM command with empty sender data. All
	* autoresponses should have an empty reverse-path, and should be directed
	* to the address in the reverse-path which triggered them. Otherwise,
	* they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
	* details.
	*/
	setOption(CURLOPT_MAIL_FROM, _from.c_str());

	// _recipients
	{
	   /**
		* Add two recipients, in this particular case they correspond to the
		* To: and Cc: addressees in the header, but they could be any kind of recipient
		*/

		struct curl_slist *recipients {};

		recipients = ::curl_slist_append(recipients, _to.c_str());
		recipients = ::curl_slist_append(recipients, _cc.c_str());

		// [out]
		_recipients.reset(recipients);
	}

	setOption(CURLOPT_MAIL_RCPT, _recipients.get());
	setOption(CURLOPT_UPLOAD, 1L);

	std::ctstring_t mimeMsg = Format::str(
		"To: {}\r\n"
		"From: {}\r\n"
		"Subject: {}\r\n"
		"\r\n"
		"{}\r\n"
		"\r\n",
		_to,
		_from,
		_subject,
		_body);

	LogCout()
		<< "mimeMsg:\n"
		<< "--------------------------------------------------\n"
		<< mimeMsg
		<< "--------------------------------------------------\n";

	// Upload data
	{
		_readData.buff = mimeMsg;

		setOption(CURLOPT_READDATA,     &_readData);
		setOption(CURLOPT_READFUNCTION,  onReadData);
	}

	perform();

	int_t responseCode {};
	info(CURLINFO_RESPONSE_CODE, &responseCode);
	xTEST(Algos::isInBounds(responseCode, 200, 299));
}
//-------------------------------------------------------------------------------------------------

} // namespace
