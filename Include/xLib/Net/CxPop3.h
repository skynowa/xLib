/**
 * \file  CxPop3.h
 * \brief POP3 (RFC 2821)
 */


#pragma once

#ifndef xLib_CxPop3H
#define xLib_CxPop3H
//-------------------------------------------------------------------------------------------------
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Net/CxDnsClient.h>
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, net)

class CxMimeHeader;
class CxMimeBody;

class CxPop3
    /// POP3 (RFC 2821)
{
public:
                      CxPop3();
                     ~CxPop3();

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
    void_t            retrieveHeader(std::csize_t &num, CxMimeHeader &mimeHeader);

    void_t            del(std::csize_t &num);
    void_t            disconnect();

private:
    std::tstring_t    _sRv;
    /////CxSocketInit _socketInit;
    CxTcpClient       _socket;
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

    xNO_COPY_ASSIGN(CxPop3)
};

xNAMESPACE2_END(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "CxPop3.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxPop3H


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
