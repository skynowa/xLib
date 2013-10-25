/**
 * \file  CxSmtp.cpp
 * \brief SMTP (RFC 2821)
 */


//------------------------------------------------------------------------------
#include <xLib/Net/CxSmtp.h>

#include <xLib/Crypt/CxBase64.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Net/CxDnsClient.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    Public methods
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxSmtp::CxSmtp() :
    _socket     (),
    _user       (),
    _password   (),
    _server     (),
    _port       (0),
    _isConnected(false)
{
////--    CxSocket::bInit();
}
//------------------------------------------------------------------------------
xINLINE_HO
CxSmtp::~CxSmtp()
{
    disconnect();

////--    CxSocket::bClean();
}
//------------------------------------------------------------------------------
xINLINE_HO
void_t
CxSmtp::create(
    std::ctstring_t &a_user,
    std::ctstring_t &a_password,
    std::ctstring_t &a_server,
    cushort_t       &a_port
)
{
    xTEST_EQ(false, a_user.empty());
    ////xTEST_EQ(false, a_password.empty());
    xTEST_EQ(false, a_server.empty());
    xTEST_EQ(true, (32767 > a_port) && (0 < a_port));

    _user   = a_user;
    _password   = a_password;
    _server = a_server;
    _port  = a_port;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSmtp::connect()
{
    std::tstring_t sRv;

    //-------------------------------------
    //������� �����
    _socket.create(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

    //-------------------------------------
    //������ �����
    std::tstring_t sIpAddr;

    CxDnsClient::hostAddrByName(_server, &sIpAddr);

    //-------------------------------------
    //�����������
    _socket.connect(sIpAddr, _port);

    //-------------------------------------
    //[welcome message]
    sRv = _socket.recvAll(0, xT("\r\n"));
    xTEST_MSG_EQ(false, _isError(sRv), sRv);

    //-------------------------------------
    //[HELO\r\n]
    std::ctstring_t sHelloCmd = xT("HELO HOST\r\n");        //std::ctstring_t sHelloCmd = "HELO\r\n";

    _command(sHelloCmd, xT("\r\n"), /*ref*/sRv);

    _isConnected = true;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSmtp::login()
{
    //-------------------------------------
    //RFC
    /*
    C: AUTH LOGIN\r\n
    S: 334 VXNlcm5hbWU6
    C: base64_encode(MYLOGIN)\r\n
    C: base64_encode(MYPASS)\r\n
    S: 235 Authentication succeeded
    */

    std::tstring_t sRv;

    //-------------------------------------
    //[AUTH\r\n]
    std::ctstring_t sAuthLoginCmd = xT("AUTH LOGIN\r\n");

    _command(sAuthLoginCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[mylogin\r\n]
    std::ctstring_t sLoginCmd = xS2TS( CxBase64::encode( xTS2S(_user) ) ) + xT("\r\n");

    _command(sLoginCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[mypassword\r\n]
    std::ctstring_t sPasswordCmd = xS2TS( CxBase64::encode( xTS2S(_password) ) ) + xT("\r\n");

    _command(sPasswordCmd, xT("\r\n"), /*ref*/sRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSmtp::noop()
{
    //-------------------------------------
    //RFC
    /*
    �: NOOP
    S: +��
    */

    std::tstring_t sRv;

    //-------------------------------------
    //[NOOP\r\n]
    std::tstring_t sNoopCmd = xT("NOOP\r\n");

    _command(sNoopCmd, xT("\r\n"), /*ref*/sRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSmtp::rset()
{
    //-------------------------------------
    //RFC
    /*
    �: RSET
    S: +OK maildrop has 2 messages (320 octets)
    */

    std::tstring_t sRv;

    //-------------------------------------
    //[RSET\r\n]
    std::tstring_t sRsetCmd = xT("RSET\r\n");

    _command(sRsetCmd, xT("\r\n"), /*ref*/sRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSmtp::sendRaw
(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_from,
    std::ctstring_t &a_to
)
{
    // TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket,   false);
    xTEST_EQ(false, a_from.empty());
    xTEST_EQ(false, a_to.empty());

    std::tstring_t sRv;

    /////////std::ctstring_t sHelloCmd = "HELO HOST\r\n";        //std::ctstring_t sHelloCmd = "HELO\r\n";
    std::ctstring_t fromCmd = xT("MAIL FROM: <") + a_from + xT(">\r\n");
    std::ctstring_t toCmd   = xT("RCPT TO: <")   + a_to   + xT(">\r\n");
    std::ctstring_t sDataCmd = xT("DATA\r\n");
    std::ctstring_t sEndCmd  = xT("\r\n.\r\n");

    //////////-------------------------------------
    //////////[HELO\r\n]
    ////////////bRv = _bCommand(sHelloCmd, "\r\n", /*ref*/sRv);
    ////////////xCHECK_RET(!bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _command(fromCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _command(toCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _command(sDataCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //DONE: ������ �� ����� � ����� ����� � �����
    std::tstring_t sText;

    CxFile::textRead(a_filePath, &sText);

    //-------------------------------------
    //[DataText\r\n.\r\n]
    _command(sText + sEndCmd, xT("\r\n"), /*ref*/sRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSmtp::send(
    std::ctstring_t &a_text,
    std::ctstring_t &a_from,
    std::ctstring_t &a_to
)
{
    // TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_EQ(false, a_from.empty());
    xTEST_EQ(false, a_to.empty());

    std::tstring_t sRv;

    std::ctstring_t sHelloCmd = xT("HELO HOST\r\n");
    std::ctstring_t fromCmd  = xT("MAIL FROM: <") + a_from + xT(">\r\n");
    std::ctstring_t toCmd    = xT("RCPT TO: <")   + a_to   + xT(">\r\n");
    std::ctstring_t sDataCmd  = xT("DATA\r\n");
    std::ctstring_t sEndCmd   = xT("\r\n.\r\n");

    //////-------------------------------------
    //////[HELO DrWEB\r\n]
    ////bRv = _bCommand(sHelloCmd, "\r\n", /*ref*/sRv);
    ////xCHECK_RET(!bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _command(fromCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _command(toCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _command(sDataCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //�������� �����
    _socket.sendAll(a_text, 0);

    //-------------------------------------
    //[\r\n.\r\n]
    _command(sEndCmd, xT("\r\n"), /*ref*/sRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSmtp::disconnect()
{
    xCHECK_DO(!_isConnected, disconnect());

    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    std::tstring_t sRv;

    //-------------------------------------
    //[QUIT]
    std::ctstring_t sQuitCmd = xT("QUIT\r\n");

    _command(sQuitCmd, xT("\r\n"), /*ref*/sRv);

    _socket.close();

    _isConnected = false;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    Private methods
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSmtp::_command(
    std::ctstring_t &a_command,
    std::ctstring_t &a_replyDelimiter,
    std::tstring_t  &a_reply
)
{
    xTEST_EQ(false, a_command.empty());
    xTEST_EQ(false, a_replyDelimiter.empty());

    std::tstring_t sRv;

    _socket.sendAll(a_command, 0);
    sRv = _socket.recvAll(0, a_replyDelimiter);

    a_reply.swap(sRv);
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxSmtp::_isError(
    std::ctstring_t &a_text
)
{
    xTEST_EQ(false, a_text.empty());

    bool_t bRv = (bool_t)!(
            !std::memcmp(a_text.c_str(), xT("334"), 3) ||    //334 VXNlcm5hbWU6
            !std::memcmp(a_text.c_str(), xT("235"), 3) ||    //235 2.0.0 Authentication successful
            !std::memcmp(a_text.c_str(), xT("220"), 3) ||    //220 Sergey Kerio MailServer 6.7.0 patch 1 ESMTP ready
            !std::memcmp(a_text.c_str(), xT("250"), 3) ||    //250 2.0.0 OK
            !std::memcmp(a_text.c_str(), xT("354"), 3) ||    //354 Enter mail, end with CRLF.CRLF
            !std::memcmp(a_text.c_str(), xT("221"), 3)       //221 221 2.0.0 SMTP closing connection
    );

    return bRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
