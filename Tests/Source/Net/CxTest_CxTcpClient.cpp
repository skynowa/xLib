/**
 * \file   CxTest_CxTcpClient.cpp
 * \brief
 */


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
bool
CxTest_CxTcpClient::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    CxSocket::EAddressFamily afAf           = CxSocket::afInet;
    CxSocket::EType          tpType         = CxSocket::tpStream;
    CxSocket::EProtocol      ptProtocol     = CxSocket::ptIp;

    const std::tstring_t             csDomain        = xT("127.0.0.1");
    std::tstring_t                     sIp            = xT("127.0.0.1");
    ushort_t                   usPort         = 80;
    std::tstring_t                  sSendBuff      = xT("TEST_STRING");
    ////char                     szRecvBuff[32] = {0};

    //-------------------------------------
    //�������������
    CxSocketInit      siInit(2, 2);
    CxTcpClient objSocket;

    //-------------------------------------
    //bCreate
    m_bRes = objSocket.bCreate(afAf, tpType, ptProtocol);
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bIsServerAlive
    ////m_bRes = objSocket.bIsServerAlive(sIp, usPort);
    ////xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bDnsParse
    m_bRes = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bConnect
    m_bRes = objSocket.bConnect(sIp, usPort);
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bIsReadable
    m_bRes = objSocket.bIsReadable();
    xTEST_EQ(false, m_bRes);

    //-------------------------------------
    //bIsWritable
    m_bRes = objSocket.bIsWritable();
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //bGetPeerName
    {
        std::tstring_t _sIp;
        ushort_t  _usPort = 0;

        m_bRes = objSocket.bGetPeerName(&_sIp, &_usPort);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bGetSocketName
    {
        std::tstring_t _sIp;
        ushort_t  _usPort = 0;

        m_bRes = objSocket.bGetSocketName(&_sIp, &_usPort);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bIsReadible
    ////m_bRes = objSocket.bIsReadable();
    ////xTEST_DIFF(false, m_bRes);

    for (; ;) {
        std::tstring_t sText;

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
    xTEST_DIFF(false, m_bRes);

    //-------------------------------------
    //iGetLastError
    m_iRes = CxTcpClient::iGetLastError();
    //xTEST_DIFF(false, m_bRes);

    return true;
}
//---------------------------------------------------------------------------
