/****************************************************************************
* Class name:  CxTcpClientSocket
* Description: client socket
* File name:   CxTcpClientSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.04.2009 6:21:18
*
*****************************************************************************/


#ifndef xLib_Net_CxTcpClientSocketH
#define xLib_Net_CxTcpClientSocketH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxSocket.h>
//---------------------------------------------------------------------------
//TODO: bIsReadable repeats from CxSocket
class CxTcpClientSocket : public CxSocket { 
    public: 
                    CxTcpClientSocket  ();
        virtual    ~CxTcpClientSocket  ();

        BOOL        bIsReadable        ();  //TODO: repeats from CxSocket
        BOOL        bIsWritable        ();  //TODO: repeats from CxSocket
        BOOL        bConnect           (const tString &csIp, USHORT usPort);

        BOOL        bIoctl             (LONG liCmd, ULONG *pulArgp);
        BOOL        bSetNonBlockingMode(const BOOL cbFlag);
        BOOL        bGetTimeout        (LONG *pliSec, LONG *pliMicroSec);
        BOOL        bSetTimeout        (LONG liSec,   LONG liMicroSec);

        static BOOL bIsServerAlive     (const tString &csIp, USHORT usPort);

    protected: 
        timeval     _m_tvTimeout;
}; 
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxTcpClientSocketH


/*

tString sStr = xT("Some string!!!");
::send(0, reinterpret_cast<char const*>(sStr.data()), sStr.size() * sizeof(tString::value_type), 0);

sizeof(tString::value_type)

*/


/*
Client

Initialize Winsock.
Create a socket.
Connect to the server.
Send and receive data.
Disconnect.
*/
 
