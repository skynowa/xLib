/**
 * \file  CxTcpServer.h
 * \brief server socket
 */


#ifndef xLib_Net_CxTcpServerH
#define xLib_Net_CxTcpServerH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxTcpServer :
    public CxSocket
    /// server socket
{
    public:
                    CxTcpServer();
            ///< constructor
        virtual    ~CxTcpServer();
        	///< destructor

        BOOL        bBind            (USHORT usPort);
        	///< associates a local address with a socket
        BOOL        bListen          (INT iBacklog /* = SOMAXCONN*/);
    		///< places a socket in a state in which it is listening for an incoming connection
        BOOL        bAccept          (CxTcpServer *pscktAcceptSocket, std::tstring *psFromIp);
    		///< permits an incoming connection attempt on a socket

    protected:
        timeval     _m_tvTimeout;		///< timeout
};
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxTcpServerH


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
