/****************************************************************************
* Class name:  CxPop3
* Description: POP3
* File name:   CxPop3.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     13.04.2009 16:44:49
*
*****************************************************************************/


#include <xLib/Net/CxPop3.h>

#include <xLib/Filesystem/CxStdioFile.h>


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxPop3
CxPop3::CxPop3() :
    _m_bRes      (FALSE),
    _m_sRes      (),
    ////_m_siInit    (2, 2),
    _m_scktSocket(),
    _m_clLog     (FALSE),
    _m_sUser     (),
    _m_sPass     (),
    _m_sServer   (),
    _m_usPort    (0),
    _m_bConnected(FALSE)
{
}
//---------------------------------------------------------------------------
//DONE: ~CxPop3
CxPop3::~CxPop3() {
    xCHECK_DO(TRUE == _m_bConnected, bDisconnect());
}
//---------------------------------------------------------------------------
//DONE: bCreate
BOOL CxPop3::bCreate(const tString &csUser, const tString &csPass, const tString &csServer, USHORT usPort) {
     /*DEBUG*/xASSERT_RET(FALSE == csUser.empty(),          FALSE);
     /*DEBUG*/xASSERT_RET(FALSE == csPass.empty(),          FALSE);
     /*DEBUG*/xASSERT_RET(FALSE == csServer.empty(),        FALSE);
     /*DEBUG*/xASSERT_RET((32767 > usPort) && (0 < usPort), FALSE);

     _m_sUser   = csUser;
     _m_sPass   = csPass;
     _m_sServer = csServer;
     _m_usPort  = usPort;

     return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bConnect
BOOL CxPop3::bConnect() {
     //-------------------------------------
     //Create sock
    _m_bRes = _m_scktSocket.bCreate(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);
     xCHECK_RET(FALSE == _m_bRes, FALSE);

     //-------------------------------------
     //Parse domain
     tString sIp;

     _m_bRes = CxDnsClient::bGetHostAddrByName(_m_sServer, &sIp);
     xCHECK_RET(FALSE == _m_bRes, FALSE);

     //-------------------------------------
     //Connect
     _m_bRes = _m_scktSocket.bConnect(sIp, _m_usPort);
     xCHECK_RET(FALSE == _m_bRes, FALSE);

     //-------------------------------------
     //[welcome message]
     _m_sRes = _m_scktSocket.sRecvAll(0, "\r\n");
     /*DEBUG*/xASSERT_MSG_RET(FALSE == _bIsError(_m_sRes), _m_sRes.c_str(), FALSE); //��� "+OK"

    _m_bConnected = TRUE;

     return TRUE;
 }
//---------------------------------------------------------------------------
//DONE: bLogin
BOOL CxPop3::bLogin() {
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
    const tString sUserCmd = "USER " + _m_sUser + "\r\n";

    _m_bRes = _bCommand(sUserCmd, "\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    //-------------------------------------
    //[PASS\r\n]
    tString sPassCmd = "PASS " + _m_sPass + "\r\n";

    _m_bRes = _bCommand(sPassCmd, "\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bStat
BOOL CxPop3::bStat(ULONG &ulSum, ULONG &ulSize) {
    //-------------------------------------
    //RFC
    /*
    �: STAT
    S: +�� 2 320
    */

    //-------------------------------------
    //[LIST\r\n]
    const tString sStatCmd = "STAT\r\n";

    _m_bRes = _bCommand(sStatCmd, "\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    ulSum  = _ulMailsSum (_m_sRes);    //???????????????????????????
    ulSize = _ulMailsSize(_m_sRes);

#ifdef _DEBUG
    //+OK 2 1141841
    /*DEBUG*/_m_clLog.bWrite("Recv STAT Resp: MailsSum  = %u\n", ulSum);
    /*DEBUG*/_m_clLog.bWrite("Recv STAT Resp: MailsSize = %u\n", ulSize);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bList (������ ��������, ������ �� �������)
BOOL CxPop3::bList(std::vector<ULONG> &veculList) {
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


    return FALSE;
}
//---------------------------------------------------------------------------
//TODO: bListAt (������ ������ � �������� ulIndex)
BOOL CxPop3::bListAt(ULONG &ulIndex) {
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

    return FALSE;
}
//---------------------------------------------------------------------------
//DONE: bNoop (�������� ��������� ���������� � ����)
BOOL CxPop3::bNoop() {
    //-------------------------------------
    //RFC
    /*
    �: NOOP
    S: +��
    */

    //-------------------------------------
    //[NOOP\r\n]
    tString sNoopCmd = "NOOP\r\n";

    _m_bRes = _bCommand(sNoopCmd, "\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRset (������ ����� �������� �����)
BOOL CxPop3::bRset() {
    //-------------------------------------
    //RFC
    /*
    �: RSET
    S: +OK maildrop has 2 messages (320 octets)
    */

    //-------------------------------------
    //[RSET\r\n]
    tString sRsetCmd = "RSET\r\n";

    _m_bRes = _bCommand(sRsetCmd, "\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bTop (�������� ��������� ������)
BOOL CxPop3::bTop(INT iNum, INT iLines, tString &sBuff) {
    /*DEBUG*/xASSERT_RET(iNum   > 0,   FALSE);
    /*DEBUG*/xASSERT_RET(iLines > - 1, FALSE);

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
    tString sTopCmd = "TOP " + CxString::lexical_cast(iNum) + " " + CxString::lexical_cast(iLines) + "\r\n";

    _m_bRes = _bCommand(sTopCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    sBuff.assign(_m_sRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRetriveRaw ()
BOOL CxPop3::bRetriveRaw(INT iNum, const tString &csDirPath, const tString &csFileName) {  //csDirPath ��� �����
    /*DEBUG*/xASSERT_RET(iNum > 0,                    FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), FALSE);

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
    const tString sRetrCmd = "RETR " + CxString::lexical_cast(iNum) + "\r\n";

    _m_bRes = _bCommand(sRetrCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t uiOkPos      = _m_sRes.find("+OK");
    size_t uiFirstCRPos = _m_sRes.find("\r\n");
    if (tString::npos != uiOkPos && 0 == uiOkPos && tString::npos != uiFirstCRPos) {
        _m_sRes.erase(uiOkPos, uiFirstCRPos - uiOkPos + 2);    //"\r\n - 2 c������"
    } else {
        /*DEBUG*/xASSERT(FALSE);
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t uiEndOfMessagePos = _m_sRes.rfind("\r\n.\r\n");
    if (tString::npos != uiEndOfMessagePos) {
        _m_sRes.erase(uiEndOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        /*DEBUG*/xASSERT(FALSE);
    }

    //-------------------------------------
    //��������� ���� �� ����
    CxStdioFile stdFile;

	_m_bRes = stdFile.bOpen(csDirPath + "\\" + csFileName, CxStdioFile::omBinWrite, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    size_t uiWriteSize = stdFile.uiWrite(&_m_sRes[0], _m_sRes.size());
    /*DEBUG*///???
    xUNUSED(uiWriteSize);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRetriveRawAndBackup ()
BOOL CxPop3::bRetriveRawAndBackup(INT iNum, const tString &csDirPath, const tString &csBackupDirPath, const tString &csFileName) {
    /*DEBUG*/xASSERT_RET(iNum > 0,                                                         FALSE);
    /*DEBUG*/xASSERT_RET(! (true == csDirPath.empty() && true == csBackupDirPath.empty()), FALSE);
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(),                                      FALSE);

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
    const tString sRetrCmd = "RETR " + CxString::lexical_cast(iNum) + "\r\n";

    _m_bRes = _bCommand(sRetrCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t uiOkPos      = _m_sRes.find("+OK");
    size_t uiFirstCRPos = _m_sRes.find("\r\n");
    if (tString::npos != uiOkPos && 0 == uiOkPos && tString::npos != uiFirstCRPos) {
        _m_sRes.erase(uiOkPos, uiFirstCRPos - uiOkPos + 2);    //"\r\n - 2 c������"
    } else {
        /*DEBUG*/xASSERT(FALSE);
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t uiEndOfMessagePos = _m_sRes.rfind("\r\n.\r\n");
    if (tString::npos != uiEndOfMessagePos) {
        _m_sRes.erase(uiEndOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        /*DEBUG*/xASSERT(FALSE);
    }

    //-------------------------------------
    //��������� ���� �� ���� (��������), ���� ���� ���� - �� ���������
    if (false == csDirPath.empty()) {
        CxStdioFile stdfOriginal;

		_m_bRes = stdfOriginal.bOpen(csDirPath + "\\" + csFileName, CxStdioFile::omBinWrite, TRUE);
        xCHECK_RET(FALSE == _m_bRes, FALSE);

        size_t uiOriginalWriteSize = stdfOriginal.uiWrite(&_m_sRes[0], _m_sRes.size());
        xCHECK_RET(0 == uiOriginalWriteSize, FALSE);
    }

    //-------------------------------------
    //��������� ���� �� ���� (�����), ���� ���� ���� - �� ���������
    if (false == csBackupDirPath.empty()) {
        CxStdioFile stdfBackup;

        _m_bRes = stdfBackup.bOpen(csBackupDirPath + "\\" + csFileName, CxStdioFile::omBinWrite, TRUE);
        xCHECK_RET(FALSE == _m_bRes, FALSE);

        size_t uiBackupWriteSize = stdfBackup.uiWrite(&_m_sRes[0], _m_sRes.size());
        xCHECK_RET(0 == uiBackupWriteSize, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRetrieveHeader ()
BOOL CxPop3::bRetrieveHeader(INT iNum, CxMimeHeader &mhMimeHeader) {
    /*DEBUG*/xASSERT_RET(iNum > 0, FALSE);

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
    tString sTopCmd = "TOP " + CxString::lexical_cast(iNum) + " " + "0" + "\r\n";

    _m_bRes = _bCommand(sTopCmd, "\r\n.\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    //-------------------------------------
    //������ �����
    mhMimeHeader.bParse(_m_sRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDelete (������� ������)
BOOL CxPop3::bDelete(INT iNum) {
    /*DEBUG*/xASSERT_RET(iNum > 0, FALSE);

    //-------------------------------------
    //RFC
    /*
    �: DELE 1
    S: +�� message 1 deleted

    ���

    �: DELE 2
    S: -ERR message 2 already deleted
    */

    tString _m_sRes;

    //-------------------------------------
    //[DELE 2\r\n]
    const tString sDeleCmd = "DELE " + CxString::lexical_cast(iNum) + "\r\n";

    _m_bRes = _bCommand(sDeleCmd, "\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDisconnect (������������� �� �������)
BOOL CxPop3::bDisconnect() {
    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    //-------------------------------------
    //[QUIT\r\n]
    const tString sQuitCmd = "QUIT\r\n";

    _m_bRes = _bCommand(sQuitCmd, "\r\n", &_m_sRes);
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    _m_bRes = _m_scktSocket.bClose();
    xCHECK_RET(FALSE == _m_bRes, FALSE);

    _m_bConnected = FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _ulMailsSum (������� ����� �����)
ULONG CxPop3::_ulMailsSum(const tString &csServerAnswer) {
    /*DEBUG*/xASSERT_RET(false == csServerAnswer.empty(), FALSE);

    //+OK 2 1141841
    ULONG   ulSum = 0;
    tString sSum;
    std::vector<tString> vsRes;

    _m_bRes = CxString::bSplit(csServerAnswer, " ", &vsRes);
    /*DEBUG*///TODO:

    sSum  = vsRes.at(1);
    ulSum = atol(sSum.c_str());        //!!! ul -> l

    return ulSum;
}
//---------------------------------------------------------------------------
//DONE: _ulMailsSize (����� ������ ����� � ������)
ULONG CxPop3::_ulMailsSize(const tString &csServerAnswer) {
    /*DEBUG*/xASSERT_RET(false == csServerAnswer.empty(), FALSE);

    //+OK 2 1141841
    ULONG   ulSize = 0;
    tString sSize;
    std::vector<tString> vsRes;

    _m_bRes = CxString::bSplit(csServerAnswer, " ", &vsRes);
    /*DEBUG*///TODO:

    sSize  = vsRes.at(2);
    ulSize = atol(sSize.c_str());    //!!! ul+\r\n -> l

    return ulSize;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bCommand ()
BOOL CxPop3::_bCommand(const tString &csCmd, const tString &csReplyDelimiter, tString *psReply) {
    /*DEBUG*/xASSERT_RET(false == csCmd.empty(),            FALSE);
    /*DEBUG*/xASSERT_RET(false == csReplyDelimiter.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psReply,                  FALSE);

    _m_bRes = _m_scktSocket.bSendAll(csCmd, 0);
    /*DEBUG*/xASSERT_RET(TRUE == _m_bRes, FALSE);

    _m_sRes = _m_scktSocket.sRecvAll(0, csReplyDelimiter);
    /*DEBUG*/////xASSERT_MSG_RET(FALSE == _bIsError(_m_sRes), _m_sRes.c_str(), FALSE);

    (*psReply).assign(_m_sRes);

#ifdef _DEBUG
    /*DEBUG*/////_m_clLog.bWrite("Command :  %s          Response: %s\n", csCmd.c_str(), _m_sRes.c_str());
#endif

    return static_cast<BOOL>( !_bIsError(_m_sRes)/*TRUE*/ );
}
//---------------------------------------------------------------------------
//DONE: _bIsError ()
BOOL CxPop3::_bIsError(const tString &csText) {
    /*DEBUG*/xASSERT_RET(FALSE == csText.empty(), TRUE);

    if (0 == memcmp(csText.c_str(), "+OK", 3)) {
        return FALSE;
    }
    if (0 == memcmp(csText.c_str(), "-ERR", 4)) {
        return TRUE;
    }

    /*DEBUG*/xASSERT_RET(FALSE, TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
