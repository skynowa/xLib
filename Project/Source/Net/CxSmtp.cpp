/**
 * \file  CxSmtp.cpp
 * \brief SMTP (RFC 2821)
 */


//------------------------------------------------------------------------------
#include <xLib/Net/CxSmtp.h>

#include <xLib/Crypt/OpenSSL/CxBase64.h>
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
//DONE: CxSmtp
CxSmtp::CxSmtp() :
    _m_scktSocket(),
    _m_sUser     (),
    _m_sPass     (),
    _m_sServer   (),
    _m_usPort    (0),
    _m_bConnected(false)
{
////--    CxSocket::bInit();
}
//------------------------------------------------------------------------------
//DONE: ~CxSmtp
CxSmtp::~CxSmtp() {
    disconnect();

////--    CxSocket::bClean();
}
//------------------------------------------------------------------------------
//DONE: bCreate
void_t
CxSmtp::create(
    std::ctstring_t &a_csUser, 
    std::ctstring_t &a_csPass, 
    std::ctstring_t &a_csServer, 
    cushort_t       &a_cusPort
)
{
    xTEST_EQ(false, a_csUser.empty());
    ////xTEST_EQ(false, a_csPass.empty());
    xTEST_EQ(false, a_csServer.empty());
    xTEST_EQ(true, (32767 > a_cusPort) && (0 < a_cusPort));

    _m_sUser   = a_csUser;
    _m_sPass   = a_csPass;
    _m_sServer = a_csServer;
    _m_usPort  = a_cusPort;
}
//------------------------------------------------------------------------------
//DONE: bConnect
void_t
CxSmtp::connect() {
    std::tstring_t sRv;

    //-------------------------------------
    //������� �����
    _m_scktSocket.create(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

    //-------------------------------------
    //������ �����
    std::tstring_t sIpAddr;

    CxDnsClient::hostAddrByName(_m_sServer, &sIpAddr);

    //-------------------------------------
    //�����������
    _m_scktSocket.connect(sIpAddr, _m_usPort);

    //-------------------------------------
    //[welcome message]
    sRv = _m_scktSocket.recvAll(0, xT("\r\n"));
    xTEST_MSG_EQ(false, _isError(sRv), sRv);

    //-------------------------------------
    //[HELO\r\n]
    std::ctstring_t sHelloCmd = xT("HELO HOST\r\n");        //std::ctstring_t sHelloCmd = "HELO\r\n";

    _command(sHelloCmd, xT("\r\n"), /*ref*/sRv);

    _m_bConnected = true;
}
//------------------------------------------------------------------------------
//DONE: bLogin (��������� �� ������)
void_t
CxSmtp::login() {
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
    std::ctstring_t sLoginCmd = xS2TS( CxBase64::encode( xTS2S(_m_sUser) ) ) + xT("\r\n");

    _command(sLoginCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[mypassword\r\n]
    std::ctstring_t sPasswordCmd = xS2TS( CxBase64::encode( xTS2S(_m_sPass) ) ) + xT("\r\n");

    _command(sPasswordCmd, xT("\r\n"), /*ref*/sRv);
}
//------------------------------------------------------------------------------
//DONE: bNoop (�������� ��������� ���������� � ���������)
void_t
CxSmtp::noop() {
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
//DONE: bRset (������ ����� �������� �����)
void_t
CxSmtp::rset() {
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
//DONE: bSendRaw
void_t
CxSmtp::sendRaw(
    std::ctstring_t &a_csFilePath, 
    std::ctstring_t &a_sFrom, 
    std::ctstring_t &a_sTo
)
{
    // TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_scktSocket,   false);
    xTEST_EQ(false, a_sFrom.empty());
    xTEST_EQ(false, a_sTo.empty());

    std::tstring_t sRv;

    /////////std::ctstring_t sHelloCmd = "HELO HOST\r\n";        //std::ctstring_t sHelloCmd = "HELO\r\n";
    std::ctstring_t sFromCmd = xT("MAIL FROM: <") + a_sFrom + xT(">\r\n");
    std::ctstring_t sToCmd   = xT("RCPT TO: <")   + a_sTo   + xT(">\r\n");
    std::ctstring_t sDataCmd = xT("DATA\r\n");
    std::ctstring_t sEndCmd  = xT("\r\n.\r\n");

    //////////-------------------------------------
    //////////[HELO\r\n]
    ////////////bRv = _bCommand(sHelloCmd, "\r\n", /*ref*/sRv);
    ////////////xCHECK_RET(!bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _command(sFromCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _command(sToCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _command(sDataCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //DONE: ������ �� ����� � ����� ����� � �����
    std::tstring_t sText;

    CxFile::textRead(a_csFilePath, &sText);

    //-------------------------------------
    //[DataText\r\n.\r\n]
    _command(sText + sEndCmd, xT("\r\n"), /*ref*/sRv);
}
//------------------------------------------------------------------------------
//DONE: bSend
void_t
CxSmtp::send(
    std::ctstring_t &a_csText, 
    std::ctstring_t &a_sFrom, 
    std::ctstring_t &a_sTo
)
{
    // TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_scktSocket);
    xTEST_EQ(false, a_sFrom.empty());
    xTEST_EQ(false, a_sTo.empty());

    std::tstring_t sRv;

    std::ctstring_t sHelloCmd = xT("HELO HOST\r\n");
    std::ctstring_t sFromCmd  = xT("MAIL FROM: <") + a_sFrom + xT(">\r\n");
    std::ctstring_t sToCmd    = xT("RCPT TO: <")   + a_sTo   + xT(">\r\n");
    std::ctstring_t sDataCmd  = xT("DATA\r\n");
    std::ctstring_t sEndCmd   = xT("\r\n.\r\n");

    //////-------------------------------------
    //////[HELO DrWEB\r\n]
    ////bRv = _bCommand(sHelloCmd, "\r\n", /*ref*/sRv);
    ////xCHECK_RET(!bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _command(sFromCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _command(sToCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _command(sDataCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //�������� �����
    _m_scktSocket.sendAll(a_csText, 0);

    //-------------------------------------
    //[\r\n.\r\n]
    _command(sEndCmd, xT("\r\n"), /*ref*/sRv);
}
//------------------------------------------------------------------------------
//DONE: bDisconnect
void_t
CxSmtp::disconnect() {
    xCHECK_DO(!_m_bConnected, disconnect());

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

    _m_scktSocket.close();

    _m_bConnected = false;
}
//------------------------------------------------------------------------------



/*******************************************************************************
*    Private methods
*
*******************************************************************************/

//------------------------------------------------------------------------------
//DONE: _bCommand
void_t
CxSmtp::_command(std::ctstring_t &a_csCmd, std::ctstring_t &a_csReplyDelimiter, std::tstring_t &a_sReply) {
    xTEST_EQ(false, a_csCmd.empty());
    xTEST_EQ(false, a_csReplyDelimiter.empty());

    std::tstring_t sRv;

    _m_scktSocket.sendAll(a_csCmd, 0);
    _m_scktSocket.recvAll(0, a_csReplyDelimiter);

    a_sReply = sRv;
}
//------------------------------------------------------------------------------
//DONE: _isError
bool_t
CxSmtp::_isError(std::ctstring_t &a_csText) {
    xTEST_EQ(false, a_csText.empty());

    bool_t bRv = (bool_t)!(
            !std::memcmp(a_csText.c_str(), xT("334"), 3) ||    //334 VXNlcm5hbWU6
            !std::memcmp(a_csText.c_str(), xT("235"), 3) ||    //235 2.0.0 Authentication successful
            !std::memcmp(a_csText.c_str(), xT("220"), 3) ||    //220 Sergey Kerio MailServer 6.7.0 patch 1 ESMTP ready
            !std::memcmp(a_csText.c_str(), xT("250"), 3) ||    //250 2.0.0 OK
            !std::memcmp(a_csText.c_str(), xT("354"), 3) ||    //354 Enter mail, end with CRLF.CRLF
            !std::memcmp(a_csText.c_str(), xT("221"), 3)       //221 221 2.0.0 SMTP closing connection
    );

    return bRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
