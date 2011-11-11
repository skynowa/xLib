/**
 * \file  CxSmtp.h
 * \brief SMTP (RFC 2821)
 */


#ifndef xLib_Net_CxSmtpH
#define xLib_Net_CxSmtpH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSmtp :
    public CxNonCopyable
    /// SMTP (RFC 2821)
{
    public:
                            CxSmtp     ();
                           ~CxSmtp     ();

        BOOL                bCreate    (const std::string &csUser, const std::string &csPass, const std::string &csServer, USHORT usPort);
        BOOL                bConnect   ();
        BOOL                bLogin     ();
        BOOL                bNoop      ();
        BOOL                bRset      ();
        BOOL                bSendRaw   (const std::string &csFilePath, const std::string &csFrom, const std::string &csTo);
        BOOL                bSend      (const std::string &csText, const std::string &sFrom, const std::string &sTo);
        BOOL                bDisconnect();

    private:
        CxTcpClient         _m_scktSocket;
        CxConsoleLog        _m_ConsoleLog;
        std::string         _m_sUser;
        std::string         _m_sPass;
        std::string         _m_sServer;
        USHORT              _m_usPort;
        BOOL                _m_bConnected;

        BOOL                _bCommand   (const std::string &csCmd, const std::string &csReplyDelimiter, std::string &sReply); /*+*/
        BOOL                _bIsError   (const std::string &csText);
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
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
VRFY <SP> <string> <CRLF>
EXPN <SP> <string> <CRLF>
HELP [<SP> <string>] <CRLF>
NOOP <CRLF>
QUIT <CRLF>
TURN <CRLF>
*/
