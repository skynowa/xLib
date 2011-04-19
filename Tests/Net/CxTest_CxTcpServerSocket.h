/****************************************************************************
* Class name:  CxTest_CxTcpServerSocket
* Description: test CxTcpServerSocket
* File name:   CxTest_CxTcpServerSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTcpServerSocketH
#define CxTest_CxTcpServerSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxTcpServerSocket.h> 
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxTcpServerSocket : public CxTest {
	public:
		CxTest_CxTcpServerSocket();
	   ~CxTest_CxTcpServerSocket();

	   /*virtual*/ BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------

#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxDnsClient.h>


//---------------------------------------------------------------------------
//TODO: + CxTest_CxTcpServerSocket (comment)
CxTest_CxTcpServerSocket::CxTest_CxTcpServerSocket() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxTcpServerSocket (comment)
CxTest_CxTcpServerSocket::~CxTest_CxTcpServerSocket() {
	//code
}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxTcpServerSocket::bUnit() {
	/*DEBUG*/

	CxSocket::EAddressFamily afAf       = CxSocket::afIPv4; 
	CxSocket::EType          tpType     = CxSocket::tpStream; 
	CxSocket::EProtocol      ptProtocol = CxSocket::ptIp;

	const tString     csDomain        = xT("127.0.0.1");
	tString           sIp             = xT("");
	USHORT            usPort          = 6666;

	tString           sSendBuff       = xT("TEST_STRING");  
	TCHAR             szRecvBuff[1024 * sizeof(TCHAR)]  = {0};  

	CxSocketInit      siInit(2, 2);
	CxTcpServerSocket objListenSocket; 
	CxTcpServerSocket objClientSocket; 

	//-------------------------------------
	//bCreate
	m_bRes = objListenSocket.bCreate(afAf, tpType, ptProtocol); 
	xASSERT(TRUE == m_bRes);

	//-------------------------------------
	//bGetHostAddrByName
	m_bRes = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
	xASSERT(TRUE == m_bRes);

	//-------------------------------------
	//bConnect
	m_bRes = objListenSocket.bBind(usPort); 
	xASSERT(TRUE == m_bRes);

	//-------------------------------------
	//bListen
	m_bRes = objListenSocket.bListen(SOMAXCONN);
	xASSERT(TRUE == m_bRes);	

	//-------------------------------------
	//bAccept
	m_bRes = objListenSocket.bAccept(&objClientSocket, &sIp);
	xASSERT(FALSE != m_bRes);

	for (; ;) {
		//-------------------------------------
		//iRecv
		m_iRes = objClientSocket.iRecv(&szRecvBuff[0], xARRAY_SIZE(szRecvBuff), 0); 
		xASSERT(CxTcpServerSocket::etError != m_iRes);

		tcout << tString(szRecvBuff, m_iRes) << std::endl;
	}

	//-------------------------------------
	//bClose
	m_bRes = objClientSocket.bClose(); 
	xASSERT(TRUE == m_bRes);

	//-------------------------------------
	//iSend
	////m_iRes = objSocket.iSend(sSendBuff.c_str(), sSendBuff.size(), 0); 
	////xASSERT(CxTcpServerSocket::etError != m_iRes);

	//-------------------------------------
	//bClose
	m_bRes = objListenSocket.bClose(); 
	xASSERT(TRUE == m_bRes);

	//-------------------------------------
	//iGetLastError
	m_iRes = CxTcpServerSocket::iGetLastError(); 
	//xASSERT(TRUE == m_bRes);

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxTcpServerSocketH
