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
    xCHECK_DO(true == _m_bConnected, bDisconnect());
}
//---------------------------------------------------------------------------
//DONE: bCreate
bool
CxPop3::bCreate(const std::tstring_t &a_csUser, const std::tstring_t &a_csPass, const std::tstring_t &a_csServer, ushort_t a_usPort) {
     /*DEBUG*/xTEST_EQ(false, a_csUser.empty());
     /*DEBUG*/xTEST_EQ(false, a_csPass.empty());
     /*DEBUG*/xTEST_EQ(false, a_csServer.empty());
     /*DEBUG*/xTEST_EQ(true, (32767 > a_usPort) && (0 < a_usPort));

     _m_sUser   = a_csUser;
     _m_sPass   = a_csPass;
     _m_sServer = a_csServer;
     _m_usPort  = a_usPort;

     return true;
}
//---------------------------------------------------------------------------
//DONE: bConnect
bool
CxPop3::bConnect() {
     //-------------------------------------
     //Create sock
     bool bRv = _m_scktSocket.bCreate(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);
     xCHECK_RET(false == bRv, false);

     //-------------------------------------
     //Parse domain
     std::tstring_t sIp;

     bRv = CxDnsClient::bGetHostAddrByName(_m_sServer, &sIp);
     xCHECK_RET(false == bRv, false);

     //-------------------------------------
     //Connect
     bRv = _m_scktSocket.bConnect(sIp, _m_usPort);
     xCHECK_RET(false == bRv, false);

     //-------------------------------------
     //[welcome message]
     _m_sRes = _m_scktSocket.sRecvAll(0, "\r\n");
     /*DEBUG*/xTEST_MSG_EQ(false, _bIsError(_m_sRes), _m_sRes); // "+OK"

    _m_bConnected = true;

     return true;
 }
