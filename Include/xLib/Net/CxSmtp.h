/**
 * \file  CxSmtp.h
 * \brief SMTP (RFC 2821)
 */


#pragma once

#ifndef xLib_CxSmtpH
#define xLib_CxSmtpH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Net/CxTcpClient.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader;
class CxMimeBody;

class CxSmtp
    /// SMTP (RFC 2821)
{
public:
                   CxSmtp();
                  ~CxSmtp();

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
    CxTcpClient    _socket;
    std::tstring_t _user;
    std::tstring_t _password;
    std::tstring_t _server;
    ushort_t       _port;
    bool_t         _isConnected;

    void_t         _command(std::ctstring_t &command, std::ctstring_t &replyDelimiter,
                       std::tstring_t &reply);
    bool_t         _isError(std::ctstring_t &text) xWARN_UNUSED_RV;

    xNO_COPY_ASSIGN(CxSmtp)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxSmtp.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSmtpH


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
