/**
 * \file  CxPop3.h
 * \brief POP3 (RFC 2821)
 */


#ifndef xLib_Net_CxPop3H
#define xLib_Net_CxPop3H
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Net/CxDnsClient.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader;
class CxMimeBody;

class CxPop3 :
    private CxNonCopyable
    /// POP3 (RFC 2821)
{
    public:
                          CxPop3              ();
                         ~CxPop3              ();

        bool              bCreate             (const std::tstring_t &csUser, const std::tstring_t &csPass, const std::tstring_t &csServer, ushort_t usPort);
        bool              bConnect            ();
        bool              bLogin              ();

        bool              bStat               (ulong_t &ulSum, ulong_t &ulSize);
        bool              bList               (std::vector<ulong_t> &veculList);
        bool              bListAt             (ulong_t &ulIndex);
        bool              bNoop               ();
        bool              bRset               ();
        bool              bTop                (int iNum, int iLines, std::tstring_t &sBuff);

        bool      /*RETR*/bRetrive            (int iNum, const std::tstring_t &csRawMimeMessage);
        bool      /*RETR*/bRetriveRaw         (int iNum, const std::tstring_t &csDirPath, const std::tstring_t &csFileName);
        bool      /*RETR*/bRetriveRawAndBackup(int iNum, const std::tstring_t &csDirPath, const std::tstring_t &csBackupDirPath, const std::tstring_t &csFileName);
        bool      /*TOP*/ bRetrieveHeader     (int iNum, CxMimeHeader &mhMimeHeader);

        bool              bDelete             (int iNum);
        bool              bDisconnect         ();

    private:
        std::tstring_t    _m_sRes;
        /////CxSocketInit _m_siInit;
        CxTcpClient       _m_scktSocket;
        CxConsoleLog      _m_clLog;
        std::tstring_t    _m_sUser;
        std::tstring_t    _m_sPass;
        std::tstring_t    _m_sServer;
        ushort_t          _m_usPort;
        bool              _m_bConnected;

        bool              _bCommand           (const std::tstring_t &csCmd, const std::tstring_t &csReplyDelimiter, std::tstring_t *psReply);
        bool              _bIsError           (const std::tstring_t &csText);
        ulong_t           _ulMailsSum         (const std::tstring_t &csServerAnswer);
        ulong_t           _ulMailsSize        (const std::tstring_t &csServerAnswer);
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxPop3H

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
