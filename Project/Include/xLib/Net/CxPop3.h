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
    private CxNonCopyable
    /// POP3 (RFC 2821)
{
public:
                      CxPop3();
                     ~CxPop3();

    void_t            create(std::ctstring_t &csUser, std::ctstring_t &csPass,
                          std::ctstring_t &csServer, ushort_t usPort);
    void_t            connect();
    void_t            login();

    void_t            stat(ulong_t &ulSum, ulong_t &ulSize);
    void_t            list(std::vector<ulong_t> &veculList);
    void_t            listAt(ulong_t &ulIndex);
    void_t            noop();
    void_t            rset();
    void_t            top(int_t iNum, int_t iLines, std::tstring_t &sBuff);

    void_t            retriv(int_t iNum, std::ctstring_t &csRawMimeMessage);
    void_t            retriveRaw(int_t iNum, std::ctstring_t &csDirPath,
                          std::ctstring_t &csFileName);
    void_t            retriveRawAndBackup(int_t iNum, std::ctstring_t &csDirPath,
                          std::ctstring_t &csBackupDirPath, std::ctstring_t &csFileName);
    void_t            retrieveHeader(int_t iNum, CxMimeHeader &mhMimeHeader);

    void_t            del(int_t iNum);
    void_t            disconnect();

private:
    std::tstring_t    _m_sRes;
    /////CxSocketInit _m_siInit;
    CxTcpClient       _m_scktSocket;
    std::tstring_t    _m_sUser;
    std::tstring_t    _m_sPass;
    std::tstring_t    _m_sServer;
    ushort_t          _m_usPort;
    bool_t            _m_bConnected;

    void_t            _command(std::ctstring_t &csCmd, std::ctstring_t &csReplyDelimiter,
                          std::tstring_t *psReply);
    bool_t            _isError(std::ctstring_t &csText) xWARN_UNUSED_RV;
    ulong_t           _mailsSum(std::ctstring_t &csServerAnswer) xWARN_UNUSED_RV;
    ulong_t           _mailsSize(std::ctstring_t &csServerAnswer) xWARN_UNUSED_RV;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------


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
