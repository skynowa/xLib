/**
 * \file  SmtpClient.inl
 * \brief SMTP (RFC 2821)
 */


#if !xOPTION_HEADER_ONLY
    #include "SmtpClient.h"
#endif


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/Crypt/Base64.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/Net/DnsClient.h>


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    Public methods
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
SmtpClient::SmtpClient() :
    _socket     (),
    _user       (),
    _password   (),
    _server     (),
    _port       (0),
    _isConnected(false)
{
////--    Socket::bInit();
}
//-------------------------------------------------------------------------------------------------
xINLINE
SmtpClient::~SmtpClient()
{
    disconnect();

////--    Socket::bClean();
}
//-------------------------------------------------------------------------------------------------
xINLINE
void_t
SmtpClient::create(
    std::ctstring_t &a_user,
    std::ctstring_t &a_password,
    std::ctstring_t &a_server,
    cushort_t       &a_port
)
{
    xTEST_EQ(a_user.empty(), false);
    ////xTEST_EQ(a_password.empty(), false);
    xTEST_EQ(a_server.empty(), false);
    xTEST_EQ((32767 > a_port) && (0 < a_port), true);

    _user     = a_user;
    _password = a_password;
    _server   = a_server;
    _port     = a_port;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SmtpClient::connect()
{
    std::tstring_t sRv;

    //-------------------------------------
    //������� �����
    _socket.create(Socket::afInet, Socket::tpStream, Socket::ptIp);

    //-------------------------------------
    //������ �����
    std::tstring_t ip;

    DnsClient::hostAddrByName(_server, &ip);

    //-------------------------------------
    //�����������
    _socket.connect(ip, _port);

    //-------------------------------------
    //[welcome message]
    sRv = _socket.recvAll(0, xT("\r\n"));
    xTEST_MSG_EQ(false, _isError(sRv), sRv);

    //-------------------------------------
    //[HELO\r\n]
    std::ctstring_t helloCmd = xT("HELO HOST\r\n");        //std::ctstring_t helloCmd = "HELO\r\n";

    _command(helloCmd, xT("\r\n"), /*ref*/sRv);

    _isConnected = true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SmtpClient::login()
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
    std::ctstring_t authLoginCmd = xT("AUTH LOGIN\r\n");

    _command(authLoginCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[mylogin\r\n]
    std::ctstring_t loginCmd = xS2TS( Base64().encode( xTS2S(_user) ) ) + xT("\r\n");

    _command(loginCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[mypassword\r\n]
    std::ctstring_t passwordCmd = xS2TS( Base64().encode( xTS2S(_password) ) ) + xT("\r\n");

    _command(passwordCmd, xT("\r\n"), /*ref*/sRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SmtpClient::noop()
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
    std::tstring_t noopCmd = xT("NOOP\r\n");

    _command(noopCmd, xT("\r\n"), /*ref*/sRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SmtpClient::rset()
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
    std::tstring_t rsetCmd = xT("RSET\r\n");

    _command(rsetCmd, xT("\r\n"), /*ref*/sRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SmtpClient::sendRaw
(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_from,
    std::ctstring_t &a_to
)
{
    // TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket,   false);
    xTEST_EQ(a_from.empty(), false);
    xTEST_EQ(a_to.empty(), false);

    std::tstring_t sRv;

    /////////std::ctstring_t helloCmd = "HELO HOST\r\n"; // std::ctstring_t helloCmd = "HELO\r\n";
    std::ctstring_t fromCmd = xT("MAIL FROM: <") + a_from + xT(">\r\n");
    std::ctstring_t toCmd   = xT("RCPT TO: <")   + a_to   + xT(">\r\n");
    std::ctstring_t dataCmd = xT("DATA\r\n");
    std::ctstring_t endCmd  = xT("\r\n.\r\n");

    //////////-------------------------------------
    //////////[HELO\r\n]
    ////////////bRv = _bCommand(helloCmd, "\r\n", /*ref*/sRv);
    ////////////xCHECK_RET(!bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _command(fromCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _command(toCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _command(dataCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    std::tstring_t text;

    File::textRead(a_filePath, &text);

    //-------------------------------------
    //[DataText\r\n.\r\n]
    _command(text + endCmd, xT("\r\n"), /*ref*/sRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SmtpClient::send(
    std::ctstring_t &a_text,
    std::ctstring_t &a_from,
    std::ctstring_t &a_to
)
{
    // TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_EQ(a_from.empty(), false);
    xTEST_EQ(a_to.empty(), false);

    std::tstring_t sRv;

    std::ctstring_t helloCmd = xT("HELO HOST\r\n");
    std::ctstring_t fromCmd  = xT("MAIL FROM: <") + a_from + xT(">\r\n");
    std::ctstring_t toCmd    = xT("RCPT TO: <")   + a_to   + xT(">\r\n");
    std::ctstring_t dataCmd  = xT("DATA\r\n");
    std::ctstring_t endCmd   = xT("\r\n.\r\n");

    //////-------------------------------------
    //////[HELO DrWEB\r\n]
    ////bRv = _bCommand(helloCmd, "\r\n", /*ref*/sRv);
    ////xCHECK_RET(!bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _command(fromCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _command(toCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _command(dataCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //�������� �����
    _socket.sendAll(a_text, 0);

    //-------------------------------------
    //[\r\n.\r\n]
    _command(endCmd, xT("\r\n"), /*ref*/sRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
SmtpClient::disconnect()
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
    std::ctstring_t quitCmd = xT("QUIT\r\n");

    _command(quitCmd, xT("\r\n"), /*ref*/sRv);

    _socket.close();

    _isConnected = false;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    Private methods
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
SmtpClient::_command(
    std::ctstring_t &a_command,
    std::ctstring_t &a_replyDelimiter,
    std::tstring_t  &a_reply
)
{
    xTEST_EQ(a_command.empty(), false);
    xTEST_EQ(a_replyDelimiter.empty(), false);

    std::tstring_t sRv;

    _socket.sendAll(a_command, 0);
    sRv = _socket.recvAll(0, a_replyDelimiter);

    a_reply.swap(sRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
SmtpClient::_isError(
    std::ctstring_t &a_text
)
{
    xTEST_EQ(a_text.empty(), false);

    bool_t bRv = !(
        !std::memcmp(a_text.c_str(), xT("334"), 3) || // 334 VXNlcm5hbWU6
        !std::memcmp(a_text.c_str(), xT("235"), 3) || // 235 2.0.0 Authentication successful
        !std::memcmp(a_text.c_str(), xT("220"), 3) || // 220 Kerio MailServer ESMTP ready
        !std::memcmp(a_text.c_str(), xT("250"), 3) || // 250 2.0.0 OK
        !std::memcmp(a_text.c_str(), xT("354"), 3) || // 354 Enter mail, end with CRLF.CRLF
        !std::memcmp(a_text.c_str(), xT("221"), 3)    // 221 221 2.0.0 SMTP closing connection
    );

    return bRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
