/**
 * \file  CxPop3.h
 * \brief POP3 (RFC 2821)
 */


#pragma once

#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Net/CxDnsClient.h>
#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader;
class CxMimeBody;

class CxPop3 :
    public CxNonCopyable
    /// POP3 (RFC 2821)
{
public:
                      CxPop3();
                     ~CxPop3();

    void_t            create(std::ctstring_t &user, std::ctstring_t &password,
                          std::ctstring_t &server, ushort_t port);
    void_t            connect();
    void_t            login();

    void_t            stat(ulong_t &sum, ulong_t &size);
    void_t            list(std::vector<ulong_t> &list);
    void_t            listAt(ulong_t &index);
    void_t            noop();
    void_t            rset();
    void_t            top(int_t num, int_t lines, std::tstring_t &buff);

    void_t            retriv(int_t num, std::ctstring_t &rawMimeMessage);
    void_t            retriveRaw(int_t num, std::ctstring_t &dirPath,
                          std::ctstring_t &fileName);
    void_t            retriveRawAndBackup(int_t num, std::ctstring_t &dirPath,
                          std::ctstring_t &backupDirPath, std::ctstring_t &fileName);
    void_t            retrieveHeader(int_t num, CxMimeHeader &mimeHeader);

    void_t            del(int_t num);
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
    ulong_t           _mailsSum(std::ctstring_t &serverAnswer) xWARN_UNUSED_RV;
    ulong_t           _mailsSize(std::ctstring_t &serverAnswer) xWARN_UNUSED_RV;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Net/CxPop3.cpp>
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
