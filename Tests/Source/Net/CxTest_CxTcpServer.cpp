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
bool
CxTest_CxTcpServer::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

    CxSocket::EAddressFamily afAf       = CxSocket::afInet;
    CxSocket::EType          tpType     = CxSocket::tpStream;
    CxSocket::EProtocol      ptProtocol = CxSocket::ptIp;

    const std::tstring_t     csDomain        = xT("127.0.0.1");
    std::tstring_t           sIp             = xT("");
    ushort_t            usPort          = 80;

    std::tstring_t           sSendBuff       = xT("TEST_STRING");
    tchar_t             szRecvBuff[1024 * sizeof(tchar_t)]  = {0};

    CxSocketInit      siInit(2, 2);
    CxTcpServer objListenSocket;
    CxTcpServer objClientSocket;

    //-------------------------------------
    //bCreate
    m_bRes = objListenSocket.bCreate(afAf, tpType, ptProtocol);
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //bGetHostAddrByName
    m_bRes = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //bConnect
    m_bRes = objListenSocket.bBind(usPort);
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //bListen
    m_bRes = objListenSocket.bListen(SOMAXCONN);
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //bAccept
    m_bRes = objListenSocket.bAccept(&objClientSocket, &sIp);
    xTEST_EQ(true, m_bRes);

    for (; ;) {
        //-------------------------------------
        //iRecv
        m_iRes = objClientSocket.iRecv(&szRecvBuff[0], xARRAY_SIZE(szRecvBuff), 0);
        xTEST_DIFF((int)CxTcpServer::etError, m_iRes);

        std::tcout << std::tstring_t(szRecvBuff, m_iRes) << std::endl;
    }

    //-------------------------------------
    //bClose
    m_bRes = objClientSocket.bClose();
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //iSend
    ////m_iRes = objSocket.iSend(sSendBuff.c_str(), sSendBuff.size(), 0);
    ////xTEST_DIFF(CxTcpServer::etError, m_iRes);

    //-------------------------------------
    //bClose
    m_bRes = objListenSocket.bClose();
    xTEST_EQ(true, m_bRes);

    //-------------------------------------
    //iGetLastError
    m_iRes = CxTcpServer::iGetLastError();
    //xTEST_EQ(true, m_bRes);

    return true;
}
//---------------------------------------------------------------------------
