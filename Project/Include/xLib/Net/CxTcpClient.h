/**
 * \file  CxTcpClient.h
 * \brief client socket
 */


#ifndef xLib_Net_CxTcpClientH
#define xLib_Net_CxTcpClientH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
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
        bool        bConnect           (const std::tstring_t &csIp, ushort_t usPort);
            ///< connecting

        bool        bIoctl             (long_t liCmd, ulong_t *pulArgp);
            ///< controls the i/o mode
        bool        bSetNonBlockingMode(const bool cbFlag);
            ///< set nonblocking mode
        bool        bGetTimeout        (long_t *pliSec, long_t *pliMicroSec);
            ///< get timeout
        bool        bSetTimeout        (long_t liSec,   long_t liMicroSec);
            ///< set timeout

        static bool bIsServerAlive     (const std::tstring_t &csIp, ushort_t usPort);
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

