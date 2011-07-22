/****************************************************************************
* Class name:  CxTcpServerSocket
* Description: server socket
* File name:   CxTcpServerSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.04.2009 6:21:18
*
*****************************************************************************/


#ifndef xLib_Net_CxTcpServerSocketH
#define xLib_Net_CxTcpServerSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxTcpServerSocket :
    public CxSocket
{
    public:
                    CxTcpServerSocket();
        virtual    ~CxTcpServerSocket();

        BOOL        bBind            (USHORT usPort);
        BOOL        bListen          (INT iBacklog /* = SOMAXCONN*/);
        BOOL        bAccept          (CxTcpServerSocket *pscktAcceptSocket, tString *psFromIp);

    protected:
        timeval     _m_tvTimeout;
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
