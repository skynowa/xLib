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
    void        vConnect           (const std::tstring_t &csIp, const ushort_t &cusPort);
        ///< connecting

    void        vIoctl             (const long_t &cliCmd, ulong_t *pulArgp);
        ///< controls the i/o mode
    void        vSetNonBlockingMode(const bool &cbFlag);
        ///< set nonblocking mode
    void        vTimeout           (long_t *pliSec, long_t *pliMicroSec);
        ///< get timeout
    void        vSetTimeout        (const long_t &cliSec, const long_t &cliMicroSec);
        ///< set timeout

    static bool bIsServerAlive     (const std::tstring_t &csIp, const ushort_t &cusPort);
        ///< is sever socket available

protected:
    timeval     _m_tvTimeout;    ///< timeout
};
//TODO: bIsWritable repeats from CxSocket
//TODO: bIsReadable repeats from CxSocket

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Net_CxTcpClientH


/*
Client

Initialize Winsock.
Create a socket.
Connect to the server.
Send and receive data.
Disconnect.
*/

