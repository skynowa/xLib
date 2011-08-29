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
class CxTcpClientSocket :
    public CxSocket
    /// client socket
{
    public:
                    CxTcpClientSocket  ();
            ///< constructor
        virtual    ~CxTcpClientSocket  ();
        	///< constructor

        BOOL        bIsReadable        ();
        	///< checking for readability
        BOOL        bIsWritable        ();
        	///< checking for writability
        BOOL        bConnect           (const std::tstring &csIp, USHORT usPort);
        	///< connecting

        BOOL        bIoctl             (LONG liCmd, ULONG *pulArgp);
        	///< controls the i/o mode
        BOOL        bSetNonBlockingMode(const BOOL cbFlag);
        	///< set nonblocking mode
        BOOL        bGetTimeout        (LONG *pliSec, LONG *pliMicroSec);
        	///< get timeout
        BOOL        bSetTimeout        (LONG liSec,   LONG liMicroSec);
        	///< set timeout

        static BOOL bIsServerAlive     (const std::tstring &csIp, USHORT usPort);
        	///< is sever socket available

    protected:
        timeval     _m_tvTimeout;	///< timeout
};
//TODO: bIsWritable repeats from CxSocket
//TODO: bIsReadable repeats from CxSocket
//---------------------------------------------------------------------------
#endif    //xLib_Net_CxTcpClientSocketH


/*
Client

Initialize Winsock.
Create a socket.
Connect to the server.
Send and receive data.
Disconnect.
*/

