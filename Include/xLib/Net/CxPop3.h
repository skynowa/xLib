/**
 * \file  CxPop3.h
 * \brief POP3 (RFC 2821)
 */


#ifndef xLib_Net_CxPop3H
#define xLib_Net_CxPop3H
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxTcpClientSocket.h>
#include <xLib/Net/CxDnsClient.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxMimeMessage.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
//---------------------------------------------------------------------------
class CxPop3 :
    public CxNonCopyable
{
    public:
                          CxPop3              ();
                         ~CxPop3              ();

        BOOL              bCreate             (const std::tstring &csUser, const std::tstring &csPass, const std::tstring &csServer, USHORT usPort);
        BOOL              bConnect            ();
         BOOL              bLogin              ();

        BOOL              bStat               (ULONG &ulSum, ULONG &ulSize);
        BOOL              bList               (std::vector<ULONG> &veculList);
        BOOL              bListAt             (ULONG &ulIndex);
        BOOL              bNoop               ();
        BOOL              bRset               ();
        BOOL              bTop                (INT iNum, INT iLines, std::tstring &sBuff);

        BOOL      /*RETR*/bRetrive            (INT iNum, const std::tstring &csRawMimeMessage);
        BOOL      /*RETR*/bRetriveRaw         (INT iNum, const std::tstring &csDirPath, const std::tstring &csFileName);
        BOOL      /*RETR*/bRetriveRawAndBackup(INT iNum, const std::tstring &csDirPath, const std::tstring &csBackupDirPath, const std::tstring &csFileName);
        BOOL      /*TOP*/ bRetrieveHeader     (INT iNum, CxMimeHeader &mhMimeHeader);

        BOOL              bDelete             (INT iNum);
        BOOL              bDisconnect         ();

    private:
        BOOL              _m_bRes;
        std::tstring           _m_sRes;
        /////CxSocketInit      _m_siInit;
        CxTcpClientSocket _m_scktSocket;
        CxConsoleLog      _m_clLog;
        std::tstring              _m_sUser;
        std::tstring           _m_sPass;
        std::tstring           _m_sServer;
        USHORT            _m_usPort;
        BOOL              _m_bConnected;

        BOOL              _bCommand           (const std::tstring &csCmd, const std::tstring &csReplyDelimiter, std::tstring *psReply);
        BOOL              _bIsError           (const std::tstring &csText);
        ULONG             _ulMailsSum         (const std::tstring &csServerAnswer);
        ULONG             _ulMailsSize        (const std::tstring &csServerAnswer);
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
