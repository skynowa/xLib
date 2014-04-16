/**
 * \file  CxTcpServer.h
 * \brief server socket
 */


#pragma once

#ifndef xLib_CxTcpServerH
#define xLib_CxTcpServerH
//-------------------------------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, net)

class CxTcpServer :
    public CxSocket
    /// server socket
{
public:
             CxTcpServer() {}
        ///< constructor
    virtual ~CxTcpServer() {}
        ///< destructor

    void_t   bind(cushort_t &port) const;
        ///< associates a local address with a socket
    void_t   listen(cint_t &backlog = xSOCKET_CONNECTIONS_MAX) const;
        ///< places a socket in a state in which it is listening for an incoming connection
    void_t   accept(CxTcpServer *serverSocket, std::tstring_t *fromIp) const;
        ///< permits an incoming connection attempt on a socket

protected:
    timeval  _timeout;  ///< timeout

    xNO_COPY_ASSIGN(CxTcpServer)
};

xNAMESPACE2_END(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "CxTcpServer.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxTcpServerH


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
