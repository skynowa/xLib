/**
 * \file  CxTcpServerSocket.h
 * \brief server socket
 */


#ifndef xLib_Net_CxTcpServerSocketH
#define xLib_Net_CxTcpServerSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxTcpServerSocket :
    public CxSocket
    /// server socket
{
    public:
                    CxTcpServerSocket();
            ///< constructor
        virtual    ~CxTcpServerSocket();
        	///< destructor

        BOOL        bBind            (USHORT usPort);
        	///< associates a local address with a socket
        BOOL        bListen          (INT iBacklog /* = SOMAXCONN*/);
    		///< places a socket in a state in which it is listening for an incoming connection
        BOOL        bAccept          (CxTcpServerSocket *pscktAcceptSocket, std::tstring *psFromIp);
    		///< permits an incoming connection attempt on a socket

    protected:
        timeval     _m_tvTimeout;		///< timeout
};
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxTcpServerSocketH


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
