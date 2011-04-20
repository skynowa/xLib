/****************************************************************************
* Class name:  CxSmtp
* Description: SMTP (RFC 2821)
* File name:   CxSmtp.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     13.04.2009 16:44:49
*
*****************************************************************************/

    
//---------------------------------------------------------------------------
#include <xLib/Net/CxSmtp.h> 

#include <xLib/Fso/CxPath.h>
#include <xLib/Log/CxTraceLog.h> 
#include <xLib/Fso/CxStdioFile.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Crypt/CxBase64.h>
//---------------------------------------------------------------------------  


/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSmtp
CxSmtp::CxSmtp() :
    _m_scktSocket(), 
    _m_ConsoleLog(FALSE),
    _m_sUser(), 
    _m_sPass(),
    _m_sServer(), 
    _m_usPort(0), 
    _m_bConnected(FALSE)
{   
////--    CxSocket::bInit(); 
}   
//--------------------------------------------------------------------------- 
//DONE: ~CxSmtp 
CxSmtp::~CxSmtp() { 
    if (TRUE == _m_bConnected) {
        bDisconnect();
    }        
        
////--    CxSocket::bClean(); 
}   
//--------------------------------------------------------------------------- 
//DONE: bCreate
BOOL CxSmtp::bCreate(const std::string &csUser, const std::string &csPass, const std::string &csServer, USHORT usPort) {
    /*DEBUG*/xASSERT_RET(FALSE == csUser.empty(),          FALSE);
    /*DEBUG*/////xASSERT_RET(FALSE == csPass.empty(),          FALSE);
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
BOOL CxSmtp::bConnect() {   
    BOOL        bRes = FALSE;
    std::string sRes = "";

    //-------------------------------------
    //������� ����� 
    bRes = _m_scktSocket.bCreate(AF_INET, SOCK_STREAM, 0);   
    xCHECK_RET(FALSE == bRes, FALSE);
    
    //-------------------------------------
    //������ �����  
    std::string sIpAddr = "";
    
    bRes = CxTcpClientSocket::bDnsParse(_m_sServer, /*ref*/sIpAddr);
    xCHECK_RET(FALSE == bRes, FALSE);
    
    //-------------------------------------
    //�����������   
    bRes = _m_scktSocket.bConnect(sIpAddr, _m_usPort);
    xCHECK_RET(FALSE == bRes, FALSE);
    
    //-------------------------------------
    //[welcome message]   
    sRes = _m_scktSocket.sRecvAll(0, "\r\n");   
    /*DEBUG*/xASSERT_MSG_RET(FALSE == _bIsError(sRes), sRes.c_str(), FALSE); 
    
    //-------------------------------------
    //[HELO\r\n]
    const std::string sHelloCmd = "HELO HOST\r\n";        //const std::string sHelloCmd = "HELO\r\n";
    
    bRes = _bCommand(sHelloCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);
    
    
    _m_bConnected = TRUE;
   
    return TRUE;   
}   
//---------------------------------------------------------------------------  
//DONE: bLogin (��������� �� ������)
BOOL CxSmtp::bLogin() {   
    //-------------------------------------
    //RFC
    /*
    C: AUTH LOGIN\r\n
    S: 334 VXNlcm5hbWU6
    C: base64_encode(MYLOGIN)\r\n
    C: base64_encode(MYPASS)\r\n
    S: 235 Authentication succeeded
    */

    BOOL        bRes = FALSE;
    std::string sRes = "";

    //-------------------------------------
    //[AUTH\r\n]
    const std::string sAuthLoginCmd = "AUTH LOGIN\r\n";

    bRes = _bCommand(sAuthLoginCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);
  
    //-------------------------------------
    //[mylogin\r\n]   
    const std::string sLoginCmd = CxBase64::sEncode(_m_sUser) + "\r\n";

    bRes = _bCommand(sLoginCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //[mypassword\r\n]   
    const std::string sPasswordCmd = CxBase64::sEncode(_m_sPass) + "\r\n";

    bRes = _bCommand(sPasswordCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    return TRUE;   
}   
//---------------------------------------------------------------------------
//DONE: bNoop (�������� ��������� ���������� � ���������)   
BOOL CxSmtp::bNoop() {
    //-------------------------------------
    //RFC
    /*
    �: NOOP
    S: +��
    */

    BOOL        bRes = FALSE;
    std::string sRes = "";

    //-------------------------------------
    //[NOOP\r\n]   
    std::string sNoopCmd = "NOOP\r\n";

    bRes = _bCommand(sNoopCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRset (������ ����� �������� �����)   
BOOL CxSmtp::bRset() {
    //-------------------------------------
    //RFC
    /*
    �: RSET 
    S: +OK maildrop has 2 messages (320 octets)
    */

    BOOL        bRes = FALSE;
    std::string sRes = "";

    //-------------------------------------
    //[RSET\r\n]   
    std::string sRsetCmd = "RSET\r\n";

    bRes = _bCommand(sRsetCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------    
//DONE: bSendRaw
BOOL CxSmtp::bSendRaw(const std::string &csFilePath, const std::string &sFrom, const std::string &sTo) {   
    /*DEBUG*/xASSERT_RET(INVALID_SOCKET != _m_scktSocket, FALSE);
    /*DEBUG*/xASSERT_RET(FALSE == sFrom.empty(),         FALSE); 
    /*DEBUG*/xASSERT_RET(FALSE == sTo.empty(),             FALSE); 
    
    BOOL              bRes      = FALSE;
    std::string       sRes      = "";

    /////////const std::string sHelloCmd = "HELO HOST\r\n";        //const std::string sHelloCmd = "HELO\r\n";
    const std::string sFromCmd  = "MAIL FROM: <" + sFrom + ">\r\n";
    const std::string sToCmd    = "RCPT TO: <"   + sTo   + ">\r\n";
    const std::string sDataCmd  = "DATA\r\n";
    const std::string sEndCmd   = "\r\n.\r\n";

    //////////-------------------------------------
    //////////[HELO\r\n]
    ////////////bRes = _bCommand(sHelloCmd, "\r\n", /*ref*/sRes);
    ////////////xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    bRes = _bCommand(sFromCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);
    
    //-------------------------------------    
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    bRes = _bCommand(sToCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);
    
    //-------------------------------------
    //[DATA\r\n]
    bRes = _bCommand(sDataCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //DONE: ������ �� ����� � ����� ����� � �����
    std::string sText = "";
    
    bRes = CxStdioFile::bReadFile(csFilePath, /*ref*/sText);
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //[DataText\r\n.\r\n]
    bRes = _bCommand(sText + sEndCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);
    
    return TRUE;   
}   
//---------------------------------------------------------------------------  
//DONE: bSend
BOOL CxSmtp::bSend(const std::string &csText, const std::string &sFrom, const std::string &sTo) {   
    /*DEBUG*/xASSERT_RET(INVALID_SOCKET != _m_scktSocket, FALSE);
    /*DEBUG*/xASSERT_RET(FALSE == sFrom.empty(),          FALSE); 
    /*DEBUG*/xASSERT_RET(FALSE == sTo.empty(),              FALSE); 

    BOOL              bRes      = FALSE;
    std::string       sRes      = "";

    const std::string sHelloCmd = "HELO HOST\r\n";
    const std::string sFromCmd  = "MAIL FROM: <" + sFrom + ">\r\n";
    const std::string sToCmd    = "RCPT TO: <"   + sTo   + ">\r\n";
    const std::string sDataCmd  = "DATA\r\n";
    const std::string sEndCmd   = "\r\n.\r\n";

    //////-------------------------------------
    //////[HELO DrWEB\r\n]
    ////bRes = _bCommand(sHelloCmd, "\r\n", /*ref*/sRes);
    ////xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //[MAIL FROM:<my_mail@mail.ru>\r\n]
    bRes = _bCommand(sFromCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------    
    //[RCPT TO:<your_mail@mail.ru>\r\n]
    bRes = _bCommand(sToCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //[DATA\r\n]
    bRes = _bCommand(sDataCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    //-------------------------------------
    //�������� �����
    bRes = _m_scktSocket.bSendAll(csText, 0);
    xASSERT_RET(TRUE == bRes, FALSE);

    //-------------------------------------
    //[\r\n.\r\n]
    bRes = _bCommand(sEndCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    return TRUE;   
}   
//--------------------------------------------------------------------------- 
//DONE: bDisconnect
BOOL CxSmtp::bDisconnect() {
    //-------------------------------------
    //RFC
    /*
    [QUIT\r\n]
    +�� dewey POP3 server signing off
    */

    BOOL        bRes = FALSE;
    std::string sRes = "";

    //-------------------------------------
    //[QUIT]  
    const std::string sQuitCmd = "QUIT\r\n";

    bRes = _bCommand(sQuitCmd, "\r\n", /*ref*/sRes);
    xCHECK_RET(FALSE == bRes, FALSE);

    bRes = _m_scktSocket.bClose();
    xCHECK_RET(FALSE == bRes, FALSE);
    
    _m_bConnected = FALSE;

    return TRUE;   
}   
//---------------------------------------------------------------------------   



/****************************************************************************
*    Private methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bCommand
BOOL CxSmtp::_bCommand(const std::string &csCmd, const std::string &csReplyDelimiter, std::string &sReply) {
    /*DEBUG*/xASSERT_RET(false == csCmd.empty(),            FALSE);    
    /*DEBUG*/xASSERT_RET(false == csReplyDelimiter.empty(), FALSE);    

    BOOL        bRes = FALSE;
    std::string sRes = "";

    bRes = _m_scktSocket.bSendAll(csCmd, 0);
    /*DEBUG*/xASSERT_RET(TRUE == bRes, FALSE);

    sRes = _m_scktSocket.sRecvAll(0, csReplyDelimiter);
    /*DEBUG*/xASSERT_MSG_RET(FALSE == _bIsError(sRes), sRes.c_str(), FALSE);

    sReply.assign(sRes);
    
#ifdef _DEBUG   
    /*DEBUG*/_m_ConsoleLog.bWrite("Command :  %s          Response: %s\n", csCmd.c_str(), sRes.c_str());
#endif 

    return TRUE;
} 
//---------------------------------------------------------------------------
//DONE: _bIsError
BOOL CxSmtp::_bIsError(const std::string &csText) {
    /*DEBUG*/xASSERT_RET(FALSE == csText.empty(), TRUE);
     
    BOOL bRes = !(  
            !memcmp(csText.c_str(), "334", 3) ||    //334 VXNlcm5hbWU6
            !memcmp(csText.c_str(), "235", 3) ||    //235 2.0.0 Authentication successful
            !memcmp(csText.c_str(), "220", 3) ||    //220 Sergey Kerio MailServer 6.7.0 patch 1 ESMTP ready
            !memcmp(csText.c_str(), "250", 3) ||    //250 2.0.0 OK
            !memcmp(csText.c_str(), "354", 3) ||    //354 Enter mail, end with CRLF.CRLF
            !memcmp(csText.c_str(), "221", 3)        //221 221 2.0.0 SMTP closing connection
    );
     
    return bRes;
}
//---------------------------------------------------------------------------
