/**
 * \file  CxSmtp.h
 * \brief SMTP (RFC 2821)
 */


#ifndef xLib_Net_CxSmtpH
#define xLib_Net_CxSmtpH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxTcpClient.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader;
class CxMimeBody;

class CxSmtp :
    private CxNonCopyable
    /// SMTP (RFC 2821)
{
    public:
                            CxSmtp     ();
                           ~CxSmtp     ();

        void                vCreate    (const std::string &csUser, const std::string &csPass, const std::string &csServer, const ushort_t &cusPort);
        void                vConnect   ();
        void                vLogin     ();
        void                vNoop      ();
        void                vRset      ();
        void                vSendRaw   (const std::string &csFilePath, const std::string &csFrom, const std::string &csTo);
        void                vSend      (const std::string &csText, const std::string &sFrom, const std::string &sTo);
        void                vDisconnect();

    private:
        CxTcpClient         _m_scktSocket;
        std::string         _m_sUser;
        std::string         _m_sPass;
        std::string         _m_sServer;
        ushort_t            _m_usPort;
        bool                _m_bConnected;

        void                _vCommand   (const std::string &csCmd, const std::string &csReplyDelimiter, std::string &sReply); /*+*/
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
