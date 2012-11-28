/**
 * \file  CxSmtp.cpp
 * \brief SMTP (RFC 2821)
 */


//---------------------------------------------------------------------------
#include <xLib/Net/CxSmtp.h>

#include <xLib/Crypt/OpenSSL/CxBase64.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Net/CxDnsClient.h>
//---------------------------------------------------------------------------


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSmtp
CxSmtp::CxSmtp() :
    _m_scktSocket(),
    _m_sUser(),
    _m_sPass(),
    _m_sServer(),
    _m_usPort(0),
    _m_bConnected(false)
{
////--    CxSocket::bInit();
}
//---------------------------------------------------------------------------
//DONE: ~CxSmtp
CxSmtp::~CxSmtp() {
    vDisconnect();

////--    CxSocket::bClean();
}
//---------------------------------------------------------------------------
//DONE: bCreate
void
CxSmtp::vCreate(const std::tstring_t &a_csUser, const std::tstring_t &a_csPass, const std::tstring_t &a_csServer, const ushort_t &a_cusPort) {
    xTEST_EQ(false, a_csUser.empty());
    ////xTEST_EQ(false, a_csPass.empty());
    xTEST_EQ(false, a_csServer.empty());
    xTEST_EQ(true, (32767 > a_cusPort) && (0 < a_cusPort));

    _m_sUser   = a_csUser;
    _m_sPass   = a_csPass;
    _m_sServer = a_csServer;
    _m_usPort  = a_cusPort;
}
//---------------------------------------------------------------------------
//DONE: bConnect
void
CxSmtp::vConnect() {
    std::tstring_t sRv;

    //-------------------------------------
    //������� �����
    _m_scktSocket.vCreate(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

    //-------------------------------------
    //������ �����
    std::tstring_t sIpAddr;

    CxDnsClient::vHostAddrByName(_m_sServer, &sIpAddr);

    //-------------------------------------
    //�����������
    _m_scktSocket.vConnect(sIpAddr, _m_usPort);

    //-------------------------------------
    //[welcome message]
    sRv = _m_scktSocket.sRecvAll(0, xT("\r\n"));
    xTEST_MSG_EQ(false, _bIsError(sRv), sRv);

    //-------------------------------------
    //[HELO\r\n]
    const std::tstring_t sHelloCmd = xT("HELO HOST\r\n");        //const std::tstring_t sHelloCmd = "HELO\r\n";

    _vCommand(sHelloCmd, xT("\r\n"), /*ref*/sRv);

    _m_bConnected = true;
}
//---------------------------------------------------------------------------
//DONE: bLogin (��������� �� ������)
void
CxSmtp::vLogin() {
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
    const std::tstring_t sAuthLoginCmd = xT("AUTH LOGIN\r\n");

    _vCommand(sAuthLoginCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[mylogin\r\n]
    const std::tstring_t sLoginCmd = xS2TS( CxBase64::sEncode( xTS2S(_m_sUser) ) ) + xT("\r\n");

    _vCommand(sLoginCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[mypassword\r\n]
    const std::tstring_t sPasswordCmd = xS2TS( CxBase64::sEncode( xTS2S(_m_sPass) ) ) + xT("\r\n");

    _vCommand(sPasswordCmd, xT("\r\n"), /*ref*/sRv);
}
//---------------------------------------------------------------------------
//DONE: bNoop (�������� ��������� ���������� � ���������)
void
CxSmtp::vNoop() {
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

    _vCommand(sNoopCmd, xT("\r\n"), /*ref*/sRv);
}
//---------------------------------------------------------------------------
//DONE: bRset (������ ����� �������� �����)
void
CxSmtp::vRset() {
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

    _vCommand(sRsetCmd, xT("\r\n"), /*ref*/sRv);
}
//---------------------------------------------------------------------------
//DONE: bSendRaw
void
CxSmtp::vSendRaw(const std::tstring_t &a_csFilePath, const std::tstring_t &a_sFrom, const std::tstring_t &a_sTo) {
    // TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_scktSocket,   false);
    xTEST_EQ(false, a_sFrom.empty());
    xTEST_EQ(false, a_sTo.empty());

    std::tstring_t sRv;

    /////////const std::tstring_t sHelloCmd = "HELO HOST\r\n";        //const std::tstring_t sHelloCmd = "HELO\r\n";
    const std::tstring_t sFromCmd = xT("MAIL FROM: <") + a_sFrom + xT(">\r\n");
    const std::tstring_t sToCmd   = xT("RCPT TO: <")   + a_sTo   + xT(">\r\n");
    const std::tstring_t sDataCmd = xT("DATA\r\n");
    const std::tstring_t sEndCmd  = xT("\r\n.\r\n");

    //////////-------------------------------------
    //////////[HELO\r\n]
    ////////////bRv = _bCommand(sHelloCmd, "\r\n", /*ref*/sRv);
    ////////////xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _vCommand(sFromCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _vCommand(sToCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _vCommand(sDataCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //DONE: ������ �� ����� � ����� ����� � �����
    std::tstring_t sText;

    CxFile::vTextRead(a_csFilePath, &sText);

    //-------------------------------------
    //[DataText\r\n.\r\n]
    _vCommand(sText + sEndCmd, xT("\r\n"), /*ref*/sRv);
}
//---------------------------------------------------------------------------
//DONE: bSend
void
CxSmtp::vSend(const std::tstring_t &a_csText, const std::tstring_t &a_sFrom, const std::tstring_t &a_sTo) {
    // TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_scktSocket);
    xTEST_EQ(false, a_sFrom.empty());
    xTEST_EQ(false, a_sTo.empty());

    std::tstring_t sRv;

    const std::tstring_t sHelloCmd = xT("HELO HOST\r\n");
    const std::tstring_t sFromCmd  = xT("MAIL FROM: <") + a_sFrom + xT(">\r\n");
    const std::tstring_t sToCmd    = xT("RCPT TO: <")   + a_sTo   + xT(">\r\n");
    const std::tstring_t sDataCmd  = xT("DATA\r\n");
    const std::tstring_t sEndCmd   = xT("\r\n.\r\n");

    //////-------------------------------------
    //////[HELO DrWEB\r\n]
    ////bRv = _bCommand(sHelloCmd, "\r\n", /*ref*/sRv);
    ////xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _vCommand(sFromCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _vCommand(sToCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _vCommand(sDataCmd, xT("\r\n"), /*ref*/sRv);

    //-------------------------------------
    //�������� �����
    _m_scktSocket.vSendAll(a_csText, 0);

    //-------------------------------------
    //[\r\n.\r\n]
    _vCommand(sEndCmd, xT("\r\n"), /*ref*/sRv);
}
//---------------------------------------------------------------------------
//DONE: bDisconnect
void
CxSmtp::vDisconnect() {
    xCHECK_DO(false == _m_bConnected, vDisconnect());

    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    std::tstring_t sRv;

    //-------------------------------------
    //[QUIT]
    const std::tstring_t sQuitCmd = xT("QUIT\r\n");

    _vCommand(sQuitCmd, xT("\r\n"), /*ref*/sRv);

    _m_scktSocket.vClose();

    _m_bConnected = false;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    Private methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bCommand
void
CxSmtp::_vCommand(const std::tstring_t &a_csCmd, const std::tstring_t &a_csReplyDelimiter, std::tstring_t &a_sReply) {
    xTEST_EQ(false, a_csCmd.empty());
    xTEST_EQ(false, a_csReplyDelimiter.empty());

    std::tstring_t sRv;

    _m_scktSocket.vSendAll(a_csCmd, 0);
    _m_scktSocket.sRecvAll(0, a_csReplyDelimiter);

    a_sReply = sRv;
}
//---------------------------------------------------------------------------
//DONE: _bIsError
bool
CxSmtp::_bIsError(const std::tstring_t &a_csText) {
    xTEST_EQ(false, a_csText.empty());

    bool bRv = (bool)!(
            !std::memcmp(a_csText.c_str(), xT("334"), 3) ||    //334 VXNlcm5hbWU6
            !std::memcmp(a_csText.c_str(), xT("235"), 3) ||    //235 2.0.0 Authentication successful
            !std::memcmp(a_csText.c_str(), xT("220"), 3) ||    //220 Sergey Kerio MailServer 6.7.0 patch 1 ESMTP ready
            !std::memcmp(a_csText.c_str(), xT("250"), 3) ||    //250 2.0.0 OK
            !std::memcmp(a_csText.c_str(), xT("354"), 3) ||    //354 Enter mail, end with CRLF.CRLF
            !std::memcmp(a_csText.c_str(), xT("221"), 3)       //221 221 2.0.0 SMTP closing connection
    );

    return bRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
