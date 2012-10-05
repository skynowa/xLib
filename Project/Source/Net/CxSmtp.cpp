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
CxSmtp::vCreate(const std::string &a_csUser, const std::string &a_csPass, const std::string &a_csServer, const ushort_t &a_cusPort) {
    /*DEBUG*/xTEST_EQ(false, a_csUser.empty());
    /*DEBUG*/////xTEST_EQ(false, a_csPass.empty());
    /*DEBUG*/xTEST_EQ(false, a_csServer.empty());
    /*DEBUG*/xTEST_EQ(true, (32767 > a_cusPort) && (0 < a_cusPort));

    _m_sUser   = a_csUser;
    _m_sPass   = a_csPass;
    _m_sServer = a_csServer;
    _m_usPort  = a_cusPort;
}
//---------------------------------------------------------------------------
//DONE: bConnect
void
CxSmtp::vConnect() {
    bool        bRv = false;
    std::string sRv = "";

    //-------------------------------------
    //������� �����
    _m_scktSocket.bCreate(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

    //-------------------------------------
    //������ �����
    std::string sIpAddr;

    CxDnsClient::vGetHostAddrByName(_m_sServer, &sIpAddr);

    //-------------------------------------
    //�����������
    _m_scktSocket.bConnect(sIpAddr, _m_usPort);

    //-------------------------------------
    //[welcome message]
    sRv = _m_scktSocket.sRecvAll(0, "\r\n");
    /*DEBUG*/xTEST_MSG_EQ(false, _bIsError(sRv), sRv);

    //-------------------------------------
    //[HELO\r\n]
    const std::string sHelloCmd = "HELO HOST\r\n";        //const std::string sHelloCmd = "HELO\r\n";

    _vCommand(sHelloCmd, "\r\n", /*ref*/sRv);

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

    std::string sRv;

    //-------------------------------------
    //[AUTH\r\n]
    const std::string sAuthLoginCmd = "AUTH LOGIN\r\n";

    _vCommand(sAuthLoginCmd, "\r\n", /*ref*/sRv);

    //-------------------------------------
    //[mylogin\r\n]
    const std::string sLoginCmd = CxBase64::sEncode(_m_sUser) + "\r\n";

    _vCommand(sLoginCmd, "\r\n", /*ref*/sRv);

    //-------------------------------------
    //[mypassword\r\n]
    const std::string sPasswordCmd = CxBase64::sEncode(_m_sPass) + "\r\n";

    _vCommand(sPasswordCmd, "\r\n", /*ref*/sRv);
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

    std::string sRv;

    //-------------------------------------
    //[NOOP\r\n]
    std::string sNoopCmd = "NOOP\r\n";

    _vCommand(sNoopCmd, "\r\n", /*ref*/sRv);
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

    std::string sRv;

    //-------------------------------------
    //[RSET\r\n]
    std::string sRsetCmd = "RSET\r\n";

    _vCommand(sRsetCmd, "\r\n", /*ref*/sRv);
}
//---------------------------------------------------------------------------
//DONE: bSendRaw
void
CxSmtp::vSendRaw(const std::string &a_csFilePath, const std::string &a_sFrom, const std::string &a_sTo) {
    /*DEBUG*/// TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_scktSocket,   false);
    /*DEBUG*/xTEST_EQ(false, a_sFrom.empty());
    /*DEBUG*/xTEST_EQ(false, a_sTo.empty());

    std::string sRv;

    /////////const std::string sHelloCmd = "HELO HOST\r\n";        //const std::string sHelloCmd = "HELO\r\n";
    const std::string sFromCmd  = "MAIL FROM: <" + a_sFrom + ">\r\n";
    const std::string sToCmd    = "RCPT TO: <"   + a_sTo   + ">\r\n";
    const std::string sDataCmd  = "DATA\r\n";
    const std::string sEndCmd   = "\r\n.\r\n";

    //////////-------------------------------------
    //////////[HELO\r\n]
    ////////////bRv = _bCommand(sHelloCmd, "\r\n", /*ref*/sRv);
    ////////////xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _vCommand(sFromCmd, "\r\n", /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _vCommand(sToCmd, "\r\n", /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _vCommand(sDataCmd, "\r\n", /*ref*/sRv);

    //-------------------------------------
    //DONE: ������ �� ����� � ����� ����� � �����
    std::string sText = "";

    CxFile::vTextRead(a_csFilePath, &sText);

    //-------------------------------------
    //[DataText\r\n.\r\n]
    _vCommand(sText + sEndCmd, "\r\n", /*ref*/sRv);
}
//---------------------------------------------------------------------------
//DONE: bSend
void
CxSmtp::vSend(const std::string &a_csText, const std::string &a_sFrom, const std::string &a_sTo) {
    /*DEBUG*/// TODO: xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_scktSocket);
    /*DEBUG*/xTEST_EQ(false, a_sFrom.empty());
    /*DEBUG*/xTEST_EQ(false, a_sTo.empty());

    std::string sRv;

    const std::string sHelloCmd = "HELO HOST\r\n";
    const std::string sFromCmd  = "MAIL FROM: <" + a_sFrom + ">\r\n";
    const std::string sToCmd    = "RCPT TO: <"   + a_sTo   + ">\r\n";
    const std::string sDataCmd  = "DATA\r\n";
    const std::string sEndCmd   = "\r\n.\r\n";

    //////-------------------------------------
    //////[HELO DrWEB\r\n]
    ////bRv = _bCommand(sHelloCmd, "\r\n", /*ref*/sRv);
    ////xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    _vCommand(sFromCmd, "\r\n", /*ref*/sRv);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    _vCommand(sToCmd, "\r\n", /*ref*/sRv);

    //-------------------------------------
    //[DATA\r\n]
    _vCommand(sDataCmd, "\r\n", /*ref*/sRv);

    //-------------------------------------
    //�������� �����
    _m_scktSocket.bSendAll(a_csText, 0);

    //-------------------------------------
    //[\r\n.\r\n]
    _vCommand(sEndCmd, "\r\n", /*ref*/sRv);
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

    std::string sRv;

    //-------------------------------------
    //[QUIT]
    const std::string sQuitCmd = "QUIT\r\n";

    _vCommand(sQuitCmd, "\r\n", /*ref*/sRv);

    _m_scktSocket.bClose();

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
CxSmtp::_vCommand(const std::string &a_csCmd, const std::string &a_csReplyDelimiter, std::string &a_sReply) {
    /*DEBUG*/xTEST_EQ(false, a_csCmd.empty());
    /*DEBUG*/xTEST_EQ(false, a_csReplyDelimiter.empty());

    std::string sRv;

    _m_scktSocket.bSendAll(a_csCmd, 0);

    _m_scktSocket.sRecvAll(0, a_csReplyDelimiter);

    a_sReply = sRv;
}
//---------------------------------------------------------------------------
//DONE: _bIsError
bool
CxSmtp::_bIsError(const std::string &a_csText) {
    /*DEBUG*/xTEST_EQ(false, a_csText.empty());

    bool bRv = (bool)!(
            !std::memcmp(a_csText.c_str(), "334", 3) ||    //334 VXNlcm5hbWU6
            !std::memcmp(a_csText.c_str(), "235", 3) ||    //235 2.0.0 Authentication successful
            !std::memcmp(a_csText.c_str(), "220", 3) ||    //220 Sergey Kerio MailServer 6.7.0 patch 1 ESMTP ready
            !std::memcmp(a_csText.c_str(), "250", 3) ||    //250 2.0.0 OK
            !std::memcmp(a_csText.c_str(), "354", 3) ||    //354 Enter mail, end with CRLF.CRLF
            !std::memcmp(a_csText.c_str(), "221", 3)       //221 221 2.0.0 SMTP closing connection
    );

    return bRv;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
