/**
 * \file  TcpServer.inl
 * \brief server socket
 */


#include "TcpServer.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>
#include <xLib/Core/Utils.h>

xNAMESPACE_BEGIN2(xl, net)

//-------------------------------------------------------------------------------------------------
void_t
TcpServer::bind(
    cushort_t &a_port
) const
{
    xTEST_EQ(_handle.isValid(), true);
    xTEST_NA(a_port);

    sockaddr_in sockAddr;    Utils::structZeroT(sockAddr);
    sockAddr.sin_family      = static_cast<sa_family_t>(_family);
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port        = htons(a_port);

    int_t iRv = ::bind(_handle.get(), Utils::reinterpretCastT<const sockaddr *>( &sockAddr ),
        sizeof(sockAddr));
    xTEST_DIFF(iRv, xSOCKET_ERROR);

#if 0
    int_t iOpt = 1;

    if (::setsockopt(_handle.get(), SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(iOpt)) < 0) {
        return false;
    }
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
TcpServer::listen(
    cint_t &a_backlog /* = xSOCKET_LISTEN_CONNECTIONS_MAX */
) const
{
    xTEST_EQ(_handle.isValid(), true);

    int_t iRv = ::listen(_handle.get(), a_backlog);
    xTEST_DIFF(iRv, xSOCKET_ERROR);
}
//-------------------------------------------------------------------------------------------------
void_t
TcpServer::accept(
    TcpServer      *a_serverSocket,
    std::tstring_t *a_fromIp
) const
{
    xTEST_EQ(_handle.isValid(), true);
    xTEST_PTR(a_serverSocket);
    xTEST_PTR(a_fromIp);

    sockaddr_in     cliaddr; Utils::structZeroT(cliaddr);
    socket_length_t addrlen = sizeof(cliaddr);

    socket_t client = ::accept(_handle.get(), Utils::reinterpretCastT<sockaddr *>( &cliaddr ),
        &addrlen);
    xTEST_DIFF(client, xSOCKET_HANDLE_INVALID);

#if 0
    // TODO: [skynowa] TcpServer::accept()
    scktAcceptSocket.assign(client);
#endif
    a_serverSocket->assign(client);

    std::string fromIp = ::inet_ntoa(cliaddr.sin_addr);

    *a_fromIp = xA2T(fromIp);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
