/**
 * \file  MailClient.h
 * \brief Mail client
 *
 * https://github.com/curl/curl/blob/master/docs/examples/smtp-tls.c
 *
 * GMail:
 *
 * https://www.google.com/settings/security/lesssecureapps
 * You should change the “Access for less secure apps” to Enabled
 * (it was enabled, I changed to disabled and than back to enabled).
 * After a while I could send email.
 */


#pragma once

#include <xLib/Package/Curl/BaseClient.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

class MailClient :
    public BaseClient
    /// Mail client
{
public:
///@name ctors, dtor
///@{
			 MailClient(std::ctstring_t &url, std::ctstring_t &caPath, std::ctstring_t &userName,
				std::ctstring_t &password, std::ctstring_t &from, std::ctstring_t &to,
				std::ctstring_t &cc, std::ctstring_t &subject,std::ctstring_t &body);
    virtual ~MailClient() = default;

    xNO_COPY_ASSIGN(MailClient)
///@}

    void_t send();
        ///< send request

private:
    std::ctstring_t _url;
    std::ctstring_t _caPath;
    std::ctstring_t _userName;
    std::ctstring_t _password;
    std::ctstring_t _from;
	std::ctstring_t _to;
	std::ctstring_t _cc;
	std::ctstring_t _subject;
	std::ctstring_t _body;

private:
    slist_unique_ptr_t _recipients;
};

} // namespace
//-------------------------------------------------------------------------------------------------
