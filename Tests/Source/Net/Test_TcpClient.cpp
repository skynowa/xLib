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

    Socket::ExAddressFamily addressFamily           = Socket::afInet;
    Socket::ExType          type         = Socket::tpStream;
    Socket::ExProtocol      ptProtocol     = Socket::ptIp;

    std::ctstring_t         hostName       = xT("skynowa-pc");
    std::tstring_t          ip             = xT("127.0.0.1");
    ushort_t                port         = 80;
    std::tstring_t          sendBuff      = xT("TEST_STRING");
    char                    recvBuff[32] = {0};

    SocketInit init(2, 2);
    TcpClient  tcpClient;

    tcpClient.create(addressFamily, type, ptProtocol);

    m_bRv = TcpClient::isServerAlive(ip, port);
    xTEST_EQ(m_bRv, true);

    DnsClient::hostAddrByName(hostName, &ip);

    tcpClient.connect(ip, port);

    m_bRv = tcpClient.isReadable();
    xTEST_EQ(m_bRv, false);

    m_bRv = tcpClient.isWritable();
    xTEST_EQ(m_bRv, true);

    {
        std::tstring_t _sIp;
        ushort_t       _usPort = 0;

        tcpClient.peerName(&_sIp, &_usPort);
    }

    {
        std::tstring_t _sIp;
        ushort_t       _usPort = 0;

        tcpClient.socketName(&_sIp, &_usPort);
    }

    m_bRv = tcpClient.isReadable();
    xTEST_EQ(m_bRv, true);

    for ( ; ; ) {
        std::tstring_t sText;

        sText.resize(256);

        std::tcout << xT("> Input text: ");
        std::tcin.getline(&sText[0], sText.size());

        ssize_t iRv = tcpClient.send(sText.c_str(), sText.size(), 0);
        xTEST_DIFF((ssize_t)xSOCKET_ERROR, iRv);
    }

    m_iRv = tcpClient.receive(&recvBuff[0], xARRAY_SIZE(recvBuff), 0);
    xTEST_DIFF(m_iRv, xSOCKET_ERROR)

    tcpClient.close();

    m_iRv = TcpClient::nativeError();
    //// xTEST_EQ(m_bRv, true);
}
//-------------------------------------------------------------------------------------------------
