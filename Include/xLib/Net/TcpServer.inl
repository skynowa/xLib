/**
 * \file  TcpServer.inl
 * \brief server socket
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/LastError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>
#include <xLib/Core/Utils.h>

xNAMESPACE_BEGIN2(xlib, net)

//-------------------------------------------------------------------------------------------------
inline void_t
TcpServer::bind(
    cushort_t &a_port
) const
{
    xTEST_DIFF(_handle, xSOCKET_HANDLE_INVALID);
    xTEST_NA(a_port);

    sockaddr_in sockAddr;    xSTRUCT_ZERO(sockAddr);
    sockAddr.sin_family      = _family;
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port        = htons(a_port);

    int_t iRv = ::bind(_handle, Utils::reinterpretCastT<const sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_DIFF(iRv, xSOCKET_ERROR);

#if 0
    int_t iOpt = 1;

    if (::setsockopt(_handle, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
        return false;
    }
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
TcpServer::listen(
    cint_t &a_backlog /* = xSOCKET_CONNECTIONS_MAX */
) const
{
    xTEST_DIFF(_handle, xSOCKET_HANDLE_INVALID);

    int_t iRv = ::listen(_handle, a_backlog);
    xTEST_DIFF(iRv, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------
inline void_t
TcpServer::accept(
    TcpServer    *a_serverSocket,
    std::tstring_t *a_fromIp
) const
{
    xTEST_DIFF(_handle, xSOCKET_HANDLE_INVALID);
    xTEST_PTR(a_serverSocket);
    xTEST_PTR(a_fromIp);

    sockaddr_in     cliaddr; xSTRUCT_ZERO(cliaddr);
    socket_length_t addrlen = sizeof(cliaddr);

    socket_t client = ::accept(_handle, Utils::reinterpretCastT<sockaddr *>( &cliaddr ), &addrlen);
    xTEST_DIFF(client, xSOCKET_HANDLE_INVALID);

#if 0
    // TODO: TcpServer::accept()
    scktAcceptSocket.assign(client);
#endif
    a_serverSocket->assign(client);

    // convert from UNICODE
    std::string fromIp = ::inet_ntoa(cliaddr.sin_addr);

    a_fromIp->assign(fromIp.begin(), fromIp.end());
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
