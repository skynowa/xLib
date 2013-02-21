/**
 * \file  CxTcpClient.h
 * \brief client socket
 */


#ifndef xLib_Net_CxTcpClientH
#define xLib_Net_CxTcpClientH
//------------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTcpClient :
    public CxSocket
    /// client socket
{
public:
                CxTcpClient       ();
        ///< constructor
    virtual    ~CxTcpClient       ();
        ///< constructor

    bool        isReadable        () xWARN_UNUSED_RESULT;
        ///< checking for readability
    bool        isWritable        () xWARN_UNUSED_RESULT;
        ///< checking for writability
    void        connect           (const std::tstring_t &csIp, const ushort_t &cusPort);
        ///< connecting

    void        ioctl             (const long_t &cliCmd, ulong_t *pulArgp);
        ///< controls the i/o mode
    void        setNonBlockingMode(const bool &cbFlag);
        ///< set nonblocking mode
    void        timeout           (long_t *pliSec, long_t *pliMicroSec);
        ///< get timeout
    void        setTimeout        (const long_t &cliSec, const long_t &cliMicroSec);
        ///< set timeout

    static bool isServerAlive     (const std::tstring_t &csIp, const ushort_t &cusPort) xWARN_UNUSED_RESULT;
        ///< is sever socket available

protected:
    timeval     _m_tvTimeout;    ///< timeout
};
//TODO: bIsWritable repeats from CxSocket
//TODO: bIsReadable repeats from CxSocket

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Net_CxTcpClientH


/*
Client

Initialize Winsock.
Create a socket.
Connect to the server.
Send and receive data.
Disconnect.
*/

