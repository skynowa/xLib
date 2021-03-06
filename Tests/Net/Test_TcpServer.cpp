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
	{
		// TODO: Test_TcpServer - fix tests
		xTRACE_NOT_IMPLEMENTED

		return true;
	}

    ISocket::AddressFamily afAf       = ISocket::AddressFamily::afInet;
    ISocket::Type          tpType     = ISocket::Type::tpStream;
    ISocket::Protocol      ptProtocol = ISocket::Protocol::ptIp;

    std::ctstring_t         csDomain        = xT("127.0.0.1");
    std::tstring_t          sIp             = xT("");
    ushort_t                usPort          = 80;

    std::tstring_t          sSendBuff       = xT("TEST_STRING");
    tchar_t                 szRecvBuff[1024 * sizeof(tchar_t)]  = {0};

    SocketInit siInit(2, 2);
    TcpServer  objListenSocket;
    TcpServer  objClientSocket;

    objListenSocket.create(afAf, tpType, ptProtocol);
    DnsClient::hostAddrByName(csDomain, &sIp);
    objListenSocket.bind(usPort);
    objListenSocket.listen(xSOCKET_LISTEN_CONNECTIONS_MAX);
    objListenSocket.accept(&objClientSocket, &sIp);

    for ( ; ; ) {
        ssize_t iRv = objClientSocket.receive(&szRecvBuff[0], xARRAY_SIZE(szRecvBuff), 0);
        xTEST_DIFF(iRv, (ssize_t)xSOCKET_ERROR);

        std::tcout << std::tstring_t(szRecvBuff, static_cast<std::size_t>(iRv)) << std::endl;
    }

    objClientSocket.close();

    m_iRv = objListenSocket.send(sSendBuff.c_str(), sSendBuff.size(), 0);
    xTEST_DIFF(m_iRv, xSOCKET_ERROR)

    objListenSocket.close();

    m_iRv = TcpServer::nativeError();
    //// xTEST(m_bRv);

    return true;
}
//-------------------------------------------------------------------------------------------------
