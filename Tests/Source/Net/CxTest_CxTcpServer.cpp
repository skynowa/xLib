/**
 * \file   CxTest_CxTcpServer.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxTcpServer.h>

#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxDnsClient.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxTcpServer::unit(
    culonglong_t &a_cullCaseLoops
)
{
    CxSocket::ExAddressFamily afAf       = CxSocket::afInet;
    CxSocket::ExType          tpType     = CxSocket::tpStream;
    CxSocket::ExProtocol      ptProtocol = CxSocket::ptIp;

    std::ctstring_t      csDomain        = xT("127.0.0.1");
    std::tstring_t            sIp             = xT("");
    ushort_t                  usPort          = 80;

    std::tstring_t            sSendBuff       = xT("TEST_STRING");
    tchar_t                   szRecvBuff[1024 * sizeof(tchar_t)]  = {0};

    CxSocketInit siInit(2, 2);
    CxTcpServer  objListenSocket;
    CxTcpServer  objClientSocket;

    //-------------------------------------
    //bCreate
    objListenSocket.create(afAf, tpType, ptProtocol);

    //-------------------------------------
    //bGetHostAddrByName
    CxDnsClient::hostAddrByName(csDomain, &sIp);

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
    ////xTEST_DIFF(CxTcpServer::etError, m_iRv);

    //-------------------------------------
    //bClose
    objListenSocket.close();

    //-------------------------------------
    //iGetLastError
    m_iRv = CxTcpServer::lastError();
    //xTEST_EQ(true, m_bRv);
}
//------------------------------------------------------------------------------
