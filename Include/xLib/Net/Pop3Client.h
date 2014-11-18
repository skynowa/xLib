/**
 * \file  Pop3Client.h
 * \brief POP3 (RFC 2821)
 */


#pragma once

#include <xLib/Net/SocketInit.h>
#include <xLib/Net/TcpClient.h>
#include <xLib/Net/DnsClient.h>
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class MimeHeader;
class MimeBody;

class Pop3Client
    /// POP3 (RFC 2821)
{
public:
                      Pop3Client();
                     ~Pop3Client();

    void_t            create(std::ctstring_t &user, std::ctstring_t &password,
                          std::ctstring_t &server, ushort_t port);
    void_t            connect();
    void_t            login();

    void_t            stat(std::size_t &sum, std::size_t &size);
    void_t            list(std::vector<std::size_t> &list);
    void_t            listAt(std::size_t &index);
    void_t            noop();
    void_t            rset();
    void_t            top(std::csize_t &num, std::csize_t &lines, std::tstring_t &buff);

    void_t            retriv(std::csize_t &num, std::ctstring_t &rawMimeMessage);
    void_t            retriveRaw(std::csize_t &num, std::ctstring_t &dirPath,
                          std::ctstring_t &fileName);
    void_t            retriveRawAndBackup(std::csize_t &num, std::ctstring_t &dirPath,
                          std::ctstring_t &backupDirPath, std::ctstring_t &fileName);
    void_t            retrieveHeader(std::csize_t &num, MimeHeader &mimeHeader);

    void_t            del(std::csize_t &num);
    void_t            disconnect();

private:
    std::tstring_t    _sRv;
    /////SocketInit _socketInit;
    TcpClient       _socket;
    std::tstring_t    _user;
    std::tstring_t    _password;
    std::tstring_t    _server;
    ushort_t          _port;
    bool_t            _isConnected;

    void_t            _command(std::ctstring_t &command, std::ctstring_t &replyDelimiter,
                          std::tstring_t *reply);
    bool_t            _isError(std::ctstring_t &text) xWARN_UNUSED_RV;
    std::size_t       _mailsSum(std::ctstring_t &serverAnswer) xWARN_UNUSED_RV;
    std::size_t       _mailsSize(std::ctstring_t &serverAnswer) xWARN_UNUSED_RV;

    xNO_COPY_ASSIGN(Pop3Client)
};

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Pop3Client.cpp"
#endif


/*
RFC 1225

USER <SP> name <CRLF>
PASS <SP> secret <CRLF>
STAT <CRLF>
LIST <SP> [msg] <CRLF>
LIST <CRLF>
RETR <SP> msg <CRLF>
DELE <SP> msg <CRLF>
NOOP <CRLF>
LAST <CRLF>
RSET <CRLF>
QUIT <CRLF>
*/
