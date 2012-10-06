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

/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//DONE: ~CxPop3
CxPop3::~CxPop3() {
    vDisconnect();
}
//---------------------------------------------------------------------------
//DONE: bCreate
void
CxPop3::vCreate(const std::tstring_t &a_csUser, const std::tstring_t &a_csPass, const std::tstring_t &a_csServer, ushort_t a_usPort) {
     /*DEBUG*/xTEST_EQ(false, a_csUser.empty());
     /*DEBUG*/xTEST_EQ(false, a_csPass.empty());
     /*DEBUG*/xTEST_EQ(false, a_csServer.empty());
     /*DEBUG*/xTEST_EQ(true, (32767 > a_usPort) && (0 < a_usPort));

     _m_sUser   = a_csUser;
     _m_sPass   = a_csPass;
     _m_sServer = a_csServer;
     _m_usPort  = a_usPort;
}
//---------------------------------------------------------------------------
//DONE: bConnect
void
CxPop3::vConnect() {
     //-------------------------------------
     //Create sock
     _m_scktSocket.vCreate(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

     //-------------------------------------
     //Parse domain
     std::tstring_t sIp;

     CxDnsClient::vGetHostAddrByName(_m_sServer, &sIp);

     //-------------------------------------
     //Connect
     _m_scktSocket.vConnect(sIp, _m_usPort);

     //-------------------------------------
     //[welcome message]
     _m_sRes = _m_scktSocket.sRecvAll(0, "\r\n");
     /*DEBUG*/xTEST_MSG_EQ(false, _bIsError(_m_sRes), _m_sRes); // "+OK"

    _m_bConnected = true;
 }
//---------------------------------------------------------------------------
//DONE: bLogin
void
CxPop3::vLogin() {
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
    const std::tstring_t sUserCmd = "USER " + _m_sUser + "\r\n";

    _vCommand(sUserCmd, "\r\n", &_m_sRes);

    //-------------------------------------
    //[PASS\r\n]
    std::tstring_t sPassCmd = "PASS " + _m_sPass + "\r\n";

    _vCommand(sPassCmd, "\r\n", &_m_sRes);
}
//---------------------------------------------------------------------------
//DONE: bStat
void
CxPop3::vStat(ulong_t &a_ulSum, ulong_t &a_ulSize) {
    //-------------------------------------
    //RFC
    /*
    �: STAT
    S: +�� 2 320
    */

    //-------------------------------------
    //[LIST\r\n]
    const std::tstring_t sStatCmd = "STAT\r\n";

    _vCommand(sStatCmd, "\r\n", &_m_sRes);

    a_ulSum  = _ulMailsSum (_m_sRes);
    a_ulSize = _ulMailsSize(_m_sRes);

#if 0
    //+OK 2 1141841
    /*DEBUG*/_m_clLog.bWrite("Recv STAT Resp: MailsSum  = %u\n", a_ulSum);
    /*DEBUG*/_m_clLog.bWrite("Recv STAT Resp: MailsSize = %u\n", a_ulSize);
#endif
}
//---------------------------------------------------------------------------
//TODO: bList (������ ��������, ������ �� �������)
void
CxPop3::vList(std::vector<ulong_t> &a_veculList) {
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
//---------------------------------------------------------------------------
//TODO: bListAt (������ ������ � �������� ulIndex)
void
CxPop3::vListAt(ulong_t &a_ulIndex) {
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
//---------------------------------------------------------------------------
//DONE: bNoop (�������� ��������� ���������� � ����)
void
CxPop3::vNoop() {
    //-------------------------------------
    //RFC
    /*
    �: NOOP
    S: +��
    */

    //-------------------------------------
    //[NOOP\r\n]
    std::tstring_t sNoopCmd = "NOOP\r\n";

    _vCommand(sNoopCmd, "\r\n", &_m_sRes);
}
//---------------------------------------------------------------------------
//DONE: bRset (������ ����� �������� �����)
void
CxPop3::vRset() {
    //-------------------------------------
    //RFC
    /*
    �: RSET
    S: +OK maildrop has 2 messages (320 octets)
    */

    //-------------------------------------
    //[RSET\r\n]
    std::tstring_t sRsetCmd = "RSET\r\n";

    _vCommand(sRsetCmd, "\r\n", &_m_sRes);
}
//---------------------------------------------------------------------------
//DONE: bTop (�������� ��������� ������)
void
CxPop3::vTop(int a_iNum, int a_iLines, std::tstring_t &a_sBuff) {
    /*DEBUG*/xTEST_GR(a_iNum, 0);
    /*DEBUG*/xTEST_GR(a_iLines,- 1);

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
    std::tstring_t sTopCmd = "TOP " + CxString::string_cast(a_iNum) + " " + CxString::string_cast(a_iLines) + "\r\n";

    _vCommand(sTopCmd, "\r\n.\r\n", &_m_sRes);

    a_sBuff = _m_sRes;
}
//---------------------------------------------------------------------------
//DONE: bRetriveRaw ()
void
CxPop3::vRetriveRaw(int a_iNum, const std::tstring_t &a_csDirPath, const std::tstring_t &a_csFileName) {  //csDirPath ��� �����
    /*DEBUG*/xTEST_GR(a_iNum, 0);
    /*DEBUG*/xTEST_EQ(false, a_csDirPath.empty());
    /*DEBUG*/xTEST_EQ(false, a_csFileName.empty());

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
    const std::tstring_t sRetrCmd = "RETR " + CxString::string_cast(a_iNum) + "\r\n";

    _vCommand(sRetrCmd, "\r\n.\r\n", &_m_sRes);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t uiOkPos      = _m_sRes.find("+OK");
    size_t uiFirstCRPos = _m_sRes.find("\r\n");
    if (std::tstring_t::npos != uiOkPos && 0 == uiOkPos && std::tstring_t::npos != uiFirstCRPos) {
        _m_sRes.erase(uiOkPos, uiFirstCRPos - uiOkPos + 2);    //"\r\n - 2 c������"
    } else {
        /*DEBUG*/xTEST_FAIL;
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t uiEndOfMessagePos = _m_sRes.rfind("\r\n.\r\n");
    if (std::tstring_t::npos != uiEndOfMessagePos) {
        _m_sRes.erase(uiEndOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        /*DEBUG*/xTEST_FAIL;
    }

    //-------------------------------------
    //��������� ���� �� ����
    CxFile stdFile;

    stdFile.vCreate(a_csDirPath + "\\" + a_csFileName, CxFile::omBinWrite, true);

    size_t uiWriteSize = stdFile.uiWrite(&_m_sRes[0], _m_sRes.size());
    /*DEBUG*///???
    xUNUSED(uiWriteSize);
}
//---------------------------------------------------------------------------
//DONE: bRetriveRawAndBackup ()
void
CxPop3::vRetriveRawAndBackup(int a_iNum, const std::tstring_t &a_csDirPath, const std::tstring_t &a_csBackupDirPath, const std::tstring_t &a_csFileName) {
    /*DEBUG*/xTEST_GR(a_iNum, 0);
    /*DEBUG*/xTEST_EQ(false, (true == a_csDirPath.empty() && true == a_csBackupDirPath.empty()));
    /*DEBUG*/xTEST_EQ(false, a_csFileName.empty());

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
    const std::tstring_t sRetrCmd = "RETR " + CxString::string_cast(a_iNum) + "\r\n";

    _vCommand(sRetrCmd, "\r\n.\r\n", &_m_sRes);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t uiOkPos      = _m_sRes.find("+OK");
    size_t uiFirstCRPos = _m_sRes.find("\r\n");
    if (std::tstring_t::npos != uiOkPos && 0 == uiOkPos && std::tstring_t::npos != uiFirstCRPos) {
        _m_sRes.erase(uiOkPos, uiFirstCRPos - uiOkPos + 2);    //"\r\n - 2 c������"
    } else {
        /*DEBUG*/xTEST_FAIL;
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t uiEndOfMessagePos = _m_sRes.rfind("\r\n.\r\n");
    if (std::tstring_t::npos != uiEndOfMessagePos) {
        _m_sRes.erase(uiEndOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        /*DEBUG*/xTEST_FAIL;
    }

    //-------------------------------------
    //��������� ���� �� ���� (��������), ���� ���� ���� - �� ���������
    if (false == a_csDirPath.empty()) {
        CxFile stdfOriginal;

        stdfOriginal.vCreate(a_csDirPath + "\\" + a_csFileName, CxFile::omBinWrite, true);

        size_t uiOriginalWriteSize = stdfOriginal.uiWrite(&_m_sRes[0], _m_sRes.size());
        xTEST_DIFF(size_t(0), uiOriginalWriteSize);
    }

    //-------------------------------------
    //��������� ���� �� ���� (�����), ���� ���� ���� - �� ���������
    if (false == a_csBackupDirPath.empty()) {
        CxFile stdfBackup;

        stdfBackup.vCreate(a_csBackupDirPath + "\\" + a_csFileName, CxFile::omBinWrite, true);

        size_t uiBackupWriteSize = stdfBackup.uiWrite(&_m_sRes[0], _m_sRes.size());
        xTEST_DIFF(size_t(0), uiBackupWriteSize);
    }
}
//---------------------------------------------------------------------------
//DONE: bRetrieveHeader ()
void
CxPop3::vRetrieveHeader(int a_iNum, CxMimeHeader &a_mhMimeHeader) {
    /*DEBUG*/xTEST_LESS(a_iNum, 0);

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
    std::tstring_t sTopCmd = "TOP " + CxString::string_cast(a_iNum) + " " + "0" + "\r\n";

    _vCommand(sTopCmd, "\r\n.\r\n", &_m_sRes);

    //-------------------------------------
    //������ �����
    a_mhMimeHeader.vParse(_m_sRes);
}
//---------------------------------------------------------------------------
//DONE: bDelete (������� ������)
void
CxPop3::vDelete(int a_iNum) {
    /*DEBUG*/xTEST_GR(a_iNum, 0);

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
    const std::tstring_t sDeleCmd = "DELE " + CxString::string_cast(a_iNum) + "\r\n";

    _vCommand(sDeleCmd, "\r\n", &_m_sRes);
}
//---------------------------------------------------------------------------
//DONE: bDisconnect (������������� �� �������)
void
CxPop3::vDisconnect() {
    xCHECK_DO(false == _m_bConnected, return);

    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    //-------------------------------------
    //[QUIT\r\n]
    const std::tstring_t sQuitCmd = "QUIT\r\n";

    _vCommand(sQuitCmd, "\r\n", &_m_sRes);

    _m_scktSocket.vClose();

    _m_bConnected = false;
}
//---------------------------------------------------------------------------
//DONE: _ulMailsSum (������� ����� �����)
ulong_t
CxPop3::_ulMailsSum(const std::tstring_t &a_csServerAnswer) {
    /*DEBUG*/xTEST_EQ(false, a_csServerAnswer.empty());

    //+OK 2 1141841
    ulong_t            ulSum = 0UL;
    std::tstring_t     sSum;
    std::vec_tstring_t vsRes;

    CxString::vSplit(a_csServerAnswer, " ", &vsRes);

    sSum  = vsRes.at(1);
    ulSum = ::atol(sSum.c_str());        // ul -> l

    return ulSum;
}
//---------------------------------------------------------------------------
//DONE: _ulMailsSize (����� ������ ����� � ������)
ulong_t
CxPop3::_ulMailsSize(const std::tstring_t &a_csServerAnswer) {
    /*DEBUG*/xTEST_EQ(false, a_csServerAnswer.empty());

    //+OK 2 1141841
    ulong_t            ulSize = 0;
    std::tstring_t     sSize;
    std::vec_tstring_t vsRes;

    CxString::vSplit(a_csServerAnswer, " ", &vsRes);

    sSize  = vsRes.at(2);
    ulSize = ::atol(sSize.c_str());    // ul+\r\n -> l

    return ulSize;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bCommand ()
void
CxPop3::_vCommand(const std::tstring_t &csCmd, const std::tstring_t &csReplyDelimiter, std::tstring_t *psReply) {
    /*DEBUG*/xTEST_EQ(false, csCmd.empty());
    /*DEBUG*/xTEST_EQ(false, csReplyDelimiter.empty());
    /*DEBUG*/xTEST_PTR(psReply);

    _m_scktSocket.vSendAll(csCmd, 0);

    _m_sRes = _m_scktSocket.sRecvAll(0, csReplyDelimiter);
    /*DEBUG*/////xTEST_MSG_EQ(false, _bIsError(_m_sRes), _m_sRes);

    (*psReply) = _m_sRes;

#ifdef _DEBUG
    /*DEBUG*/////_m_clLog.bWrite("Command :  %s          Response: %s\n", csCmd.c_str(), _m_sRes.c_str());
#endif

    xTEST_EQ(false, _bIsError(_m_sRes));
}
//---------------------------------------------------------------------------
//DONE: _bIsError ()
bool
CxPop3::_bIsError(const std::tstring_t &csText) {
    /*DEBUG*/xTEST_EQ(false, csText.empty());

    if (0 == std::memcmp(csText.c_str(), "+OK", 3)) {
        return false;
    }
    if (0 == std::memcmp(csText.c_str(), "-ERR", 4)) {
        return true;
    }

    /*DEBUG*/xTEST_FAIL;

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
