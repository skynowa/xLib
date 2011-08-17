/****************************************************************************
* Class name:  CxTest_CxTcpClientSocket
* Description: test CxTcpClientSocket
* File name:   CxTest_CxTcpClientSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxTcpClientSocket.h>

#include <xLib/Net/CxDnsClient.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxTcpClientSocket
CxTest_CxTcpClientSocket::CxTest_CxTcpClientSocket() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxTcpClientSocket
CxTest_CxTcpClientSocket::~CxTest_CxTcpClientSocket() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxTcpClientSocket::bUnit(
    const ULONGLONG cullBlockLoops
)
{
	CxSocket::EAddressFamily afAf           = CxSocket::afInet;
	CxSocket::EType          tpType         = CxSocket::tpStream;
	CxSocket::EProtocol      ptProtocol     = CxSocket::ptIp;

	const tString			 csDomain		= xT("127.0.0.1");
	tString					 sIp            = xT("127.0.0.1");
	USHORT                   usPort         = 80;
	tString                  sSendBuff      = xT("TEST_STRING");
	////CHAR                     szRecvBuff[32] = {0};

	//-------------------------------------
	//�������������
	CxSocketInit      siInit(2, 2);
	CxTcpClientSocket objSocket;

	//-------------------------------------
	//bCreate
	m_bRes = objSocket.bCreate(afAf, tpType, ptProtocol);
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bIsServerAlive
	////m_bRes = objSocket.bIsServerAlive(sIp, usPort);
	////xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bDnsParse
	m_bRes = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bConnect
	m_bRes = objSocket.bConnect(sIp, usPort);
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bIsReadable
	m_bRes = objSocket.bIsReadable();
	xASSERT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bIsWritable
	m_bRes = objSocket.bIsWritable();
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//bGetPeerName
	{
		tString sIp;
		USHORT  usPort = 0;

		m_bRes = objSocket.bGetPeerName(&sIp, &usPort);
		xASSERT_NOT_EQ(FALSE, m_bRes);
	}

	//-------------------------------------
	//bGetSocketName
	{
		tString sIp;
		USHORT  usPort = 0;

		m_bRes = objSocket.bGetSocketName(&sIp, &usPort);
		xASSERT_NOT_EQ(FALSE, m_bRes);
	}

	//-------------------------------------
	//bIsReadible
	////m_bRes = objSocket.bIsReadable();
	////xASSERT_NOT_EQ(FALSE, m_bRes);

	for (; ;) {
		tString sText;

		sText.resize(256);

		tcout << xT("> Input text: ");
		tcin.getline(&sText[0], sText.size());

		//-------------------------------------
		//iSend
		m_iRes = objSocket.iSend(sText.c_str(), sText.size(), 0);
		xASSERT_NOT_EQ((INT)CxTcpClientSocket::etError, m_iRes);
	}

	//-------------------------------------
	//iRecv
	////m_iRes = objSocket.iRecv(&szRecvBuff[0], ARRAYSIZE(szRecvBuff), 0);
	////xASSERT_NOT_EQ(CxTcpClientSocket::etError, m_iRes);

	//-------------------------------------
	//bClose
	m_bRes = objSocket.bClose();
	xASSERT_NOT_EQ(FALSE, m_bRes);

	//-------------------------------------
	//iGetLastError
	m_iRes = CxTcpClientSocket::iGetLastError();
	//xASSERT_NOT_EQ(FALSE, m_bRes);

	return TRUE;
}
//---------------------------------------------------------------------------
