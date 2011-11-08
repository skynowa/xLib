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
#include <xLib/Net/CxMimeMessage.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
//---------------------------------------------------------------------------
class CxPop3 :
    public CxNonCopyable
    /// POP3 (RFC 2821)
{
    public:
                          CxPop3              ();
                         ~CxPop3              ();

        BOOL              bCreate             (const std::string_t &csUser, const std::string_t &csPass, const std::string_t &csServer, USHORT usPort);
        BOOL              bConnect            ();
        BOOL              bLogin              ();

        BOOL              bStat               (ULONG &ulSum, ULONG &ulSize);
        BOOL              bList               (std::vector<ULONG> &veculList);
        BOOL              bListAt             (ULONG &ulIndex);
        BOOL              bNoop               ();
        BOOL              bRset               ();
        BOOL              bTop                (int iNum, int iLines, std::string_t &sBuff);

        BOOL      /*RETR*/bRetrive            (int iNum, const std::string_t &csRawMimeMessage);
        BOOL      /*RETR*/bRetriveRaw         (int iNum, const std::string_t &csDirPath, const std::string_t &csFileName);
        BOOL      /*RETR*/bRetriveRawAndBackup(int iNum, const std::string_t &csDirPath, const std::string_t &csBackupDirPath, const std::string_t &csFileName);
        BOOL      /*TOP*/ bRetrieveHeader     (int iNum, CxMimeHeader &mhMimeHeader);

        BOOL              bDelete             (int iNum);
        BOOL              bDisconnect         ();

    private:
        std::string_t      _m_sRes;
        /////CxSocketInit _m_siInit;
        CxTcpClient       _m_scktSocket;
        CxConsoleLog      _m_clLog;
        std::string_t      _m_sUser;
        std::string_t      _m_sPass;
        std::string_t      _m_sServer;
        USHORT            _m_usPort;
        BOOL              _m_bConnected;

        BOOL              _bCommand           (const std::string_t &csCmd, const std::string_t &csReplyDelimiter, std::string_t *psReply);
        BOOL              _bIsError           (const std::string_t &csText);
        ULONG             _ulMailsSum         (const std::string_t &csServerAnswer);
        ULONG             _ulMailsSize        (const std::string_t &csServerAnswer);
};
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
