/**
 * \file  TcpServer.h
 * \brief server socket
 */


#pragma once

#include <xLib/Net/ISocket.h>
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::net
{

class TcpServer final :
    public ISocket
    /// server socket
{
public:
///\name ctors, dtor
///\{
			 TcpServer() = default;
	virtual ~TcpServer() = default;

    xNO_COPY_ASSIGN(TcpServer);
///\}

    void_t   bind(cushort_t &port) const;
        ///< associates a local address with a socket
    void_t   listen(cint_t &backlog = xSOCKET_LISTEN_CONNECTIONS_MAX) const;
        ///< places a socket in a state in which it is listening for an incoming connection
    void_t   accept(TcpServer *serverSocket, std::tstring_t *fromIp) const;
        ///< permits an incoming connection attempt on a socket

protected:
    timeval _timeout {};  ///< timeout
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * Server
 *
 * - Initialize Winsock.
 * - Create a socket.
 * - Bind the socket.
 * - Listen on the socket for a client.
 * - Accept a connection from a client.
 * - Receive and send data.
 * - Disconnect.
*/
