/**
 * \file  CxTcpClient.h
 * \brief client socket
 */


#ifndef xLib_Net_CxTcpClientH
#define xLib_Net_CxTcpClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Net/CxSocket.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTcpClient :
    public CxSocket
    /// client socket
{
    public:
                    CxTcpClient  ();
            ///< constructor
        virtual    ~CxTcpClient  ();
            ///< constructor

        bool        bIsReadable        ();
            ///< checking for readability
        bool        bIsWritable        ();
            ///< checking for writability
        bool        bConnect           (const std::tstring &csIp, USHORT usPort);
            ///< connecting

        bool        bIoctl             (LONG liCmd, ULONG *pulArgp);
            ///< controls the i/o mode
        bool        bSetNonBlockingMode(const bool cbFlag);
            ///< set nonblocking mode
        bool        bGetTimeout        (LONG *pliSec, LONG *pliMicroSec);
            ///< get timeout
        bool        bSetTimeout        (LONG liSec,   LONG liMicroSec);
            ///< set timeout

        static bool bIsServerAlive     (const std::tstring &csIp, USHORT usPort);
            ///< is sever socket available

    protected:
        timeval     _m_tvTimeout;    ///< timeout
};
//TODO: bIsWritable repeats from CxSocket
//TODO: bIsReadable repeats from CxSocket

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxTcpClientH


/*
Client

Initialize Winsock.
Create a socket.
Connect to the server.
Send and receive data.
Disconnect.
*/

