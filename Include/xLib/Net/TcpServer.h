/**
 * \file  TcpServer.h
 * \brief server socket
 */


#pragma once

#include <xLib/Net/Socket.h>
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class TcpServer :
    public Socket
    /// server socket
{
public:
             TcpServer() {}
        ///< constructor
    virtual ~TcpServer() {}
        ///< destructor

    void_t   bind(cushort_t &port) const;
        ///< associates a local address with a socket
    void_t   listen(cint_t &backlog = xSOCKET_CONNECTIONS_MAX) const;
        ///< places a socket in a state in which it is listening for an incoming connection
    void_t   accept(TcpServer *serverSocket, std::tstring_t *fromIp) const;
        ///< permits an incoming connection attempt on a socket

protected:
    timeval  _timeout;  ///< timeout

    xNO_COPY_ASSIGN(TcpServer)
};

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "TcpServer.inl"
#endif


/*
Server

Initialize Winsock.
Create a socket.
Bind the socket.
Listen on the socket for a client.
Accept a connection from a client.
Receive and send data.
Disconnect.
*/
