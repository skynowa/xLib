/**
 * \file   CxTest_CxTcpClient.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxTcpClient.h>

#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxDnsClient.h>


//---------------------------------------------------------------------------
CxTest_CxTcpClient::CxTest_CxTcpClient() {

}
//---------------------------------------------------------------------------
CxTest_CxTcpClient::~CxTest_CxTcpClient() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxTcpClient::unit(
    const ulonglong_t &cullCaseLoops
)
{
    CxSocket::ExAddressFamily afAf           = CxSocket::afInet;
    CxSocket::ExType          tpType         = CxSocket::tpStream;
    CxSocket::ExProtocol      ptProtocol     = CxSocket::ptIp;

    const std::tstring_t      csDomain        = xT("127.0.0.1");
    std::tstring_t            sIp            = xT("127.0.0.1");
    ushort_t                  usPort         = 80;
    std::tstring_t            sSendBuff      = xT("TEST_STRING");
    ////char                  szRecvBuff[32] = {0};

    //-------------------------------------
    //�������������
    CxSocketInit      siInit(2, 2);
    CxTcpClient objSocket;

    //-------------------------------------
    //bCreate
    objSocket.create(afAf, tpType, ptProtocol);

    //-------------------------------------
    //bIsServerAlive
    ////m_bRv = objSocket.bIsServerAlive(sIp, usPort);
    ////xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bDnsParse
    CxDnsClient::hostAddrByName(csDomain, &sIp);

    //-------------------------------------
    //bConnect
    objSocket.connect(sIp, usPort);

    //-------------------------------------
    //bIsReadable
    m_bRv = objSocket.isReadable();
    xTEST_EQ(false, m_bRv);

    //-------------------------------------
    //bIsWritable
    m_bRv = objSocket.isWritable();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bGetPeerName
    {
        std::tstring_t _sIp;
        ushort_t       _usPort = 0;

        objSocket.peerName(&_sIp, &_usPort);
    }

    //-------------------------------------
    //bGetSocketName
    {
        std::tstring_t _sIp;
        ushort_t       _usPort = 0;

        objSocket.socketName(&_sIp, &_usPort);
    }

    //-------------------------------------
    //bIsReadible
    ////m_bRv = objSocket.bIsReadable();
    ////xTEST_EQ(true, m_bRv);

    for (; ;) {
        std::tstring_t sText;

        sText.resize(256);

        std::tcout << xT("> Input text: ");
        std::tcin.getline(&sText[0], sText.size());

        //-------------------------------------
        //iSend
        m_iRv = objSocket.send(sText.c_str(), static_cast<int>( sText.size() ), 0);
        xTEST_DIFF(xSOCKET_ERROR, m_iRv);
    }

    //-------------------------------------
    //iRecv
    ////m_iRv = objSocket.iRecv(&szRecvBuff[0], ARRAYSIZE(szRecvBuff), 0);
    ////xTEST_DIFF(CxTcpClient::etError, m_iRv);

    //-------------------------------------
    //bClose
    objSocket.close();

    //-------------------------------------
    //iGetLastError
    m_iRv = CxTcpClient::lastError();
    //xTEST_EQ(true, m_bRv);
}
//---------------------------------------------------------------------------
