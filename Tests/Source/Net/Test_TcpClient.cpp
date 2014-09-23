/**
 * \file   Test_TcpClient.cpp
 * \brief
 */


#include <Test/Net/Test_TcpClient.h>

#include <xLib/Net/SocketInit.h>
#include <xLib/Net/DnsClient.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_TcpClient::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

    Socket::ExAddressFamily afAf           = Socket::afInet;
    Socket::ExType          tpType         = Socket::tpStream;
    Socket::ExProtocol      ptProtocol     = Socket::ptIp;

    std::ctstring_t      csDomain        = xT("127.0.0.1");
    std::tstring_t            sIp            = xT("127.0.0.1");
    ushort_t                  usPort         = 80;
    std::tstring_t            sSendBuff      = xT("TEST_STRING");
    ////char                  szRecvBuff[32] = {0};

    //-------------------------------------
    //�������������
    SocketInit      siInit(2, 2);
    TcpClient objSocket;

    //-------------------------------------
    //bCreate
    objSocket.create(afAf, tpType, ptProtocol);

    //-------------------------------------
    //bIsServerAlive
    ////m_bRv = objSocket.bIsServerAlive(sIp, usPort);
    ////xTEST_EQ(m_bRv, true);

    //-------------------------------------
    //bDnsParse
    DnsClient::hostAddrByName(csDomain, &sIp);

    //-------------------------------------
    //bConnect
    objSocket.connect(sIp, usPort);

    //-------------------------------------
    //bIsReadable
    m_bRv = objSocket.isReadable();
    xTEST_EQ(m_bRv, false);

    //-------------------------------------
    //bIsWritable
    m_bRv = objSocket.isWritable();
    xTEST_EQ(m_bRv, true);

    //-------------------------------------
    //bGetPeerName
    {
        std::tstring_t _sIp;
        ushort_t       _usPort = 0;

        objSocket.peerName(&_sIp, &_usPort);
    }

    //-------------------------------------
    //bGetSocketName
    {
        std::tstring_t _sIp;
        ushort_t       _usPort = 0;

        objSocket.socketName(&_sIp, &_usPort);
    }

    //-------------------------------------
    //bIsReadible
    ////m_bRv = objSocket.bIsReadable();
    ////xTEST_EQ(m_bRv, true);

    for (; ;) {
        std::tstring_t sText;

        sText.resize(256);

        std::tcout << xT("> Input text: ");
        std::tcin.getline(&sText[0], sText.size());

        //-------------------------------------
        //iSend
        ssize_t iRv = objSocket.send(sText.c_str(), sText.size(), 0);
        xTEST_DIFF((ssize_t)xSOCKET_ERROR, iRv);
    }

    //-------------------------------------
    //iRecv
    ////m_iRv = objSocket.iRecv(&szRecvBuff[0], ARRAYSIZE(szRecvBuff), 0);
    ////xTEST_DIFF(TcpClient::etError, m_iRv);

    //-------------------------------------
    //bClose
    objSocket.close();

    m_iRv = TcpClient::nativeError();
    //xTEST_EQ(m_bRv, true);
}
//-------------------------------------------------------------------------------------------------