//---------------------------------------------------------------------------
//DONE: bLogin
bool
CxPop3::bLogin() {
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

    bool bRv = _bCommand(sUserCmd, "\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //[PASS\r\n]
    std::tstring_t sPassCmd = "PASS " + _m_sPass + "\r\n";

    bRv = _bCommand(sPassCmd, "\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bStat
bool
CxPop3::bStat(ulong_t &a_ulSum, ulong_t &a_ulSize) {
    //-------------------------------------
    //RFC
    /*
    �: STAT
    S: +�� 2 320
    */

    //-------------------------------------
    //[LIST\r\n]
    const std::tstring_t sStatCmd = "STAT\r\n";

    bool bRv = _bCommand(sStatCmd, "\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    a_ulSum  = _ulMailsSum (_m_sRes);
    a_ulSize = _ulMailsSize(_m_sRes);

#if 0
    //+OK 2 1141841
    /*DEBUG*/_m_clLog.bWrite("Recv STAT Resp: MailsSum  = %u\n", a_ulSum);
    /*DEBUG*/_m_clLog.bWrite("Recv STAT Resp: MailsSize = %u\n", a_ulSize);
#endif

    return true;
}
//---------------------------------------------------------------------------
//TODO: bList (������ ��������, ������ �� �������)
bool
CxPop3::bList(std::vector<ulong_t> &a_veculList) {
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


    return false;
}
//---------------------------------------------------------------------------
//TODO: bListAt (������ ������ � �������� ulIndex)
bool
CxPop3::bListAt(ulong_t &a_ulIndex) {
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

    return false;
}
//---------------------------------------------------------------------------
//DONE: bNoop (�������� ��������� ���������� � ����)
bool
CxPop3::bNoop() {
    //-------------------------------------
    //RFC
    /*
    �: NOOP
    S: +��
    */

    //-------------------------------------
    //[NOOP\r\n]
    std::tstring_t sNoopCmd = "NOOP\r\n";

    bool bRv = _bCommand(sNoopCmd, "\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRset (������ ����� �������� �����)
bool
CxPop3::bRset() {
    //-------------------------------------
    //RFC
    /*
    �: RSET
    S: +OK maildrop has 2 messages (320 octets)
    */

    //-------------------------------------
    //[RSET\r\n]
    std::tstring_t sRsetCmd = "RSET\r\n";

    bool bRv = _bCommand(sRsetCmd, "\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bTop (�������� ��������� ������)
bool
CxPop3::bTop(int a_iNum, int a_iLines, std::tstring_t &a_sBuff) {
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

    bool bRv = _bCommand(sTopCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    a_sBuff = _m_sRes;

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRetriveRaw ()
bool
CxPop3::bRetriveRaw(int a_iNum, const std::tstring_t &a_csDirPath, const std::tstring_t &a_csFileName) {  //csDirPath ��� �����
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

    bool bRv = _bCommand(sRetrCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

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

    bRv = stdFile.bCreate(a_csDirPath + "\\" + a_csFileName, CxFile::omBinWrite, true);
    /*DEBUG*/xTEST_EQ(true, bRv);

    size_t uiWriteSize = stdFile.uiWrite(&_m_sRes[0], _m_sRes.size());
    /*DEBUG*///???
    xUNUSED(uiWriteSize);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRetriveRawAndBackup ()
bool
CxPop3::bRetriveRawAndBackup(int a_iNum, const std::tstring_t &a_csDirPath, const std::tstring_t &a_csBackupDirPath, const std::tstring_t &a_csFileName) {
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

    bool bRv = _bCommand(sRetrCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

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

        bRv = stdfOriginal.bCreate(a_csDirPath + "\\" + a_csFileName, CxFile::omBinWrite, true);
        xCHECK_RET(false == bRv, false);

        size_t uiOriginalWriteSize = stdfOriginal.uiWrite(&_m_sRes[0], _m_sRes.size());
        xCHECK_RET(0 == uiOriginalWriteSize, false);
    }

    //-------------------------------------
    //��������� ���� �� ���� (�����), ���� ���� ���� - �� ���������
    if (false == a_csBackupDirPath.empty()) {
        CxFile stdfBackup;

        bRv = stdfBackup.bCreate(a_csBackupDirPath + "\\" + a_csFileName, CxFile::omBinWrite, true);
        xCHECK_RET(false == bRv, false);

        size_t uiBackupWriteSize = stdfBackup.uiWrite(&_m_sRes[0], _m_sRes.size());
        xCHECK_RET(0 == uiBackupWriteSize, false);
    }

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRetrieveHeader ()
bool
CxPop3::bRetrieveHeader(int a_iNum, CxMimeHeader &a_mhMimeHeader) {
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

    bool bRv = _bCommand(sTopCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //������ �����
    a_mhMimeHeader.bParse(_m_sRes);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bDelete (������� ������)
bool
CxPop3::bDelete(int a_iNum) {
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

    bool bRv = _bCommand(sDeleCmd, "\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bDisconnect (������������� �� �������)
bool
CxPop3::bDisconnect() {
    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    //-------------------------------------
    //[QUIT\r\n]
    const std::tstring_t sQuitCmd = "QUIT\r\n";

    bool bRv = _bCommand(sQuitCmd, "\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    bRv = _m_scktSocket.bClose();
    xCHECK_RET(false == bRv, false);

    _m_bConnected = false;

    return true;
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

    bool bRv = CxString::bSplit(a_csServerAnswer, " ", &vsRes);
    /*DEBUG*/xTEST_EQ(true, bRv);

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

    bool bRv = CxString::bSplit(a_csServerAnswer, " ", &vsRes);
    /*DEBUG*/xTEST_EQ(true, bRv);

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
bool
CxPop3::_bCommand(const std::tstring_t &csCmd, const std::tstring_t &csReplyDelimiter, std::tstring_t *psReply) {
    /*DEBUG*/xTEST_EQ(false, csCmd.empty());
    /*DEBUG*/xTEST_EQ(false, csReplyDelimiter.empty());
    /*DEBUG*/xTEST_PTR(psReply);

    bool bRv = _m_scktSocket.bSendAll(csCmd, 0);
    /*DEBUG*/xTEST_EQ(true, bRv);

    _m_sRes = _m_scktSocket.sRecvAll(0, csReplyDelimiter);
    /*DEBUG*/////xASSERT_MSG_RET(false == _bIsError(_m_sRes), _m_sRes.c_str(), false);

    (*psReply) = _m_sRes;

#ifdef _DEBUG
    /*DEBUG*/////_m_clLog.bWrite("Command :  %s          Response: %s\n", csCmd.c_str(), _m_sRes.c_str());
#endif

    return (! _bIsError(_m_sRes)/*true*/);
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
