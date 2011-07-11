/****************************************************************************
* Class name:  CxTest_CxTcpClientSocket
* Description: test CxTcpClientSocket
* File name:   CxTest_CxTcpClientSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTcpClientSocketH
#define CxTest_CxTcpClientSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxTcpClientSocket.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxTcpClientSocket :
    public CxTest
{
	public:
		CxTest_CxTcpClientSocket();
		virtual     ~CxTest_CxTcpClientSocket();

	   virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------

#include <xLib/Net/CxDnsClient.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxTcpClientSocket (comment)
CxTest_CxTcpClientSocket::CxTest_CxTcpClientSocket() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxTcpClientSocket (comment)
CxTest_CxTcpClientSocket::~CxTest_CxTcpClientSocket() {
	//code
}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL CxTest_CxTcpClientSocket::bUnit() {
	CxSocket::EAddressFamily afAf           = CxSocket::afInet;
	CxSocket::EType          tpType         = CxSocket::tpStream;
	CxSocket::EProtocol      ptProtocol     = CxSocket::ptIp;

	const tString			 csDomain		= xT("127.0.0.1");
	tString					 sIp            = xT("127.0.0.1");
	USHORT                   usPort         = 6666;
	tString                  sSendBuff      = xT("TEST_STRING");
	////CHAR                     szRecvBuff[32] = {0};

	//-------------------------------------
	//�������������
	CxSocketInit      siInit(2, 2);
	CxTcpClientSocket objSocket;

	//-------------------------------------
	//bCreate
	m_bRes = objSocket.bCreate(afAf, tpType, ptProtocol);
	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//bIsServerAlive
	////m_bRes = objSocket.bIsServerAlive(sIp, usPort);
	////xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//bDnsParse
	m_bRes = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//bConnect
	m_bRes = objSocket.bConnect(sIp, usPort);
	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//bIsReadable
	m_bRes = objSocket.bIsReadable();
	xASSERT(FALSE == m_bRes);

	//-------------------------------------
	//bIsWritable
	m_bRes = objSocket.bIsWritable();
	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//bGetPeerName
	{
		tString sIp;
		USHORT  usPort = 0;

		m_bRes = objSocket.bGetPeerName(&sIp, &usPort);
		xASSERT(FALSE != m_bRes);
	}

	//-------------------------------------
	//bGetSocketName
	{
		tString sIp;
		USHORT  usPort = 0;

		m_bRes = objSocket.bGetSocketName(&sIp, &usPort);
		xASSERT(FALSE != m_bRes);
	}

	//-------------------------------------
	//bIsReadible
	////m_bRes = objSocket.bIsReadable();
	////xASSERT(FALSE != m_bRes);

	for (; ;) {
		tString sText;

		sText.resize(256);

		tcout << xT("> Input text: ");
		tcin.getline(&sText[0], sText.size());

		//-------------------------------------
		//iSend
		m_iRes = objSocket.iSend(sText.c_str(), sText.size(), 0);
		xASSERT(CxTcpClientSocket::etError != m_iRes);
	}

	//-------------------------------------
	//iRecv
	////m_iRes = objSocket.iRecv(&szRecvBuff[0], ARRAYSIZE(szRecvBuff), 0);
	////xASSERT(CxTcpClientSocket::etError != m_iRes);

	//-------------------------------------
	//bClose
	m_bRes = objSocket.bClose();
	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//iGetLastError
	m_iRes = CxTcpClientSocket::iGetLastError();
	//xASSERT(FALSE != m_bRes);

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxTcpClientSocketH

