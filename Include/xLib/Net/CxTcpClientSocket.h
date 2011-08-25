/**
 * \file  CxTcpClientSocket.h
 * \brief client socket
 */


#ifndef xLib_Net_CxTcpClientSocketH
#define xLib_Net_CxTcpClientSocketH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxSocket.h>
//---------------------------------------------------------------------------
//TODO: bIsReadable repeats from CxSocket
class CxTcpClientSocket :
    public CxSocket
{
    public:
                    CxTcpClientSocket  ();
        virtual    ~CxTcpClientSocket  ();

        BOOL        bIsReadable        ();  //TODO: repeats from CxSocket
        BOOL        bIsWritable        ();  //TODO: repeats from CxSocket
        BOOL        bConnect           (const std::tstring &csIp, USHORT usPort);

        BOOL        bIoctl             (LONG liCmd, ULONG *pulArgp);
        BOOL        bSetNonBlockingMode(const BOOL cbFlag);
        BOOL        bGetTimeout        (LONG *pliSec, LONG *pliMicroSec);
        BOOL        bSetTimeout        (LONG liSec,   LONG liMicroSec);

        static BOOL bIsServerAlive     (const std::tstring &csIp, USHORT usPort);

    protected:
        timeval     _m_tvTimeout;
};
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxTcpClientSocketH


/*

std::tstring sStr = xT("Some string!!!");
::send(0, reinterpret_cast<char const*>(sStr.data()), sStr.size() * sizeof(std::tstring::value_type), 0);

sizeof(std::tstring::value_type)

*/


/*
Client

Initialize Winsock.
Create a socket.
Connect to the server.
Send and receive data.
Disconnect.
*/

