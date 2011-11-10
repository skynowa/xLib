/****************************************************************************
* Class name:  CxTest_CxTcpClient
* Description: test CxTcpClient
* File name:   CxTest_CxTcpClient.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxTcpClient.h>

#include <xLib/Net/CxDnsClient.h>


//---------------------------------------------------------------------------
CxTest_CxTcpClient::CxTest_CxTcpClient() {

}
//---------------------------------------------------------------------------
CxTest_CxTcpClient::~CxTest_CxTcpClient() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxTcpClient::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    CxSocket::EAddressFamily afAf           = CxSocket::afInet;
    CxSocket::EType          tpType         = CxSocket::tpStream;
    CxSocket::EProtocol      ptProtocol     = CxSocket::ptIp;

    const std::string_t             csDomain        = xT("127.0.0.1");
    std::string_t                     sIp            = xT("127.0.0.1");
    USHORT                   usPort         = 80;
    std::string_t                  sSendBuff      = xT("TEST_STRING");
    ////char                     szRecvBuff[32] = {0};

    //-------------------------------------
    //�������������
    CxSocketInit      siInit(2, 2);
    CxTcpClient objSocket;

    //-------------------------------------
    //bCreate
    m_bRes = objSocket.bCreate(afAf, tpType, ptProtocol);
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bIsServerAlive
    ////m_bRes = objSocket.bIsServerAlive(sIp, usPort);
    ////xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bDnsParse
    m_bRes = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bConnect
    m_bRes = objSocket.bConnect(sIp, usPort);
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bIsReadable
    m_bRes = objSocket.bIsReadable();
    xTEST_EQ(FALSE, m_bRes);

    //-------------------------------------
    //bIsWritable
    m_bRes = objSocket.bIsWritable();
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //bGetPeerName
    {
        std::string_t _sIp;
        USHORT  _usPort = 0;

        m_bRes = objSocket.bGetPeerName(&_sIp, &_usPort);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bGetSocketName
    {
        std::string_t _sIp;
        USHORT  _usPort = 0;

        m_bRes = objSocket.bGetSocketName(&_sIp, &_usPort);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsReadible
    ////m_bRes = objSocket.bIsReadable();
    ////xTEST_DIFF(FALSE, m_bRes);

    for (; ;) {
        std::string_t sText;

        sText.resize(256);

        std::tcout << xT("> Input text: ");
        std::tcin.getline(&sText[0], sText.size());

        //-------------------------------------
        //iSend
        m_iRes = objSocket.iSend(sText.c_str(), sText.size(), 0);
        xTEST_DIFF((int)CxTcpClient::etError, m_iRes);
    }

    //-------------------------------------
    //iRecv
    ////m_iRes = objSocket.iRecv(&szRecvBuff[0], ARRAYSIZE(szRecvBuff), 0);
    ////xTEST_DIFF(CxTcpClient::etError, m_iRes);

    //-------------------------------------
    //bClose
    m_bRes = objSocket.bClose();
    xTEST_DIFF(FALSE, m_bRes);

    //-------------------------------------
    //iGetLastError
    m_iRes = CxTcpClient::iGetLastError();
    //xTEST_DIFF(FALSE, m_bRes);

    return TRUE;
}
//---------------------------------------------------------------------------
