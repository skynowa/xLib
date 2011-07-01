/****************************************************************************
* Class name:  CxSmtp
* Description: POP3 (RFC 2821)
* File name:   CxSmtp.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     13.04.2009 16:44:49
*
*****************************************************************************/


#ifndef xLib_Net_CxSmtpH
#define xLib_Net_CxSmtpH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxTcpClientSocket.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxSmtp :
    public CxNonCopyable
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
        CxTcpClientSocket   _m_scktSocket;
        CxConsoleLog        _m_ConsoleLog;
        std::string         _m_sUser;
        std::string         _m_sPass;
        std::string         _m_sServer;
        USHORT              _m_usPort;
        BOOL                _m_bConnected;

        BOOL                _bCommand   (const std::string &csCmd, const std::string &csReplyDelimiter, std::string &sReply); /*+*/
        BOOL                _bIsError   (const std::string &csText);
};
#elif defined(xOS_LINUX)

#endif
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
