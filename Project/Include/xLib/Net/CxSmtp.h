/**
 * \file  CxSmtp.h
 * \brief SMTP (RFC 2821)
 */


#ifndef xLib_Net_CxSmtpH
#define xLib_Net_CxSmtpH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxTcpClient.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeHeader;
class CxMimeBody;

class CxSmtp :
    private CxNonCopyable
    /// SMTP (RFC 2821)
{
public:
                   CxSmtp    ();
                  ~CxSmtp    ();

    void           create    (std::ctstring_t &csUser, std::ctstring_t &csPass,
                              std::ctstring_t &csServer, cushort_t &cusPort);
    void           connect   ();
    void           login     ();
    void           noop      ();
    void           rset      ();
    void           sendRaw   (std::ctstring_t &csFilePath, std::ctstring_t &csFrom,
                              std::ctstring_t &csTo);
    void           send      (std::ctstring_t &csText, std::ctstring_t &sFrom,
                              std::ctstring_t &sTo);
    void           disconnect();

private:
    CxTcpClient    _m_scktSocket;
    std::tstring_t _m_sUser;
    std::tstring_t _m_sPass;
    std::tstring_t _m_sServer;
    ushort_t       _m_usPort;
    bool_t           _m_bConnected;

    void           _command  (std::ctstring_t &csCmd, std::ctstring_t &csReplyDelimiter,
                              std::tstring_t &sReply);
    bool_t           _isError  (std::ctstring_t &csText) xWARN_UNUSED_RV;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
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
VRFY <SP> <std::tstring_t> <CRLF>
EXPN <SP> <std::tstring_t> <CRLF>
HELP [<SP> <std::tstring_t>] <CRLF>
NOOP <CRLF>
QUIT <CRLF>
TURN <CRLF>
*/
