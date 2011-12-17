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
    private CxNonCopyable
    /// SMTP (RFC 2821)
{
    public:
                            CxSmtp     ();
                           ~CxSmtp     ();

        bool                bCreate    (const std::string &csUser, const std::string &csPass, const std::string &csServer, ushort_t usPort);
        bool                bConnect   ();
        bool                bLogin     ();
        bool                bNoop      ();
        bool                bRset      ();
        bool                bSendRaw   (const std::string &csFilePath, const std::string &csFrom, const std::string &csTo);
        bool                bSend      (const std::string &csText, const std::string &sFrom, const std::string &sTo);
        bool                bDisconnect();

    private:
        CxTcpClient         _m_scktSocket;
        CxConsoleLog        _m_ConsoleLog;
        std::string         _m_sUser;
        std::string         _m_sPass;
        std::string         _m_sServer;
        ushort_t            _m_usPort;
        bool                _m_bConnected;

        bool                _bCommand   (const std::string &csCmd, const std::string &csReplyDelimiter, std::string &sReply); /*+*/
        bool                _bIsError   (const std::string &csText);
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
