/**
 * \file  CxPop3.cpp
 * \brief POP3
 */


#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxPop3::CxPop3() :
    _sRv        (),
    ////_socketInit(2, 2),
    _socket     (),
    _user       (),
    _password   (),
    _server     (),
    _port       (0),
    _isConnected(false)
{
}
//-------------------------------------------------------------------------------------------------
inline
CxPop3::~CxPop3()
{
    disconnect();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::create(
    std::ctstring_t &a_user,
    std::ctstring_t &a_password,
    std::ctstring_t &a_server,
    ushort_t         a_port
)
{
     xTEST_EQ(false, a_user.empty());
     xTEST_EQ(false, a_password.empty());
     xTEST_EQ(false, a_server.empty());
     xTEST_EQ(true, (32767 > a_port) && (0 < a_port));

     _user   = a_user;
     _password   = a_password;
     _server = a_server;
     _port  = a_port;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::connect()
{
     //-------------------------------------
     //Create sock
     _socket.create(CxSocket::afInet, CxSocket::tpStream, CxSocket::ptIp);

     //-------------------------------------
     //Parse domain
     std::tstring_t ip;

     CxDnsClient::hostAddrByName(_server, &ip);

     //-------------------------------------
     //Connect
     _socket.connect(ip, _port);

     //-------------------------------------
     //[welcome message]
     _sRv = _socket.recvAll(0, xT("\r\n"));
     xTEST_MSG_EQ(false, _isError(_sRv), _sRv); // "+OK"

    _isConnected = true;
 }
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::login()
{
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
    std::ctstring_t userCmd = xT("USER ") + _user + xT("\r\n");

    _command(userCmd, xT("\r\n"), &_sRv);

    //-------------------------------------
    //[PASS\r\n]
    std::tstring_t passCmd = xT("PASS ") + _password + xT("\r\n");

    _command(passCmd, xT("\r\n"), &_sRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::stat(
    ulong_t &a_sum,
    ulong_t &a_size
)
{
    //-------------------------------------
    //RFC
    /*
    �: STAT
    S: +�� 2 320
    */

    //-------------------------------------
    //[LIST\r\n]
    std::ctstring_t statCmd = xT("STAT\r\n");

    _command(statCmd, xT("\r\n"), &_sRv);

    a_sum  = _mailsSum (_sRv);
    a_size = _mailsSize(_sRv);

#if 0
    //+OK 2 1141841
    _m_clLog.bWrite("Recv STAT Resp: MailsSum  = %u\n", a_sum);
    _m_clLog.bWrite("Recv STAT Resp: MailsSize = %u\n", a_size);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::list(
    std::vector<ulong_t> &a_list
)
{
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
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::listAt(
    ulong_t &a_index
)
{
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
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::noop()
{
    //-------------------------------------
    //RFC
    /*
    �: NOOP
    S: +��
    */

    //-------------------------------------
    //[NOOP\r\n]
    std::tstring_t noopCmd = xT("NOOP\r\n");

    _command(noopCmd, xT("\r\n"), &_sRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::rset()
{
    //-------------------------------------
    //RFC
    /*
    �: RSET
    S: +OK maildrop has 2 messages (320 octets)
    */

    //-------------------------------------
    //[RSET\r\n]
    std::tstring_t rsetCmd = xT("RSET\r\n");

    _command(rsetCmd, xT("\r\n"), &_sRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::top(
    int_t           a_num,
    int_t           a_lines,
    std::tstring_t &a_buff
)
{
    xTEST_GR(a_num, 0);
    xTEST_GR(a_lines,- 1);

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
    std::tstring_t topCmd = xT("TOP ") + CxString::cast(a_num) + xT(" ") +
        CxString::cast(a_lines) + xT("\r\n");

    _command(topCmd, xT("\r\n.\r\n"), &_sRv);

    a_buff = _sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::retriveRaw(
    int_t            a_num,
    std::ctstring_t &a_dirPath,
    std::ctstring_t &a_fileName
)
{  //dirPath ��� �����
    xTEST_GR(a_num, 0);
    xTEST_EQ(false, a_dirPath.empty());
    xTEST_EQ(false, a_fileName.empty());

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
    std::ctstring_t retrCmd = xT("RETR ") + CxString::cast(a_num) + xT("\r\n");

    _command(retrCmd, xT("\r\n.\r\n"), &_sRv);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t okPos      = _sRv.find(xT("+OK"));
    size_t firstCRPos = _sRv.find(xT("\r\n"));
    if (std::tstring_t::npos != okPos && 0 == okPos && std::tstring_t::npos != firstCRPos) {
        _sRv.erase(okPos, firstCRPos - okPos + 2);    //"\r\n - 2 c������"
    } else {
        xTEST_FAIL;
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t endOfMessagePos = _sRv.rfind(xT("\r\n.\r\n"));
    if (std::tstring_t::npos != endOfMessagePos) {
        _sRv.erase(endOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        xTEST_FAIL;
    }

    //-------------------------------------
    //��������� ���� �� ����
    CxFile file;

    file.create(a_dirPath + xT("\\") + a_fileName, CxFile::omBinWrite, true);

    size_t writeSize = file.write((cvoid_t *)&_sRv[0], _sRv.size());
    //???
    xUNUSED(writeSize);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::retriveRawAndBackup(
    int_t            a_num,
    std::ctstring_t &a_dirPath,
    std::ctstring_t &a_backupDirPath,
    std::ctstring_t &a_fileName
)
{
    xTEST_GR(a_num, 0);
    xTEST_EQ(false, (a_dirPath.empty() && a_backupDirPath.empty()));
    xTEST_EQ(false, a_fileName.empty());

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
    std::ctstring_t retrCmd = xT("RETR ") + CxString::cast(a_num) + xT("\r\n");

    _command(retrCmd, xT("\r\n.\r\n"), &_sRv);

    //-------------------------------------
    //DONE: ������� 1-�� ������ [+OK message 1 (652 octets)]
    size_t okPos      = _sRv.find(xT("+OK"));
    size_t firstCRPos = _sRv.find(xT("\r\n"));
    if (std::tstring_t::npos != okPos && 0 == okPos && std::tstring_t::npos != firstCRPos) {
        _sRv.erase(okPos, firstCRPos - okPos + 2);    //"\r\n - 2 c������"
    } else {
        xTEST_FAIL;
    }

    //-------------------------------------
    //DONE: ������� [\r\n.\r\n]
    size_t endOfMessagePos = _sRv.rfind(xT("\r\n.\r\n"));
    if (std::tstring_t::npos != endOfMessagePos) {
        _sRv.erase(endOfMessagePos, 5);    //"\r\n.\r\n" - 5 c������"
    } else {
        xTEST_FAIL;
    }

    //-------------------------------------
    //��������� ���� �� ���� (��������), ���� ���� ���� - �� ���������
    if (!a_dirPath.empty()) {
        CxFile original;

        original.create(a_dirPath + xT("\\") + a_fileName, CxFile::omBinWrite, true);

        size_t originalWriteSize = original.write((cvoid_t *)&_sRv[0], _sRv.size());
        xTEST_DIFF(size_t(0), originalWriteSize);
    }

    //-------------------------------------
    //��������� ���� �� ���� (�����), ���� ���� ���� - �� ���������
    if (!a_backupDirPath.empty()) {
        CxFile backup;

        backup.create(a_backupDirPath + xT("\\") + a_fileName, CxFile::omBinWrite, true);

        size_t backupWriteSize = backup.write((cvoid_t *)&_sRv[0], _sRv.size());
        xTEST_DIFF(size_t(0), backupWriteSize);
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::retrieveHeader(
    int_t         a_num,
    CxMimeHeader &a_mimeHeader
)
{
    xTEST_LESS(a_num, 0);

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
    std::tstring_t topCmd = xT("TOP ") + CxString::cast(a_num) + xT(" ") + xT("0") + xT("\r\n");

    _command(topCmd, xT("\r\n.\r\n"), &_sRv);

    //-------------------------------------
    //������ �����
    a_mimeHeader.parse(_sRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::del(
    int_t a_num
)
{
    xTEST_GR(a_num, 0);

    //-------------------------------------
    //RFC
    /*
    �: DELE 1
    S: +�� message 1 deleted

    ���

    �: DELE 2
    S: -ERR message 2 already deleted
    */

    std::tstring_t _sRv;

    //-------------------------------------
    //[DELE 2\r\n]
    std::ctstring_t deleCmd = xT("DELE ") + CxString::cast(a_num) + xT("\r\n");

    _command(deleCmd, xT("\r\n"), &_sRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::disconnect()
{
    xCHECK_DO(!_isConnected, return);

    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    //-------------------------------------
    //[QUIT\r\n]
    std::ctstring_t quitCmd = xT("QUIT\r\n");

    _command(quitCmd, xT("\r\n"), &_sRv);

    _socket.close();

    _isConnected = false;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxPop3::_mailsSum(
    std::ctstring_t &a_serverAnswer
)
{
    xTEST_EQ(false, a_serverAnswer.empty());

    //+OK 2 1141841
    ulong_t            sum = 0UL;
    std::tstring_t     sSum;
    std::vec_tstring_t vsRv;

    CxString::split(a_serverAnswer, xT(" "), &vsRv);

    sSum  = vsRv.at(1);
    sum = CxString::cast<ulong_t>( sSum );        // ul -> l

    return sum;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxPop3::_mailsSize(
    std::ctstring_t &a_serverAnswer
)
{
    xTEST_EQ(false, a_serverAnswer.empty());

    //+OK 2 1141841
    ulong_t            size = 0;
    std::tstring_t     sSize;
    std::vec_tstring_t vsRv;

    CxString::split(a_serverAnswer, xT(" "), &vsRv);

    sSize  = vsRv.at(2);
    size = CxString::cast<ulong_t>( sSize );    // ul+\r\n -> l

    return size;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxPop3::_command(
    std::ctstring_t &command,
    std::ctstring_t &replyDelimiter,
    std::tstring_t  *reply
)
{
    xTEST_EQ(false, command.empty());
    xTEST_EQ(false, replyDelimiter.empty());
    xTEST_PTR(reply);

    _socket.sendAll(command, 0);

    _sRv = _socket.recvAll(0, replyDelimiter);
    ////xTEST_MSG_EQ(false, _bIsError(_sRv), _sRv);

    (*reply) = _sRv;

#ifdef _DEBUG
    ////_m_clLog.bWrite("Command :  %s          Response: %s\n", command.c_str(), _sRv.c_str());
#endif

    xTEST_EQ(false, _isError(_sRv));
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxPop3::_isError(
    std::ctstring_t &text
)
{
    xTEST_EQ(false, text.empty());

    if (0 == std::memcmp(text.c_str(), xT("+OK"), 3)) {
        return false;
    }
    if (0 == std::memcmp(text.c_str(), xT("-ERR"), 4)) {
        return true;
    }

    xTEST_FAIL;

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
