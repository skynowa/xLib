/**
 * \file  CxSmtp.cpp
 * \brief SMTP (RFC 2821)
 */


//---------------------------------------------------------------------------
#include <xLib/Net/CxSmtp.h>

#include <xLib/Crypt/OpenSSL/CxBase64.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Log/CxTraceLog.h>
#include <xLib/Log/CxConsoleLog.h>
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
    _m_ConsoleLog(false),
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
    if (true == _m_bConnected) {
        bDisconnect();
    }

////--    CxSocket::bClean();
}
//---------------------------------------------------------------------------
//DONE: bCreate
bool
CxSmtp::bCreate(const std::string &csUser, const std::string &csPass, const std::string &csServer, ushort_t usPort) {
    /*DEBUG*/xASSERT_RET(false == csUser.empty(),          false);
    /*DEBUG*/////xASSERT_RET(false == csPass.empty(),          false);
    /*DEBUG*/xASSERT_RET(false == csServer.empty(),        false);
    /*DEBUG*/xASSERT_RET((32767 > usPort) && (0 < usPort), false);

    _m_sUser   = csUser;
    _m_sPass   = csPass;
    _m_sServer = csServer;
    _m_usPort  = usPort;

    return true;
}
//---------------------------------------------------------------------------
//DONE: bConnect
bool
CxSmtp::bConnect() {
    bool        bRes = false;
    std::string sRes = "";

    //-------------------------------------
    //������� �����
    bRes = _m_scktSocket.bCreate(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //������ �����
    std::string sIpAddr;

    bRes = CxDnsClient::bGetHostAddrByName(_m_sServer, &sIpAddr);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //�����������
    bRes = _m_scktSocket.bConnect(sIpAddr, _m_usPort);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[welcome message]
    sRes = _m_scktSocket.sRecvAll(0, "\r\n");
    /*DEBUG*/xASSERT_MSG_RET(false == _bIsError(sRes), sRes.c_str(), false);

    //-------------------------------------
    //[HELO\r\n]
    const std::string sHelloCmd = "HELO HOST\r\n";        //const std::string sHelloCmd = "HELO\r\n";

    bRes = _bCommand(sHelloCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);


    _m_bConnected = true;

    return true;
}
//---------------------------------------------------------------------------
//DONE: bLogin (��������� �� ������)
bool
CxSmtp::bLogin() {
    //-------------------------------------
    //RFC
    /*
    C: AUTH LOGIN\r\n
    S: 334 VXNlcm5hbWU6
    C: base64_encode(MYLOGIN)\r\n
    C: base64_encode(MYPASS)\r\n
    S: 235 Authentication succeeded
    */

    bool        bRes = false;
    std::string sRes = "";

    //-------------------------------------
    //[AUTH\r\n]
    const std::string sAuthLoginCmd = "AUTH LOGIN\r\n";

    bRes = _bCommand(sAuthLoginCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[mylogin\r\n]
    const std::string sLoginCmd = CxBase64::sEncode(_m_sUser) + "\r\n";

    bRes = _bCommand(sLoginCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[mypassword\r\n]
    const std::string sPasswordCmd = CxBase64::sEncode(_m_sPass) + "\r\n";

    bRes = _bCommand(sPasswordCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bNoop (�������� ��������� ���������� � ���������)
bool
CxSmtp::bNoop() {
    //-------------------------------------
    //RFC
    /*
    �: NOOP
    S: +��
    */

    bool        bRes = false;
    std::string sRes = "";

    //-------------------------------------
    //[NOOP\r\n]
    std::string sNoopCmd = "NOOP\r\n";

    bRes = _bCommand(sNoopCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRset (������ ����� �������� �����)
bool
CxSmtp::bRset() {
    //-------------------------------------
    //RFC
    /*
    �: RSET
    S: +OK maildrop has 2 messages (320 octets)
    */

    bool        bRes = false;
    std::string sRes = "";

    //-------------------------------------
    //[RSET\r\n]
    std::string sRsetCmd = "RSET\r\n";

    bRes = _bCommand(sRsetCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bSendRaw
bool
CxSmtp::bSendRaw(const std::string &csFilePath, const std::string &sFrom, const std::string &sTo) {
    /*DEBUG*/xASSERT_RET(CxSocket::etInvalid != _m_scktSocket, false);
    /*DEBUG*/xASSERT_RET(false               == sFrom.empty(), false);
    /*DEBUG*/xASSERT_RET(false               == sTo.empty(),   false);

    bool              bRes      = false;
    std::string       sRes      = "";

    /////////const std::string sHelloCmd = "HELO HOST\r\n";        //const std::string sHelloCmd = "HELO\r\n";
    const std::string sFromCmd  = "MAIL FROM: <" + sFrom + ">\r\n";
    const std::string sToCmd    = "RCPT TO: <"   + sTo   + ">\r\n";
    const std::string sDataCmd  = "DATA\r\n";
    const std::string sEndCmd   = "\r\n.\r\n";

    //////////-------------------------------------
    //////////[HELO\r\n]
    ////////////bRes = _bCommand(sHelloCmd, "\r\n", /*ref*/sRes);
    ////////////xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    bRes = _bCommand(sFromCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    bRes = _bCommand(sToCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[DATA\r\n]
    bRes = _bCommand(sDataCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //DONE: ������ �� ����� � ����� ����� � �����
    std::string sText = "";

    bRes = CxFile::bTextRead(csFilePath, &sText);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[DataText\r\n.\r\n]
    bRes = _bCommand(sText + sEndCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bSend
bool
CxSmtp::bSend(const std::string &csText, const std::string &sFrom, const std::string &sTo) {
    /*DEBUG*/xASSERT_RET(CxSocket::etInvalid != _m_scktSocket, false);
    /*DEBUG*/xASSERT_RET(false               == sFrom.empty(), false);
    /*DEBUG*/xASSERT_RET(false               == sTo.empty(),   false);

    bool              bRes      = false;
    std::string       sRes      = "";

    const std::string sHelloCmd = "HELO HOST\r\n";
    const std::string sFromCmd  = "MAIL FROM: <" + sFrom + ">\r\n";
    const std::string sToCmd    = "RCPT TO: <"   + sTo   + ">\r\n";
    const std::string sDataCmd  = "DATA\r\n";
    const std::string sEndCmd   = "\r\n.\r\n";

    //////-------------------------------------
    //////[HELO DrWEB\r\n]
    ////bRes = _bCommand(sHelloCmd, "\r\n", /*ref*/sRes);
    ////xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    bRes = _bCommand(sFromCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    bRes = _bCommand(sToCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //[DATA\r\n]
    bRes = _bCommand(sDataCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    //-------------------------------------
    //�������� �����
    bRes = _m_scktSocket.bSendAll(csText, 0);
    xASSERT_RET(true == bRes, false);

    //-------------------------------------
    //[\r\n.\r\n]
    bRes = _bCommand(sEndCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bDisconnect
bool
CxSmtp::bDisconnect() {
    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    bool        bRes = false;
    std::string sRes = "";

    //-------------------------------------
    //[QUIT]
    const std::string sQuitCmd = "QUIT\r\n";

    bRes = _bCommand(sQuitCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(false == bRes, false);

    bRes = _m_scktSocket.bClose();
    xCHECK_RET(false == bRes, false);

    _m_bConnected = false;

    return true;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    Private methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bCommand
bool
CxSmtp::_bCommand(const std::string &csCmd, const std::string &csReplyDelimiter, std::string &sReply) {
    /*DEBUG*/xASSERT_RET(false == csCmd.empty(),            false);
    /*DEBUG*/xASSERT_RET(false == csReplyDelimiter.empty(), false);

    bool        bRes = false;
    std::string sRes = "";

    bRes = _m_scktSocket.bSendAll(csCmd, 0);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    sRes = _m_scktSocket.sRecvAll(0, csReplyDelimiter);
    /*DEBUG*/xASSERT_MSG_RET(false == _bIsError(sRes), sRes.c_str(), false);

    sReply = sRes;

#ifdef _DEBUG
    /*DEBUG*/_m_ConsoleLog.bWrite("Command :  %s          Response: %s\n", csCmd.c_str(), sRes.c_str());
#endif

    return true;
}
//---------------------------------------------------------------------------
//DONE: _bIsError
bool
CxSmtp::_bIsError(const std::string &csText) {
    /*DEBUG*/xASSERT_RET(false == csText.empty(), true);

    bool bRes = (bool)!(
            !std::memcmp(csText.c_str(), "334", 3) ||    //334 VXNlcm5hbWU6
            !std::memcmp(csText.c_str(), "235", 3) ||    //235 2.0.0 Authentication successful
            !std::memcmp(csText.c_str(), "220", 3) ||    //220 Sergey Kerio MailServer 6.7.0 patch 1 ESMTP ready
            !std::memcmp(csText.c_str(), "250", 3) ||    //250 2.0.0 OK
            !std::memcmp(csText.c_str(), "354", 3) ||    //354 Enter mail, end with CRLF.CRLF
            !std::memcmp(csText.c_str(), "221", 3)        //221 221 2.0.0 SMTP closing connection
    );

    return bRes;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
