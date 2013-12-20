/**
 * \file  CxTcpServer.cpp
 * \brief server socket
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>
#include <xLib/Core/CxUtils.h>

xNAMESPACE_BEGIN(NxLib)

//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpServer::bind(
    cushort_t &a_port
) const
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_EQ(true, (32767 > a_port) && (0 < a_port));

    struct sockaddr_in sockAddr;    xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = _family;
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port        = htons(a_port);

    int_t iRv = ::bind(_socket, CxUtils::reinterpretCastT<const struct sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_DIFF(xSOCKET_ERROR, iRv);

    ////int_t iOpt = 1;
    //???
    ////if (::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
    ////    return false;
    ////}
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpServer::listen(
    cint_t &a_backlog /*= SOMAXCONN*/
) const
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);

    int_t iRv = ::listen(_socket, a_backlog);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpServer::accept(
    CxTcpServer    *a_serverSocket,
    std::tstring_t *a_fromIp
) const
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_PTR(a_serverSocket);
    xTEST_PTR(a_fromIp);

    socket_t scktClient = xSOCKET_HANDLE_INVALID;

#if   xOS_ENV_WIN
    struct sockaddr_in cliaddr = {0};
    int_t              addrlen = sizeof(cliaddr);

    scktClient = ::accept(_socket, CxUtils::reinterpretCastT<struct sockaddr *>( &cliaddr ),
        &addrlen);
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, scktClient);
#elif xOS_ENV_UNIX
    struct sockaddr_in cliaddr; xSTRUCT_ZERO(cliaddr);
    socklen_t          addrlen = sizeof(cliaddr);

    scktClient = ::accept(_socket, CxUtils::reinterpretCastT<struct sockaddr *>( &cliaddr ),
        &addrlen);
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, scktClient);
#endif

    //TODO: bAccept
    ////scktAcceptSocket = scktClient;
    a_serverSocket->assign(scktClient);

    //конверт из UNICODE
    std::string fromIp = ::inet_ntoa(cliaddr.sin_addr);

    a_fromIp->assign(fromIp.begin(), fromIp.end());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
