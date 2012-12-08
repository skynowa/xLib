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
/* virtual */
void
CxTest_CxTcpServer::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    CxSocket::ExAddressFamily afAf       = CxSocket::afInet;
    CxSocket::ExType          tpType     = CxSocket::tpStream;
    CxSocket::ExProtocol      ptProtocol = CxSocket::ptIp;

    const std::tstring_t      csDomain        = xT("127.0.0.1");
    std::tstring_t            sIp             = xT("");
    ushort_t                  usPort          = 80;

    std::tstring_t            sSendBuff       = xT("TEST_STRING");
    tchar_t                   szRecvBuff[1024 * sizeof(tchar_t)]  = {0};

    CxSocketInit siInit(2, 2);
    CxTcpServer  objListenSocket;
    CxTcpServer  objClientSocket;

    //-------------------------------------
    //bCreate
    objListenSocket.vCreate(afAf, tpType, ptProtocol);

    //-------------------------------------
    //bGetHostAddrByName
    CxDnsClient::vHostAddrByName(csDomain, &sIp);

    //-------------------------------------
    //bConnect
    objListenSocket.vBind(usPort);

    //-------------------------------------
    //bListen
    objListenSocket.vListen(SOMAXCONN);

    //-------------------------------------
    //bAccept
    objListenSocket.vAccept(&objClientSocket, &sIp);

    for (; ;) {
        //-------------------------------------
        //iRecv
        m_iRv = objClientSocket.iRecv(&szRecvBuff[0], static_cast<int>( xARRAY_SIZE(szRecvBuff) ), 0);
        xTEST_DIFF(xSOCKET_ERROR, m_iRv);

        std::tcout << std::tstring_t(szRecvBuff, m_iRv) << std::endl;
    }

    //-------------------------------------
    //bClose
    objClientSocket.vClose();

    //-------------------------------------
    //iSend
    ////m_iRv = objSocket.iSend(sSendBuff.c_str(), sSendBuff.size(), 0);
    ////xTEST_DIFF(CxTcpServer::etError, m_iRv);

    //-------------------------------------
    //bClose
    objListenSocket.vClose();

    //-------------------------------------
    //iGetLastError
    m_iRv = CxTcpServer::iLastError();
    //xTEST_EQ(true, m_bRv);
}
//---------------------------------------------------------------------------
