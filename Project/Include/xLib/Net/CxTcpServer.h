/**
 * \file  CxTcpServer.h
 * \brief server socket
 */


#pragma once

#include <xLib/Net/CxSocket.h>
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTcpServer :
    public CxSocket
    /// server socket
{
public:
             CxTcpServer() {}
        ///< constructor
    virtual ~CxTcpServer() {}
        ///< destructor

    void_t   bind(cushort_t &port);
        ///< associates a local address with a socket
    void_t   listen(cint_t &backlog /* = SOMAXCONN*/);
        ///< places a socket in a state in which it is listening for an incoming connection
    void_t   accept(CxTcpServer *serverSocket, std::tstring_t *fromIp);
        ///< permits an incoming connection attempt on a socket

protected:
    timeval  _timeout;  ///< timeout
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Net/CxTcpServer.inl>


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
