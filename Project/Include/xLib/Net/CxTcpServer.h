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
xNAMESPACE_BEGIN(NxLib)

class CxTcpServer :
    public CxSocket
    /// server socket
{
    public:
                 CxTcpServer();
            ///< constructor
        virtual ~CxTcpServer();
            ///< destructor

        void     vBind      (const ushort_t &cusPort);
            ///< associates a local address with a socket
        void     vListen    (const int &ciBacklog /* = SOMAXCONN*/);
            ///< places a socket in a state in which it is listening for an incoming connection
        void     vAccept    (CxTcpServer *pscktAcceptSocket, std::tstring_t *psFromIp);
            ///< permits an incoming connection attempt on a socket

    protected:
        timeval  _m_tvTimeout;  ///< timeout
};

xNAMESPACE_END(NxLib)
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
