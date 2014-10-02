/**
 * \file  SmtpClient.h
 * \brief SMTP (RFC 2821)
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Net/TcpClient.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class MimeHeader;
class MimeBody;

class SmtpClient
    /// SMTP (RFC 2821)
{
public:
                   SmtpClient();
                  ~SmtpClient();

    void_t         create(std::ctstring_t &user, std::ctstring_t &password,
                       std::ctstring_t &server, cushort_t &port);
    void_t         connect();
    void_t         login();
    void_t         noop();
    void_t         rset();
    void_t         sendRaw(std::ctstring_t &filePath, std::ctstring_t &from,
                       std::ctstring_t &to);
    void_t         send(std::ctstring_t &text, std::ctstring_t &from, std::ctstring_t &to);
    void_t         disconnect();

private:
    TcpClient    _socket;
    std::tstring_t _user;
    std::tstring_t _password;
    std::tstring_t _server;
    ushort_t       _port;
    bool_t         _isConnected;

    void_t         _command(std::ctstring_t &command, std::ctstring_t &replyDelimiter,
                       std::tstring_t &reply);
    bool_t         _isError(std::ctstring_t &text) xWARN_UNUSED_RV;

    xNO_COPY_ASSIGN(SmtpClient)
};

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "SmtpClient.cpp"
#endif


/*
RFC 821

HELO <SP> <domain> <CRLF>
MAIL <SP> FROM:<reverse-path> <CRLF>
RCPT <SP> TO:<forward-path> <CRLF>
DATA <CRLF>
RSET <CRLF>
SEND <SP> FROM:<reverse-path> <CRLF>
SOML <SP> FROM:<reverse-path> <CRLF>
SAML <SP> FROM:<reverse-path> <CRLF>
VRFY <SP> <std::tstring_t> <CRLF>
EXPN <SP> <std::tstring_t> <CRLF>
HELP [<SP> <std::tstring_t>] <CRLF>
NOOP <CRLF>
QUIT <CRLF>
TURN <CRLF>
*/
