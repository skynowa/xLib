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
             MailClient() = default;
    virtual ~MailClient() = default;

    xNO_COPY_ASSIGN(MailClient)
///@}

    bool_t request(DataIn &dataIn, DataOut *dataOut);
        ///< send request

private:
    slist_unique_ptr_t _recipients;
};

} // namespace
//-------------------------------------------------------------------------------------------------
