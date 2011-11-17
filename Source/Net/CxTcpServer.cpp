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
BOOL
CxTcpServer::bBind(
    USHORT usPort
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,        FALSE);
    /*DEBUG*/xASSERT_RET((32767 > usPort) && (0 < usPort), FALSE);

    struct sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _m_siFamily;
    saSockAddr.sin_addr.s_addr = INADDR_ANY;
    saSockAddr.sin_port        = htons(usPort);

    int iRes = ::bind(_m_puiSocket, CxMacros::xreinterpret_cast<const struct sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);

    ////int iOpt = 1;
    //???
    ////if (::setsockopt(_m_puiSocket, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
    ////    return FALSE;
    ////}

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxTcpServer::bListen(
    int iBacklog /*= SOMAXCONN*/
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket, FALSE);

    int iRes = ::listen(_m_puiSocket, iBacklog);
    /*DEBUG*/xASSERT_RET(etError != iRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxTcpServer::bAccept(
    CxTcpServer *pscktAcceptSocket,
    std::string_t      *psFromIp
)
{
    /*DEBUG*/xASSERT_RET(etInvalid != _m_puiSocket,      FALSE);
    /*DEBUG*/xASSERT_RET(NULL      != pscktAcceptSocket, FALSE);
    /*DEBUG*/xASSERT_RET(NULL      != psFromIp,          FALSE);

    SOCKET scktClient = etInvalid;

#if xOS_ENV_WIN
    struct sockaddr_in cliaddr  = {0};
    int                iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_m_puiSocket, CxMacros::xreinterpret_cast<struct sockaddr *>( &cliaddr ), &iAddrlen);
    /*DEBUG*/xASSERT_RET(etInvalid != scktClient, FALSE);
#elif xOS_ENV_UNIX
    struct sockaddr_in cliaddr  = {0};
    socklen_t          iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_m_puiSocket, CxMacros::xreinterpret_cast<struct sockaddr *>( &cliaddr ), &iAddrlen);
    /*DEBUG*/xASSERT_RET(etInvalid != scktClient, FALSE);
#endif

    //TODO: bAccept
    ////scktAcceptSocket = scktClient;
    BOOL bRes = (* pscktAcceptSocket).bAssign(scktClient);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //конверт из UNICODE
    std::string asFromIp = ::inet_ntoa(cliaddr.sin_addr);

    (*psFromIp).assign(asFromIp.begin(), asFromIp.end());

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

