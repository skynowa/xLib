/**
 * \file  TcpClient.h
 * \brief client socket
 */


#pragma once

#include <xLib/Net/ISocket.h>
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::net
{

class TcpClient final :
    public ISocket
    /// client socket
{
public:
///\name ctors, dtor
///\{
			 TcpClient();
	virtual ~TcpClient() = default;

	xNO_COPY_ASSIGN(TcpClient);
///\}

    void_t   connect(std::ctstring_t &ip, cushort_t &port) const;
        ///< connecting

    void_t   ioctl(clong_t &command, ulong_t *args) const;
        ///< controls the i/o mode
    void_t   setNonBlockingMode(cbool_t flag) const;
        ///< set nonblocking mode
    void_t   timeout(long_t *seconds, long_t *microsec) const;
        ///< get timeout
    void_t   setTimeout(clong_t &seconds, clong_t &microsec);
        ///< set timeout

    static
    bool_t   isServerAlive(std::ctstring_t &ip, cushort_t &port);
        ///< is sever socket available

protected:
    timeval  _timeout {};    ///< timeout

xPLATFORM_IMPL:
    void_t   _setNonBlockingMode_impl(cbool_t flag) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * Client
 *
 * - Initialize Winsock.
 * - Create a socket.
 * - Connect to the server.
 * - Send and receive data.
 * - Disconnect.
 */
