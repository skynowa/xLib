/**
 * \file   CxTest_CxTcpServer.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxTcpServer.h>

#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxDnsClient.h>


//---------------------------------------------------------------------------
CxTest_CxTcpServer::CxTest_CxTcpServer() {

}
//---------------------------------------------------------------------------
CxTest_CxTcpServer::~CxTest_CxTcpServer() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxTcpServer::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    CxSocket::EAddressFamily afAf       = CxSocket::afInet;
    CxSocket::EType          tpType     = CxSocket::tpStream;
    CxSocket::EProtocol      ptProtocol = CxSocket::ptIp;

    const std::string_t     csDomain        = xT("127.0.0.1");
    std::string_t           sIp             = xT("");
    USHORT            usPort          = 80;

    std::string_t           sSendBuff       = xT("TEST_STRING");
    char_t             szRecvBuff[1024 * sizeof(char_t)]  = {0};

    CxSocketInit      siInit(2, 2);
    CxTcpServer objListenSocket;
    CxTcpServer objClientSocket;

    //-------------------------------------
    //bCreate
    m_bRes = objListenSocket.bCreate(afAf, tpType, ptProtocol);
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bGetHostAddrByName
    m_bRes = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bConnect
    m_bRes = objListenSocket.bBind(usPort);
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bListen
    m_bRes = objListenSocket.bListen(SOMAXCONN);
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bAccept
    m_bRes = objListenSocket.bAccept(&objClientSocket, &sIp);
    xTEST_DIFF(FALSE, m_bRes);

    for (; ;) {
        //-------------------------------------
        //iRecv
        m_iRes = objClientSocket.iRecv(&szRecvBuff[0], xARRAY_SIZE(szRecvBuff), 0);
        xTEST_DIFF((int)CxTcpServer::etError, m_iRes);

        std::tcout << std::string_t(szRecvBuff, m_iRes) << std::endl;
    }

    //-------------------------------------
    //bClose
    m_bRes = objClientSocket.bClose();
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //iSend
    ////m_iRes = objSocket.iSend(sSendBuff.c_str(), sSendBuff.size(), 0);
    ////xTEST_DIFF(CxTcpServer::etError, m_iRes);

    //-------------------------------------
    //bClose
    m_bRes = objListenSocket.bClose();
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //iGetLastError
    m_iRes = CxTcpServer::iGetLastError();
    //xTEST_DIFF(FALSE, m_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------
