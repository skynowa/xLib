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

    bool_t        isReadable        () xWARN_UNUSED_RV;
        ///< checking for readability
    bool_t        isWritable        () xWARN_UNUSED_RV;
        ///< checking for writability
    void        connect           (const std::tstring_t &csIp, cushort_t &cusPort);
        ///< connecting

    void        ioctl             (clong_t &cliCmd, ulong_t *pulArgp);
        ///< controls the i/o mode
    void        setNonBlockingMode(cbool_t &cbFlag);
        ///< set nonblocking mode
    void        timeout           (long_t *pliSec, long_t *pliMicroSec);
        ///< get timeout
    void        setTimeout        (clong_t &cliSec, clong_t &cliMicroSec);
        ///< set timeout

    static bool_t isServerAlive     (const std::tstring_t &csIp, cushort_t &cusPort) xWARN_UNUSED_RV;
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

