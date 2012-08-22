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
/*virtual*/
bool
CxTest_CxTcpClient::bUnit(
    const ulonglong_t cullCaseLoops
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
    m_bRv = objSocket.bCreate(afAf, tpType, ptProtocol);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bIsServerAlive
    ////m_bRv = objSocket.bIsServerAlive(sIp, usPort);
    ////xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bDnsParse
    m_bRv = CxDnsClient::bGetHostAddrByName(csDomain, &sIp);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bConnect
    m_bRv = objSocket.bConnect(sIp, usPort);
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bIsReadable
    m_bRv = objSocket.bIsReadable();
    xTEST_EQ(false, m_bRv);

    //-------------------------------------
    //bIsWritable
    m_bRv = objSocket.bIsWritable();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //bGetPeerName
    {
        std::tstring_t _sIp;
        ushort_t  _usPort = 0;

        m_bRv = objSocket.bGetPeerName(&_sIp, &_usPort);
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bGetSocketName
    {
        std::tstring_t _sIp;
        ushort_t  _usPort = 0;

        m_bRv = objSocket.bGetSocketName(&_sIp, &_usPort);
        xTEST_EQ(true, m_bRv);
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
        m_iRv = objSocket.iSend(sText.c_str(), sText.size(), 0);
        xTEST_DIFF((int)CxTcpClient::etError, m_iRv);
    }

    //-------------------------------------
    //iRecv
    ////m_iRv = objSocket.iRecv(&szRecvBuff[0], ARRAYSIZE(szRecvBuff), 0);
    ////xTEST_DIFF(CxTcpClient::etError, m_iRv);

    //-------------------------------------
    //bClose
    m_bRv = objSocket.bClose();
    xTEST_EQ(true, m_bRv);

    //-------------------------------------
    //iGetLastError
    m_iRv = CxTcpClient::iGetLastError();
    //xTEST_EQ(true, m_bRv);

    return true;
}
//---------------------------------------------------------------------------
