/**
 * \file   Test_TcpClient.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_TcpClient)
xTEST_UNIT(Test_TcpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_TcpClient::unit()
{
    ISocket::ExAddressFamily addressFamily = ISocket::afInet;
    ISocket::ExType          type          = ISocket::tpStream;
    ISocket::ExProtocol      ptProtocol    = ISocket::ptIp;

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

	xTEST_CASE("SocketInit")
	{
		SocketInit init(2, 2);
	}

    TcpClient tcpClient;

	xTEST_CASE("create")
	{
		tcpClient.create(addressFamily, type, ptProtocol);
	}

	xTEST_CASE("isServerAlive")
	{
		m_bRv = TcpClient::isServerAlive(ip, port);
		xTEST_EQ(m_bRv, true);

		std::tstring_t ipFromDns;
		DnsClient::hostAddrByName(hostName, &ipFromDns);
		xTEST_EQ(ip, ipFromDns);
	}

	xTEST_CASE("connect")
	{
		tcpClient.connect(ip, port);
	}

	xTEST_CASE("isReadable")
	{
		m_bRv = tcpClient.isReadable();
		xTEST_EQ(m_bRv, false);
	}

	xTEST_CASE("isWritable")
	{
		m_bRv = tcpClient.isWritable();
		xTEST_EQ(m_bRv, false);
	}

	xTEST_CASE("peerName")
    {
        std::tstring_t _ip;
        ushort_t       _port = 0;

        tcpClient.peerName(&_ip, &_port);
    }

	xTEST_CASE("socketName")
    {
        std::tstring_t _ip;
        ushort_t       _port = 0;

        tcpClient.socketName(&_ip, &_port);
    }

	xTEST_CASE("isReadable")
	{
		m_bRv = tcpClient.isReadable();
		xTEST_EQ(m_bRv, false);
	}

	xTEST_CASE("send")
	{
		for ( ; ; ) {
			std::tstring_t text;

			text.resize(256);

			std::tcout << xT("> Input text: ");
			std::tcin.getline(&text[0], static_cast<std::streamsize>( text.size() ));

			m_sstRv = tcpClient.send(text.c_str(), text.size(), 0);
			xTEST_DIFF(m_sstRv, (ssize_t)xSOCKET_ERROR);
		}
	}

	xTEST_CASE("receive")
	{
		m_sstRv = tcpClient.receive(&recvBuff[0], xARRAY_SIZE(recvBuff), 0);
		xTEST_DIFF(m_sstRv, (ssize_t)xSOCKET_ERROR)
	}

	xTEST_CASE("close")
	{
		tcpClient.close();
	}

	xTEST_CASE("nativeError")
	{
		m_iRv = TcpClient::nativeError();
		xTEST_EQ(m_iRv, 0);
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
