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
bool
CxTest_CxTcpServer::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

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
    m_bRv = objListenSocket.bCreate(afAf, tpType, ptProtocol);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bGetHostAddrByName
    CxDnsClient::vGetHostAddrByName(csDomain, &sIp);

    //-------------------------------------
    //bConnect
    m_bRv = objListenSocket.bBind(usPort);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bListen
    m_bRv = objListenSocket.bListen(SOMAXCONN);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bAccept
    m_bRv = objListenSocket.bAccept(&objClientSocket, &sIp);
    xTEST_EQ(true, m_bRv);

    for (; ;) {
        //-------------------------------------
        //iRecv
        m_iRv = objClientSocket.iRecv(&szRecvBuff[0], xARRAY_SIZE(szRecvBuff), 0);
        xTEST_DIFF(xSOCKET_ERROR, m_iRv);

        std::tcout << std::tstring_t(szRecvBuff, m_iRv) << std::endl;
    }

    //-------------------------------------
    //bClose
    m_bRv = objClientSocket.bClose();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //iSend
    ////m_iRv = objSocket.iSend(sSendBuff.c_str(), sSendBuff.size(), 0);
    ////xTEST_DIFF(CxTcpServer::etError, m_iRv);

    //-------------------------------------
    //bClose
    m_bRv = objListenSocket.bClose();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //iGetLastError
    m_iRv = CxTcpServer::iGetLastError();
    //xTEST_EQ(true, m_bRv);

    return true;
}
//---------------------------------------------------------------------------
