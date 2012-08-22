/**
 * \file  CxPop3.cpp
 * \brief POP3
 */


#include <xLib/Net/CxPop3.h>

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
    _m_clLog     (false),
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
CxPop3::bCreate(const std::tstring_t &csUser, const std::tstring_t &csPass, const std::tstring_t &csServer, ushort_t usPort) {
     /*DEBUG*/xASSERT_RET(false == csUser.empty(),          false);
     /*DEBUG*/xASSERT_RET(false == csPass.empty(),          false);
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
     /*DEBUG*/xASSERT_MSG_RET(false == _bIsError(_m_sRes), _m_sRes.c_str(), false); //��� "+OK"

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
CxPop3::bStat(ulong_t &ulSum, ulong_t &ulSize) {
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

    ulSum  = _ulMailsSum (_m_sRes);
    ulSize = _ulMailsSize(_m_sRes);

#ifdef _DEBUG
    //+OK 2 1141841
    /*DEBUG*/_m_clLog.bWrite("Recv STAT Resp: MailsSum  = %u\n", ulSum);
    /*DEBUG*/_m_clLog.bWrite("Recv STAT Resp: MailsSize = %u\n", ulSize);
#endif

    return true;
}
//---------------------------------------------------------------------------
//TODO: bList (������ ��������, ������ �� �������)
bool
CxPop3::bList(std::vector<ulong_t> &veculList) {
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
CxPop3::bListAt(ulong_t &ulIndex) {
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
CxPop3::bTop(int iNum, int iLines, std::tstring_t &sBuff) {
    /*DEBUG*/xASSERT_RET(iNum   > 0,   false);
    /*DEBUG*/xASSERT_RET(iLines > - 1, false);

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
    std::tstring_t sTopCmd = "TOP " + CxString::lexical_cast(iNum) + " " + CxString::lexical_cast(iLines) + "\r\n";

    bool bRv = _bCommand(sTopCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    sBuff = _m_sRes;

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRetriveRaw ()
bool
CxPop3::bRetriveRaw(int iNum, const std::tstring_t &csDirPath, const std::tstring_t &csFileName) {  //csDirPath ��� �����
    /*DEBUG*/xASSERT_RET(iNum > 0,                    false);
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  false);
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), false);

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
    const std::tstring_t sRetrCmd = "RETR " + CxString::lexical_cast(iNum) + "\r\n";

    bool bRv = _bCommand(sRetrCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t uiOkPos      = _m_sRes.find("+OK");
    size_t uiFirstCRPos = _m_sRes.find("\r\n");
    if (std::tstring_t::npos != uiOkPos && 0 == uiOkPos && std::tstring_t::npos != uiFirstCRPos) {
        _m_sRes.erase(uiOkPos, uiFirstCRPos - uiOkPos + 2);    //"\r\n - 2 c������"
    } else {
        /*DEBUG*/xASSERT(false);
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t uiEndOfMessagePos = _m_sRes.rfind("\r\n.\r\n");
    if (std::tstring_t::npos != uiEndOfMessagePos) {
        _m_sRes.erase(uiEndOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        /*DEBUG*/xASSERT(false);
    }

    //-------------------------------------
    //��������� ���� �� ����
    CxFile stdFile;

    bRv = stdFile.bCreate(csDirPath + "\\" + csFileName, CxFile::omBinWrite, true);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    size_t uiWriteSize = stdFile.uiWrite(&_m_sRes[0], _m_sRes.size());
    /*DEBUG*///???
    xUNUSED(uiWriteSize);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRetriveRawAndBackup ()
bool
CxPop3::bRetriveRawAndBackup(int iNum, const std::tstring_t &csDirPath, const std::tstring_t &csBackupDirPath, const std::tstring_t &csFileName) {
    /*DEBUG*/xASSERT_RET(iNum > 0,                                                         false);
    /*DEBUG*/xASSERT_RET(! (true == csDirPath.empty() && true == csBackupDirPath.empty()), false);
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(),                                      false);

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
    const std::tstring_t sRetrCmd = "RETR " + CxString::lexical_cast(iNum) + "\r\n";

    bool bRv = _bCommand(sRetrCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t uiOkPos      = _m_sRes.find("+OK");
    size_t uiFirstCRPos = _m_sRes.find("\r\n");
    if (std::tstring_t::npos != uiOkPos && 0 == uiOkPos && std::tstring_t::npos != uiFirstCRPos) {
        _m_sRes.erase(uiOkPos, uiFirstCRPos - uiOkPos + 2);    //"\r\n - 2 c������"
    } else {
        /*DEBUG*/xASSERT(false);
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t uiEndOfMessagePos = _m_sRes.rfind("\r\n.\r\n");
    if (std::tstring_t::npos != uiEndOfMessagePos) {
        _m_sRes.erase(uiEndOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        /*DEBUG*/xASSERT(false);
    }

    //-------------------------------------
    //��������� ���� �� ���� (��������), ���� ���� ���� - �� ���������
    if (false == csDirPath.empty()) {
        CxFile stdfOriginal;

        bRv = stdfOriginal.bCreate(csDirPath + "\\" + csFileName, CxFile::omBinWrite, true);
        xCHECK_RET(false == bRv, false);

        size_t uiOriginalWriteSize = stdfOriginal.uiWrite(&_m_sRes[0], _m_sRes.size());
        xCHECK_RET(0 == uiOriginalWriteSize, false);
    }

    //-------------------------------------
    //��������� ���� �� ���� (�����), ���� ���� ���� - �� ���������
    if (false == csBackupDirPath.empty()) {
        CxFile stdfBackup;

        bRv = stdfBackup.bCreate(csBackupDirPath + "\\" + csFileName, CxFile::omBinWrite, true);
        xCHECK_RET(false == bRv, false);

        size_t uiBackupWriteSize = stdfBackup.uiWrite(&_m_sRes[0], _m_sRes.size());
        xCHECK_RET(0 == uiBackupWriteSize, false);
    }

    return true;
}
//---------------------------------------------------------------------------
//DONE: bRetrieveHeader ()
bool
CxPop3::bRetrieveHeader(int iNum, CxMimeHeader &mhMimeHeader) {
    /*DEBUG*/xASSERT_RET(iNum > 0, false);

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
    std::tstring_t sTopCmd = "TOP " + CxString::lexical_cast(iNum) + " " + "0" + "\r\n";

    bool bRv = _bCommand(sTopCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(false == bRv, false);

    //-------------------------------------
    //������ �����
    mhMimeHeader.bParse(_m_sRes);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bDelete (������� ������)
bool
CxPop3::bDelete(int iNum) {
    /*DEBUG*/xASSERT_RET(iNum > 0, false);

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
    const std::tstring_t sDeleCmd = "DELE " + CxString::lexical_cast(iNum) + "\r\n";

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
CxPop3::_ulMailsSum(const std::tstring_t &csServerAnswer) {
    /*DEBUG*/xASSERT_RET(false == csServerAnswer.empty(), false);

    //+OK 2 1141841
    ulong_t                     ulSum = 0UL;
    std::tstring_t              sSum;
    std::vector<std::tstring_t> vsRes;

    bool bRv = CxString::bSplit(csServerAnswer, " ", &vsRes);
    /*DEBUG*/xASSERT_RET(true == bRv, 0UL);

    sSum  = vsRes.at(1);
    ulSum = ::atol(sSum.c_str());        // ul -> l

    return ulSum;
}
//---------------------------------------------------------------------------
//DONE: _ulMailsSize (����� ������ ����� � ������)
ulong_t
CxPop3::_ulMailsSize(const std::tstring_t &csServerAnswer) {
    /*DEBUG*/xASSERT_RET(false == csServerAnswer.empty(), false);

    //+OK 2 1141841
    ulong_t        ulSize = 0;
    std::tstring_t sSize;
    std::vector<std::tstring_t> vsRes;

    bool bRv = CxString::bSplit(csServerAnswer, " ", &vsRes);
    /*DEBUG*/xASSERT_RET(true == bRv, 0UL);

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
    /*DEBUG*/xASSERT_RET(false == csCmd.empty(),            false);
    /*DEBUG*/xASSERT_RET(false == csReplyDelimiter.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != psReply,                  false);

    bool bRv = _m_scktSocket.bSendAll(csCmd, 0);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

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
    /*DEBUG*/xASSERT_RET(false == csText.empty(), true);

    if (0 == std::memcmp(csText.c_str(), "+OK", 3)) {
        return false;
    }
    if (0 == std::memcmp(csText.c_str(), "-ERR", 4)) {
        return true;
    }

    /*DEBUG*/xASSERT_RET(false, true);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
