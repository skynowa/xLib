/**
 * \file   Test_TcpClient.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_TcpClient)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_TcpClient::unit()
{
	if ( isGithubCI() ) {
		LogCout() << "GithubCI - skip";
		return true;
	}

	if ( !isVpnActive() ) {
		LogCout() << "VPN off - skip";
		return true;
	}

    ISocket::cAddressFamily addressFamily = ISocket::AddressFamily::afInet;
    ISocket::cType          type          = ISocket::Type::tpStream;
    ISocket::cProtocol      ptProtocol    = ISocket::Protocol::ptIp;

	std::ctstring_t         hostName      = xT("localhost");
	std::tstring_t          ip            = xT("127.0.0.1");
    cushort_t               port          {80};

    std::ctstring_t         sendBuff      = xT("TEST_STRING");
    char                    recvBuff[32]  {};

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
		xTEST(m_bRv);

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
		xTEST(!m_bRv);
	}

	xTEST_CASE("isWritable")
	{
		m_bRv = tcpClient.isWritable();
		xTEST(!m_bRv);
	}

	xTEST_CASE("peerName")
    {
		std::tstring_t _ip;
		ushort_t       _port {};

		tcpClient.peerName(&_ip, &_port);
    }

	xTEST_CASE("socketName")
    {
		std::tstring_t _ip;
		ushort_t       _port {};

		tcpClient.socketName(&_ip, &_port);
    }

	xTEST_CASE("isReadable")
	{
		m_bRv = tcpClient.isReadable();
		xTEST(!m_bRv);
	}

	xTEST_CASE("send")
	{
		// TEST: send
		if (false) {
			for (size_t i {}; i < 3; ++ i) {
				std::tstring_t text;
				text.resize(256);

				std::tcout << xT("> Input text: ");
				std::tcin.getline(&text[0], static_cast<std::streamsize>( text.size() ));

				m_sstRv = tcpClient.send(text.c_str(), text.size(), 0);
				xTEST_DIFF(m_sstRv, (ssize_t)xSOCKET_ERROR);
			}
		}
	}

	xTEST_CASE("receive")
	{
		// TEST: receive
		if (false) {
			m_sstRv = tcpClient.receive(&recvBuff[0], xARRAY_SIZE(recvBuff), 0);
			xTEST_DIFF(m_sstRv, (ssize_t)xSOCKET_ERROR);

			LogCout() << xTRACE_VAR(recvBuff);
		}
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
