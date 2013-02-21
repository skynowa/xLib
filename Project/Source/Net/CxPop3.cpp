/**
 * \file  CxPop3.cpp
 * \brief POP3
 */


#include <xLib/Net/CxPop3.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
//DONE: CxPop3
CxPop3::CxPop3() :
    _m_sRes      (),
    ////_m_siInit    (2, 2),
    _m_scktSocket(),
    _m_sUser     (),
    _m_sPass     (),
    _m_sServer   (),
    _m_usPort    (0),
    _m_bConnected(false)
{
}
//------------------------------------------------------------------------------
//DONE: ~CxPop3
CxPop3::~CxPop3() {
    disconnect();
}
//------------------------------------------------------------------------------
//DONE: bCreate
void
CxPop3::create(const std::tstring_t &a_csUser, const std::tstring_t &a_csPass, const std::tstring_t &a_csServer, ushort_t a_usPort) {
     xTEST_EQ(false, a_csUser.empty());
     xTEST_EQ(false, a_csPass.empty());
     xTEST_EQ(false, a_csServer.empty());
     xTEST_EQ(true, (32767 > a_usPort) && (0 < a_usPort));

     _m_sUser   = a_csUser;
     _m_sPass   = a_csPass;
     _m_sServer = a_csServer;
     _m_usPort  = a_usPort;
}
//------------------------------------------------------------------------------
//DONE: bConnect
void
CxPop3::connect() {
     //-------------------------------------
     //Create sock
     _m_scktSocket.create(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

     //-------------------------------------
     //Parse domain
     std::tstring_t sIp;

     CxDnsClient::hostAddrByName(_m_sServer, &sIp);

     //-------------------------------------
     //Connect
     _m_scktSocket.connect(sIp, _m_usPort);

     //-------------------------------------
     //[welcome message]
     _m_sRes = _m_scktSocket.recvAll(0, xT("\r\n"));
     xTEST_MSG_EQ(false, _isError(_m_sRes), _m_sRes); // "+OK"

    _m_bConnected = true;
 }
//------------------------------------------------------------------------------
//DONE: bLogin
void
CxPop3::login() {
    //-------------------------------------
    //RFC
    /*
    �: USER frated
    S: -ERR sorry, no mailbox for frated here

    ���

    �: USER mrose
    S: +OK mrose is a real hoopy frood
    */

    /*
    �: USER mrose
    S: +OK mrose is a real hoopy frood
    �: PASS secret
    S: -ERR maildrop already locked

    ���

    �: USER mrose
    S: +OK mrose is a real hoopy frood
    C: PASS secret
    S: +OK mrose's maildrop has 2 messages (320 octets)
    */

    //-------------------------------------
    //[USER user\r\n]
    const std::tstring_t sUserCmd = xT("USER ") + _m_sUser + xT("\r\n");

    _command(sUserCmd, xT("\r\n"), &_m_sRes);

    //-------------------------------------
    //[PASS\r\n]
    std::tstring_t sPassCmd = xT("PASS ") + _m_sPass + xT("\r\n");

    _command(sPassCmd, xT("\r\n"), &_m_sRes);
}
//------------------------------------------------------------------------------
//DONE: bStat
void
CxPop3::stat(ulong_t &a_ulSum, ulong_t &a_ulSize) {
    //-------------------------------------
    //RFC
    /*
    �: STAT
    S: +�� 2 320
    */

    //-------------------------------------
    //[LIST\r\n]
    const std::tstring_t sStatCmd = xT("STAT\r\n");

    _command(sStatCmd, xT("\r\n"), &_m_sRes);

    a_ulSum  = _mailsSum (_m_sRes);
    a_ulSize = _mailsSize(_m_sRes);

#if 0
    //+OK 2 1141841
    _m_clLog.bWrite("Recv STAT Resp: MailsSum  = %u\n", a_ulSum);
    _m_clLog.bWrite("Recv STAT Resp: MailsSize = %u\n", a_ulSize);
#endif
}
//------------------------------------------------------------------------------
//TODO: bList (������ ��������, ������ �� �������)
void
CxPop3::list(std::vector<ulong_t> &a_veculList) {
    //-------------------------------------
    //RFC
    /*
    �: LIST
    S: +�� 2 messages (320 octets)
    S: 1 120
    S: 2 200
    S: .

    ���

    �: LIST 2
    S: +�� 2 200

    ���

    �: LIST 3
    S: -ERR no such message, only 2 messages in maildrop
    */

    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//TODO: bListAt (������ ������ � �������� ulIndex)
void
CxPop3::listAt(ulong_t &a_ulIndex) {
    //-------------------------------------
    //RFC
    /*
    �: LIST
    S: +�� 2 messages (320 octets)
    S: 1 120
    S: 2 200
    S: .

    ���

    �: LIST 2
    S: +�� 2 200

    ���

    �: LIST 3
    S: -ERR no such message, only 2 messages in maildrop
    */

    xNOT_IMPLEMENTED;
}
//------------------------------------------------------------------------------
//DONE: bNoop (�������� ��������� ���������� � ����)
void
CxPop3::noop() {
    //-------------------------------------
    //RFC
    /*
    �: NOOP
    S: +��
    */

    //-------------------------------------
    //[NOOP\r\n]
    std::tstring_t sNoopCmd = xT("NOOP\r\n");

    _command(sNoopCmd, xT("\r\n"), &_m_sRes);
}
//------------------------------------------------------------------------------
//DONE: bRset (������ ����� �������� �����)
void
CxPop3::rset() {
    //-------------------------------------
    //RFC
    /*
    �: RSET
    S: +OK maildrop has 2 messages (320 octets)
    */

    //-------------------------------------
    //[RSET\r\n]
    std::tstring_t sRsetCmd = xT("RSET\r\n");

    _command(sRsetCmd, xT("\r\n"), &_m_sRes);
}
//------------------------------------------------------------------------------
//DONE: bTop (�������� ��������� ������)
void
CxPop3::top(int a_iNum, int a_iLines, std::tstring_t &a_sBuff) {
    xTEST_GR(a_iNum, 0);
    xTEST_GR(a_iLines,- 1);

    //-------------------------------------
    //RFC
    /*
    � ��� 1 10
    S +OK
    S <header>
    S <blank>
    S <message body>
    S .
    */

    //-------------------------------------
    //[TOP 1 10\r\n]
    std::tstring_t sTopCmd = xT("TOP ") + CxString::cast(a_iNum) + xT(" ") + CxString::cast(a_iLines) + xT("\r\n");

    _command(sTopCmd, xT("\r\n.\r\n"), &_m_sRes);

    a_sBuff = _m_sRes;
}
//------------------------------------------------------------------------------
//DONE: bRetriveRaw ()
void
CxPop3::retriveRaw(int a_iNum, const std::tstring_t &a_csDirPath, const std::tstring_t &a_csFileName) {  //csDirPath ��� �����
    xTEST_GR(a_iNum, 0);
    xTEST_EQ(false, a_csDirPath.empty());
    xTEST_EQ(false, a_csFileName.empty());

    //-------------------------------------
    //RFC
    /*
    �: RETR 1
    S: +�� 120 octets
    S: <text message>
    S: .
    */

    //-------------------------------------
    //[RETR 3\r\n]
    const std::tstring_t sRetrCmd = xT("RETR ") + CxString::cast(a_iNum) + xT("\r\n");

    _command(sRetrCmd, xT("\r\n.\r\n"), &_m_sRes);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t uiOkPos      = _m_sRes.find(xT("+OK"));
    size_t uiFirstCRPos = _m_sRes.find(xT("\r\n"));
    if (std::tstring_t::npos != uiOkPos && 0 == uiOkPos && std::tstring_t::npos != uiFirstCRPos) {
        _m_sRes.erase(uiOkPos, uiFirstCRPos - uiOkPos + 2);    //"\r\n - 2 c������"
    } else {
        xTEST_FAIL;
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t uiEndOfMessagePos = _m_sRes.rfind(xT("\r\n.\r\n"));
    if (std::tstring_t::npos != uiEndOfMessagePos) {
        _m_sRes.erase(uiEndOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        xTEST_FAIL;
    }

    //-------------------------------------
    //��������� ���� �� ����
    CxFile stdFile;

    stdFile.create(a_csDirPath + xT("\\") + a_csFileName, CxFile::omBinWrite, true);

    size_t uiWriteSize = stdFile.write((const void *)&_m_sRes[0], _m_sRes.size());
    //???
    xUNUSED(uiWriteSize);
}
//------------------------------------------------------------------------------
//DONE: bRetriveRawAndBackup ()
void
CxPop3::retriveRawAndBackup(int a_iNum, const std::tstring_t &a_csDirPath, const std::tstring_t &a_csBackupDirPath, const std::tstring_t &a_csFileName) {
    xTEST_GR(a_iNum, 0);
    xTEST_EQ(false, (true == a_csDirPath.empty() && true == a_csBackupDirPath.empty()));
    xTEST_EQ(false, a_csFileName.empty());

    //-------------------------------------
    //RFC
    /*
    �: RETR 1
    S: +�� 120 octets
    S: <text message>
    S: .
    */

    //-------------------------------------
    //[RETR 3\r\n]
    const std::tstring_t sRetrCmd = xT("RETR ") + CxString::cast(a_iNum) + xT("\r\n");

    _command(sRetrCmd, xT("\r\n.\r\n"), &_m_sRes);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t uiOkPos      = _m_sRes.find(xT("+OK"));
    size_t uiFirstCRPos = _m_sRes.find(xT("\r\n"));
    if (std::tstring_t::npos != uiOkPos && 0 == uiOkPos && std::tstring_t::npos != uiFirstCRPos) {
        _m_sRes.erase(uiOkPos, uiFirstCRPos - uiOkPos + 2);    //"\r\n - 2 c������"
    } else {
        xTEST_FAIL;
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t uiEndOfMessagePos = _m_sRes.rfind(xT("\r\n.\r\n"));
    if (std::tstring_t::npos != uiEndOfMessagePos) {
        _m_sRes.erase(uiEndOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        xTEST_FAIL;
    }

    //-------------------------------------
    //��������� ���� �� ���� (��������), ���� ���� ���� - �� ���������
    if (false == a_csDirPath.empty()) {
        CxFile stdfOriginal;

        stdfOriginal.create(a_csDirPath + xT("\\") + a_csFileName, CxFile::omBinWrite, true);

        size_t uiOriginalWriteSize = stdfOriginal.write((const void *)&_m_sRes[0], _m_sRes.size());
        xTEST_DIFF(size_t(0), uiOriginalWriteSize);
    }

    //-------------------------------------
    //��������� ���� �� ���� (�����), ���� ���� ���� - �� ���������
    if (false == a_csBackupDirPath.empty()) {
        CxFile stdfBackup;

        stdfBackup.create(a_csBackupDirPath + xT("\\") + a_csFileName, CxFile::omBinWrite, true);

        size_t uiBackupWriteSize = stdfBackup.write((const void *)&_m_sRes[0], _m_sRes.size());
        xTEST_DIFF(size_t(0), uiBackupWriteSize);
    }
}
//------------------------------------------------------------------------------
//DONE: bRetrieveHeader ()
void
CxPop3::retrieveHeader(int a_iNum, CxMimeHeader &a_mhMimeHeader) {
    xTEST_LESS(a_iNum, 0);

    //-------------------------------------
    //RFC
    /*
    � ��� 1 10
    S +OK
    S <header>
    S <blank>
    S <message body>
    S .
    */

    //-------------------------------------
    //[TOP 1 0\r\n]
    std::tstring_t sTopCmd = xT("TOP ") + CxString::cast(a_iNum) + xT(" ") + xT("0") + xT("\r\n");

    _command(sTopCmd, xT("\r\n.\r\n"), &_m_sRes);

    //-------------------------------------
    //������ �����
    a_mhMimeHeader.parse(_m_sRes);
}
//------------------------------------------------------------------------------
//DONE: bDelete (������� ������)
void
CxPop3::del(int a_iNum) {
    xTEST_GR(a_iNum, 0);

    //-------------------------------------
    //RFC
    /*
    �: DELE 1
    S: +�� message 1 deleted

    ���

    �: DELE 2
    S: -ERR message 2 already deleted
    */

    std::tstring_t _m_sRes;

    //-------------------------------------
    //[DELE 2\r\n]
    const std::tstring_t sDeleCmd = xT("DELE ") + CxString::cast(a_iNum) + xT("\r\n");

    _command(sDeleCmd, xT("\r\n"), &_m_sRes);
}
//------------------------------------------------------------------------------
//DONE: bDisconnect (������������� �� �������)
void
CxPop3::disconnect() {
    xCHECK_DO(false == _m_bConnected, return);

    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    //-------------------------------------
    //[QUIT\r\n]
    const std::tstring_t sQuitCmd = xT("QUIT\r\n");

    _command(sQuitCmd, xT("\r\n"), &_m_sRes);

    _m_scktSocket.close();

    _m_bConnected = false;
}
//------------------------------------------------------------------------------
//DONE: _mailsSum (������� ����� �����)
ulong_t
CxPop3::_mailsSum(const std::tstring_t &a_csServerAnswer) {
    xTEST_EQ(false, a_csServerAnswer.empty());

    //+OK 2 1141841
    ulong_t            ulSum = 0UL;
    std::tstring_t     sSum;
    std::vec_tstring_t vsRes;

    CxString::split(a_csServerAnswer, xT(" "), &vsRes);

    sSum  = vsRes.at(1);
    ulSum = CxString::cast<ulong_t>( sSum );        // ul -> l

    return ulSum;
}
//------------------------------------------------------------------------------
//DONE: _mailsSize (����� ������ ����� � ������)
ulong_t
CxPop3::_mailsSize(const std::tstring_t &a_csServerAnswer) {
    xTEST_EQ(false, a_csServerAnswer.empty());

    //+OK 2 1141841
    ulong_t            ulSize = 0;
    std::tstring_t     sSize;
    std::vec_tstring_t vsRes;

    CxString::split(a_csServerAnswer, xT(" "), &vsRes);

    sSize  = vsRes.at(2);
    ulSize = CxString::cast<ulong_t>( sSize );    // ul+\r\n -> l

    return ulSize;
}
//------------------------------------------------------------------------------



/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
//DONE: _bCommand ()
void
CxPop3::_command(const std::tstring_t &csCmd, const std::tstring_t &csReplyDelimiter, std::tstring_t *psReply) {
    xTEST_EQ(false, csCmd.empty());
    xTEST_EQ(false, csReplyDelimiter.empty());
    xTEST_PTR(psReply);

    _m_scktSocket.sendAll(csCmd, 0);

    _m_sRes = _m_scktSocket.recvAll(0, csReplyDelimiter);
    ////xTEST_MSG_EQ(false, _bIsError(_m_sRes), _m_sRes);

    (*psReply) = _m_sRes;

#ifdef _DEBUG
    ////_m_clLog.bWrite("Command :  %s          Response: %s\n", csCmd.c_str(), _m_sRes.c_str());
#endif

    xTEST_EQ(false, _isError(_m_sRes));
}
//------------------------------------------------------------------------------
//DONE: _bIsError ()
bool
CxPop3::_isError(const std::tstring_t &csText) {
    xTEST_EQ(false, csText.empty());

    if (0 == std::memcmp(csText.c_str(), xT("+OK"), 3)) {
        return false;
    }
    if (0 == std::memcmp(csText.c_str(), xT("-ERR"), 4)) {
        return true;
    }

    xTEST_FAIL;

    return true;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
