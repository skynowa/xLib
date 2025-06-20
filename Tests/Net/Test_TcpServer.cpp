/**
 * \file   Test_TcpServer.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_TcpServer)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_TcpServer::unit()
{
	if ( isGithubCI() ) {
		LogCout() << "GithubCI - skip";
		return true;
	}

	if ( !isVpnActive() ) {
		LogCout() << "VPN off - skip";
		return true;
	}

	{
		// TODO: Test_TcpServer - fix tests
		xTRACE_NOT_IMPLEMENTED

		return true;
	}

    ISocket::cAddressFamily afAf       = ISocket::AddressFamily::afInet;
    ISocket::cType          tpType     = ISocket::Type::tpStream;
    ISocket::cProtocol      ptProtocol = ISocket::Protocol::ptIp;

    std::ctstring_t         csDomain   = xT("127.0.0.1");
    std::tstring_t          sIp        = xT("");
    cushort_t               usPort     = 80;

    std::tstring_t          sSendBuff       = xT("TEST_STRING");
    tchar_t                 szRecvBuff[1024 * sizeof(tchar_t)] {};

    SocketInit siInit(2, 2);
    TcpServer  objListenSocket;
    TcpServer  objClientSocket;

    objListenSocket.create(afAf, tpType, ptProtocol);
    objListenSocket.bind(usPort);
    objListenSocket.listen(xSOCKET_LISTEN_CONNECTIONS_MAX);

    DnsClient::hostAddrByName(csDomain, &sIp);
    objListenSocket.accept(&objClientSocket, &sIp);

    for ( ; ; ) {
        ssize_t iRv = objClientSocket.receive(&szRecvBuff[0], xARRAY_SIZE(szRecvBuff), 0);
        xTEST_DIFF(iRv, (ssize_t)xSOCKET_ERROR);

        // LogCout() << std::tstring_t(szRecvBuff, static_cast<std::size_t>(iRv));
    }

    objClientSocket.close();

    m_sstRv = objListenSocket.send(sSendBuff.c_str(), sSendBuff.size(), 0);
    xTEST_DIFF(m_sstRv, (ssize_t)xSOCKET_ERROR)

    objListenSocket.close();

    m_iRv = TcpServer::nativeError();
    xTEST_EQ(m_iRv, 0);

    return true;
}
//-------------------------------------------------------------------------------------------------
