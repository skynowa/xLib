/**
 * \file   Test_TcpClient.cpp
 * \brief
 */


#include "Test_TcpClient.h"

#include <xLib/Net/SocketInit.h>
#include <xLib/Net/DnsClient.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_TcpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_TcpClient::unit()
{
    Socket::ExAddressFamily addressFamily = Socket::afInet;
    Socket::ExType          type          = Socket::tpStream;
    Socket::ExProtocol      ptProtocol    = Socket::ptIp;

#if 0
	std::ctstring_t         hostName      = xT("skynowa-pc");
	std::tstring_t          ip            = xT("127.0.0.1");
    ushort_t                port          = 80;
#else
	std::ctstring_t         hostName      = xT("jail.skynowa");
	std::tstring_t          ip            = xT("192.168.12.206");
    ushort_t                port          = 22;
#endif

    std::tstring_t          sendBuff      = xT("TEST_STRING");
    char                    recvBuff[32]  = {0};

    SocketInit init(2, 2);
    TcpClient  tcpClient;

    tcpClient.create(addressFamily, type, ptProtocol);

    m_bRv = TcpClient::isServerAlive(ip, port);
    xTEST_EQ(m_bRv, true);

    DnsClient::hostAddrByName(hostName, &ip);

    Trace() << xTRACE_VAR(hostName);
    Trace() << xTRACE_VAR(ip);
    Trace() << xTRACE_VAR(port);

    tcpClient.connect(ip, port);

    m_bRv = tcpClient.isReadable();
    xTEST_EQ(m_bRv, false);

    m_bRv = tcpClient.isWritable();
    xTEST_EQ(m_bRv, true);

    {
        std::tstring_t _ip;
        ushort_t       _port = 0;

        tcpClient.peerName(&_ip, &_port);
    }

    {
        std::tstring_t _ip;
        ushort_t       _port = 0;

        tcpClient.socketName(&_ip, &_port);
    }

    m_bRv = tcpClient.isReadable();
    xTEST_EQ(m_bRv, true);

    for ( ; ; ) {
        std::tstring_t text;

        text.resize(256);

        std::tcout << xT("> Input text: ");
        std::tcin.getline(&text[0], text.size());

        ssize_t iRv = tcpClient.send(text.c_str(), text.size(), 0);
        xTEST_DIFF((ssize_t)xSOCKET_ERROR, iRv);
    }

    m_iRv = tcpClient.receive(&recvBuff[0], xARRAY_SIZE(recvBuff), 0);
    xTEST_DIFF(m_iRv, xSOCKET_ERROR)

    tcpClient.close();

    m_iRv = TcpClient::nativeError();
    //// xTEST_EQ(m_bRv, true);

    return true;
}
//-------------------------------------------------------------------------------------------------
