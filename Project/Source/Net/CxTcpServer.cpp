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
    ushort_t usPort
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_sktSocket,        false);
    /*DEBUG*/xASSERT_RET((32767 > usPort) && (0 < usPort), false);

    struct sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = INADDR_ANY;
    saSockAddr.sin_port        = htons(usPort);

    int iRv = ::bind(_m_sktSocket, CxMacros::reinterpretCastT<const struct sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/xASSERT_RET(etError != iRv, false);

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
    int iBacklog /*= SOMAXCONN*/
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_sktSocket, false);

    int iRv = ::listen(_m_sktSocket, iBacklog);
    /*DEBUG*/xASSERT_RET(etError != iRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxTcpServer::bAccept(
    CxTcpServer *pscktAcceptSocket,
    std::tstring_t      *psFromIp
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_sktSocket,      false);
    /*DEBUG*/xASSERT_RET(NULL      != pscktAcceptSocket, false);
    /*DEBUG*/xASSERT_RET(NULL      != psFromIp,          false);

    socket_t scktClient = etInvalid;

#if xOS_ENV_WIN
    struct sockaddr_in cliaddr  = {0};
    int                iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_m_sktSocket, CxMacros::reinterpretCastT<struct sockaddr *>( &cliaddr ), &iAddrlen);
    /*DEBUG*/xASSERT_RET(etInvalid != scktClient, false);
#elif xOS_ENV_UNIX
    struct sockaddr_in cliaddr  = {0};
    socklen_t          iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_m_sktSocket, CxMacros::reinterpretCastT<struct sockaddr *>( &cliaddr ), &iAddrlen);
    /*DEBUG*/xASSERT_RET(etInvalid != scktClient, false);
#endif

    //TODO: bAccept
    ////scktAcceptSocket = scktClient;
    bool bRv = (* pscktAcceptSocket).bAssign(scktClient);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //конверт из UNICODE
    std::string asFromIp = ::inet_ntoa(cliaddr.sin_addr);

    (*psFromIp).assign(asFromIp.begin(), asFromIp.end());

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
