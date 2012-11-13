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
void
CxTcpServer::vBind(
    const ushort_t &a_cusPort
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);
    xTEST_EQ(true, (32767 > a_cusPort) && (0 < a_cusPort));

    struct sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = INADDR_ANY;
    saSockAddr.sin_port        = htons(a_cusPort);

    int iRv = ::bind(_m_sktSocket, CxUtils::reinterpretCastT<const struct sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    xTEST_DIFF(xSOCKET_ERROR, iRv);

    ////int iOpt = 1;
    //???
    ////if (::setsockopt(_m_sktSocket, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
    ////    return false;
    ////}
}
//---------------------------------------------------------------------------
void
CxTcpServer::vListen(
    const int &a_ciBacklog /*= SOMAXCONN*/
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);

    int iRv = ::listen(_m_sktSocket, a_ciBacklog);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
}
//---------------------------------------------------------------------------
void
CxTcpServer::vAccept(
    CxTcpServer    *a_pscktAcceptSocket,
    std::tstring_t *a_psFromIp
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _m_sktSocket);
    xTEST_PTR(a_pscktAcceptSocket);
    xTEST_PTR(a_psFromIp);

    socket_t scktClient = xSOCKET_HANDLE_INVALID;

#if   xOS_ENV_WIN
    struct sockaddr_in cliaddr  = {0};
    int                iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_m_sktSocket, CxUtils::reinterpretCastT<struct sockaddr *>( &cliaddr ), &iAddrlen);
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, scktClient);
#elif xOS_ENV_UNIX
    struct sockaddr_in cliaddr  = {0};
    socklen_t          iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_m_sktSocket, CxUtils::reinterpretCastT<struct sockaddr *>( &cliaddr ), &iAddrlen);
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, scktClient);
#endif

    //TODO: bAccept
    ////scktAcceptSocket = scktClient;
    (*a_pscktAcceptSocket).vAssign(scktClient);

    //конверт из UNICODE
    std::string asFromIp = ::inet_ntoa(cliaddr.sin_addr);

    (*a_psFromIp).assign(asFromIp.begin(), asFromIp.end());
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
