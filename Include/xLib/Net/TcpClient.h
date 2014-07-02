/**
 * \file  TcpClient.h
 * \brief client socket
 */


#pragma once

#include <xLib/Net/Socket.h>
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, net)

class TcpClient :
    public Socket
    /// client socket
{
public:
             TcpClient();
        ///< constructor
    virtual ~TcpClient() {}
        ///< constructor

    bool_t   isReadable() const xWARN_UNUSED_RV;
        ///< checking for readability
    bool_t   isWritable() const xWARN_UNUSED_RV;
        ///< checking for writability
    void_t   connect(std::ctstring_t &ip, cushort_t &port) const;
        ///< connecting

    void_t   ioctl(clong_t &command, ulong_t *args) const;
        ///< controls the i/o mode
    void_t   setNonBlockingMode(cbool_t &flag) const;
        ///< set nonblocking mode
    void_t   timeout(long_t *seconds, long_t *microsec) const;
        ///< get timeout
    void_t   setTimeout(clong_t &seconds, clong_t &microsec);
        ///< set timeout

    static
    bool_t   isServerAlive(std::ctstring_t &ip, cushort_t &port) xWARN_UNUSED_RV;
        ///< is sever socket available

protected:
    timeval  _timeout;    ///< timeout

    xNO_COPY_ASSIGN(TcpClient)

xPLATFORM:
    void_t   _setNonBlockingMode_impl(cbool_t &flag) const;
};

// TODO: TcpClient::isWritable() - repeats from Socket
// TODO: TcpClient::isReadable() - repeats from Socket

xNAMESPACE_END2(xlib, net)
//-------------------------------------------------------------------------------------------------
#include "TcpClient.inl"


/**
    Client

    Initialize Winsock.
    Create a socket.
    Connect to the server.
    Send and receive data.
    Disconnect.
*/
