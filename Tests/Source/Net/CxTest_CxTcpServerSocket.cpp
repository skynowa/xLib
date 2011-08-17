/****************************************************************************
* Class name:  CxTest_CxTcpServerSocket
* Description: test CxTcpServerSocket
* File name:   CxTest_CxTcpServerSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxTcpServerSocket.h>

#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxDnsClient.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxTcpServerSocket
CxTest_CxTcpServerSocket::CxTest_CxTcpServerSocket() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxTcpServerSocket
CxTest_CxTcpServerSocket::~CxTest_CxTcpServerSocket() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxTcpServerSocket::bUnit(
    const ULONGLONG cullBlockLoops
)
{
	/*DEBUG*/

	CxSocket::EAddressFamily afAf       = CxSocket::afInet;
	CxSocket::EType          tpType     = CxSocket::tpStream;
	CxSocket::EProtocol      ptProtocol = CxSocket::ptIp;

	const tString     csDomain        = xT("127.0.0.1");
	tString           sIp             = xT("");
	USHORT            usPort          = 80;

	tString           sSendBuff       = xT("TEST_STRING");
	TCHAR             szRecvBuff[1024 * sizeof(TCHAR)]  = {0};

	CxSocketInit      siInit(2, 2);
	CxTcpServerSocket objListenSocket;
	CxTcpServerSocket objClientSocket;

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
		xASSERT_NOT_EQ((INT)CxTcpServerSocket::etError, m_iRes);

		tcout << tString(szRecvBuff, m_iRes) << std::endl;
	}

	//-------------------------------------
	//bClose
	m_bRes = objClientSocket.bClose();
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//iSend
	////m_iRes = objSocket.iSend(sSendBuff.c_str(), sSendBuff.size(), 0);
	////xASSERT_NOT_EQ(CxTcpServerSocket::etError, m_iRes);

	//-------------------------------------
	//bClose
	m_bRes = objListenSocket.bClose();
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//iGetLastError
	m_iRes = CxTcpServerSocket::iGetLastError();
	//xASSERT_NOT_EQ(FALSE, m_bRes);

	return TRUE;
}
//---------------------------------------------------------------------------
