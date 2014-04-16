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
#include <xLib/Log/CxTrace.h>
#include <xLib/Core/CxUtils.h>

xNAMESPACE2_BEGIN(xlib, net)

//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpServer::bind(
    cushort_t &a_port
) const
{
    xTEST_DIFF(_socket, xSOCKET_HANDLE_INVALID);
    xTEST_EQ((a_port > 0) && (a_port < 32767), true);

    sockaddr_in sockAddr;    xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = _family;
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port        = htons(a_port);

    int_t iRv = ::bind(_socket, CxUtils::reinterpretCastT<const sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_DIFF(iRv, xSOCKET_ERROR);

#if 0
    int_t iOpt = 1;

    if (::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
        return false;
    }
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpServer::listen(
    cint_t &a_backlog /* = xSOCKET_CONNECTIONS_MAX */
) const
{
    xTEST_DIFF(_socket, xSOCKET_HANDLE_INVALID);

    int_t iRv = ::listen(_socket, a_backlog);
    xTEST_DIFF(iRv, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTcpServer::accept(
    CxTcpServer    *a_serverSocket,
    std::tstring_t *a_fromIp
) const
{
    xTEST_DIFF(_socket, xSOCKET_HANDLE_INVALID);
    xTEST_PTR(a_serverSocket);
    xTEST_PTR(a_fromIp);

    socket_t client = xSOCKET_HANDLE_INVALID;

#if   xOS_ENV_WIN
    sockaddr_in cliaddr = {0};
    int_t       addrlen = sizeof(cliaddr);

    client = ::accept(_socket, CxUtils::reinterpretCastT<sockaddr *>( &cliaddr ), &addrlen);
    xTEST_DIFF(client, xSOCKET_HANDLE_INVALID);
#elif xOS_ENV_UNIX
    sockaddr_in cliaddr; xSTRUCT_ZERO(cliaddr);
    socklen_t   addrlen = sizeof(cliaddr);

    client = ::accept(_socket, CxUtils::reinterpretCastT<sockaddr *>( &cliaddr ), &addrlen);
    xTEST_DIFF(client, xSOCKET_HANDLE_INVALID);
#endif

#if 0
    // TODO: CxTcpServer::accept()
    scktAcceptSocket = client;
#endif
    a_serverSocket->assign(client);

    // convert from UNICODE
    std::string fromIp = ::inet_ntoa(cliaddr.sin_addr);

    a_fromIp->assign(fromIp.begin(), fromIp.end());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, net)
