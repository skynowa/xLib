/**
 * \file  CxTcpServer.cpp
 * \brief server socket
 */


#include <xLib/Net/CxTcpServer.h>

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

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTcpServer::bind(
    cushort_t &a_port
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_EQ(true, (32767 > a_port) && (0 < a_port));

    struct sockaddr_in saSockAddr = {0};
    saSockAddr.sin_family      = _family;
    saSockAddr.sin_addr.s_addr = INADDR_ANY;
    saSockAddr.sin_port        = htons(a_port);

    int_t iRv = ::bind(_socket, CxUtils::reinterpretCastT<const struct sockaddr *>( &saSockAddr ), sizeof(saSockAddr));
    xTEST_DIFF(xSOCKET_ERROR, iRv);

    ////int_t iOpt = 1;
    //???
    ////if (::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
    ////    return false;
    ////}
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTcpServer::listen(
    cint_t &a_backlog /*= SOMAXCONN*/
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);

    int_t iRv = ::listen(_socket, a_backlog);
    xTEST_DIFF(xSOCKET_ERROR, iRv);
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTcpServer::accept(
    CxTcpServer    *a_serverSocket,
    std::tstring_t *a_fromIp
)
{
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, _socket);
    xTEST_PTR(a_serverSocket);
    xTEST_PTR(a_fromIp);

    socket_t scktClient = xSOCKET_HANDLE_INVALID;

#if xOS_ENV_WIN
    struct sockaddr_in cliaddr  = {0};
    int_t              iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_socket, CxUtils::reinterpretCastT<struct sockaddr *>( &cliaddr ), &iAddrlen);
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, scktClient);
#else
    struct sockaddr_in cliaddr  = {0};
    socklen_t          iAddrlen = sizeof(cliaddr);

    scktClient = ::accept(_socket, CxUtils::reinterpretCastT<struct sockaddr *>( &cliaddr ), &iAddrlen);
    xTEST_DIFF(xSOCKET_HANDLE_INVALID, scktClient);
#endif

    //TODO: bAccept
    ////scktAcceptSocket = scktClient;
    (*a_serverSocket).assign(scktClient);

    //конверт из UNICODE
    std::string asFromIp = ::inet_ntoa(cliaddr.sin_addr);

    (*a_fromIp).assign(asFromIp.begin(), asFromIp.end());
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
