/**
 * \file  CxTcpServer.cpp
 * \brief server socket
 */


#include <xLib/Net/CxTcpServer.h>


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
CxTcpServer::CxTcpServer() {

}
//---------------------------------------------------------------------------
CxTcpServer::~CxTcpServer() {

}
//---------------------------------------------------------------------------
bool
CxTcpServer::bBind(
    ushort_t a_usPort
)
{
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);
    /*DEBUG*/xTEST_EQ(true, (32767 > a_usPort) && (0 < a_usPort));

    struct sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = INADDR_ANY;
    saSockAddr.sin_port        = htons(a_usPort);

    int iRv = ::bind(_m_sktSocket, CxUtils::reinterpretCastT<const struct sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);

    ////int iOpt = 1;
    //???
    ////if (::setsockopt(_m_sktSocket, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
    ////    return false;
    ////}

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpServer::bListen(
    int a_iBacklog /*= SOMAXCONN*/
)
{
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);

    int iRv = ::listen(_m_sktSocket, a_iBacklog);
    /*DEBUG*/xTEST_DIFF(xSOCKET_ERROR, iRv);

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpServer::bAccept(
    CxTcpServer    *a_pscktAcceptSocket,
    std::tstring_t *a_psFromIp
)
{
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);
    /*DEBUG*/xTEST_PTR(a_pscktAcceptSocket);
    /*DEBUG*/xTEST_PTR(a_psFromIp);

    socket_t scktClient = xSOCKET_HANDLE_INVALID;

#if   xOS_ENV_WIN
    struct sockaddr_in cliaddr  = {0};
    int                iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_m_sktSocket, CxUtils::reinterpretCastT<struct sockaddr *>( &cliaddr ), &iAddrlen);
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, scktClient);
#elif xOS_ENV_UNIX
    struct sockaddr_in cliaddr  = {0};
    socklen_t          iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_m_sktSocket, CxUtils::reinterpretCastT<struct sockaddr *>( &cliaddr ), &iAddrlen);
    /*DEBUG*/xTEST_DIFF(xSOCKET_HANDLE_INVALID, scktClient);
#endif

    //TODO: bAccept
    ////scktAcceptSocket = scktClient;
    bool bRv = (*a_pscktAcceptSocket).bAssign(scktClient);
    /*DEBUG*/xTEST_EQ(true, bRv);

    //конверт из UNICODE
    std::string asFromIp = ::inet_ntoa(cliaddr.sin_addr);

    (*a_psFromIp).assign(asFromIp.begin(), asFromIp.end());

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
