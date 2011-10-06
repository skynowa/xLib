/****************************************************************************
* Class name:  CxTest_CxTcpServer
* Description: test CxTcpServer
* File name:   CxTest_CxTcpServer.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


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
/*virtual*/
BOOL
CxTest_CxTcpServer::bUnit(
    const ULONGLONG cullBlockLoops
)
{
	/*DEBUG*/

	CxSocket::EAddressFamily afAf       = CxSocket::afInet;
	CxSocket::EType          tpType     = CxSocket::tpStream;
	CxSocket::EProtocol      ptProtocol = CxSocket::ptIp;

	const std::tstring     csDomain        = xT("127.0.0.1");
	std::tstring           sIp             = xT("");
	USHORT            usPort          = 80;

	std::tstring           sSendBuff       = xT("TEST_STRING");
	TCHAR             szRecvBuff[1024 * sizeof(TCHAR)]  = {0};

	CxSocketInit      siInit(2, 2);
	CxTcpServer objListenSocket;
	CxTcpServer objClientSocket;

	//-------------------------------------
	//bCreate
	m_bRes = objListenSocket.bCreate(afAf, tpType, ptProtocol);
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bGetHostAddrByName
	m_bRes = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bConnect
	m_bRes = objListenSocket.bBind(usPort);
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bListen
	m_bRes = objListenSocket.bListen(SOMAXCONN);
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bAccept
	m_bRes = objListenSocket.bAccept(&objClientSocket, &sIp);
	xASSERT_NOT_EQ(FALSE, m_bRes);

	for (; ;) {
		//-------------------------------------
		//iRecv
		m_iRes = objClientSocket.iRecv(&szRecvBuff[0], xARRAY_SIZE(szRecvBuff), 0);
		xASSERT_NOT_EQ((INT)CxTcpServer::etError, m_iRes);

		std::tcout << std::tstring(szRecvBuff, m_iRes) << std::endl;
	}

	//-------------------------------------
	//bClose
	m_bRes = objClientSocket.bClose();
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//iSend
	////m_iRes = objSocket.iSend(sSendBuff.c_str(), sSendBuff.size(), 0);
	////xASSERT_NOT_EQ(CxTcpServer::etError, m_iRes);

	//-------------------------------------
	//bClose
	m_bRes = objListenSocket.bClose();
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//iGetLastError
	m_iRes = CxTcpServer::iGetLastError();
	//xASSERT_NOT_EQ(FALSE, m_bRes);

	return TRUE;
}
//---------------------------------------------------------------------------
