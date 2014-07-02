/**
 * \file   Test_TcpServer.cpp
 * \brief
 */


#include <Test/Net/Test_TcpServer.h>

#include <xLib/Net/SocketInit.h>
#include <xLib/Net/DnsClient.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_TcpServer::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

    Socket::ExAddressFamily afAf       = Socket::afInet;
    Socket::ExType          tpType     = Socket::tpStream;
    Socket::ExProtocol      ptProtocol = Socket::ptIp;

    std::ctstring_t      csDomain        = xT("127.0.0.1");
    std::tstring_t            sIp             = xT("");
    ushort_t                  usPort          = 80;

    std::tstring_t            sSendBuff       = xT("TEST_STRING");
    tchar_t                   szRecvBuff[1024 * sizeof(tchar_t)]  = {0};

    SocketInit siInit(2, 2);
    TcpServer  objListenSocket;
    TcpServer  objClientSocket;

    //-------------------------------------
    //bCreate
    objListenSocket.create(afAf, tpType, ptProtocol);

    //-------------------------------------
    //bGetHostAddrByName
    DnsClient::hostAddrByName(csDomain, &sIp);

    //-------------------------------------
    //bConnect
    objListenSocket.bind(usPort);

    //-------------------------------------
    //bListen
    objListenSocket.listen(SOMAXCONN);

    //-------------------------------------
    //bAccept
    objListenSocket.accept(&objClientSocket, &sIp);

    for (; ;) {
        //-------------------------------------
        //iRecv
        ssize_t iRv = objClientSocket.receive(&szRecvBuff[0], xARRAY_SIZE(szRecvBuff), 0);
        xTEST_DIFF((ssize_t)xSOCKET_ERROR, iRv);

        std::tcout << std::tstring_t(szRecvBuff, iRv) << std::endl;
    }

    //-------------------------------------
    //bClose
    objClientSocket.close();

    //-------------------------------------
    //iSend
    ////m_iRv = objSocket.send(sSendBuff.c_str(), sSendBuff.size(), 0);
    ////xTEST_DIFF(TcpServer::etError, m_iRv);

    //-------------------------------------
    //bClose
    objListenSocket.close();

    //-------------------------------------
    //iGetLastError
    m_iRv = TcpServer::lastError();
    //xTEST_EQ(m_bRv, true);
}
//-------------------------------------------------------------------------------------------------
