/**
 * \file  CxPop3.h
 * \brief POP3 (RFC 2821)
 */


#ifndef xLib_Net_CxPop3H
#define xLib_Net_CxPop3H
//------------------------------------------------------------------------------
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Net/CxDnsClient.h>
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader;
class CxMimeBody;

class CxPop3 :
    private CxNonCopyable
    /// POP3 (RFC 2821)
{
public:
                      CxPop3             ();
                     ~CxPop3             ();

    void              create             (const std::tstring_t &csUser, const std::tstring_t &csPass,
                                          const std::tstring_t &csServer, ushort_t usPort);
    void              connect            ();
    void              login              ();

    void              stat               (ulong_t &ulSum, ulong_t &ulSize);
    void              list               (std::vector<ulong_t> &veculList);
    void              listAt             (ulong_t &ulIndex);
    void              noop               ();
    void              rset               ();
    void              top                (int iNum, int iLines, std::tstring_t &sBuff);

    void              retrive            (int iNum, const std::tstring_t &csRawMimeMessage);
    void              retriveRaw         (int iNum, const std::tstring_t &csDirPath, const std::tstring_t &csFileName);
    void              retriveRawAndBackup(int iNum, const std::tstring_t &csDirPath, const std::tstring_t &csBackupDirPath,
                                          const std::tstring_t &csFileName);
    void              retrieveHeader     (int iNum, CxMimeHeader &mhMimeHeader);

    void              del                (int iNum);
    void              disconnect         ();

private:
    std::tstring_t    _m_sRes;
    /////CxSocketInit _m_siInit;
    CxTcpClient       _m_scktSocket;
    std::tstring_t    _m_sUser;
    std::tstring_t    _m_sPass;
    std::tstring_t    _m_sServer;
    ushort_t          _m_usPort;
    bool              _m_bConnected;

    void              _command           (const std::tstring_t &csCmd, const std::tstring_t &csReplyDelimiter,
                                          std::tstring_t *psReply);
    bool              _isError           (const std::tstring_t &csText) xWARN_UNUSED_RESULT;
    ulong_t           _mailsSum          (const std::tstring_t &csServerAnswer) xWARN_UNUSED_RESULT;
    ulong_t           _mailsSize         (const std::tstring_t &csServerAnswer) xWARN_UNUSED_RESULT;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Net_CxPop3H

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
